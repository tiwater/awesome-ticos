/************************************************************************
 * @file ticos_project.ino
 * @brief 项目程序入口
 * @author
 * @date 2022-11-18 14:50:00
 * @copyright
 ************************************************************************/

/************************************************************************
 * 设置ticos_onloop函数触发间隔，若不设置，则默认为200毫秒
 ************************************************************************/
#define TICOS_HEARTBEAT_MILLIS 250

#include "ticos_project.h"

static bool g_light_on;

static void set_light(bool on) {
    // 获得物模型接口
    ticos_iot_t* iot = ticos_dev(DEV_IOT);
    // 设置属性值以同步至云端
    ticos_set(iot, prop_led, on);

    // 设置 LED 物理状态
    ticos_dev_setval(DEV_IO23, level, on);

    // 记录当前 LED 状态
    g_light_on = on;
}
static inline void switch_light(void) {
    set_light(!g_light_on);
}
/************************************************************************
 * 生命周期函数，负责系统启动后的自定义初始化工作
 ************************************************************************/
int ticos_onboot(void) {
    return TICOS_OK;
}

/************************************************************************
 * 生命周期函数，按照一定时间间隔(TICOS_HEARTBEAT_MILLIS)触发
 ************************************************************************/
int ticos_onloop(void) {
    ticos_gpio_t* io_0 = ticos_dev(DEV_IO0);
    if (ticos_isdirty(io_0, level)) {
        // GPIO0 被释放
        if (!ticos_get(io_0, level)) {
            switch_light();
        }
    }
    ticos_iot_t* iot = ticos_dev(DEV_IOT);
    if (ticos_isdirty(iot, prop_led)) {
        // led 属性有改变
        bool on = ticos_get(iot, prop_led);
        set_light(on);
    }
    return TICOS_OK;
}
