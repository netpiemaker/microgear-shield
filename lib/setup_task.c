#include "user_main.h"
#include "setup_task.h"


extern xQueueHandle setup_queue;

void setup_task(void *pvParameters) {
	char setup_buf[128],buf[1];
	char* setup_argv[10];
	int index=0;
		while(1){
			if(xQueueReceive( setup_queue,&buf,100000 ) == pdPASS){
				if(*buf == '\r'){				
					tokenize(setup_buf, setup_argv, MAXARG, cmdstopper, argdelimiter);
					char *comm = command();
					//~ os_printf("arg0 = %s\n",comm);
					//~ os_printf("arg1 = %s\n",argString(1,setup_argv));
					//~ os_printf("arg2 = %s\n",argString(2,setup_argv));
					//~ os_printf("arg3 = %s\n",argString(3,setup_argv));

					if(strcmp(comm,ECHOMODE)==0) setechomode(argInt(1,setup_argv));
					if(strcmp(comm,PUSHMODE)==0)	setpushmode(argInt(1,setup_argv));	
					
					index=0;
					setup_argv[0] = '\0';
				}else{
					setup_buf[index] = *(char*)buf;
					setup_buf[++index] = '\0';
				}
			}
		}
	vTaskDelete( NULL );	
}

	void setpushmode(int n){
		if(echo_mode==1){
			//~ char msg[30];
			//~ strcat(msg,PUSHMODE);
			//~ strcat(msg,"=");
			//~ strcat(msg,(char*)n);
			//~ strcat(msg,"\n");
			//~ uart0_puts(msg);
			
			uart0_puts(PUSHMODE);
			 uart0_puts("=");
			 char d[1];
			 sprintf(d,"%d", n);
			 uart0_puts(d);
			 uart0_puts("\r\n");
			  //~ os_printf("\r\n");
		 }
		 
		push_mode = n;
		 //~ switch (push_mode){
			//~ case 0: os_printf("Push mode: 0\n"); break;
			//~ case 1: os_printf("Push mode: 1\n"); break;		 
		//~ }
	}
	
	void setechomode(int n){
		if(echo_mode==1){
			uart0_puts(ECHOMODE);
			 uart0_puts("=");
			 char d[1];
			 sprintf(d,"%d", n);
			 uart0_puts(d);
			 uart0_puts("\r\n");
			
			}
		echo_mode = n;
		//~ switch (echo_mode){
			//~ case 0: os_printf("Echo mode: 0\n"); break;
			//~ case 1: os_printf("Echo mode: 1\n");  break;		 
		//~ }
	}
