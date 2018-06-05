#ifndef _STATISTICS_H
#define _STATISTICS_H
#include "structs.h"
#include "lists.h"

typedef struct pais_temp{
    float sum_temp;
    char pais[400];
    int reps;
    float average_temp;
    float min_temp;
    float max_temp;
    float amplitude;
}pais_temp;

typedef struct city_temp{
    float sum_temp;
    char cidade[400];
    int reps;
    float average_temp;
    float min_temp;
    float max_temp;
    float amplitude;
}city_temp;

void MinMaxMedGlobalCalc(node_t_country **, node_t_country **, int );
void MinMaxMedCountryCalc(node_t_country **, node_t_country **, int, char[] );
void MinMaxMedCityCalc(node_t_city **, node_t_city **, int, char[] );
void AnaliseTempAnoCountry(node_t_country **);
void AnaliseTempAnoCity(node_t_city **);
void MovingAverageGlobal(node_t_country **, node_t_country **);
void MovingAverageGlobal(node_t_country **, node_t_country **);
void MovingAverageCountries(node_t_country **, node_t_country **);
void calcMonthsAverage(node_t_country **, int, int, int);
void calcMonthsAverageCountries(node_t_country **, int, int, int, char[]);


void calcMonthsAverageCities(node_t_city **, int , int , int , char []);
void MovingAverageCities(node_t_city **, node_t_city **);

#endif