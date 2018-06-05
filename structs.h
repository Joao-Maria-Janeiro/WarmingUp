#ifndef _STRUCTS_H 
#define _STRUCTS_H 

typedef struct{
    int dia;
    int mes;
    int ano;
} data;

 typedef struct{
     float angular;
     char direcao;
 } geo_coord;

 typedef struct{
    data dt;
    float temperatura;
    float incerteza;
    char pais[400];
}dados_country;

typedef struct{
    data dt;
    float temperatura;
    float incerteza;
    char pais[400];
    char cidade[400];
    geo_coord latitude;
    geo_coord longitude;
}dados_city;

typedef struct node{
    dados_country payload;
    struct node *next;
    struct node *prev;
} node_t_country;

typedef struct node_city{
    dados_city payload;
    struct node_city *next;
    struct node_city *prev;
} node_t_city;


typedef struct node_auxYear{
    int ano;
    node_t_country *head;
    node_t_country *tail;
    struct node_auxYear *next;
    struct node_auxYear *prev;
} node_t_auxYear;


void loadCountryFromFile(char [], node_t_country **, node_t_country **);

void loadCityFromFile(char [], node_t_city **, node_t_city **);

#endif
