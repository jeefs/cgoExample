#ifdef __cplusplus
extern "C" {
#endif

#include "../data_handle/cgm_data_handle.h"
//#include "my_struct_2_json.inc"
#include "cJSON.h"
#include "s2j.h"


cJSON *struct_to_json_cgmv120_cmd_ack_t(void* struct_obj);

void *json_to_struct_cgmv120_cmd_ack_t(cJSON* json_obj);

cJSON* struct_to_json_cgmv120_only_glouse_info_t(void* struct_obj);

void* json_to_struct_cgmv120_only_glouse_info_t(cJSON* json_obj);

cJSON* struct_to_json_cgmv120_only_lactate_info_t(void* struct_obj);

void* json_to_struct_cgmv120_only_lactate_info_t(cJSON* json_obj);

cJSON* struct_to_json_cgmv120_lactate_info_t(void* struct_obj);

void* json_to_struct_cgmv120_lactate_info_t(cJSON* json_obj);

cJSON *struct_to_json_cgmv120_glouse_info_t(void* struct_obj);

void *json_to_struct_cgmv120_glouse_info_t(cJSON* json_obj);

cJSON *struct_to_json_cgmv120_device_time_t(void* struct_obj);

void *json_to_struct_cgmv120_device_time_t(cJSON* json_obj);

cJSON *struct_to_json_cgmv120_device_storage_t(void* struct_obj);

void *json_to_struct_cgmv120_device_storage_t(cJSON* json_obj);

cJSON *struct_to_json_cgmv120_device_calibration_t(void* struct_obj);

void *json_to_struct_cgmv120_device_calibration_t(cJSON* json_obj);

cJSON *struct_to_json_cgmv120_device_key_t(void* struct_obj);

void *json_to_struct_cgmv120_device_key_t(cJSON* json_obj);

cJSON *struct_to_json_cgmv120_device_reset_t(void* struct_obj);

void *json_to_struct_cgmv120_device_reset_t(cJSON* json_obj);

cJSON* struct_to_json_cgmv120_u8activation(void* struct_obj);

void* json_to_struct_cgmv120_u8activation(cJSON* json_obj);

cJSON* struct_to_json_cgmv120_u16sens_t(void* struct_obj);

void* json_to_struct_cgmv120_u16sens_t(cJSON* json_obj);

cJSON* struct_to_json_cgmv120_glousethreshold_t(void* struct_obj);

void* json_to_struct_cgmv120_glousethreshold_t(cJSON* json_obj);

cJSON* struct_to_json_cgmv120_oscillator_t(void* struct_obj);

void* json_to_struct_cgmv120_oscillator_t(cJSON* json_obj);
/**********************************V110**************************************************************/
cJSON* struct_to_json_cgmv110_three_glouse_info_t(void* struct_obj);

void* json_to_struct_cgmv110_three_glouse_info_t(cJSON* json_obj);

cJSON* struct_to_json_cgmv110_glouse_info_t(void* struct_obj);

void* json_to_struct_cgmv110_glouse_info_t(cJSON* json_obj);

cJSON* struct_to_json_cgmv110_cmd_ack_t(void* struct_obj);

void* json_to_struct_cgmv110_cmd_ack_t(cJSON* json_obj);

cJSON* struct_to_json_cgmv120_secret_key_t(void* struct_obj);

void* json_to_struct_cgmv120_secret_key_t(cJSON* json_obj);

#ifdef __cplusplus
}
#endif /* end of __cplusplus */