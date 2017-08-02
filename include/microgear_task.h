/*************************************************************	
 * 																												  ***
 * 	File Description:  Colletion of functions								 		  ***
 * 								  available in microgear task     							  ***
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
 
 #ifndef MG_TASK
 #define MG_TASK
extern xQueueHandle microgear_queue;


void onConnected(char *attribute, uint8_t* msg, uint16_t msglen);
void onMsghandler(char *topic, uint8_t* msg, uint16_t msglen);


void microgear_task(void *pvParameters);

void mg_connect();
void mg_status();
//~ void setup_token(char* token,char* token_secret);
void config_netpie(char* appid_fn, char*key, char*secret, char* alias, char* token,char* token_secret);
void mg_disconn();
void set_alias(char* alias);
void mg_publish(char* topic, char* payload);
void mg_subscribe(char* topic);
void mg_unscribe(char* topic);
void mg_writefeed(int feedmode, char* feedname, char* feeddata, char* apikey);
void mg_chat(char* device_name, char* payload);
void mg_pull_buf();
void mg_pull_buf_to_arduino();
int size(char *ptr);







#endif
				
