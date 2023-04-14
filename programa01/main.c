#include <stdio.h>
#include <time.h>
#include <Windows.h>

int main(void){

    time_t epoch = time(NULL);//função para pegar os segundos desde 1 de janeiro de 1970 ou epoch
    FILE *pont_arq;//variavel ponteiro para criação do txt
    struct tm *tm = localtime(&epoch);//importando bibilioteca para pegar hora, ano...

    int contador = 1; //contador

    //hora
    int horas = tm -> tm_hour;
    int minutos = tm -> tm_min;

    //data
    int mes = tm -> tm_mon + 1;
    int ano = tm -> tm_year + 1900;
    int dia = tm -> tm_mday;

    char concatenacao[100];//variavel onde concateno todos os dados do arquivo
    
    //Abrindo ou criando o arquivo
    pont_arq = fopen("../../REGISTRO_GERAL.txt", "a");
    printf("Arquivo criado  ou aberto!");
    
    //verificando se o arquivo foi aberto
    if(pont_arq == NULL){

        printf("ERR0!");
        return 1;
    }else{
        
        while(contador <= 100000){
            
            sprintf(concatenacao, "1 programa1 - Thread%d - Data: %02d/%02d/%d Horário: %02d:%02d", contador, dia, mes, ano, horas, minutos);//função que vai juntar todos os dados e colocar em uma só variavel "concatenacao"
            fprintf(pont_arq, "%s\n", concatenacao);//função que escreve dentro do arquivo "pont_arq"

            contador++;//incrementando
        }
        
        fclose(pont_arq);//fechando o arquivo
        printf("Arquivo fechado!");
    }

    return 0;
}