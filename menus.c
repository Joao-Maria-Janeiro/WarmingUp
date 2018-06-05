/**
 * File for managing the menus to print and return the user chosen option 
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menus.h"
#include "structs.h"
#include "lists.h"
#include "statistics.h"


/**MainMenu
 * returns 1-4 with the user input to select the corresponding menu
 */
int MainMenu() {
    int chosenOption = 0;
    char tmp[30] = {0};

    do {
        system("clear");  //Specific command for linux, for cleaning the screen, in windows is system("cls");
        printf("**************************************************\n");
        printf("*     1. Filtragem de dados                      *\n*     2. Histórico de temperaturas               *\n*     3. Análise da temperatura por ano          *\n*     4. Análise da temperatura global           *\n*     5. Sair                                    *\n");
        printf("**************************************************\n\n");
        fgets(tmp, 30, stdin);
        sscanf(tmp, " %d",  &chosenOption);
    } while(chosenOption<1 || chosenOption>5 );

    return chosenOption;
}

/**FiltragemDeDados
 * returns 1-3 and summons the corresponding functions to process the data
 * 1. Limpa critérios
 * 2. Escolhe intervalo para análise
 * 3. Escolhe mês para análise
 */
int FiltragemDeDados(node_t_country **_headCountry, node_t_country **_tailCountry, node_t_city **_headCity, node_t_city **_tailCity, char _fileNameCountry[], char _fileNameCity[]) {
    int chosenOption = 0;
    char tmp[30] = {0};
    int filterYear=0, filterMonth = 0;
    int initMonth=0, finalMonth = 0;

    do {
        system("clear");  //Specific command for linux, for cleaning the screen, in windows is system("cls");
        printf("**************************************************\n");
        printf("*     1. Limpa critérios                         *\n*     2. Escolhe intervalo para análise          *\n*     3. Escolhe mês para análise                *\n");
        printf("**************************************************\n\n");
        fgets(tmp, 30, stdin);
        sscanf(tmp, " %d",  &chosenOption);
    } while(chosenOption<1 || chosenOption>3 );

    switch(chosenOption) {
        case 1:
            system("clear");
            //Frees the filtered lists
            node_t_country *aux = *_headCountry;
            node_t_city *tmp = *_headCity;
            while(aux->next != NULL) {
                aux=aux->next;
                free(aux->prev);
            }
            free(aux);
            while(tmp->next != NULL) {
                tmp= tmp->next;
                free(tmp->prev);
            }
            free(tmp);
            *_headCity = NULL;
            *_tailCity = NULL;
            printf("Espere 1 minuto!\n");
            *_headCountry = NULL;
            *_tailCountry = NULL;
            //Creates both lists from the files again
            loadCountryFromFile(_fileNameCountry, _headCountry, _tailCountry); //Faz o load completo da lista
            loadCityFromFile(_fileNameCity, _headCity, _tailCity);
            return 1;
            break;
        case 2:
            system("clear");
            printf("Selecione um ano e um mês separados por um espaço: ");
            scanf(" %d %d", &filterYear, &filterMonth);
            getchar(); //for the enter char
            //Elimina nodes da lista de acordo com o filtro inserido
            RemoveNodesByInterval( _headCountry, _tailCountry, filterYear, filterMonth);
            RemoveCityNodesByInterval( _headCity, _tailCity, filterYear, filterMonth);
            break;
        case 3:
            system("clear");
            printf("Selecione um mês inicial e um final separados por um espaço: ");
            scanf(" %d %d", &initMonth, &finalMonth);
            getchar(); //For the enter char
            //Elimina nodes da lista de acordo com o filtro inserido
            RemoveNodesByMonth( _headCountry, _tailCountry, initMonth, finalMonth);
            RemoveCityNodesByMonth( _headCity, _tailCity, initMonth, finalMonth);
            break;
    }

    return chosenOption;
}

/**HistoricoTemperaturas
 * returns 1-3 and summons the corresponding functions to process the data
 * 1. Global
 * 2. Por pais
 * 3. Por cidade
 */
int HistoricoTemperaturas(node_t_country **_headCountries, node_t_country **_tailCountries, node_t_city **_headCities, node_t_city **_tailCities){
    int chosenOption = 0;
    char tmp[50] = {0};
    int interval = 0;
    int length = 0;
    char linha[300] = {0};
    system("clear");
    printf("Digite o periodo de tempo da amostragem em anos: ");
    scanf(" %d", &interval);

    system("clear");

    do {
        system("clear");  //Specific command for linux, for cleaning the screen, in windows is system("cls");
        printf("**************************************************\n");
        printf("*     1. Global:aplica-se a todos os  países     *\n*     2. Por país:aplica-se a um único país      *\n*     3. Por cidade: aplica-se a uma única cidade*\n");
        printf("**************************************************\n\n");
        fgets(tmp, 50, stdin);
        sscanf(tmp, " %d",  &chosenOption);
    } while(chosenOption<1 || chosenOption>3 );

    switch(chosenOption) {
        case 1:
            //Summons the function to calculate the minimum and max values of each interval
            MinMaxMedGlobalCalc(_headCountries, _tailCountries, interval);
            break;
        case 2:
            printf( "Digite o país a filtrar: " );
            fgets(linha, 300, stdin);
            sscanf(linha, " %[^\n]", tmp);
            length = strlen(tmp);
            tmp[length] = '\0';
            //Summons the function to calculate the minimum and max values of each interval for a selected country
            MinMaxMedCountryCalc(_headCountries, _tailCountries, interval, tmp);
            getchar();
            break;
        case 3:
            printf("Digite a cidade a filtrar: ");
            fgets(linha, 300, stdin);
            sscanf(linha, " %[^\n]", tmp);
            length = strlen(tmp);
            tmp[length] = '\0';
            //Summons the function to calculate the minimum and max values of each interval for a selected city
            MinMaxMedCityCalc(_headCities, _tailCities, interval, tmp);
            break;
        default:
            printf("Erro na opção escolhida");
            exit(EXIT_FAILURE);
    }

    return chosenOption;
}

/**AnaliseTemperaturaPorAno
 * returns 1-3 and summons the corresponding functions to process the data
 * 1. Global
 * 2. Por pais
 * 3. Por cidade
 */
int AnaliseTemperaturaPorAno(node_t_country **_headCountries, node_t_city **_headCities){
    int chosenOption = 0;
    char tmp[30] = {0};

    do {
        system("clear");  //Specific command for linux, for cleaning the screen, in windows is system("cls");
        printf("**************************************************\n");
        printf("*     1. Análise por país                        *\n*     2. Análise por cidade                      *\n");
        printf("**************************************************\n\n");
        fgets(tmp, 30, stdin);
        sscanf(tmp, " %d",  &chosenOption);
    } while(chosenOption<1 || chosenOption>2 );

    switch(chosenOption) {
        case 1:
            AnaliseTempAnoCountry(_headCountries);
            break;
        case 2:
            AnaliseTempAnoCity(_headCities);
            break;
    }

    return chosenOption;
}


/**AnaliseTemperaturaGlobal (MovingAverage)
 * Sumons the corresponding functions between:
 * 1: Aumento da temperatura do planeta
 * 2: Aumento da temperatura de um país
 * 3: Aumento da temperatura de uma cidade
*/
int AnaliseTemperaturaGlobal(node_t_country **_headCountries, node_t_country **_tailCountries, node_t_city **_headCities, node_t_city **_tailCities){
    int chosenOption = 0;
    char tmp[30] = {0};

    do {
        system("clear");  //Specific command for linux, for cleaning the screen, in windows is system("cls");
        printf("**************************************************\n");
        printf("*   1. Aumento da Temperatura Global do Planeta  *\n*   2. Aumento da Temperatura Global do País     *\n*   3. Aumento da Temperatura Global da Cidade   *\n");
        printf("**************************************************\n\n");
        fgets(tmp, 30, stdin);
        sscanf(tmp, " %d",  &chosenOption);
    } while(chosenOption<1 || chosenOption>3 );

    switch(chosenOption) {
        case 1:
            MovingAverageGlobal(_headCountries, _tailCountries);
            break;
        case 2:
            MovingAverageCountries(_headCountries, _tailCountries);
            break;
        case 3:
        MovingAverageCities(_headCities, _tailCities);
            break;
    }

    return chosenOption;
}