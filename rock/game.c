//main.c

#include "tk.h"
#include "aluno.h"
#include <stdio.h>
#include <ncurses.h>

void elem_pintar(const Elemento * el, int indice, char * nome){
    if(el != NULL){
        if(el->exists == True){
            tk_color(el->color);
            tk_write(el->x, el->y, "%c", el->face);
            int offx = max_colunas;
            int offy = max_linhas;
            tk_write(offx + 6 * indice, offy + 0, nome);
            tk_write(offx + 6 * indice, offy + 1, "ST=%d", el->power);
            tk_write(offx + 6 * indice, offy + 2, "x=%d", el->x);
            tk_write(offx + 6 * indice, offy + 3, "y=%d", el->y);
            tk_write(offx + 6 * indice, offy + 4, "x_=%d", el->xold);
            tk_write(offx + 6 * indice, offy + 5, "y_=%d", el->yold);
        }
    }
}

int main(){
    tk_init();
    Ambiente amb = {NULL, NULL, NULL, NULL, NULL};
    Elemento hero = elem_create(5, 5, '@', 'w', 4);
    Elemento wall;
    Elemento trap;
    Elemento enemy;
    Elemento ball;
    amb.hero = &hero;
    amb.wall = &wall;
    amb.trap = &trap;
    amb.enemy = &enemy;
    amb.ball = &ball;

    wall.exists = False;
    trap.exists = False;
    enemy.exists = False;
    ball.exists = False;
    char tecla = ' ';

    elem_pintar(amb.hero, 0, "hero");
    while(tecla != 'q'){
        tecla = tk_wait();
        if(process_input(&hero, tecla, &amb)){
            clear();
            refresh();

            process_interactions(&amb);

            //funcoes de pintura
            elem_pintar(amb.wall, 1, "wall");
            elem_pintar(amb.trap, 2, "trap");
            elem_pintar(amb.enemy, 3, "enemy");
            elem_pintar(amb.ball, 4, "ball");
            elem_pintar(amb.hero, 0, "hero");
        }
    }
    tk_end();
    return 0;
}
