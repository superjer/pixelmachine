/*
** SJUI - SuperJer's User Interface
** v 0.1.fresh
**
** A very simple SDL Gooey by SuperJer
**
** Email = superjer@superjer.com
** Web   = http://www.superjer.com/
**
**
**
*/


#include <string.h>
#include <SDL/SDL.h>

#include "font.h"



#define SJUIF_EXTENDSV   0x1
#define SJUIF_EXTENDSH   0x2
#define SJUIF_STRETCHFIT 0x4


typedef int SJUI_HANDLE;


struct SJUI_CONTROL
{
    SJUI_HANDLE handle;
    SJUI_CONTROL *parent;
    SJUI_CONTROL **children;
    SDL_Rect pos;
    int child_count;
    int child_alloc;
    char *caption;
    bool visible;
    bool interactive;
    int flags;

    void init();
    void destroy();
};


struct SJUI
{
    int handle_max;
    SJUI_CONTROL root;
    SJUI_CONTROL **shortcuts;
    int shortcut_count;
    int shortcut_alloc;
    SJUI_HANDLE modal;

    void init();
    void destroy();

    
    void paint( SDL_Surface *screen );
    void focus( SJUI_HANDLE handle, bool _modal );
    void check_in();
    bool mouse_to(int x, int y);
    bool mouse_down(int button);
    bool mouse_up(int button);
    bool key_down(int key);
    bool key_up(int key);

    void set_pos(SJUI_HANDLE handle,int x, int y);
    void set_size(SJUI_HANDLE handle,int w, int h);
    void set_caption(SJUI_HANDLE handle,const char *s);

    SJUI_HANDLE new_control(SJUI_HANDLE parent,int w,int h,int flags);
    SJUI_HANDLE new_menu(SJUI_HANDLE parent);
    SJUI_CONTROL *get_by_handle(SJUI_HANDLE parent);
};






