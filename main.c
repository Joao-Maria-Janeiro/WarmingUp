/*********************************************************************
 *      Final Project for the Programming Subject                    *
 * Integrated Master in Electrical and Computer Engineering - IST    *
 * Authors:    João Maria Janeiro - ist190105                        *
 *             Guilherme Viegas  -  ist190090                        *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "menus.h"
#include "lists.h"
#include "statistics.h"
#include "graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#define WINDOW_POSX 200       // initial position of the window: x
#define WINDOW_POSY 200       // initial position of the window: y
#define WORLD_WIDTH 1400      //World map sizes
#define WORLD_HEIGHT 601
#define MAP_CENTER_WIDTH 600
#define MAP_CENTER_HEIGHT 300.5
#define M_PI 3.14158265

int GetUserMainParams(int, char*[], char[], char[], int *);

int main(int argc, char* argv[]){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *serif = NULL;
    SDL_Surface *imgs[3];
    SDL_Event event;
    int width = WORLD_WIDTH; //map image width
    int height = WORLD_HEIGHT; //map image height
    int delay = 100;
    int quit = 0;
    int colors[3][3] = {{0, 255, 255}, {0, 255, 0}, {255, 0, 0}};   //Azul, Amarelo, Vermelho
    int anoAtual = 1743;
    int primeiroAno = 2500;
    char strAnoAtual[10] = {0};
    int pt_x = 0, pt_y = 0;
    SDL_Color white = {255, 255, 255};

    int isGraphic = -1; //If is graphic->1, if is textual->0
    char fileNameCountry[40] = {0};
    char fileNameCity[40] = {0};
    node_t_country *headCountry = NULL;
    node_t_country *tailCountry = NULL;
    node_t_city *headCity = NULL;
    node_t_city *tailCity = NULL;
    node_t_city *aux = NULL;
    node_t_country *auxCountry = NULL;
    int doExit = 0;

    //If user params weren't well inserted
    if(!GetUserMainParams(argc, argv, fileNameCountry, fileNameCity, &isGraphic)) {
        exit(EXIT_FAILURE);
    }

    printf("A Carregar os Dados - Espere 1 Minuto\n");
    loadCountryFromFile(fileNameCountry, &headCountry, &tailCountry);
    printf("Loaded Country File - Loading City File\n");
    loadCityFromFile(fileNameCity, &headCity, &tailCity);
    aux = headCity;

    if(isGraphic == 1) {
        //Modo Gráfico:
            while(aux != NULL) { //Para saber qual o ano a começar a mostrar na gráfica (permite um código independente do ficheiro, senão seria preciso inserir diretamente 1743)
                if(aux->payload.dt.ano < primeiroAno)
                    primeiroAno = aux->payload.dt.ano;
                aux=aux->next;
            }
            anoAtual = primeiroAno;
        InitEverything(width, height, WINDOW_POSX, WINDOW_POSY, &serif, imgs, &window, &renderer);
        while( quit == 0) {
            while( SDL_PollEvent( &event) ) {
                if(event.type == SDL_QUIT) {
                    quit = 1;
                    //Frees both city and country lists in case of exit
                    auxCountry = headCountry;
                    while(auxCountry != tailCountry) {
                        auxCountry = auxCountry->next;
                        free(auxCountry->prev);
                    }
                    free(tailCountry);

                    aux = headCity;
                    while(aux != tailCity) {
                        aux = aux->next;
                        free(aux->prev);
                    }
                    free(tailCity);

                }
                if(event.type == SDL_MOUSEMOTION) {
                    //Saves the mouse positions
                    pt_x = event.button.x;
                    pt_y = event.button.y;
                }
            }
            RenderTexture(imgs, serif, renderer);
            if(anoAtual > tailCity->payload.dt.ano) {
                anoAtual = primeiroAno;
            }
            sprintf(strAnoAtual, "%d", anoAtual);  //Converts an int to a string
            RenderText(10, 10, strAnoAtual, serif, &white, renderer);
            ReadFromCityList(renderer, serif, &anoAtual, &headCity, &tailCity, colors, MAP_CENTER_HEIGHT, MAP_CENTER_WIDTH, pt_x, pt_y);
            // render in the screen all changes above
            SDL_RenderPresent(renderer);
            // add a delay
            SDL_Delay( delay );
        }
            TTF_CloseFont(serif);
            SDL_FreeSurface(imgs[0]);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
    }else if(!isGraphic) {
        //Modo Textual:
        while(doExit != 1) {
            switch(MainMenu()) {
                case 1:
                    FiltragemDeDados(&headCountry, &tailCountry, &headCity, &tailCity, fileNameCountry, fileNameCity);
                    break;
                case 2:
                    HistoricoTemperaturas(&headCountry, &tailCountry, &headCity, &tailCity);
                    getchar();
                    break;
                case 3:
                    AnaliseTemperaturaPorAno(&headCountry, &headCity);
                    getchar();
                    break;
                case 4:
                    AnaliseTemperaturaGlobal(&headCountry, &tailCountry, &headCity, &tailCity);
                    getchar();
                    break;
                case 5:
                    doExit = 1;
                    //Frees both country and city lists
                    auxCountry = headCountry;
                    while(auxCountry != tailCountry) {
                        auxCountry = auxCountry->next;
                        free(auxCountry->prev);
                    }
                    free(tailCountry);

                    aux = headCity;
                    while(aux != tailCity) {
                        aux = aux->next;
                        free(aux->prev);
                    }
                    free(tailCity);
                    break;
                default:
                    printf("Erro na introdução de dados!\n");
                    exit(EXIT_FAILURE);
            }
        }

    } else {
        printf("Need to choose Textual or Graphical Mode!\n");
        exit(EXIT_FAILURE);
    }

    

    
    return EXIT_SUCCESS;
}



/* Gets and Verifies User Params from terminal
*/
int GetUserMainParams(int _argc, char* _argv[], char _fileNameCountry[], char _fileNameCity[], int *_isGraphic) {

    if(_argc != 6)
        return 0;

    for(int i=1; i<_argc; i++) {
        if(!strcmp(_argv[i], "-g")) {
            *_isGraphic = 1;
        } else if(!strcmp(_argv[i], "-t")) {
            *_isGraphic = 0;
        } else if(i != _argc-1 && !strcmp(_argv[i], "-f1")) {
            strcpy(_fileNameCountry, _argv[i+1]);
        } else if(i != _argc-1 && !strcmp(_argv[i], "-f2")) {
            strcpy(_fileNameCity, _argv[i+1]);
        }
    }
    return 1;
}
