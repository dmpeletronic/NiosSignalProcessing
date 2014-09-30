/*
 * defines.h
 *
 *  Created on: 30/11/2011
 *      Author: Danilo
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define IP4_ADDR(ipaddr, a,b,c,d) ipaddr = \
    htonl((((alt_u32)(a & 0xff) << 24) | ((alt_u32)(b & 0xff) << 16) | \
          ((alt_u32)(c & 0xff) << 8) | (alt_u32)(d & 0xff)))

//Prioridade das tarefas existentes
#define SOCKET_RECEIVER_PRIORITY 11
#define SOCKET_SENDER_PRIORITY 12
#define SOCKET_RESULT_SENDER_PRIORITY 13
#define TASK_TIMER_PRIORITY      14
#define LCD_TASK_PRIORITY      15
#define AQUISICAO_TASK_PRIORITY 16
#define   TASK_STACKSIZE       2048
#define   TASKAQUIS_STACKSIZE       1024
#define   TASKTIMER_STACKSIZE       512
#define TAMANHOBUFFER 4000

//Definições Matemáticas
#define PI2 6.2832

#endif /* DEFINES_H_ */
