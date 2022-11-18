/************************************************************************
 * @file ticos_config.h
 * @brief 项目配置文件
 * @date 2022-11-18 11:12:03
 ************************************************************************/

#ifndef __TICOS_CONFIG_H
#define __TICOS_CONFIG_H

#include <ticos/bus_center.h>
#include <ticos/device_center.h>

#include <ticos/device/gpio.h>
#include "ticos_iot.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * 向工程注册总线
 ************************************************************************/
TICOS_BUS_BEGIN
    // TODO 注册更多总线
TICOS_BUS_END

/************************************************************************
 * 向工程注册设备
 ************************************************************************/
TICOS_DEV_BEGIN
    TICOS_DEV(DEV_IOT, ticos_iot,
             /* 请填充测试所需的 WiFi ssid */
             .ssid="TP-LINK_FF1E",
             /* 请填充测试所需的 WiFi password */
             .pswd="abcD1234",
             /* 请填充测试所需的 mqtt fqdn */
             .fqdn="mqtt://hub.ticos.cn",
             /* 请填充测试所需的 product id */
             .product_id="HITXM3K4IE",
              /* 请填充测试所需的 device id */
             .device_id="SLC1",
             /* 请填充测试所需的 security key */
             .secret_key="AxMrpqHTlErAEfsXEl0rJQ==")
    // TODO 注册更多设备
    TICOS_DEV(DEV_IO0, ticos_gpio, .pin=0, .mode=TICOS_GPIO_MODE_INPUT)
    TICOS_DEV(DEV_IO23, ticos_gpio, .pin=23, .mode=TICOS_GPIO_MODE_OUTPUT)
TICOS_DEV_END

#ifdef __cplusplus
}
#endif

#endif // __TICOS_CONFIG_H
