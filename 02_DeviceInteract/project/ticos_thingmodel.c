/************************************************************************
 * @file ticos_thingmodel.c
 * @brief 物模型接口实现
 * @author
 * @details 此文件为自动生成，请不要更改文件内容
 * @date: 2022-11-06 14:31:56
 * @copyright
 ************************************************************************/

#include "ticos_thingmodel.h"
#include <ticos_thingmodel_type.h>
#include <ticos/device_center.h>
#include "ticos_iot.h"

bool ticos_telemetry_switch_send(void) {
    ticos_iot_t* iot = ticos_dev(0, ticos_iot);
    return ticos_cache_get(iot, tele_switch);
}

const ticos_telemetry_info_t ticos_telemetry_tab[] = {
    { "switch", TICOS_VAL_TYPE_BOOLEAN,  ticos_telemetry_switch_send },
};

const ticos_property_info_t ticos_property_tab[] = {
};

const ticos_command_info_t ticos_command_tab[] = {
};

const int ticos_telemetry_cnt = TICOS_TELEMETRY_MAX;
const int ticos_property_cnt = TICOS_PROPERTY_MAX;
const int ticos_command_cnt = TICOS_COMMAND_MAX;
