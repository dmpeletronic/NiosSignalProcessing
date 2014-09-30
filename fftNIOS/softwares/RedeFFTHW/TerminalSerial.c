/*
 * TerminalSerial.c
 *
 *  Created on: 30/11/2011
 *      Author: Danilo
 */
#include "DanWindow/DanWindow.h"
#include "TerminalSerial.h"
#include "defines.h"
#include "types.h"
#include "externs.h"

/***********TELA TERMINAL SERIAL*****************************/
TScreen TerminalSerial;
TBox 	boxTituloTermSerial;
TButton btnFecharTermSerial;
TBox 	boxPainelTermSerial;
TLabel  lblLinha1TermSerial, lblTerminalSerialTitulo;
char lblLinha1TermSerial_Caption[80] = "NIOS> ";
char btnFecharTermSerial_Caption[5] = "X";
char lblTerminalSerialTitulo_Caption[100]="TERMINAL SERIAL NIOS";
//Ponteiros
TButton                *TerminalSerial_Buttons[1];
TLabel                 *TerminalSerial_Labels[2];
TBox                   *TerminalSerial_Boxes[2];
/***********FIM DOS OBJETOS DA TELA TERMINAL SERIAL**********/

//Funções de usuário


//Evento dos botões
void btnFecharTerminalSerial_Click(void){
	DrawScreen(&Desktop);
}


void InicializaObjetosTerminalSerial(void){
	int order = 0;
		  TerminalSerial.Color                     = 0x000000;
		  TerminalSerial.Width                     = 800;
		  TerminalSerial.Height                    = 480;
		  TerminalSerial.ButtonsCount              = 1;
		  TerminalSerial.Buttons                   = TerminalSerial_Buttons;
		  TerminalSerial.Buttons_RoundCount        = 0;
		  TerminalSerial.LabelsCount               = 2;
		  TerminalSerial.Labels                    = TerminalSerial_Labels;
		  TerminalSerial.ImagesCount               = 0;
		  TerminalSerial.BoxesCount                = 2;
		  TerminalSerial.Boxes                     = TerminalSerial_Boxes;
		  TerminalSerial.Boxes_RoundCount          = 0;
		  TerminalSerial.LinesCount                = 0;
		  TerminalSerial.GraphsCount			   = 0;
		  TerminalSerial.ObjectsCount              = TerminalSerial.ButtonsCount + TerminalSerial.LabelsCount + TerminalSerial.BoxesCount + TerminalSerial.LinesCount +  TerminalSerial.GraphsCount;//Total de objetos

		  //Determina quais serão o box da tela TerminalSerial
		  TerminalSerial_Boxes[0]                  = &boxTituloTermSerial;
		  TerminalSerial_Boxes[1]                  = &boxPainelTermSerial;

		  //Determina quais são os botoes da tela
		  TerminalSerial_Buttons[0]                = &btnFecharTermSerial;

		  //Determina quais labels pertencem a esta tela
		  TerminalSerial_Labels[0]                 = &lblTerminalSerialTitulo;
		  TerminalSerial_Labels[1]                 = &lblLinha1TermSerial;

		  //Inicializa o box barra de titulo
		  	boxTituloTermSerial.OwnerScreen     = &TerminalSerial;
		  	boxTituloTermSerial.Order           = order++;
		  	boxTituloTermSerial.Left            = 0;
		  	boxTituloTermSerial.Top             = 0;
		  	boxTituloTermSerial.Width           = 801;
		  	boxTituloTermSerial.Height          = 22;
		  	boxTituloTermSerial.Pen_Width       = 0;
		  	boxTituloTermSerial.Pen_Color       = BLACK_24;
		  	boxTituloTermSerial.Visible         = 1;
		  	boxTituloTermSerial.Active          = 0;
		  	boxTituloTermSerial.Color           = 0x0000FF;
		  	boxTituloTermSerial.PressColEnabled = 1;
		  	boxTituloTermSerial.Press_Color     = GRAY_24;

		  	//Inicializa o box barra de titulo
			boxPainelTermSerial.OwnerScreen     = &TerminalSerial;
			boxPainelTermSerial.Order           = order++;
			boxPainelTermSerial.Left            = 0;
			boxPainelTermSerial.Top             = 23;
			boxPainelTermSerial.Width           = 801;
			boxPainelTermSerial.Height          = 457;
			boxPainelTermSerial.Pen_Width       = 0;
			boxPainelTermSerial.Pen_Color       = BLACK_24;
			boxPainelTermSerial.Visible         = 1;
			boxPainelTermSerial.Active          = 0;
			boxPainelTermSerial.Color           = 0x000000;
			boxPainelTermSerial.PressColEnabled = 1;
			boxPainelTermSerial.Press_Color     = GRAY_24;

			//Botao Fechar aquis
			btnFecharTermSerial.OwnerScreen     = &TerminalSerial;
			btnFecharTermSerial.Order           = order++;
			btnFecharTermSerial.Left            = 780;
			btnFecharTermSerial.Top             = 2;
			btnFecharTermSerial.Width           = 18;
			btnFecharTermSerial.Height          = 18;
			btnFecharTermSerial.Pen_Width       = 1;
			btnFecharTermSerial.Pen_Color       = 0x0000;
			btnFecharTermSerial.Visible         = 1;
			btnFecharTermSerial.Active          = 1;
			btnFecharTermSerial.Transparent     = 1;
			btnFecharTermSerial.Caption         = btnFecharTermSerial_Caption;
			btnFecharTermSerial.FontName        = cour10_font;
			btnFecharTermSerial.Font_Color      = 0x000000;
			btnFecharTermSerial.Gradient        = 1;
			btnFecharTermSerial.Gradient_Orientation    = 0;
			btnFecharTermSerial.Gradient_End_Color      = 0x0280;
			btnFecharTermSerial.Color           = 0x0000FF;
			btnFecharTermSerial.PressColEnabled = 1;
			btnFecharTermSerial.Press_Color     = 0x0000F0;
			btnFecharTermSerial.OnUpPtr        = 0;
			btnFecharTermSerial.OnDownPtr      = 0;
			btnFecharTermSerial.OnClickPtr     = btnFecharTerminalSerial_Click;
			btnFecharTermSerial.OnPressPtr     = 0;

			//Label Titulo
			lblTerminalSerialTitulo.OwnerScreen     = &TerminalSerial;
			lblTerminalSerialTitulo.Order           = order++;
			lblTerminalSerialTitulo.Left            = 10;
			lblTerminalSerialTitulo.Top             = 5;
			lblTerminalSerialTitulo.Width           = 80;
			lblTerminalSerialTitulo.Height          = 25;
			lblTerminalSerialTitulo.Visible         = 1;
			lblTerminalSerialTitulo.Active          = 1;
			lblTerminalSerialTitulo.Caption         = lblTerminalSerialTitulo_Caption;
			lblTerminalSerialTitulo.FontName        = cour10_font;
			lblTerminalSerialTitulo.Font_Color      = WHITE_24;

			//Label Linha 1
			lblLinha1TermSerial.OwnerScreen     = &TerminalSerial;
			lblLinha1TermSerial.Order           = order++;
			lblLinha1TermSerial.Left            = 5;
			lblLinha1TermSerial.Top         = 35;
			lblLinha1TermSerial.Width           = 100;
			lblLinha1TermSerial.Height          = 25;
			lblLinha1TermSerial.Visible         = 1;
			lblLinha1TermSerial.Active          = 1;
			lblLinha1TermSerial.Caption         = lblLinha1TermSerial_Caption;
			lblLinha1TermSerial.FontName        = cour10_font;
			lblLinha1TermSerial.Font_Color      = WHITE_24;
}
