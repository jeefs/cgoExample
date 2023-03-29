#include "my_struct_2_json.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#if 0
typedef struct
{
	uint16_t u16reply_ack_type;
	uint8_t u8reply_ack_resule;
	uint8_t u8error_code;
}cgmv120_cmd_ack_t;
#endif

cJSON *struct_to_json_cgmv120_cmd_ack_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_cmd_ack_t *struct_obj_ = (cgmv120_cmd_ack_t *)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u16reply_ack_type);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u8reply_ack_resule);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u8error_code);
	return json_obj_;
}

void *json_to_struct_cgmv120_cmd_ack_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_cmd_ack_t);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u16reply_ack_type);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u8reply_ack_resule);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u8error_code);
	return struct_obj_;
}

#if 0
typedef struct
{
	uint16_t u16index;
	uint16_t reindex;
	uint16_t u16glouse;
	uint8_t u8trend;
	uint8_t u8gwarn;
	bool btwarn;
	bool bcwarn;
	uint32_t itime;
}cgmv120_only_glouse_info_t;
#endif
cJSON *struct_to_json_cgmv120_only_glouse_info_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_only_glouse_info_t*struct_obj_ = (cgmv120_only_glouse_info_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, index);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, reindex);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, glouse);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, trend);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, gwarn);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, twarn);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, cwarn);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, itime);
	return json_obj_;
}

void *json_to_struct_cgmv120_only_glouse_info_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_glouse_info_t);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, index);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, reindex);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, glouse);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, trend);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, gwarn);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, twarn);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, cwarn);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, itime);
	return struct_obj_;
}


#if 0
typedef struct
{
	uint16_t index;
	uint16_t reindex;
	uint16_t lactate;
	uint8_t twarn;
	uint8_t cwarn;
	uint32_t itime;
}cgmv120_only_lactate_info_t;
#endif
cJSON* struct_to_json_cgmv120_only_lactate_info_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_only_lactate_info_t* struct_obj_ = (cgmv120_only_lactate_info_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, index);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, reindex);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, lactate);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, twarn);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, cwarn);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, itime);
	return json_obj_;
}

void* json_to_struct_cgmv120_only_lactate_info_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_only_lactate_info_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, index);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, reindex);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, lactate);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, twarn);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, cwarn);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, itime);

	return struct_obj_;
}


#if 0
typedef struct
{
	uint16_t index;
	uint16_t temp;
	uint16_t current;
	uint16_t dump;
	uint16_t reindex;

	uint16_t lactate;
	uint8_t twarn;
	uint8_t cwarn;
	uint32_t itime;
}cgmv120_lactate_info_t;
#endif
cJSON* struct_to_json_cgmv120_lactate_info_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_lactate_info_t* struct_obj_ = (cgmv120_lactate_info_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, index);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, temp);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, current);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, dump);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, reindex);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, lactate);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, twarn);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, cwarn);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, itime);
	return json_obj_;
}

void* json_to_struct_cgmv120_lactate_info_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_lactate_info_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, index);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, temp);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, current);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, dump);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, reindex);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, lactate);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, twarn);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, cwarn);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, itime);

	return struct_obj_;
}

#if 0
typedef struct
{
	uint8_t u8secret_key_num;
	uint8_t p8secret_key1[16];
	uint8_t p8secret_key2[16];

}cgmv120_secret_key_t;
#endif

cJSON* struct_to_json_cgmv120_secret_key_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_secret_key_t* struct_obj_ = (cgmv120_secret_key_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u8secret_key_num);
	s2j_json_set_array_element(json_obj_, struct_obj_, int, p8secret_key1,16);
	s2j_json_set_array_element(json_obj_, struct_obj_, int, p8secret_key2,16);
	return json_obj_;
}

void* json_to_struct_cgmv120_secret_key_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_secret_key_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, u8secret_key_num);
	s2j_struct_get_array_element(struct_obj_, json_obj, int, p8secret_key1);
	s2j_struct_get_array_element(struct_obj_, json_obj, int, p8secret_key2);
	return struct_obj_;
}


#if 0
typedef struct
{
	uint16_t u16index;
	uint16_t u16temp;
	uint16_t u16current;
	uint16_t u16dump;
	uint16_t reindex;

	uint16_t u16glouse;
	uint8_t u8trend;
	uint8_t u8gwarn;
	bool btwarn;
	bool bcwarn;
	uint32_t itime;
}cgmv120_glouse_info_t;
#endif
cJSON* struct_to_json_cgmv120_glouse_info_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_glouse_info_t* struct_obj_ = (cgmv120_glouse_info_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, index);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, temp);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, current);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, dump);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, reindex);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, glouse);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, trend);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, gwarn);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, twarn);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, cwarn);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, itime);
	return json_obj_;
}

void* json_to_struct_cgmv120_glouse_info_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_glouse_info_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, index);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, temp);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, current);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, dump);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, reindex);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, glouse);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, trend);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, gwarn);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, twarn);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, cwarn);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, itime);
	return struct_obj_;
}

#if 0
typedef struct
{
	uint32_t iactivation_time;
	uint32_t icurrent_time;
	uint32_t ilast_time;
	uint16_t u16last_index;
}cgmv120_device_time_t;
#endif
cJSON *struct_to_json_cgmv120_device_time_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_device_time_t *struct_obj_ = (cgmv120_device_time_t *)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u16startover_time);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, iactivation_time);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, icurrent_time);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, ilast_time);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u16last_index);
	return json_obj_;
}

void *json_to_struct_cgmv120_device_time_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_device_time_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, u16startover_time);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, iactivation_time);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, icurrent_time);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, ilast_time);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u16last_index);
	return struct_obj_;
}

#if 0
typedef struct
{
	uint8_t u8storage_status;
	uint16_t u16storage_number;
	uint8_t u8config_times;
	uint8_t u8key_times;
}cgmv120_device_storage_t;
#endif
cJSON *struct_to_json_cgmv120_device_storage_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_device_storage_t *struct_obj_ = (cgmv120_device_storage_t *)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u8storage_status);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u16storage_number);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u8config_times);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u8key_times);
	return json_obj_;
}

void *json_to_struct_cgmv120_device_storage_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_device_storage_t);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u8storage_status);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u16storage_number);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u8config_times);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u8key_times);
	return struct_obj_;
}

#if 0
typedef struct
{
	uint32_t icurrent0;
	uint32_t icurrent1;
	uint32_t itemp0;
	uint32_t itemp1;
}cgmv120_device_calibration_t;
#endif
cJSON *struct_to_json_cgmv120_device_calibration_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_device_calibration_t *struct_obj_ = (cgmv120_device_calibration_t *)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, icurrent0);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, icurrent1);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, itemp0);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, itemp1);
	return json_obj_;
}

void *json_to_struct_cgmv120_device_calibration_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_device_calibration_t);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, icurrent0);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, icurrent1);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, itemp0);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, itemp1);
	return struct_obj_;
}



#if 0
typedef struct
{
	uint8_t u8reset_times;
	uint8_t u8reset_synchron;
	uint16_t u16reset_index;
	uint32_t ireset_time_stamp;
}cgmv120_device_reset_t;
#endif
cJSON *struct_to_json_cgmv120_device_reset_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_device_reset_t *struct_obj_ = (cgmv120_device_reset_t *)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u8reset_times);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u8reset_synchron);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u16reset_index);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, ireset_time_stamp);
	return json_obj_;
}

void *json_to_struct_cgmv120_device_reset_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_device_reset_t);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u8reset_times);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u8reset_synchron);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, u16reset_index);
	s2j_struct_get_basic_element(struct_obj_,json_obj, int, ireset_time_stamp);
	return struct_obj_;
}

#if 0
typedef struct {
	uint8_t  u8activation;
}cgmv120_u8activation;
#endif
cJSON* struct_to_json_cgmv120_u8activation(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_u8activation* struct_obj_ = (cgmv120_u8activation*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u8activation);
	return json_obj_;
}

void* json_to_struct_cgmv120_u8activation(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_u8activation);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, u8activation);
	return struct_obj_;
}

#if 0
typedef struct {
	uint16_t u16sens;
}cgmv120_u16sens_t;
#endif
cJSON* struct_to_json_cgmv120_u16sens_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_u16sens_t* struct_obj_ = (cgmv120_u16sens_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u16sens);
	return json_obj_;
}

void* json_to_struct_cgmv120_u16sens_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_u16sens_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, u16sens);
	return struct_obj_;
}



#if 0
typedef struct {
	uint16_t  upper;
	uint16_t  lower;
}cgmv120_glousethreshold_t;
#endif
cJSON* struct_to_json_cgmv120_glousethreshold_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_glousethreshold_t* struct_obj_ = (cgmv120_glousethreshold_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, upper);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, lower);
	return json_obj_;
}

void* json_to_struct_cgmv120_glousethreshold_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_glousethreshold_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, upper);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, lower);
	return struct_obj_;
}


#if 0
typedef struct
{
	uint8_t state;
}cgmv120_oscillator_t;
#endif
cJSON* struct_to_json_cgmv120_oscillator_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv120_oscillator_t* struct_obj_ = (cgmv120_oscillator_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, state);
	return json_obj_;
}

void* json_to_struct_cgmv120_oscillator_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv120_oscillator_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, state);
	return struct_obj_;
}


#if 0
typedef struct {
	uint16_t index;
	uint16_t temp;
	uint16_t current;
	uint16_t current2;
	uint16_t current3;
	uint16_t dump;
	uint16_t status;
	uint16_t leftsend;
	uint16_t nexttime;
}cgmv110_three_glouse_info_t;
#endif
cJSON* struct_to_json_cgmv110_three_glouse_info_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv110_three_glouse_info_t* struct_obj_ = (cgmv110_three_glouse_info_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, index);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, temp);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, current);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, current2);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, current3);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, dump);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, status);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, leftsend);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, nexttime);
	return json_obj_;
}

void* json_to_struct_cgmv110_three_glouse_info_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv110_three_glouse_info_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, index);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, temp);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, current);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, current2);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, current3);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, dump);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, status);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, leftsend);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, nexttime);
	return struct_obj_;
}


#if 0
typedef struct {
	uint16_t u16index;
	uint16_t u16temp;
	uint16_t u16current;
	uint16_t u16dump;
	uint16_t u16status;
	uint16_t leftsend;
	uint16_t nexttime;
}cgmv110_glouse_info_t;
#endif
cJSON* struct_to_json_cgmv110_glouse_info_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv110_glouse_info_t* struct_obj_ = (cgmv110_glouse_info_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, index);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, temp);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, current);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, dump);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, status);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, leftsend);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, nexttime);
	return json_obj_;
}

void* json_to_struct_cgmv110_glouse_info_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv110_glouse_info_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, index);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, temp);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, current);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, dump);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, status);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, leftsend);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, nexttime);
	return struct_obj_;
}

#if 0
typedef struct {
	uint16_t u16reply_ack_type;
	uint8_t  u8reply_ack_resule;
}cgmv110_cmd_ack_t;
#endif
cJSON* struct_to_json_cgmv110_cmd_ack_t(void* struct_obj)
{
	s2j_create_json_obj(json_obj_);
	cgmv110_cmd_ack_t* struct_obj_ = (cgmv110_cmd_ack_t*)struct_obj;
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u16reply_ack_type);
	s2j_json_set_basic_element(json_obj_, struct_obj_, int, u8reply_ack_resule);
	return json_obj_;
}

void* json_to_struct_cgmv110_cmd_ack_t(cJSON* json_obj)
{
	s2j_create_struct_obj(struct_obj_, cgmv110_cmd_ack_t);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, u16reply_ack_type);
	s2j_struct_get_basic_element(struct_obj_, json_obj, int, u8reply_ack_resule);
	return struct_obj_;
}


#ifdef DEBUGS2J 
 int s2j_test(void)
 {
	
    char file_name[] = "struct_defination.json";
    FILE *fp;

    fp = fopen(file_name, "w");
    if (NULL == fp) return 1;
    fprintf(fp,"{\n\t\"struct\": [\n\t\t{\n\t\t\t\"type\": \"void*\",\n\t\t\t\"value\": null\n\t\t}"); 

    TEST_S2J_STRUCT(cgmv120_cmd_ack_t, 0 , fp);
    TEST_S2J_STRUCT(cgmv120_glouse_info_t, 0 , fp);
    TEST_S2J_STRUCT(cgmv120_device_time_t, 0 , fp);
    TEST_S2J_STRUCT(cgmv120_device_storage_t, 0 , fp);
    TEST_S2J_STRUCT(cgmv120_device_calibration_t, 0 , fp);
    TEST_S2J_STRUCT(cgmv120_device_key_t, 0 , fp);
    TEST_S2J_STRUCT(cgmv120_device_reset_t, 0 , fp);
    
    fprintf(fp,"\n\t]\n}");
    fclose(fp);
    return 0;
}



 int s2j_test2(void)
 {

    char file_name[] = "struct_defination.json";
    FILE *fp;

    fp = fopen(file_name, "rb");
    if (NULL == fp) return 1;

   fseek(fp,0L,SEEK_END);
   int flen=ftell(fp);
   char* p=(char *)malloc(flen+1);
   if(p==NULL)
   {
        fclose(fp);
        return 0;
    }
    fseek(fp,0L,SEEK_SET);
    fread(p,flen,1,fp);
    p[flen]=0;

    printf("\nstruct_defination.json:\n%s\n",p);

    cJSON *json_obj =cJSON_Parse(p);
    CHECK_NOT_NULL(json_obj)
    cJSON *json_struct = cJSON_GetObjectItem(json_obj, "struct");
    CHECK_NOT_NULL(json_struct)

    int array_size = cJSON_GetArraySize(json_struct);
    printf("\nsize:\n%d\n",array_size);
    int i = 0; \

    TEST_S2J_JSON(cgmv120_cmd_ack_t, array_size);
    TEST_S2J_JSON(cgmv120_glouse_info_t, array_size);
    TEST_S2J_JSON(cgmv120_device_time_t, array_size);
    TEST_S2J_JSON(cgmv120_device_storage_t, array_size);
    TEST_S2J_JSON(cgmv120_device_calibration_t, array_size);
    TEST_S2J_JSON(cgmv120_device_key_t, array_size);
    TEST_S2J_JSON(cgmv120_device_reset_t, array_size);
    
    fclose(fp);
    free(p);
    return 0;
}


#endif// DEBUGS2J

#ifdef __cplusplus
}
#endif /* end of __cplusplus */