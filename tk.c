/*
 * [Autor]
 * David Sena
 * sena.ufc@gmail.com
 *
 */

#define _POSIX_C_SOURCE	199309L
#include <stdlib.h>//rand e srand
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>//srand e k_sleep
#include <time.h>//k_sleep
#include <curses.h>


void tk_color(char color)
{
    switch(color)
    {

        case 'r': attron(COLOR_PAIR(1)); break;
        case 'g': attron(COLOR_PAIR(2)); break;
        case 'b': attron(COLOR_PAIR(3)); break;
        case 'y': attron(COLOR_PAIR(4)); break;
        case 'm': attron(COLOR_PAIR(5)); break;
        case 'c': attron(COLOR_PAIR(6)); break;
        case 'w': attron(COLOR_PAIR(7)); break;
        case 'k': attron(COLOR_PAIR(8)); break;
    }
}

const char * tk_get_colors(){
    static const char *colors = "rgbycmkw";
    return colors;
}

void tk_clear(){
    clear();
}

void tk_write(int x, int y, const char *format, ...)
{
    //corrigindo alinhamento
//    y = y + 2;
//    x = x + 1;

    char str[1000];   \
    va_list args;     \
    va_start( args, format );\
    vsprintf(str, format, args);\
    va_end( args );

    mvprintw(y, x, str);
}


int tk_peek(void) {
	nodelay(stdscr, TRUE);
	char ch = getch();
	nodelay(stdscr, FALSE);
	if (ch == ERR)
        return 0;
	return ch;
}

int tk_wait(void){
	return getch();
}

void tk_sleep(int msec)
{
    puts(" ");
    struct timespec interval;
    struct timespec remainder;
    interval.tv_sec = msec / 1000;
    interval.tv_nsec = (msec % 1000) * (1000 * 1000);
    nanosleep(&interval, &remainder) ;
    //usleep(1000*msec);
}

int tk_rand()
{
    static int init = 1;
    if(init) {
        init = 0;
        srand(time(NULL));
    }
    return rand();
}

void tk_play(char *path){
    char c[500];
    sprintf(c,"aplay %s 2>/dev/null 1>/dev/null&",path);
    system(c);
}

void tk_mp3_stop(char *path){
    char c[500];
    sprintf(c,"ps aux  | grep \"aplay %s\" |head -1|  awk '{ print $2; }' | xargs kill -9 2>/dev/null 1>/dev/null&",path);
    system(c);
}

void tk_flush(){
	refresh();
}

void tk_init(){
  initscr();
  if(has_colors() == FALSE){
    endwin();
		printf("Seu terminal nao suporta cores\n");
		exit(1);
	}
  start_color();
  cbreak();
  noecho();
  curs_set(0);
  scrollok(stdscr, TRUE);


	init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  init_pair(8, COLOR_BLACK, COLOR_BLACK);
}

void tk_end(){
	endwin();
}

void tk_dim(int *x, int *y){
	int max_y;
	int max_x;
	getmaxyx(stdscr, max_y, max_x);
	*x = max_x;
	*y = max_y;
}
