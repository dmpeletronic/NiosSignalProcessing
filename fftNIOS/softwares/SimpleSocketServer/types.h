/*
 * types.h
 *
 *  Created on: 21/11/2011
 *      Author: Danilo
 */

#ifndef TYPES_H_
#define TYPES_H_

//Estados da Recepção
typedef enum{
  starting = 0,
  listening,
  accepting,
  selecting,
  sending,
  sending_graph,
  receiving,
  processing,
  error,
  closing,
  waiting,
  stopped,
  size_stt_socket
}stt_socket;



//Pacotes que podem ser recebidos da rede
typedef union{
	short Aquis[2000];
	char Info[4000];
}Dados_t;

typedef struct{
	char Origem; //Id da origem dos dados: 0 = PC, 1 = TOWER1, 2 = TOWER2
	char Tipo; //Tipo de dados: 0 = Dados de aquisição, 1 = Informações em strings
	short Size; //Quantidade de dados de aquisição
	Dados_t Dados;//Dados do pacote
}Pacote_t;

#endif /* TYPES_H_ */
