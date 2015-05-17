#ifndef ALUNO_C
#define ALUNO_C

typedef enum { False, True } boolean;
typedef enum { Up, Right, Down, Left, Stay } direcao;

static const int max_linhas = 20;
static const int max_colunas = 30;

typedef struct{
	int x;
	int y;
	char face;
	char color;
	int forca;
	int xold;
	int yold;
	boolean existe;
}Elemento;

typedef struct{
	Elemento * hero;
	Elemento * enemy;
	Elemento * wall;
	Elemento * trap;
}Ambiente;

Elemento elem_criar(int x, int y, char face, char color, int forca);


void elem_mover(Elemento * ent, direcao dir);


boolean processar_entrada(Elemento * hero, char tecla, Ambiente * amb);

void elem_criar_parede(Elemento * hero, Elemento * wall);

boolean elem_colidiu(Elemento um, Elemento dois);

void elem_teste_colidiu_parede(Elemento *elem, Elemento wall);

void elem_kick(Elemento *elem, Elemento *wall);

void elem_criar_trap(Elemento * hero, Elemento *trap);

void elem_teste_preso_trap(Elemento *elem, Elemento *trap);

void elem_criar_enemy(Elemento hero, Elemento *enemy);

void elem_perseguir(Elemento hero, Elemento * enemy);

void elem_enemy_colide(Elemento * hero, Elemento * enemy);

#endif
