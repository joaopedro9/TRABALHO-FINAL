#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex_conta;
float saldo_conta = 1000;

void *deposito(void *arg) {
    float deposito = *((float *)arg);

    pthread_mutex_lock(&mutex_conta);
    printf("Saldo antes do depósito: %.2f\n", saldo_conta);
    saldo_conta += deposito;
    printf("Depósito de %.2f realizado. \nSaldo atual: %.2f\n", deposito, saldo_conta);
    pthread_mutex_unlock(&mutex_conta);

    pthread_exit(NULL);
}

void *saque(void *arg) {
    float valor_saque = *((float *)arg);

    pthread_mutex_lock(&mutex_conta);
    printf("Saldo antes do saque: %.2f\n", saldo_conta);
    if (saldo_conta >= valor_saque) {
        saldo_conta -= valor_saque;
        printf("Saque de %.2f realizado. \nSaldo atual: %.2f\n", valor_saque, saldo_conta);
    } else {
        printf("Saldo insuficiente para o saque de %.2f. Saldo atual: %.2f\n", valor_saque, saldo_conta);
    }
    pthread_mutex_unlock(&mutex_conta);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    float valor_deposito, valor_saque;

    if (pthread_mutex_init(&mutex_conta, NULL) != 0) {
        perror("Erro ao inicializar o mutex");
        return 1;
    }

    printf("Digite o valor do depósito: ");
    scanf("%f", &valor_deposito);
    if (valor_deposito < 0) {
        printf("Valor de depósito inválido\n");
        return 1;
    }

    printf("Digite o valor do saque: ");
    scanf("%f", &valor_saque);
    if (valor_saque < 0) {
        printf("Valor de saque inválido\n");
        return 1;
    }

    printf("Saldo inicial: %.2f\n", saldo_conta);

    if (pthread_create(&threads[0], NULL, deposito, &valor_deposito) != 0 ||
        pthread_create(&threads[1], NULL, saque, &valor_saque) != 0) {
        perror("Erro ao criar as threads");
        return 1;
    }

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    printf("Saldo final: %.2f\n", saldo_conta);

    pthread_mutex_destroy(&mutex_conta);

    return 0;
}
