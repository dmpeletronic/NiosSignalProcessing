/*Inclusão das bibliotecas padroes */
#include <stdio.h>
#include <string.h>
//#include <ctype.h>

/* MicroC/OS-II definitions */
#include "includes.h"
#include "system.h"



void LCDTask(void *task_data);
void boxMenuItem0_Click(void);
void boxMenuItem1_Click(void);
void boxMenuItem2_Click(void);
void boxMenuItem3_Click(void);
void boxBarraTarefas_Click(void);
void boxBandeja_Click(void);
void btnIniciar_Down(void);
void InicializaObjetosDesktop(void);
void AtualizaTimer(void);
void taskTimer(void* pdata);



