#include "DanWindow/DanWindow.h"
#include "LCDTask.h"
#include "altera_avalon_performance_counter.h"
#include "types.h"
/*Inclusão das imagens codificadas em RGB*/
#include "logo.h"
#include "string.h"
#include "defines.h"
#include "externs.h"
#include "FFT/simpleDFT.h"
#include "TerminalSerial.h"
#include "AquisicaoRede.h"
#include "math.h"

//void draw_array(unsigned int *buffer, int x_size, int y_size,  alt_video_display* display, int x_offset,int y_offset, unsigned int transparent_color);

/*Objetos utilizados na applicacao*/

/****TELA DESKTOP*****/
TScreen  Desktop;
TImage   imgPlanoFundo;
TBox     boxMessageTitle;
TBox	 boxMessage;
TButton  btnMessage;
TLabel   lblMessageTitle;
TLabel   lblMessage;
TBox     boxBarraTarefas;
TBox     boxMenuItem0;
TBox     boxMenuItem1;
TBox     boxMenuItem2;
TBox     boxMenuItem3;
TBox	 boxFundoMenu;
TLabel   lblMenuItem0;
TLabel   lblMenuItem1;
TLabel   lblMenuItem2;
TLabel   lblMenuItem3;
TBox     boxBandeja;
TButton  btnIniciar;
TLabel   lblHora;
char btnIniciar_Caption[8] = "Iniciar";
char lblHora_Caption[11] = "00:00:00";
char lblMessage_Caption[40] = "Mensagem do sistema.";
char lblMessageTitle_Caption[15] = "System Message";
char lblMenuItem0_Caption[30] = "Sist. de aquis. de dados";
char lblMenuItem1_Caption[30] = "Proc. Imagem NIOS+VDHL";
char lblMenuItem2_Caption[30] = "Configuracoes de rede";
char lblMenuItem3_Caption[30] = "Terminal serial";
char mostraMenu = 0;
//Ponteiros
TButton                *Desktop_Buttons[2];
TLabel                 *Desktop_Labels[7];
TBox                   *Desktop_Boxes[8];
/*****FIM DOS OBJETOS DA TELA DESKTOP****************/



//Funções de usuário
void ShowMenu(void){
	mostraMenu = 1;
	boxMenuItem0.Visible = 1;
	boxMenuItem1.Visible = 1;
	boxMenuItem2.Visible = 1;
	boxMenuItem3.Visible = 1;
	boxMenuItem0.Active = 1;
	boxMenuItem1.Active = 1;
	boxMenuItem2.Active = 1;
	boxMenuItem3.Active = 1;
	lblMenuItem0.Visible = 1;
	lblMenuItem1.Visible = 1;
	lblMenuItem2.Visible = 1;
	lblMenuItem3.Visible = 1;
	DrawBox(&boxMenuItem0);
	DrawBox(&boxMenuItem1);
	DrawBox(&boxMenuItem2);
	DrawBox(&boxMenuItem3);
	DrawLabel(&lblMenuItem0);
	DrawLabel(&lblMenuItem1);
	DrawLabel(&lblMenuItem2);
	DrawLabel(&lblMenuItem3);

}
void HideMenu(char Limpa){
	mostraMenu = 0;
	boxMenuItem0.Visible = 0;
	boxMenuItem1.Visible = 0;
	boxMenuItem2.Visible = 0;
	boxMenuItem3.Visible = 0;
	boxMenuItem0.Active = 0;
	boxMenuItem1.Active = 0;
	boxMenuItem2.Active = 0;
	boxMenuItem3.Active = 0;
	lblMenuItem0.Visible = 0;
	lblMenuItem1.Visible = 0;
	lblMenuItem2.Visible = 0;
	lblMenuItem3.Visible = 0;
	if(Limpa)
	{
		boxFundoMenu.Visible = 1;
		DrawBox(&boxFundoMenu);
	}
}

void AtualizaTimer(void){
	static int s=0, m=0, h=0;

	sprintf(lblHora_Caption, "%02d:%02d:%02d",h,m,s);
	if(s++>=59){
		s=0;
		if(m++>=59){
			m=0;
			if(h++>=23){
				h=0;
			}
		}
	}
	if(CurrentScreen == &Desktop){
		DrawBox(&boxBandeja);
		DrawLabel(&lblHora);
		DrawScreen(&Desktop);
	}
}


//Eventos dos botões
void btnIniciar_Down(void){
	if(mostraMenu==0) ShowMenu();
	else HideMenu(1);
	DrawScreen(&Desktop);
}


void boxMenuItem0_Click(void){
	HideMenu(1);
	DrawScreen(&Aquisicao);

}


void boxMenuItem1_Click(void){
	extern char iniciar_socket;

	iniciar_socket = 1;
	printf("[LCD Task] item de menu 1 pressed");
	HideMenu(1);
	DrawScreen(&Desktop);
}

void boxMenuItem2_Click(void){

	HideMenu(1);

	int i,j,k, n;
	COMPLEXO dado[DATASIZE], out[DATASIZE];

	n = DATASIZE;

	for(i=0; i<n; i++){
			 dado[i].imag = 0.0;
			 dado[i].real = i<(n/2)? 1.0 : 0.0;
			//dado[i].real = sin(2*M_PI*i/(n/8));
	}

	imprime(&dado, n, "Dados Originais");
	dft(dado, out, 0, n);
	imprime(&out, n, "Dados Processados");

}
void boxMenuItem3_Click(void){
	HideMenu(1);
    DrawScreen(&TerminalSerial);
}
void boxBarraTarefas_Click(void){
	HideMenu(1);
	DrawScreen(&Desktop);
}
void boxBandeja_Click(void){
	HideMenu(1);
	DrawScreen(&Desktop);
}



/*TAREFAS*/

void LCDTask (void *task_data)
{
	int i;
	float dt=0.01, t=0.0, T = 0.0, F=1;
	float A = 90.0;

   printf("\nInicializando TFT e tela inicial...");
	Initialize_TFT();
    InitializeTouchPanel();
	printf("\nExibindo imagem inicial...");
	//Mostra logo da Unicamp
	printf("\nLogo Unicamp\n");
	draw_array((unsigned int *)logo, largura_logo, altura_logo, display, (WIDTH-largura_logo)/2,(HEIGHT-altura_logo)/2, SPLASH_BG_MASK);
	vid_print_string(200, 20, BLACK_24, cour10_font, display, "Inicializando sistema de aquisicao de dados..." );
	vid_print_string(200, 40, BLACK_24, cour10_font, display, "Inicializando sistema de plotagem..." );
	vid_print_string(200, 420, BLACK_24, cour10_font, display, "Desenvolvido por Danilo Pagano sob a orientacao do");
	vid_print_string(200, 440, BLACK_24, cour10_font, display, "Prof. Dr. Euripedes Guilherme de Oliveira Nobrega.");
	alt_video_display_register_written_buffer(display);
    alt_video_display_buffer_is_available( display );
	//Inicialize os dados
	F = 4;
	T = 1/F;
	dt= T/DATASIZE;
	t = 0.0;
	for(i=0; i< DATASIZE; i++){
		Tempo_Dados[i] = 0;//(short)(sin(2*M_PI*t*F/T)*A);//+(char)(sin(2*pi*(F/2)*t)*A/2);
		Frequencia_Dados[i] = 0;
		t = t+dt;
	}

	OSTimeDlyHMSM(0,0,2,0);
    printf("Limpou tela\n\r");
    InicializaObjetosDesktop();
    InicializaObjetosAquisicao();
    InicializaObjetosTerminalSerial();
   // DrawScreen(&Desktop);
    DrawScreen(&Aquisicao);
    printf("Passou no drawscreen.\n\r");
    OSTimeDlyHMSM(0,0,3,0);
    while(1){
    	Check_TP();
    	OSTimeDlyHMSM(0,0,0,30);

  	}


}

void taskTimer(void* pdata)
{
  while (1)
  {
    AtualizaTimer();
    OSTimeDlyHMSM(0, 0, 1, 0);
  }
}


//Inicialização dos objetos de cada tela
void InicializaObjetosDesktop(void){
	int order = 0;

	  Desktop.Color                     = 0x000077;
	  Desktop.Width                     = 800;
	  Desktop.Height                    = 480;
	  Desktop.ButtonsCount              = 1;
	  Desktop.Buttons                   = Desktop_Buttons;
	  Desktop.Buttons_RoundCount        = 0;
	  Desktop.LabelsCount               = 5;
	  Desktop.Labels                    = Desktop_Labels;
	  Desktop.ImagesCount               = 0;
	  Desktop.BoxesCount                = 7;
	  Desktop.Boxes                     = Desktop_Boxes;
	  Desktop.Boxes_RoundCount          = 0;
	  Desktop.LinesCount                = 0;
	  Desktop.ObjectsCount              = Desktop.ButtonsCount + Desktop.LabelsCount + Desktop.BoxesCount + Desktop.LinesCount ;//Total de objetos
	  //Determina quais serão o box da tela DESKTOP
	  Desktop_Boxes[0]                  = &boxBarraTarefas;
	  Desktop_Boxes[1]                  = &boxBandeja;
	  Desktop_Boxes[2]                  = &boxMenuItem0;
	  Desktop_Boxes[3]                  = &boxMenuItem1;
	  Desktop_Boxes[4]                  = &boxMenuItem2;
	  Desktop_Boxes[5]                  = &boxMenuItem3;
	  Desktop_Boxes[6]                  = &boxFundoMenu;
	  Desktop_Boxes[7]                  = &boxMessageTitle;
	  //Determina quais são os botoes da tela
	  Desktop_Buttons[0]                = &btnIniciar;
	  Desktop_Buttons[1]                = &btnMessage;
	  //Determina quais labels pertencem a esta tela
	  Desktop_Labels[0]                 = &lblHora;
	  Desktop_Labels[1]                 = &lblMenuItem0;
	  Desktop_Labels[2]                 = &lblMenuItem1;
	  Desktop_Labels[3]                 = &lblMenuItem2;
	  Desktop_Labels[4]                 = &lblMenuItem3;

	  //Inicializa o box barra de tarefas
	  boxBarraTarefas.OwnerScreen     = &Desktop;
	  boxBarraTarefas.Order           = order++;
	  boxBarraTarefas.Left            = 0;
	  boxBarraTarefas.Top             = 440;
	  boxBarraTarefas.Width           = 801;
	  boxBarraTarefas.Height          = 40;
	  boxBarraTarefas.Pen_Width       = 1;
	  boxBarraTarefas.Pen_Color       = BLACK_24;
	  boxBarraTarefas.Visible         = 1;
	  boxBarraTarefas.Active          = 0;
	  boxBarraTarefas.Transparent     = 1;
	  boxBarraTarefas.Gradient        = 1;
	  boxBarraTarefas.Gradient_Orientation    = 0;
	  boxBarraTarefas.Gradient_Start_Color    = 0x8410;
	  boxBarraTarefas.Gradient_End_Color      = 0x0000;
	  boxBarraTarefas.Color           = 0xF3F3F3;
	  boxBarraTarefas.PressColEnabled = 0;
	  boxBarraTarefas.Press_Color     = GRAY_24;
	  boxBarraTarefas.OnUpPtr        = 0;
	  boxBarraTarefas.OnDownPtr      = 0;
	  boxBarraTarefas.OnClickPtr     = boxBarraTarefas_Click;
	  boxBarraTarefas.OnPressPtr     = 0;

	  //Inicializa o box bandeja
	  boxBandeja.OwnerScreen     = &Desktop;
	   boxBandeja.Order           = order++;
	   boxBandeja.Left            = 720;
	   boxBandeja.Top             = 458;
	   boxBandeja.Width           = 77;
	   boxBandeja.Height          = 20;
	   boxBandeja.Pen_Width       = 1;
	   boxBandeja.Pen_Color       = 0x0000;
	   boxBandeja.Visible         = 1;
	   boxBandeja.Active          = 0;
	   boxBandeja.Transparent     = 1;
	   boxBandeja.Gradient        = 1;
	   boxBandeja.Gradient_Orientation    = 0;
	   boxBandeja.Gradient_Start_Color    = 0x8410;
	   boxBandeja.Gradient_End_Color      = 0x0000;
	   boxBandeja.Color           = 0xFAFAFA;
	   boxBandeja.PressColEnabled = 0;
	   boxBandeja.Press_Color     = GRAY_24;
	   boxBandeja.OnUpPtr        = 0;
	   boxBandeja.OnDownPtr      = 0;
	   boxBandeja.OnClickPtr     = boxBandeja_Click;
	   boxBandeja.OnPressPtr     = 0;

	   //Inicializa o box item de menu 0: 20x200
		boxMenuItem0.OwnerScreen     = &Desktop;
		boxMenuItem0.Order           = order++;
		boxMenuItem0.Left            = 1;
		boxMenuItem0.Top             = 400;
		boxMenuItem0.Width           = 300;
		boxMenuItem0.Height          = 40;
		boxMenuItem0.Pen_Width       = 0;
		boxMenuItem0.Pen_Color       = BLACK_24;
		boxMenuItem0.Visible         = 0;
		boxMenuItem0.Active          = 0;
		boxMenuItem0.Transparent     = 1;
		boxMenuItem0.Gradient        = 1;
		boxMenuItem0.Gradient_Orientation    = 0;
		boxMenuItem0.Gradient_Start_Color    = 0x8410;
		boxMenuItem0.Gradient_End_Color      = 0x0000;
		boxMenuItem0.Color           = 0xF3F3F3;
		boxMenuItem0.PressColEnabled = 0;
		boxMenuItem0.Press_Color     = GRAY_24;
		boxMenuItem0.OnUpPtr        = 0;
		boxMenuItem0.OnDownPtr      = 0;
		boxMenuItem0.OnClickPtr     = boxMenuItem0_Click;
		boxMenuItem0.OnPressPtr     = 0;

		//Inicializa o box item de menu 1: 20x200
		boxMenuItem1.OwnerScreen     = &Desktop;
		boxMenuItem1.Order           = order++;
		boxMenuItem1.Left            = 1;
		boxMenuItem1.Top             = 360;
		boxMenuItem1.Width           = 300;
		boxMenuItem1.Height          = 40;
		boxMenuItem1.Pen_Width       = 0;
		boxMenuItem1.Pen_Color       = BLACK_24;
		boxMenuItem1.Visible         = 0;
		boxMenuItem1.Active          = 0;
		boxMenuItem1.Transparent     = 1;
		boxMenuItem1.Gradient        = 1;
		boxMenuItem1.Gradient_Orientation    = 0;
		boxMenuItem1.Gradient_Start_Color    = 0x8410;
		boxMenuItem1.Gradient_End_Color      = 0x0000;
		boxMenuItem1.Color           = 0xF3F3F3;
		boxMenuItem1.PressColEnabled = 0;
		boxMenuItem1.Press_Color     = GRAY_24;
		boxMenuItem1.OnUpPtr        = 0;
		boxMenuItem1.OnDownPtr      = 0;
		boxMenuItem1.OnClickPtr     = boxMenuItem1_Click;
		boxMenuItem1.OnPressPtr     = 0;

		//Inicializa o box item de menu 2: 20x200
		boxMenuItem2.OwnerScreen     = &Desktop;
		boxMenuItem2.Order           = order++;
		boxMenuItem2.Left            = 1;
		boxMenuItem2.Top             = 320;
		boxMenuItem2.Width           = 300;
		boxMenuItem2.Height          = 40;
		boxMenuItem2.Pen_Width       = 0;
		boxMenuItem2.Pen_Color       = BLACK_24;
		boxMenuItem2.Visible         = 0;
		boxMenuItem2.Active          = 0;
		boxMenuItem2.Transparent     = 1;
		boxMenuItem2.Gradient        = 1;
		boxMenuItem2.Gradient_Orientation    = 0;
		boxMenuItem2.Gradient_Start_Color    = 0x8410;
		boxMenuItem2.Gradient_End_Color      = 0x0000;
		boxMenuItem2.Color           = 0xF3F3F3;
		boxMenuItem2.PressColEnabled = 0;
		boxMenuItem2.Press_Color     = GRAY_24;
		boxMenuItem2.OnUpPtr        = 0;
		boxMenuItem2.OnDownPtr      = 0;
		boxMenuItem2.OnClickPtr     = boxMenuItem2_Click;
		boxMenuItem2.OnPressPtr     = 0;

		//Inicializa o box item de menu 3: 20x200
		boxMenuItem3.OwnerScreen     = &Desktop;
		boxMenuItem3.Order           = order++;
		boxMenuItem3.Left            = 1;
		boxMenuItem3.Top             = 280;
		boxMenuItem3.Width           = 300;
		boxMenuItem3.Height          = 40;
		boxMenuItem3.Pen_Width       = 0;
		boxMenuItem3.Pen_Color       = BLACK_24;
		boxMenuItem3.Visible         = 0;
		boxMenuItem3.Active          = 0;
		boxMenuItem3.Transparent     = 1;
		boxMenuItem3.Gradient        = 1;
		boxMenuItem3.Gradient_Orientation    = 0;
		boxMenuItem3.Gradient_Start_Color    = 0x8410;
		boxMenuItem3.Gradient_End_Color      = 0x0000;
		boxMenuItem3.Color           = 0xF3F3F3;
		boxMenuItem3.PressColEnabled = 0;
		boxMenuItem3.Press_Color     = GRAY_24;
		boxMenuItem3.OnUpPtr        = 0;
		boxMenuItem3.OnDownPtr      = 0;
		boxMenuItem3.OnClickPtr     = boxMenuItem3_Click;
		boxMenuItem3.OnPressPtr     = 0;

		//Inicializa o box item de menu 3: 20x200
		boxFundoMenu.OwnerScreen     = &Desktop;
		boxFundoMenu.Order           = order++;
		boxFundoMenu.Left            = 1;
		boxFundoMenu.Top             = 280;
		boxFundoMenu.Width           = 300;
		boxFundoMenu.Height          = 160;
		boxFundoMenu.Pen_Width       = 0;
		boxFundoMenu.Pen_Color       = BLACK_24;
		boxFundoMenu.Visible         = 0;
		boxFundoMenu.Active          = 0;
		boxFundoMenu.Transparent     = 1;
		boxFundoMenu.Gradient        = 1;
		boxFundoMenu.Gradient_Orientation    = 0;
		boxFundoMenu.Gradient_Start_Color    = 0x8410;
		boxFundoMenu.Gradient_End_Color      = 0x0000;
		boxFundoMenu.Color           = Desktop.Color;
		boxFundoMenu.PressColEnabled = 0;
		boxFundoMenu.Press_Color     = GRAY_24;
		boxFundoMenu.OnUpPtr        = 0;
		boxFundoMenu.OnDownPtr      = 0;
		boxFundoMenu.OnClickPtr     = 0;
		boxFundoMenu.OnPressPtr     = 0;

	   //Botao iniciar
	   btnIniciar.OwnerScreen     = &Desktop;
	   btnIniciar.Order           = order++;
	   btnIniciar.Left            = 0;
	   btnIniciar.Top             = 440;
	   btnIniciar.Width           = 80;
	   btnIniciar.Height          = 40;
	   btnIniciar.Pen_Width       = 1;
	   btnIniciar.Pen_Color       = 0x0000;
	   btnIniciar.Visible         = 1;
	   btnIniciar.Active          = 1;
	   btnIniciar.Transparent     = 1;
	   btnIniciar.Caption         = btnIniciar_Caption;
	   btnIniciar.FontName        = cour10_font;
	   btnIniciar.Font_Color      = WHITE_24;
	   btnIniciar.Gradient        = 1;
	   btnIniciar.Gradient_Orientation    = 0;
	   btnIniciar.Gradient_Start_Color    = 0x0660;
	   btnIniciar.Gradient_End_Color      = 0x0280;
	   btnIniciar.Color           = 0x00F000;
	   btnIniciar.PressColEnabled = 1;
	   btnIniciar.Press_Color     = 0x008000;
	   btnIniciar.OnUpPtr        = 0;
	   btnIniciar.OnDownPtr      = btnIniciar_Down;
	   btnIniciar.OnClickPtr     = 0;
	   btnIniciar.OnPressPtr     = 0;

	   //Label Horas
	   lblHora.OwnerScreen     = &Desktop;
	   lblHora.Order           = order++;
	   lblHora.Left            = 725;
	   lblHora.Top             = 463;
	   lblHora.Width           = 80;
	   lblHora.Height          = 25;
	   lblHora.Visible         = 1;
	   lblHora.Active          = 1;
	   lblHora.Caption         = lblHora_Caption;
	   lblHora.FontName        = cour10_font;
	   lblHora.Font_Color      = BLACK_24;
	   lblHora.OnUpPtr        = 0;
	   lblHora.OnDownPtr      = 0;
	   lblHora.OnClickPtr     = 0;
	   lblHora.OnPressPtr     = 0;

		//Label item de menu 0
		lblMenuItem0.OwnerScreen     = &Desktop;
		lblMenuItem0.Order           = order++;
		lblMenuItem0.Left            = 40;
		lblMenuItem0.Top             = 420;
		lblMenuItem0.Width           = 80;
		lblMenuItem0.Height          = 25;
		lblMenuItem0.Visible         = 0;
		lblMenuItem0.Active          = 1;
		lblMenuItem0.Caption         = lblMenuItem0_Caption;
		lblMenuItem0.FontName        = cour10_font;
		lblMenuItem0.Font_Color      = BLACK_24;

		//Label Horas
		lblMenuItem1.OwnerScreen     = &Desktop;
		lblMenuItem1.Order           = order++;
		lblMenuItem1.Left            = 40;
		lblMenuItem1.Top             = 380;
		lblMenuItem1.Width           = 80;
		lblMenuItem1.Height          = 25;
		lblMenuItem1.Visible         = 0;
		lblMenuItem1.Active          = 1;
		lblMenuItem1.Caption         = lblMenuItem1_Caption;
		lblMenuItem1.FontName        = cour10_font;
		lblMenuItem1.Font_Color      = BLACK_24;

		//Label Horas
		lblMenuItem2.OwnerScreen     = &Desktop;
		lblMenuItem2.Order           = order++;
		lblMenuItem2.Left            = 40;
		lblMenuItem2.Top             = 340;
		lblMenuItem2.Width           = 80;
		lblMenuItem2.Height          = 25;
		lblMenuItem2.Visible         = 0;
		lblMenuItem2.Active          = 1;
		lblMenuItem2.Caption         = lblMenuItem2_Caption;
		lblMenuItem2.FontName        = cour10_font;
		lblMenuItem2.Font_Color      = BLACK_24;

		//Label Horas
		lblMenuItem3.OwnerScreen     = &Desktop;
		lblMenuItem3.Order           = order++;
		lblMenuItem3.Left            = 40;
		lblMenuItem3.Top             = 300;
		lblMenuItem3.Width           = 80;
		lblMenuItem3.Height          = 25;
		lblMenuItem3.Visible         = 0;
		lblMenuItem3.Active          = 1;
		lblMenuItem3.Caption         = lblMenuItem3_Caption;
		lblMenuItem3.FontName        = cour10_font;
		lblMenuItem3.Font_Color      = BLACK_24;
}

