/*
 * [Autor]
 * David Sena
 * sena.ufc@gmail.com
 *
 */

#ifndef TKIP_H
#define TKIP_H




/* Muda a cor da letra
 * r,g,b,y,c,m,k,w para cores claras
 * R,G,B,Y,C,M,K,W para cores escuras */
void tk_color(char color);



/* Escreve na posicao x,y o texto usando a sintaxe de printf
 * ex:  k_write(10,5,"oi");
 * ex:  k_write(12,6,"%d %c", idade, sexo); */
void tk_write(int x, int y, const char *format, ...);

/* Se houver alguma tecla no teclado ele retorna a tecla,
 * caso contrário, retorna 0  */
int tk_peek(void);

/* Trava e so retorna quando o usuario digitar uma tecla */
int  tk_wait(void);

/* Limpa o fundo */
void tk_clear();

/* Mostra a tela */
void tk_flush();

void tk_init();

void tk_end();


/* Faz o programa dormir por mseg, em milesegundos */
void tk_sleep(int msec);

/* Retorna um número aleatorio */
int  tk_rand();

/* Toca um wav*/
void tk_play(char *path);

/* Interrompe um wav que esteja tocando */
void tk_stop(char *path);

/* Retorna o vetor com as 8 cores */
const char * tk_get_colors();

void tk_get_dim(int *x, int *y);


#endif

/* EOF */
