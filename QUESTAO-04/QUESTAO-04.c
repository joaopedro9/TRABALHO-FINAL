#include <stdio.h>
#include <pthread.h>

pthread_mutex_t account_mutex;
float account_balance = 1000;

void *deposit(void *arg) {
    float deposit_amount = *((float *)arg);

    pthread_mutex_lock(&account_mutex);
    printf("Saldo antes do depósito: %.2f\n", account_balance);
    account_balance += deposit_amount;
    printf("Depósito de %.2f realizado. Saldo atual: %.2f\n", deposit_amount, account_balance);
    pthread_mutex_unlock(&account_mutex);

    pthread_exit(NULL);
}

void *withdraw(void *arg) {
    float withdraw_amount = *((float *)arg);

    pthread_mutex_lock(&account_mutex);
    printf("Saldo antes do saque: %.2f\n", account_balance);
    if (account_balance >= withdraw_amount) {
        account_balance -= withdraw_amount;
        printf("Saque de %.2f realizado.\n Saldo atual: %.2f\n", withdraw_amount, account_balance);
    } else {
        printf("Saldo insuficiente para o saque de %.2f.\n Saldo atual: %.2f\n", withdraw_amount, account_balance);
    }
    pthread_mutex_unlock(&account_mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    float deposit_amount, withdraw_amount;

    if (pthread_mutex_init(&account_mutex, NULL) != 0) {
        printf("Erro ao inicializar o mutex\n");
        return 1;
    }

    printf("Digite o valor do depósito: ");
    scanf("%f", &deposit_amount);
    printf("Digite o valor do saque: ");
    scanf("%f", &withdraw_amount);

    printf("Saldo inicial: %.2f\n", account_balance);

    // Criação das threads para depósito e saque
    if (pthread_create(&threads[0], NULL, deposit, &deposit_amount) != 0 ||
        pthread_create(&threads[1], NULL, withdraw, &withdraw_amount) != 0) {
        printf("Erro ao criar as threads\n");
        return 1;
    }

    // Aguarda o término das threads
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    printf("Saldo final: %.2f\n", account_balance);

    pthread_mutex_destroy(&account_mutex);

    return 0;
}