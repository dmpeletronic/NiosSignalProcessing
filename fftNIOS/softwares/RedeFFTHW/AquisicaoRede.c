/*
 * AquisicaoRede.c
 *
 *  Created on: 30/11/2011
 *      Author: Danilo
 */
#include "DanWindow/DanWindow.h"
#include "altera_avalon_performance_counter.h"
#include "math.h"
#include <float.h>  /* FLT_MAX */
#include "defines.h"
#include "types.h"
#include "externs.h"
#include "FFT/simpleDFT.h"
#include "AquisicaoRede.h"

/************TELA AQUISICAO DE DADOS**************************/
TScreen Aquisicao;
TBox 	boxMenuTitulo;
TButton btnFecharAquis;
TBox	boxBarraFerramentas;
TButton btnF1, btnF2, btnF3, btnF4;
TGraph  grpTempo, grpFrequencia;
TBox	boxBarraStatus;
TLabel	lblAquisicaoTitulo, lblStatus, lblIP, lblPorta, lblConex;
/*Lista de captions*/
char btnFecharAquis_Caption[5] = "X";
char btnF1_Caption[20] = "FFT SW";
char btnF2_Caption[20] = "DFT SW";
char btnF3_Caption[20] = "Filtro band";
char btnF4_Caption[20] = "Filtro high";
char grpTempo_Title[20] = "TEMPO";
char grpFrequencia_Title[20] = "FREQUENCIA";
char lblAquisicaoTitulo_Caption[100]="Sistema de aquisicao de dados sobre TCP/IP em tempo real";
char lblStatus_Caption[20] = "Status";
char lblIP_Caption[20] = "IP: 192.168.0.2";
char lblPorta_Caption[20] = "PORTA: 2011";
char lblConex_Caption[20] = "Desconectado";
//Ponteiros
TButton                *Aquisicao_Buttons[6];
TLabel                 *Aquisicao_Labels[6];
TBox                   *Aquisicao_Boxes[4];
TGraph				   *Aquisicao_Graphs[2];
short	Tempo_Dados[256];
short    Frequencia_Dados[256];
short 	DadosFFT[256];
/***********FIM DOS OBJETOS DA TELA DE AQUISICAO DE DADOS*****/

//Funções de usuário

void executaFFT(void){
			static COMPLEXO in_data[DATASIZE], out_data[DATASIZE];
		    grpTempo.DataSize = DATASIZE;
			copy_data_to_complex(grpTempo.Data, grpTempo.DataSize, in_data);
			//copy_complex_to_complex(in_data, grpTempo.DataSize, out_data);
			//CarregaTabw(grpTempo.DataSize);
			Reordem(in_data, grpTempo.DataSize);
			ColTuk(in_data, grpTempo.DataSize);
			copy_complex_to_data(in_data, grpTempo.DataSize, DadosFFT);
			grpFrequencia.Data = DadosFFT;
			grpFrequencia.DataSize = grpTempo.DataSize;
		    grpFrequencia.Data[0] = 0;
			DrawGraph(&grpFrequencia);
}


void AquisicaoRedeTask(void* pdata)
{
  CarregaTabw(DATASIZE);
  while (1)
  {
    //OSTimeDlyHMSM(0, 0, 0, 1);
    if(CurrentScreen == &Aquisicao){
        		if(novos_dados>=1){
        				novos_dados = 0;
        				grpTempo.Data = &pacote.Dados.Aquis;
        				grpTempo.DataSize = DATASIZE;
        				DrawGraph(&grpTempo);
        				executaFFT();
        			}
        	}
  }
}


//Eventos dos botões
void btnFiltroBand_Click(void){

	float p1, p2, p3, p4;
	p1 = p2 = M_PI;

	printf("\nBenchMarking Pow\n");
	PERF_RESET(PERFORMANCE_COUNTER_BASE);
	PERF_START_MEASURING(PERFORMANCE_COUNTER_BASE);
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 1);
		 p3 = p1*p2;
	PERF_END (PERFORMANCE_COUNTER_BASE, 1);
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 2);
		 p4 = pow(p1, 2);
	PERF_END (PERFORMANCE_COUNTER_BASE, 2);
	 PERF_STOP_MEASURING(PERFORMANCE_COUNTER_BASE);
	 printf("\nResult: %.20f", p3);
	 printf("\nResult: %.20f", p4);
	 perf_print_formatted_report((void *)PERFORMANCE_COUNTER_BASE,
								ALT_CPU_FREQ, 2,  "Calculo x*x", "Calculo pow");

	 printf("\nBenchMarking finished");

}

void btnFiltroHigh_Click(void){

}

void btnFFTSW_Press(void){

	    static COMPLEXO in_data[256], out_data[256];
	    grpTempo.DataSize = 256;
		printf("Entrou DFT\n");
		PERF_RESET(PERFORMANCE_COUNTER_BASE);
		PERF_START_MEASURING(PERFORMANCE_COUNTER_BASE);
	    PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 1);
			copy_data_to_complex(grpTempo.Data, grpTempo.DataSize, in_data);
		PERF_END (PERFORMANCE_COUNTER_BASE, 1);
		PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 2);
			copy_complex_to_complex(in_data, grpTempo.DataSize, out_data);
		PERF_END (PERFORMANCE_COUNTER_BASE, 2);
		PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 3);
			CarregaTabw(grpTempo.DataSize);
			//imprime(in_data, grpTempo.DataSize, "Dados de entrada");
		PERF_END (PERFORMANCE_COUNTER_BASE, 3);
		printf("\nCalculando FFT %d pontos", grpTempo.DataSize);
		PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 4);
			Reordem(out_data, grpTempo.DataSize);
			//FFT_Egon (out_data, grpTempo.DataSize);
		PERF_END (PERFORMANCE_COUNTER_BASE, 4);
		printf("\nCalculado.");
		PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 5);
			ColTuk(out_data, grpTempo.DataSize);
			//	imprime(out_data, grpTempo.DataSize, "Dados de saida");
		PERF_END (PERFORMANCE_COUNTER_BASE, 5);
		PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 6);
			copy_complex_to_data(out_data, grpTempo.DataSize, DadosFFT);
		PERF_END (PERFORMANCE_COUNTER_BASE, 6);


	    PERF_STOP_MEASURING(PERFORMANCE_COUNTER_BASE);
		perf_print_formatted_report((void *)PERFORMANCE_COUNTER_BASE,
									ALT_CPU_FREQ, 6,  "Copy to complex", "Cpx to Cpx", "Carrega W",
									"Reordem", "Cooley Tukey", "Copy to short");
		printf("Saiu DFT");
		grpFrequencia.Data = DadosFFT;
		grpFrequencia.DataSize = grpTempo.DataSize;
		DrawGraph(&grpFrequencia);
}

void btnFecharAquis_Click(void){
	DrawScreen(&Desktop);
}

void btnDFTSW_Down(void){
	static COMPLEXO in_data[256], out_data[256];
	static double sin_table[256][256];
	static double cos_table[256][256];

	printf("Entrou DFT\n");
	PERF_RESET(PERFORMANCE_COUNTER_BASE);
	PERF_START_MEASURING(PERFORMANCE_COUNTER_BASE);
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 1);
			init_sincos_table(sin_table, cos_table, grpTempo.DataSize);
	PERF_END (PERFORMANCE_COUNTER_BASE, 1);
	printf("iniciou tabela\n");
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 2);
		copy_data_to_complex(grpTempo.Data, grpTempo.DataSize, in_data);
	PERF_END (PERFORMANCE_COUNTER_BASE, 2);
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 3);
		//imprime(in_data, grpTempo.DataSize, "Dados de entrada");
	PERF_END (PERFORMANCE_COUNTER_BASE, 3);
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 4);
		dft(in_data, out_data, 0, grpTempo.DataSize);
	PERF_END (PERFORMANCE_COUNTER_BASE, 4);
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 5);
		dft_tabled(in_data, out_data, 0, grpTempo.DataSize, sin_table, cos_table);
	PERF_END (PERFORMANCE_COUNTER_BASE, 5);
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 6);
		//	imprime(out_data, grpTempo.DataSize, "Dados de saida");
	PERF_END (PERFORMANCE_COUNTER_BASE, 6);
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 7);
		copy_complex_to_data(out_data, grpTempo.DataSize, DadosFFT);
	PERF_END (PERFORMANCE_COUNTER_BASE, 7);


    PERF_STOP_MEASURING(PERFORMANCE_COUNTER_BASE);
	perf_print_formatted_report((void *)PERFORMANCE_COUNTER_BASE,
								ALT_CPU_FREQ, 7, "Init sin cos", "Copy to complex", "Imprime IN",
								"Calcula DFT", "Calc DFT Tabled" , "Imprime OUT",
								"Copy to integer");
	printf("Saiu DFT");
	grpFrequencia.Data = DadosFFT;
	grpFrequencia.DataSize = grpTempo.DataSize;
	DrawGraph(&grpFrequencia);
}

void InicializaObjetosAquisicao(void){
	  int order = 0;
	  Aquisicao.Color                     = 0x000000;
	  Aquisicao.Width                     = 800;
	  Aquisicao.Height                    = 480;
	  Aquisicao.ButtonsCount              = 5;
	  Aquisicao.Buttons                   = Aquisicao_Buttons;
	  Aquisicao.Buttons_RoundCount        = 0;
	  Aquisicao.LabelsCount               = 5;
	  Aquisicao.Labels                    = Aquisicao_Labels;
	  Aquisicao.ImagesCount               = 0;
	  Aquisicao.BoxesCount                = 3;
	  Aquisicao.Boxes                     = Aquisicao_Boxes;
	  Aquisicao.Boxes_RoundCount          = 0;
	  Aquisicao.LinesCount                = 0;
	  Aquisicao.GraphsCount				  = 2;
	  Aquisicao.Graphs 					  = Aquisicao_Graphs;
	  Aquisicao.ObjectsCount              = Aquisicao.ButtonsCount + Aquisicao.LabelsCount + Aquisicao.BoxesCount + Aquisicao.LinesCount +  Aquisicao.GraphsCount;//Total de objetos


	  //Determina quais serão o box da tela Aquisicao
	  Aquisicao_Boxes[0]                  = &boxMenuTitulo;
	  Aquisicao_Boxes[1]                  = &boxBarraFerramentas;
	  Aquisicao_Boxes[2]                  = &boxBarraStatus;
	  //Determina quais são os botoes da tela
	  Aquisicao_Buttons[0]                = &btnFecharAquis;
	  Aquisicao_Buttons[1]                = &btnF1;
	  Aquisicao_Buttons[2]                = &btnF2;
	  Aquisicao_Buttons[3]                = &btnF3;
	  Aquisicao_Buttons[4]                = &btnF4;
	  //Determina quais labels pertencem a esta tela
	  Aquisicao_Labels[0]                 = &lblStatus;
	  Aquisicao_Labels[1]                 = &lblIP;
	  Aquisicao_Labels[2]                 = &lblPorta;
	  Aquisicao_Labels[3]                 = &lblConex;
	  Aquisicao_Labels[4]                 = &lblAquisicaoTitulo;
	  //Determina quais são os graficos desta tela
	  Aquisicao_Graphs[0]				 = &grpTempo;
	  Aquisicao_Graphs[1]				 = &grpFrequencia;

	//Inicializa o box barra de titulo
	boxMenuTitulo.OwnerScreen     = &Aquisicao;
	boxMenuTitulo.Order           = order++;
	boxMenuTitulo.Left            = 0;
	boxMenuTitulo.Top             = 0;
	boxMenuTitulo.Width           = 801;
	boxMenuTitulo.Height          = 22;
	boxMenuTitulo.Pen_Width       = 0;
	boxMenuTitulo.Pen_Color       = BLACK_24;
	boxMenuTitulo.Visible         = 1;
	boxMenuTitulo.Active          = 0;
	boxMenuTitulo.Color           = 0x0000FF;
	boxMenuTitulo.PressColEnabled = 1;
	boxMenuTitulo.Press_Color     = GRAY_24;

	//Inicializa o box barra de ferramenas
	boxBarraFerramentas.OwnerScreen     = &Aquisicao;
	boxBarraFerramentas.Order           = order++;
	boxBarraFerramentas.Left            = 0;
	boxBarraFerramentas.Top             = 22;
	boxBarraFerramentas.Width           = 801;
	boxBarraFerramentas.Height          = 40;
	boxBarraFerramentas.Pen_Width       = 0;
	boxBarraFerramentas.Pen_Color       = BLACK_24;
	boxBarraFerramentas.Visible         = 1;
	boxBarraFerramentas.Active          = 0;
	boxBarraFerramentas.Color           = 0xF3F3F3;
	boxBarraFerramentas.PressColEnabled = 1;
	boxBarraFerramentas.Press_Color     = GRAY_24;

	//Inicializa o box barra de status
	boxBarraStatus.OwnerScreen     = &Aquisicao;
	boxBarraStatus.Order           = order++;
	boxBarraStatus.Left            = 0;
	boxBarraStatus.Top             = 458;
	boxBarraStatus.Width           = 801;
	boxBarraStatus.Height          = 22;
	boxBarraStatus.Pen_Width       = 1;
	boxBarraStatus.Pen_Color       = BLACK_24;
	boxBarraStatus.Visible         = 1;
	boxBarraStatus.Active          = 0;
	boxBarraStatus.Color           = 0xF3F3F3;
	boxBarraStatus.PressColEnabled = 1;
	boxBarraStatus.Press_Color     = GRAY_24;

	//Botao Fechar aquis
	btnFecharAquis.OwnerScreen     = &Aquisicao;
	btnFecharAquis.Order           = order++;
	btnFecharAquis.Left            = 780;
	btnFecharAquis.Top             = 2;
	btnFecharAquis.Width           = 18;
	btnFecharAquis.Height          = 18;
	btnFecharAquis.Pen_Width       = 1;
	btnFecharAquis.Pen_Color       = 0x0000;
	btnFecharAquis.Visible         = 1;
	btnFecharAquis.Active          = 1;
	btnFecharAquis.Transparent     = 1;
	btnFecharAquis.Caption         = btnFecharAquis_Caption;
	btnFecharAquis.FontName        = cour10_font;
	btnFecharAquis.Font_Color      = 0x000000;
	btnFecharAquis.Gradient        = 1;
	btnFecharAquis.Gradient_Orientation    = 0;
	btnFecharAquis.Gradient_Start_Color    = 0x0660;
	btnFecharAquis.Gradient_End_Color      = 0x0280;
	btnFecharAquis.Color           = 0x0000FF;
	btnFecharAquis.PressColEnabled = 1;
	btnFecharAquis.Press_Color     = 0x0000F0;
	btnFecharAquis.OnUpPtr        = 0;
	btnFecharAquis.OnDownPtr      = 0;
	btnFecharAquis.OnClickPtr     = btnFecharAquis_Click;
	btnFecharAquis.OnPressPtr     = 0;

	//Botao Funcao 1
	btnF1.OwnerScreen     = &Aquisicao;
	btnF1.Order           = order++;
	btnF1.Left            = 5;
	btnF1.Top             = 30;
	btnF1.Width           = 70;
	btnF1.Height          = 25;
	btnF1.Pen_Width       = 1;
	btnF1.Pen_Color       = 0x0000;
	btnF1.Visible         = 1;
	btnF1.Active          = 1;
	btnF1.Transparent     = 1;
	btnF1.Caption         = btnF1_Caption;
	btnF1.FontName        = cour10_font;
	btnF1.Font_Color      = BLACK_24;
	btnF1.Gradient        = 1;
	btnF1.Gradient_Orientation    = 0;
	btnF1.Gradient_Start_Color    = 0x0660;
	btnF1.Gradient_End_Color      = 0x0280;
	btnF1.Color           = 0xC0C0C0;
	btnF1.PressColEnabled = 1;
	btnF1.Press_Color     = WHITESMOKE_24;
	btnF1.OnUpPtr        = 0;
	btnF1.OnDownPtr      = 0;
	btnF1.OnClickPtr     = 0;
	btnF1.OnPressPtr     = btnFFTSW_Press;

	//Botao Funcao 2
	btnF2.OwnerScreen     = &Aquisicao;
	btnF2.Order           = order++;
	btnF2.Left            = 80;
	btnF2.Top             = 30;
	btnF2.Width           = 90;
	btnF2.Height          = 25;
	btnF2.Pen_Width       = 1;
	btnF2.Pen_Color       = 0x0000;
	btnF2.Visible         = 1;
	btnF2.Active          = 1;
	btnF2.Transparent     = 1;
	btnF2.Caption         = btnF2_Caption;
	btnF2.FontName        = cour10_font;
	btnF2.Font_Color      = BLACK_24;
	btnF2.Gradient        = 1;
	btnF2.Gradient_Orientation    = 0;
	btnF2.Gradient_Start_Color    = 0x0660;
	btnF2.Gradient_End_Color      = 0x0280;
	btnF2.Color           = 0xC0C0C0;
	btnF2.PressColEnabled = 1;
	btnF2.Press_Color     = WHITESMOKE_24;
	btnF2.OnUpPtr        = 0;
	btnF2.OnDownPtr      = btnDFTSW_Down;
	btnF2.OnClickPtr     = 0;
	btnF2.OnPressPtr     = 0;

	//Botao Funcao 3
	btnF3.OwnerScreen     = &Aquisicao;
	btnF3.Order           = order++;
	btnF3.Left            = 175;
	btnF3.Top             = 30;
	btnF3.Width           = 100;
	btnF3.Height          = 25;
	btnF3.Pen_Width       = 1;
	btnF3.Pen_Color       = 0x0000;
	btnF3.Visible         = 1;
	btnF3.Active          = 1;
	btnF3.Transparent     = 1;
	btnF3.Caption         = btnF3_Caption;
	btnF3.FontName        = cour10_font;
	btnF3.Font_Color      = BLACK_24;
	btnF3.Gradient        = 1;
	btnF3.Gradient_Orientation    = 0;
	btnF3.Gradient_Start_Color    = 0x0660;
	btnF3.Gradient_End_Color      = 0x0280;
	btnF3.Color           = 0xC0C0C0;
	btnF3.PressColEnabled = 1;
	btnF3.Press_Color     = WHITESMOKE_24;
	btnF3.OnUpPtr        = 0;
	btnF3.OnDownPtr      = btnFiltroBand_Click;
	btnF3.OnClickPtr     = 0;
	btnF3.OnPressPtr     = 0;

	//Botao Funcao 4
	btnF4.OwnerScreen     = &Aquisicao;
	btnF4.Order           = order++;
	btnF4.Left            = 280;
	btnF4.Top             = 30;
	btnF4.Width           = 100;
	btnF4.Height          = 25;
	btnF4.Pen_Width       = 1;
	btnF4.Pen_Color       = 0x0000;
	btnF4.Visible         = 1;
	btnF4.Active          = 1;
	btnF4.Transparent     = 1;
	btnF4.Caption         = btnF4_Caption;
	btnF4.FontName        = cour10_font;
	btnF4.Font_Color      = BLACK_24;
	btnF4.Gradient        = 1;
	btnF4.Gradient_Orientation    = 0;
	btnF4.Gradient_Start_Color    = 0x0660;
	btnF4.Gradient_End_Color      = 0x0280;
	btnF4.Color           = 0xC0C0C0;
	btnF4.PressColEnabled = 1;
	btnF4.Press_Color     = WHITESMOKE_24;
	btnF4.OnUpPtr        = 0;
	btnF4.OnDownPtr      = btnFiltroHigh_Click;
	btnF4.OnClickPtr     = 0;
	btnF4.OnPressPtr     = 0;

	//Label Status
	lblStatus.OwnerScreen     = &Aquisicao;
	lblStatus.Order           = order++;
	lblStatus.Left            = 10;
	lblStatus.Top             = 465;
	lblStatus.Width           = 80;
	lblStatus.Height          = 25;
	lblStatus.Visible         = 1;
	lblStatus.Active          = 1;
	lblStatus.Caption         = lblStatus_Caption;
	lblStatus.FontName        = cour10_font;
	lblStatus.Font_Color      = BLACK_24;

	//Label IP
	lblIP.OwnerScreen     = &Aquisicao;
	lblIP.Order           = order++;
	lblIP.Left            = 70;
	lblIP.Top             = 465;
	lblIP.Width           = 80;
	lblIP.Height          = 25;
	lblIP.Visible         = 1;
	lblIP.Active          = 1;
	lblIP.Caption         = lblIP_Caption;
	lblIP.FontName        = cour10_font;
	lblIP.Font_Color      = BLACK_24;

	//Label Porta
	lblPorta.OwnerScreen     = &Aquisicao;
	lblPorta.Order           = order++;
	lblPorta.Left            = 250;
	lblPorta.Top             = 465;
	lblPorta.Width           = 80;
	lblPorta.Height          = 25;
	lblPorta.Visible         = 1;
	lblPorta.Active          = 1;
	lblPorta.Caption         = lblPorta_Caption;
	lblPorta.FontName        = cour10_font;
	lblPorta.Font_Color      = BLACK_24;

	//Label Conex
	lblConex.OwnerScreen     = &Aquisicao;
	lblConex.Order           = order++;
	lblConex.Left            = 350;
	lblConex.Top             = 465;
	lblConex.Width           = 80;
	lblConex.Height          = 25;
	lblConex.Visible         = 1;
	lblConex.Active          = 1;
	lblConex.Caption         = lblConex_Caption;
	lblConex.FontName        = cour10_font;
	lblConex.Font_Color      = BLACK_24;

	//Label Titulo
	lblAquisicaoTitulo.OwnerScreen     = &Aquisicao;
	lblAquisicaoTitulo.Order           = order++;
	lblAquisicaoTitulo.Left            = 10;
	lblAquisicaoTitulo.Top             = 5;
	lblAquisicaoTitulo.Width           = 80;
	lblAquisicaoTitulo.Height          = 25;
	lblAquisicaoTitulo.Visible         = 1;
	lblAquisicaoTitulo.Active          = 1;
	lblAquisicaoTitulo.Caption         = lblAquisicaoTitulo_Caption;
	lblAquisicaoTitulo.FontName        = cour10_font;
	lblAquisicaoTitulo.Font_Color      = WHITE_24;

	//Inicialização dos dados do grafico
	grpTempo.Active = 1;
	grpTempo.BackColor = BLACK_24;
	grpTempo.BorderColor = WHITESMOKE_24;
	grpTempo.Data = Tempo_Dados;
	grpTempo.DataColor = RED_24;
	grpTempo.DataSize = 256;
	grpTempo.FontName = cour10_font;
	grpTempo.Graph_Name = grpTempo_Title;
	grpTempo.GridColor = 0x004000;
	grpTempo.Height = 200;
	grpTempo.Left = 0;
	grpTempo.Order = order++;
	grpTempo.ShowBorder = 0;
	grpTempo.ShowGrid = 1;
	grpTempo.Top = 62;
	grpTempo.Visible = 1;
	grpTempo.Width = 800;
	grpTempo.GraphType = PLOT;

	//Inicialização dos dados do grafico
	grpFrequencia.Active = 1;
	grpFrequencia.BackColor = BLACK_24;
	grpFrequencia.BorderColor = WHITESMOKE_24;
	grpFrequencia.Data = Frequencia_Dados;
	grpFrequencia.DataColor = BLUE_24;
	grpFrequencia.DataSize = DATASIZE;
	grpFrequencia.FontName = cour10_font;
	grpFrequencia.Graph_Name = grpFrequencia_Title;
	grpFrequencia.GridColor = 0x004000;
	grpFrequencia.Height = 200;
	grpFrequencia.Left = 0;
	grpFrequencia.Order = order++;
	grpFrequencia.ShowBorder = 0;
	grpFrequencia.ShowGrid = 1;
	grpFrequencia.Top = 62+200-1;
	grpFrequencia.Visible = 1;
	grpFrequencia.Width = 800;
	grpFrequencia.GraphType = STEM;
}
