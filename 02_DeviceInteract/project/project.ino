/************************************************************************
 * 设置ticos_onloop函数触发间隔，若不设置，则默认为200毫秒
 ************************************************************************/
#define TICOS_HEARTBEAT_MILLIS 250

#include <ticos_framework.h>
#include "ticos_iot.h"
#include <ticos/device/gpio.h>

/* 请填充测试所需的 WiFi ssid */
#define _SSID ""
/* 请填充测试所需的 WiFi password */
#define _PSWD ""
/* 请填充测试所需的 mqtt fqdn */
#define _FQDN "mqtt://hub.ticos.cn"
/* 请填充测试所需的 product id */
#define _PRD_ID ""
/* 请填充测试所需的 device id */
#define _DEV_ID ""
/* 请填充测试所需的 security key */
#define _SKEY   ""

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
    // TODO 更多设备标识号
TICOS_DEV_ID_END

/************************************************************************
 * 生命周期函数，负责系统启动后的自定义初始化工作
 ************************************************************************/
int ticos_onboot(void) {
    TICOS_DEV(DEV_IOT, ticos_iot, .ssid=_SSID, .pswd=_PSWD, .fqdn=_FQDN,
            .product_id=_PRD_ID, .device_id=_DEV_ID, .secret_key=_SKEY);
    TICOS_DEV(DEV_IO0, ticos_gpio, .pin=0, .mode=TICOS_GPIO_MODE_INPUT);
    return TICOS_OK;
}

/************************************************************************
 * 生命周期函数，按照一定时间间隔(TICOS_HEARTBEAT_MILLIS)触发
 ************************************************************************/
int ticos_onloop(void) {
    ticos_iot_t* iot = ticos_dev(DEV_IOT, ticos_iot);
    ticos_gpio_t* io_0 = ticos_dev(DEV_IO0, ticos_gpio);
    if (ticos_isdirty(io_0, level)) {
        // 按键被按动，将按键物理状态传入物模型
        ticos_set(iot, tele_switch, ticos_get(io_0, level));
    }
    return TICOS_OK;
}
