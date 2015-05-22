//main.c

#include "csf.h"
#include "aluno.h"
#include <stdio.h>
#include <SFML/Graphics.h>

void elem_pintar(const Elemento * el, int indice, char * nome){
    if(el != NULL){
        if(el->exists == True){
            //tk_color(el->color);
            tk_char(el->x, el->y, el->face);
            int offx = 0;
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

void show_cenario(Ambiente * amb){
    tk_write(0, 0, "andar(asdw) stay(.) kick(k) trap(,) wall(;) enemy(e) hadouken(h)");
    elem_pintar(amb->wall, 1, "wall");
    elem_pintar(amb->trap, 2, "trap");
    elem_pintar(amb->enemy, 3, "enemy");
    elem_pintar(amb->ball, 4, "ball");
    elem_pintar(amb->hero, 0, "hero");
}

void init_ambiente(Ambiente * amb){
    static Elemento hero;
    hero.x = 5;
    hero.y = 5;
    hero.xold = 5;
    hero.yold = 5;
    hero.face = '@';
    hero.color = 'w';
    hero.power = 10;
    hero.exists = True;
    static Elemento wall;
    static Elemento trap;
    static Elemento enemy;
    static Elemento ball;
    amb->hero = &hero;
    amb->wall = &wall;
    amb->trap = &trap;
    amb->enemy = &enemy;
    amb->ball = &ball;

    wall.exists = False;
    trap.exists = False;
    enemy.exists = False;
    ball.exists = False;
}


int main(){
    float cell = 20.0;
    int xcell = 50;
    int ycell = 30;

    tk_init(cell, xcell, ycell);
    Ambiente amb;
    init_ambiente(&amb);
    char tecla = ' ';

    elem_pintar(amb.hero, 0, "hero");
    while(tecla != 'q'){
        tk_clear();

        tecla = tk_peek();

        if(amb.hero->exists == False || amb.hero->power < 0){
            tk_write(0, 10, "Vai ser pato assim la na China");
            tk_write(0, 11, "Digite q para sair");
        }
        else{
            if(tecla !=  0)
                if(process_input(amb.hero, tecla, &amb))
                    process_interactions(&amb);
        }
        show_cenario(&amb);


        tk_display();
    }

    tk_end();
    return 0;
}
