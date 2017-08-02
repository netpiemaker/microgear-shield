#ifndef __VAR
#define __VAR


 #define MAX_SIZE_TCP_PRINT 1024
 #define MAX_SIZE_FEED_DATA 500
 #define MAX_SIZE_APIKEY 50
 #define MAX_SIZE_TOKEN 50
 #define MAX_SIZE_TOKENSECRET 50
 #define MAX_SIZE_APPID 50
 #define MAX_SIZE_KEY 50
 #define MAX_SIZE_SECRET 50
 #define MAX_SIZE_ALIAS 50
 #define MAX_SIZE_FEEDNAME 50
 #define MAX_SIZE_PUBLISH 500
 #define MAX_SIZE_TOPIC 500
 #define MAX_SIZE_CHAT 500
 
extern xQueueHandle xQueueUART;

 /* <|General Variables declaration|>
 *		@message_sr -> Buffer for serial read
 * 	@param -> Indicator use to indicate state of switch case  				
 * 	@message_index -> Index of message_sr, send_buf1 and send_buf2
 * 	@client1_buf -> Ringbuffer strore data from TCP connection[client 1]
 * 	@client2_buf -> Ringbuffer strore data from TCP connection[client 2]
 * 	@mg_buf -> Ringbuffer strore data from NETPIE  
 * 	@WifiReady -> Semaphore handler use to indicate ready state of wifi
 * 	@SetWifi -> Semaphore handler use to set up ssid and password
 * 	@xQueueHandleUart -> Queue use to handle Uart packet
 * 	@echo_modoe -> Select mode of echo
 */ 
 
 char message_sr[200];
  RingBuf *client1_buf,*client2_buf,*mg_buf;
 int param;
 int message_index;
 xSemaphoreHandle WifiReady,SetWifi;
 xQueueHandle wifi_queue,client1_queue,client2_queue,microgear_queue,setup_queue,write_queue;
 uart_event_t xQueueHandleUart;
 Microgear mg;
 int echo_mode;
 int push_mode;

unsigned long current_time,past_time;
 
 /* <|MQTT Variables declaration|>
 *		@str -> MgStruct structure type keep all information of arrival message (topic,msg,msglen)
 * 	@str_pull -> MgStruct structure type store data that pull from microgear buffer
 *  	@token,tokensecret,appid,key,secret,alias -> Required info. to connect to NETPIE
 * 	@feedmode -> Indicator to choose apikey or not
 */ 
struct MgStruct str,str_pull;	
struct ip_info ipconfig;				//Use to get IP address of ESP8266
int feedmode;


 /* <|Wifi task Variables declaration|> */
  char ssid[25],password[25];
 int sending_bytes,port;
 

 /* <|Client1 Task Variables declaration|> */
 char cli1_buffer[MAX_SIZE_TCP_PRINT];
 char buf1[1];
 int cli1_index;
 struct espconn conn1;
 esp_tcp tcp1;
 ip_addr_t HostResolve_Ip1;
 
 
  /* <|Client2 Task Variables declaration|> */
 char cli2_buffer[MAX_SIZE_TCP_PRINT];
 char buf2[1];
 int cli2_index;
 struct espconn conn2;
 esp_tcp tcp2;
 ip_addr_t HostResolve_Ip2;
 
 
   /* <|Microgear Task Variables declaration|> */
 char mg_buffer[MAX_SIZE_TCP_PRINT];
 char appid[MAX_SIZE_APPID];
 char buf3[1];
 char feed_buff[MAX_SIZE_FEED_DATA];
 int mg_index;
 
 
 

 


#endif
