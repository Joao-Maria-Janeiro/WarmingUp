#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "lists.h"

void loadCountryFromFile(char _fileNameCountry[], node_t_country **_head, node_t_country **_tail){
    dados_country payload;
    char linha[300] = {0};
    int length = 0;
    char aux[400] = {0};
    int i=0;

    node_t_auxYear *_headAuxYear = NULL;
    node_t_auxYear *_tailAuxYear = NULL;

    node_t_auxYear *tmp = NULL;

    FILE *fp;
    fp = fopen(_fileNameCountry, "r");
    if( fp == NULL){
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    //Here we use the while to read each line of the file
    while(fgets(linha, 300, fp) != NULL){
        if(i!=0) { //We don't want to save the first line of the file because it's the header
            if(strstr(linha, ",,") == NULL) { // We do this because we don't want to save lines without all the information
                sscanf(linha, "%d-%d-%d,%f,%f,%[^\n]",
                &(payload.dt.ano), 
                &(payload.dt.mes), 
                &(payload.dt.dia), 
                &(payload.temperatura), 
                &(payload.incerteza), 
                aux);

                length = strlen(aux) - 1;
                aux[length] = '\0';

                strcpy(payload.pais, aux);
                insertAuxYear(&_headAuxYear, &_tailAuxYear, payload.dt.ano, payload); //Here we send it to the year's list
            
            }
        }
        i++;
        
    }
    stitching(_headAuxYear, _tailAuxYear); //We summon this function to join all the mini lists into a big list
    //Update the head and tail of the big list
    *_head = _headAuxYear->head;
    *_tail = _tailAuxYear->tail;
    tmp = _headAuxYear;
    //Free all the years' list
    while(tmp != _tailAuxYear){
        tmp = tmp->next;
        free(tmp->prev);
    }
    free(_tailAuxYear);

    fclose(fp);
}
void loadCityFromFile(char _fileNameCity[], node_t_city **_head, node_t_city **_tail){
    dados_city payload;
    char linha[300] = {0};
    int length = 0;

    char* data = NULL;
    char* temperatura = NULL;
    char* incerteza = NULL;
    char* cidade = NULL;
    char* pais = NULL;
    char* latitude = NULL;
    char* longitude = NULL;
    int last_c = 0;

    int i=0;


    FILE *fp;
    fp = fopen(_fileNameCity, "r");
    if( fp == NULL){
        printf("Error opening file");
        exit(EXIT_FAILURE);
    }

    //Here we use the while to read each line of the file
    while(fgets(linha, 300, fp) != NULL){
        length = strlen(linha) - 1;
        linha[length] = '\0';
        if(i!=0) { //We don't want to save the first line of the file because it's the header
            if(strstr(linha, ",,") == NULL){ // We do this because we don't want to save lines without all the information
                data = strtok(linha, ",");
                temperatura = strtok(NULL, ",");
                incerteza = strtok(NULL, ",");
                cidade = strtok(NULL, ",");
                pais = strtok(NULL, ",");
                latitude = strtok(NULL, ",");
                longitude = strtok(NULL, ",");


                sscanf(data, "%d-%d-%d",
                &(payload.dt.ano), 
                &(payload.dt.mes), 
                &(payload.dt.dia)
                );

            
                payload.temperatura = atof(temperatura); //Converts string to float
                payload.incerteza = atof(incerteza);
                strcpy(payload.cidade, cidade);
                strcpy(payload.pais, pais);

                sscanf(latitude, "%f", &(payload.latitude.angular));
                last_c = strlen(latitude);
                payload.latitude.direcao = latitude[last_c-1];

                sscanf(longitude,"%f", &(payload.longitude.angular));
                last_c = strlen(longitude);
                payload.longitude.direcao = longitude[last_c-2];

                InsertCityList(_head, _tail, payload);

            }
        }
        i++;
    }

    fclose(fp);
}
