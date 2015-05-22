#ifndef CSF_H
#define CSF_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdarg.h>

//inicia uma janela com uma tamanho de celula e a quantida
sfRenderWindow * tk_init(int _cell, int sizeX, int sizeY);
void tk_end();

//pega um codigo asc de tecla lowercase, numero e pontuacao
//ou 0
int tk_peek();

int tk_is_open();

void tk_display();
void tk_clear();
//void tk_color(char c)

void tk_rect(float x, float y, sfColor cor);

//desenha o texto uma letra por celula
void tk_draw(float x, float y, const char * format, ...);
//escreve um texto
void tk_write(float x, float y, const char * format, ...);
//coloca uma letra dentro de uma celula
void tk_char(float x, float y, char letra);

void tk_play(const char * path);

#endif // CSF_H
