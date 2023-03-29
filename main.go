package main

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#cgo CFLAGS: -I./data_handle -I./rc4 -I./json
#cgo LDFLAGS: -L./data_handle -lcgm_data_handle  -L./rc4 -lWjCryptLib_Rc4  -L./json -lcJSON -lmy_struct_2_json -ls2j
#include "cgm_data_handle.h"

uint8_t valueInfo[7000] = {0};
uint8_t* decrypt(char *inputBuffer,int version) {
	//uint8_t encryptKey[] = {0x1, 0x38, 0xB, 0x9A, 0x0, 0x5B, 0x2, 0x5D, 0xcd, 0x9e, 0xc3, 0x99, 0x09, 0x37, 0xaa, 0xe8};
	char temp[3] = { 0 };
	char*ptr = inputBuffer;
	uint8_t data[500] = { 0 };
	int i = 0;
	while ((*ptr) != '\0')
    {
	  memcpy(temp, ptr, 2);
	  temp[2] = '\0';
	  data[i]=(uint8_t)strtoul(temp, NULL, 16);
	  i++;
	  ptr+= 2;
      //printf("字符是 %s\n", temp);
	  //printf("数字（无符号长整数）是 %lu\n", (uint8_t)strtoul(temp, NULL, 16));
	 }
	uint16_t cmd;
	//uint8_t valueInfo[7000];
	int succeed  = 0;
	///协议版本大于等于2，用120
	if (version >= 2) { //血糖
		succeed = v120_spilt_data(1, data, i, &cmd, valueInfo, true);
	}
	else if(version < 1){//乳酸
		succeed = v120_spilt_data_lactate(1, data, i, &cmd, valueInfo, false);
	} else {

	}
    //printf("%#x\n",cmd);
 	 //printf("%s\n",valueInfo);
	 return valueInfo;
}


uint8_t data[500] = {0};
uint8_t* strtoul2(char *str) {
	char temp[3] = { 0 };
	char*ptr = str;
	int i = 0;
	while ((*ptr) != '\0')
   	{
	  memcpy(temp, ptr, 2);
	  temp[2] = '\0';
	  data[i]=(uint8_t)strtoul(temp, NULL, 16);	 
	  i++;
	  ptr+= 2;
	  printf("字符是%s,数字（无符号长整数）是 %lu\n",temp,data[i-1]);
 	 }
	 return data;
}

uint8_t* rc4XorWithKeyOverride(char *inputBuffer,uint32_t inputBufferSize) {
	uint8_t encryptKey[] = {0x1, 0x38, 0xB, 0x9A, 0x0, 0x5B, 0x2, 0x5D, 0xcd, 0x9e, 0xc3, 0x99, 0x09, 0x37, 0xaa, 0xe8};
    	uint8_t  inputBufferUl[500] = {0};
	int i = 0;	
	strcpy(inputBufferUl,strtoul2(inputBuffer));
	for(int i=0;i<53;i++) {
	    printf("长整型为%d\n",inputBufferUl[i]);
	}
	//printf("长度为%d\n",inputBufferSize);
	Rc4XorWithKey(encryptKey, 16, 0, inputBufferUl, valueInfo,inputBufferSize);		
	//for(int i=0;i<53;i++) {
	    //printf("加密后的打印为%d\n",valueInfo[i]);
	//}
	return valueInfo;
}
*/
import "C"

import (
	"crypto/rand"
	"fmt"
	"math"
	"math/big"
	"unsafe"
)

var defaultPool = []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%&*?")

func main() {
	test04()
}

func test01() {
	//fmt.Println(randString(5, defaultPool))
	//fmt.Println(genPrivateKey("U1", "TS"))
	privateKey := genPrivateKey("U1", "TS")
	publicKey := genPublicKey(privateKey, "com.sibionicscgm.gjcg")
	fmt.Println(publicKey)
}

//func test02() {
//	//encryptStr := "(0x)AC-FF-7F-D8-08-27-66-6C-DF-5C-86-B2-04-1A-06-8C-82-57-E4-E3-29-FB-61-B6-7E-E0-FA-06-C7-FA-A7-EC-65-2D-00-8C-F4-FF-62-35-88-55-E8-75-BC-C3-A7-09-4D-B5-49-CC-F0-48-A8-CF-F4-D9-EB-25-90-60-51-FA-C7-F0-DA-9C-59-42-8F-E8-B0-4F-BC-8C-35-54-C8-6D-73-3F-02-0F-49-38-9C-4D-56-A0-A1-4A-1D-28-79-42-7A-B9-2F-25-73-5B-D8-7F-72-A9-AC-17-08-E9-46-0B-8D-AF-AC-B7-EE-AC-C2-60-17-92-51-4B-BA-2D-A3-4C-D2-8C-07-8F-09-85-9D-DF-21-FF-68-C9"
//	encryptStr2 := "(0x)AC-FF-7F-58-02-23-1C-8F-DE-B0-87-75-04-ED-06-4C-93-83-E5-3F-29-DF-61-36-6C-3A-FB-DF-C7-E6-A7-6C-77-F3-01-53-F4-8E-62-B5-9A-94-E9-AD-BC-B1-A7-D9-6F-70-48-15-F0-20-A8-1F-D6-1A-EA-FE-90-03-51-A2-E4-3C-DB-40-59-5C-8F-B0-93-82-BD-50-35-72-C8-35-50-F0-03-DD-49-11-9C-75-69-6E-A0-9D-1D-00-79-7A-45-70-2E-F1-73-73-D8-47-4A-64-AD-C0-08-C2-46-33-B5-61-AD-64-EE-98-C2-58-2F-5D-50-9D-BA-1E-A3-54-F4-40-06-5D-09-B6-9D-C7-07-D7-3B-53"
//	const GLUCOSE = 2
//	const LACTIC = 0
//	var tmp string
//	for k, v := range strings.Split(encryptStr2, "-") {
//		if k == 0 {
//			v = strings.TrimPrefix(v, "(0x)")
//		}
//		tmp += v
//		//fmt.Println("\n")
//		//fmt.Printf("%s\n", C.GoString((*C.char)(unsafe.Pointer(C.decrypt(str)))))
//	}
//	res := C.decrypt(C.CString(tmp), GLUCOSE)
//	jsonStr := C.GoString((*C.char)(unsafe.Pointer(res)))
//	fmt.Println(jsonStr)
//	var objects []DecryptData
//	var object DecryptData
//	var l, r int
//	for i := 0; i < len(jsonStr); i++ {
//		if jsonStr[i] == 123 { // {
//			l = i
//		}
//		if jsonStr[i] == 125 { // }
//			r = i
//			str := jsonStr[l : r+1]
//			fmt.Println(str)
//			err := json.Unmarshal([]byte(str), &object)
//			if err != nil {
//				fmt.Println(err.Error())
//			}
//			objects = append(objects, object)
//		}
//	}
//	//for _, v := range objects {
//	//	fmt.Println(v.Index, v.CreateTime)
//	//}
//}

func test03() {
	//加密
	privateKey := genPrivateKey("U1", "TS")
	publicKey := genPublicKey(privateKey, "com.sibionic.CGM")
	fmt.Printf("加密前key:%v\n", publicKey)
	str := fmt.Sprintf("%X\n", publicKey)
	//keyLen := len(publicKey)
	keyLen := 53
	res := C.rc4XorWithKeyOverride(C.CString(str), *(*C.uint)(unsafe.Pointer(&keyLen)))
	encryptstr := C.GoString((*C.char)(unsafe.Pointer(res)))
	fmt.Printf("加密后key:%X\n", encryptstr)
	//解密
	encryptstr_ := fmt.Sprintf("%X", encryptstr)
	keyLen2 := len(encryptstr_) / 2
	res2 := C.rc4XorWithKeyOverride(C.CString(encryptstr_), *(*C.uint)(unsafe.Pointer(&keyLen2)))
	decryptstr := C.GoString((*C.char)(unsafe.Pointer(res2)))
	//bytes := C.GoBytes(unsafe.Pointer(res2), *(*C.uint)(unsafe.Pointer(&keyLen2)))
	fmt.Printf("解密后key:%v\n", decryptstr)

}


func test04() {
	privateKey := genPrivateKey("U1", "TS")
	//privateKey := "GKSHGDU0TYA456G4"
	fmt.Printf("私钥%v\n",privateKey)
	publicKey := genPublicKey(privateKey, "com.no.sisense.newcgmtool")
	fmt.Printf("加密前key:%v\n", publicKey)
        str := fmt.Sprintf("%X", publicKey)
        keyLen := len(publicKey)
	fmt.Printf("0x长度是%v,值是%v\n",keyLen,str)
        res := C.rc4XorWithKeyOverride(C.CString(str), *(*C.uint)(unsafe.Pointer(&keyLen)))
        //encryptstr := C.GoString((*C.char)(unsafe.Pointer(res)))
	var v = keyLen
	var s []byte
	const vmax =  math.MaxInt32 / unsafe.Sizeof(s[0])
	encrypt := (*[vmax]byte)(unsafe.Pointer(res))[:v:v] //uint8_t*转byte[]
	fmt.Printf("加密后key:%X\n",encrypt)
}

// key生成
func genPrivateKey(group, user string) string {
	return fmt.Sprintf("%v%v%v%v", randString(6, defaultPool), group, user, randString(6, defaultPool))
}

func genPublicKey(privateKey, bundlerId string) string {
	return fmt.Sprintf("%v%v%v%v", randString(6, defaultPool), privateKey, bundlerId, randString(6, defaultPool))
}

func randString(n int, pool []rune) string {
	b := make([]rune, n)
	for i := range b {
		l := len(pool)
		randN, _ := rand.Int(rand.Reader, big.NewInt(int64(l)))
		b[i] = pool[randN.Int64()]
	}
	return string(b)
}
