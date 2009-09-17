
#include "stk.h"
#include "stk_label.h"
#include "stk_button.h"

STK_Widget *draw_label()
{
	
	STK_Label *label = (STK_Label *)STK_LabelNew("我爱你中国，我爱你家乡！", 400, 100);
//	STK_WidgetSetDims((STK_Widget *)label, 100, 100, 200, 100);
	STK_LabelSetAlignment((STK_Widget *)label, CENTER);
	STK_LabelSetColor((STK_Widget *)label, BACKGROUND, 0x00800080);
	STK_WidgetEventShow((STK_Widget *)label);
	
	return (STK_Widget *)label;
}

STK_Widget *draw_button()
{
	STK_Button *button = (STK_Button *)STK_ButtonNew("hehe, haha, xixi, jiji, titi", 10, 10, 100, 30);
//	STK_WindowAddWidget((STK_Widget *)button);
	STK_WidgetEventShow((STK_Widget *)button);
	return (STK_Widget *)button;
}


int main(int argc,char **argv)
{

    	SDL_Surface *video;
    	STK_Widget  *button;

    	SDL_Init(SDL_INIT_VIDEO);

    	video=SDL_SetVideoMode(600, 480, 32, SDL_HWSURFACE);
	if ( video == NULL ) {
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
							SDL_GetError());
		SDL_Quit();
	}
    	atexit(SDL_Quit);
    
    	STK_Init();

    	STK_WindowNew(0, 0, 600, 480);
    	
    	STK_Widget *label = draw_label();
    	printf("Label: %x\n", label);
    	
    	draw_button();
    	
    	STK_WindowOpen();
//    	SDL_Delay(5000);
    	
//    	STK_WidgetClose(label);
//   	SDL_Delay(5000);
    	
//    	label = draw_label();
//    	printf("Label: %x\n", label);

    	STK_Main();
}
