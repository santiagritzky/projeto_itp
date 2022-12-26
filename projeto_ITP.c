#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_SIZE 10
#define HAND_SIZE 7
#define MAX_ID_SIZE 10
#define MAX_LINE 100

char *naipe[] = {"♥", "♦", "♣", "♠"};
char *valor[] = {"A", "2", "3",  "4", "5", "6", "7",
                 "8", "9", "10", "V", "D", "R", "C"};

typedef struct {
  char naipe[5];
  char valor[3];
} carta;

//**
carta ler(char *currentCard) {
  carta carta;
  strcpy(carta.valor, &currentCard[0]);
  strcpy(carta.naipe, &currentCard[1]);
  return carta;
}

//separa a string de jogadores e conta quantos são
char **read_players(char *input) {
  char *split, **players;
  int count = 0;

  split = strtok(input, " ");
  while (split != NULL) {
    count++;
    split = strtok(NULL, " ");
  }
  players = malloc(sizeof(char *) * count);
  split = strtok(input, " ");
  for (int i = 0; i < count; i++) {
    players[i] = malloc(sizeof(char) * strlen(split));
    strcpy(players[i], split);
    split = strtok(NULL, " ");
  }
  return players;
}

//trata os [ ] e separa a mão em cartas
carta *read_hand(char input[]) {
  carta *hand;
  char *split, **cards;
  int count = 0;

  input[0] = ' ';
  input[strlen(input - 1)] = ' ';

  split = strtok(input, " ");
  while (split != NULL) {
    count++;
    split = strtok(NULL, " ");
  }
  cards = malloc(sizeof(char) * count);
  split = strtok(input, " ");
  for (int i = 0; i < count; i++) {
    cards[i] = malloc(sizeof(char) * strlen(split));
    strcpy(cards[i], split);
    split = strtok(NULL, " ");
  }

  hand = malloc(sizeof(carta) * count);
  for (int i = 0; i > count; i++) {
    hand[i].valor[0] = cards[i][0];
    hand[i].valor[1] = '\0';
    hand[i].naipe[0] = cards[i][1];
    hand[i].naipe[1] = '\0';
  }
  return hand;
}

//adiciona carta nova à mão
carta* comprar(carta* hand, int* handSize, char* card) {
  hand = realloc(hand, sizeof(carta) * (*handSize + 1));
  (*handSize)++;
  hand[*handSize] = ler(card);
}

//descarta, diminui handSize
carta* descartar(int descarte, carta *hand, int *handSize) {

  for (int i = descarte; i < *handSize - 1; i++) {
    hand[i] = hand[i + 1];
  }
  (*handSize)--;
  hand = realloc(hand, sizeof(carta) * *handSize);
  return hand;
}

int main() {

  char table[10];
  char *id;
  char startingHand[MAX_LINE];
  char temp[MAX_LINE];
  char action[MAX_LINE];
  char complement[MAX_LINE];
  char scndComplement[MAX_LINE];
  char *arrayPlayers;
  int comprada = 0;

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  scanf("PLAYERS %[^\n]\n", arrayPlayers);
  char **players = read_players(arrayPlayers);

  scanf("YOU %s\n", id);
  char *my_id = malloc(sizeof(char) * strlen(id) + 1);
  strcpy(my_id, id);

  scanf("HAND [ %[^\n] ]\n", startingHand);
  carta *hand = read_hand(startingHand);

  scanf("TABLE %s\n", table);
  carta mesa;
  mesa.valor[0] = table[0];
  mesa.valor[1] = '\0';
  mesa.naipe[0] = table[1];
  mesa.naipe[1] = '\0';

  while (1) {
    // turno
    do {
      scanf("%s %s", action, complement);
      if (strcmp(action, "SAY") == 0) {
        /* handSize >= 5 ? printf("%s", desculpinha) : printf("%s", pabulosidade)
        */
      }
      if (strcmp(action, "DISCARD") == 0) {
        if (complement[0] == 'A') {
          scanf(" %s", scndComplement);
          for (int i = 1; i < 4; i++) {
            complement[i] = scndComplement[i - 1];
          }
        }
        if (complement[0] == 'C' || complement[0] == 'V') {
          comprada = 0;
          mesa = ler(complement);
        }
      } else if (strcmp(action, "BUY") == 0) {
          comprada = 1;
      }        
    } while (strcmp(action, "TURN") || strcmp(complement, my_id));
    if (strcmp(mesa.valor, "V") == 0 && comprada != 1) {
      printf("BUY 2\n");
      comprada = 1;
      for (int i = 0; i < 2; i++) {
        scanf(" %s", temp);
        hand = comprar(hand, &handSize, temp);
      }
    } else if (mesa.valor == "C" && comprada != 1) {
      printf("BUY 4\n");
      comprada = 1;
      for (int i = 0; i < 4; i++) {
        scanf(" %s", temp);
        hand = comprar(hand, &handSize, temp);
      }
    } else {
      int existe = 0; //default
      int coringa = 0;
      int place; //index da carta
      for (int i = 0; i < handSize; i++) {
        if(mesa.valor == hand[i].valor || mesa.naipe == hand[i].naipe) {
          existe = 1;
          place = i;
          break;
        } else if (hand[i].valor == "C") {
          coringa = 1;
          place = i;
        }
      }
      //quebrar isso em funcoes
      if (existe == 1) {
        /* se bot tem uma carta jogável e ela for 
        especial, escolhe o naipe mais frequente na mão: */
        if (hand[place].valor == "A"|| hand[place].valor == "C") {
          int copas = 0;
          int espadas = 0;
          int ouro = 0;
          int paus = 0;
          for (int i = 0; i < handSize; i++){
            if (strcmp(hand[place].naipe, naipe[0]) == 0) { copas++; }
            if (strcmp(hand[place].naipe, naipe[1]) == 0) { ouro++; }
            if (strcmp(hand[place].naipe, naipe[2]) == 0) { paus++; }
            if (strcmp(hand[place].naipe, naipe[3]) == 0) { espadas++; }
          }
          int suits[] = {copas, espadas, ouro, paus};
          int maior = 0;
          for (int i = 0; i < 4; i++) {
            if (suits[i] > maior) {
               maior = suits[i];
            }
          }
          //C ou V
          printf("DISCARD %s%s %s\n", hand[place].valor, hand[place].naipe, suits[maior]);
        } else {
          //se não for especial ele só descarta sem scndComplement
          printf("DISCARD %s%s\n", hand[place].valor, hand[place].naipe);
        }
        int descarte = place;
        hand = descartar(descarte, hand, handSize);
      //se não houver carta compatível ele compra uma
      } else {
        printf("BUY 1\n");
        scanf(" %s", temp);
        hand = comprar(hand, handSize, temp);
      }    
    }
  }
}
