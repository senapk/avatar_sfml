#include "aluno.h"
#include <stdlib.h>
#include <math.h>

/*
   Cria e retorna a um Elemento com os valores passados
   por parametro.
   inicialize existe com True, xold com x e yold com y;
   */
Elemento elem_criar(int x, int y, char face, char color, int forca){
    Elemento obj;
    obj.x = x;
    obj.y = y;
    obj.face = face;
    obj.color = color;
    obj.forca = forca;
    obj.existe = True;
    obj.xold = x;
    obj.yold = y;
    return obj;
}

/*
   Salva o x e o y em xold e yold.
   E muda o x e o y do objeto conforme a direção que ele andou
   Se direcao for Stay apenas atualize xold e yold.
   */
void elem_mover(Elemento * ent, direcao dir){
    ent->xold = ent->x;
    ent->yold = ent->y;
    if(dir == Left)
        ent->x -= 1;
    if(dir == Right)
        ent->x += 1;
    if(dir == Up)
        ent->y -= 1;
    if(dir == Down)
        ent->y += 1;
}

//Dada a tecla, chame a função elem_mover passando
//a direção correta por parametro.
//tecla  direcao    face
//a   -> esquerda   <
//d   -> direita    >
//w   -> cima       A
//s   -> baixo      V
//.   -> Stay       @
//Também altere a face do heroi para corresponder a nova direcao

//retorne True se a tecla passada foi válida e False

//Ignore a variável ambiente por enquanto, mais tarde você
//voltará aqui para melhorar essa função
boolean processar_entrada(Elemento * hero, char tecla, Ambiente * amb){
    switch(tecla){
        case('a'):
            elem_mover(hero, Left);
            hero->face = '<';
            return True;
        case('s'):
            elem_mover(hero, Down);
            hero->face = 'V';
            return True;
        case('d'):
            elem_mover(hero, Right);
            hero->face = '>';
            return True;
        case('w'):
            elem_mover(hero, Up);
            hero->face = 'A';
            return True;
        case('.'):
            elem_mover(hero, Stay);
            hero->face = '@';
            return True;
        case('h'):
            elem_kick(hero, amb->wall);
            elem_kick(hero, amb->enemy);
            elem_kick(hero, amb->trap);
            return True;
        case('1'):
            elem_criar_parede(hero, amb->wall);
            return True;
        case(','):
            elem_criar_trap(hero, amb->trap);
            return True;
        case('3'):
            elem_criar_enemy(*hero, amb->enemy);
            return True;
    }
    return False;
}

/*
    Se tecla for '1' então inicialize uma parede.
    Use o x, y e face do heroi e inicialize
    a parede embaixo dele.
    No nosso joguinho eh como se o heroi conseguisse fazer
    um monte de terra se elevar em baixo dele.

   Coloque a face da parede como #, existe como True
   e forca como 3, a cor coloque
   y que representa yellow. Voce pode usar o metodo
   elem_criar que você já contruiu.

   Para o heroi chame elem_mover(hero, stay) para
   atualizar a posicao do hero. Ou ele cairá da parede
   após você implementar a colisão.

   Observe que a função não recebe um tecla.
   Voce vai voltar na funcao processar entrada e se
   a tecla for '1', vai chamar a função elem_criar_parede
   e passar como parametro a parede.

   Se você abrir o aluno.h verá que amb contém
   ponteiros para todos os elementos do cenário.
   amb->wall contém um ponteiro para parede.

   Então na função processar_entrada eh só adicionar

   if(tecla == '1'){
       elem_criar_parede(hero, amb->wall);
       return true;
   }

*/
void elem_criar_parede(Elemento * hero, Elemento * wall){
    int x = hero->x;
    int y = hero->y;
    elem_mover(hero, Stay);
    *wall = elem_criar(x, y, '#', 'y', 3);
}

//retorne True se os dois elementos estão no mesmo lugar
boolean elem_colidiu(Elemento um, Elemento dois){
    //	return False; //default
    if (um.x == dois.x && um.y == dois.y)
        return True;
    return False;
}

/*
   use a funcao elem_colidiu. Se a nova posição do personagem
   eh a mesma da parede, então faça o personagem voltar para
   xold e yold. Faça isso apenas se a parede existir.

   Observe que se você não fizer o stay do personagem no criar
   parede o personagem vai ser derrubado assim que iniciar
   a parede. Consegue descobrir porque isso acontece?
   */
void elem_teste_colidiu_parede(Elemento *elem, Elemento wall){
    if(wall.existe)
        if(elem->x == wall.x && elem->y == wall.y){
            elem->x = elem->xold;
            elem->y = elem->yold;
        }
}

/*
   Verifique pelas posições se o hero está do lado do obstaculo
   e de frente pra ele.
   Se estiver e o obstaculo existir então:
   mova a obstaculo uma posicao pra frente na direção do golpe.
   remova um ponto da forca do obstaculo
   se obstaculo chegar a forca 0, então destrua-o

   destruir a parede é colocar wall->existe = False.

   Por ultimo, vá até a função processar_entrada e
   se a tecla for 's' então chame a função elem_kick
   passando o heroi e a parede. Perceba que a variável
   Ambiente contém todos os elementos do jogo. Você
   vai fazer assim:
   if(tecla == 's')
   elem_kick(hero, amb->wall);

   use a função elem_mover para mover a parede

*/
void elem_kick(Elemento *hero, Elemento *obst){
    int dx = hero->x - obst->x;
    int dy = hero->y - obst->y;
    boolean acertou = True;
    if((abs(dx) == 1 && abs(dy) == 0) || (abs(dx) == 0 && abs(dy) == 1)){
        if(dx == 1 && hero->face == '<'){
            elem_mover(obst, Left);
        }
        else if(dx == -1 && hero->face == '>'){
            elem_mover(obst, Right);
        }
        else if(dy == 1 && hero->face == 'A'){
            elem_mover(obst, Up);
        }
        else if(dy == -1 && hero->face == 'V'){
            elem_mover(obst, Down);
        }
        else{
            acertou = False;
        }
        if(acertou){
            obst->forca -= 1;
            if(obst->forca == 0){
                obst->existe = False;
            }
        }
    }

}

/*
   Se tecla for ',' então inicialize a armadilha
   na posicao atras do heroi e faca o hero passar esse
   turno parado: elem_mover(hero, Stay);

   Lembre de chamar essa funcao no processar entrada,
   se a tecla digitada for ','. Faça como fez
   no criar_parede.

   Coloque a face da trap como '!', existe como True,
   e forca como aleatorio entre 1 e 10, a cor coloque
   'm' que representa magenta. Voce pode usar o metodo
   elem_criar que você já contruiu.
   */
void elem_criar_trap(Elemento * hero, Elemento * trap){
    int x = hero->x;
    int y = hero->y;
    int f = rand() % 9 + 1;
    elem_mover(hero, Stay);
    if(hero->face == '>'){
        *trap = elem_criar(x - 1, y, '!', 'w', f);
    }else if(hero->face == '<'){
        *trap = elem_criar(x + 1, y, '!', 'w', f);
    }else if(hero->face == 'A'){
        *trap = elem_criar(x, y + 1, '!', 'w', f);
    }else if(hero->face == 'V'){
        *trap = elem_criar(x, y - 1, '!', 'w', f);
    }
}

/*
   Como pode perceber nossa armadilha não faz nada.
   Que tal prender o personagem na trap até a trap
   se quebre.

   Observe que quando o heroi entra na posicao da
   trap, nada acontece. O problema é quando ele quiser
   sair dela. Na parede, impedimos que ele assumisse
   os novos valores de x e y. Na trap vamos fazer a
   mesma coisa. Se os valores antigos de x e y forem
   iguais os da trap, impeça-o de andar, faca x assumir
   xold e y assumir yold.

   Lembre de verificar se a trap existe e o elemento também.

   Cada vez que ele tentar sair da trap diminua a força
   dela de 1 e quando chegar a zero quebre a trap.
   Também diminua a forca do elemento de 1.

   Observe que estamos usando elem ao inves de heroi.
   É porque iremos usar nossa trap tanto no heroi quanto
   em nosso futuro inimigo.
   */
void elem_teste_preso_trap(Elemento *elem, Elemento *trap){
    if(trap->existe && elem->existe)
        if(elem->xold == trap->x && elem->yold == trap->y){
            elem->x = elem->xold;
            elem->y = elem->yold;
            trap->forca -= 1;
            elem->forca -= 1;
            if(trap->forca == 0)
                trap->existe = False;
        }
}


/*
   Crie um inimigo se a tecla for '3'
   face = 'E'
   forca entre 50 e 100
posicao: num raio de até 5 casas do heroi.
cor = 'r'

Adicione o processamento da tecla 3.


Perceba que sua função hadouken funciona com qualquer elemento
Vá lá na função processar_entrada e chame o hadouken também para
o enemy. Agora você pode empurrar um inimigo que não anda.
*/
void elem_criar_enemy(Elemento hero, Elemento *enemy){
    int x = rand() % 11 - 5 + hero.x;
    int y = rand() % 11 - 5 + hero.y;
    int f = rand() % 51 + 50;
    *enemy = elem_criar(x, y, 'E', 'c', f);
}

/*
   O objetivo dessa função eh fazer o inimigo perseguir
   o heroi. Implemente como achar mais divertido.
   Voce pode fazer o inimigo sempre se mover
   na direcao x e y do heroi inclusive nas verticais
   pode adicionar algum fator divertido aleatorio,
   te vira.

   Você não precisa usar a funcao elem_mover, mas tem
   que garantir que em enemy, xold e yold terão os
   valores da ultima posicao valida.

   Um algoritmo legal eh :
   if ex > hx:
   ex--
   elif ex < hx:
   ex++
else:
aleatoriamente escolha ir pra cima ou pra baixo

*/
void elem_perseguir(Elemento hero, Elemento * enemy){
    enemy->xold = enemy->x;
    enemy->yold = enemy->y;

    if(enemy->x < hero.x)
        enemy->x += 1;
    else if (enemy->x > hero.x)
        enemy->x -= 1;
    else{
        if(rand()%2 == 0)
            enemy->x += 1;
        else
            enemy->x -= 1;
    }
    if(enemy->y < hero.y)
        enemy->y += 1;
    else if(enemy->y > hero.y)
        enemy->y -= 1;
    else{
        if(rand()%2 == 0)
            enemy->y += 1;
        else
            enemy->y -= 1;
    }
}

/*
   Se o inimigo te pegar, diminua 1 na vida do heroi
   e arremesse o heroi em alguma direção do mapa.
   Os inimigos de filmes sempre fazem isso com os herois,
   dão uma porrada e jogam ele pra longe
   Use a funcao elem_colidiu()
   Lembre de fazer isso apenas se o inimigo existir
   */
void elem_enemy_colide(Elemento * hero, Elemento * enemy){
    if(!enemy->existe)
        return;
    if(elem_colidiu(*hero, *enemy)){
        hero->forca -= 1;
        hero->x = rand()%max_colunas;
        hero->y = rand()%max_linhas;
    }
}


/*
   Nosso heroi eh fugitivo da prisão, ele tem uma bola de ferro
   com uma corrente presa ao seu braço.
   Ele usa essa bola para bater nos Elementos do cenário.
   O tamanho da corrente eh igual a força do nosso hero.

   Ele joga a bola na direção para a qual ele está olhando.
   Se existir algum elemento no caminho da bola a bola bate
   no elemento e cai, e o elemento é projetado pra trás na
   distancia que falta da bola. Exemplo o hero com forca
   5 sem nenhum obstaculo a frente.

   >

   Ele joga o hadouken e a bola fica assim:

   >....o

   Coloquei os pontinhos só pra vocês sacarem a distancia da
   bola.

   Se tiver uma parede a dois objetos de distancia o tiro
   fica assim:

   >..#
   >..o.#

   A bola bate, para e a parede é projetada na distancia que falta.

   Essa é a função mais difícil do jogo. Ela vai te dar um
   bocadinho de trabalho mas prometo que vai valer a pena.
   Nosso heroi eh fugitivo da prisão, ele tem uma bola de ferro
   com uma corrente presa ao seu braço.
   Ele usa essa bola para bater nos Elementos do cenário.
   O tamanho da corrente eh igual a força do nosso hero.

   Ele joga a bola na direção para a qual ele está olhando.
   Se existir algum elemento no caminho da bola a bola bate
   no elemento e cai, e o elemento é projetado pra trás na
   distancia que falta da bola. Exemplo o hero com forca
   5 sem nenhum obstaculo a frente.

   >

   Ele joga o hadouken e a bola fica assim:

   >....o

   Coloquei os pontinhos só pra vocês sacarem a distancia da
   bola.

   Se tiver uma parede a dois objetos de distancia o tiro
   fica assim:

   >..#
   >..o.#

   A bola bate, para e a parede é projetada na distancia que falta.

   Essa é a função mais difícil do jogo. Ela vai te dar um
   bocadinho de trabalho, mas prometo que vai valer a pena.

*/


