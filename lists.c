#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "lists.h"

/**NewAuxYear: Creates a new auxiliar node for the years' list
 */
node_t_auxYear * NewAuxYear(int _ano) {
    node_t_auxYear *newNode = NULL;
    newNode = (node_t_auxYear*)malloc(sizeof(node_t_auxYear));
    if(newNode == NULL) {
        printf("Error alocating memory!");
        exit(EXIT_FAILURE);
    }
    newNode->ano = _ano;
    newNode->head = NULL;
    newNode->tail = NULL;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

/*InsertAuxYear:Verifies if the _payload's year already exists
* If yes: orderly inserts a new country node on the respective mini-list
* If not: creates and inserts a new year node and creates the respective mini-list with the new country node
*/
void insertAuxYear(node_t_auxYear **_head, node_t_auxYear **_tail, int _ano, dados_country _payload) {
    node_t_auxYear *aux = NULL;
    node_t_auxYear *_newNode = NULL;
    aux = *_head;
    int isValid = -1;

    if(*_head != NULL) {
        while(aux != NULL) {
            if(aux->ano == _ano) {
                InsertOrdenatedCountry(&(aux->head), &(aux->tail), _payload);
                //If the year already exists -> set's isValid to 0
                isValid = 0;
                break;
            }else {
                isValid = 1;
            }
            aux=aux->next;
        }
        
        //Se esse ano ainda não existir -> cria um novo nó e insere-o ordenadamente
        if(isValid == 1) {
            _newNode = NewAuxYear(_ano);
            if((*_head)->ano > _newNode->ano) {
                //Se a data do newNode for menor que a data da head o newNode é adicionado antes da head
                _newNode->next = *_head;
                _newNode->prev = NULL;
                (*_head)->prev = _newNode;
                *_head = _newNode;
                InsertOrdenatedCountry(&(_newNode->head), &(_newNode->tail), _payload);
            } else if((*_head)->ano == _newNode->ano) {
                //Se a data do newNode fôr igual à da head ele é adicionado antes da head
                _newNode->next = *_head;
                (*_head)->prev = _newNode;
                *_head = _newNode;
                InsertOrdenatedCountry(&(_newNode->head), &(_newNode->tail), _payload);
            } else if((*_tail)->ano == _newNode->ano) {
                //Se a data do newNode fôr igual à da tail ele é adicionado depois da tail
                (*_tail)->next = _newNode;
                _newNode->prev = *_tail;
                *_tail = _newNode;
                InsertOrdenatedCountry(&(_newNode->head), &(_newNode->tail), _payload);
            }else if(*_head == *_tail && ((*_head)->ano < _newNode->ano )){
                //Se apenas existe 1 elemento na lista: adicionamos a seguir à tail
                (*_tail)->next = _newNode;
                _newNode->prev = *_tail;
                *_tail = _newNode; 
                InsertOrdenatedCountry(&(_newNode->head), &(_newNode->tail), _payload);
            }else{

                aux = *_head;

                while(aux != *_tail && ((aux)->ano < _newNode->ano )) {
                    //Itera pelos elementos da lista até encontrar um maior
                    aux = aux->next;
                }

                if(aux == *_tail && ((aux)->ano < _newNode->ano )) {
                    //Caso exista apenas um elemento adiciona a seguir à tail
                    (*_tail)->next = _newNode;
                    _newNode->prev = *_tail;
                    *_tail = _newNode;
                    InsertOrdenatedCountry(&(_newNode->head), &(_newNode->tail), _payload);
                } else { 
                    // Inserção de um elemento generico
                    aux->prev->next = _newNode;
                    _newNode->prev = aux->prev;
                    aux->prev = _newNode;
                    _newNode->next = aux;
                    InsertOrdenatedCountry(&(_newNode->head), &(_newNode->tail), _payload);
                }
                
            }

        }
    }

    if(*_head == NULL) { //No caso de ser o 1º elemento da lista
        _newNode = NewAuxYear(_ano);
       _newNode->next = *_head;
        _newNode->prev = *_head;
        *_head = _newNode;
        *_tail = _newNode;
        InsertOrdenatedCountry(&(_newNode->head), &(_newNode->tail), _payload);
    }
}

/*Stitching: Joins all the mini-lists
* Makes the first mini-list head the main head and the last mini-list tail the main tail
*/
void stitching(node_t_auxYear *_head, node_t_auxYear *_tail){
    node_t_auxYear * aux = NULL;
    aux = _head;

    while(aux != _tail){
        aux->tail->next = aux->next->head;
        aux->next->head->prev = aux->tail;
        aux = aux->next;
    }
}

/*miniTraverse: Prints all the mini-lists
*/
void miniTraverse(node_t_auxYear *_head) {
    node_t_auxYear *aux = _head;
    if(_head == NULL) {
        printf("List is empty!!!\n");
        return;
    }
    
    node_t_country *tmp = _head->head;

    while(aux != NULL){
        tmp = aux->head;
        while(tmp != NULL) {
            printf(" %f - %s - %d/%d\n", tmp->payload.temperatura, tmp->payload.pais, tmp->payload.dt.ano, tmp->payload.dt.mes);
            tmp = tmp->next;
        }
        printf("\n\n");
        aux = aux->next;
    }

}


//FUNCTIONS FOR COUNTRIES LISTS

/*Creates a new country node with the given payload
*/
node_t_country * NewCountry(dados_country _payload) {
    node_t_country * newNode = NULL;
    newNode = (node_t_country*)malloc(sizeof(node_t_country));
    if(newNode == NULL) {
        printf("Error alocating memory!");
        exit(EXIT_FAILURE);
    }
    newNode->payload = _payload;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}


/*Orderly inserts a new country node
*/
void InsertOrdenatedCountry(node_t_country **_head, node_t_country **_tail, dados_country _payload) {
    node_t_country *aux = NULL;
    node_t_country *_newNode = NewCountry(_payload);
    int i = 0;

    //If list is empty
    if(*_head == NULL) {
        _newNode->next = *_head;
        _newNode->prev = *_head;
        *_head = _newNode;
        *_tail = _newNode;
    } else if((*_head)->payload.dt.ano > _newNode->payload.dt.ano ||( (*_head)->payload.dt.ano == _newNode->payload.dt.ano && (*_head)->payload.dt.mes > _newNode->payload.dt.mes) || ( (*_head)->payload.dt.ano == _newNode->payload.dt.ano && (*_head)->payload.dt.mes == _newNode->payload.dt.mes && (*_head)->payload.dt.dia > _newNode->payload.dt.dia) ) {
        //Se a data do newNode for menor que a data da head o newNode é adicionado antes da head
        _newNode->next = *_head;
        _newNode->prev = NULL;
        (*_head)->prev = _newNode;
        *_head = _newNode;
    } else if((*_head)->payload.dt.ano == _newNode->payload.dt.ano && (*_head)->payload.dt.mes == _newNode->payload.dt.mes && (*_head)->payload.dt.dia == _newNode->payload.dt.dia ) {
        //Se a data do newNode fôr igual à da head ele é adicionado antes da head
        _newNode->next = *_head;
        (*_head)->prev = _newNode;
        *_head = _newNode;
    } else if((*_tail)->payload.dt.ano == _newNode->payload.dt.ano && (*_tail)->payload.dt.mes == _newNode->payload.dt.mes && (*_tail)->payload.dt.dia == _newNode->payload.dt.dia ) {
        //Se a data do newNode fôr igual à da tail ele é adicionado depois da tail
        (*_tail)->next = _newNode;
        _newNode->prev = *_tail;
        *_tail = _newNode;
    }else if(*_head == *_tail && ((*_head)->payload.dt.ano < _newNode->payload.dt.ano ||( (*_head)->payload.dt.ano == _newNode->payload.dt.ano && (*_head)->payload.dt.mes < _newNode->payload.dt.mes) || ( (*_head)->payload.dt.ano == _newNode->payload.dt.ano && (*_head)->payload.dt.mes == _newNode->payload.dt.mes && (*_head)->payload.dt.dia < _newNode->payload.dt.dia) )){
            //Se só existe 1 elemento na lista
            (*_tail)->next = _newNode;
            _newNode->prev = *_tail;
            *_tail = _newNode; 
        }
    else{
        
        aux = *_head;
        while(aux != *_tail && ((aux)->payload.dt.ano < _newNode->payload.dt.ano ||( (aux)->payload.dt.ano == _newNode->payload.dt.ano && (aux)->payload.dt.mes < _newNode->payload.dt.mes) || ( (aux)->payload.dt.ano == _newNode->payload.dt.ano && (aux)->payload.dt.mes == _newNode->payload.dt.mes && (aux)->payload.dt.dia < _newNode->payload.dt.dia) )) {
            //Itera pelos elementos da lista até encontrar um maior
            aux = aux->next;
            i++;
        }

        if(aux == *_tail && ((aux)->payload.dt.ano < _newNode->payload.dt.ano ||( (aux)->payload.dt.ano == _newNode->payload.dt.ano && (aux)->payload.dt.mes < _newNode->payload.dt.mes) || ( (aux)->payload.dt.ano == _newNode->payload.dt.ano && (aux)->payload.dt.mes == _newNode->payload.dt.mes && (aux)->payload.dt.dia < _newNode->payload.dt.dia) )) {
            //Se só existe 1 elemento na lista
            (*_tail)->next = _newNode;
            _newNode->prev = *_tail;
            *_tail = _newNode;
        } else { 
            //Elemento genérico
            aux->prev->next = _newNode;
            _newNode->prev = aux->prev;
            aux->prev = _newNode;
            _newNode->next = aux;
            
        }
    }
}

//prints and iterates over all elements of the country list
void traverseCountries(node_t_country *_head) {
    node_t_country *aux = _head;

    if(_head == NULL) {
        printf("List is empty!!!\n");
        return;
    }

    printf("\n");
    while(aux != NULL) {
        printf(" %f - %s - %d/%d\n", aux->payload.temperatura, aux->payload.pais, aux->payload.dt.ano, aux->payload.dt.mes);
        aux = aux->next;
    }
    printf("\n\n");

}

//Removes all nodes older than the given year and month
void RemoveNodesByInterval(node_t_country **_head, node_t_country **_tail, int _ano, int _mes) {
    node_t_country *aux = *_head;

    //Enquanto o ano e mes dado forem maiores que o aux e o aux não chegar ao fim da lista -> é feita a iteração
    while((_ano > aux->payload.dt.ano || (_ano == aux->payload.dt.ano && _mes > aux->payload.dt.mes)) && aux != *_tail) {
        aux = aux->next;
        free(aux->prev);
        aux->prev= NULL;
    }
    *_head = aux;
    //Não está a eliminar o ultimo elemento da lista: dou free(aux), mas o aux continua a existir
    if(aux == *_tail && (_ano > aux->payload.dt.ano || (_ano == aux->payload.dt.ano && _mes > aux->payload.dt.mes))) {
        //Apenas dou free(aux) pois a lista passa a ser vazia.
        free(aux);
    }
}

//Removes all nodes out of a month interval. Ex: if month interval is [4, 8]: node of year 1982, month 3 is eliminated
void RemoveNodesByMonth(node_t_country **_head, node_t_country **_tail, int _initMonth, int _finalMonth) {
    node_t_country *aux = *_head;
    node_t_country *tmp = NULL;

    while(aux != *_tail) {
        if(_initMonth>aux->payload.dt.mes || _finalMonth<aux->payload.dt.mes) {
            if(aux == *_head) { //Se for para eliminar o primeiro elemento da lista:
                *_head = (*_head)->next;
                aux = aux->next;
                free(aux->prev);
                aux->prev = NULL;
            }else { //Se for para eliminar um elemento interior da lista:
                tmp = aux;
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
                aux = aux->next;
                free(tmp);
            }
        }else {
            aux=aux->next;
        }
    }
        //Se for para eliminar a tail:
    if(aux == *_tail && (_initMonth>aux->payload.dt.mes || _finalMonth<aux->payload.dt.mes)) {
        *_tail = aux->prev;
        (*_tail)->next = NULL;
        free(aux);
    }
}


//CITY LIST FUNCTIONS

/*Creates a new city node
*/
node_t_city * NewCity(dados_city _payload) {
    node_t_city * newNode = NULL;
    newNode = (node_t_city*)malloc(sizeof(node_t_city));
    if(newNode == NULL) {
        printf("Error alocating memory!");
        exit(EXIT_FAILURE);
    }
    newNode->payload = _payload;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

/*Inserts the new city node by the tail
*/
void InsertCityList(node_t_city **_head, node_t_city **_tail, dados_city _payload) {
    node_t_city *_newNode = NewCity(_payload);

    if(*_head == NULL) {
        _newNode->next = *_head;
        _newNode->prev = *_head;
        *_head = _newNode;
    }else {
        if(*_tail == NULL) {
            *_tail = _newNode;
            (*_tail)->prev = *_head;
            (*_head)->next = *_tail;
        } else {
            _newNode->prev = *_tail;
            (*_tail)->next = _newNode;
            *_tail = _newNode;
        }

    }
}

/*Removes all city nodes out of a given span 
*/
void RemoveCityNodesByInterval(node_t_city **_head, node_t_city **_tail, int _ano, int _mes) {
    node_t_city *aux = *_head;
    node_t_city *tmp = NULL;
    char cityName[40] = {0};
    strcpy(cityName, (*_head)->payload.cidade);

    //Enquanto o ano e mes dado forem maiores que o aux e o aux não chegar ao fim da lista -> é feita a iteração
    while(aux != *_tail) {
        if(_ano > aux->payload.dt.ano || (_ano == aux->payload.dt.ano && _mes > aux->payload.dt.mes)) {
            if(strcmp(cityName, aux->payload.cidade) == 0) {
                aux = aux->next;
                free(aux->prev);
                aux->prev= NULL;
                *_head = aux;
            } else {
                tmp = aux;
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
                aux = aux->next;
                free(tmp);

            }
        }else {
            aux=aux->next;
        }
        
    }
    //Não está a eliminar o ultimo elemento da lista: dou free(aux), mas o aux continua a existir
    if(aux == *_tail && (_ano > aux->payload.dt.ano || (_ano == aux->payload.dt.ano && _mes > aux->payload.dt.mes))) {
        //Apenas dou free(aux) pois a lista passa a ser vazia.
        free(aux);
    }
}


/*Removes city nodes by a given range of months. Ex. user input: 2 6  ->  Removes nodes with months out of [2, 6]
*/
void RemoveCityNodesByMonth(node_t_city **_head, node_t_city **_tail, int _initMonth, int _finalMonth) {
    node_t_city *aux = *_head;
    node_t_city *tmp = NULL;

    while(aux != *_tail) {
        if(_initMonth>aux->payload.dt.mes || _finalMonth<aux->payload.dt.mes) {
            if(aux == *_head) { //Se for para eliminar o primeiro elemento da lista:
                *_head = (*_head)->next;
                aux = aux->next;
                free(aux->prev);
                aux->prev = NULL;
            }else { //Se for para eliminar um elemento interior da lista:
                tmp = aux;
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
                aux = aux->next;
                free(tmp);
            }
        }else {
            aux=aux->next;
        }
    }
        //Se for para eliminar a tail:
    if(aux == *_tail && (_initMonth>aux->payload.dt.mes || _finalMonth<aux->payload.dt.mes)) {
        *_tail = aux->prev;
        (*_tail)->next = NULL;
        free(aux);
    }
}

/*Prints the city list
*/
void traverseCities(node_t_city *_head) {
    node_t_city *aux = _head;

    if(_head == NULL) {
        printf("List is empty!!!\n");
        return;
    }

    printf("\n");
    while(aux != NULL) {
            printf(" %f - %s - %s - %d/%d\n", aux->payload.temperatura, aux->payload.pais, aux->payload.cidade, aux->payload.dt.ano, aux->payload.dt.mes);
        aux = aux->next;
    }
    printf("\n\n");

}