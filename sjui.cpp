

#include "sjui.h"
#include "font.h"



void SJUI::init()
{
    root.init();
    handle_max = 1;
    shortcut_count = 1;
    shortcut_alloc = 8;
    shortcuts = (SJUI_CONTROL**)malloc(sizeof(SJUI_CONTROL*)*shortcut_alloc);
    shortcuts[0] = &root;
    modal = 0;
}


void SJUI::destroy()
{
    free(shortcuts);
    root.destroy();
}


void SJUI::paint( SDL_Surface *screen )
{
    int i;
    bool visible;
    SDL_Rect rect;
    SJUI_CONTROL *p, *q;

    for( i=0; i<shortcut_count; i++ )
    {
        p = shortcuts[i];
        visible = p->visible;
        rect = p->pos;

        q = p;
        while( q->parent )
        {
            q = q->parent;
            rect.x += q->pos.x;
            rect.y += q->pos.y;
            if( !q->visible )
                visible = false;
        }

        if( visible )
        {
            SDL_FillRect(screen,&rect,0x000000);
            DrawSquare(screen,&rect,0x3333FF);
            if( p->caption )
              SJF_DrawText(screen,rect.x+2,rect.y+2,p->caption);
        }
    }
}


void SJUI::focus( SJUI_HANDLE handle, bool _modal )
{
    ;
}


SJUI_HANDLE SJUI::new_control(SJUI_HANDLE parent, int w, int h, int flags)
{
    int i;
    SJUI_CONTROL *p = get_by_handle(parent);
    SJUI_CONTROL *q;
    if( p->child_count >= p->child_alloc )
        p->children = (SJUI_CONTROL**)realloc( p->children, sizeof(SJUI_CONTROL*)*(p->child_alloc*=2) );
    q = p->children[p->child_count++] = (SJUI_CONTROL*)malloc(sizeof(SJUI_CONTROL));
    q->init();
    q->parent = p;
    q->flags = flags;
    q->handle = handle_max++;
    q->pos.w = w;
    q->pos.h = h;
    if( shortcut_count >= shortcut_alloc )
        shortcuts = (SJUI_CONTROL**)realloc( shortcuts, sizeof(SJUI_CONTROL*)*(shortcut_alloc*=2) );
    shortcuts[shortcut_count++] = q;

    if( flags&SJUIF_EXTENDSV )
    {
        int max = 0;
        int temp;
        for( i=0; i<p->child_count; i++ )
        {
            temp = p->children[i]->pos.y + p->children[i]->pos.h;
            if( temp > max )
                max = temp;
        }
        q->pos.y = max;
    }

    if( flags&SJUIF_EXTENDSV || flags&SJUIF_EXTENDSH )
    {
        if( p->pos.h < q->pos.y+q->pos.h )
            p->pos.h = q->pos.y+q->pos.h;
        if( p->pos.w < q->pos.x+q->pos.w )
            p->pos.w = q->pos.x+q->pos.w;
    }

    return q->handle;
}


void SJUI::set_pos(SJUI_HANDLE handle,int x, int y)
{
    SJUI_CONTROL *p = get_by_handle(handle);
    p->pos.x = x;
    p->pos.y = y;
}


void SJUI::set_size(SJUI_HANDLE handle,int w, int h)
{
    SJUI_CONTROL *p = get_by_handle(handle);
    p->pos.w = w;
    p->pos.h = h;
}


void SJUI::set_caption(SJUI_HANDLE handle,const char *s)
{
    SJUI_CONTROL *p = get_by_handle(handle);
    p->caption = (char*)realloc(p->caption,strlen(s)+1);
    strcpy(p->caption,s);
}


SJUI_HANDLE SJUI::new_menu(SJUI_HANDLE parent)
{
    return 0;
}


SJUI_CONTROL *SJUI::get_by_handle(SJUI_HANDLE handle)
{
    int i;
    for( i=0; i<shortcut_count; i++ )
        if( shortcuts[i]->handle == handle )
            return shortcuts[i];
    return &root;
}


void SJUI_CONTROL::init()
{
    handle = 0;
    parent = NULL;
    pos.x = 0;
    pos.y = 0;
    pos.w = 0;
    pos.h = 0;
    child_count = 0;
    child_alloc = 8;
    children = (SJUI_CONTROL**)malloc(sizeof(SJUI_CONTROL*)*child_alloc);
    caption = NULL;
    visible = true;
    interactive = true;
    flags = 0;
}


void SJUI_CONTROL::destroy()
{
    int i;
    for(i=0; i<child_count; i++)
    {
        children[i]->destroy();
        free( children[i] );
    }
    free(children);
    if( caption )
        free(caption);
}











void DrawSquare( SDL_Surface *surf, SDL_Rect *rect, Uint32 color )
{
    SDL_Rect edge;
    edge = *rect;
    edge.w = 1;
    SDL_FillRect(surf,&edge,color);
    edge.x += rect->w - 1;
    SDL_FillRect(surf,&edge,color);
    edge = *rect;
    edge.h = 1;
    SDL_FillRect(surf,&edge,color);
    edge.y += rect->h - 1;
    SDL_FillRect(surf,&edge,color);
}


