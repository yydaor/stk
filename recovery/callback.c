#include "stk.h"
#include "lua.h"
#include "lauxlib.h"

#include "recover.h"

extern Recovery *grec;
extern progress;
extern lua_State *L;


int thread_bar(void *data)
{
	int ret;

	if (grec->button_start) {
		STK_WidgetClose((STK_Widget *)grec->button_start);
		grec->button_start = NULL;	
	}

	ret = system("./bar /root/tmp/home.tar.gz | tar xzf - -C ttt");
/*	
	ret = loadFile(L, "recovery.lua");
	printf("ret = %d \n", ret);
*/
	// pass
	if (ret == 0) {
		STK_MsgBoxAddMsg(grec->msgbox, "还原结束。");
		STK_LabelSetText(grec->label_status, "系统还原结束。请按‘退出’键重启");
	
	}
	// failed
	else {
		printf("%s", "Error while extract!");
		STK_MsgBoxAddMsg(grec->msgbox, "解压中出错！");
		STK_LabelSetColor(grec->label_status, STK_COLOR_FOREGROUND, 0xff, 0x00, 0x00);
		STK_LabelSetText(grec->label_status, "  还原出错！                   ");
	}
	
	return 0;
}

int thread_update(void *data)
{
	FILE *fprogress;
	char str[16];
	int ret;
	
	while (progress <= 99 ) {
		
		if ((fprogress = fopen("progress.txt", "r")) == NULL) {
			// printf("progress.txt doesn't exist.\n");
			progress = 0;
		}
		else {	
			fscanf(fprogress, "%d", &progress);
			fclose(fprogress);

			//sprintf(str, "%d%%", progress);
			//STK_MsgBoxAddMsg(grec->msgbox, str);
		}
		SDL_Delay(1000);
	}
	
	return 0;
}




void cb_button_start()
{
	SDL_Thread *thread;
	
	STK_MsgBoxAddMsg(grec->msgbox, "现在开始还原。");
	STK_LabelSetText(grec->label_status, "系统正在还原中……");

        if ((thread = SDL_CreateThread(thread_bar, NULL)) == NULL ) {
	        fprintf(stderr, "Can't create thread: %s \n", SDL_GetError());
	        return;
        }

        if ((thread = SDL_CreateThread(thread_update, NULL)) == NULL ) {
	        fprintf(stderr, "Can't create thread: %s \n", SDL_GetError());
	        return;
        }
	

}

void cb_button_exit()
{
	SDL_Event event;
	
	lua_close(L);

	event.type = SDL_QUIT;
	event.user.code = 0;
	event.user.data1 = NULL;
	event.user.data2 = 0;
		
	SDL_PushEvent(&event);
}