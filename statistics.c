#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statistics.h"
#include "structs.h"
#include "lists.h"


/**Calculates the global minimum, maximum and medium temperatures for each given interval
*/
void MinMaxMedGlobalCalc(node_t_country **_head, node_t_country **_tail, int _interval) {
    float min = 1000; //Valores irreais para temperaturas
    float max = -200;
    float sum = 0;
    int count = 0;
    node_t_country *aux = *_head;
    int initYear=aux->payload.dt.ano, finalYear=initYear+_interval;
    int lineCount=0;
    char ch = 0;
    int endLoop = 0;

    //Iterates through all the elements unless 'q' key was pressed
    while(aux != NULL && endLoop != 1) {
        if(aux->payload.dt.ano >= initYear && aux->payload.dt.ano <= finalYear) {
            if(aux->payload.temperatura<min)
                min=aux->payload.temperatura;
            if(aux->payload.temperatura>max)
                max=aux->payload.temperatura;
            
            count++;
            sum+=aux->payload.temperatura;
            aux = aux->next;
        }else {
            if(lineCount < 20) { 
                if(count != 0) { //Se não existir nenhum ano no intervalo do if anteriormente, não é apresentada nenhuma linha para esse intervalo
                    printf("[%d, %d]: Minima: %f  |  Máxima: %f  |  Média: %f\n", initYear, finalYear, min, max, (float)sum/count);
                } else {
                    printf("[%d, %d]: Não existem dados para este intervalo\n", initYear, finalYear);
                }
                lineCount++;
            } else {
                printf("Digite 'a' para continuar a amostragem de resultados ou 'q' para sair\n");
                lineCount=0; //Resets the line counts
                scanf(" %c", &ch);
                getchar();
                system("clear");
            }
            initYear += _interval;
            finalYear += _interval;
            min=1000;
            max=-200;
            sum=0;
            count=0;
        }
        switch(ch) {
            case 'a':
                continue;
            case 'q':
                endLoop=1;
                break;
        }
        
    }
    
    //Como não chega a imprimir o ultimo intervalo de anos, e se o user não tiver escolhido sair
    if(endLoop != 1) {
        printf("[%d, %d]: Minima: %f  |  Máxima: %f  |  Média: %f\n", initYear, finalYear, min, max, (float)sum/count);
        initYear += _interval;
        finalYear += _interval;
    }

}

/*Calculates the country minimum, maximum and medium temperatures for each given interval
*/
void MinMaxMedCountryCalc(node_t_country **_head, node_t_country **_tail, int _interval, char _country_name[]) {
    float min = 1000; //Valores irreais para temperaturas
    float max = -200;
    float sum = 0;
    int count = 0;
    node_t_country *aux = *_head;
    int initYear=aux->payload.dt.ano, finalYear=initYear+_interval;
    int lineCount=0;
    char ch = 0;
    int endLoop = 0;

    while(aux != NULL && endLoop != 1) {
        if(aux->payload.dt.ano >= initYear && aux->payload.dt.ano <= finalYear) {
            if(!strcmp(_country_name, aux->payload.pais)) {  //Checks if the current aux node is of the selected country
                if(aux->payload.temperatura<min)
                    min=aux->payload.temperatura;
                if(aux->payload.temperatura>max)
                    max=aux->payload.temperatura;
                            
                count++;
                sum+=aux->payload.temperatura;
            }

            aux = aux->next;
        }else {
            if(lineCount < 20) {
                if(count != 0) { //Se não existir nenhum ano no intervalo do if anteriormente, não é apresentada nenhuma linha para esse intervalo
                    printf("[%d, %d]: Minima: %f  |  Máxima: %f  |  Média: %f\n", initYear, finalYear, min, max, (float)sum/count);
                } else {
                    printf("[%d, %d]: Não existem dados para este intervalo\n", initYear, finalYear);
                }
                lineCount++;
            } else {
                printf("Digite 'a' para continuar a amostragem de resultados ou 'q' para sair\n");
                lineCount=0;
                scanf(" %c", &ch);
                system("clear");
            }
            initYear += _interval;
            finalYear += _interval;
            min=1000;
            max=-200;
            sum=0;
            count=0;
        }
        switch(ch) {
            case 'a':
                continue;
            case 'q':
                endLoop=1;
                break;
            }
        
        
    }
    
    //Como não chega a imprimir o ultimo intervalo de anos, e se o user não tiver escolhido sair
    if(endLoop != 1) {
        if(count!=0)
            printf("[%d, %d]: Minima: %f  |  Máxima: %f  |  Média: %f\n", initYear, finalYear, min, max, (float)sum/count);
        else
            printf("[%d, %d]: Não existem dados para este intervalo\n", initYear, finalYear);
        initYear += _interval;
        finalYear += _interval;
    }

}

/*Calculates the city minimum, maximum and medium temperatures for each given interval
*/
void MinMaxMedCityCalc(node_t_city **_headCities, node_t_city **_tailCities, int _interval, char _city_name[]) {
    float min = 1000; //Valores irreais para temperaturas
    float max = -200;
    float sum = 0;
    int count = 0;
    node_t_city *aux = *_headCities;
    int initYear = 0, finalYear = 0;
    int lineCount=0;
    char ch = 0;
    int endLoop = 0;

    getchar();

    //Iterates the city list until it finds the first element of the selected city. After it find's it, breaks out of the loop
    while(aux != *_tailCities) {
        if(!strcmp(aux->payload.cidade, _city_name)) {
            break;
        }
        aux = aux->next;
    }
    initYear=aux->payload.dt.ano;
    finalYear = initYear + _interval;

    while(aux != *_tailCities && endLoop != 1) {
        if(strcmp(aux->payload.cidade, _city_name)) { //If the aux city node is no longer the selected city
                endLoop=1;
        }
        if(aux->payload.dt.ano >= initYear && aux->payload.dt.ano <= finalYear) {
            if(aux->payload.temperatura<min) {
                min=aux->payload.temperatura;
            }
            if(aux->payload.temperatura>max) {
                max=aux->payload.temperatura;
            }
            sum = sum + aux->payload.temperatura;
            count++;
            aux=aux->next;
        }else {
            if(lineCount < 20) {
                if(count != 0) { //Se não existir nenhum ano no intervalo do if anteriormente, não é apresentada nenhuma linha para esse intervalo
                    printf("[%d, %d]: Minima: %f  |  Máxima: %f  |  Média: %f\n", initYear, finalYear, min, max, (float)sum/count);
                } else {
                    printf("[%d, %d]: Não existem dados para este intervalo\n", initYear, finalYear);
                }
                lineCount++;
            } else {
                printf("Digite 'a' para continuar a amostragem de resultados ou 'q' para sair\n");
                lineCount=0;
                scanf(" %c", &ch);
                system("clear");
            }
            initYear += _interval;
            finalYear += _interval;
            min=1000;
            max=-200;
            sum=0;
            count=0;
        }
        switch(ch) {
            case 'a':
                continue;
            case 'q':
                endLoop=1;
                break;
            }
    }
    if(endLoop != 1) {
        if(count!=0)
            printf("[%d, %d]: Minima: %f  |  Máxima: %f  |  Média: %f\n", initYear, finalYear, min, max, (float)sum/count);
        else
            printf("[%d, %d]: Não existem dados para este intervalo\n", initYear, finalYear);
        initYear += _interval;
        finalYear += _interval;
    }

    getchar();

}

/*AnaliseTempAnoCountry: Prints the N hottest, coldest and the ones with the biggest span, countries -> For a specific year
*/
void AnaliseTempAnoCountry(node_t_country **_head){
    int ano, N = 0;
    int i = 0, n = 0;
    int j = 0;
    int k = 0;
    node_t_country * aux = *_head;
    dados_country *tmp = NULL;
    int is_valid = 4;
    int array_size = 0;

    pais_temp * tmp1 = NULL;
    pais_temp * tmp2 = NULL;
    pais_temp * tmp3 = NULL;
    

    pais_temp a;

    printf("Insira o ano a analisar: ");
    scanf("%d", &ano);


    while(aux!= NULL) {
        if(aux->payload.dt.ano == ano) { 
            //Creates an array which only contains the information of the selected year so the proccessing is faster
            tmp = (dados_country *)realloc(tmp, (i+1)*sizeof(dados_country));
            tmp[i] = aux->payload;
            i++;
        }
        aux=aux->next;
    }
    n=i; //Copies the array size to the variable n
    
    do{
    printf("Insira o valor do N: ");
    scanf("%d", &N);
        if(N > 20 || N < 1){
            printf("O valor de N tem de estar entre 1 e 20\n");
        }
    }while(N > 20 || N < 1);

    tmp1 = (pais_temp *)malloc(sizeof(pais_temp));
    strcpy(tmp1[0].pais, tmp[0].pais);
    tmp1[0].sum_temp = 0;
    tmp1[0].reps = 0;
    tmp1[0].average_temp = 0;
    tmp1[0].min_temp = 10000;
    tmp1[0].max_temp = -10000;
    tmp1[0].amplitude = 0;
    array_size = 1;

    //Calculates the maximum and minimum temperature for the first element only as well as the sum of all temperatures and reps
    for(i = 0; i < n; i++){
        if(strcmp(tmp[0].pais, tmp[i].pais) == 0){
            tmp1[0].sum_temp = tmp1[0].sum_temp + tmp[i].temperatura;
            tmp1[0].reps ++;
            if( tmp[i].temperatura > tmp1[0].max_temp){
                tmp1[0].max_temp = tmp[i].temperatura;
            }
            if( tmp[i].temperatura < tmp1[0].min_temp){
                tmp1[0].min_temp = tmp[i].temperatura;
            }
        }
    }


    for(i = 0; i < n; i++){
        for(j = 0; j < i; j++){
            if(strcmp(tmp[i].pais, tmp[j].pais) != 0){ 
    // If all the previous countries are different from the current one(which means it's a new country) set is_valid to 1
                is_valid = 1;
            }else{
                is_valid = 0;
            }
            if( is_valid == 0)
                break;
        }
        if(is_valid == 1){
            //If it's a new country create an array entry for the new country
            tmp1 = (pais_temp *)realloc(tmp1, (array_size+1)*sizeof(pais_temp));
            strcpy(tmp1[array_size].pais, tmp[i].pais);
            tmp1[array_size].sum_temp = 0;
            tmp1[array_size].reps = 0;
            tmp1[array_size].average_temp = 0;
            tmp1[array_size].min_temp = 10000;
            tmp1[array_size].max_temp = -10000;
            tmp1[array_size].amplitude = 0;
            array_size++;
            for(k = 0; k < n; k++){
                if(strcmp(tmp1[array_size-1].pais, tmp[k].pais) == 0){
                    //Sums all the temperatures for the selected country and the respective reps
                    tmp1[array_size-1].sum_temp = tmp1[array_size-1].sum_temp + tmp[k].temperatura;
                    tmp1[array_size-1].reps ++;
                    if( tmp[k].temperatura > tmp1[array_size-1].max_temp){
                        tmp1[array_size-1].max_temp = tmp[k].temperatura;
                    }
                    if( tmp[k].temperatura < tmp1[array_size-1].min_temp){
                        tmp1[array_size-1].min_temp = tmp[k].temperatura;
                    }
                }
            }
        }
        is_valid = 4;
    }

    for( i = 0; i < array_size; i++){
        //Calculates the average temps and the span for each country
        tmp1[i].average_temp = tmp1[i].sum_temp / tmp1[i].reps;
        tmp1[i].amplitude = tmp1[i].max_temp - tmp1[i].min_temp;
    }

    tmp2 = (pais_temp *)malloc( (array_size)*sizeof(pais_temp));
    tmp3 = (pais_temp *)malloc( (array_size)*sizeof(pais_temp));

    //Copies the tmp1 information to tmp2 and tmp3
    for(i = 0; i < array_size; i++){
        tmp2[i].average_temp = tmp1[i].average_temp;
        strcpy(tmp2[i].pais, tmp1[i].pais);
        tmp2[i].reps = tmp1[i].reps;
        tmp2[i].min_temp = tmp1[i].min_temp;
        tmp2[i].max_temp = tmp1[i].max_temp;
        tmp2[i].amplitude = tmp1[i].amplitude;

        tmp3[i].average_temp = tmp1[i].average_temp;
        strcpy(tmp3[i].pais, tmp1[i].pais);
        tmp3[i].reps = tmp1[i].reps;
        tmp3[i].min_temp = tmp1[i].min_temp;
        tmp3[i].max_temp = tmp1[i].max_temp;
        tmp3[i].amplitude = tmp1[i].amplitude;
    }

    //Uses bubble sort to sort the tmp1 ascending according to temperatures
    for (i = 0; i < array_size; ++i){
        for (j = i + 1; j < array_size; ++j){
            if (tmp1[i].average_temp > tmp1[j].average_temp) {
                a.average_temp = tmp1[i].average_temp;
                strcpy(a.pais, tmp1[i].pais);
                a.reps = tmp1[i].reps;
                a.min_temp = tmp1[i].min_temp;
                a.max_temp = tmp1[i].max_temp;
                a.amplitude = tmp1[i].amplitude;

                tmp1[i].average_temp = tmp1[j].average_temp;
                strcpy(tmp1[i].pais, tmp1[j].pais);
                tmp1[i].reps = tmp1[j].reps;
                tmp1[i].min_temp = tmp1[j].min_temp;
                tmp1[i].max_temp = tmp1[j].max_temp;
                tmp1[i].amplitude = tmp1[j].amplitude;

                tmp1[j].average_temp = a.average_temp;
                strcpy(tmp1[j].pais, a.pais);
                tmp1[j].reps = a.reps;
                tmp1[j].min_temp = a.min_temp;
                tmp1[j].max_temp = a.max_temp;
                tmp1[j].amplitude = a.amplitude;
            }
        }
    }

    //Uses bubble sort to sort the tmp2 descending according to temperatures
    for (i = 0; i < array_size; ++i){
        for (j = i + 1; j < array_size; ++j){
            if (tmp2[i].average_temp < tmp2[j].average_temp){
                a.average_temp = tmp2[i].average_temp;
                strcpy(a.pais, tmp2[i].pais);
                a.reps = tmp2[i].reps;
                a.min_temp = tmp2[i].min_temp;
                a.max_temp = tmp2[i].max_temp;
                a.amplitude = tmp2[i].amplitude;

                tmp2[i].average_temp = tmp2[j].average_temp;
                strcpy(tmp2[i].pais, tmp2[j].pais);
                tmp2[i].reps = tmp2[j].reps;
                tmp2[i].min_temp = tmp2[j].min_temp;
                tmp2[i].max_temp = tmp2[j].max_temp;
                tmp2[i].amplitude = tmp2[j].amplitude;

                tmp2[j].average_temp = a.average_temp;
                strcpy(tmp2[j].pais, a.pais);
                tmp2[j].reps = a.reps;
                tmp2[j].min_temp = a.min_temp;
                tmp2[j].max_temp = a.max_temp;
                tmp2[j].amplitude = a.amplitude;
            }
        }
    }

    //Uses bubble sort to sort the tmp3 descending according to span
    for (i = 0; i < array_size; ++i){
        for (j = i + 1; j < array_size; ++j){
            if (tmp3[i].amplitude < tmp3[j].amplitude){
                a.average_temp = tmp3[i].average_temp;
                strcpy(a.pais, tmp3[i].pais);
                a.reps = tmp3[i].reps;
                a.min_temp = tmp3[i].min_temp;
                a.max_temp = tmp3[i].max_temp;
                a.amplitude = tmp3[i].amplitude;

                tmp3[i].average_temp = tmp3[j].average_temp;
                strcpy(tmp3[i].pais, tmp3[j].pais);
                tmp3[i].reps = tmp3[j].reps;
                tmp3[i].min_temp = tmp3[j].min_temp;
                tmp3[i].max_temp = tmp3[j].max_temp;
                tmp3[i].amplitude = tmp3[j].amplitude;

                tmp3[j].average_temp = a.average_temp;
                strcpy(tmp3[j].pais, a.pais);
                tmp3[j].reps = a.reps;
                tmp3[j].min_temp = a.min_temp;
                tmp3[j].max_temp = a.max_temp;
                tmp3[j].amplitude = a.amplitude;
            }
        }
    }
  
    printf("Min Temps   |   Max Temps    | Max span\n");
    printf("---------------------------------------------\n");
    for(i = 0; i < N; i++){
        printf(" %s    | %s    | %s \n", tmp1[i].pais, tmp2[i].pais, tmp3[i].pais); 
    }

    getchar();


    free(tmp1);
    free(tmp2);
    free(tmp3);
    free(tmp);
}

/*AnaliseTempAnoCity: Prints the N hottest and coldes cities and the biggest spans -> For a specific year
*/
void AnaliseTempAnoCity(node_t_city **_head){
    int ano, N = 0;
    int i = 0, n = 0;
    int j = 0;
    int k = 0;
    node_t_city * aux = *_head;
    dados_city *tmp = NULL;
    int is_valid = 4;
    int array_size = 0;

    city_temp * tmp1 = NULL;
    city_temp * tmp2 = NULL;
    city_temp * tmp3 = NULL;

    city_temp a;

    printf("Insira o ano a analisar: ");
    scanf("%d", &ano);


    while(aux!= NULL) {
        if(aux->payload.dt.ano == ano) {
            //Creates an array which only contains the information of the selected year so the proccessing is faster
            tmp = (dados_city *)realloc(tmp, (i+1)*sizeof(dados_city));
            tmp[i] = aux->payload;
            i++;
        }
        aux=aux->next;
    }
    n=i;

    do{
    printf("Insira o valor do N: ");
    scanf("%d", &N);
        if(N > 20 || N < 1){
            printf("O valor de N tem de estar entre 1 e 20\n");
        }
    }while(N > 20 || N < 1);

    //Creates the first entry in the tmp1 array
    tmp1 = (city_temp *)malloc(sizeof(city_temp));
    strcpy(tmp1[0].cidade, tmp[0].cidade);
    tmp1[0].sum_temp = 0;
    tmp1[0].reps = 0;
    tmp1[0].average_temp = 0;
    tmp1[0].min_temp = 10000;
    tmp1[0].max_temp = -10000;
    tmp1[0].amplitude = 0;
    array_size = 1;

    //Calculates the maximum and minimum temperature for the first element only as well as the sum of all temperatures and reps
    for(i = 0; i < n; i++){
        if(strcmp(tmp[0].cidade, tmp[i].cidade) == 0){
            tmp1[0].sum_temp = tmp1[0].sum_temp + tmp[i].temperatura;
            tmp1[0].reps ++;
            if( tmp[i].temperatura > tmp1[0].max_temp){
                tmp1[0].max_temp = tmp[i].temperatura;
            }
            if( tmp[i].temperatura < tmp1[0].min_temp){
                tmp1[0].min_temp = tmp[i].temperatura;
            }
        }
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < i; j++){
            if(strcmp(tmp[i].cidade, tmp[j].cidade) != 0){
                // If all the previous cities are different from the current one(which means it's a new city) set is_valid to 1
                is_valid = 1;
                // array_size++;
            }else{
                is_valid = 0;
            }
            if( is_valid == 0)
                break;
        }
        if(is_valid == 1){
            //If it's a new city create an array entry for the new city
            tmp1 = (city_temp *)realloc(tmp1, (array_size+1)*sizeof(city_temp));
            strcpy(tmp1[array_size].cidade, tmp[i].cidade);
            tmp1[array_size].sum_temp = 0;
            tmp1[array_size].reps = 0;
            tmp1[array_size].average_temp = 0;
            tmp1[array_size].min_temp = 10000;
            tmp1[array_size].max_temp = -10000;
            tmp1[array_size].amplitude = 0;
            array_size++;
            for(k = 0; k < n; k++){
                if(strcmp(tmp1[array_size-1].cidade, tmp[k].cidade) == 0){
                    //Sums all the temperatures for the selected city and the respective reps
                    tmp1[array_size-1].sum_temp = tmp1[array_size-1].sum_temp + tmp[k].temperatura;
                    tmp1[array_size-1].reps ++;
                    if( tmp[k].temperatura > tmp1[array_size-1].max_temp){
                        tmp1[array_size-1].max_temp = tmp[k].temperatura;
                    }
                    if( tmp[k].temperatura < tmp1[array_size-1].min_temp){
                        tmp1[array_size-1].min_temp = tmp[k].temperatura;
                    }
                }
            }
        }
        is_valid = 4;
    }

    for( i = 0; i < array_size; i++){
        //Calculates the average temps and the span for each city
        tmp1[i].average_temp = tmp1[i].sum_temp / tmp1[i].reps;
        tmp1[i].amplitude = tmp1[i].max_temp - tmp1[i].min_temp;
    }

    tmp2 = (city_temp *)malloc( (array_size)*sizeof(city_temp));
    tmp3 = (city_temp *)malloc( (array_size)*sizeof(city_temp));

    //Copies the tmp1 information to tmp2 and tmp3
    for(i = 0; i < array_size; i++){
        tmp2[i].average_temp = tmp1[i].average_temp;
        strcpy(tmp2[i].cidade, tmp1[i].cidade);
        tmp2[i].reps = tmp1[i].reps;
        tmp2[i].min_temp = tmp1[i].min_temp;
        tmp2[i].max_temp = tmp1[i].max_temp;
        tmp2[i].amplitude = tmp1[i].amplitude;

        tmp3[i].average_temp = tmp1[i].average_temp;
        strcpy(tmp3[i].cidade, tmp1[i].cidade);
        tmp3[i].reps = tmp1[i].reps;
        tmp3[i].min_temp = tmp1[i].min_temp;
        tmp3[i].max_temp = tmp1[i].max_temp;
        tmp3[i].amplitude = tmp1[i].amplitude;
    }

    //Uses bubble sort to sort the tmp1 ascending according to temperatures
    for (i = 0; i < array_size; ++i){
        for (j = i + 1; j < array_size; ++j){
            if (tmp1[i].average_temp > tmp1[j].average_temp) {
                a.average_temp = tmp1[i].average_temp;
                strcpy(a.cidade, tmp1[i].cidade);
                a.reps = tmp1[i].reps;
                a.min_temp = tmp1[i].min_temp;
                a.max_temp = tmp1[i].max_temp;
                a.amplitude = tmp1[i].amplitude;

                tmp1[i].average_temp = tmp1[j].average_temp;
                strcpy(tmp1[i].cidade, tmp1[j].cidade);
                tmp1[i].reps = tmp1[j].reps;
                tmp1[i].min_temp = tmp1[j].min_temp;
                tmp1[i].max_temp = tmp1[j].max_temp;
                tmp1[i].amplitude = tmp1[j].amplitude;

                tmp1[j].average_temp = a.average_temp;
                strcpy(tmp1[j].cidade, a.cidade);
                tmp1[j].reps = a.reps;
                tmp1[j].min_temp = a.min_temp;
                tmp1[j].max_temp = a.max_temp;
                tmp1[j].amplitude = a.amplitude;
            }
        }
    }

    //Uses bubble sort to sort the tmp2 descending according to temperatures
    for (i = 0; i < array_size; ++i){
        for (j = i + 1; j < array_size; ++j){
            if (tmp2[i].average_temp < tmp2[j].average_temp) {
                a.average_temp = tmp2[i].average_temp;
                strcpy(a.cidade, tmp2[i].cidade);
                a.reps = tmp2[i].reps;
                a.min_temp = tmp2[i].min_temp;
                a.max_temp = tmp2[i].max_temp;
                a.amplitude = tmp2[i].amplitude;

                tmp2[i].average_temp = tmp2[j].average_temp;
                strcpy(tmp2[i].cidade, tmp2[j].cidade);
                tmp2[i].reps = tmp2[j].reps;
                tmp2[i].min_temp = tmp2[j].min_temp;
                tmp2[i].max_temp = tmp2[j].max_temp;
                tmp2[i].amplitude = tmp2[j].amplitude;

                tmp2[j].average_temp = a.average_temp;
                strcpy(tmp2[j].cidade, a.cidade);
                tmp2[j].reps = a.reps;
                tmp2[j].min_temp = a.min_temp;
                tmp2[j].max_temp = a.max_temp;
                tmp2[j].amplitude = a.amplitude;
            }
        }
    }

    //Uses bubble sort to sort the tmp3 descending according to temperatures
    for (i = 0; i < array_size; ++i){
        for (j = i + 1; j < array_size; ++j){
            if (tmp3[i].amplitude < tmp3[j].amplitude) {
                a.average_temp = tmp3[i].average_temp;
                strcpy(a.cidade, tmp3[i].cidade);
                a.reps = tmp3[i].reps;
                a.min_temp = tmp3[i].min_temp;
                a.max_temp = tmp3[i].max_temp;
                a.amplitude = tmp3[i].amplitude;

                tmp3[i].average_temp = tmp3[j].average_temp;
                strcpy(tmp3[i].cidade, tmp3[j].cidade);
                tmp3[i].reps = tmp3[j].reps;
                tmp3[i].min_temp = tmp3[j].min_temp;
                tmp3[i].max_temp = tmp3[j].max_temp;
                tmp3[i].amplitude = tmp3[j].amplitude;

                tmp3[j].average_temp = a.average_temp;
                strcpy(tmp3[j].cidade, a.cidade);
                tmp3[j].reps = a.reps;
                tmp3[j].min_temp = a.min_temp;
                tmp3[j].max_temp = a.max_temp;
                tmp3[j].amplitude = a.amplitude;
            }
        }
    }

    printf("Min Temps   |   Max Temps    | Max span\n");
    printf("--------------------------------------------\n");
    for(i = 0; i < N; i++){
        printf(" %s    | %s    | %s \n", tmp1[i].cidade, tmp2[i].cidade, tmp3[i].cidade); 
    }

    getchar();


    free(tmp1);
    free(tmp2);
    free(tmp3);
    free(tmp);
}

/**Calculates the global moving average from the inicial list year to 1860, 1910, 1960, 1990, 2013
 * 
*/
void MovingAverageGlobal(node_t_country **_head, node_t_country **_tail) {
    int m = 0;
    int anoAContar = 1860;

    printf("Insira o valor do intervalo de movimentação (em meses): ");
    scanf(" %d", &m);

    calcMonthsAverage(_head, anoAContar, m, 1860);
    calcMonthsAverage(_head, anoAContar, m, 1910);
    calcMonthsAverage(_head, anoAContar, m, 1960);
    calcMonthsAverage(_head, anoAContar, m, 1990);
    calcMonthsAverage(_head, anoAContar, m, 2013);
    getchar();

}

/*Calculates the moving average for each given interval
*/
void calcMonthsAverage(node_t_country **_head, int _anoAContar, int m, int _anoFinal) {
    node_t_country *aux = *_head;
    int anoAtual = aux->payload.dt.ano;  //Ano que vai sendo alterado conforme as iterações
    int anoInicial = aux->payload.dt.ano;
    int repsPerMonth[12] = {0};   //Month reps count for the medium calculation
    int count = 1;
    float *temperaturas[12] = {0}; //Array to store the medium temperatures for each month(by year)
    float sumMAverage = 0;
    int makesCount = 0; //Só efetua a conta qnd n encontrou nenhum valor a 0, quando faz o MAverage (ou seja qnd makesCount != m)
    float *tempMAverage[12] = {0}; //Stores the Moving Average in respect to each month
    float *anualMAverage = NULL;
    float max = -1000, min = 1000;
    int zerosOnCounts = 0;

    //Inicializes the first array element
    for(int i=0; i< 12; i++) {
        temperaturas[i] = (float*)malloc(sizeof(float));
        temperaturas[i][count-1] = 0;
    }

    while(aux != NULL && aux->payload.dt.ano <= _anoFinal) {
        if(aux->payload.dt.ano == anoAtual) {
            for(int i=0; i<12; i++) {
                //For each year, stores on 1 of the 12 array vectors a sum of the respective temperature and updates the repsPerMonth
                if(aux->payload.dt.mes == i+1) {
                    repsPerMonth[i]++;
                    temperaturas[i][count-1] = temperaturas[i][count-1] + aux->payload.temperatura;
                }
            }
        }else { //Makes the medium count and reallocates memory for the next iteration
            for(int i=0; i<12; i++) {
                if(temperaturas[i][count-1] != 0)
                    temperaturas[i][count-1] = temperaturas[i][count-1] / repsPerMonth[i];
            }
            //Reset das reps
            for(int i=0; i<12; i++) {
                repsPerMonth[i] = 0;
            }
            anoAtual = aux->payload.dt.ano;
            count++;
            for(int i=0; i< 12; i++) {
                temperaturas[i] = (float*)realloc(temperaturas[i], count*sizeof(float));
                temperaturas[i][count-1] = 0;
            }

            //Pq o primeiro elemento não foi contabilizado
            for(int i=0; i<12; i++) {
                if(aux->payload.dt.mes == i+1) {
                    repsPerMonth[i]++;
                    temperaturas[i][count-1] = temperaturas[i][count-1] + aux->payload.temperatura;
                }
            }

        }
        aux = aux->next;
    }



    for(int i=0; i<12; i++) {
        tempMAverage[i] = (float*)calloc(count, sizeof(float));  //Calloc() para q tudo seja inicializado a 0, assim se ao não existirem dados a conta n for efetuada -> fica a 0
    }
    //Realizar o Moving Average aos meses:
    for(int i=0; i<12; i++) {
        for(int j=0; j<m-1; j++) {
            tempMAverage[i][j] = temperaturas[i][j];
        }
    }

    for(int i = 0; i < 12; i++) {
        for(int j = m-1; j < count; j++) {
            for(int k=0; k < m; k++) {
                sumMAverage += temperaturas[i][j-k];
                if(temperaturas[i][j-k] != 0) 
                    makesCount++;
            }
            if(makesCount == m) {
                tempMAverage[i][j] = sumMAverage / (float)m;
            }
            makesCount = 0;
            sumMAverage = 0;
        }
    }

    //Realiza a média de todos os meses, transformando o array duplo num vetor (por anos)
    anualMAverage = (float*)calloc(count, sizeof(float));
    for(int i=0; i<count; i++) {
        if(tempMAverage[0][i]!=0 && tempMAverage[1][i]!=0 && tempMAverage[2][i]!=0 && tempMAverage[3][i]!=0 && tempMAverage[4][i]!=0 && tempMAverage[5][i]!=0 && tempMAverage[6][i]!=0 && tempMAverage[7][i]!=0 && tempMAverage[8][i]!=0 && tempMAverage[9][i]!=0 && tempMAverage[10][i]!=0 && tempMAverage[11][i]!=0) {
            anualMAverage[i] = tempMAverage[0][i] + tempMAverage[1][i] + tempMAverage[2][i] + tempMAverage[3][i] + tempMAverage[4][i] + tempMAverage[5][i] + tempMAverage[6][i] + tempMAverage[7][i] + tempMAverage[8][i] + tempMAverage[9][i] + tempMAverage[10][i] + tempMAverage[11][i];
            anualMAverage[i] = anualMAverage[i] / 12;
        }
    }

    //Count - 1 pq é normal o ultimo ano não apresentar todos os valores para todos os meses
    for(int i=0; i<count-1; i++) {
        if(anualMAverage[i] != 0) {
            if(anualMAverage[i] > max)
                max = anualMAverage[i];
            if(anualMAverage[i] < min)
                min = anualMAverage[i];
        }else {
            zerosOnCounts = 1;
        }
    }
    
    if(max-min != -2000) { //Se não existirem dados no ano a contabilizar(acontece em listras filtradas)
        if(zerosOnCounts == 1) { //Se existerem certos países em que não existe dados para algum mes contabilzado
            printf("De %d até %d a Temperatura Global variou %f ºC\n", anoInicial, anoAtual, max-min);
            printf("Este resultado pode apresentar algumas incertezas pois existem meses em falta nos dados\n");
        }else {
            printf("De %d até %d a Temperatura Global variou %f ºC\n", anoInicial, anoAtual, max-min);
        }
    } else 
        printf("Dados não contabilizados até %d\n", anoAtual);
    
    free(anualMAverage);
    for(int i=0; i<12; i++) {
        free(tempMAverage[i]);
        free(temperaturas[i]);
    }
}

/**Calculates a specific country moving average from the inicial list year to 1860, 1910, 1960, 1990, 2013
 * 
*/
void MovingAverageCountries(node_t_country **_head, node_t_country **_tail) {
    int m = 0;
    int anoAContar = 1860;
    char pais[40] = {0};

    printf("Insira o valor do intervalo de movimentação (em meses): ");
    scanf(" %d", &m);

    printf("Insira o nome do pais a filtrar: ");
    scanf(" %s", pais);

    calcMonthsAverageCountries(_head, anoAContar, m, 1860, pais);
    calcMonthsAverageCountries(_head, anoAContar, m, 1910, pais);
    calcMonthsAverageCountries(_head, anoAContar, m, 1960, pais);
    calcMonthsAverageCountries(_head, anoAContar, m, 1990, pais);
    calcMonthsAverageCountries(_head, anoAContar, m, 2013, pais);
    getchar();

}

void calcMonthsAverageCountries(node_t_country **_head, int _anoAContar, int m, int _anoFinal, char _pais[40]) {
    node_t_country *aux = *_head;
    int anoAtual = aux->payload.dt.ano;
    int anoInicial = aux->payload.dt.ano;
    int repsPerMonth[12] = {0};
    int count = 1;
    float *temperaturas[12] = {0};
    float sumMAverage = 0;
    int makesCount = 0; //Só efetua a conta qnd n encontrou nenhum valor a 0, quando faz o MAverage (ou seja qnd makesCount != m)
    float *tempMAverage[12] = {0};
    float *anualMAverage = NULL;
    float max = -1000, min = 1000;
    int zerosOnCounts = 0;


    for(int i=0; i< 12; i++) {
        temperaturas[i] = (float*)malloc(sizeof(float));
        temperaturas[i][count-1] = 0;
    }

    while(aux != NULL && aux->payload.dt.ano <= _anoFinal) {
        if(!strcmp(aux->payload.pais, _pais)){ //Only counts the nodes that are from the user entered country 
            if(aux->payload.dt.ano == anoAtual) {
                for(int i=0; i<12; i++) {
                    if(aux->payload.dt.mes == i+1) {
                        repsPerMonth[i]++;
                        temperaturas[i][count-1] = temperaturas[i][count-1] + aux->payload.temperatura;
                    }
                }
            }else {
                for(int i=0; i<12; i++) {
                    if(temperaturas[i][count-1] != 0)
                        temperaturas[i][count-1] = temperaturas[i][count-1] / repsPerMonth[i];
                }
                //Reset das reps
                for(int i=0; i<12; i++) {
                    repsPerMonth[i] = 0;
                }
                anoAtual = aux->payload.dt.ano;
                count++;
                for(int i=0; i< 12; i++) {
                    temperaturas[i] = (float*)realloc(temperaturas[i], count*sizeof(float));
                    temperaturas[i][count-1] = 0;
                }

                //Pq o primeiro elemento não foi contabilizado
                for(int i=0; i<12; i++) {
                    if(aux->payload.dt.mes == i+1) {
                        repsPerMonth[i]++;
                        temperaturas[i][count-1] = temperaturas[i][count-1] + aux->payload.temperatura;
                    }
                }

            }
        }
        aux = aux->next;
    }



    for(int i=0; i<12; i++) {
        tempMAverage[i] = (float*)calloc(count, sizeof(float));  //Calloc() para q tudo seja inicializado a 0, assim se ao não existirem dados a conta n for efetuada -> fica a 0
    }
    //Realizar o Moving Average aos meses:
    for(int i=0; i<12; i++) {
        for(int j=0; j<m-1; j++) {
            tempMAverage[i][j] = temperaturas[i][j];
        }
    }

    for(int i = 0; i < 12; i++) {
        for(int j = m-1; j < count; j++) {
            for(int k=0; k < m; k++) {
                sumMAverage += temperaturas[i][j-k];
                if(temperaturas[i][j-k] != 0) 
                    makesCount++;
            }
            if(makesCount == m) {
                tempMAverage[i][j] = sumMAverage / (float)m;
            }
            makesCount = 0;
            sumMAverage = 0;
        }
    }

    //Realiza a média de todos os meses, transformando o array duplo num vetor (por anos)
    anualMAverage = (float*)calloc(count, sizeof(float));
    for(int i=0; i<count; i++) {
        if(tempMAverage[0][i]!=0 && tempMAverage[1][i]!=0 && tempMAverage[2][i]!=0 && tempMAverage[3][i]!=0 && tempMAverage[4][i]!=0 && tempMAverage[5][i]!=0 && tempMAverage[6][i]!=0 && tempMAverage[7][i]!=0 && tempMAverage[8][i]!=0 && tempMAverage[9][i]!=0 && tempMAverage[10][i]!=0 && tempMAverage[11][i]!=0) {
            anualMAverage[i] = tempMAverage[0][i] + tempMAverage[1][i] + tempMAverage[2][i] + tempMAverage[3][i] + tempMAverage[4][i] + tempMAverage[5][i] + tempMAverage[6][i] + tempMAverage[7][i] + tempMAverage[8][i] + tempMAverage[9][i] + tempMAverage[10][i] + tempMAverage[11][i];
            anualMAverage[i] = anualMAverage[i] / 12;
        }
    }

    //Count - 1 pq é normal o ultimo ano não apresentar todos valores para todos os meses
    for(int i=0; i<count-1; i++) {
        if(anualMAverage[i] != 0) {
            if(anualMAverage[i] > max)
                max = anualMAverage[i];
            if(anualMAverage[i] < min)
                min = anualMAverage[i];
        }else {
            zerosOnCounts = 1;
        }
    }
    
    if(max-min != -2000) {
        if(zerosOnCounts == 1) {
            printf("De %d até %d a Temperatura Global variou %f ºC\n", anoInicial, anoAtual, max-min);
            printf("Este resultado pode apresentar algumas incertezas pois existem meses em falta nos dados\n");
        }else {
            printf("De %d até %d a Temperatura Global variou %f ºC\n", anoInicial, anoAtual, max-min);
        }
    } else 
        printf("Dados não contabilizados até %d\n", anoAtual);
    
    free(anualMAverage);
    for(int i=0; i<12; i++) {
        free(tempMAverage[i]);
        free(temperaturas[i]);
    }
}

/**Calculates a specific city moving average from the inicial list year to 1860, 1910, 1960, 1990, 2013
 * 
*/
void MovingAverageCities(node_t_city **_head, node_t_city **_tail) {
    int m = 0;
    int anoAContar = 1860;
    char cidade[40] = {0};

    printf("Insira o valor do intervalo de movimentação (em meses): ");
    scanf(" %d", &m);

    printf("Insira o nome da cidade a filtrar: ");
    scanf(" %s", cidade);

    calcMonthsAverageCities(_head, anoAContar, m, 1860, cidade);
    calcMonthsAverageCities(_head, anoAContar, m, 1910, cidade);
    calcMonthsAverageCities(_head, anoAContar, m, 1960, cidade);
    calcMonthsAverageCities(_head, anoAContar, m, 1990, cidade);
    calcMonthsAverageCities(_head, anoAContar, m, 2013, cidade);
    getchar();

}

void calcMonthsAverageCities(node_t_city **_head, int _anoAContar, int m, int _anoFinal, char _cidade[40]) {
    node_t_city *aux = *_head;
    int anoAtual = aux->payload.dt.ano;
    int anoInicial = aux->payload.dt.ano;
    int repsPerMonth[12] = {0};
    int count = 1;
    float *temperaturas[12] = {0};
    float sumMAverage = 0;
    int makesCount = 0; //Só efetua a conta qnd n encontrou nenhum valor a 0, quando faz o MAverage (ou seja qnd makesCount != m)
    float *tempMAverage[12] = {0};
    float *anualMAverage = NULL;
    float max = -1000, min = 1000;
    int zerosOnCounts = 0;


    for(int i=0; i< 12; i++) {
        temperaturas[i] = (float*)malloc(sizeof(float));
        temperaturas[i][count-1] = 0;
    }

    while(aux != NULL && aux->payload.dt.ano <= _anoFinal) {
        if(!strcmp(aux->payload.cidade, _cidade)){  //Only counts the nodes that are from the user entered city
            if(aux->payload.dt.ano == anoAtual) {
                for(int i=0; i<12; i++) {
                    if(aux->payload.dt.mes == i+1) {
                        repsPerMonth[i]++;
                        temperaturas[i][count-1] = temperaturas[i][count-1] + aux->payload.temperatura;
                    }
                }
            }else {
                for(int i=0; i<12; i++) {
                    if(temperaturas[i][count-1] != 0)
                        temperaturas[i][count-1] = temperaturas[i][count-1] / repsPerMonth[i];
                }
                //Reset das reps
                for(int i=0; i<12; i++) {
                    repsPerMonth[i] = 0;
                }
                anoAtual = aux->payload.dt.ano;
                count++;
                for(int i=0; i< 12; i++) {
                    temperaturas[i] = (float*)realloc(temperaturas[i], count*sizeof(float));
                    temperaturas[i][count-1] = 0;
                }

                //Pq o primeiro elemento não foi contabilizado
                for(int i=0; i<12; i++) {
                    if(aux->payload.dt.mes == i+1) {
                        repsPerMonth[i]++;
                        temperaturas[i][count-1] = temperaturas[i][count-1] + aux->payload.temperatura;
                    }
                }

            }
        }
        aux = aux->next;
    }



    for(int i=0; i<12; i++) {
        tempMAverage[i] = (float*)calloc(count, sizeof(float));  //Calloc() para q tudo seja inicializado a 0, assim se ao não existirem dados a conta n for efetuada -> fica a 0
    }
    //Realizar o Moving Average aos meses:
    for(int i=0; i<12; i++) {
        for(int j=0; j<m-1; j++) {
            tempMAverage[i][j] = temperaturas[i][j];
        }
    }

    for(int i = 0; i < 12; i++) {
        for(int j = m-1; j < count; j++) {
            for(int k=0; k < m; k++) {
                sumMAverage += temperaturas[i][j-k];
                if(temperaturas[i][j-k] != 0) 
                    makesCount++;
            }
            if(makesCount == m) {
                tempMAverage[i][j] = sumMAverage / (float)m;
            }
            makesCount = 0;
            sumMAverage = 0;
        }
    }

    //Realiza a média de todos os meses, transformando o array duplo num vetor (por anos)
    anualMAverage = (float*)calloc(count, sizeof(float));
    for(int i=0; i<count; i++) {
        if(tempMAverage[0][i]!=0 && tempMAverage[1][i]!=0 && tempMAverage[2][i]!=0 && tempMAverage[3][i]!=0 && tempMAverage[4][i]!=0 && tempMAverage[5][i]!=0 && tempMAverage[6][i]!=0 && tempMAverage[7][i]!=0 && tempMAverage[8][i]!=0 && tempMAverage[9][i]!=0 && tempMAverage[10][i]!=0 && tempMAverage[11][i]!=0) {
            anualMAverage[i] = tempMAverage[0][i] + tempMAverage[1][i] + tempMAverage[2][i] + tempMAverage[3][i] + tempMAverage[4][i] + tempMAverage[5][i] + tempMAverage[6][i] + tempMAverage[7][i] + tempMAverage[8][i] + tempMAverage[9][i] + tempMAverage[10][i] + tempMAverage[11][i];
            anualMAverage[i] = anualMAverage[i] / 12;
        }
    }

    //Count - 1 pq é normal o ultimo ano não apresentar todos valores para todos os meses
    for(int i=0; i<count-1; i++) {
        if(anualMAverage[i] != 0) {
            if(anualMAverage[i] > max)
                max = anualMAverage[i];
            if(anualMAverage[i] < min)
                min = anualMAverage[i];
        }else {
            zerosOnCounts = 1;
        }
    }
    
    if(max-min != -2000) {
        if(zerosOnCounts == 1) {
            printf("De %d até %d a Temperatura dessa cidade variou %f ºC\n", anoInicial, anoAtual, max-min);
            printf("Este resultado pode apresentar algumas incertezas pois existem meses em falta nos dados\n");
        }else {
            printf("De %d até %d a Temperatura dessa cidade variou %f ºC\n", anoInicial, anoAtual, max-min);
        }
    } else 
        printf("Dados não contabilizados até %d\n", anoAtual);
    
    free(anualMAverage);
    for(int i=0; i<12; i++) {
        free(tempMAverage[i]);
        free(temperaturas[i]);
    }
}