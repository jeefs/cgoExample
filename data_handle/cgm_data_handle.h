#ifndef _CGM_DATA_HANDLE_H
#define _CGM_DATA_HANDLE_H

#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"

#ifdef _WINDOWS


#ifndef DLLEXPORT
#define DLLEXPORT  __declspec(dllexport)
#endif

#else
#ifndef DLLEXPORT
#define DLLEXPORT
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif


#define ALGORITHM_VERSION   "V1.3.2_2022_07_14"
/********************************V120底软协议*************************************/
#define  CGMV120_MAX_USER_CODE      10
#define  CGMV120_MAX_SYSTEM_CODE	3
#define  CGMV120_AUTKEY_LEN	17
#define  CMD_V120_BUFF_LEN  30
#define  REC_V120_BUFF_LEN  250

#define  REC_V120_GLOUSE_MAXLEN  16
#define  REC_V120_ONLY_GLOUSE_MAXLEN  67

typedef struct cgmv120_user_code_id_s
{
    int customID;
    unsigned char encryptKey[CGMV120_AUTKEY_LEN];
}cgmv120_user_code_id_t;

typedef int Iret;


typedef struct
{
	uint16_t u16reply_ack_type;
	uint8_t u8reply_ack_resule;
    uint8_t u8error_code;
}cgmv120_cmd_ack_t;


typedef struct
{
    uint16_t index;
    uint16_t temp;
    uint16_t current;
    uint16_t dump;
    uint16_t reindex;

    uint16_t glouse;
    uint8_t trend;
    uint8_t gwarn;
    bool twarn;
    bool cwarn;
    uint32_t itime;
}cgmv120_glouse_info_t;

typedef struct
{
    uint16_t index;
    uint16_t reindex;
    uint16_t glouse;
    uint8_t trend;
    uint8_t gwarn;
    bool twarn;
    bool cwarn;
    uint32_t itime;
}cgmv120_only_glouse_info_t;


typedef struct
{
    uint16_t index;
    uint16_t reindex;
    uint16_t lactate;
    uint8_t twarn;
    uint8_t cwarn;
    uint32_t itime;
}cgmv120_only_lactate_info_t;

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

typedef struct
{
    uint16_t u16startover_time;
    uint32_t iactivation_time;
    uint32_t icurrent_time;
    uint32_t ilast_time;
    uint16_t u16last_index;
}cgmv120_device_time_t;

typedef struct
{
    uint8_t u8storage_status;
    uint16_t u16storage_number;
    uint8_t u8config_times;
    uint8_t u8key_times;
}cgmv120_device_storage_t;

typedef struct
{
    uint32_t icurrent0;
    uint32_t icurrent1;
    uint32_t itemp0;
    uint32_t itemp1;
}cgmv120_device_calibration_t;

typedef struct
{
    uint8_t u8reset_times;
    uint8_t u8reset_synchron;
    uint16_t u16reset_index;
    uint32_t ireset_time_stamp;
}cgmv120_device_reset_t;


typedef struct {
    uint16_t u16sens;
}cgmv120_u16sens_t;

typedef struct {
    uint16_t  upper;
    uint16_t  lower;
}cgmv120_glousethreshold_t;


typedef struct {
    uint8_t  u8activation;
}cgmv120_u8activation;


typedef struct
{
    uint8_t u8secret_key_num;
    uint8_t p8secret_key1[16];
    uint8_t p8secret_key2[16];

}cgmv120_secret_key_t;


typedef struct
{
    uint8_t state;
}cgmv120_oscillator_t;

/********************************V110底软协议*************************************/
#define  CMD_V110_BUFF_LEN  20
#define  REC_V110_BUFF_LEN  250
#define  REC_V110_GLOUSE_MAXLEN  10
typedef struct {
    uint16_t index;
    uint16_t temp;
    uint16_t current;
    uint16_t dump;
    uint16_t status;
    uint16_t leftsend;
    uint16_t nexttime;
}cgmv110_glouse_info_t;


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

typedef struct {
    uint16_t u16reply_ack_type;
    uint8_t  u8reply_ack_resule;
}cgmv110_cmd_ack_t;


/*********************************接口描述****************************************/

/**********************************V120*******************************************/
Iret v120_isec_update(int customID, bool bEncyrpt, uint32_t isec, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen);
Iret v120_activation(int customID, bool bEncyrpt, uint32_t isec, uint32_t u16Sens, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen);
Iret v120_raw_data(int customID, bool bEncyrpt, uint16_t startindex, uint16_t indexnum, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen);
Iret v120_reset(int customID, bool bEncyrpt, uint8_t u8Type, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen);
Iret v120_device_information(int customID, bool bEncyrpt, uint8_t u8Type, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen);
Iret v120_apply_authentication(int customID, bool bEncyrpt, uint8_t u8Type, uint8_t* mac, uint8_t* p8RetBuffer, uint16_t   U16RetBuffLen);
Iret v120_switch_authentication(int customID, bool bEncyrpt,  uint8_t u8type, uint8_t* p8RetBuffer, uint16_t   U16RetBuffLen);
Iret v120_set_secretkey(int customID, bool bEncyrpt, uint8_t u8type, uint8_t* keyset, uint8_t* p8RetBuffer, uint16_t   U16RetBuffLen);
Iret v120_glouse(int customID, bool bEncyrpt, uint16_t startindex, uint16_t indexnum, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen);
Iret v120_set_threshold(int customID, bool bEncyrpt, uint16_t highthreshold, uint16_t lowthreshold, uint8_t* p8RetBuffer, uint16_t   U16RetBuffLen);

Iret v120_spilt_data(int customID, uint8_t* p8DataBuffer, uint8_t u8DataBufferLen, uint16_t* P16cmd, uint8_t* p_value_info_t, bool bEncyrpt);
Iret v120_spilt_data_lactate(int customID, uint8_t* p8DataBuffer, uint8_t u8DataBufferLen, uint16_t* P16cmd, uint8_t* p_value_info_t, bool bEncyrpt);

Iret global_register_id(cgmv120_user_code_id_t* p8IdRegisterPack, unsigned short u16max_init_num);
/**********************************V110*******************************************/
Iret v110_raw_data(int customID, bool bEncyrpt, uint8_t* a8Mac, uint16_t u16index, uint16_t u16Rtc, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen);
Iret v110_activation(int customID, bool bEncyrpt, uint8_t* a8Mac, uint16_t u16Rtc, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen);
Iret v110_reset(int customID, bool bEncyrpt, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen);

Iret v110_spilt_data(int customID, uint8_t* p8DataBuffer, uint16_t* P16cmd, uint8_t* p_value_info_t, bool bEncyrpt);


/***********************************混合接口**************************************/
//Iret spilt_data(int customID, uint8_t* p8DataBuffer, uint8_t u8DataBufferLen, uint16_t* P16cmd, uint8_t* p_value_info_t, bool bEncyrpt, uint8_t* key);
void string_to_struct_test(char* str);
#ifdef __cplusplus
}
#endif

#endif
