#include "cgm_data_handle.h"
#include "../json/my_struct_2_json.h"
#include "../rc4/WjCryptLib_Rc4.h"
/*********************************************************V120底软协议****************************************************************************************/
/*********************************************************V120底软协议****************************************************************************************/
/*********************************************************V120底软协议****************************************************************************************/
#define CGMV120_ROOTKEY	"FURRY*ROROFUXFOX"
#define ROOT_CODE_ID  {1,CGMV120_ROOTKEY}

#define CGMV120_SETKEY "114514ROSKWD&TFS"
#define SETKEY_CODE_ID  {2,CGMV120_SETKEY}

#define CGMV120_MAIRUIKEY "LA52OGU1MRSA8OIA"
#define MAIRUIKEY_CODE_ID  {20011,CGMV120_MAIRUIKEY}

static const uint8_t encrypt_key[] = { 0x1,0x38,0xB,0x9A,0x0,0x5B,0x2,0x5D,0xcd,0x9e,0xc3,0x99,0x09,0x37,0xaa,0xe8 };

static const cgmv120_user_code_id_t  User_code_list[CGMV120_MAX_SYSTEM_CODE] =
{
    ROOT_CODE_ID,
    SETKEY_CODE_ID,
    MAIRUIKEY_CODE_ID
};

cgmv120_user_code_id_t  User_code_list_register[CGMV120_MAX_USER_CODE] = {

    {0,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00}},
    {0,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00}},
    {0,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00}},
    {0,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00}},
    {0,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00}},
    {0,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00}},
    {0,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00}},
    {0,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00}},
    {0,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00}},
    {0,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00}},
};




unsigned char  md_app_get_checksum(unsigned char* pData, unsigned char len);
void* id_ture_or_false(int customID);
int get_json_length(char* str);
uint8_t get_errocode(uint8_t errocode, uint16_t package_type);
//APP =======>> CGM 相关API
Iret v120_isec_update(int customID, bool bEncyrpt,uint32_t isec, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V120_BUFF_LEN];

    memset(cmd_buff,0, CMD_V120_BUFF_LEN);
    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 0x06 + 1))
    {
        cmd_buff[0] = 0x06;
        cmd_buff[1] = 0x03;
        cmd_buff[2] = (uint8_t)(isec & 0xff);
        cmd_buff[3] = (uint8_t)((isec >> 8) & 0xff);
        cmd_buff[4] = (uint8_t)((isec >> 16) & 0xff);
        cmd_buff[5] = (uint8_t)((isec >> 24) & 0xff);

        cmd_buff[0x06] = md_app_get_checksum(cmd_buff, 0x06);

        //加解密（保留）
        if(bEncyrpt==1)
        {
            Rc4XorWithKey(encrypt_key, 16, 0, cmd_buff, p8RetBuffer, 0x06 + 1);
        }
        else
        {
            memcpy(p8RetBuffer, cmd_buff, 0x06 + 1);
        }


        ret = 0x06 + 1;
    }
    else
    {
        ret = -2;
    }
    return ret;
}

Iret v120_activation(int customID, bool bEncyrpt,uint32_t isec, uint32_t u16Sens, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V120_BUFF_LEN];

    memset(cmd_buff, 0, CMD_V120_BUFF_LEN);
    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    if ((p8RetBuffer != NULL)&& (U16RetBuffLen >= 0x08 + 1))
    {
        cmd_buff[0] = 0x0a;
        cmd_buff[1] = 0x07;

        cmd_buff[2] = (uint8_t)(isec & 0xff);
        cmd_buff[3] = (uint8_t)((isec >> 8) & 0xff);
        cmd_buff[4] = (uint8_t)((isec >> 16) & 0xff);
        cmd_buff[5] = (uint8_t)((isec >> 24) & 0xff);

        cmd_buff[6] = (uint8_t)(u16Sens & 0xff);
        cmd_buff[7] = (uint8_t)((u16Sens >> 8) & 0xff);
        cmd_buff[8] = (uint8_t)((u16Sens >> 16) & 0xff);
        cmd_buff[9] = (uint8_t)((u16Sens >> 24) & 0xff);

        cmd_buff[10] = md_app_get_checksum(cmd_buff, 0x0a);

        //加解密（保留）
        if (bEncyrpt == 1)
        {
           Rc4XorWithKey(encrypt_key, 16, 0, cmd_buff, p8RetBuffer, 0x0a + 1);
        }
        else
        {
            memcpy(p8RetBuffer, cmd_buff, 0x0a + 1);
        }

        ret = 0x0a + 1;
    }
    else
    {
        ret = -2;
    }
    return ret;
}

Iret v120_raw_data(int customID, bool bEncyrpt, uint16_t startindex, uint16_t indexnum, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V120_BUFF_LEN];

    memset(cmd_buff, 0, CMD_V120_BUFF_LEN);
    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 0x06 + 1))
    {
        cmd_buff[0] = 0x06;
        cmd_buff[1] = 0x08;

        cmd_buff[2] = (uint8_t)(startindex & 0xff);
        cmd_buff[3] = (uint8_t)((startindex >> 8) & 0xff);
        cmd_buff[4] = (uint8_t)(indexnum & 0xff);
        cmd_buff[5] = (uint8_t)((indexnum >> 8) & 0xff);

        cmd_buff[0x06] = md_app_get_checksum(cmd_buff, 0x06);

        //加解密（保留）
        if (bEncyrpt == 1)
        {
           Rc4XorWithKey(encrypt_key, 16, 0, cmd_buff, p8RetBuffer, 0x06 + 1);
        }
        else
        {
            memcpy(p8RetBuffer, cmd_buff,0x06+1);
        }

        ret = 0x06 + 1;
    }
    else
    {
        ret = -2;
    }
    return ret;
}

Iret v120_reset(int customID, bool bEncyrpt, uint8_t u8Type, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V120_BUFF_LEN];

    memset(cmd_buff, 0, CMD_V120_BUFF_LEN);
    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 0x06 + 1))
    {
        cmd_buff[0] = 0x03;
        cmd_buff[1] = 0x10;
        cmd_buff[2] = (uint8_t)(u8Type);


        cmd_buff[0x03] = md_app_get_checksum(cmd_buff, 0x03);

        //加解密（保留）
        if (bEncyrpt == 1)
        {
            Rc4XorWithKey(encrypt_key, 16, 0, cmd_buff, p8RetBuffer, 0x03 + 1);
        }
        else
        {
            memcpy(p8RetBuffer, cmd_buff, 0x03 + 1);
        }

        ret = 0x03 + 1;
    }
    else
    {
        ret = -2;
    }
    return ret;
}

Iret v120_device_information(int customID, bool bEncyrpt, uint8_t u8Type, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V120_BUFF_LEN];

    memset(cmd_buff, 0, CMD_V120_BUFF_LEN);

    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 0x03 + 1))
    {
        cmd_buff[0] = 0x03;
        cmd_buff[1] = 0xf0;

        cmd_buff[2] = u8Type;

        cmd_buff[0x03] = md_app_get_checksum(cmd_buff, 0x03);

        //加解密（保留）
        if (bEncyrpt == 1)
        {
            Rc4XorWithKey(encrypt_key, 16, 0, cmd_buff, p8RetBuffer, 0x03 + 1);
        }
        else
        {
            memcpy(p8RetBuffer, cmd_buff, 0x03 + 1);
        }

        ret = 0x03 + 1;
    }
    else
    {
        ret = -2;
    }
    return ret;
}

Iret v120_apply_authentication(int customID, bool bEncyrpt, uint8_t u8Type, uint8_t* mac, uint8_t* p8RetBuffer, uint16_t   U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V120_BUFF_LEN];

    memset(cmd_buff, 0, CMD_V120_BUFF_LEN);

    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 25 + 1))
    {
        cmd_buff[0] = 0x19;
        cmd_buff[1] = 0x01;

        cmd_buff[2] = u8Type;


        memcpy(&cmd_buff[3], mac, 6);
        memcpy(&cmd_buff[9], id_ture_or_false(customID), 16);

        cmd_buff[25] = md_app_get_checksum(cmd_buff, 25);

        //加解密（保留）
        if (bEncyrpt == 1)
        {
            Rc4XorWithKey(encrypt_key, 16, 0, cmd_buff, p8RetBuffer, 25 + 1);
        }
        else
        {
            memcpy(p8RetBuffer, cmd_buff, 25 + 1);
        }

        ret = 25 + 1;
    }
    else
    {
        ret = -2;
    }
    return ret;
}

Iret v120_switch_authentication(int customID, bool bEncyrpt, uint8_t u8type, uint8_t* p8RetBuffer, uint16_t   U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V120_BUFF_LEN];

    memset(cmd_buff, 0, CMD_V120_BUFF_LEN);

    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 3 + 1))
    {
        cmd_buff[0] = 0x03;
        cmd_buff[1] = 0x02;

        cmd_buff[2] = u8type;


        cmd_buff[3] = md_app_get_checksum(cmd_buff, 3);

        //加解密（保留）
        if (bEncyrpt == 1)
        {
            Rc4XorWithKey(encrypt_key, 16, 0, cmd_buff, p8RetBuffer, 3 + 1);
        }
        else
        {
            memcpy(p8RetBuffer, cmd_buff, 3 + 1);
        }

        ret = 3 + 1;
    }
    else
    {
        ret = -2;
    }
    return ret;
}

Iret v120_set_secretkey(int customID, bool bEncyrpt, uint8_t u8type, uint8_t* keyset, uint8_t* p8RetBuffer, uint16_t   U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V120_BUFF_LEN];

    memset(cmd_buff, 0, CMD_V120_BUFF_LEN);

    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 19 + 1))
    {
        cmd_buff[0] = 0x13;
        cmd_buff[1] = 0x04;

        cmd_buff[2] = u8type;

        memcpy(&cmd_buff[3], keyset, 16);

        cmd_buff[19] = md_app_get_checksum(cmd_buff, 19);

        //加解密（保留）
        if (bEncyrpt == 1)
        {
            Rc4XorWithKey(encrypt_key, 16, 0, cmd_buff, p8RetBuffer, 19 + 1);
        }
        else
        {
            memcpy(p8RetBuffer, cmd_buff, 19 + 1);
        }

        ret = 19 + 1;
    }
    else
    {
        ret = -2;
    }
    return ret;
}
 
Iret v120_glouse(int customID, bool bEncyrpt, uint16_t startindex, uint16_t indexnum, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V120_BUFF_LEN];

    memset(cmd_buff, 0, CMD_V120_BUFF_LEN);
    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 0x06 + 1))
    {
        cmd_buff[0] = 0x06;
        cmd_buff[1] = 0x0a;

        cmd_buff[2] = (uint8_t)(startindex & 0xff);
        cmd_buff[3] = (uint8_t)((startindex >> 8) & 0xff);
        cmd_buff[4] = (uint8_t)(indexnum & 0xff);
        cmd_buff[5] = (uint8_t)((indexnum >> 8) & 0xff);

        cmd_buff[0x06] = md_app_get_checksum(cmd_buff, 0x06);

        //加解密（保留）
        if (bEncyrpt == 1)
        {
            Rc4XorWithKey(encrypt_key, 16, 0, cmd_buff, p8RetBuffer, 0x06 + 1);
        }
        else
        {
            memcpy(p8RetBuffer, cmd_buff, 0x06 + 1);
        }

        ret = 0x06 + 1;
    }
    else
    {
        ret = -2;
    }
    return ret;
}

Iret v120_set_threshold(int customID, bool bEncyrpt, uint16_t highthreshold, uint16_t lowthreshold, uint8_t* p8RetBuffer, uint16_t   U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V120_BUFF_LEN];

    memset(cmd_buff, 0, CMD_V120_BUFF_LEN);
    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 0x06 + 1))
    {
        cmd_buff[0] = 0x06;
        cmd_buff[1] = 0x06;

        cmd_buff[2] = (uint8_t)(lowthreshold & 0xff);
        cmd_buff[3] = (uint8_t)((lowthreshold >> 8) & 0xff);
        cmd_buff[4] = (uint8_t)(highthreshold & 0xff);
        cmd_buff[5] = (uint8_t)((highthreshold >> 8) & 0xff);

        cmd_buff[0x06] = md_app_get_checksum(cmd_buff, 0x06);

        //加解密（保留）
        if (bEncyrpt == 1)
        {
            Rc4XorWithKey(encrypt_key, 16, 0, cmd_buff, p8RetBuffer, 0x06 + 1);
        }
        else
        {
            memcpy(p8RetBuffer, cmd_buff, 0x06 + 1);
        }

        ret = 0x06 + 1;
    }
    else
    {
        ret = -2;
    }
    return ret;

}

//CGM =======>> APP 相关API
Iret v120_spilt_data(int customID, uint8_t* p8DataBuffer, uint8_t u8DataBufferLen, uint16_t* P16cmd, uint8_t* p_value_info_t, bool bEncyrpt)
{
    int ret = 0;
    uint16_t cmd_value = 0;
    uint8_t  p8DataBuffer_temp[REC_V120_BUFF_LEN];
    uint8_t  rec_buff[REC_V120_BUFF_LEN];
    uint8_t  object_arry[5] = {0x04,0x00,0x00,0x00,0xfc};
    uint8_t  Plaintext_flag = 0;  

    memset(rec_buff, 0, REC_V120_BUFF_LEN);
    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    //判断是否为明文的无效指令
    if (u8DataBufferLen == 5)
    {
        for (int i = 0; i < 5; i++) 
        {
            if (p8DataBuffer[i] == object_arry[i]) 
            {
                Plaintext_flag++;
            }
            else
            {
               break;
            }
        }
    }
    if (Plaintext_flag == 5)
    {
        bEncyrpt = 0;
    }

    //加解密（保留）
    if (bEncyrpt == 1)
    {
        Rc4XorWithKey(encrypt_key, 16, 0, p8DataBuffer, p8DataBuffer_temp, u8DataBufferLen);
    }
    else
    {
        memcpy(p8DataBuffer_temp, p8DataBuffer, u8DataBufferLen);
    }

    if ((p8DataBuffer != NULL) && (p_value_info_t != NULL) && (P16cmd != NULL))
    {
        cmd_value |= *(p8DataBuffer_temp + 1);

        switch (cmd_value)
        {
            case 0x00:
            case 0x01:
            case 0x02:
            case 0x03:
            case 0x04:
            case 0x06:
            case 0x07:
            case 0x10:
            {
                cgmv120_cmd_ack_t  my_cgmv120_cmd_ack_t;
                memset(&my_cgmv120_cmd_ack_t, 0, sizeof(cgmv120_cmd_ack_t));

                memcpy(rec_buff, p8DataBuffer_temp, 4 + 1);

                if ((*rec_buff == 4) && (rec_buff[4] == md_app_get_checksum(rec_buff, 4)))
                {
                    my_cgmv120_cmd_ack_t.u16reply_ack_type = ((cmd_value | 0xc000) + 1);
                    my_cgmv120_cmd_ack_t.u8reply_ack_resule = rec_buff[2];
                    if(my_cgmv120_cmd_ack_t.u8reply_ack_resule==0)
                    {
                        my_cgmv120_cmd_ack_t.u8error_code = get_errocode(rec_buff[3], my_cgmv120_cmd_ack_t.u16reply_ack_type);

                        if (Plaintext_flag == 5)  my_cgmv120_cmd_ack_t.u8error_code = 0x0a;
                    }

                    *P16cmd = 0xc00d;
                    //struct==============>json
                    cJSON* json_ack = struct_to_json_cgmv120_cmd_ack_t(&my_cgmv120_cmd_ack_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    //json_string = cJSON_Print(json_ack);
                    ret = 1;
                }
                else
                {
                    ret = -3;
                }
            }
                break;
            case 0x08:
            {
                if (*p8DataBuffer_temp == 4)
                {
                    cgmv120_cmd_ack_t  my_cgmv120_cmd_ack_t;
                    memset(&my_cgmv120_cmd_ack_t, 0, sizeof(cgmv120_cmd_ack_t));

                    memcpy(rec_buff, p8DataBuffer_temp, 4 + 1);

                    if ((*rec_buff == 4) && (rec_buff[4] == md_app_get_checksum(rec_buff, 4)))
                    {
                        my_cgmv120_cmd_ack_t.u16reply_ack_type = ((cmd_value | 0xc000) + 1);
                        my_cgmv120_cmd_ack_t.u8reply_ack_resule = rec_buff[2];
                        if (my_cgmv120_cmd_ack_t.u8reply_ack_resule == 0)
                        {
                            my_cgmv120_cmd_ack_t.u8error_code = get_errocode(rec_buff[3], my_cgmv120_cmd_ack_t.u16reply_ack_type);
                        }

                        *P16cmd = 0xc00d;
                        //struct==============>json
                        cJSON* json_ack = struct_to_json_cgmv120_cmd_ack_t(&my_cgmv120_cmd_ack_t);

                        char* json_string = cJSON_PrintUnformatted(json_ack);
                        //puts(json_string);

                        memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                        
                        s2j_delete_json_obj(json_ack);
                        free(json_string);
                        ret = 1;
                    }
                    else
                    {
                        ret = -3;
                    }
                }
                else
                {
                    int package_num = 0;
                    uint16_t package_index = 0;
                    int package_time_stamp = 0;
                    uint16_t repackage_index = 0;

                    cgmv120_glouse_info_t my_cgmv120_glouse_info_t[REC_V120_GLOUSE_MAXLEN] = { 0 };
                    
                    memcpy(rec_buff, p8DataBuffer_temp, *p8DataBuffer_temp + 1);

                    if (rec_buff[*p8DataBuffer_temp] == md_app_get_checksum(rec_buff, *p8DataBuffer_temp))
                    {
                        package_num = rec_buff[2];
                       /* memcpy(p8RetReplyPack->a8packet_data, &cmd_buff[2], *p8DataBuffer - 2);*/
                        package_index = ((rec_buff[4]) << 8) | (rec_buff[3]);
                        package_time_stamp = (rec_buff[8] << 24) | (rec_buff[7] << 16) | (rec_buff[6] << 8) | (rec_buff[5]);
                        repackage_index = (rec_buff[*p8DataBuffer_temp - 1] << 8) | (rec_buff[*p8DataBuffer_temp - 2])+ package_num;

                        for (int i = 0; i < package_num; i++)
                        {
                                my_cgmv120_glouse_info_t[i].index = package_index;
                                my_cgmv120_glouse_info_t[i].itime = package_time_stamp;

                                my_cgmv120_glouse_info_t[i].reindex = repackage_index-i-1;
                                my_cgmv120_glouse_info_t[i].temp = (rec_buff[10 + i * 8] << 8) | (rec_buff[9 + i * 8]);
                                my_cgmv120_glouse_info_t[i].dump = (rec_buff[12 + i * 8] << 8) | (rec_buff[11 + i * 8]);
                                my_cgmv120_glouse_info_t[i].current = (rec_buff[14 + i * 8] << 8) | (rec_buff[13 + i * 8]);

                                my_cgmv120_glouse_info_t[i].glouse = (rec_buff[16 + i * 8] << 2) | (rec_buff[15 + i * 8] >> 6);
                                my_cgmv120_glouse_info_t[i].trend =  (rec_buff[15 + i * 8] & 0x38) >> 3;
                                my_cgmv120_glouse_info_t[i].gwarn =  (rec_buff[15 + i * 8] & 0x06) >> 1;
                                my_cgmv120_glouse_info_t[i].cwarn =  (rec_buff[15 + i * 8] & 0x01);
                                my_cgmv120_glouse_info_t[i].twarn =  (rec_buff[15 + i * 8] & 0x01);


                                package_index++;
                                package_time_stamp += 60;
                        }

                        *P16cmd = 0xc007;
                        //struct==============>json
                        uint8_t* ptr = p_value_info_t;
                        cJSON* json_ack=NULL;
                        uint16_t length_json = 0;
                        for (int i = 0; i < package_num; i++)
                        {
                            json_ack = struct_to_json_cgmv120_glouse_info_t(&my_cgmv120_glouse_info_t[i]);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            int length = get_json_length(json_string);
                            length_json += length;
                           // printf("\nsize:%d", length + 1);
                            //printf("\n%s\n", json_string);
                            if (i == package_num-1)
                            {
                                memcpy(ptr, json_string, length + 1);
                            }
                            else
                            {
                                json_string[length] = ',';
                                memcpy(ptr, json_string, length+1);
                                ptr = ptr + length+1;
                            }

                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                        }
                        if (length_json > 2400)
                        {
                            ret = -3;
                        }
                        else
                        { 
                            ret = package_num;
                        }
                    }
                    else
                    {
                        ret = -3;
                    }
                }
            }
                break;
            case 0x0a:
            {
                if (*p8DataBuffer_temp == 4)
                {
                    cgmv120_cmd_ack_t  my_cgmv120_cmd_ack_t;
                    memset(&my_cgmv120_cmd_ack_t, 0, sizeof(cgmv120_cmd_ack_t));

                    memcpy(rec_buff, p8DataBuffer_temp, 4 + 1);

                    if ((*rec_buff == 4) && (rec_buff[4] == md_app_get_checksum(rec_buff, 4)))
                    {
                        my_cgmv120_cmd_ack_t.u16reply_ack_type = ((cmd_value | 0xc000) + 1);
                        my_cgmv120_cmd_ack_t.u8reply_ack_resule = rec_buff[2];
                        if (my_cgmv120_cmd_ack_t.u8reply_ack_resule == 0)
                        {
                            my_cgmv120_cmd_ack_t.u8error_code = get_errocode(rec_buff[3], my_cgmv120_cmd_ack_t.u16reply_ack_type);
                        }

                        *P16cmd = 0xc00d;
                        //struct==============>json
                        cJSON* json_ack = struct_to_json_cgmv120_cmd_ack_t(&my_cgmv120_cmd_ack_t);

                        char* json_string = cJSON_PrintUnformatted(json_ack);
                        //puts(json_string);

                        memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);

                        s2j_delete_json_obj(json_ack);
                        free(json_string);
                        ret = 1;
                    }
                    else
                    {
                        ret = -3;
                    }
                }
                else
                {
                    int package_num = 0;
                    uint16_t package_index = 0;
                    int package_time_stamp = 0;
                    uint16_t repackage_index = 0;

                    cgmv120_only_glouse_info_t my_cgmv120_only_glouse_info_t[REC_V120_ONLY_GLOUSE_MAXLEN] = { 0 };

                    memcpy(rec_buff, p8DataBuffer_temp, *p8DataBuffer_temp + 1);

                    if (rec_buff[*p8DataBuffer_temp] == md_app_get_checksum(rec_buff, *p8DataBuffer_temp))
                    {
                        package_num = rec_buff[2];
                        /* memcpy(p8RetReplyPack->a8packet_data, &cmd_buff[2], *p8DataBuffer - 2);*/
                        package_index = ((rec_buff[4]) << 8) | (rec_buff[3]);
                        package_time_stamp = (rec_buff[8] << 24) | (rec_buff[7] << 16) | (rec_buff[6] << 8) | (rec_buff[5]);
                        repackage_index = (rec_buff[*p8DataBuffer_temp - 1] << 8) | (rec_buff[*p8DataBuffer_temp - 2]) + package_num;

                        for (int i = 0; i < package_num; i++)
                        {
                            my_cgmv120_only_glouse_info_t[i].index = package_index;
                            my_cgmv120_only_glouse_info_t[i].itime = package_time_stamp;

                            my_cgmv120_only_glouse_info_t[i].reindex = repackage_index - i - 1;

                            my_cgmv120_only_glouse_info_t[i].glouse = (rec_buff[9 + i * 2] >> 6) | (rec_buff[10 + i * 2] << 2);
                            my_cgmv120_only_glouse_info_t[i].trend = (rec_buff[9 + i * 2] & 0x38) >> 3;
                            my_cgmv120_only_glouse_info_t[i].gwarn = (rec_buff[9 + i * 2] & 0x06) >> 1;
                            my_cgmv120_only_glouse_info_t[i].cwarn = (rec_buff[9 + i * 2] & 0x01);
                            my_cgmv120_only_glouse_info_t[i].twarn = (rec_buff[9 + i * 2] & 0x01);


                            package_index++;
                            package_time_stamp += 60;
                        }

                        *P16cmd = 0xc008;
                        //struct==============>json
                        uint8_t* ptr = p_value_info_t;
                        cJSON* json_ack = NULL;
                        uint16_t length_json = 0;
                        for (int i = 0; i < package_num; i++)
                        {
                            json_ack = struct_to_json_cgmv120_only_glouse_info_t(&my_cgmv120_only_glouse_info_t[i]);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            int length = get_json_length(json_string);
                            length_json += length;
                            // printf("\nsize:%d", length + 1);
                             //printf("\n%s\n", json_string);
                            if (i == package_num - 1)
                            {
                                memcpy(ptr, json_string, length + 1);
                            }
                            else
                            {
                                json_string[length] = ',';
                                memcpy(ptr, json_string, length + 1);
                                ptr = ptr + length + 1;
                            }

                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                        }
                        if (length_json > 7000)
                        {
                            ret = -3;
                        }
                        else
                        {
                            ret = package_num;
                        }
                    }
                    else
                    {
                        ret = -3;
                    }
                }
            }
            break;
            case 0xf0:
            {
                uint8_t u8reply_resule_data = 0;
                memcpy(rec_buff, p8DataBuffer_temp, *p8DataBuffer_temp + 1);

                if (rec_buff[*p8DataBuffer_temp] == md_app_get_checksum(rec_buff, *p8DataBuffer_temp))
                {
                    u8reply_resule_data = rec_buff[2];

                    switch (u8reply_resule_data)
                    {
                        case 1:
                        {
                            cgmv120_u16sens_t my_cgmv120_u16sens_t;
                            memset(&my_cgmv120_u16sens_t, 0, sizeof(my_cgmv120_u16sens_t));
                            my_cgmv120_u16sens_t.u16sens = (rec_buff[4]<<8)|rec_buff[3];
                            *P16cmd = 0xc01b;

                            //struct==============>json
                            cJSON* json_ack = struct_to_json_cgmv120_u16sens_t(&my_cgmv120_u16sens_t);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            //puts(json_string);

                            memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                            ret = 1;
                        }
                            break;
                        case 2:
                        {
                            cgmv120_u8activation my_cgmv120_u8activation;
                            memset(&my_cgmv120_u8activation, 0, sizeof(my_cgmv120_u8activation));
                            my_cgmv120_u8activation.u8activation = rec_buff[3];
                            *P16cmd = 0xc02b;
                            
                            //struct==============>json
                            cJSON* json_ack = struct_to_json_cgmv120_u8activation(&my_cgmv120_u8activation);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            //puts(json_string);

                            memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                            ret = 1;
                        }
                            break;
                        case 3:
                        {
                            cgmv120_device_time_t my_cgmv120_device_time_t;
                            memset(&my_cgmv120_device_time_t, 0, sizeof(my_cgmv120_device_time_t));

                            my_cgmv120_device_time_t.u16startover_time = (rec_buff[4] << 8) | (rec_buff[3]);
                            my_cgmv120_device_time_t.iactivation_time = (rec_buff[8] << 24) | (rec_buff[7] << 16) | (rec_buff[6] << 8) | (rec_buff[5]);
                            my_cgmv120_device_time_t.icurrent_time = (rec_buff[12] << 24) | (rec_buff[11] << 16) | (rec_buff[10] << 8) | (rec_buff[9]);
                            my_cgmv120_device_time_t.ilast_time = (rec_buff[16] << 24) | (rec_buff[15] << 16) | (rec_buff[14] << 8) | (rec_buff[13]);
                            my_cgmv120_device_time_t.u16last_index = (rec_buff[18] << 8) | (rec_buff[17]);
                            *P16cmd = 0xc03b;
                            //struct==============>json
                            cJSON* json_ack = struct_to_json_cgmv120_device_time_t(&my_cgmv120_device_time_t);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            //puts(json_string);

                            memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                            ret = 1;
                        }
                            break;
                        case 4:
                        {
                            cgmv120_device_storage_t my_cgmv120_device_storage_t;
                            memset(&my_cgmv120_device_storage_t, 0, sizeof(my_cgmv120_device_storage_t));

                            my_cgmv120_device_storage_t.u8storage_status = rec_buff[3];
                            my_cgmv120_device_storage_t.u16storage_number = (rec_buff[5] << 8) | (rec_buff[4]);
                            my_cgmv120_device_storage_t.u8config_times= rec_buff[6];
                            my_cgmv120_device_storage_t .u8key_times= rec_buff[7];
                            *P16cmd = 0xc04b;
                            //struct==============>json 
                            cJSON* json_ack = struct_to_json_cgmv120_device_storage_t(&my_cgmv120_device_storage_t);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            //puts(json_string);

                            memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                            ret = 1;
                        }
                            break;
                        case 5:
                        {
                            cgmv120_device_calibration_t my_cgmv120_device_calibration_t;
                            memset(&my_cgmv120_device_calibration_t,0,sizeof(my_cgmv120_device_calibration_t));

                            my_cgmv120_device_calibration_t.icurrent0 = (rec_buff[6] << 24) | (rec_buff[5] << 16) | (rec_buff[4] << 8) | (rec_buff[3]);
                            my_cgmv120_device_calibration_t.icurrent1 = (rec_buff[10] << 24) | (rec_buff[9] << 16) | (rec_buff[8] << 8) | (rec_buff[7]);
                            my_cgmv120_device_calibration_t.itemp0 = (rec_buff[14] << 24) | (rec_buff[13] << 16) | (rec_buff[12] << 8) | (rec_buff[11]);
                            my_cgmv120_device_calibration_t.itemp1 = (rec_buff[18] << 24) | (rec_buff[17] << 16) | (rec_buff[16] << 8) | (rec_buff[15]);
                            *P16cmd = 0xc05b;
                            //struct==============>json  
                            cJSON* json_ack = struct_to_json_cgmv120_device_calibration_t(&my_cgmv120_device_calibration_t);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            //puts(json_string);

                            memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                            ret = 1;
                        }
                            break;
                        case 6:
                        {
                            cgmv120_secret_key_t my_cgmv120_secret_key_t;
                            memset(&my_cgmv120_secret_key_t, 0, sizeof(my_cgmv120_secret_key_t));

                            my_cgmv120_secret_key_t.u8secret_key_num = (rec_buff[3]);
                            memcpy(my_cgmv120_secret_key_t.p8secret_key1, &rec_buff[4], 16);
                            memcpy(my_cgmv120_secret_key_t.p8secret_key2, &rec_buff[20], 16);
                     
                            *P16cmd = 0xc06b;
                            //struct==============>json  
                            cJSON* json_ack = struct_to_json_cgmv120_secret_key_t(&my_cgmv120_secret_key_t);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            //puts(json_string);

                            memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                            ret = 1;
                        }
                           break;
                        case 7:
                        {
                            cgmv120_device_reset_t my_cgmv120_device_reset_t;
                            memset(&my_cgmv120_device_reset_t, 0, sizeof(my_cgmv120_device_reset_t));

                            my_cgmv120_device_reset_t.ireset_time_stamp = (rec_buff[10] << 24) | (rec_buff[9] << 16) | (rec_buff[8] << 8) | (rec_buff[7]);
                            my_cgmv120_device_reset_t.u16reset_index = (rec_buff[6] << 8) | (rec_buff[5]);
                            my_cgmv120_device_reset_t.u8reset_synchron = rec_buff[4];
                            my_cgmv120_device_reset_t.u8reset_times = rec_buff[3];
                            *P16cmd = 0xc07b;
                            //struct==============>json  
                            cJSON* json_ack = struct_to_json_cgmv120_device_reset_t(&my_cgmv120_device_reset_t);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            //puts(json_string);

                            memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                            ret = 1;

                        }
                            break;
                        case 8:
                        {
                            cgmv120_glousethreshold_t my_cgmv120_glousethreshold_t;
                            memset(&my_cgmv120_glousethreshold_t, 0, sizeof(my_cgmv120_glousethreshold_t));

                            my_cgmv120_glousethreshold_t.lower= (rec_buff[4] << 8) | rec_buff[3];
                            my_cgmv120_glousethreshold_t.upper= (rec_buff[6] << 8) | rec_buff[5];
 ;
                            *P16cmd = 0xc08b;
                            //struct==============>json  
                            cJSON* json_ack = struct_to_json_cgmv120_glousethreshold_t(&my_cgmv120_glousethreshold_t);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            //puts(json_string);

                            memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                            ret = 1;

                        }
                        break;
                        case 9:
                        {
                            cgmv120_oscillator_t my_cgmv120_oscillator_t;
                            memset(&my_cgmv120_oscillator_t, 0, sizeof(my_cgmv120_oscillator_t));

                            my_cgmv120_oscillator_t.state = rec_buff[3];
         
                            *P16cmd = 0xc09b;
                            //struct==============>json  
                            cJSON* json_ack = struct_to_json_cgmv120_oscillator_t(&my_cgmv120_oscillator_t);

                            char* json_string = cJSON_PrintUnformatted(json_ack);
                            //puts(json_string);

                            memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                            s2j_delete_json_obj(json_ack);
                            free(json_string);
                            ret = 1;

                        }
                        break;
                        default:
                            break;
                    }
                }
                else
                {
                    ret = -3;
                }
            
            } 
                break;
            default:
                ret = -3;
                break;
        }
    }
    else
    {
        ret = -2;
    }

    return ret; 
}

Iret v120_spilt_data_lactate(int customID, uint8_t* p8DataBuffer, uint8_t u8DataBufferLen, uint16_t* P16cmd, uint8_t* p_value_info_t, bool bEncyrpt)
{
    int ret = 0;
    uint16_t cmd_value = 0;
    uint8_t  p8DataBuffer_temp[REC_V120_BUFF_LEN];
    uint8_t  rec_buff[REC_V120_BUFF_LEN];
    uint8_t  object_arry[5] = { 0x04,0x00,0x00,0x00,0xfc };
    uint8_t  Plaintext_flag = 0;

    memset(rec_buff, 0, REC_V120_BUFF_LEN);
    //鉴权ID判断一下
    if ((id_ture_or_false(customID) == NULL))
    {
        ret = -1;
        return ret;
    }

    //判断是否为明文的无效指令
    if (u8DataBufferLen == 5)
    {
        for (int i = 0; i < 5; i++)
        {
            if (p8DataBuffer[i] == object_arry[i])
            {
                Plaintext_flag++;
            }
            else
            {
                break;
            }
        }
    }
    if (Plaintext_flag == 5)
    {
        bEncyrpt = 0;
    }

    //加解密（保留）
    if (bEncyrpt == 1)
    {
        Rc4XorWithKey(encrypt_key, 16, 0, p8DataBuffer, p8DataBuffer_temp, u8DataBufferLen);
    }
    else
    {
        memcpy(p8DataBuffer_temp, p8DataBuffer, u8DataBufferLen);
    }

    if ((p8DataBuffer != NULL) && (p_value_info_t != NULL) && (P16cmd != NULL))
    {
        cmd_value |= *(p8DataBuffer_temp + 1);

        switch (cmd_value)
        {
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x06:
        case 0x07:
        case 0x10:
        {
            cgmv120_cmd_ack_t  my_cgmv120_cmd_ack_t;
            memset(&my_cgmv120_cmd_ack_t, 0, sizeof(cgmv120_cmd_ack_t));

            memcpy(rec_buff, p8DataBuffer_temp, 4 + 1);

            if ((*rec_buff == 4) && (rec_buff[4] == md_app_get_checksum(rec_buff, 4)))
            {
                my_cgmv120_cmd_ack_t.u16reply_ack_type = ((cmd_value | 0xc000) + 1);
                my_cgmv120_cmd_ack_t.u8reply_ack_resule = rec_buff[2];
                if (my_cgmv120_cmd_ack_t.u8reply_ack_resule == 0)
                {
                    my_cgmv120_cmd_ack_t.u8error_code = get_errocode(rec_buff[3], my_cgmv120_cmd_ack_t.u16reply_ack_type);

                    if (Plaintext_flag == 5)  my_cgmv120_cmd_ack_t.u8error_code = 0x0a;
                }

                *P16cmd = 0xc00d;
                //struct==============>json
                cJSON* json_ack = struct_to_json_cgmv120_cmd_ack_t(&my_cgmv120_cmd_ack_t);

                char* json_string = cJSON_PrintUnformatted(json_ack);
                //puts(json_string);

                memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                s2j_delete_json_obj(json_ack);
                free(json_string);
                //json_string = cJSON_Print(json_ack);
                ret = 1;
            }
            else
            {
                ret = -3;
            }
        }
        break;
        case 0x08:
        {
            if (*p8DataBuffer_temp == 4)
            {
                cgmv120_cmd_ack_t  my_cgmv120_cmd_ack_t;
                memset(&my_cgmv120_cmd_ack_t, 0, sizeof(cgmv120_cmd_ack_t));

                memcpy(rec_buff, p8DataBuffer_temp, 4 + 1);

                if ((*rec_buff == 4) && (rec_buff[4] == md_app_get_checksum(rec_buff, 4)))
                {
                    my_cgmv120_cmd_ack_t.u16reply_ack_type = ((cmd_value | 0xc000) + 1);
                    my_cgmv120_cmd_ack_t.u8reply_ack_resule = rec_buff[2];
                    if (my_cgmv120_cmd_ack_t.u8reply_ack_resule == 0)
                    {
                        my_cgmv120_cmd_ack_t.u8error_code = get_errocode(rec_buff[3], my_cgmv120_cmd_ack_t.u16reply_ack_type);
                    }

                    *P16cmd = 0xc00d;
                    //struct==============>json
                    cJSON* json_ack = struct_to_json_cgmv120_cmd_ack_t(&my_cgmv120_cmd_ack_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);

                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;
                }
                else
                {
                    ret = -3;
                }
            }
            else
            {
                int package_num = 0;
                uint16_t package_index = 0;
                int package_time_stamp = 0;
                uint16_t repackage_index = 0;

                cgmv120_lactate_info_t my_cgmv120_lactate_info_t[REC_V120_GLOUSE_MAXLEN] = { 0 };

                memcpy(rec_buff, p8DataBuffer_temp, *p8DataBuffer_temp + 1);

                if (rec_buff[*p8DataBuffer_temp] == md_app_get_checksum(rec_buff, *p8DataBuffer_temp))
                {
                    package_num = rec_buff[2];
                    /* memcpy(p8RetReplyPack->a8packet_data, &cmd_buff[2], *p8DataBuffer - 2);*/
                    package_index = ((rec_buff[4]) << 8) | (rec_buff[3]);
                    package_time_stamp = (rec_buff[8] << 24) | (rec_buff[7] << 16) | (rec_buff[6] << 8) | (rec_buff[5]);
                    repackage_index = (rec_buff[*p8DataBuffer_temp - 1] << 8) | (rec_buff[*p8DataBuffer_temp - 2]) + package_num;

                    for (int i = 0; i < package_num; i++)
                    {
                        my_cgmv120_lactate_info_t[i].index = package_index;
                        my_cgmv120_lactate_info_t[i].itime = package_time_stamp;

                        my_cgmv120_lactate_info_t[i].reindex = repackage_index - i - 1;
                        my_cgmv120_lactate_info_t[i].temp = (rec_buff[10 + i * 8] << 8) | (rec_buff[9 + i * 8]);
                        my_cgmv120_lactate_info_t[i].dump = (rec_buff[12 + i * 8] << 8) | (rec_buff[11 + i * 8]);
                        my_cgmv120_lactate_info_t[i].current = (rec_buff[14 + i * 8] << 8) | (rec_buff[13 + i * 8]);

                        my_cgmv120_lactate_info_t[i].lactate = (rec_buff[16 + i * 8] << 2) | (rec_buff[15 + i * 8] >> 6);
                        my_cgmv120_lactate_info_t[i].twarn = (rec_buff[15 + i * 8] & 0x38) >> 3;
                        my_cgmv120_lactate_info_t[i].cwarn = (rec_buff[15 + i * 8] & 0x06) >> 1;

                        package_index++;
                        package_time_stamp += 60;
                    }

                    *P16cmd = 0xc007;
                    //struct==============>json
                    uint8_t* ptr = p_value_info_t;
                    cJSON* json_ack = NULL;
                    uint16_t length_json = 0;
                    for (int i = 0; i < package_num; i++)
                    {
                        json_ack = struct_to_json_cgmv120_lactate_info_t(&my_cgmv120_lactate_info_t[i]);

                        char* json_string = cJSON_PrintUnformatted(json_ack);
                        int length = get_json_length(json_string);
                        length_json += length;
                        // printf("\nsize:%d", length + 1);
                         //printf("\n%s\n", json_string);
                        if (i == package_num - 1)
                        {
                            memcpy(ptr, json_string, length + 1);
                        }
                        else
                        {
                            json_string[length] = ',';
                            memcpy(ptr, json_string, length + 1);
                            ptr = ptr + length + 1;
                        }

                        s2j_delete_json_obj(json_ack);
                        free(json_string);
                    }
                    if (length_json > 2400)
                    {
                        ret = -3;
                    }
                    else
                    {
                        ret = package_num;
                    }
                }
                else
                {
                    ret = -3;
                }
            }
        }
        break;
        case 0x0a:
        {
            if (*p8DataBuffer_temp == 4)
            {
                cgmv120_cmd_ack_t  my_cgmv120_cmd_ack_t;
                memset(&my_cgmv120_cmd_ack_t, 0, sizeof(cgmv120_cmd_ack_t));

                memcpy(rec_buff, p8DataBuffer_temp, 4 + 1);

                if ((*rec_buff == 4) && (rec_buff[4] == md_app_get_checksum(rec_buff, 4)))
                {
                    my_cgmv120_cmd_ack_t.u16reply_ack_type = ((cmd_value | 0xc000) + 1);
                    my_cgmv120_cmd_ack_t.u8reply_ack_resule = rec_buff[2];
                    if (my_cgmv120_cmd_ack_t.u8reply_ack_resule == 0)
                    {
                        my_cgmv120_cmd_ack_t.u8error_code = get_errocode(rec_buff[3], my_cgmv120_cmd_ack_t.u16reply_ack_type);
                    }

                    *P16cmd = 0xc00d;
                    //struct==============>json
                    cJSON* json_ack = struct_to_json_cgmv120_cmd_ack_t(&my_cgmv120_cmd_ack_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);

                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;
                }
                else
                {
                    ret = -3;
                }
            }
            else
            {
                int package_num = 0;
                uint16_t package_index = 0;
                int package_time_stamp = 0;
                uint16_t repackage_index = 0;

                cgmv120_only_lactate_info_t my_cgmv120_only_lactate_info_t[REC_V120_ONLY_GLOUSE_MAXLEN] = { 0 };

                memcpy(rec_buff, p8DataBuffer_temp, *p8DataBuffer_temp + 1);

                if (rec_buff[*p8DataBuffer_temp] == md_app_get_checksum(rec_buff, *p8DataBuffer_temp))
                {
                    package_num = rec_buff[2];
                    /* memcpy(p8RetReplyPack->a8packet_data, &cmd_buff[2], *p8DataBuffer - 2);*/
                    package_index = ((rec_buff[4]) << 8) | (rec_buff[3]);
                    package_time_stamp = (rec_buff[8] << 24) | (rec_buff[7] << 16) | (rec_buff[6] << 8) | (rec_buff[5]);
                    repackage_index = (rec_buff[*p8DataBuffer_temp - 1] << 8) | (rec_buff[*p8DataBuffer_temp - 2]) + package_num;

                    for (int i = 0; i < package_num; i++)
                    {
                        my_cgmv120_only_lactate_info_t[i].index = package_index;
                        my_cgmv120_only_lactate_info_t[i].itime = package_time_stamp;

                        my_cgmv120_only_lactate_info_t[i].reindex = repackage_index - i - 1;

                        my_cgmv120_only_lactate_info_t[i].lactate = (rec_buff[9 + i * 2] >> 6) | (rec_buff[10 + i * 2] << 2);
                        my_cgmv120_only_lactate_info_t[i].twarn = (rec_buff[9 + i * 2] & 0x38) >> 3;
                        my_cgmv120_only_lactate_info_t[i].cwarn = (rec_buff[9 + i * 2] & 0x06) >> 1;

                        package_index++;
                        package_time_stamp += 60;
                    }

                    *P16cmd = 0xc008;
                    //struct==============>json
                    uint8_t* ptr = p_value_info_t;
                    cJSON* json_ack = NULL;
                    uint16_t length_json = 0;
                    for (int i = 0; i < package_num; i++)
                    {
                        json_ack = struct_to_json_cgmv120_only_lactate_info_t(&my_cgmv120_only_lactate_info_t[i]);

                        char* json_string = cJSON_PrintUnformatted(json_ack);
                        int length = get_json_length(json_string);
                        length_json += length;
                        // printf("\nsize:%d", length + 1);
                         //printf("\n%s\n", json_string);
                        if (i == package_num - 1)
                        {
                            memcpy(ptr, json_string, length + 1);
                        }
                        else
                        {
                            json_string[length] = ',';
                            memcpy(ptr, json_string, length + 1);
                            ptr = ptr + length + 1;
                        }

                        s2j_delete_json_obj(json_ack);
                        free(json_string);
                    }
                    if (length_json > 7000)
                    {
                        ret = -3;
                    }
                    else
                    {
                        ret = package_num;
                    }
                }
                else
                {
                    ret = -3;
                }
            }
        }
        break;
        case 0xf0:
        {
            uint8_t u8reply_resule_data = 0;
            memcpy(rec_buff, p8DataBuffer_temp, *p8DataBuffer_temp + 1);

            if (rec_buff[*p8DataBuffer_temp] == md_app_get_checksum(rec_buff, *p8DataBuffer_temp))
            {
                u8reply_resule_data = rec_buff[2];

                switch (u8reply_resule_data)
                {
                case 1:
                {
                    cgmv120_u16sens_t my_cgmv120_u16sens_t;
                    memset(&my_cgmv120_u16sens_t, 0, sizeof(my_cgmv120_u16sens_t));
                    my_cgmv120_u16sens_t.u16sens = (rec_buff[4] << 8) | rec_buff[3];
                    *P16cmd = 0xc01b;

                    //struct==============>json
                    cJSON* json_ack = struct_to_json_cgmv120_u16sens_t(&my_cgmv120_u16sens_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;
                }
                break;
                case 2:
                {
                    cgmv120_u8activation my_cgmv120_u8activation;
                    memset(&my_cgmv120_u8activation, 0, sizeof(my_cgmv120_u8activation));
                    my_cgmv120_u8activation.u8activation = rec_buff[3];
                    *P16cmd = 0xc02b;

                    //struct==============>json
                    cJSON* json_ack = struct_to_json_cgmv120_u8activation(&my_cgmv120_u8activation);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;
                }
                break;
                case 3:
                {
                    cgmv120_device_time_t my_cgmv120_device_time_t;
                    memset(&my_cgmv120_device_time_t, 0, sizeof(my_cgmv120_device_time_t));

                    my_cgmv120_device_time_t.u16startover_time = (rec_buff[4] << 8) | (rec_buff[3]);
                    my_cgmv120_device_time_t.iactivation_time = (rec_buff[8] << 24) | (rec_buff[7] << 16) | (rec_buff[6] << 8) | (rec_buff[5]);
                    my_cgmv120_device_time_t.icurrent_time = (rec_buff[12] << 24) | (rec_buff[11] << 16) | (rec_buff[10] << 8) | (rec_buff[9]);
                    my_cgmv120_device_time_t.ilast_time = (rec_buff[16] << 24) | (rec_buff[15] << 16) | (rec_buff[14] << 8) | (rec_buff[13]);
                    my_cgmv120_device_time_t.u16last_index = (rec_buff[18] << 8) | (rec_buff[17]);
                    *P16cmd = 0xc03b;
                    //struct==============>json
                    cJSON* json_ack = struct_to_json_cgmv120_device_time_t(&my_cgmv120_device_time_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;
                }
                break;
                case 4:
                {
                    cgmv120_device_storage_t my_cgmv120_device_storage_t;
                    memset(&my_cgmv120_device_storage_t, 0, sizeof(my_cgmv120_device_storage_t));

                    my_cgmv120_device_storage_t.u8storage_status = rec_buff[3];
                    my_cgmv120_device_storage_t.u16storage_number = (rec_buff[5] << 8) | (rec_buff[4]);
                    my_cgmv120_device_storage_t.u8config_times = rec_buff[6];
                    my_cgmv120_device_storage_t.u8key_times = rec_buff[7];
                    *P16cmd = 0xc04b;
                    //struct==============>json 
                    cJSON* json_ack = struct_to_json_cgmv120_device_storage_t(&my_cgmv120_device_storage_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;
                }
                break;
                case 5:
                {
                    cgmv120_device_calibration_t my_cgmv120_device_calibration_t;
                    memset(&my_cgmv120_device_calibration_t, 0, sizeof(my_cgmv120_device_calibration_t));

                    my_cgmv120_device_calibration_t.icurrent0 = (rec_buff[6] << 24) | (rec_buff[5] << 16) | (rec_buff[4] << 8) | (rec_buff[3]);
                    my_cgmv120_device_calibration_t.icurrent1 = (rec_buff[10] << 24) | (rec_buff[9] << 16) | (rec_buff[8] << 8) | (rec_buff[7]);
                    my_cgmv120_device_calibration_t.itemp0 = (rec_buff[14] << 24) | (rec_buff[13] << 16) | (rec_buff[12] << 8) | (rec_buff[11]);
                    my_cgmv120_device_calibration_t.itemp1 = (rec_buff[18] << 24) | (rec_buff[17] << 16) | (rec_buff[16] << 8) | (rec_buff[15]);
                    *P16cmd = 0xc05b;
                    //struct==============>json  
                    cJSON* json_ack = struct_to_json_cgmv120_device_calibration_t(&my_cgmv120_device_calibration_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;
                }
                break;
                case 6:
                {
                    cgmv120_secret_key_t my_cgmv120_secret_key_t;
                    memset(&my_cgmv120_secret_key_t, 0, sizeof(my_cgmv120_secret_key_t));

                    my_cgmv120_secret_key_t.u8secret_key_num = (rec_buff[3]);
                    memcpy(my_cgmv120_secret_key_t.p8secret_key1, &rec_buff[4], 16);
                    memcpy(my_cgmv120_secret_key_t.p8secret_key2, &rec_buff[20], 16);

                    *P16cmd = 0xc06b;
                    //struct==============>json  
                    cJSON* json_ack = struct_to_json_cgmv120_secret_key_t(&my_cgmv120_secret_key_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;
                }
                break;
                case 7:
                {
                    cgmv120_device_reset_t my_cgmv120_device_reset_t;
                    memset(&my_cgmv120_device_reset_t, 0, sizeof(my_cgmv120_device_reset_t));

                    my_cgmv120_device_reset_t.ireset_time_stamp = (rec_buff[10] << 24) | (rec_buff[9] << 16) | (rec_buff[8] << 8) | (rec_buff[7]);
                    my_cgmv120_device_reset_t.u16reset_index = (rec_buff[6] << 8) | (rec_buff[5]);
                    my_cgmv120_device_reset_t.u8reset_synchron = rec_buff[4];
                    my_cgmv120_device_reset_t.u8reset_times = rec_buff[3];
                    *P16cmd = 0xc07b;
                    //struct==============>json  
                    cJSON* json_ack = struct_to_json_cgmv120_device_reset_t(&my_cgmv120_device_reset_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;

                }
                break;
                case 8:
                {
                    cgmv120_glousethreshold_t my_cgmv120_glousethreshold_t;
                    memset(&my_cgmv120_glousethreshold_t, 0, sizeof(my_cgmv120_glousethreshold_t));

                    my_cgmv120_glousethreshold_t.lower = (rec_buff[4] << 8) | rec_buff[3];
                    my_cgmv120_glousethreshold_t.upper = (rec_buff[6] << 8) | rec_buff[5];
                    ;
                    *P16cmd = 0xc08b;
                    //struct==============>json  
                    cJSON* json_ack = struct_to_json_cgmv120_glousethreshold_t(&my_cgmv120_glousethreshold_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;

                }
                break;
                case 9:
                {
                    cgmv120_oscillator_t my_cgmv120_oscillator_t;
                    memset(&my_cgmv120_oscillator_t, 0, sizeof(my_cgmv120_oscillator_t));

                    my_cgmv120_oscillator_t.state = rec_buff[3];

                    *P16cmd = 0xc09b;
                    //struct==============>json  
                    cJSON* json_ack = struct_to_json_cgmv120_oscillator_t(&my_cgmv120_oscillator_t);

                    char* json_string = cJSON_PrintUnformatted(json_ack);
                    //puts(json_string);

                    memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                    s2j_delete_json_obj(json_ack);
                    free(json_string);
                    ret = 1;

                }
                break;
                default:
                    break;
                }
            }
            else
            {
                ret = -3;
            }

        }
        break;
        default:
            ret = -3;
            break;
        }
    }
    else
    {
        ret = -2;
    }

    return ret;
}


/*********************************************************V110底软协议****************************************************************************************/
/*********************************************************V110底软协议****************************************************************************************/
/*********************************************************V110底软协议****************************************************************************************/
//APP =======>> CGM 相关API
Iret v110_raw_data(int customID, bool bEncyrpt,  uint8_t* a8Mac, uint16_t u16index, uint16_t u16Rtc, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V110_BUFF_LEN];
    memset(cmd_buff, 0, CMD_V110_BUFF_LEN);
    //加解密保留

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 20))
    {
        cmd_buff[0] = 0xAA;
        cmd_buff[1] = 0x55;

        cmd_buff[2] = 0x07;   // request

        cmd_buff[3] = (unsigned char)(u16index & 0xff); //INEX先传送低8位
        cmd_buff[4] = (unsigned char)(u16index >> 8);   //再送高8位

        memcpy(&cmd_buff[5], a8Mac, 6);
        cmd_buff[19] = md_app_get_checksum(cmd_buff, 19);

        memcpy(p8RetBuffer, cmd_buff, 20);
        ret = 20;
    }
    else
    {
        ret = -1;
    }
    return ret;
}

Iret v110_activation(int customID, bool bEncyrpt, uint8_t* a8Mac, uint16_t u16Rtc, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V110_BUFF_LEN];
    memset(cmd_buff, 0, CMD_V110_BUFF_LEN);
    //加解密保留

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 20))
    {
        cmd_buff[0] = 0xAA;
        cmd_buff[1] = 0x55;

        cmd_buff[2] = 0x07;   // request

        cmd_buff[3] = (unsigned char)(0x0001 & 0xff); //INEX先传送低8位
        cmd_buff[4] = (unsigned char)(0x0001 >> 8);   //再送高8位

        memcpy(&cmd_buff[5], a8Mac, 6);
        cmd_buff[19] = md_app_get_checksum(cmd_buff, 19);

        memcpy(p8RetBuffer, cmd_buff, 20);
        ret = 20;
    }
    else
    {
        ret = -1;
    }
    return ret;
}

Iret v110_reset(int customID, bool bEncyrpt, uint8_t* p8RetBuffer, uint16_t U16RetBuffLen)
{
    int ret = 0;
    uint8_t cmd_buff[CMD_V110_BUFF_LEN];
    memset(cmd_buff, 0, CMD_V110_BUFF_LEN);
    //加解密保留

    if ((p8RetBuffer != NULL) && (U16RetBuffLen >= 4))
    {
        cmd_buff[0] = 0xAA;
        cmd_buff[1] = 0x55;

        cmd_buff[2] = 0x10;   // request
        cmd_buff[3] = 0xf1;   

        memcpy(p8RetBuffer, cmd_buff, 4);
        ret = 4;
    }
    else
    {
        ret = -1;
    }
    return ret;
}

//CGM =======>> APP 相关API
Iret v110_spilt_data(int customID, uint8_t* p8DataBuffer, uint16_t* P16cmd, uint8_t* p_value_info_t, bool bEncyrpt)
{
    int ret = 0;
    uint16_t cmd_value = 0;
    uint8_t  rec_buff[REC_V110_BUFF_LEN];

    memset(rec_buff, 0, REC_V110_BUFF_LEN);

    if ((p8DataBuffer != NULL) && (p_value_info_t != NULL) && (P16cmd != NULL))
    {
        cmd_value |= *(p8DataBuffer + 2);

        switch (cmd_value)
        {
          case 0x07:
          {
              cgmv110_cmd_ack_t  my_cgmv110_cmd_ack_t;
              memset(&my_cgmv110_cmd_ack_t, 0, sizeof(my_cgmv110_cmd_ack_t));

              memcpy(rec_buff, p8DataBuffer, 20);

              if ((*rec_buff == 0xaa) && (*(rec_buff+1) == 0x55) && (rec_buff[19] == md_app_get_checksum(rec_buff, 19)))
              {
                  my_cgmv110_cmd_ack_t.u16reply_ack_type = 0xe001;
                  my_cgmv110_cmd_ack_t.u8reply_ack_resule = rec_buff[3];
                  *P16cmd = 0xe005;

                  //struct==============>json
                  cJSON* json_ack = struct_to_json_cgmv110_cmd_ack_t(&my_cgmv110_cmd_ack_t);

                  char* json_string = cJSON_PrintUnformatted(json_ack);
                  //puts(json_string);

                  memcpy(p_value_info_t, json_string, get_json_length(json_string) + 1);
                  s2j_delete_json_obj(json_ack);
                  free(json_string);
                  //json_string = cJSON_Print(json_ack);
                  ret = 1;
              }
              else
              {
                  ret = -3;
              }
          }
            break;
          case 0x09:
          {
              cgmv110_glouse_info_t  my_cgmv110_glouse_info_t[REC_V110_GLOUSE_MAXLEN] = {0};
              int package_num = 0;

              package_num = *(p8DataBuffer + 3);

              memcpy(rec_buff, p8DataBuffer, 145);

              if ((*rec_buff == 0xaa) && (*(rec_buff + 1) == 0x55) && (rec_buff[144] == md_app_get_checksum(rec_buff, package_num * 14 + 4)))
              {
                  for (int i = 0; i < package_num; i++)
                  {
                      my_cgmv110_glouse_info_t[i].index= (rec_buff[4+i*14]<<8)|rec_buff[5 + i * 14];
                      my_cgmv110_glouse_info_t[i].temp=  (rec_buff[6 + i * 14] << 8) | rec_buff[7 + i * 14];
                      my_cgmv110_glouse_info_t[i].dump= (rec_buff[8 + i * 14] << 8) | rec_buff[9 + i * 14];
                      my_cgmv110_glouse_info_t[i].current= (rec_buff[10 + i * 14] << 8) | rec_buff[11 + i * 14];
                      my_cgmv110_glouse_info_t[i].status = (rec_buff[12 + i * 14] << 8) | rec_buff[13 + i * 14];
                      my_cgmv110_glouse_info_t[i].leftsend = (rec_buff[14 + i * 14] << 8) | rec_buff[15 + i * 14];
                      my_cgmv110_glouse_info_t[i].nexttime = (rec_buff[16 + i * 14] << 8) | rec_buff[17 + i * 14];
                  }

                  *P16cmd = 0xe002;
                  //struct==============>json
                  unsigned char* ptr = p_value_info_t;
                  cJSON* json_ack=NULL;
                  uint16_t length_json = 0;
                  for (int i = 0; i < package_num; i++)
                  {
                      json_ack = struct_to_json_cgmv110_glouse_info_t(&my_cgmv110_glouse_info_t[i]);

                      char* json_string = cJSON_PrintUnformatted(json_ack);
                      int length = get_json_length(json_string);

                      length_json += length;
                     // printf("\nsize:%d", length + 1);
                     // printf("\n%s\n", json_string);
                      if (i == package_num - 1)
                      {
                          memcpy(ptr, json_string, length+1);
                      }
                      else
                      {
                          json_string[length] = ',';
                          memcpy(ptr, json_string, length+1);
                          ptr = ptr + length+1;
                      }
                      s2j_delete_json_obj(json_ack);
                      free(json_string);
                  }
                  if (length_json > 2400)
                  {
                      ret = -3;
                  }
                  else
                  {
                      ret = package_num;
                  }
              }
              else
              {
                  ret = -3;
              }
          }
            break;
          case 0x0A:
          {
              cgmv110_three_glouse_info_t  my_cgmv110_three_glouse_info_t[REC_V110_GLOUSE_MAXLEN] = { 0 };
              int package_num = 0;

              package_num = *(p8DataBuffer + 3);

              memcpy(rec_buff, p8DataBuffer, 145);

              if ((*rec_buff == 0xaa) && (*(rec_buff + 1) == 0x55) && (rec_buff[144] == md_app_get_checksum(rec_buff, package_num * 18 + 4)))
              {
                  for (int i = 0; i < package_num; i++)
                  {
                      my_cgmv110_three_glouse_info_t[i].index = (rec_buff[4 + i * 18] << 8) | rec_buff[5 + i * 18];
                      my_cgmv110_three_glouse_info_t[i].temp = (rec_buff[6 + i * 18] << 8) | rec_buff[7 + i * 18];
                      my_cgmv110_three_glouse_info_t[i].dump = (rec_buff[8 + i * 18] << 8) | rec_buff[9 + i * 18];
                      my_cgmv110_three_glouse_info_t[i].current = (rec_buff[10 + i * 18] << 8) | rec_buff[11 + i * 18];
                      my_cgmv110_three_glouse_info_t[i].current2 = (rec_buff[12 + i * 18] << 8) | rec_buff[13 + i * 18];
                      my_cgmv110_three_glouse_info_t[i].current3 = (rec_buff[14 + i * 18] << 8) | rec_buff[15 + i * 18];
                      my_cgmv110_three_glouse_info_t[i].status = (rec_buff[16 + i * 18] << 8) | rec_buff[17 + i * 18];
                      my_cgmv110_three_glouse_info_t[i].leftsend = (rec_buff[18 + i * 18] << 8) | rec_buff[19 + i * 18];
                      my_cgmv110_three_glouse_info_t[i].nexttime = (rec_buff[20 + i * 18] << 8) | rec_buff[21 + i * 18];
                  }

                  *P16cmd = 0xe003;
                  //struct==============>json
                  unsigned char* ptr = p_value_info_t;
                  cJSON* json_ack = NULL;
                  uint16_t length_json = 0;
                  for (int i = 0; i < package_num; i++)
                  {
                      json_ack = struct_to_json_cgmv110_three_glouse_info_t(&my_cgmv110_three_glouse_info_t[i]);

                      char* json_string = cJSON_PrintUnformatted(json_ack);
                      int length = get_json_length(json_string);

                      length_json += length;
                      // printf("\nsize:%d", length + 1);
                      // printf("\n%s\n", json_string);
                      if (i == package_num - 1)
                      {
                          memcpy(ptr, json_string, length + 1);
                      }
                      else
                      {
                          json_string[length] = ',';
                          memcpy(ptr, json_string, length + 1);
                          ptr = ptr + length + 1;
                      }
                      s2j_delete_json_obj(json_ack);
                      free(json_string);
                  }
                  if (length_json > 2400)
                  {
                      ret = -3;
                  }
                  else
                  {
                      ret = package_num;
                  }
              }
              else
              {
                  ret = -3;
              }
          }
            break;
        }
    }
    else
    {
        ret = -2;
    }

    return ret;
}


/********************************************************其它关联函数*****************************************************************************************/
/********************************************************其它关联函数*****************************************************************************************/
/********************************************************其它关联函数*****************************************************************************************/
Iret global_register_id(cgmv120_user_code_id_t* p8IdRegisterPack, unsigned short u16max_init_num)
{
    int ret = 0;
    unsigned char custemIndex = 0;
    unsigned char num_id = 0;
    unsigned short count = 0;
    cgmv120_user_code_id_t* p_cur_usercodeid = NULL;
    cgmv120_user_code_id_t* p_register_usercodeid = NULL;

    for (custemIndex = 0; custemIndex < CGMV120_MAX_USER_CODE; custemIndex++)   //遍历数组判断ID表里面元素个数
    {
        p_cur_usercodeid = (cgmv120_user_code_id_t*)&User_code_list_register[custemIndex];

        if (p_cur_usercodeid->customID != 0)
        {
            num_id++;
        }
        else
        {
            break;
        }
    }

    if ((CGMV120_MAX_USER_CODE - num_id) < u16max_init_num) //ID表剩下的位置装不了这么多了，能装多少装多少
    {
        count = CGMV120_MAX_USER_CODE - num_id;
        ret = -2;
    }
    else
    {
        count = u16max_init_num;
    }

    for (int i = 0; i < count; i++)       //ID号存在重复
    {
        p_register_usercodeid = (p8IdRegisterPack + i);
        for (int j = 0; j < num_id; j++)
        {
            p_cur_usercodeid = (cgmv120_user_code_id_t*)&User_code_list_register[j];
            if (p_cur_usercodeid->customID == p_register_usercodeid->customID)
            {
                ret = -1;
                return ret;
            }
        }
        for (int j = 0; j < CGMV120_MAX_SYSTEM_CODE; j++)
        {
            p_cur_usercodeid = (cgmv120_user_code_id_t*)&User_code_list[j];
            if (p_cur_usercodeid->customID == p_register_usercodeid->customID)
            {
                ret = -1;
                return ret;
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        p_register_usercodeid = (p8IdRegisterPack + i);

        p_cur_usercodeid = (cgmv120_user_code_id_t*)&User_code_list_register[num_id + i];

        p_cur_usercodeid->customID = p_register_usercodeid->customID;

        for (int j = 0; j < 17; j++)
        {
            p_cur_usercodeid->encryptKey[j] = p_register_usercodeid->encryptKey[j];
        }
    }

    if (ret != -2)
    {
        ret = num_id + count;
    }

    return ret;
}

int get_json_length(char* str)
{
    int length = 0;
    char* ptr = NULL;

    ptr = str;
    while (*ptr != '\0')
    {
        ptr++;
        length++;
    }
    return length;
}

void* id_ture_or_false(int customID)
{
    cgmv120_user_code_id_t* p_cur_usercodeid = NULL;
    const cgmv120_user_code_id_t* p_const_cur_usercodeid = NULL;

    void* ret = NULL;

    for (int i = 0; i < CGMV120_MAX_USER_CODE; i++)
    {
        p_cur_usercodeid = &User_code_list_register[i];

        if (p_cur_usercodeid->customID == customID)
        {
            ret = &(p_cur_usercodeid->encryptKey);
            return ret;
        }
    }
    for (int i = 0; i < CGMV120_MAX_SYSTEM_CODE; i++)
    {
        p_const_cur_usercodeid = &User_code_list[i];

        if (p_const_cur_usercodeid->customID == customID)
        {
            ret = &(p_const_cur_usercodeid->encryptKey);
            return ret;
        }
    }
    return ret;
}

unsigned char  md_app_get_checksum(unsigned char* pData, unsigned char len)
{
    unsigned short sum = 0;

    if (pData && len)
    {
        while (len--)
        {
            sum += *pData++;
        }
        sum = ~sum + 1;
        return (unsigned char)sum;
    }
    return 0;
}

uint8_t get_errocode(uint8_t errocode,uint16_t package_type)
{
    uint8_t ret = -1;
    switch (package_type)
    {
       case 0xc005: if (errocode == 5) { ret = 7; }break;
       case 0xc004: if (errocode == 2) { ret = 1; }  else if(errocode == 4) { ret = 2; }break;
       case 0xc008: if (errocode == 4) { ret = 3; }  else if(errocode == 5) { ret = 4; }break;
       case 0xc009: if (errocode == 4) { ret = 2; }  else if(errocode == 5) { ret = 5; }break;
       case 0xc011: if (errocode == 4) { ret = 2; }  else if(errocode == 5) { ret = 6; }break;
       case 0xc002: if (errocode == 2) { ret = 8; }  else if (errocode == 3) { ret = 9; }break;
       case 0xc00b: if (errocode == 4) { ret = 2; }  else if (errocode == 5) { ret = 5; }break;
       case 0xc007: if (errocode == 4) { ret = 2; }  else if (errocode == 5) { ret = 12; }break;
       default:
           ret = 11;
           break;
    }
    return ret;
}


/********************************************************混合接口*****************************************************************************************/
/********************************************************混合接口*****************************************************************************************/
/********************************************************混合接口*****************************************************************************************/
//Iret spilt_data(int customID, uint8_t* p8DataBuffer, uint8_t u8DataBufferLen, uint16_t* P16cmd, uint8_t* p_value_info_t, bool bEncyrpt, uint8_t* key)
//{
//    if ((*p8DataBuffer == 0xaa) && (*(p8DataBuffer + 1) == 0x55))
//    {
//        return v110_spilt_data( customID,  p8DataBuffer, P16cmd, p_value_info_t,  bEncyrpt,  key);
//    }
//    else
//    {
//        return v120_spilt_data(customID, p8DataBuffer,u8DataBufferLen,P16cmd, p_value_info_t, bEncyrpt, key);
//    }
//}


void string_to_struct_test(char* str)
{
    cgmv120_device_time_t* jj = (cgmv120_device_time_t*)malloc(250);

    cJSON* test1 = cJSON_Parse(str);
    jj = (cgmv120_device_time_t*)json_to_struct_cgmv120_device_time_t(test1);

    printf("\n0x%x", jj->iactivation_time);
    printf("\n0x%x", jj->icurrent_time);
    printf("\n0x%x", jj->ilast_time);
    printf("\n0x%x", jj->u16last_index);

}
