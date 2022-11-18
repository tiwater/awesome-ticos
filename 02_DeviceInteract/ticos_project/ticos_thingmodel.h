/************************************************************************
 * @file ticos_thingmodel.h
 * @brief 物模型接口头文件
 * @date 2022-11-18 17:50:09
 * @note 此文件为自动生成，请不要更改文件内容
 ************************************************************************/

#ifndef __TICOS_THING_MODEL_H
#define __TICOS_THING_MODEL_H

#include <ticos/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TICOS_TELEMETRY_switch,
    TICOS_TELEMETRY_MAX,
} ticos_telemetry_t;

typedef enum {
    TICOS_PROPERTY_MAX,
} ticos_property_t;

typedef enum {
    TICOS_COMMAND_MAX,
} ticos_command_t;

bool ticos_telemetry_switch_send(void);

#ifdef __cplusplus
}
#endif

#endif // __TICOS_THING_MODEL_H
