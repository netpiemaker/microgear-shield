/*************************************************************	
 * 																												  ***
 * 	File Description:  Colletion of functions								 		  ***
 * 								  available in Client2 task     							  	  ***
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
 #ifndef CLIENT2_TASK
 #define CLIENT2_TASK 

void client2_task(void *pvParameters) ;

void connect2(char* ip, int port);
void disconn2();
void status2();
void read2(int size);
void print2(char* payload);
void read_arduino2(int size);

void ResolveDNS_for_conn2( const char *name, ip_addr_t *ipaddr, void *arg );

void recv_cb2(void *arg, char *pData, unsigned short len);
void connectCB2(void *arg);
void errorCB2(void *arg, sint8 err);
void disconnectCB2(void *arg) ;



#endif
