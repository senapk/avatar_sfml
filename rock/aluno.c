#include "aluno.h"
#include <stdlib.h>
#include <math.h>


/*
Requisitos:

    Como requisitos desse trabalho você deve conhecer a linguagem C. Também
    deve ter algum contato com funções, enum, structs e ponteiros. Vamos usar
    apenas isso. Você não vai precisar ou usar de laços, vetores ou matrizes.

Objetivo:

    O objetivo desse trabalho é implementar um pequeno jogo em TURNOS com
    um hero, um inimigo, um obstáculo, uma armadilha, um chute e um ataque
    mágico.

Instruções:

    Você terá todas as instruções função a função. Mas as instruções não
    são obrigações. Você pode fazer suas alterações e testar o que acontece
    com o jogo.

    Você apenas vai precisar editar um arquivo, esse daqui, o "aluno.c".
    Fora isso, você precisará consultar o arquivo "aluno.h". É no aluno.h
    que estão as definições das structs utilizadas.

    Se você encontrar alguma linha como (void) algo, pode remover. Ela só
    foi adicionada para não ficar aparecendo os warnings de variável não
    utilizada. Ela não faz absolutamente nada.

Tipos de dados:

    Vamos utilizar 2 enums e 2 structs.
    Como c não possui tipo bool pro default, vamos criar uma enum boolean
    com os tipos True e False para simular o comportamento de um bool.

    Vamos usar também a enum direcao para definir o movimento. Se o elemento
    do cenário se move pra direita, esquerda, cima, baixo, ou fica parado.

    Temos a struct Elemento que define os atributos dos elementos do cenário.
    O herói, o inimigo, a parede, a armadilha e o hadouken são abstraídos
    como Elementos, mesmo que não usemos todas as variáveis em alguns deles.
    Dê uma olhada na struct Elemento para entender o que cada variável significa.

    Por fim temos um Ambiente. O Ambiente contém todos os Elementos do nosso
    jogo.

Orientações:

    Precedendo cada função você encontrará as seguintes seções:

        Objetivo:

            Descreve o objetivo da função.

        Resultado:

            Descreve o que deve acontecer no jogo se a função estiver
            corretamente implementada.

        Função:

            Descreve qual o algoritmo a ser implementado na função.

        Retorno:

            Descreve o tipo de retorno se existir.

        Flashback:

            Descreve quais outros lugares do código você deverá alterar para
            obter o comportamento desejado. Normalmente você irá adicionar
            chamada de funções no processamento de entrada.

        Ajuda:

            Vai lhe fornecer algumas dicas pra você que está com dificuldade.


    Bom trabalho.
*/

//##############################################################################

/*                           _MOVE_
Objetivo:

    Implementar a função que fará os elementos do seu cenário se moverem.

Resultado:

    Essa função será utilizada em quase todo seu código. Quando você implementar
    _MOVE_ e _INPUT_, será capaz de movimentar seu hero com ASDW. nas
    quatro direções.

Função:

    Utilizaremos xold e yold como as posições do elemento no último turno. Eles
    nos serão úteis na hora de processarmos as colisões do sistema.

    A primeira coisa a fazer é colocar os valores de x e y em xold e yold.

    Então, de acordo com a direção passada por parametro, altere os valores de x
    e y do elemento el. Lembre que x cresce pra direita e y cresce pra baixo.

    Como el é um ponteiro você acessa os elementos utilizando ->

Ajuda:

    Pra lhe ajudar eu já salvei xold e já processei a direcao Left.

*/
void elem_move(Elemento * el, direcao dir){

    el->xold = el->x;
    if(dir == Left)
        el->x -= 1;
}

/*                           _INPUT_
Objetivo:

    Implementar a função que tratará a entrada do usuário.

Resultado:

    Essa função agora tratará a entrada dos direcionais 'ASDW.', após ela você
    já deverá ser capaz de mover seu hero pela tela e verá a face dele mudando.

Função:

    Você receberá o hero, a tecla digitada e o ambiente. Não se preocupe com o
    ambiente agora. Você voltará a essa função no futuro para utilizá-lo.

    Dada a tecla, altere a face do hero. Também chame a função elem_move
    passando o hero e a direção correta por parametro. Quando ele fica
    parado(Stay) ele não muda de face.

        tecla  direcao    face
        a      Left       <
        d      Right      >
        w      Up         A
        s      Down       V
        .      Stay

Retorno:

    Se a tecla digitada levou a uma ação válida retorne True. Se não, retorne
    False.

Ajuda:

    Pra lhe ajudar eu já processei a tecla 'a'. Sugiro trocar o if por um
    switch.
*/

boolean process_input(Elemento * hero, char tecla, Ambiente * amb){
    (void) amb;
    if(tecla == 'a'){
        elem_move(hero, Left);
        hero->face = '<';
        return True;
    }
    return False;

}

/*                           _CREATE_

Objetivo:

    Implementar a função que inicia e retorna um Elemento dados os parametros.

Resultado:

    Ao terminar as funções _CREATE_ e _CREATE_WALL_ você será capaz de criar
    uma parede de terra sob seus pés.

Função:

    Crie uma variável Elemento. Atribuia a ela os valores passados por parametro.
    Após isso retorne o Elemento construído.
    As variáveis que faltaram passar por parametro defina assim:
        exists = True
        xold = x
        yold = y

Ajuda:

    Estou criando e retornando um Elemento vazio.

*/
Elemento elem_create(int x, int y, char face, char color, int power){
    (void) x;
    (void) y;
    (void) face;
    (void) color;
    (void) power;

    Elemento obj;
    return obj;

}

/*                           _CREATE_WALL_

Objetivo:

    Criar uma parede de terra debaixo dos pés do hero. Você já viu os
    dobradores de terra do desenho Avatar. Pois é, nosso hero faz desse jeito.

Resultado:

    Ao final dessa função você será capaz de criar uma parede de terra e
    enxergá-la, mas só quando fizer _COLIDE_WALL que ela se tornará um
    obstáculo real pro seu hero.

Função:

    Use a função elem_create para criar uma parede com essas variáveis:
        posicao: as mesmas do seu hero
        face = #
        power = 10
        cor = 'y', para nossa parede ficar amarela

    Entretanto, nosso hero vai passar esse turno contruindo a parede, então você
    deve passá-lo para função elem_move na direção Stay. Isso vai atualizará a
    posição old do nosso hero nesse turno que ele ficou parado.

    Observe que aqui, tanto o hero quanto wall são passados por endereço porque
    ambos serão alterados. Quando NÃO formos alterar a struct ela será passada
    por cópia.

Flashback:

    Pra função funcionar ela precisa ser chamada em algum lugar. Voce vai voltar
    na funcao processar entrada e se a tecla for ';', vai chamar a função
    elem_create_wall e passar como parametro o hero e a parede.

Ajuda:

    Se você abrir o aluno.h verá que Amb contém ponteiros para todos os
    elementos do cenário. Em process_input amb->wall contém um ponteiro para
    parede.

    Na função process_input eh só adicionar
       elem_create_wall(hero, amb->wall);
    caso a tecla seja ';'

Futuro:

    Depois de implementar o _COLIDE_WALL_, volte aqui e tire o Stay e veja
    o hero caindo da parede. Tente descobrir porque isso acontece.

*/

void elem_create_wall(Elemento * hero, Elemento * wall){
    (void) hero;
    (void) wall;
}

/*                           _COLIDE_

Objetivo:

    Verificar se dois obstáculos estão colidindo.

Resultado:

    Essa função será utilizada nas demais funções de colisão do jogo.

Função:

    Se os dois elementos tiverem o mesmo x e mesmo y então eles estão
    colidindo. Retorne True se estiverem e False caso não estejam.

    Observe que como não temos intenção de alterar nenhum valor dos
    elementos, estes são passados por cópia.

Ajuda:

    Como não são ponteiros você utiliza um.x para obter o x do elemento
    um.

Futuro:

    Existe uma forma de passar um ponteiro e evitar que a estrutura seja
    alterada. Mais tarde pesquise sobre ponteiros contantes em c.
        https://goo.gl/ozXU4m

*/
boolean elem_colide(Elemento um, Elemento dois){
    (void) um;
    (void) dois;
    return False;

}

/*                           _COLIDE_WALL_

Objetivo:

    Impedir um elemento que se mova de atravessar paredes.

Resultado:

    Depois dessa função, seu hero não conseguirá mais atravessar paredes.

Função:

    As funções de colisão acontecem depois das funções de movimento. Primeiro
    deixamos o elemento tentar se mover, depois testamos as colisões e se o
    movimento foi inválido, o fazemos voltar à última posição válida que está
    guardada em xold e yold. Ou seja, se o hero anda pra posição de uma parede,
    essa função de colisão o fará voltar para última posição válida.

    Use a funcao elem_colide para verificar a colisão entre o elem e a wall. Se
    a nova posição do elemento é a mesma da parede, então faça o elemento voltar
    para xold e yold. Faça isso APENAS se ambos a parede e o elemento EXISTIREM.
    Se os dois elementos tiverem o mesmo x e mesmo y, então eles estão
    colidindo.

Ajuda:

    Observe que elem é passado por endereço porque iremos alterar sua posição
    se houver colisão, mas wall é passado por cópia pois não queremos alterar
    wall. Lembre de verificar se ambos existem.

*/

void elem_colide_wall(Elemento *elem, Elemento wall){
    (void) elem;
    (void) wall;
}

/*                           _INTERACTIONS_

Objetivo:

    Nesta função você vai colocar todas as funções de interação entre elementos
    do jogo. As funções que são iniciadas por teclas como andar, ou lançar
    armadilhas são chamadas no process_input. As funções que verificam as
    colisões entre hero e parede, hero e trap, inimigo e parede, hero e
    inimigo serão chamadas aqui.

Resultado:

    Já está aqui implementada a chamada da interação entre o hero e a parede.
    Por enquanto você não precisa fazer nada. Mais tarde, conforme for
    adicionando os novos elementos e implementando as novas interações, você
    será orientado a voltar aqui e colocar as chamadas das funções.

Ajuda:

    Observe o protótipo de elem_colide_wall. Recebe um ponteiro pra Elemento
    na primeira variável e um Elemento na segunda. A função process_interactions
    recebe um ponteiro pra Ambiente. Para obter os dados de amb utilizamos então
    ->, amb->hero nos retorna um ponteiro pra Elemento. Ótimo, é o que queremos.
    amb->wall também nos retorna um ponteiro, para obter o Elemento desse
    ponteiro adicionamos o * na frente.
*/
void process_interactions(Ambiente * amb){

    //funcoes de movimento


    elem_colide_wall(amb->hero, *amb->wall);

    //funcoes que consolidam movimento dos personagens


}


/*                           _KICK_

Objetivo:

    O objetivo dessa função é que seu hero seja capaz de chutar os elementos do
    cenário.

Resultado:

    Após o fim dessa operação você será capaz de chutar e mover a parede que é
    por enquanto o único outro elemento criado. Também será capaz de destruir a
    parede se a power dela chegar a zero.

Função:

    Seu hero irá interagir com um obstáculo qualquer. Se ambos existirem E seu
    hero estiver ao lado do obstáculo e virado para ele, então mova o obstáculo
    uma posição na direção do chute e remova 1 ponto da força do obstáculo. Se a
    força chegar a zero, então atribua False à variável existe do obstáculo.
    O seu hero também passará esse turno no mesmo lugar então atualize sua
    posição usando Stay.

Flashback:

    Sua função mesmo implementada não fará nada a não ser que seja chamada pelo
    método process_input.

    Vá até a função process_input e se a tecla for 'k' chame a função
    elem_kick passando o hero e a parede. Perceba que a variável Ambiente amb
    contém todos os elementos do jogo. Você vai fazer assim:

    if(tecla == 'k')
        elem_kick(hero, amb->wall);

Ajuda:

   Destruir a parede é colocar wall->exists = False. Use a função elem_move
   para mover a parede. Você pode começar o algoritmo assim: Se hero na direita
   da parede e virado para esquerda...

*/

void elem_kick(Elemento *hero, Elemento *obst){
    (void) hero;
    (void) obst;
}

/*                           _CREATE_TRAP_

Objetivo:

    O objetivo dessa função é que seu hero seja capaz de criar uma armadilha
    que irá prender qualquer elemento que nela pisar.

Resultado:

    Ao final dessa função você verá uma armadilha sendo criada atrás do herói,
    mas a armadilha só vai FUNCIONAR quando você implementar a colisão na
    próxima função.

Função:

    Se tecla for ',' então inicialize a armadilha na posicao atrás do hero e
    faca o hero passar esse turno parado: elem_move(hero, Stay);

    Variáveis:
        face  = !
        power = 5 a 10
        posição = atrás do hero. Analise sua posição e direção.
        cor = m (magenta)

    Use o método elem_create que você implementou.

Flashback:

    Volte na função process_input e se a tecla digitada for ',', chame a
    função elem_create_trap passando os parametros correspondentes. Faça como fez
    na função elem_create_wall.

    Vá na função process_input e caso adicione o kick para avaliar a trap
    também caso o usuário digite 'k'.

Ajuda:

    Para usar a função rand() você precisa dar o include na biblioteca
    <stdlib.h>. Se não encontrar no começo desse arquivo, faça o include.
    Descubra como fazer o rand gerar um número entre dois inteiros x e y.

*/

void elem_create_trap(Elemento * hero, Elemento * trap){
    (void) hero;
    (void) trap;
}

/*                           _COLIDE_TRAP_

Objetivo:

    Implementar uma função que faça qualquer elemento que pisar na trap, nela
    ficar preso perdendo força até que a trap quebre.

Resultado:

    Após implementar essa função seu personagem quando passar pela trap vai
    ficar preso tantos turnos quanto for a força da trap e a cada turno ambos
    vão perder um ponto de força.

Função:

    As funções de colisão acontecem depois das funções de movimento. Elas
    consolidam as tentativas de movimento. Então se no último turno, o hero
    estava na trap, mesmo que ele tenha se movido a posição old ainda é igual a
    posição da trap.

    Então, se os valores antigos de x e y forem iguais os da trap, impeça-o de
    andar, faca x assumir xold e y assumir yold.

    Lembre de verificar se ambos os elementos existam.

    A cada colisão diminua um na força de ambos em um e se algum chegar em força
    0 atribua exists para False.

Flashback:

    Vá na função process_interactions e adicione a colisão entre o hero e a
    trap.

Ajuda:

    Te vira!
*/
void elem_colide_trap(Elemento *elem, Elemento *trap){
    (void) elem;
    (void) trap;
}

/*                           _CREATE_ENEMY_

Objetivo:

    Essa função visa criar um inimigo, que futuramente virá a perseguir nosso
    hero.

Resultado:

    Nosso inimigo sofrerá as mesmas interações com paredes, armadilhas e chutes.
    Observe que nossas funções foram feitas pensando em um elemento qualquer e
    o inimigo também é um elemento. Você vai conseguir chutar um inimigo que não
    se move, mas qual a graça disso? Também terá deixado pronto as colisões do
    inimigo com wall e trap, mas se nosso inimigo ainda não se move, qual a
    graça disso? Não se preocupe, na função que vem, vamos implementar nossa
    perseguição.

Função:

    Se for digitada a tecla 'e' inicie um inimigo com os seguintes dados:
        face = 'E'
        power entre 50 e 100
        posicao aleatória num raio de até 5 casas do hero.
        cor = 'r'

Flashback:

    Vá na função process_input e chame a funcao elem_create_enemy com os
    parametros corretos caso o jogador tecle 'e'. Também chame a função
    elem_kick entre o hero e o enemy. Agora seu hero pode chutar o enemy.

    Vá na função process_interactions e adicione as interações entre enemy e
    trap e entre enemy e parede.

Ajuda:

    Você pode fazer um rand para posição do enemy que varie de hero.x - 5, até
    hero.x + 5. A linha
        rand() % 11 - 5 + hero.x;
    pode gerar esse valor pra você.

*/
void elem_create_enemy(Elemento hero, Elemento *enemy){
    (void) hero;
    (void) enemy;
}


/*                           _PURSUIT_

Objetivo:

    O objetivo dessa função é fazer o enemy perseguir seu hero pra onde ele for.

Resultado:

    Ao final dessa função o enemy estará perseguindo seu hero. Ficará preso se
    pisar em uma armadilha e não conseguirá atravessar paredes.

Função:

    Vou dar uma sugestão de implementação. Você pode tentar e testar várias
    outras que imaginar. Combinar teleportação, saltos, etc.

    Uma simples porém eficaz é:
    Voce pode fazer o inimigo sempre se mover
    na direcao x e y do hero inclusive nas verticais
    pode adicionar algum fator divertido aleatorio,
    te vira.

    Você não precisa usar a funcao elem_move, mas tem
    que garantir que em enemy, xold e yold terão os
    valores da ultima posicao valida.

    Um algoritmo legal é:
        Se o inimigo estiver a esquerda do hero:
            faça ir 1 para direita
        senão se estiver a direita:
            faça ir 1 para esquerda
        se estiver no mesmo x, então escolha aleatóriamente esq ou direita

    Faça a mesma coisa para o y.

Flashback:

    Vá na função process_interactions e adicione essa função entre o hero e o
    enemy.

Ajuda:

    Só uma uma ajudinha. Essa é uma interação de movimento. É importante que na
    função process_interactions ela esteja antes das funções de colide, pois
    estas vão impedir que o enemy se mova pra posições inválidas.

    Lembre de guardar em xold, yold a última posição válida do enemy.

*/
void elem_pursuit(Elemento hero, Elemento * enemy){
    (void) hero;
    (void) enemy;
}


/*                           _PURSUIT_

Objetivo:

    Vamos implementar o que acontece quando o enemy consegue alcançar o hero.

Resultado:

    Ao final dessa função, toda vez que o enemy alcançar o hero, hero vai perder
    força e será arremessado aleatoriamente para qualquer lugar da tela.

Função:

   Se o inimigo alcançar o hero, diminua 1 na power do hero e arremesse o hero em alguma
   direção do mapa. Os inimigos de filmes sempre fazem isso com os heros, dão
   uma porrada e jogam ele pra longe. Use a funcao elem_colide() para testar a
   colisão. Configure xold e yold também para a nova posição.

   Lembre de verificar se ambos os Elementos existem. Se o power do hero chegar
   a 0, coloque exists como False.

Flashback:

    Vá em process_interactions e adicione a colisão entre hero e enemy depois
    das colisões de movimento como wall and trap.

Ajuda:

    Em aluno.h você encontrará duas variáveis, max_colunas e max_linhas. Elas
    definem o tamanho máximo do ambiente. Ao colidir gere novos x e y entre 0 e
    essas variáveis max.

*/


/*
   */
void elem_colide_enemy(Elemento * hero, Elemento enemy){
    (void) hero;
    (void) enemy;
}

/*                           _UPDATE_MOVE_

Objetivo:

    Vamos evitar que seu hero saia do cenário.

Resultado:

    Quando seu hero tentar se mover para além dos limites do cenário, é como se
    ele ficasse parado e todos os outros elementos se movessem na direção
    oposta.

Função:

    Nessa função você recebe o ambiente. Seu objetivo é analisar a posição do
    hero. Se ele estiver a direita de max_colunas, faça todos os elementos irem
    pra esquerda. Atualize tanto a posição atual como as old.

Flashback:

    Vá em process_interactions e adicione essa função depois de colisão e depois
    de pursuit pois ela é apenas uma atualização da visão do jogo.

Ajuda:

    Aqui é a primeira vez que vetores nos seriam muito úteis. Mas nosso acordo é
    que esse trabalho não use vetores. Mas se você quiser montar seu próprio
    vetor é problema seu. Você pode fazer assim:

    Elemento * vet[5] = {amb->hero, amb->wall, amb->enemy, amb->trap, amb->ball};

    Depois você faz um laço pra atualizar a posição de todos. Mas se não sabe
    vetores, faça na mão. Você também pode criar uma função auxiliar do tipo
    move_update(Elemento * el, direcao dir) que aplica a mudança de movimento
    tanto em x e y como em xold e yold.

    Você acessa o x de hero usando amb->hero->x
*/


void update_move(Ambiente * amb){
    (void) amb;
}

/*                           _HADOUKEN_

Objetivo:

    Implementar um ataque mágico que interaja com múltiplos Elementos. Essa
    daqui é nível Hacker, faça se tiver vontade e coragem.

Resultado:

    Após essa função você conseguirá lançar uma bola de aço que irá projetar
    os elementos da função como recuperá-la.

Função:

    Você pode implementar o hadouken como bem entender: fazendo o teleporte do
    elemento, fazendo life-steel, projetando o dobro da distância, matando
    instantâneamente, lançando uma onde de força que acerta elementos em todos
    os lados, etc.

    Na minha sugestão, o nosso hero eh fugitivo da prisão. Ele tem uma bola de
    ferro com uma corrente presa ao seu braço. Tipo o Kratos ou o Andrômeda. Ele
    usa essa bola para bater nos Elementos do cenário. O tamanho da corrente é
    definida pela constante hadouken_power em aluno.h.

    Quando lançada, a bola vai na direção para onde o hero está olhando até a
    distância da corrente. Se existir algum elemento no caminho da bola, a bola
    o lança pra trás power posições.


    Exemplo 1: power = 5 sem nenhum obstáculo.
    >....o

    Coloquei os pontinhos só pra vocês sacarem a distancia da bola.

    Exemplo 2: power = 5, um inimigo a 2 de distancia e parede a 3.

    >.E#
    >....o.E#

    Essa é a função mais difícil do jogo. Ela vai te dar um bocadinho de
    trabalho mas prometo que vai valer a pena.

    Após lançar o hadouken, você precisará ir para posição da bola para
    recuperá-la. Você escolhe se vai tirar ou não dano no inimigos.

Implementação:

    Verifique se o hadouken já existe, se não existir, faça-o interagir com os
    elementos do cenário, derrubando-os ou destruindo-os. Esteja atento a
    verificar se os elementos existem e atualizar suas posições atuais e
    anteriores.

    Se o hadouken já existe, significa que ele já foi lançado e está em algum
    lugar do cenário. Se a posição do heroi foi a mesma do hadouken, recolha-o
    colocando hadouken existe para False.

    Atenção que você vai utilizar a mesma tecla para atirar e recolher o
    hadouken.

    Você pode usar a constante hadouken_power para inicializar o poder do
    hadouken.

Flashback:

    Vá na função process_input e chame essa função caso a tecla seja 'h'. Bônus:
    Vá em update_move e não permita que seu heroi se afaste da bola uma
    distância maior do que a de lançamento inicial. Dica: guarde na bola a força
    do hero no lancamento. Se a distancia pra direita ou pra esquerda se tornar
    maior do que a força, mova a bola como que sendo arrastada.

Ajuda:

    Se você já chegou até aqui, deve ter aprendido muita coisa. Sua maior ajuda
    é a internet, criatividade e testes e muita paciência pra debugar o que está
    estranho ou errado. Boa sorte.

    Você pode usar o vetor criado na função anterior para simplificar aqui. Ou
    então crie uma função auxiliar e chame individualmente para cada elemento
    do cenário.

*/


void elem_hadouken(Ambiente * amb){
    (void) amb;
}


