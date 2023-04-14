#include <stdio.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t mutex;
FILE *pont_arq;

void *escreve_arquivo(void *arg) {
    int contador = 1;
    char concatenacao[100];

    while (contador <= 100000) {
        pthread_mutex_lock(&mutex);
        sprintf(concatenacao, "1 programa1 - Thread%d - Data: %02d/%02d/%d Horário: %02d:%02d", contador, dia, mes, ano, horas, minutos);
        fprintf(pont_arq, "%s\n", concatenacao);
        pthread_mutex_unlock(&mutex);

        contador++;
    }

    return NULL;
}

int main(void) {
    time_t epoch = time(NULL);
    struct tm *tm = localtime(&epoch);

    int horas = tm->tm_hour;
    int minutos = tm->tm_min;

    int mes = tm->tm_mon + 1;
    int ano = tm->tm_year + 1900;
    int dia = tm->tm_mday;

    // Criando ou abrindo o arquivo
    pont_arq = fopen("../../REGISTRO_GERAL.txt", "a");
    printf("Arquivo criado ou aberto!\n");

    // Inicializando o mutex
    pthread_mutex_init(&mutex, NULL);

    // Criando as threads
    pthread_t threads[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, escreve_arquivo, NULL);
    }

    // Esperando as threads terminarem
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Fechando o arquivo e liberando o mutex
    fclose(pont_arq);
    pthread_mutex_destroy(&mutex);
    printf("Arquivo fechado!\n");

    return 0;
}
