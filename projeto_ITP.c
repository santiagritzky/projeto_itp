#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constantes para as strings a serem lidas 
#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10

void debug(char *message) {
  fprintf(stderr, "%s\n", message);
}

int main() {
 
  char temp[MAX_LINE];      // string para leitura temporária de dados NECESSARIO TRATAR ESSA VARIAVEL PARA DIMINUIR O NUMERO VARIAVEIS UTILIZADAS
  char my_id[MAX_ID_SIZE];  // identificador do seu bot
  char reading[MAX_LINE];   // string para leitura das cartas criada pela falta de tratamento de temp, futuramente vai ser excluida
  char HAND[MAX_ACTION][MAX_LINE]; // string para guardar as cartas recebidas declarada estaticamente mais deve ser alocada dinamicamente por conta das cartas a ser compradas e descartadas durante a partida

  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===

  /*Um exemplo de dados iniciais é:
    PLAYERS b1 b2 b3
    YOU b1
    HAND [ 4♥ 7♦ 2♣ V♠ A♥ 3♦ 2♣ 9♠ ]
    TABLE 8♦*/

  scanf("PLAYERS %[^\n]\n", temp);

  debug(temp);

  // Lê o identificador do próprio bot. Isso é importante para testar quando é sua vez.
  scanf("YOU %s\n", my_id);
  
  scanf("HAND %[^\n]\n", reading); // Leitura da 'mão' do jogo

  int count = 0;
    for(int i = 0; i <= sizeof(reading); i++){
        if(reading[i] != '[' && reading[i] != ' ' && reading[i] != ']'){
           reading[count] = reading[i];
            count++;
        }
    }                                   //Utilizado para tratar a entrada de HAND mas só esta funcionando parcialmente e é necessario utilizar isso em função para deixar o codigo mais limpo
    for (int i = 0; i <= 8; i++){
        for (int j = 0; j <= 4; j++){
            HAND[i][j] = reading[j];
        }
    }

  //Lê a carta aberta sobre a mesa. Ex: TABLE 8♣
  scanf("TABLE %s\n", temp);

  printf("%s\n", reading);
  printf("%s \n", HAND[8]);

  // === PARTIDA ===

  /char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];
  char card[];
  int acao;

 
  while(1) {
    do {
      

      scanf("%s %s", action, complement);

      if (strcmp(action, "DISCARD")){ // Testes de caso de 'DISCARD' 
        for (int i = 0; i <= 8; i++){
            for (int j = 0; j <= 5; j++){
                if (strcmp(complement, HAND[i])){
                    char card = HAND[i];     // Não funcional, apenas uma ideia de logica 
                }
            }   
        }
        
        
        if (strcmp(complement[0], 'C')){
            acao = 1;
        }
        if (strcmp(complement[0], 'V')){
            acao = 2;
        }
        /*if (strcmp(complement[0], 'D')){   
            acao = 3;
        }
        if (strcmp(complement[0], 'R')){    // necessario realizar a leitura mas não sei se precisa realizar alguma ação ou isso é de responsabilidade do gerenciador do jogo.
            acao = 4;
        }
        if (strcmp(complement[0], 'A')){
            acao = 5;
        }*/
      }
      

      

    } while (strcmp(action, "TURN") || strcmp(complement, my_id));
    
    // agora é a vez do seu bot jogar
    debug("----- MINHA VEZ -----");
    
    switch (acao){
    case 1: 
        printf("BUY 4"); 
        //scanf(%[^\n]\n, HAND);
        // inserir função para adicionar nova carta
        //scanf(%[^\n]\n, HAND);
        // inserir função para adicionar nova carta
        //scanf(%[^\n]\n, HAND);
        // inserir função para adicionar nova carta
        //scanf(%[^\n]\n, HAND);
        // inserir função para adicionar nova carta
        break;     
    case 2:     // Case 1 e 2, necessario implementar a alocação dinamica na variavel HAND e alocar as novas cartas compradas
        printf("BUY 2");
        //scanf(%[^\n]\n, HAND);
        // inserir função para adicionar nova carta
        //scanf(%[^\n]\n, HAND);
        // inserir função para adicionar nova carta
        break;
        scanf();
    default:
        break;
    }

    printf("DISCARD %s\n", card);
    //Necessario implementar uma função para retiar a carta que foi descartada
  }

  return 0;*/
}