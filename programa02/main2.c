#include <stdio.h>
#include <time.h>

#include <pthread.h> // biblioteca para trabalhar com threads

pthread_mutex_t mutex; // variável do tipo mutex para fazer a sincronização

void *escreve_arquivo(void *thread_id) {
    int *id = (int *)thread_id; // identificador da thread

    time_t epoch = time(NULL); // função para pegar os segundos desde 1 de janeiro de 1970 ou epoch
    struct tm *tm = localtime(&epoch); // importando bibilioteca para pegar hora, ano...

    // hora
    int horas = tm->tm_hour;
    int minutos = tm->tm_min;

    // data
    int mes = tm->tm_mon + 1;
    int ano = tm->tm_year + 1900;
    int dia = tm->tm_mday;

    char concatenacao[100]; // variável onde concateno todos os dados do arquivo

    FILE *pont_arq; // variável ponteiro para criação do txt
    pont_arq = fopen("../../REGISTRO_GERAL.txt", "a"); // Abrindo ou criando o arquivo
    printf("Arquivo criado ou aberto!\n");

    // verificando se o arquivo foi aberto
    if (pont_arq == NULL) {
        printf("ERRO!\n");
        return NULL;
    }
    else {
        int contador = 1; // contador

        while (contador <= 100000) {
            // faz a sincronização para evitar conflitos de escrita no arquivo
            pthread_mutex_lock(&mutex);

            // função que vai juntar todos os dados e colocar em uma só variavel "concatenacao"
            sprintf(concatenacao, "2 programa2 - Thread%d - Data: %02d/%02d/%d Horário: %02d:%02d", *id, dia, mes, ano, horas, minutos);

            // função que escreve dentro do arquivo "pont_arq"
            fprintf(pont_arq, "%s\n", concatenacao);

            // libera o mutex para permitir que outras threads possam escrever no arquivo
            pthread_mutex_unlock(&mutex);

            contador++; // incrementando
        }

        fclose(pont_arq); // fechando o arquivo
        printf("Arquivo fechado!\n");
    }

    pthread_exit(NULL); // encerra a thread
}

int main(void) {
    pthread_t threads[10]; // array de threads
    int thread_ids[10]; // array de identificadores de threads

    pthread_mutex_init(&mutex, NULL); // inicializa o mutex

    // cria as 10 threads
    for (int i = 0; i < 10; i++) {
        thread_ids[i] = i + 1; // define o identificador da thread
        pthread_create(&threads[i], NULL, escreve_arquivo, (void *)&thread_ids[i]); // cria a thread
    }

    // aguarda as threads terminarem
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // destrói o mutex

    return 0;
}
