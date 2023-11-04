#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int escolha, scanf_result;

struct Operacao{
  int operando1;
  int operando2;
  int resultado;
};

void *potenciacao (void *arg){
  struct Operacao *op = (struct Operacao *) arg;
  op->resultado = 1;
  for (int i = 0; i < op->operando2; ++i){
    op->resultado *= op->operando1;
  }
  return NULL;
}

void *multiplicacao (void *arg){
  struct Operacao *op = (struct Operacao *) arg;
  op->resultado = op->operando1 * op->operando2;
  return NULL;
}

void *fatorial (void *arg){
  struct Operacao *op = (struct Operacao *) arg;
  op->resultado = 1;
  for (int i = 1; i <= op->operando1; ++i){
    op->resultado *= i;
  }
  return NULL;
}

void *soma (void *arg){
  struct Operacao *op = (struct Operacao *) arg;
  op->resultado = op->operando1 + op->operando2;
  return NULL;
}

void *subtracao (void *arg){
  struct Operacao *op = (struct Operacao *) arg;
  op->resultado = op->operando1 - op->operando2;
  return NULL;
}

void MenuDeOperacoes (){
  printf ("\t\t\t\t+=========================================+\n");
  printf ("\t\t\t\t|            Escolha a operacao:          |     \n");
  printf ("\t\t\t\t+-----------------------------------------+\n");
  printf ("\t\t\t\t|  1. Potenciacao  |   2. Multiplicacao   |\n");
  printf ("\t\t\t\t+-----------------------------------------+\n");
  printf ("\t\t\t\t|    3. Fatorial   |       4. Soma        |\n");
  printf ("\t\t\t\t+-----------------------------------------+\n");
  printf ("\t\t\t\t|   5. Subtração   |       0. Sair        |\n");
  printf ("\t\t\t\t+=========================================+\n");
  printf ("Digite a opção escolhida: ");
}

int main (){
  struct Operacao op;
  while (1){
    MenuDeOperacoes ();

    scanf_result = scanf ("%d", &escolha);

    if (scanf_result != 1 || escolha < 0 || escolha > 5){
      printf ("Escolha invC!lida. Tente novamente.\n");
      while (getchar () != '\n');
      continue;
    }
    if (escolha == 0){
      printf ("\t\t\t\t\t\tAté mais!!\n");
      break;
    }

    while (1){
      printf ("Digite o primeiro operando: ");
      scanf_result = scanf ("%d", &op.operando1);
      if (scanf_result != 1){
        printf ("Entrada invC!lida. Tente novamente.\n");
        while (getchar () != '\n');
        continue;
      }
      break;
    }
    while (1){
      printf ("Digite o segundo operando: ");
      scanf_result = scanf ("%d", &op.operando2);

      if (scanf_result != 1){
        printf ("Entrada invC!lida. Tente novamente.\n");
        while (getchar () != '\n');	// Limpa o buffer do teclado
        continue;
      }
      break;
    }
    pthread_t thread;
    switch (escolha){

      case 1:
        pthread_create (&thread, NULL, potenciacao, (void *) &op);
        break;
      case 2:
        pthread_create (&thread, NULL, multiplicacao, (void *) &op);
        break;
      case 3:
        pthread_create (&thread, NULL, fatorial, (void *) &op);
        break;
      case 4:
        pthread_create (&thread, NULL, soma, (void *) &op);
        break;
      case 5:
        pthread_create (&thread, NULL, subtracao, (void *) &op);
        break;
    }
    pthread_join (thread, NULL);

    printf ("Resultado: %d\n", op.resultado);
    sleep(1);
  }
  return 0;
}