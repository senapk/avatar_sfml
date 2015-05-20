#ifndef ALUNO_C
#define ALUNO_C

typedef enum { False, True } boolean;
typedef enum { Up = 0, Right = 1, Down = 2, Left = 3, Stay = 4 } direcao;

static const int max_linhas = 20;
static const int max_colunas = 30;

static const int hadouken_power = 10;

typedef struct{
    int x;          //a posicão atual x
    int y;          //a posição atual y
    char face;      //o char que será mostrado na tela
    char color;     //a cor que será impresso face, cores possíveis: rgbycmwk
    int power;      //a interpretação da variável força varia para cada elemento
    int xold;       //a posição x no último turno
    int yold;       //a posição y no último turno
    boolean exists; //se o Elemento existe, ou seja,
    //se ja foi criado e não foi destruído
}Elemento;

typedef struct{
    Elemento * hero;
    Elemento * enemy;
    Elemento * wall;
    Elemento * trap;
    Elemento * ball;
}Ambiente;

Elemento elem_create(int x, int y, char face, char color, int power);

void elem_move(Elemento * ent, direcao dir);

boolean process_input(Elemento * hero, char tecla, Ambiente * amb);
void process_interactions(Ambiente * amb);

void elem_kick(Elemento *elem, Elemento *wall);

void elem_create_wall(Elemento * hero, Elemento * wall);
void elem_create_trap(Elemento * hero, Elemento *trap);
void elem_create_enemy(Elemento hero, Elemento *enemy);

void elem_pursuit(Elemento hero, Elemento * enemy);

boolean elem_colide(Elemento um, Elemento dois);

void elem_colide_wall(Elemento *elem, Elemento wall);
void elem_colide_trap(Elemento *elem, Elemento *trap);
void elem_colide_enemy(Elemento * hero, Elemento enemy);


void update_move(Ambiente * amb);
void elem_hadouken(Ambiente * amb);

#endif
