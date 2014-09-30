#ifndef DANWINDOW_H_
#define DANWINDOW_H_

//Tipos de dados
typedef struct Screen TScreen;

typedef struct  Button {
  TScreen       *OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char 			Pressed;
  char          Transparent;
  char          *Caption;
  const char    *FontName;
  unsigned int  Font_Color;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TButton;

typedef struct  Button_Round {
  TScreen       *OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char          Transparent;
  char          *Caption;
  const char    *FontName;
  unsigned int  Font_Color;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TButton_Round;

typedef struct  Label {
  char          Order;
  TScreen       *OwnerScreen;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          *Caption;
  const char    *FontName;
  unsigned int  Font_Pos_Ver;
  unsigned int  Font_Color;
  char          Visible;
  char          Active;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TLabel;

typedef struct  Image {
  TScreen       *OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  unsigned int  PictureWidth;
  unsigned int  PictureHeight;
  const char    *Picture_Name;
  int			*Picture;
  char          Visible;
  char          Active;
  char          AutoSize;
  char          Picture_Type;
  char          Picture_Ratio;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TImage;

typedef struct  Graph {
  TScreen       *OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          *Graph_Name;
  short			*Data;
  const char    *FontName;
  int			DataSize;
  int 			DataColor;
  int 			BackColor;
  char			ShowGrid;
  int			GridColor;
  char			ShowBorder;
  int			BorderColor;
  char 			GraphType;
  char          Visible;
  char          Active;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TGraph;

typedef struct  Box {
  TScreen       *OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char          Transparent;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TBox;

typedef struct  Box_Round {
  TScreen       *OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char          Transparent;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TBox_Round;

typedef struct  Line {
  TScreen       *OwnerScreen;
  char          Order;
  unsigned int  First_Point_X;
  unsigned int  First_Point_Y;
  unsigned int  Second_Point_X;
  unsigned int  Second_Point_Y;
  char          Pen_Width;
  char          Visible;
  char          Active;
  unsigned int  Color;
} TLine;

struct Screen {
  unsigned int           Color;
  unsigned int           Width;
  unsigned int           Height;
  unsigned short         ObjectsCount;
  unsigned int           ButtonsCount;
  TButton                **Buttons;
  unsigned int           Buttons_RoundCount;
  TButton_Round          **Buttons_Round;
  unsigned int           LabelsCount;
  TLabel                 **Labels;
  unsigned int           ImagesCount;
  TImage                 **Images;
  unsigned int           BoxesCount;
  TBox                   **Boxes;
  unsigned int           Boxes_RoundCount;
  TBox_Round             **Boxes_Round;
  unsigned int           LinesCount;
  TLine                 **Lines;
  unsigned int			GraphsCount;
  TGraph 				**Graphs;
};

extern unsigned int Xcoord, Ycoord;
extern char PenDown;
extern void *PressedObject;
extern int PressedObjectType;
extern unsigned int caption_length, caption_height;
extern unsigned int display_width, display_height;
//extern alt_touchscreen touchscreen; //Touch
//extern alt_tpo_lcd lcd; //Controle do LCD
//extern alt_video_display *display;//Buffer de imagem do LCD
extern TScreen *CurrentScreen;


void InitializeTouchPanel(void);
void Initialize_TFT(void);
short BuscaMaior(short * vet, int size);
char IsInsideObject (unsigned int X, unsigned int Y, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height);
void DrawButton(TButton *Abutton);
#define GetButton(index)              CurrentScreen->Buttons[index]
#define GetRoundButton(index)         CurrentScreen->Buttons_Round[index]
#define GetLabel(index)               CurrentScreen->Labels[index]
#define GetImage(index)               CurrentScreen->Images[index]
#define GetBox(index)                 CurrentScreen->Boxes[index]
#define GetBox_Round(index)           CurrentScreen->Boxes_Round[index]
#define GetLine(index)                CurrentScreen->Lines[index]
#define GetGraph(index)				  CurrentScreen->Graphs[index]
void DrawButtons();
void DrawLabel(TLabel *Alabel);
void DrawLabels();
void DrawBox(TBox *ABox);
void DrawBoxes();
void DrawGraph(TGraph *AGraph);
void DrawGraphs();
void DrawScreen(TScreen *aScreen);
void Process_TP_Press(unsigned int X, unsigned int Y);
void Process_TP_Up(unsigned int X, unsigned int Y);
void Process_TP_Down(unsigned int X, unsigned int Y);
void Check_TP();
void ClearScreen(int color);


//Board definitions and includes
/* Altera Embedded Evaluation Kit IO drivers */
#include "../alt_video_display/alt_video_display.h"
#include "../graphics_lib/simple_graphics.h"
#include "../alt_touchscreen/alt_touchscreen.h"
#include "../alt_tpo_lcd/alt_tpo_lcd.h"
#include "altera_avalon_sgdma_regs.h"
//#include "altera_avalon_spi_regs.h"
#define DEBUG_PRINT 0              // enable debug printf messages to stdout()
#define WIDTH       800            // LCD screen width
#define HEIGHT      480            // LCD sreen height
#define COLORDEPTH  32             // LCD screen color depth (bits per pixel)
#define NUMBUFFER   2              // Number of buffers for LCD driver
#define TEXT_COLOR 0xFFFFFF        // Color of text (white)
#define BACKGROUND_COLOR 0x0
#define BACKGROUND_MASK 0x0
#define SPLASH_BG_COLOR 0xFFFFFF   // Background color for splash screen (white)
#define SPLASH_BG_MASK 0x1
#define BUFFER_NUMBER 10           // Number of images to pre-buffer
#define INITIAL_TIME 10            // Initial time (seconds) between photos
#define PHOTOS_DIRECTORY "image"   // Folder on SD card to recurse for images
#define TOUCHSCREEN_SAMPLE_RATE 50 // Sample-rate for touch screen (Hz)
#define BMP      0
#define JPEG     1
#define UNKNOWN -1
#define FUNDO 0x006000
#define LCD_PRIORIDADE 6
//Tipos de grafico
#define PLOT 0
#define STEM 1
#define STAIR 2
#define BAR 3


typedef struct
{
  unsigned int framebuffer[HEIGHT][WIDTH];
  char text_string[100];
  unsigned short show_text;
  unsigned short data_ready;
  unsigned short lock;
  struct display_buffer *next;
  struct display_buffer *prev;
} display_buffer;

void draw_array(unsigned int *buffer, int x_size, int y_size, alt_video_display* display, int x_offset, int y_offset, unsigned int transparent_color);
void Redraw(alt_video_display * display);

#endif /* DANWINDOW_H_ */
