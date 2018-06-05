#ifndef _LISTS_H 
#define _LISTS_H 
#include "structs.h"

node_t_country * NewCountry(dados_country);

void InsertOrdenatedCountry(node_t_country **, node_t_country **, dados_country);

void traverseCountries(node_t_country *);

void RemoveNodesByInterval(node_t_country **, node_t_country **, int, int);

void RemoveNodesByMonth(node_t_country **, node_t_country **, int, int);

void insertAuxYear(node_t_auxYear **, node_t_auxYear **, int, dados_country);
node_t_auxYear * NewAuxYear(int);
void miniTraverse(node_t_auxYear *); 

void stitching(node_t_auxYear *, node_t_auxYear *);

void traverseCities(node_t_city *);
node_t_city *NewCity(dados_city);
void InsertCityList(node_t_city **, node_t_city **, dados_city);
void RemoveCityNodesByInterval(node_t_city **, node_t_city **, int , int );
void RemoveCityNodesByMonth(node_t_city **, node_t_city **, int, int);


#endif

