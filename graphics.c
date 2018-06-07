#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "graphics.h"
#include "structs.h"
#include "lists.h"

#define M_PI 3.14159265

/**HoverInfo: Displays the city name on mouse hover
*/
void HoverInfo(char *_cityName, TTF_Font *_font, SDL_Renderer *_renderer, int _posX, int _posY) {
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect solidRect;
    SDL_Color white = {255, 255, 255};

    //defines the text position, based on the dot position
    solidRect.x = _posX;
    solidRect.y = _posY - 5;
    // create a surface from the string text with a predefined font
    text_surface = TTF_RenderText_Blended(_font,_cityName,white);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // create texture
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    //return solidRect.h;
}


/**ReadFromCityList: Iterates over City List and prints on the world map
 * a colored circle for each City
*/

void ReadFromCityList(SDL_Renderer *_renderer, TTF_Font *_font,  int *_anoAtual, node_t_city **_head, node_t_city **_tail, int colors[3][3], int _centerHeight, int _centerWidth, int _pt_x, int _pt_y) {
    node_t_city *aux = *_head;
    int posX = 0;
    int posY = 0;
    int r=0, g=0, b=0;

    while(aux != NULL) {
        if(aux->payload.dt.ano == *_anoAtual) {
            //Converts city coordenates to pixel coordenates
            CoordToPixels(aux->payload.latitude.angular, aux->payload.latitude.direcao, aux->payload.longitude.angular, aux->payload.longitude.direcao, &posX, &posY, _centerHeight, _centerWidth);
            //Defines the color for each temperature (Diferent type of function for color conversion below and over 0ºC)
            if(aux->payload.temperatura <= 0) {  //Below 0ºC ranges from blue to white
                r=0;
                g = b = 255 + 10*aux->payload.temperatura;
                filledCircleRGBA(_renderer, posX, posY, 3, r, g, b);
            }else{ //Over 0ºC ranges from white to red
                r=255;
                b = g = 255 - 8*aux->payload.temperatura;
                filledCircleRGBA(_renderer, posX, posY, 3, r, g, b);
            }
            
            //If the mouse position is equal to dot position + radius display city name
            if((_pt_x >= posX-4 && _pt_x <= posX+4) && (_pt_y <= posY+4 && _pt_y >= posY-4)) {
                HoverInfo(aux->payload.cidade, _font, _renderer, posX, posY-25);
            }
        }
        aux=aux->next;
    }
    *_anoAtual += 2;
}


/**CoordToPixels: Converts the coordinates values of lat and long to pixels width and height
*/

void CoordToPixels(float _latit, char _angleLatit, float _longit, char _angleLongit,int *_posX, int *_posY, int _centerHeight, int _centerWidth) {
    float posXVariation = 0;
    float posYVariation = 0;

    posYVariation = (_latit * _centerHeight) / 90; //Makes a rule of 3 method specific for latitude (it ranges from 0 to 90º)
    posXVariation = (_longit * _centerWidth) / 180; //Makes a rule of 3 method specific for longitude (it ranges from 0 to 180º)

    //Defines the absolute position based on the given direction
    if(_angleLatit == 'N') {
        *_posY = (int)(_centerHeight - posYVariation);
    }else {
        *_posY = (int)(_centerHeight + posYVariation);
    }

    if(_angleLongit == 'E') {
        *_posX = (int)(_centerWidth + posXVariation);
    }else {
        *_posX = (int)(_centerWidth - posXVariation);
    }
}


/**
 * filledCircleRGBA: renders a filled circle
 * \param _circleX x pos
 * \param _circleY y pos
 * \param _circleR radius
 * \param _r red
 * \param _g gree
 * \param _b blue
 */
void filledCircleRGBA(SDL_Renderer * _renderer, int _circleX, int _circleY, int _circleR, int _r, int _g, int _b)
{

    int off_x = 0;
    int off_y = 0;
    float degree = 0.0;
    float step = M_PI / (_circleR*8);

    SDL_SetRenderDrawColor(_renderer, _r, _g, _b, 255);

    while (_circleR > 0)
    {
        for (degree = 0.0; degree < M_PI/2; degree+=step)
        {
            off_x = (int)(_circleR * cos(degree));
            off_y = (int)(_circleR * sin(degree));
            SDL_RenderDrawPoint(_renderer, _circleX+off_x, _circleY+off_y);
            SDL_RenderDrawPoint(_renderer, _circleX-off_y, _circleY+off_x);
            SDL_RenderDrawPoint(_renderer, _circleX-off_x, _circleY-off_y);
            SDL_RenderDrawPoint(_renderer, _circleX+off_y, _circleY-off_x);
        }
        _circleR--;
    }
}



/**
 * RenderTable: Draws the table where the game will be played, namely:
 * -  some texture for the background
 * -  the right part with the IST logo and the student name and number
 * -  the grid for game board with squares and seperator lines
 * \param _board_pos_x number of positions in the board (x axis)
 * \param _board_pos_y number of positions in the board (y axis)
 * \param _board_size_px size of the board
 * \param _font font used to render the text
 * \param _img surfaces with the table background and IST logo (already loaded)
 * \param _renderer renderer to handle all rendering in a window
 */
void RenderTexture( SDL_Surface *_img[], TTF_Font *_font ,SDL_Renderer* _renderer)
{
    SDL_Texture *table_texture;
    SDL_Rect tableSrc, tableDest;
    SDL_Color black = { 0, 0, 0 }; // black
    //int square_size_px;
    int height;

    // set color of renderer to some color
    SDL_SetRenderDrawColor( _renderer, 255, 255, 255, 255 );

    // clear the window
    SDL_RenderClear( _renderer );

    tableDest.x = tableSrc.x = 0;
    tableDest.y = tableSrc.y = 0;
    tableSrc.w = _img[0]->w;
    tableSrc.h = _img[0]->h;
    tableDest.w = 1200; //width and height of world map image
    tableDest.h = 601;

    // draws the table texture
    table_texture = SDL_CreateTextureFromSurface(_renderer, _img[0]);
    SDL_RenderCopy(_renderer, table_texture, &tableSrc, &tableDest);

    height = RenderLogo(1225, 5, _img[1], _renderer);
    height += RenderText(1200 +10, height, "Guilherme Viegas", _font, &black, _renderer);
    height += RenderText(1200+50, height, "90090", _font, &black, _renderer);
    height += RenderText(1200 + 10, height, "Joao Maria Silva", _font, &black, _renderer);
    height += RenderText(1200+50, height, "90105", _font, &black, _renderer);
    
    // // draws the table texture
    tableDest.x = 700;
    tableDest.y = tableSrc.y = 0;
    tableSrc.w = _img[2]->w;
    tableSrc.h = _img[2]->h;
    // tableDest.y = tableSrc.y = height +5;
    table_texture = SDL_CreateTextureFromSurface(_renderer, _img[2]);
    SDL_RenderCopy(_renderer, table_texture, &tableSrc, &tableDest);
    // destroy everything
    SDL_DestroyTexture(table_texture);
    // return for later use
}

/**
 * RenderText function: Renders some text on a position inside the app window
 * \param x X coordinate of the text
 * \param y Y coordinate of the text
 * \param text string with the text to be written
 * \param _font TTF font used to render the text
 * \param _color color of the text
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderText(int x, int y, char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect solidRect;

    solidRect.x = x;
    solidRect.y = y;
    // create a surface from the string text with a predefined font
    text_surface = TTF_RenderText_Blended(_font,text,*_color);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // create texture
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    return solidRect.h;
}

/**
 * RenderLogo function: Renders the IST logo on the app window
 * \param x X coordinate of the Logo
 * \param y Y coordinate of the Logo
 * \param _logoIST surface with the IST logo image to render
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderLogo(int x, int y, SDL_Surface *_logoIST, SDL_Renderer* _renderer)
{
    SDL_Texture *text_IST;
    SDL_Rect boardPos;

    // space occupied by the logo
    boardPos.x = x;
    boardPos.y = y;
    boardPos.w = _logoIST->w;
    boardPos.h = _logoIST->h;

    // render it
    text_IST = SDL_CreateTextureFromSurface(_renderer, _logoIST);
    SDL_RenderCopy(_renderer, text_IST, NULL, &boardPos);

    // destroy associated texture !
    SDL_DestroyTexture(text_IST);
    return _logoIST->h;
}

/**
 * InitEverything: Initializes the SDL2 library and all graphical components: font, window, renderer
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _font font that will be used to render the text
 * \param _img surface to be created with the table background and IST logo
 * \param _window represents the window of the application
 * \param _renderer renderer to handle all rendering in a window
 * \param _font font that will be used to render the big text of Victory or Defeat
 */
void InitEverything(int width, int height, int window_pos_x, int window_pos_y, TTF_Font **_font, SDL_Surface *_img[], SDL_Window** _window, SDL_Renderer** _renderer)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height, window_pos_x, window_pos_y);
    *_renderer = CreateRenderer(width, height, *_window);

    // load the table texture
    _img[0] = IMG_Load("map.png");
    if (_img[0] == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    _img[1] = SDL_LoadBMP("ist_logo.bmp");
    if (_img[1] == NULL)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    _img[2] = IMG_Load("scale.png");
    if (_img[2] == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

 
    // this opens (loads) a font file and sets a size
    *_font = TTF_OpenFont("FreeSerif.ttf", 20);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitSDL: Initializes the SDL2 graphic library
 */
void InitSDL()
{
    // init SDL library
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitFont: Initializes the SDL2_ttf font library
 */
void InitFont()
{
    // Init font library
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * CreateWindow: Creates a window for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \return pointer to the window created
 */
SDL_Window* CreateWindow(int width, int height, int window_pos_x, int window_pos_y)
{
    SDL_Window *window;
    // init window
    window = SDL_CreateWindow( "WarmingUp", window_pos_x, window_pos_y, width, height, 0 );
    // check for error !
    if ( window == NULL )
    {
        printf("Failed to create window : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

/**
 * CreateRenderer: Creates a renderer for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _window represents the window for which the renderer is associated
 * \return pointer to the renderer created
 */
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
{
    SDL_Renderer *renderer;
    // init renderer
    renderer = SDL_CreateRenderer( _window, -1, 0 );

    if ( renderer == NULL )
    {
        printf("Failed to create renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, width, height );

    return renderer;
}
