#include "user_main.h"
#include "client2_task.h"

extern xQueueHandle client2_queue;



/* <|DNS callback for conn2 if there is no maping ip in cache|> */
void ResolveDNS_for_conn2( const char *name, ip_addr_t *ipaddr, void *arg ){
	if(ipaddr == NULL){
		os_printf("Unable to resolved address from %s",name); 
	}else{
		memcpy(conn2.proto.tcp->remote_ip, ipaddr, 4);
		switch(conn2.state){
			case ESPCONN_CONNECT: os_printf("Error: %d \n", CONN_NOT_READY_TO_CONNECT); break;
			case ESPCONN_NONE: espconn_connect(&conn2); break;
			case ESPCONN_LISTEN: os_printf("Error: %d \n", CONN_NOT_READY_TO_CONNECT); break;
			case ESPCONN_WAIT: os_printf("Error: %d \n", CONN_NOT_READY_TO_CONNECT); break;
			case ESPCONN_WRITE: os_printf("Error: %d \n", CONN_NOT_READY_TO_CONNECT); break;
			case ESPCONN_READ: os_printf("Error: %d \n", CONN_NOT_READY_TO_CONNECT); break;
			case ESPCONN_CLOSE: espconn_connect(&conn2);  break;
		}
	}
}	


void client2_task(void *pvParameters) {
	cli2_index =0;
		while(1){
			if(xQueueReceive( client2_queue,&buf2, 100000) == pdPASS){
				if(*buf2 == '\r'){			
					//~ os_printf("RAW data inside task: %s\n",cli2_buffer);	
					cli2_index=0;
					char* cli2_argv[10];
					tokenize(cli2_buffer, cli2_argv, MAXARG, cmdstopper, argdelimiter);
					char *comm = command();
					//~ os_printf("arg0 = %s\n",comm);
					//~ os_printf("arg1 = %s\n",argString(1,cli2_argv));
					//~ os_printf("arg2 = %d\n",argInt(2,cli2_argv));
					//~ os_printf("arg3 = %s\n",argString(3,cli2_argv));
					
					if(strcmp(comm,CONNECT_TO_SERVER2_BY_CLIENT2)==0) connect2(argString(1,cli2_argv),argInt(2,cli2_argv));
					if(strcmp(comm,DISCONNECT_FROM_SERVER2)==0)	disconn2();
					if(strcmp(comm,CHECKSTATUS_CLIENT2)==0)	status2();	
					if(strcmp(comm,READ_DATA_FROM_CLIENT2_BUFFER)==0)	read2(argInt(1,cli2_argv));	
					if(strcmp(comm,PRINT_TO_SERVER2)==0)	print2(argString(1,cli2_argv));	
					if(strcmp(comm,READ_DATA_FROM_CLIENT2_BUFFER_TO_ARDUINO_LIB)==0)	read_arduino2(argInt(1,cli2_argv));		
					
				}else{
					cli2_buffer[cli2_index] = *(char*)buf2;
					cli2_buffer[++cli2_index] = '\0';
				}
			}
		}
	vTaskDelete( NULL );	
}

void connect2(char* ip, int port){
	if(echo_mode ==1) os_printf("%s=\"%s\",%d\n",CONNECT_TO_SERVER2_BY_CLIENT2,ip,port);
	conn2.proto.tcp->remote_port = port;
	if(espconn_gethostbyname(&conn2, ip, &HostResolve_Ip2, ResolveDNS_for_conn2) == ESPCONN_OK){
		memcpy(conn2.proto.tcp->remote_ip, &HostResolve_Ip2, 4);
		switch(conn2.state){
			case ESPCONN_CONNECT: os_printf("Error: %d \n", CONN_NOT_READY_TO_CONNECT); break;
			case ESPCONN_NONE:  espconn_connect(&conn2); break;
			case ESPCONN_LISTEN: os_printf("Error: %d \n", CONN_NOT_READY_TO_CONNECT); break;
			case ESPCONN_WAIT: os_printf("Error: %d \n", CONN_NOT_READY_TO_CONNECT); break;
			case ESPCONN_WRITE: os_printf("Error: %d \n", CONN_NOT_READY_TO_CONNECT); break;
			case ESPCONN_READ: os_printf("Error: %d \n", CONN_NOT_READY_TO_CONNECT); break;
			case ESPCONN_CLOSE: espconn_connect(&conn2);   break;
		}
	}
}

void disconn2(){
	if(echo_mode==1) os_printf("%s\n",DISCONNECT_FROM_SERVER2);
	espconn_disconnect(&conn2);
	conn2.type = ESPCONN_TCP;
	conn2.state = ESPCONN_NONE;
	conn2.proto.tcp = &tcp2;
	conn2.proto.tcp->local_port=espconn_port();
}

void status2(){
	if(echo_mode==1) os_printf("%s \n",CHECKSTATUS_CLIENT2	);
	switch(conn2.state){
		case ESPCONN_CONNECT: uart0_puts("OK\r\n"); break;
		case ESPCONN_NONE: uart0_puts("NONE\r\n"); break;
		case ESPCONN_LISTEN: uart0_puts("LISTENING\r\n"); break;
		case ESPCONN_WAIT: uart0_puts("WAITING\r\n"); break;
		case ESPCONN_WRITE: uart0_puts("WRITING\r\n"); break;
		case ESPCONN_READ: uart0_puts("READING\r\n"); break;
		case ESPCONN_CLOSE: uart0_puts("NOT CONNECTED\r\n"); break;
	}
}

void read2(int sending_bytes){
	if(echo_mode==1) os_printf("%s=\"%d\"\n",READ_DATA_FROM_CLIENT2_BUFFER,sending_bytes);
	int x;
	char c;
	int buffer_ele = client2_buf->numElements(client2_buf);
	if(buffer_ele != 0){
		if(buffer_ele > sending_bytes){
			for(x = 0;x<sending_bytes;x++){   					
				client2_buf->pull(client2_buf,&c);
				os_printf("%c",c);
			}
		}else {
			for(x = 0;x<buffer_ele;x++){   					
				client2_buf->pull(client2_buf,&c);
				os_printf("%c",c);
			}
		}
	}
}
	
	
void print2(char* payload){
	if(echo_mode==1) os_printf("%s=\"%s\"\n",PRINT_TO_SERVER2,payload);
		int index=0;
		while((int)payload[index] != 0){
			//~ os_printf("Payload : %d\n",(int)payload[index]);
			index++;
		}
		//~ os_printf("Index: %d",index);
		if(!(espconn_send(&conn2,payload,index))){
			uart0_puts("OK\r\n");				
		}else{
			os_printf("ERROR\n");
		}
}

void read_arduino2(int sending_bytes){
	int x;
	char c;
	int buffer_ele = client2_buf->numElements(client2_buf);
	if(buffer_ele != 0){
		uart0_putchar(162);
		if(buffer_ele > sending_bytes){
			  uart0_putchar((char)sending_bytes);
			for(x = 0;x<sending_bytes;x++){   					
					client2_buf->pull(client2_buf,&c);
					uart0_putchar(c);
			}
		}else {
			uart0_putchar((char)buffer_ele);
			//~ os_printf("%c",buffer_ele);				
			for(x = 0;x<buffer_ele;x++){   																
					client2_buf->pull(client2_buf,&c);
					uart0_putchar(c);
			}
		}
	}else{
		uart0_putchar(176);
	}	
}


/* <|DATA RECEIVED CALLBACK (FOR CLIENT 2)|> */ 
void recv_cb2(void *arg, char *pData, unsigned short len){
	int i;
	for(i=0;i<len;i++)client2_buf->add(client2_buf,(pData+i));
}

void connectCB2(void *arg) {
	uart0_puts("OK\r\n");
}

void errorCB2(void *arg, sint8 err) {
	os_printf("Error: %d\n", err);
}

/*	<|CLIENT2 DISCONNECT CALLBACK|> */
void disconnectCB2(void *arg) {
	 conn2.type = ESPCONN_TCP;
	conn2.state = ESPCONN_NONE;
	conn2.proto.tcp = &tcp2;
	conn2.proto.tcp->local_port=espconn_port();
}


