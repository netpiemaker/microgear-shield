/*************************************************************	
 * 																												  ***
 * 	File Description:  Colletion of functions								 		  ***
 * 								  available in wifi_task							        		  ***
 * 																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 *  																												  ***
 * 																												  ***
 * ************************************************************/


#ifndef WIFI_TASK
#define WIFI_TASK

void checkstatuswifi();

void setupwifi(char* ssid, char* pass);

void give_wifi_semaphore(void *pvParameters);

void wifi_task(void *pvParameters);

#endif
