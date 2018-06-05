#ifndef _MENUS_H 
#define _MENUS_H 
#include "structs.h"
#include "lists.h"

int MainMenu();
int FiltragemDeDados(node_t_country **, node_t_country **, node_t_city **, node_t_city **, char[], char[]);
int HistoricoTemperaturas(node_t_country **, node_t_country **, node_t_city **, node_t_city **);
int AnaliseTemperaturaPorAno(node_t_country **, node_t_city **);
int AnaliseTemperaturaGlobal(node_t_country **, node_t_country **, node_t_city **, node_t_city **);
#endif