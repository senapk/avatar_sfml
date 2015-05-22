#include "csf.h"
#include <string.h>
#include <stdio.h>

static sfRenderWindow* _janela;
static sfRectangleShape *_rect;
static sfCircleShape * _circle;
static sfText* _text;
static sfFont* _font;
static sfMusic *_som;
static int _cell = 20;

sfRenderWindow * tk_init(int cell, int sizeX, int sizeY)
{
    _cell = cell;
    sfVideoMode mode = {_cell * sizeX, _cell * sizeY, 32};
    _janela = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(_janela, 20);
    if (!_janela)
        return NULL;

    _font = sfFont_createFromFile("../rock/inconsolata.otf");
    if (!_font)
        return NULL;
    _text = sfText_create();
    sfText_setFont(_text, _font);
    sfText_setColor(_text, sfWhite);

    _rect = sfRectangleShape_create();
    sfVector2f size = {_cell, _cell};
    sfRectangleShape_setSize(_rect, size);

    _circle = sfCircleShape_create();
    sfCircleShape_setRadius(_circle, _cell/2);


    return _janela;
}


void tk_rect(float x, float y, sfColor cor)
{
    sfVector2f pos = {x * _cell, y * _cell};
    sfRectangleShape_setPosition(_rect, pos);
    sfRectangleShape_setFillColor(_rect, cor);
    sfRenderWindow_drawRectangleShape(_janela, _rect, NULL);
}

int tk_is_open(){
    if(sfRenderWindow_isOpen(_janela))
        return 1;
    return 0;
}

int tk_peek(){
    sfEvent event;
    int code = 0;
    while(sfRenderWindow_pollEvent(_janela, &event)){
        if(event.type == sfEvtResized){
            sfFloatRect frect = {0, 0, event.size.width, event.size.height};
            sfView * view = sfView_createFromRect(frect);
            sfRenderWindow_setView(_janela, view);
            sfView_destroy(view);
        }
        if(event.type == sfEvtClosed)
            sfRenderWindow_close(_janela);
        if(event.type == sfEvtKeyPressed){
            int keycode = event.key.code;
            if(keycode >= sfKeyA && keycode <= sfKeyZ)
                code = 'a' - sfKeyA + keycode;
            if(keycode >= sfKeyNum0 && keycode <= sfKeyNum9)
                code = '0' - sfKeyNum0 + keycode;

            switch (keycode) {
                case sfKeyLBracket:     code = '['; break;
                case sfKeyRBracket:     code = ']'; break;
                case sfKeySemiColon:    code = ';'; break;
                case sfKeyComma:        code = ','; break;
                case sfKeyPeriod:       code = '.'; break;
                case sfKeyQuote:        code = '\''; break;
                case sfKeySlash:        code = '/'; break;
                case sfKeyBackSlash:    code = '\\'; break;
                case sfKeyTilde:        code = '~'; break;
                case sfKeyEqual:        code = '='; break;
                case sfKeyDash:         code = '-'; break;
                case sfKeySpace:        code = ' '; break;
                case sfKeyAdd:          code = '+'; break;
                case sfKeySubtract:     code = '-'; break;
                case sfKeyMultiply:     code = '*'; break;
                case sfKeyDivide:       code = '/'; break;
            }
        }
        /*case sfKeyLeft: sprintf(keyStr, "Left"); break;*/
        /*case sfKeyRight: sprintf(keyStr, "Right"); break;*/
        /*case sfKeyUp: sprintf(keyStr, "UP"); break;*/
        /*case sfKeyDown: sprintf(keyStr, "Down"); break;*/
    }//while

    return code;
}


void tk_write(float x, float y, const char * format, ...)
{
    char str[1000];
    va_list args;
    va_start( args, format );
    vsprintf(str, format, args);
    va_end( args );

    sfText_setString(_text, str);
    sfText_setCharacterSize(_text, _cell);
    sfVector2f pos = {x * _cell, y * _cell};
    sfText_setPosition(_text, pos);
    sfRenderWindow_drawText(_janela, _text, NULL);
}

void tk_clear(){
    sfRenderWindow_clear(_janela, sfBlack);
}

void tk_display(){
    sfRenderWindow_display(_janela);
}

void tk_draw(float x, float y, const char * format, ...)
{
    char str[1000];
    va_list args;
    va_start( args, format );
    vsprintf(str, format, args);
    va_end( args );

    int tam = strlen(str);
    int i = 0;
    for(i = 0; i < tam; i++){
        tk_char(x + i, y, str[i]);
    }
}

void tk_circle(float x, float y){
    sfVector2f pos = {x * _cell, y * _cell};
    sfCircleShape_setPosition(_circle, pos);

    sfColor cor_transp = sfColor_fromRGBA(100, 100, 100, 0);
    sfCircleShape_setFillColor(_circle, cor_transp);
    sfCircleShape_setOutlineColor(_circle, sfRed);
    sfCircleShape_setOutlineThickness(_circle, 1);
    sfRenderWindow_drawCircleShape(_janela, _circle, NULL);
}

void tk_char(float x, float y, char letra){
    char texto[2];
    tk_circle(x, y);
    texto[0] = letra;
    texto[1] = '\0';
    sfText_setString(_text, texto);
    sfText_setCharacterSize(_text, _cell);
    sfVector2f pos;
    pos.x =(x + 0.25) * _cell;
    pos.y =(y - 0.25) * _cell;
    sfText_setPosition(_text, pos);
    sfRenderWindow_drawText(_janela, _text, NULL);
}

void tk_end(){
    sfMusic_destroy(_som);
    sfText_destroy(_text);
    sfFont_destroy(_font);
    sfRectangleShape_destroy(_rect);
    sfRenderWindow_destroy(_janela);
}

void tk_play(const char * path){
    if(_som != NULL)
        sfMusic_destroy(_som);
    _som = sfMusic_createFromFile(path);
    sfMusic_play(_som);
}
