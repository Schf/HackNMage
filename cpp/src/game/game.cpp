#include "game.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

#include <SDL2/SDL_image.h>

static int number_of_running_games = 0;
static std::mutex SDL_InitAndQuit_mutex;

void TextureLoader (SDL_Renderer * renderer, std::vector <SDL_Rect> & rects,
        SDL_Texture * & source, std::string fname)
{
    SDL_Surface * temp_surface = IMG_Load (fname.c_str ());
    source = SDL_CreateTextureFromSurface (renderer, temp_surface);
    SDL_FreeSurface (temp_surface);

    // Size of PNG in pixels;
    std::ifstream graphic_source_ifstream (fname.c_str ());
    unsigned int width, height;
    graphic_source_ifstream.seekg (16);
    graphic_source_ifstream.read ((char *) & width, 4);
    graphic_source_ifstream.read ((char *) & height, 4);
    graphic_source_ifstream.close ();
    width = ntohl(width);
    height = ntohl(height);

    // Getting graphic image source pieces of each element
    rects.clear ();
    rects.resize (256);
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 16; ++j)
            rects[i*16 + j].w = width/16,
            rects[i*16 + j].h = height/16,
            rects[i*16 + j].x = width*j/16,
            rects[i*16 + j].y = height*i/16;
}

Game::Game (std::string title, int xpos, int ypos, int width, int height,
        bool fullscreen)
{
    {   // Initializing SDL if it is not already initialized
        // Thread safe btw
        SDL_InitAndQuit_mutex.lock ();
        int SDL_Init_res = 0;

        if (number_of_running_games <= 0)
            number_of_running_games = 0,
            SDL_Init_res = SDL_Init (SDL_INIT_EVERYTHING);

        if (SDL_Init_res != 0)
        {
            this->is_running = false;
            std::cout << "Couldn't initialize SDL2" << std::endl;
            return;
        }
        ++number_of_running_games;
        SDL_InitAndQuit_mutex.unlock ();
    }


    {   // Opening game window
        if (fullscreen)
            this->window = SDL_CreateWindow (title.c_str (), xpos, ypos, 1920,
                1080, SDL_WINDOW_FULLSCREEN);
        else
            this->window = SDL_CreateWindow (title.c_str (), xpos, ypos, width,
                height, SDL_WINDOW_SHOWN);
        if (this->window == NULL)
        {
            this->is_running = false;
            std::cout << "SDL2 couldn't create window" << std::endl;
            return;
        }
    }


    {   // Creating game renderer
        this->renderer = SDL_CreateRenderer (window, -1, 0);
        if (this->renderer == NULL)
        {
            this->is_running = false;
            std::cout << "SDL2 couldn't create renderer" << std::endl;
            return;
        }
    }


    {   // Initializing board
        // Shouldn't even have it's own block
        this->board.resize (15);
        for (auto & line : this->board)
            line.resize (11);
    }


    {   // Loading textures
        // Duh
        TextureLoader (this->renderer, this->graphic_textures,
                this->graphic_texture_source, "assets/graphic.png");

        TextureLoader (this->renderer, this->font_textures,
                this->font_texture_source, "assets/graphic.png");
    }


    this->is_running = true;
}

Game::~Game ()
{
    SDL_DestroyRenderer (this->renderer);
    SDL_DestroyWindow (this->window);

    SDL_InitAndQuit_mutex.lock ();
    --number_of_running_games;
    if (number_of_running_games <= 0)
        number_of_running_games = 0,
        SDL_Quit ();
    SDL_InitAndQuit_mutex.unlock ();
}

bool Game::Running ()
{
    return this->is_running;
}

void Game::HandleEvents ()
{
    SDL_Event event;
    SDL_PollEvent (& event);
    switch (event.type)
    {
        case SDL_QUIT:
            this->is_running = false;
            break;
        
        default:
            break;
    }
}

void Game::Update ()
{

}


void Game::Render ()
{
    SDL_RenderClear (this->renderer);

    // Actual rendering;
    static int cnt = 0;
    if (++cnt < 60*256)
        SDL_RenderCopy (this->renderer, this->graphic_texture_source,
                & (this->graphic_textures[cnt/60]), NULL);

    SDL_RenderPresent (this->renderer);
}
