 
/******************************************************************************
 * Simple Socket Server (SSS) example. 
 * 
 * This example demonstrates the use of MicroC/OS-II running on NIOS II.       
 * In addition it is to serve as a good starting point for designs using       
 * MicroC/OS-II and Altera NicheStack TCP/IP Stack - NIOS II Edition.                                          
 *                                                                             
 * -Known Issues                                                             
 *     None.   
 *      
 * Please refer to the Altera NicheStack Tutorial documentation for details on this 
 * software example, as well as details on how to configure the NicheStack TCP/IP 
 * networking stack and MicroC/OS-II Real-Time Operating System.  
 */
 
#include <stdio.h>
#include <string.h>
#include <ctype.h> 

/* MicroC/OS-II definitions */
#include "includes.h"
#include "LCDTask.h"
/* Simple Socket Server definitions */
#include "types.h"
#include "simple_socket_server.h"
#include "AquisicaoRede.h"
#include "alt_error_handler.h"

/* Nichestack definitions */
#include "ipport.h"
#include "tcpport.h"
#include "defines.h"

#include "fft_pipeline_.h"
#include "fixedpoint2_16.h"
#define PI	3.14159265358979323846

#define DEBUG 1

void CopiaResultadoAoBuffer(FIXED2_16 *real, FIXED2_16 *imag, int size, unsigned char * buffer);

OS_STK    timer_task_stk[TASKTIMER_STACKSIZE];
OS_STK    aquisicao_task_stk[TASKAQUIS_STACKSIZE];
OS_STK    aquisicao_task1_stk[TASKAQUIS_STACKSIZE];
OS_STK    lcd_task_stk[TASK_STACKSIZE];
OS_STK    socket_sender_task_stk[TASK_STACKSIZE];
OS_STK    socket_receiver_task_stk[TASK_STACKSIZE];
OS_STK    socket_result_sender_task_stk[TASK_STACKSIZE];

OS_FLAG_GRP *EventoSocket;
OS_FLAG_GRP *novos_dados=0;

//variaveis globais
static stt_socket estado_socket = stopped;
static stt_socket estado_socket_sender = stopped;
static stt_socket estado_socket_receiver = stopped;
static stt_socket estado_socket_sender_result = stopped;

int fdSocketSender, fdSocketReceiver, fdSocketSenderResult; //ponteiro para o socket
Pacote_t pacote;
unsigned char buffer_tx[TAMANHOBUFFER], buffer_rx[TAMANHOBUFFER];
unsigned char bufferDADOS[TAMANHOBUFFER];

//Flag que dá inicio ao socket
char iniciar_socket = 0;


void AquisicaoRedeTask1(void *task_data){
	OS_FLAGS value;
	INT8U error_code;
	int i,j;
	FIXED2_16 vetorXreal[256], vetorXimag[256];
	FIXED2_16 ponto;
	float fp;

	OSTimeDlyHMSM(0,0,1,0);
	while(1){
		//Aguarda pelo evento da recepção ou pelo timeout
	    value = OSFlagPend(novos_dados, 0x0001, OS_FLAG_WAIT_SET_ANY+OS_FLAG_CONSUME, 0, &error_code);
	    printf("\n[Aquisição de dados] Novos dados recebidos:\n");
	   // for(i=0; i < pacote.Size; i++){
	   // 	printf("%d, ", pacote.Dados.Aquis[i]);
	  //  }
	 //   printf("Inicializando FFT... ");
		for(i=0; i<256; i++){
			    //printf("%d, ", pacote.Dados.Aquis[i]);
			    ponto.full = (long)((float)(pacote.Dados.Aquis[i]-1250)*0.1);
				FFT_ESCREVE_DADO(i, ponto.full);
		}
	//	printf("Executando FFT!\n");
		FFT_START();

	//	printf("Aguardando execução FFT!\n");
/*	i=0;
		while(FFT_FINISHED() == 0){
				if(i++>100000)break;
		}

		#define real1base 0
		#define imag1base 512
		#define real2base 1024
		#define imag2base 1536

		j=0;
		for(i=0; i<256; i+=2){
			vetorXreal[i].full = FFT_LE_DADO(j+real1base);
			vetorXreal[i+1].full = FFT_LE_DADO(j+real2base);
			vetorXimag[i].full = FFT_LE_DADO(j+imag1base);
			vetorXimag[i+1].full = FFT_LE_DADO(j+imag2base);
			j++;
		}
		*/
	//	printf("Pronto!\n");
	//	printf("Enviando os dados ao PC\n");
		OSTimeDlyHMSM(0,0,1,0);
		CopiaResultadoAoBuffer(vetorXreal, vetorXimag, 256, bufferDADOS);
		OSFlagPost(novos_dados, 0x0002, OS_FLAG_SET, &error_code);
	}
}
void CopiaResultadoAoBuffer(FIXED2_16 *real, FIXED2_16 *imag, int size, unsigned char * buffer){
		int i,j;

		j=0;
		for(i=0; i<4*size-4; i+=4){
			buffer[i] = (unsigned char)(real[j].full>>10);
			buffer[i+1] = (unsigned char)((real[j].full>>2)&0xFF);
			buffer[i+2] = (unsigned char)(imag[j].full>>8);
			buffer[i+3] = (unsigned char)((imag[j].full&0xFF));
			j++;
		}

}


void SocketResultSender(void *task_data){
	    INT8U error_code;
		OS_FLAGS value;

		char count=0;
		int enviados;
		int rlen;
		short msglen;
		struct sockaddr_in addr, remoto;

		printf("\n Socket result sender active");
		while(1){

			switch(estado_socket_sender_result){
				case stopped:
					estado_socket_sender_result = starting;
				break;
				case starting:
					//Crie o socket
					 if ((fdSocketSenderResult = socket(AF_INET,  SOCK_DGRAM, 0)) < 0)
					 {
						 alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,"\n [SocketSenderResultTask] Socket creation failed");
					 }else{
						 printf("\n [SocketSenderResultTask] Criou o socket.");
					 }
					 //Configure os dados do socket
					 addr.sin_family = AF_INET;
					 addr.sin_port = htons(PORTA_UDP-1);
					 addr.sin_addr.s_addr = INADDR_ANY;
					  //Bind
					 if ((bind(fdSocketSenderResult,(struct sockaddr *)&addr,sizeof(addr))) < 0)
					 {
						alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,"\n [SocketSenderResultTask] Bind failed");
					 }else{
						  printf("\n[SocketSenderResultTask] Vinculou o IP.");
						  //Passou pela inicialização necessária entao vá para o estado de aguardando
						  estado_socket_sender_result = waiting;
					 }
				break;
				case sending:

					remoto.sin_family = AF_INET;
					remoto.sin_port= htons(PORTA_UDP-1);
					IP4_ADDR(remoto.sin_addr.s_addr, 192,168,1,103); //Colocar o IP do destino
					rlen = sizeof(remoto);

					enviados = sendto(fdSocketSenderResult,    buffer_rx+4,  512,         0, (struct sockaddr *)&remoto,      rlen);
					printf("\n[SocketSenderResultTask] Enviados %d dados.", enviados);

					msglen = 1024;
					//Envia dados UDP:SOCKET   BUFFER      TAMANHO BUFFER  FLAGS   ENDERECO REMOTO e seu TAMANHO
					enviados = sendto(fdSocketSenderResult,    bufferDADOS,     msglen,         0, (struct sockaddr *)&remoto,      rlen);


					if(enviados>0){
						printf("\n[SocketSenderResultTask] Enviados %d dados.", enviados);
						estado_socket_sender_result = waiting;
					}else
					{
						printf("\n[SocketSenderResultTask] Erro! Enviados %d dados.", enviados);
						estado_socket_sender_result = error;
					}
				break;
				case waiting:
					//Aguarda pelo evento de enviar dados
					value = OSFlagPend(novos_dados, 0x0002, OS_FLAG_WAIT_SET_ANY+OS_FLAG_CONSUME, 0, &error_code);
					if(error_code == OS_TIMEOUT)
						{

						}
					else if(error_code==OS_NO_ERR){
						printf("\n[SocketSenderResultTask] Evento recebido.");

					}else{
						printf("\n[SocketSenderResultTask] Erro desconhecido= 0x%X", error_code);
					}
					estado_socket_sender_result = sending;
				break;
				case error:
					estado_socket_sender_result = closing;
				break;
				case closing:
					close(fdSocketSenderResult);
				break;
				default:
				break;
			}
		}
}

void CopiaDadosAoPacote(unsigned char * buffer, Pacote_t * pacote){

	 short i;
	 short dado;

	pacote->Origem = *buffer;
	buffer++;
	pacote->Tipo = *buffer;
	buffer++;

	dado = (short)(*buffer)*256;
	buffer++;
	dado += (short)(*buffer);
	buffer++;
	pacote->Size = dado;

	for(i=0; i< pacote->Size; i++){
		dado = (short)(*buffer)*256;
		buffer++;
		dado += (short)(*buffer);
		buffer++;
		pacote->Dados.Aquis[i] = dado;//(dado>>4) - 128;
	}

}

void CriaTarefas(void)
{
   INT8U error_code;
  alt_uCOSIIErrorHandler(error_code, 0);

   printf("Criando tarefas.\n");
   error_code = OSTaskCreateExt(LCDTask,
                       NULL,
                       (void *)&lcd_task_stk[TASK_STACKSIZE-1],
                       LCD_TASK_PRIORITY,
                       LCD_TASK_PRIORITY,
                       lcd_task_stk,
                       TASK_STACKSIZE,
                       NULL,
                       0);

   error_code = OSTaskCreateExt(AquisicaoRedeTask1,  //Função
                      NULL, //Argumentos
                      (void *)&aquisicao_task1_stk[TASKAQUIS_STACKSIZE-1], //Stack
                    		  AQUISICAO_TASK1_PRIORITY,//Prioridade
                    		  AQUISICAO_TASK1_PRIORITY,//ID
                    		  aquisicao_task1_stk,//Stack
                    		  TASKAQUIS_STACKSIZE,//Tamanho do stack
                      NULL,
                      0);//Opções*/

   error_code = OSTaskCreateExt(AquisicaoRedeTask,  //Função
                         NULL, //Argumentos
                         (void *)&aquisicao_task_stk[TASKAQUIS_STACKSIZE-1], //Stack
                       		  AQUISICAO_TASK_PRIORITY,//Prioridade
                       		  AQUISICAO_TASK_PRIORITY,//ID
                       		  aquisicao_task_stk,//Stack
                       		  TASKAQUIS_STACKSIZE,//Tamanho do stack
                         NULL,
                         0);//Opções*/

   printf("Criou tarefa aquisicaorede.");

}

void Temporizador(void){
	while(1){
		//aguarda evento de inicio..
		OSTimeDlyHMSM(0,0,1,0);
		//Fim do tempo
		//Se recebeu dados, limpe o flag, e volte ao inicio
		//Se não recebeu dados, feche o socket e reinicie a tarefa de recepção de dados UDP
	}
}

void CriaSocketsTasks(void){
	INT8U error_code;

	printf("\nCria grupo de eventos.");
	EventoSocket = OSFlagCreate(0x00, &error_code);
	novos_dados =  OSFlagCreate(0x00, &error_code);
	alt_uCOSIIErrorHandler(error_code, 0);


    printf("\nCriando tarefa socket sender. ");
    error_code = OSTaskCreateExt(SocketSender,
					 NULL,
					 (void *)&socket_sender_task_stk[TASK_STACKSIZE-1],
					 SOCKET_SENDER_PRIORITY,
					 SOCKET_SENDER_PRIORITY,
					 socket_sender_task_stk,
					 TASK_STACKSIZE,
					 NULL,
					 0);

    printf("Criou tarefa socket server.");
    alt_uCOSIIErrorHandler(error_code, 0);

    printf("\nCriando tarefa socket receiver. ");
    error_code = OSTaskCreateExt(SocketReceiver,
						NULL,
						(void *)&socket_receiver_task_stk[TASK_STACKSIZE-1],
						SOCKET_RECEIVER_PRIORITY,
						SOCKET_RECEIVER_PRIORITY,
						socket_receiver_task_stk,
						TASK_STACKSIZE,
						NULL,
				0);

	  printf("Criou tarefa socket receiver");
	  alt_uCOSIIErrorHandler(error_code, 0);

	  printf("\nCriando tarefa socket result sender. ");
	      error_code = OSTaskCreateExt(SocketResultSender,
	  						NULL,
	  						(void *)&socket_result_sender_task_stk[TASK_STACKSIZE-1],
	  						SOCKET_RESULT_SENDER_PRIORITY,
	  						SOCKET_RESULT_SENDER_PRIORITY,
	  						socket_result_sender_task_stk,
	  						TASK_STACKSIZE,
	  						NULL,
	  				0);

	  	  printf("Criou tarefa socket result sender");
	  	  alt_uCOSIIErrorHandler(error_code, 0);
}

void SocketSender(void *task_data){
	INT8U error_code;
	OS_FLAGS value;

	char count=0;
	int enviados;
	int rlen;
	short msglen;
	struct sockaddr_in addr, remoto;

	OSTimeDlyHMSM(0,0,1,0);
#ifdef DEBUG
	printf("\n Socket sender active");
#endif
	 while(1){

		switch(estado_socket_sender){
			case stopped:
				estado_socket_sender = starting;
			break;
			case starting:
				//Crie o socket
				 if ((fdSocketSender = socket(AF_INET,  SOCK_DGRAM, 0)) < 0)
				 {
					 alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,"\n [SocketSenderTask] Socket creation failed");
				 }else{
					 printf("\n [SocketSenderTask] Criou o socket.");
				 }
				 //Configure os dados do socket
				 addr.sin_family = AF_INET;
				 addr.sin_port = htons(PORTA_UDP);
				 addr.sin_addr.s_addr = INADDR_ANY;
				  //Bind
				 if ((bind(fdSocketSender,(struct sockaddr *)&addr,sizeof(addr))) < 0)
				 {
					alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,"\n [SocketSenderTask] Bind failed");
				 }else{
					  printf("\n[SocketSenderTask] Vinculou o IP.");
					  //Passou pela inicialização necessária entao vá para o estado de solicitação de dados
					  estado_socket_sender = sending;
				 }
			break;
			case sending:

				remoto.sin_family = AF_INET;
				remoto.sin_port= htons(PORTA_UDP);
				IP4_ADDR(remoto.sin_addr.s_addr, 192,168,1,110); //Colocar o IP do destino
				rlen = sizeof(remoto);
				//Dado a enviar para o Tower: G
				sprintf(buffer_tx, "G %d\r\n", count++);
				if(count>=100) count = 0;
				msglen = 1;

				OSTimeDlyHMSM(0,0, 1, 200);
				//Envia dados UDP:SOCKET   BUFFER      TAMANHO BUFFER  FLAGS   ENDERECO REMOTO e seu TAMANHO
				enviados = sendto(fdSocketSender,    buffer_tx,     msglen,         0, (struct sockaddr *)&remoto,      rlen);
				if(enviados>0){
#ifdef DEBUG
					printf("\n[SocketSenderTask] Enviados %d dados.", enviados);
#endif
				 estado_socket_sender = waiting;
				}else
				{
#ifdef DEBUG
				 printf("\n[SocketSenderTask] Erro! Enviados %d dados.", enviados);
#endif
				 estado_socket_sender = error;
				}
			break;
			case waiting:
				//Aguarda pelo evento da recepção ou pelo timeout
				value = OSFlagPend(EventoSocket, 0x0001, OS_FLAG_WAIT_SET_ANY+OS_FLAG_CONSUME, 500, &error_code);
				if(error_code == OS_TIMEOUT)
					{
#ifdef DEBUG
					printf("\n[SocketSenderTask] Timeout na recepção de dados, reenviando em 3 segundos.");
#endif
					OSTimeDlyHMSM(0,0,3,0);//Eram 3 segundos
					}
				else if(error_code==OS_NO_ERR){
#ifdef DEBUG
					printf("\n[SocketSenderTask] Evento recebido.");
					//OSTimeDlyHMSM(0,0,0,1);
#endif
				}else{
#ifdef DEBUG
					printf("\n[SocketSenderTask] Erro desconhecido= 0x%X", error_code);
#endif
				}
				estado_socket_sender = sending;
			break;
			case error:
				estado_socket_sender = closing;
			break;
			case closing:
				close(fdSocketSender);
			break;
			default:
			break;
		}
	}
}

void SocketReceiver(void *task_data){
	INT8U error_code;

	int recebidos;
	int rlen;
	struct sockaddr_in addr, remoto;

	OSTimeDlyHMSM(0,0,1,0);
#ifdef DEBUG
	printf("\n Socket receiver active");
#endif
	while(1){
		switch(estado_socket_receiver){
					case stopped:
						estado_socket_receiver = starting;
					break;
					case starting:
						//Crie o socket
						 if ((fdSocketReceiver = socket(AF_INET,  SOCK_DGRAM, 0)) < 0)
						 {
							 alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,"\n [SocketReceiverTask] Socket creation failed");
						 }else{
#ifdef DEBUG
							 printf("\n [SocketReceiverTask] Criou o socket.");
#endif
						 }
						 //Configure os dados do socket
						 addr.sin_family = AF_INET;
						 addr.sin_port = htons(PORTA_UDP+1);
						 addr.sin_addr.s_addr = INADDR_ANY;
						  //Bind
						 if ((bind(fdSocketReceiver,(struct sockaddr *)&addr,sizeof(addr))) < 0)
						 {
							alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,"\n [SocketReceiverTask] Bind failed");
						 }else{
#ifdef DEBUG
							 printf("\n [SocketReceiverTask] Vinculou o IP.");
#endif
							  //Passou pela inicialização necessária entao vá para o estado de solicitação de dados
							  estado_socket_receiver = receiving;
						 }
					break;
					case waiting:
					break;
					case receiving:
							//Receba 100 pontos e avise a aplicação
							//Recebe dados UDP:  SOCKET     BUFFER      TAMANHO BUFFER      FLAGS ENDERECO REMOTO e seu TAMANHO
							rlen = sizeof(remoto);
							remoto.sin_family = AF_INET;
							remoto.sin_port= htons(PORTA_UDP);
							remoto.sin_addr.s_addr = INADDR_ANY;
							recebidos = recvfrom(fdSocketReceiver, buffer_rx,     TAMANHOBUFFER,     0,   (struct sockaddr *) &remoto,     &rlen);
							//Se recebeu dados, entao recebido será maior que zero
							if(recebidos>0){
								   estado_socket_receiver = receiving;


								   //pacote = (Pacote_t *)buffer_rx;
								   CopiaDadosAoPacote(buffer_rx, &pacote);

#ifdef DEBUG
									printf("\n[SocketReceiverTask] Recebidos %d dados. IP: %s:%d",
											recebidos, inet_ntoa(remoto.sin_addr), ntohs(remoto.sin_port));

									/*printf("[RecepcaoDadosUDP] Origem: %c, Tipo %c, Size: %d, Buffer: %s\n",
											pacote->Origem, pacote->Tipo, pacote->Size, pacote->Dados.Info);*/
									printf("\n[SocketReceiverTask] Origem: %d, Tipo %d, Size: %d",
											pacote.Origem, pacote.Tipo, pacote.Size);
#endif
									//Envia um evento para a tarefa SocketSender
									OSFlagPost(EventoSocket, 0x0003, OS_FLAG_SET, &error_code);
									OSFlagPost(novos_dados, 0x0001, OS_FLAG_SET, &error_code);
									//novos_dados = 1;

							} else {
								//Senao, recebidos será igual a -1, entao houve um erro
								estado_socket_receiver = error;
#ifdef DEBUG
								printf("\n[SocketReceiverTask] Erro! Recebidos %d dados.", recebidos);
#endif
							}
					break;
					case error:
						estado_socket_receiver = closing;
					break;
					case closing:
						close(fdSocketReceiver);
					break;
					default:
					break;
				}
	}

}

void RecepcaoDadosUDP()
{

	 char count=0;
	 int enviados, recebidos;
	 int rlen;
	 short msglen;
	 struct sockaddr_in addr, remoto;

	 printf("\n[RecepcaoDadosUDP] Inicializando sockets...");
	 CriaSocketsTasks();
	 OSTaskSuspend(OS_PRIO_SELF);//Suspende a atual tarefa
	 OSTimeDlyHMSM(0,0,2,0); //Aguarde 3 segundo antes de iniciar.
	 while(1){
	 switch(estado_socket){
	     /*=============================================================================
    	 Inicializando socket
	     ==============================================================================*/
	     case starting:

				 //Crie o socket
			 	 if ((fdSocketSender = socket(AF_INET,  SOCK_DGRAM, 0)) < 0)
			 	 {
			 	     alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,"[RecepcaoDadosUDP] Socket creation failed");
			 	 }else{
			 		 printf("[RecepcaoDadosUDP] Criou o socket.\n");
			 	 }

			 	 //Configure os dados do socket
			 	 addr.sin_family = AF_INET;
			 	 addr.sin_port = htons(PORTA_UDP);
			 	 addr.sin_addr.s_addr = INADDR_ANY;
			 	  //Bind
			 	 if ((bind(fdSocketSender,(struct sockaddr *)&addr,sizeof(addr))) < 0)
			 	 {
			 	    alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,"[RecepcaoDadosUDP] Bind failed");
			 	 }else{
			 		  printf("[RecepcaoDadosUDP] Vinculou o IP.\n");
			 		  //Passou pela inicialização necessária entao vá para o estado de solicitação de dados
					  estado_socket = sending;
			 	 }
				OSTimeDlyHMSM(0,0,3,0);
		 break;
		 /*=============================================================================
		 Enviando dados
		 ==============================================================================*/
		 case sending:
			 remoto.sin_family = AF_INET;
			 remoto.sin_port= htons(PORTA_UDP);
			 IP4_ADDR(remoto.sin_addr.s_addr, 192,168,1,110); //Colocar o IP do destino
			 rlen = sizeof(remoto);
			 //Dado a enviar para o Tower: D
			 sprintf(buffer_tx, "G %d\r\n", count++);
			 if(count>=100) count = 0;
			 msglen = 1;
			 //Envia dados UDP:SOCKET   BUFFER      TAMANHO BUFFER  FLAGS   ENDERECO REMOTO e seu TAMANHO
			 enviados = sendto(fdSocketSender,    buffer_tx,     msglen,         0, (struct sockaddr *)&remoto,      rlen);
			 if(enviados>0){
				 printf("[RecepcaoDadosUDP] Enviados %d dados.\n", enviados);
				 estado_socket = receiving;
			 }else
			 {
				 printf("[RecepcaoDadosUDP] Erro! Enviados %d dados.\n", enviados);
				 estado_socket = error;
			 }

		 break;
		 /*=============================================================================
		 Recebendo dados
		 ==============================================================================*/
		 case receiving:
			//Receba 100 pontos e avise a aplicação
			//Recebe dados UDP:  SOCKET     BUFFER      TAMANHO BUFFER      FLAGS ENDERECO REMOTO e seu TAMANHO
			rlen = sizeof(remoto);
			remoto.sin_family = AF_INET;
		    remoto.sin_port= htons(PORTA_UDP);
		    remoto.sin_addr.s_addr = INADDR_ANY;
			recebidos = recvfrom(fdSocketSender, buffer_rx,     TAMANHOBUFFER,     0,   (struct sockaddr *) &remoto,     &rlen);
			//Se recebeu dados, entao recebido será maior que zero
			if(recebidos>0){
					estado_socket = sending;
					CopiaDadosAoPacote(buffer_rx, &pacote);
					//pacote = (Pacote_t *)buffer_rx;
					printf("[RecepcaoDadosUDP] Recebidos %d dados. IP: %s:%d\n",
							recebidos, inet_ntoa(remoto.sin_addr), ntohs(remoto.sin_port));
					/*printf("[RecepcaoDadosUDP] Origem: %c, Tipo %c, Size: %d, Buffer: %s\n",
							pacote->Origem, pacote->Tipo, pacote->Size, pacote->Dados.Info);*/
					printf("[RecepcaoDadosUDP] Origem: %d, Tipo %d, Size: %d\n",
							pacote.Origem, pacote.Tipo, pacote.Size);
					novos_dados = 1;

			} else {
				//Senao, recebidos será igual a -1, entao houve um erro
				estado_socket = error;
				printf("[RecepcaoDadosUDP] Erro! Recebidos %d dados.\n", recebidos);
			}
			 //aguarde 1 segundo, envie D e volte a receber dados
			 OSTimeDlyHMSM(0,0,0,100);
	     break;
	     /*=============================================================================
		 Erro de execução
		 ==============================================================================*/
		 case error:
			 estado_socket = closing;

		 break;
		 /*=============================================================================
		 Fechando o socket
		 ==============================================================================*/
		 case closing:
			 close(fdSocketSender);
			 printf("[RecepcaoDadosUDP]Fechou socket!\n");
			 estado_socket = waiting;
	     break;
	     /*=============================================================================
		 Aguardando comando para iniciar o socket
		 ==============================================================================*/
		 case waiting:
		 			if(iniciar_socket){
		 				iniciar_socket = 0;
		 				estado_socket = starting;
		 			}
		 			else
		 				OSTimeDlyHMSM(0,0,1,0);
		 break;
		 /*============================================================================*/
		 default:
			estado_socket = closing;
		 break;
	 }

	 }
}




