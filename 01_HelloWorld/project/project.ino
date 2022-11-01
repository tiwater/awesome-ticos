/************************************************************************
 * 设置ticos_onloop函数触发间隔，若不设置，则默认为200毫秒
 ************************************************************************/
#define TICOS_HEARTBEAT_MILLIS 250

#include <ticos_framework.h>
#include <ticos/device/gpio.h>
#include "ticos_iot.h"

/* 请填充测试所需的 WiFi ssid */
#define _SSID "CSJ-M17"
/* 请填充测试所需的 WiFi password */
#define _PSWD "Kechuangzhongxin"
/* 请填充测试所需的 mqtt fqdn */
#define _FQDN "mqtt://hub.ticos.cn"
/* 请填充测试所需的 product id */
#define _PRD_ID "HITXM3K4IE"
/* 请填充测试所需的 device id */
#define _DEV_ID "SLC1"
/* 请填充测试所需的 security key */
#define _SKEY   "AxMrpqHTlErAEfsXEl0rJQ=="

/************************************************************************
 * 向工程注册总线标识号，请将此标识号列表成员作为TICOS_BUS_ADD首参
 ************************************************************************/
TICOS_BUS_ID_BEGIN
    // TODO 更多总线标识号
TICOS_BUS_ID_END

/************************************************************************
 * 向工程注册设备标识号，请将此标识号列表成员作为TICOS_DEV_ADD首参
 ************************************************************************/
TICOS_DEV_ID_BEGIN
    DEV_IOT,
    DEV_IO0,
    DEV_IO23,
    // TODO 更多设备标识号
TICOS_DEV_ID_END

/************************************************************************
 * 生命周期函数，负责系统启动后的自定义初始化工作
 ************************************************************************/
int ticos_onboot(void) {
    TICOS_DEV_ADD(DEV_IOT, ticos_iot, .ssid=_SSID, .pswd=_PSWD, .fqdn=_FQDN, .product_id=_PRD_ID, .device_id=_DEV_ID, .secret_key=_SKEY);
    TICOS_DEV_ADD(DEV_IO0, ticos_gpio, .pin=0, .mode=TICOS_GPIO_MODE_INPUT);
    TICOS_DEV_ADD(DEV_IO23, ticos_gpio, .pin=23, .mode=TICOS_GPIO_MODE_OUTPUT);
    return TICOS_OK;
}
static bool g_light_on;

static void set_light(bool on) {
    // 获得物模型接口
    ticos_iot_t* iot = ticos_dev(DEV_IOT, ticos_iot);
    // 设置属性值以同步至云端
    ticos_set(iot, prop_led, on);

    // 设置 LED 物理状态
    ticos_dev_setval(DEV_IO23, ticos_gpio, level, on);

    // 记录当前 LED 状态
    g_light_on = on;
}

static inline void switch_light(void) {
    set_light(!g_light_on);
}
/************************************************************************
 * 生命周期函数，按照一定时间间隔(TICOS_HEARTBEAT_MILLIS)触发
 ************************************************************************/
int ticos_onloop(void) {
    ticos_gpio_t* io_0 = ticos_dev(DEV_IO0, ticos_gpio);
    if (ticos_isdirty(io_0, level)) {
        // GPIO23 被释放
        if (!ticos_get(io_0, level)) {
            switch_light();
        }
    }
    
    ticos_iot_t* iot = ticos_dev(DEV_IOT, ticos_iot);
    if (ticos_isdirty(iot, prop_led)) {
        // led 属性有改变
        bool on = ticos_get(iot, prop_led);
        set_light(on);
    }
    return TICOS_OK;
}
