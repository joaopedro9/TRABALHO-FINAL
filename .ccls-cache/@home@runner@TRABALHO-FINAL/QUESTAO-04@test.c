#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
int recurso_compartilhado = 0;

void *funcao_thread(void *arg) {
    int num_incrementos = *((int *)arg);

    for (int i = 0; i < num_incrementos; i++) {
        pthread_mutex_lock(&mutex);
        recurso_compartilhado++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    int num_threads, num_incrementos;
    printf("Quantas threads deseja criar? ");
    scanf("%d", &num_threads);

    printf("Quantos incrementos por thread? ");
    scanf("%d", &num_incrementos);

    pthread_t threads[num_threads];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < num_threads; i++) {
        if (pthread_create(&threads[i], NULL, funcao_thread, &num_incrementos) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return EXIT_FAILURE;
        }
    }

    pthread_mutex_destroy(&mutex);

    printf("Valor final do recurso compartilhado: %d\n", recurso_compartilhado);

    return EXIT_SUCCESS;
}