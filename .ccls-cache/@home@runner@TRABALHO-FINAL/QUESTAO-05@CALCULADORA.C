#include <stdio.h>
#include <pthread.h>

// Estrutura para armazenar os operandos e o resultado
struct Operacao {
    int operando1;
    int operando2;
    int resultado;
};

// Função para realizar a potenciação
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

int main() {
    // Estrutura para armazenar operações
    struct Operacao op;

    // Variável para armazenar a escolha do usuário
    int escolha;

    // Loop até que uma escolha válida seja feita
    do {
        // Solicita a operação ao usuário
        printf("Escolha a operacao:\n");
        printf("1. Potenciacao\n");
        printf("2. Multiplicacao\n");
        printf("3. Fatorial\n");
        printf("4. Soma\n");
        printf("5. Subtracao\n");
        scanf("%d", &escolha);

        // Verifica se a escolha é válida
        if (escolha < 1 || escolha > 5) {
            printf("Escolha invalida. Tente novamente.\n");
            continue;
        }

        // Solicita os operandos ao usuário
        printf("Digite o primeiro operando: ");
        scanf("%d", &op.operando1);
        printf("Digite o segundo operando: ");
        scanf("%d", &op.operando2);

        // Thread para realizar a operação escolhida
        pthread_t thread;
        switch (escolha) {
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
        }

        // Espera até que a thread tenha terminado
        pthread_join(thread, NULL);

        // Exibe o resultado da operação
        printf("Resultado: %d\n", op.resultado);

    } while (escolha < 1 || escolha > 5);  // Continua até que uma escolha válida seja feita

    return 0;
}
