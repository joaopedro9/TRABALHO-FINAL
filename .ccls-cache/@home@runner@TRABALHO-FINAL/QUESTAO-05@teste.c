#include <stdio.h>
#include <pthread.h>
int escolha, scanf_result;
// Estrutura para armazenar os operandos e o resultado
struct Operacao {
    int operando1;
    int operando2;
    int resultado;
};

// Funções para realizar operações matemáticas
void* potenciacao(void* arg) {
    struct Operacao* op = (struct Operacao*)arg;
    op->resultado = 1;
    for (int i = 0; i < op->operando2; ++i) {
        op->resultado *= op->operando1;
    }
    return NULL;
}

// Função para realizar a multiplicação
void* multiplicacao(void* arg) {
    struct Operacao* op = (struct Operacao*)arg;
    op->resultado = op->operando1 * op->operando2;
    return NULL;
}

// Função para realizar o fatorial
void* fatorial(void* arg) {
    struct Operacao* op = (struct Operacao*)arg;
    op->resultado = 1;
    for (int i = 1; i <= op->operando1; ++i) {
        op->resultado *= i;
    }
    return NULL;
}

// Função para realizar a soma
void* soma(void* arg) {
    struct Operacao* op = (struct Operacao*)arg;
    op->resultado = op->operando1 + op->operando2;
    return NULL;
}

// Função para realizar a subtração
void* subtracao(void* arg) {
    struct Operacao* op = (struct Operacao*)arg;
    op->resultado = op->operando1 - op->operando2;
    return NULL;
}

void MenuDeOperacoes() {
    printf("\t\t\t\t+=========================================+\n");
    printf("\t\t\t\t|            Escolha a operacao:          |     \n");
    printf("\t\t\t\t+-----------------------------------------+\n");
    printf("\t\t\t\t|  1. Potenciacao  |   2. Multiplicacao   |\n");
    printf("\t\t\t\t+-----------------------------------------+\n");
    printf("\t\t\t\t|    3. Fatorial   |       4. Soma        |\n");
    printf("\t\t\t\t+-----------------------------------------+\n");
    printf("\t\t\t\t|   5. Subtração   |       0. Sair        |\n");
    printf("\t\t\t\t+=========================================+\n");
    printf("Digite a opção escolhida:");
}

int main() {
    // Estrutura para armazenar operações
    struct Operacao op;
  while (1) {

      // Solicita a operação ao usuário
      MenuDeOperacoes();

      // Verifica o valor de retorno do scanf para garantir que a entrada foi bem-sucedida
      scanf_result = scanf("%d", &escolha);


      // Se a entrada não for bem-sucedida, limpa o buffer do teclado e pede ao usuário para tentar novamente
      if (scanf_result != 1 || escolha < 0 || escolha > 5) {
         printf("Escolha inválida. Tente novamente.\n");
         while (getchar() != '\n'); // Limpa o buffer do teclado
         continue;
      }

       //Se o usuário escolheu sair, encerra o programa
      if (escolha == 0) {
         printf("\t\t\t\t\t\tAté mais!!\n");
         break;
      }

      // Solicita os operandos ao usuário
      while (1) {
          printf("Digite o primeiro operando: ");
          scanf_result = scanf("%d", &op.operando1);

          // Se a entrada não for bem-sucedida, limpa o buffer do teclado e pede ao usuário para tentar novamente
          if (scanf_result != 1) {
              printf("Entrada inválida. Tente novamente.\n");
              while (getchar() != '\n'); // Limpa o buffer do teclado
              continue;
          }

          // Se chegou até aqui, a entrada é válida, pode sair do loop interno
          break;
      }

      // Solicita o segundo operando ao usuário até que uma entrada válida seja fornecida
      while (1) {
          printf("Digite o segundo operando: ");
          scanf_result = scanf("%d", &op.operando2);

          // Se a entrada não for bem-sucedida, limpa o buffer do teclado e pede ao usuário para tentar novamente
          if (scanf_result != 1) {
              printf("Entrada inválida. Tente novamente.\n");
              while (getchar() != '\n'); // Limpa o buffer do teclado
              continue;
          }

          // Se chegou até aqui, a entrada é válida, pode sair do loop interno
          break;
      }
    pthread_t thread;
    switch (escolha) {
      case 0:
        printf("Até a proxima");
        return 0;
      case 1:
        pthread_create(&thread, NULL, potenciacao, (void*)&op);
        break;
      case 2:
        pthread_create(&thread, NULL, multiplicacao, (void*)&op);
        break;
      case 3:
        pthread_create(&thread, NULL, fatorial, (void*)&op);
        break;
      case 4:
        pthread_create(&thread, NULL, soma, (void*)&op);
        break;
      case 5:
        pthread_create(&thread, NULL, subtracao, (void*)&op);
        break;
      default:
        printf("Escolha inválida. Tente novamente.\n");
        while (getchar() != '\n'); // Limpa o buffer do teclado
        continue;
    }
    pthread_join(thread, NULL);

      // Execução das operações e exibição dos resultados



      // Espera até que a thread tenha terminado


      // Exibe o resultado da operação
      printf("Resultado: %d\n", op.resultado);
  }
    return 0;
}
