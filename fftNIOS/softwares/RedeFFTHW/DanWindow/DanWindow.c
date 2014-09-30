/*
 * DanWindow.c
 *
 *  Created on: 03/10/2011
 *      Author: Danilo
 */
/* MicroC/OS-II definitions */
#include "includes.h"
#include "system.h"
#include "DanWindow.h"

// Variáveis globais
TScreen *CurrentScreen;
unsigned int Xcoord, Ycoord;
char PenDown=0;
int pen_is_down;
void *PressedObject;
int PressedObjectType;
unsigned int caption_length, caption_height;
unsigned int display_width=800, display_height=600;
alt_touchscreen touchscreen; //Touch
alt_tpo_lcd lcd; //Controle do LCD
alt_video_display *display;//Buffer de imagem do LCD

/*Busca o maior valor int16 em um vetor de tamanho size*/
short BuscaMaior(short * vet, int size){
	short maior = 0x8000;//menor inteiro de 16 bits possivel
	while (size-- > 0){
		if(*vet >= maior) maior = *vet;
		vet++;
	}
	return maior;
}

void InitializeTouchPanel(void) {
	//Inicializa o touchscreen
	 /* alt_touchscreen_init ( &touchscreen,
							 TOUCH_PANEL_SPI_BASE,
							 TOUCH_PANEL_SPI_IRQ,
							 TOUCH_PANEL_PEN_IRQ_N_BASE,
							 60,    // 60 samples/sec
							 ALT_TOUCHSCREEN_SWAP_XY);
	  // Calibrate the touch panel
	  alt_touchscreen_calibrate_upper_right (&touchscreen,
			   3946,   3849,    // ADC readings
				799,      0  ); // pixel coords
	  alt_touchscreen_calibrate_lower_left  (&touchscreen,
			   132,    148,     // ADC readings
				 0,    479  );  // pixel coords
*/
	PenDown = 0;
	PressedObject = 0;
	PressedObjectType = -1;
	printf("Touch screen inicializado.\n\r");
}

char IsInsideObject (unsigned int X, unsigned int Y, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height) { // static
  if ( (Left<= X) && (Left+ Width - 1 >= X) &&
       (Top <= Y)  && (Top + Height - 1 >= Y) )
    return 1;
  else
    return 0;
}

void ClearScreen(int color)
{
	vid_draw_box(0, 0, 800, 480, color, 1, display);
}

void Redraw(alt_video_display * display){
	alt_video_display_register_written_buffer(display);
	while(alt_video_display_buffer_is_available( display ) != 0){};
}

void DrawGraph(TGraph *AGraph){
	int i, pos;
	int n, step;
	int y, y2, cor;
	int d,d2;
	int meio;
	short maxValue;
	int gx; //desenha o grid
	n = AGraph->Width; //largura do grafico, ou seja, tamnho da tela

	if(AGraph->Visible==1){

		vid_draw_box(AGraph->Left, AGraph->Top, AGraph->Left+AGraph->Width, AGraph->Top+AGraph->Height, bgr2rgb(AGraph->BackColor), 1, display);
		if(AGraph->ShowGrid){
	    	//Desenha o grid
				//linhas horizontais
				for(gx=AGraph->Top; gx<(AGraph->Top + AGraph->Height); gx+=20){
				   vid_draw_line(AGraph->Left, gx, AGraph->Left+AGraph->Width-1, gx, 1, bgr2rgb(AGraph->GridColor), display);
				}
				//linhas verticais
				for(gx=AGraph->Left+20; gx<(AGraph->Left+AGraph->Width); gx+=20){
					   vid_draw_line(gx, AGraph->Top, gx, (AGraph->Top + AGraph->Height -1), 1, bgr2rgb(AGraph->GridColor), display);
			   }
	    }/*endif showgrid*/
		/*Draw the graph*/
		switch( AGraph->GraphType){
			/*--------------------------------------------------------------*/
			case PLOT:
				step = n/(AGraph->DataSize-1);
				//printf("Step= %d\n", step);
				cor = bgr2rgb(AGraph->DataColor);
				i = 0;
				meio = AGraph->Top+AGraph->Height/2;
				maxValue = BuscaMaior(AGraph->Data, AGraph->DataSize);
				//printf("Maxvalue = %d", maxValue);
				//for(i=0; i< (n-step); i= i+ step)
				for(pos=0; pos < AGraph->DataSize-1; pos++)
				{
					//printf("pos=%d i=%d\n", pos, i);
					/*if(AGraph->Data[pos]>100)d = -100;
					else if(AGraph->Data[pos]<-100)d = 100;
					else d = AGraph->Data[pos]*-1;*/
					if(maxValue>=80){
						d = ((-80*AGraph->Data[pos])/maxValue);

					/*if(AGraph->Data[pos+1]>100)d2 = -100;
					else if(AGraph->Data[pos+1]<-100)d2 = 100;
					else d2 = AGraph->Data[pos+1]*-1;*/
						d2 = ((-80*AGraph->Data[pos+1])/maxValue);

					}else
					{
						d = AGraph->Data[pos]*-1;
						d2 = AGraph->Data[pos+1]*-1;
					}

				/*	if(d>100) d = 100;
					else if (d<-100) d=-100;
					if(d2>100) d = 100;
					else if (d2<-100) d=-100;*/

					y = d + meio;
					y2 = d2 + meio;
					//printf("Graf. %s: %d %d\n",grafico->name, y, y2);
					vid_draw_line(i, y, i+step, y2, 1, cor, display);
					//vid_set_pixel(i, (int)grafico[pos]+200, BLUE_24, display);
					i+=step;
					if(i>n) i=n;
				}/*endfor draw graph*/
			break;/*end case plot*/
			/*--------------------------------------------------------------*/
			case STEM:
				step = n/AGraph->DataSize;
				cor = bgr2rgb(AGraph->DataColor);
				pos = 0;
				meio = AGraph->Top+AGraph->Height/2;
				maxValue = BuscaMaior(AGraph->Data, AGraph->DataSize);
				for(i=step; i< (n-step); i= i+ step)
				{
					/*if(AGraph->Data[pos]>100)d = -100;
					else if(AGraph->Data[pos]<-100)d = 100;
					else d = AGraph->Data[pos]*-1;*/
					d = ((-70*AGraph->Data[pos])/maxValue);

					/*if(AGraph->Data[pos+1]>100)d2 = -100;
					else if(AGraph->Data[pos+1]<-100)d2 = 100;
					else d2 = AGraph->Data[pos+1]*-1;*/

					y = d + meio;
					y2 = meio;
					//printf("Graf. %s: %d %d\n",grafico->name, y, y2);
					vid_draw_line(i, y, i, y2, 1, cor, display);
					vid_draw_circle(i, y, 3, cor, 0, display);
					//vid_set_pixel(i, (int)grafico[pos]+200, BLUE_24, display);
					pos++;
					if(pos>=(AGraph->DataSize-1))
					{
						pos = 0;
						break;
					}
				}/*endfor draw graph*/
			break;/*end case stem*/
			/*--------------------------------------------------------------*/
			case STAIR:
				step = n/AGraph->DataSize;
				cor = bgr2rgb(AGraph->DataColor);
				pos = 0;
				meio = AGraph->Top+AGraph->Height/2;
				maxValue = BuscaMaior(AGraph->Data, AGraph->DataSize);
				for(i=0; i< (n-step); i= i+ step)
				{
					/*if(AGraph->Data[pos]>100)d = -100;
					else if(AGraph->Data[pos]<-100)d = 100;
					else d = AGraph->Data[pos]*-1;*/
					d = ((-70*AGraph->Data[pos])/maxValue);

					/*if(AGraph->Data[pos+1]>100)d2 = -100;
					else if(AGraph->Data[pos+1]<-100)d2 = 100;
					else d2 = AGraph->Data[pos+1]*-1;*/
					d2 = ((-70*AGraph->Data[pos+1])/maxValue);

					y = d + meio;
					y2 = d2 + meio;
					//printf("Graf. %s: %d %d\n",grafico->name, y, y2);
					vid_draw_line(i, y, i+step, y2, 1, cor, display);
					//vid_set_pixel(i, (int)grafico[pos]+200, BLUE_24, display);
					pos++;
					if(pos>=(AGraph->DataSize-1)) pos = 0;
				}/*endfor draw graph*/
			break;/*end case stair*/
			/*--------------------------------------------------------------*/
			case BAR:
				step = n/AGraph->DataSize;
				cor = bgr2rgb(AGraph->DataColor);
				pos = 0;
				meio = AGraph->Top+AGraph->Height/2;
				for(i=0; i< (n-step); i= i+ step)
				{
					if(AGraph->Data[pos]>100)d = -100;
					else if(AGraph->Data[pos]<-100)d = 100;
					else d = AGraph->Data[pos]*-1;

					if(AGraph->Data[pos+1]>100)d2 = -100;
					else if(AGraph->Data[pos+1]<-100)d2 = 100;
					else d2 = AGraph->Data[pos+1]*-1;

					y = d + meio;
					y2 = d2 + meio;
					//printf("Graf. %s: %d %d\n",grafico->name, y, y2);
					vid_draw_line(i, y, i+step, y2, 1, cor, display);
					//vid_set_pixel(i, (int)grafico[pos]+200, BLUE_24, display);
					pos++;
					if(pos>=(AGraph->DataSize-1)) pos = 0;
				}/*endfor draw graph*/
			break;/*end case bar*/
		}/*end switch graph type*/
		//Show Border
		if(AGraph->ShowBorder){
				vid_draw_box(AGraph->Left, AGraph->Top, AGraph->Left+AGraph->Width, AGraph->Top+AGraph->Height, bgr2rgb(AGraph->BorderColor), 0, display);
		}
		//Draw Title
		vid_print_string(AGraph->Left+ AGraph->Width/2 - 40, AGraph->Top + 5, bgr2rgb(AGraph->DataColor), AGraph->FontName, display, AGraph->Graph_Name);
	}/*endif visible*/

}

void DrawGraphs() {
  int i;
  TGraph *local_graph;

  for ( i = 0 ; i < CurrentScreen->GraphsCount ; i++ ) {
	  local_graph = GetGraph(i);
      DrawGraph(local_graph);
  }

}

void DrawButton(TButton *Abutton) {
  if (Abutton->Visible == 1) {
	  //Box envolta do botao
	  	vid_draw_box(Abutton->Left,  Abutton->Top, Abutton->Left + Abutton->Width, Abutton->Top + Abutton->Height, Abutton->Pen_Color, 0, display);
	  	if(Abutton->Pressed){
	  		//Cor interna do botao pressionado
	  		vid_draw_box(Abutton->Left+1, Abutton->Top+1, Abutton->Left + Abutton->Width -1, Abutton->Top + Abutton->Height - 1, bgr2rgb(Abutton->Press_Color), 1, display);
	  		//Texto do botao
	  		vid_print_string(Abutton->Left+6, (Abutton->Top*2+Abutton->Height)/2-4, Abutton->Font_Color, Abutton->FontName, display, Abutton->Caption);
	  	}else{
	  		//Cor interna do botao nao pressionado
	  		vid_draw_box(Abutton->Left+1, Abutton->Top+1, Abutton->Left + Abutton->Width -1, Abutton->Top + Abutton->Height - 1, bgr2rgb(Abutton->Color), 1, display);
	  		vid_draw_line(Abutton->Left+1, Abutton->Top+1, Abutton->Left+1, Abutton->Top+Abutton->Height-2, 1, bgr2rgb(Abutton->Color), display );
	  		vid_draw_line(Abutton->Left+1, Abutton->Top+1, Abutton->Left+ Abutton->Width-3,Abutton->Top+1, 1, bgr2rgb(Abutton->Color), display );
	  		//Linhas cinza do efeito 3d do botao nao pressionado
	  		vid_draw_line(Abutton->Left+1, Abutton->Top+Abutton->Height-2,Abutton->Left+Abutton->Width-1,Abutton->Top+Abutton->Height-2, 1, bgr2rgb(GRAY_24), display );
	  		vid_draw_line(Abutton->Left+Abutton->Width-2, Abutton->Top+Abutton->Height-2, Abutton->Left+Abutton->Width-2,Abutton->Top+1, 1, bgr2rgb(GRAY_24), display );
	  		vid_print_string(Abutton->Left+5, (Abutton->Top*2+Abutton->Height)/2-5, Abutton->Font_Color, Abutton->FontName, display, Abutton->Caption);
	  	}
	  }

}

void DrawButtons() {
  int i;
  TButton *local_button;

  for ( i = 0 ; i < CurrentScreen->ButtonsCount ; i++ ) {
    local_button = GetButton(i);
    DrawButton(local_button);
  }
}

void DrawLabel(TLabel *Alabel) {
  if (Alabel->Visible == 1) {
	  vid_print_string(Alabel->Left, Alabel->Top, Alabel->Font_Color, Alabel->FontName, display, Alabel->Caption);
  }

}

void DrawLabels() {
  int i;
  TLabel *local_label;
  for ( i = 0 ; i < CurrentScreen->LabelsCount ; i++ ) {
    local_label = GetLabel(i);
    DrawLabel(local_label);
  }

}

void DrawBox(TBox *ABox) {
  if (ABox->Visible == 1) {
	  vid_draw_box(ABox->Left, ABox->Top, ABox->Left + ABox->Width-1, ABox->Top + ABox->Height-1, ABox->Color, 1, display);
	if(ABox->Pen_Width>0){
		vid_draw_box(ABox->Left, ABox->Top, ABox->Left + ABox->Width-1, ABox->Top + ABox->Height-1, ABox->Pen_Color, 0, display);
	}
  }
}

void DrawBoxes() {
  int i;
  TBox *local_box;

  for ( i = 0 ; i < CurrentScreen->BoxesCount ; i++ ) {
    local_box = GetBox(i);
    DrawBox(local_box);
  }
}

void DrawScreen(TScreen *aScreen) {
  unsigned short order;
  unsigned short button_idx;
  TButton *local_button;
  unsigned short round_button_idx;
  TButton_Round *local_round_button;
  unsigned short label_idx;
  TLabel *local_label;
  unsigned short image_idx;
  TImage *local_image;
  unsigned short box_idx;
  TBox *local_box;
  unsigned short round_box_idx;
  TBox_Round *local_round_box;
  unsigned short line_idx;
  TLine *local_line;
  unsigned short graph_idx;
  TGraph * local_graph;
  order = 0;
  button_idx = 0;
  round_button_idx = 0;
  label_idx = 0;
  image_idx = 0;
  box_idx = 0;
  round_box_idx = 0;
  line_idx = 0;
  graph_idx = 0;

  if ((display_width != aScreen->Width) || (display_height != aScreen->Height)) {
    ClearScreen(aScreen->Color);
    display_width = aScreen->Width;
    display_height = aScreen->Height;
  }
  else
	  ClearScreen(aScreen->Color);

  CurrentScreen = aScreen;
  //printf("DrawScreen: fundo azul\n\r");
  while (order < CurrentScreen->ObjectsCount) {

    if (button_idx < CurrentScreen->ButtonsCount) {
      local_button = GetButton(button_idx);
      //printf("Order: %d Local button: %d\n\r", order, local_button->Order);
      if (order == local_button->Order) {
        button_idx++;
        order++;
        DrawButton(local_button);
      }
    }

   /* if (round_button_idx < CurrentScreen->Buttons_RoundCount) {
      local_round_button = GetRoundButton(round_button_idx);
      if (order == local_round_button->Order) {
        order++;
        round_button_idx++;
        DrawRoundButton(local_round_button);
      }
    }*/

    if (label_idx < CurrentScreen->LabelsCount) {
      local_label = GetLabel(label_idx);
      //printf("Order: %d Local label: %d\n\r", order, local_label->Order);
      if (order == local_label->Order) {
        label_idx++;
        order++;
        DrawLabel(local_label);
      }
    }

    if (box_idx < CurrentScreen->BoxesCount) {
      local_box = GetBox(box_idx);
     // printf("Order: %d Local box: %d\n\r", order, local_box->Order);
      if (order == local_box->Order) {
        box_idx++;
        order++;
        DrawBox(local_box);
      }
    }

   /* if (round_box_idx < CurrentScreen->Boxes_RoundCount) {
      local_round_box = GetBox_Round(round_box_idx);
      if (order == local_round_box->Order) {
        round_box_idx++;
        order++;
        DrawRoundBox(local_round_box);
      }
    }

    if (line_idx  < CurrentScreen->LinesCount) {
      local_line = GetLine(line_idx);
      if (order == local_line->Order) {
        line_idx++;
        order++;
        DrawLine(local_line);
      }
    }

    if (image_idx  < CurrentScreen->ImagesCount) {
      local_image = GetImage(image_idx);
      if (order == local_image->Order) {
        image_idx++;
        order++;
        DrawImage(local_image);
      }
    }*/


    if (graph_idx < CurrentScreen->GraphsCount) {
        local_graph = GetGraph(graph_idx);
        //printf("Order: %d Local graph: %d\n\r", order, local_graph->Order);
        if (order == local_graph->Order) {
          graph_idx++;
          order++;
          DrawGraph(local_graph);
        }
      }
  }
  Redraw(display);
}

void Process_TP_Press(unsigned int X, unsigned int Y) {
  int i;
  TButton *local_button;
  TButton *exec_button;
  short button_order;
  TButton_Round *local_round_button;
  TButton_Round *exec_round_button;
  short round_button_order;
  TLabel *local_label;
  TLabel *exec_label;
  short label_order;
  TImage *local_image;
  TImage *exec_image;
  short image_order;
  TBox *local_box;
  TBox *exec_box;
  short box_order;
  TBox_Round *local_round_box;
  TBox_Round *exec_round_box;
  short box_round_order;

  button_order        = -1;
  round_button_order  = -1;
  label_order         = -1;
  image_order         = -1;
  box_order           = -1;
  box_round_order     = -1;

  // Buttons
  for ( i = 0 ; i < CurrentScreen->ButtonsCount ; i++ ) {
    local_button = GetButton(i);
    if (local_button->Active == 1) {
      if (IsInsideObject(X, Y, local_button->Left, local_button->Top,
                         local_button->Width, local_button->Height) == 1) {
        button_order = local_button->Order;
        exec_button = local_button;
      }
    }
  }

  // Buttons with Round Edges
/*  for ( i = 0 ; i < CurrentScreen->Buttons_RoundCount ; i++ ) {
    local_round_button = GetRoundButton(i);
    if (local_round_button->Active == 1) {
      if (IsInsideObject(X, Y, local_round_button->Left, local_round_button->Top,
                         local_round_button->Width, local_round_button->Height) == 1) {
        round_button_order = local_round_button->Order;
        exec_round_button = local_round_button;
      }
    }
  }*/

  // Labels
  for ( i = 0 ; i < CurrentScreen->LabelsCount ; i++ ) {
    local_label = GetLabel(i);
    if (local_label->Active == 1) {
      if (IsInsideObject(X, Y, local_label->Left, local_label->Top,
                         local_label->Width, local_label->Height) == 1) {
        label_order = local_label->Order;
        exec_label = local_label;
      }
    }
  }

  // Images
 /* for ( i = 0 ; i < CurrentScreen->ImagesCount ; i++ ) {
    local_image = GetImage(i);
    if (local_image->Active == 1) {
      if (IsInsideObject(X, Y, local_image->Left, local_image->Top,
                         local_image->Width, local_image->Height) == 1) {
        image_order = local_image->Order;
        exec_image = local_image;
      }
    }
  }
*/
  // Boxes
  for ( i = 0 ; i < CurrentScreen->BoxesCount ; i++ ) {
    local_box = GetBox(i);
    if (local_box->Active == 1) {
      if (IsInsideObject(X, Y, local_box->Left, local_box->Top,
                         local_box->Width, local_box->Height) == 1) {
        box_order = local_box->Order;
        exec_box = local_box;
      }
    }
  }
/*
  // Boxes with Round Edges
  for ( i = 0 ; i < CurrentScreen->Boxes_RoundCount ; i++ ) {
    local_round_box = GetBox_Round(i);
    if (local_round_box->Active == 1) {
      if (IsInsideObject(X, Y, local_round_box->Left, local_round_box->Top,
                         local_round_box->Width, local_round_box->Height) == 1) {
        box_round_order = local_round_box->Order;
        exec_round_box = local_round_box;
      }
    }
  }
*/
  i = -1;
  if (button_order > i)
    i = button_order;
  if (round_button_order > i)
    i = round_button_order;
  if (label_order > i)
    i = label_order;
  if (image_order > i)
    i = image_order;
  if (box_order > i)
    i = box_order;
  if (box_round_order > i)
    i = box_round_order;

  if (i != -1) {
    if (i == button_order) {
      if (exec_button->Active == 1) {
        if (exec_button->OnPressPtr != 0) {
          exec_button->OnPressPtr();
          return;
        }
      }
    }

    if (i == round_button_order) {
      if (exec_round_button->Active == 1) {
        if (exec_round_button->OnPressPtr != 0) {
          exec_round_button->OnPressPtr();
          return;
        }
      }
    }

    if (i == label_order) {
      if (exec_label->Active == 1) {
        if (exec_label->OnPressPtr != 0) {
          exec_label->OnPressPtr();
          return;
        }
      }
    }

    if (i == image_order) {
      if (exec_image->Active == 1) {
        if (exec_image->OnPressPtr != 0) {
          exec_image->OnPressPtr();
          return;
        }
      }
    }

    if (i == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->OnPressPtr != 0) {
          exec_box->OnPressPtr();
          return;
        }
      }
    }

    if (i == box_round_order) {
      if (exec_round_box->Active == 1) {
        if (exec_round_box->OnPressPtr != 0) {
          exec_round_box->OnPressPtr();
          return;
        }
      }
    }

  }
}

void Process_TP_Up(unsigned int X, unsigned int Y) {
  int i;
  TButton *local_button;
  TButton *exec_button;
  short button_order;
  TButton_Round *local_round_button;
  TButton_Round *exec_round_button;
  short round_button_order;
  TLabel *local_label;
  TLabel *exec_label;
  short label_order;
  TImage *local_image;
  TImage *exec_image;
  short image_order;
  TBox *local_box;
  TBox *exec_box;
  short box_order;
  TBox_Round *local_round_box;
  TBox_Round *exec_round_box;
  short box_round_order;

  switch (PressedObjectType) {
    // Button
    case 0: {
      if (PressedObject != 0) {
        exec_button = (TButton*)PressedObject;
        if (exec_button->PressColEnabled == 1) {
        	exec_button->Pressed = 0;
        	DrawButton(exec_button);
        }
        break;
      }
      break;
    }
   /* // Round Button
    case 1: {
      if (PressedObject != 0) {
        exec_round_button = (TButton_Round*)PressedObject;
        if (exec_round_button->PressColEnabled == 1) {
          TFT_Set_Brush(exec_round_button->Transparent, exec_round_button->Color, exec_round_button->Gradient, exec_round_button->Gradient_Orientation,
                        exec_round_button->Gradient_Start_Color, exec_round_button->Gradient_End_Color);
          TFT_Set_Pen(exec_round_button->Pen_Color, exec_round_button->Pen_Width);
          if (exec_round_button->Height > exec_round_button->Width)
            TFT_Rectangle_Round_Edges(exec_round_button->Left + 1, exec_round_button->Top + 1,
                                      exec_round_button->Left + exec_round_button->Width - 2,
                                      exec_round_button->Top + exec_round_button->Height - 2, (exec_round_button->Width / 4));
          else if (exec_round_button->Width > exec_round_button->Height)
            TFT_Rectangle_Round_Edges(exec_round_button->Left + 1, exec_round_button->Top + 1,
                                      exec_round_button->Left + exec_round_button->Width - 2,
                                      exec_round_button->Top + exec_round_button->Height - 2, (exec_round_button->Height / 4));
          TFT_Set_Font(exec_round_button->FontName, exec_round_button->Font_Color, FO_HORIZONTAL);
          TFT_Write_Text_Return_Pos(exec_round_button->Caption, exec_round_button->Left, exec_round_button->Top);
          TFT_Write_Text(exec_round_button->Caption, (exec_round_button->Left + ((exec_round_button->Width - caption_length) / 2)),
                        (exec_round_button->Top + ((exec_round_button->Height - caption_height) / 2)));
        }
        break;
      }
      break;
    }*/
    // Box
    case 6: {
      if (PressedObject != 0) {
        exec_box = (TBox*)PressedObject;
        if (exec_box->PressColEnabled == 1) {
          DrawBox(exec_box);
        }
        break;
      }
      break;
    }
 /*   // Round Box
    case 7: {
      if (PressedObject != 0) {
        exec_round_box = (TBox_Round*)PressedObject;
        if (exec_round_box->PressColEnabled == 1) {
          TFT_Set_Brush(exec_round_box->Transparent, exec_round_box->Color, exec_round_box->Gradient, exec_round_box->Gradient_Orientation,
                        exec_round_box->Gradient_Start_Color, exec_round_box->Gradient_End_Color);
          TFT_Set_Pen(exec_round_box->Pen_Color, exec_round_box->Pen_Width);
          if (exec_round_box->Height > exec_round_box->Width)
            TFT_Rectangle_Round_Edges(exec_round_box->Left + 1, exec_round_box->Top + 1,
                                      exec_round_box->Left + exec_round_box->Width - 2,
                                      exec_round_box->Top + exec_round_box->Height - 2, (exec_round_box->Width / 4));
          else if (exec_round_box->Width > exec_round_box->Height)
            TFT_Rectangle_Round_Edges(exec_round_box->Left + 1, exec_round_box->Top + 1,
                                      exec_round_box->Left + exec_round_box->Width - 2,
                                      exec_round_box->Top + exec_round_box->Height - 2, (exec_round_box->Height / 4));
        }
        break;
      }
      break;
    }*/
  }

  button_order        = -1;
  round_button_order  = -1;
  label_order         = -1;
  image_order         = -1;
  box_order           = -1;
  box_round_order     = -1;

  // Buttons
  for ( i = 0 ; i < CurrentScreen->ButtonsCount ; i++ ) {
    local_button = GetButton(i);
    if (local_button->Active == 1) {
      if (IsInsideObject(X, Y, local_button->Left, local_button->Top,
                         local_button->Width, local_button->Height) == 1) {
        button_order = local_button->Order;
        exec_button = local_button;
      }
    }
  }
/*
  // Buttons with Round Edges
  for ( i = 0 ; i < CurrentScreen->Buttons_RoundCount ; i++ ) {
    local_round_button = GetRoundButton(i);
    if (local_round_button->Active == 1) {
      if (IsInsideObject(X, Y, local_round_button->Left, local_round_button->Top,
                         local_round_button->Width, local_round_button->Height) == 1) {
        round_button_order = local_round_button->Order;
        exec_round_button = local_round_button;
      }
    }
  }*/

  // Labels
  for ( i = 0 ; i < CurrentScreen->LabelsCount ; i++ ) {
    local_label = GetLabel(i);
    if (local_label->Active == 1) {
      if (IsInsideObject(X, Y, local_label->Left, local_label->Top,
                         local_label->Width, local_label->Height) == 1) {
        label_order = local_label->Order;
        exec_label = local_label;
      }
    }
  }
/*
  // Images
  for ( i = 0 ; i < CurrentScreen->ImagesCount ; i++ ) {
    local_image = GetImage(i);
    if (local_image->Active == 1) {
      if (IsInsideObject(X, Y, local_image->Left, local_image->Top,
                         local_image->Width, local_image->Height) == 1) {
        image_order = local_image->Order;
        exec_image = local_image;
      }
    }
  }*/

  // Boxes
  for ( i = 0 ; i < CurrentScreen->BoxesCount ; i++ ) {
    local_box = GetBox(i);
    if (local_box->Active == 1) {
      if (IsInsideObject(X, Y, local_box->Left, local_box->Top,
                         local_box->Width, local_box->Height) == 1) {
        box_order = local_box->Order;
        exec_box = local_box;
      }
    }
  }
/*
  // Boxes with Round Edges
  for ( i = 0 ; i < CurrentScreen->Boxes_RoundCount ; i++ ) {
    local_round_box = GetBox_Round(i);
    if (local_round_box->Active == 1) {
      if (IsInsideObject(X, Y, local_round_box->Left, local_round_box->Top,
                         local_round_box->Width, local_round_box->Height) == 1) {
        box_round_order = local_round_box->Order;
        exec_round_box = local_round_box;
      }
    }
  }
*/
  i = -1;
  if (button_order > i)
    i = button_order;
  if (round_button_order > i)
    i = round_button_order;
  if (label_order > i)
    i = label_order;
  if (image_order > i)
    i = image_order;
  if (box_order > i)
    i = box_order;
  if (box_round_order > i)
    i = box_round_order;

  if (i != -1) {
  // Buttons
    if (i == button_order) {
      if (exec_button->Active == 1) {
        if (exec_button->OnUpPtr != 0)
          exec_button->OnUpPtr();
        if (PressedObject == (void *)exec_button)
          if (exec_button->OnClickPtr != 0)
            exec_button->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }
/*
  // Buttons with Round Edges
    if (i == round_button_order) {
      if (exec_round_button->Active == 1) {
        if (exec_round_button->OnUpPtr != 0)
          exec_round_button->OnUpPtr();
        if (PressedObject == (void *)exec_round_button)
          if (exec_round_button->OnClickPtr != 0)
            exec_round_button->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }
*/
  // Labels
    if (i == label_order) {
      if (exec_label->Active == 1) {
        if (exec_label->OnUpPtr != 0)
          exec_label->OnUpPtr();
        if (PressedObject == (void *)exec_label)
          if (exec_label->OnClickPtr != 0)
            exec_label->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }
/*
  // Images
    if (i == image_order) {
      if (exec_image->Active == 1) {
        if (exec_image->OnUpPtr != 0)
          exec_image->OnUpPtr();
        if (PressedObject == (void *)exec_image)
          if (exec_image->OnClickPtr != 0)
            exec_image->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }
*/
  // Boxes
    if (i == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->OnUpPtr != 0)
          exec_box->OnUpPtr();
        if (PressedObject == (void *)exec_box)
          if (exec_box->OnClickPtr != 0)
            exec_box->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

 /* // Boxes with Round Edges
    if (i == box_round_order) {
      if (exec_round_box->Active == 1) {
        if (exec_round_box->OnUpPtr != 0)
          exec_round_box->OnUpPtr();
        if (PressedObject == (void *)exec_round_box)
          if (exec_round_box->OnClickPtr != 0)
            exec_round_box->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }
*/
  }
  PressedObject = 0;
  PressedObjectType = -1;
}

void Process_TP_Down(unsigned int X, unsigned int Y) {
  int i;
  TButton *local_button;
  TButton *exec_button;
  short button_order;
  TButton_Round *local_round_button;
  TButton_Round *exec_round_button;
  short round_button_order;
  TLabel *local_label;
  TLabel *exec_label;
  short label_order;
  TImage *local_image;
  TImage *exec_image;
  short image_order;
  TBox *local_box;
  TBox *exec_box;
  short box_order;
  TBox_Round *local_round_box;
  TBox_Round *exec_round_box;
  short box_round_order;

  button_order        = -1;
  round_button_order  = -1;
  label_order         = -1;
  image_order         = -1;
  box_order           = -1;
  box_round_order     = -1;

  // Buttons
  for ( i = 0 ; i < CurrentScreen->ButtonsCount ; i++ ) {
    local_button = GetButton(i);
    if (local_button->Active == 1) {
      if (IsInsideObject(X, Y, local_button->Left, local_button->Top,local_button->Width, local_button->Height) == 1) {
			  button_order = local_button->Order;
			  exec_button = local_button;
      }
    }
  }

  // Buttons with Round Edges
  for ( i = 0 ; i < CurrentScreen->Buttons_RoundCount ; i++ ) {
    local_round_button = GetRoundButton(i);
    if (local_round_button->Active == 1) {
      if (IsInsideObject(X, Y, local_round_button->Left, local_round_button->Top,
                         local_round_button->Width, local_round_button->Height) == 1) {
        round_button_order = local_round_button->Order;
        exec_round_button = local_round_button;
      }
    }
  }

  // Labels
  for ( i = 0 ; i < CurrentScreen->LabelsCount ; i++ ) {
    local_label = GetLabel(i);
    if (local_label->Active == 1) {
      if (IsInsideObject(X, Y, local_label->Left, local_label->Top,
                         local_label->Width, local_label->Height) == 1) {
        label_order = local_label->Order;
        exec_label = local_label;
      }
    }
  }

  // Images
  for ( i = 0 ; i < CurrentScreen->ImagesCount ; i++ ) {
    local_image = GetImage(i);
    if (local_image->Active == 1) {
      if (IsInsideObject(X, Y, local_image->Left, local_image->Top,
                         local_image->Width, local_image->Height) == 1) {
        image_order = local_image->Order;
        exec_image = local_image;
      }
    }
  }

  // Boxes
  for ( i = 0 ; i < CurrentScreen->BoxesCount ; i++ ) {
    local_box = GetBox(i);
    if (local_box->Active == 1) {
      if (IsInsideObject(X, Y, local_box->Left, local_box->Top,
                         local_box->Width, local_box->Height) == 1) {
        box_order = local_box->Order;
        exec_box = local_box;
      }
    }
  }

  // Boxes with Round Edges
  for ( i = 0 ; i < CurrentScreen->Boxes_RoundCount ; i++ ) {
    local_round_box = GetBox_Round(i);
    if (local_round_box->Active == 1) {
      if (IsInsideObject(X, Y, local_round_box->Left, local_round_box->Top,
                         local_round_box->Width, local_round_box->Height) == 1) {
        box_round_order = local_round_box->Order;
        exec_round_box = local_round_box;
      }
    }
  }

  i = -1;
  if (button_order > i)
    i = button_order;
  if (round_button_order > i)
    i = round_button_order;
  if (label_order > i)
    i = label_order;
  if (image_order > i)
    i = image_order;
  if (box_order > i)
    i = box_order;
  if (box_round_order > i)
    i = box_round_order;
  if (i != -1) {
    if (i == button_order) {
      if (exec_button->Active == 1) {
        if (exec_button->PressColEnabled == 1) {
        	exec_button->Pressed = 1;
        	printf("Draw exec button, with press = 1\n\r");
        	DrawButton(exec_button);
        }
        PressedObject = (void *)exec_button;
        PressedObjectType = 0;
        if (exec_button->OnDownPtr != 0) {
          exec_button->OnDownPtr();
          return;
        }
      }
    }

   /* if (i == round_button_order) {
      if (exec_round_button->Active == 1) {
        if (exec_round_button->PressColEnabled == 1) {
          TFT_Set_Brush(exec_round_button->Transparent, exec_round_button->Press_Color, exec_round_button->Gradient, exec_round_button->Gradient_Orientation,
                        exec_round_button->Gradient_End_Color, exec_round_button->Gradient_Start_Color);
          TFT_Set_Pen(exec_round_button->Pen_Color, exec_round_button->Pen_Width);
          if (exec_round_button->Height > exec_round_button->Width)
            TFT_Rectangle_Round_Edges(exec_round_button->Left + 1, exec_round_button->Top + 1,
                                      exec_round_button->Left + exec_round_button->Width - 2,
                                      exec_round_button->Top + exec_round_button->Height - 2, (exec_round_button->Width / 4));
          else if (exec_round_button->Width > exec_round_button->Height)
            TFT_Rectangle_Round_Edges(exec_round_button->Left + 1, exec_round_button->Top + 1,
                                      exec_round_button->Left + exec_round_button->Width - 2,
                                      exec_round_button->Top + exec_round_button->Height - 2, (exec_round_button->Height / 4));
          TFT_Set_Font(exec_round_button->FontName, exec_round_button->Font_Color, FO_HORIZONTAL);
          TFT_Write_Text_Return_Pos(exec_round_button->Caption, exec_round_button->Left, exec_round_button->Top);
          TFT_Write_Text(exec_round_button->Caption, (exec_round_button->Left + ((exec_round_button->Width - caption_length) / 2)),
                        (exec_round_button->Top + ((exec_round_button->Height - caption_height) / 2)));
        }
        PressedObject = (void *)exec_round_button;
        PressedObjectType = 1;
        if (exec_round_button->OnDownPtr != 0) {
          exec_round_button->OnDownPtr();
          return;
        }
      }
    }*/

    if (i == label_order) {
      if (exec_label->Active == 1) {
        PressedObject = (void *)exec_label;
        PressedObjectType = 2;
        if (exec_label->OnDownPtr != 0) {
          exec_label->OnDownPtr();
          return;
        }
      }
    }

    if (i == image_order) {
      if (exec_image->Active == 1) {
        PressedObject = (void *)exec_image;
        PressedObjectType = 3;
        if (exec_image->OnDownPtr != 0) {
          exec_image->OnDownPtr();
          return;
        }
      }
    }

    if (i == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->PressColEnabled == 1) {
        DrawBox(exec_box);
        }
        PressedObject = (void *)exec_box;
        PressedObjectType = 6;
        if (exec_box->OnDownPtr != 0) {
          exec_box->OnDownPtr();
          return;
        }
      }
    }

   /* if (i == box_round_order) {
      if (exec_round_box->Active == 1) {
        if (exec_round_box->PressColEnabled == 1) {
          TFT_Set_Brush(exec_round_box->Transparent, exec_round_box->Press_Color, exec_round_box->Gradient, exec_round_box->Gradient_Orientation,
                        exec_round_box->Gradient_End_Color, exec_round_box->Gradient_Start_Color);
          TFT_Set_Pen(exec_round_box->Pen_Color, exec_round_box->Pen_Width);
          if (exec_round_box->Height > exec_round_box->Width)
            TFT_Rectangle_Round_Edges(exec_round_box->Left + 1, exec_round_box->Top + 1,
                                      exec_round_box->Left + exec_round_box->Width - 2,
                                      exec_round_box->Top + exec_round_box->Height - 2, (exec_round_box->Width / 4));
          else if (exec_round_box->Width > exec_round_box->Height)
            TFT_Rectangle_Round_Edges(exec_round_box->Left + 1, exec_round_box->Top + 1,
                                      exec_round_box->Left + exec_round_box->Width - 2,
                                      exec_round_box->Top + exec_round_box->Height - 2, (exec_round_box->Height / 4));
        }
        PressedObject = (void *)exec_round_box;
        PressedObjectType = 7;
        if (exec_round_box->OnDownPtr != 0) {
          exec_round_box->OnDownPtr();
          return;
        }
      }
    }*/

  }
}

void Check_TP() {

  //alt_touchscreen_get_pen ( &touchscreen, &pen_is_down, &Xcoord, &Ycoord );
 // printf("Rodadndo Pen:%d X:%d Y:%d.\n\r", pen_is_down, Xcoord, Ycoord);
  if (pen_is_down) {
    // After a PRESS is detected read X-Y and convert it to Display dimensions space
      //printf("Pen is down!\n\r");
	  Process_TP_Press(Xcoord, Ycoord);
      if (PenDown == 0) {
        PenDown = 1;
        Process_TP_Down(Xcoord, Ycoord);
      }
  }
  else if (PenDown == 1) {
    PenDown = 0;
    Process_TP_Up(Xcoord, Ycoord);
  }
}

void Initialize_TFT(void){
		printf("Inicializando controlador do LCD\n");
	  	/*Inicialize o controlador LCD*/
	  	lcd.scen_pio = LCD_I2C_EN_BASE;
	  	lcd.scl_pio = LCD_I2C_SCL_BASE;
	  	lcd.sda_pio = LCD_I2C_SDAT_BASE;
	  	alt_tpo_lcd_init(&lcd, WIDTH, HEIGHT);
	  	printf("Inicializando buffer de imagem\n");
	  	/*Inicialize o buffer de imagem*/

	  	IOWR_ALTERA_AVALON_SGDMA_CONTROL(LCD_SGDMA_BASE, ALTERA_AVALON_SGDMA_CONTROL_SOFTWARERESET_MSK);
	  	display = alt_video_display_init(
	  		    "/dev/lcd_sgdma",            // char* sgdma_name
	  		    WIDTH,                       // int width
	  		    HEIGHT,                      // int height
	  		    COLORDEPTH,                  // int color_depth
	  		    ALT_VIDEO_DISPLAY_USE_HEAP,  // int buffer_location (malloc buffers)
	  		    ALT_VIDEO_DISPLAY_USE_HEAP,  // int descriptor_location (malloc descriptors)
	  		    NUMBUFFER);                  // int num_buffers
	  	  if(display) {
	  		printf("Successo na inicialização do buffer de imagem.\n");
	  	  }
	  	  else {
	  		printf("Falhou ao inicializar. Parando a execução...\n");
	     }
         alt_video_display_clear_screen(display, 0xFF);
}

void draw_array(unsigned int *buffer, int x_size, int y_size,
alt_video_display* display, int x_offset, int y_offset,
  unsigned int transparent_color)
{
  unsigned int *current_buffer;
  int addr = ( (int)(display->buffer_ptrs[display->buffer_being_written]->buffer) );
  current_buffer = (unsigned int *)addr;
  int x_b,y_b;
  unsigned int color;

  for (x_b = 0; x_b<x_size; x_b++) {
    for (y_b = 0; y_b<y_size; y_b++) {
      color = buffer[y_b*x_size+x_b];
      if (color != transparent_color) {
        current_buffer[(y_b+y_offset)*WIDTH+(x_b+x_offset)] = color;
      }
    }
  }
}





