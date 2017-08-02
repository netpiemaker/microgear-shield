/*************************************************************	
 * 																												  ***
 * 	File Description:  Colletion of functions								 		  ***
 * 								  available in Client1 task     								  ***
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
 #ifndef CLIENT1_TASK
 #define CLIENT1_TASK 

void client1_task(void *pvParameters) ;

void connect1(char* ip, int port);
void disconn1();
void status1();
void read1(int size);
void print1(char* payload);
void read_arduino1(int size);

void ResolveDNS_for_conn1( const char *name, ip_addr_t *ipaddr, void *arg );

void recv_cb1(void *arg, char *pData, unsigned short len);
void connectCB1(void *arg);
void errorCB1(void *arg, sint8 err);
void disconnectCB1(void *arg) ;



#endif
