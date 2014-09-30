/*
 * externs.h
 *
 *  Created on: 30/11/2011
 *      Author: Danilo
 */

#ifndef EXTERNS_H_
#define EXTERNS_H_

#include "DanWindow/DanWindow.h"
#include "includes.h"



extern void taskTimer(void* pdata);

extern int Executa();
extern alt_video_display *display;//Buffer de imagem do LCD
extern char novos_dados;
extern Pacote_t pacote;

//Sincronismo entre tarefas
extern OS_FLAG_GRP *EventoSocket;


//Telas
extern TScreen  Desktop;
extern TScreen Aquisicao;
extern TScreen TerminalSerial;
extern TGraph  grpTempo, grpFrequencia;

//Dados dos graficos
extern short	Tempo_Dados[256];
extern short    Frequencia_Dados[256];
extern short 	DadosFFT[256];


#endif /* EXTERNS_H_ */
