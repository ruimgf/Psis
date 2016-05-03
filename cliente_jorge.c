#include "psiskv.h"
#include <stdio.h>
#include <string.h>

int main()
{
  int i=0;
  char linha[300];

  i++;sprintf(linha, "A HISTORIA DO PATINHO FEIO", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Era uma vez uma mamã pata que teve 5 ovos.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Ela esperava ansiosamente pelo dia em que os seus ovos quebrassem e deles nascessem os seus queridos filhos!", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Quando esse dia chegou, os ovos da mamã pata começaram a abrir, um a um, e ela, alegremente, começou a saudar os seus novos patinhos.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Mas o último ovo demorou mais a partir, e a mamã começou a ficar nervosa…", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Finalmente, a casca quebrou e, para surpresa da mamã pata, de lá saiu um patinho muito diferente de todos os seus outros filhos.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "- Este patinho feio não pode ser meu! Exclama a mamã pata.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "- Alguém te pregou uma partida. Afirma a vizinha galinha.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Os dias passaram e, à medida que os patinhos cresciam, o patinho feio tornava-se cada vez mais diferente dos outros patinhos.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Cansado de ser gozado pelos seus irmãos e por todos os animais da quinta, o patinho feio decide partir.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Mesmo longe da quinta, o patinho não conseguiu paz, pois os seus irmãos perseguiam-no por todo o lago, gritando:", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "- És o pato mais feio que nós alguma vez vimos!", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "E, para onde quer que fosse, todos os animais que encontrava faziam troça dele.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "- Que hei de eu fazer? Para onde hei de ir? O patinho sentia-se muito triste e abandonado.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Com a chegada do inverno, o patinho cansado e cheio de fome encontra uma casa e pensa:", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "- Talvez aqui encontre alguém que goste de mim! E assim foi.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "O patinho passou o inverno aconchegadinho, numa casa quentinha e na companhia de quem gostava dele.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Tudo teria corrido bem se não tivesse chegado a primavera e com ela, um gato malvado, que enganando os donos da casa, correu com o patinho para fora dali!", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "- Mais uma vez estou sozinho e infeliz… Suspirou o patinho feio.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "O patinho seguiu o seu caminho e, ao chegar a um grande lago, refugiou-se junto a uns juncos, e ali ficou durante vários dias.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Um dia, muito cedo, o patinho feio foi acordado por vozes de crianças.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "- Olha! Um recém-chegado! Gritou uma das crianças. Todas as outras crianças davam gritos de alegria.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "- E é tão bonito! Dizia outra.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Bonito?... De quem estarão a falar? Pensou o patinho feio. ", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "De repente, o patinho feio viu que todos olhavam para ele e, ao ver o seu reflexo na água, viu um grande e elegante cisne. ", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "- Oh!... Exclama o patinho admirado.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Crianças e outros cisnes admiravam a sua beleza e cumprimentavam-no alegremente.", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "Afinal ele não era um patinho feio mas um belo e jovem cisne!", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "A partir desse dia, não houve mais tristezas, e o patinho feio que agora era um belo cisne, viveu feliz para sempre!", i);kv_write(kv, i , linha, strlen(linha)+1, 0);
  i++;sprintf(linha, "VITORIA VITORIA ACABOU-SE A HISTORIA", i);kv_write(kv, i , linha, strlen(linha)+1, 0);

}
