#include "user_main.h"
#include "wifi_task.h"


extern  xQueueHandle wifi_queue;

/**********************************************************************
 *												 Wifi task
 * 
 **********************************************************************/

 void wifi_task(void *pvParameters) {
	char wifi_buf[128],buf[1];
	char* wifi_argv[10];
	int index=0;;
	while(1){
		if(xQueueReceive( wifi_queue,&buf,2000 ) == pdPASS){
			if(*buf == '\r'){				
				tokenize(wifi_buf, wifi_argv, MAXARG, cmdstopper, argdelimiter);
				char *comm = command();
				//~ os_printf("arg0 = %s\n",comm);
				//~ os_printf("arg1 = %s\n",argString(1,wifi_argv));
				//~ os_printf("arg2 = %s\n",argString(2,wifi_argv));
				//~ os_printf("arg3 = %s\n",argString(3,wifi_argv));
				
				if(strcmp(comm,SETUPWIFI)==0) setupwifi(argString(1,wifi_argv), argString(2,wifi_argv));
				if(strcmp(comm,CHECKSTATUS_WIFI)==0)	checkstatuswifi();	
				
				index=0;
				wifi_argv[0] = '\0';
			}else{
				wifi_buf[index] = *(char*)buf;
				wifi_buf[++index] = '\0';
			}
		}
	}	
	vTaskDelete( NULL );
}
 
 
/**********************************************************************
 *												Check status Wifi
 * 
 **********************************************************************/
void checkstatuswifi() {
		if(echo_mode==1) os_printf("%s\n",CHECKSTATUS_WIFI);
		uint8_t status; 
		status = wifi_station_get_connect_status();
		if(status == STATION_GOT_IP){
			wifi_get_ip_info(STATION_IF, &ipconfig);
			os_printf("CONNECTED %d.%d.%d.%d\n", IP2STR(&ipconfig.ip));
		}else{
			os_printf("NOTCONNECTED\n");
		}
}

/**********************************************************************
 *												Setup/Config Wifi
 * 
 **********************************************************************/
void setupwifi(char* ssid, char* pass){
	if(echo_mode==1) os_printf("%s=\"%s\",\"%s\"\n",SETUPWIFI,ssid,pass);
	strcpy(ssid,ssid);
	strcpy(password,pass);
	xSemaphoreGive(SetWifi);
	uint8_t status;
	struct station_config *config = (struct station_config *)zalloc(sizeof(struct station_config));
	sprintf(config->ssid, ssid);
	sprintf(config->password, password);
	wifi_station_set_config(config);
	free(config);
	wifi_station_connect();
	
	int8_t retries = 30;
	while ((wifi_station_get_connect_status() != STATION_GOT_IP) && (retries > 0)) {
		status = wifi_station_get_connect_status();
		if (status == STATION_WRONG_PASSWORD) {
			os_printf("WRONG PASSWORD\n");
			break;
		}
		else if (status == STATION_NO_AP_FOUND) {
			os_printf("AP NOT FOUND\n");
			break;
		}
		else if (status == STATION_CONNECT_FAIL) {
			os_printf("CONNECTION FAIL\n");
			break;
		}
		vTaskDelay(1000 / portTICK_RATE_MS);
		--retries;
	}
	
	//~ if ((status = wifi_station_get_connect_status()) == STATION_GOT_IP) {
		//~ wifi_get_ip_info(STATION_IF, &ipconfig);
		//~ os_printf("CONNECTED %d.%d.%d.%d\n", IP2STR(&ipconfig.ip));
		//~ vTaskDelay(1000 / portTICK_RATE_MS);
	//~ }

	
}
 
/* <| Need for handle function inside microgear.h |> */ 
void give_wifi_semaphore(void *pvParameters){
	while(1){
		while ( wifi_station_get_connect_status()== STATION_GOT_IP) {
				xSemaphoreGive(WifiReady);
				//os_printf("WiFi: Alive\n");
				vTaskDelay(1000 / portTICK_RATE_MS);
		}
		vTaskDelay(100 / portTICK_RATE_MS);
	}
	vTaskDelete( NULL );
}




