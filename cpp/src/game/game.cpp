#include "game.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <cstdlib>
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
        this->window_width = width;
        this->window_height = height;
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
        this->board.resize (13);
        for (auto & line : this->board)
            line.resize (15);
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
    static bool init = true;
    if (init)
    {
        int board_height = this->board.size ();
        int board_width = this->board[0].size ();
        for (int i = 0; i < board_height; ++i)
        {
            for (int j = 0; j < board_width; ++j)
            {
                if (i == 0 && j == 0)
                    this->board[i][j].insert ({201, NULL});
                else if (i == 0 && j == board_width - 1)
                    this->board[i][j].insert ({187, NULL});
                else if (i == board_height - 1 && j == 0)
                    this->board[i][j].insert ({200, NULL});
                else if (i == board_height - 1 &&
                        j == board_width - 1)
                    this->board[i][j].insert ({188, NULL});
                else if (i == 0 || i == board_height - 1)
                    this->board[i][j].insert ({205, NULL});
                else if (j == 0 || j == board_width - 1)
                    this->board[i][j].insert ({186, NULL});
                else switch (rand () % 16)
                {
                case 0:
                    this->board[i][j].insert ({96, NULL});
                    break;
                case 1:
                    this->board[i][j].insert ({46, NULL});
                    break;
                case 2:
                    this->board[i][j].insert ({44, NULL});
                    break;
                default:
                    this->board[i][j].insert ({0, NULL});
                    break;
                }
            }
        }
        init = false;
    }
}


void Game::Render ()
{
    SDL_RenderClear (this->renderer);

    // Actual rendering;
    int board_height = this->board.size ();
    int board_width = this->board[0].size ();
    int slot_height = std::min (this->window_height/(board_height*1.6),
            this->window_width/(board_width*1.0)*2);
    int slot_width = slot_height/2;
    int slot_x_delta = (this->window_width - board_width*slot_width)/2;
    int slot_y_delta = (this->window_height - board_height*slot_height)/2;
    for (int i = 0; i < board_height; ++i)
    {
        for (int j = 0; j < board_width; ++j)
        {
            int texture_rect_index = this->board[i][j].begin ()->first;
            SDL_Rect target_pos_rect;

            target_pos_rect.w = slot_width;
            target_pos_rect.h = slot_height;
            target_pos_rect.x = j*slot_width + slot_x_delta;
            target_pos_rect.y = i*slot_height;// + slot_y_delta;
            SDL_RenderCopy (this->renderer, this->graphic_texture_source,
                    & (this->graphic_textures[texture_rect_index]),
                    & target_pos_rect);
        }
    }

    SDL_RenderPresent (this->renderer);
}
