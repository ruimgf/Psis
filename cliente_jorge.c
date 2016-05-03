#include "psiskv.h"
#include <stdio.h>
#include <string.h>

int main()
{
  int i=0;
  char linha[300];
  int kv = kv_connect("127.0.0.1",9999);
  i++;sprintf(linha, "%d: A HISTORIA DO PATINHO FEIO", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Era uma vez uma mamã pata que teve 5 ovos.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Ela esperava ansiosamente pelo dia em que os seus ovos quebrassem e deles nascessem os seus queridos filhos!", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Quando esse dia chegou, os ovos da mamã pata começaram a abrir, um a um, e ela, alegremente, começou a saudar os seus novos patinhos.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Mas o último ovo demorou mais a partir, e a mamã começou a ficar nervosa…", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Finalmente, a casca quebrou e, para surpresa da mamã pata, de lá saiu um patinho muito diferente de todos os seus outros filhos.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: - Este patinho feio não pode ser meu! Exclama a mamã pata.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: - Alguém te pregou uma partida. Afirma a vizinha galinha.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Os dias passaram e, à medida que os patinhos cresciam, o patinho feio tornava-se cada vez mais diferente dos outros patinhos.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Cansado de ser gozado pelos seus irmãos e por todos os animais da quinta, o patinho feio decide partir.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Mesmo longe da quinta, o patinho não conseguiu paz, pois os seus irmãos perseguiam-no por todo o lago, gritando:", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: - És o pato mais feio que nós alguma vez vimos!", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: E, para onde quer que fosse, todos os animais que encontrava faziam troça dele.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: - Que hei de eu fazer? Para onde hei de ir? O patinho sentia-se muito triste e abandonado.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Com a chegada do inverno, o patinho cansado e cheio de fome encontra uma casa e pensa:", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: - Talvez aqui encontre alguém que goste de mim! E assim foi.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: O patinho passou o inverno aconchegadinho, numa casa quentinha e na companhia de quem gostava dele.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Tudo teria corrido bem se não tivesse chegado a primavera e com ela, um gato malvado, que enganando os donos da casa, correu com o patinho para fora dali!", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: - Mais uma vez estou sozinho e infeliz… Suspirou o patinho feio.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: O patinho seguiu o seu caminho e, ao chegar a um grande lago, refugiou-se junto a uns juncos, e ali ficou durante vários dias.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Um dia, muito cedo, o patinho feio foi acordado por vozes de crianças.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: - Olha! Um recém-chegado! Gritou uma das crianças. Todas as outras crianças davam gritos de alegria.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: - E é tão bonito! Dizia outra.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Bonito?... De quem estarão a falar? Pensou o patinho feio. ", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: De repente, o patinho feio viu que todos olhavam para ele e, ao ver o seu reflexo na água, viu um grande e elegante cisne. ", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: - Oh!... Exclama o patinho admirado.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Crianças e outros cisnes admiravam a sua beleza e cumprimentavam-no alegremente.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: Afinal ele não era um patinho feio mas um belo e jovem cisne!", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: A partir desse dia, não houve mais tristezas, e o patinho feio que agora era um belo cisne, viveu feliz para sempre!", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "%d: VITORIA VITORIA ACABOU-SE A HISTORIA", i);kv_write(kv, i , linha, strlen(linha)+1, 0);

}
