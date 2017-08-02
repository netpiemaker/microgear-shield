#ifndef __USER_MAIN_H
#define __USER_MAIN_H

#define INCLUDE_vTaskSuspend 1

#include "uart.h"

#include "Microgear.h"
#include "ringbuf.h"
#include "string.h"
#include "lwip/inet.h"
#include "var.h"
#include "wifi_task.h"
#include "error.h"

#include "microgear_task.h"
#include "client1_task.h"
#include "setup_task.h"
#include "client2_task.h"

#include "parser.h"


//WIFI task format
#define SETUPWIFI "AT+CW"																							//AT+CW "<SSID>","<PASS>"
#define CHECKSTATUS_WIFI "AT+CW?\r"																			//AT+CW?


//Setup task format
#define ECHOMODE "ATE"																									//ATE=0 (For turn off echo), ATE=1 (Turn on echo)
#define PUSHMODE "ATP"																										//ATP=1 (Push message on),ATP=0 (PUSH message off)

//Client 1 task
#define CONNECT_TO_SERVER1_BY_CLIENT1 "AT+CCS1"											//AT+CCS1="<IP>",<PORT>\r
#define DISCONNECT_FROM_SERVER1 "AT+CD1\r"															//AT+CD1\r
#define CHECKSTATUS_CLIENT1 "AT+CCS1?\r"																	//AT+CCS1?\r
#define READ_DATA_FROM_CLIENT1_BUFFER "AT+CR1"											//AT+CR1=<SIZE_TO_READ>\r
#define PRINT_TO_SERVER1 "AT+CP1"																			//AT+CP1="<PAYLOAD>"\r
#define READ_DATA_FROM_CLIENT1_BUFFER_TO_ARDUINO_LIB "AT+CRTA1"	//AT+CRTA1=<SIZE_TO_READ>\r

//Client 2 task
#define CONNECT_TO_SERVER2_BY_CLIENT2 "AT+CCS2"											//AT+CCS2="<IP>",<PORT>\r
#define DISCONNECT_FROM_SERVER2 "AT+CD2\r"															//AT+CD2\r
#define CHECKSTATUS_CLIENT2 "AT+CCS2?\r"																	//AT+CCS2?\r
#define PRINT_TO_SERVER2 "AT+CP2"																			//AT+CP2="<PAYLOAD>"\r
#define READ_DATA_FROM_CLIENT2_BUFFER "AT+CR2"											//AT+CR2=<SIZE_TO_READ>\r
#define READ_DATA_FROM_CLIENT2_BUFFER_TO_ARDUINO_LIB "AT+CRTA2"	//AT+CRTA2=<SIZE_TO_READ>\r

#define SECURE_CONNECT "AT+SCC "																				//AT+SCC <SERVER>,<PORT>,<OPTION>,<FOOTPRINT>
#define SECURE_CONNECTED "AT+SCC?"																		//AT+SCC?
#define SECURE_VERIFY "AT+SCVF"																					//AT+SCVF 
#define SECURE_READ "AT+SCR"																						//SECURE CLIENT READ
#define SECURE_PRINT "AT+SCP"																						//SECURE CLIENT PRINT



//Microgear task
#define CONNECT_TO_NETPIE "AT+MGCN\r"																		//AT+MGCN\r
#define MG_CHECKSTATUS "AT+MGCN?\r"  																			//AT+MGCN?
#define DISCONNECT_FROM_NETPIE "AT+MGDC\r"															//AT+MGDC\r
#define SETUP_TOKEN "AT+MGST"																					//AT+MGST="d4Y9Jl5vk1p1hWfM","ZRnOjRgpCEkK2mSlowI8zjQpqILpf7wI"\r
#define CONFIG_MICROGEAR "AT+MGCF"																				//AT+MGCF="HelloNetpie1","YhtHPvlmMxL5yJB","YphWgyUI31q8sEMu6qtNrIPn1","Light_control"\r
#define SET_ALIAS_NAME "AT+MGSA"																				//AT+MGSA="ALIAS_NEW"\r
#define PUBLISH "AT+MGP"																								//AT+MGP="<TOPIC>","<PAYLOAD>"\r
#define SUBSCRIBE "AT+MGS"																							//AT+MGS="<TOPIC>"\r
#define UNSUBSCRIBE "AT+MGUS"																					//AT+MGUS="<TOPIC>"\r
#define CHAT "AT+MGC"																										//AT+MGC="<ALIAS>","<PAYLOAD>"\r
#define PULL_MESSAGE "AT+MGPM\r"																					//AT+MGPM \r
#define PULL_MESSAGE_TO_ARDUINO_LIB "AT+MGPTA\r"												//AT+MGPMTA \r
#define WRITE_FEED "AT+MGWF"																					//AT+MGWF=<MODE>,"<FEEDNAME>","<DATA>","<API KEY>"\r

//AT+MGWF 0,"MicrogearShield","{Temp:12}"
//AT+MGWF 1,"MicrogearShield","{Temp:12}","fA78nqOtzasvAS1xg4MzlnfMn1FKHdUj"
//#define MAX_SIZE_TCP_PRINT 1024









#endif
