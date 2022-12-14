/************************************************************************
 * @file ticos_iot
 * @brief 设备接口实现
 * @author
 * @date 2022-11-18 14:50:00
 * @copyright
 ************************************************************************/

#include "ticos_iot.h"
#include <ticos/nil/wifi.h>
#include <ticos_api.h>

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备“打开”操作，
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_iot_open(ticos_iot_t* self) {
    ticos_wifi_start_as_sta(self->ssid, self->pswd);
    ticos_cloud_start(self->product_id, self->device_id, self->secret_key);
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备“关闭”操作，
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_iot_close(ticos_iot_t* self) {
    TICOS_UNUSED(self);
    ticos_cloud_stop();
    ticos_wifi_stop();
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，系统改变“电源模式”时被动触发，
 * @param[in] self 类实例
 * @param[in] mode 更改后的电源模式
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_iot_power_mode_changed(ticos_iot_t* self, ticos_power_mode_t mode) {
    /* 填充代码内容后请删除TICOS_UNUSED函数调用 */
    TICOS_UNUSED(self);
    TICOS_UNUSED(mode);
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备数据从缓存复制到应用层的复制操作
 * @attention 此函数为自动生成，请不要更改函数内容
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_iot_sync_from_cache(ticos_iot_t* self) {
    ticos_sync_from_cache(self, prop_switch);
    ticos_sync_from_cache(self, prop_led);
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备数据从应用层到缓存的复制操作
 * @attention 此函数为自动生成，请不要更改函数内容
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_iot_post_to_cache(ticos_iot_t* self) {
    ticos_post_to_cache(self, prop_switch);
    ticos_post_to_cache(self, prop_led);
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备数据从传感器到缓存的获取操作
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_iot_sync_from_dev(ticos_iot_t* self) {
    TICOS_UNUSED(self);
    return TICOS_OK;
}

/************************************************************************
 * @brief 必须实现的类成员函数，负责设备数据从缓存到传感器的提交操作
 * @param[in] self 类实例
 * @return 返回操作结果 TICOS_OK: 成功, TICOS_FAIL: 失败
 ************************************************************************/
int ticos_iot_post_to_dev(ticos_iot_t* self) {
    if (ticos_cache_isdirty(self, prop_switch)
     || ticos_cache_isdirty(self, prop_led)) {
        ticos_property_report();
    }
    return TICOS_OK;
}
