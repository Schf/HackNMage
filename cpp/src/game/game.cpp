#include "game.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <mutex>

#include <SDL2/SDL_image.h>

// 322 is the number of SDLK_DOWN events
std::vector <bool> KEYS (322, false);

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
    {   // Initializing SDL
        if (SDL_Init (SDL_INIT_EVERYTHING) != 0)
        {
            this->is_running = false;
            std::cout << "Couldn't initialize SDL2" << std::endl;
            return;
        }
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

    this->player1.AbsoluteMove (this->board.size () - 2, 1);
    this->player2.AbsoluteMove (1, this->board[0].size () - 2);
    this->board[this->player1.BoardPos ().first][this->player1.BoardPos ().second].
            insert ({1, &this->player1});
    this->board[this->player2.BoardPos ().first][this->player2.BoardPos ().second].
            insert ({2, &this->player2});

    this->is_running = true;
}

Game::~Game ()
{
    SDL_DestroyRenderer (this->renderer);
    SDL_DestroyWindow (this->window);
    SDL_Quit ();
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
        case SDL_KEYDOWN:
            KEYS[event.key.keysym.sym & (~ (1<<30))] = true;
            break;
        case SDL_KEYUP:
            KEYS[event.key.keysym.sym & (~ (1<<30))] = false;
            break;
        default:
            break;
    }
}

bool ValidPos (std::pair <int, int> pos,
        std::vector <std::vector <std::set <std::pair <int, void *>>>> & board)
{
    return 1 <= pos.first && pos.first <= board.size () - 2 &&
            1 <= pos.second && pos.second <= board[0].size () - 2;
}

void MovePlayer (int y, int x, int pcode, Player & player,
        std::vector <std::vector <std::set <std::pair <int, void *>>>> & board)
{
    board[player.BoardPos ().first][player.BoardPos ().second].
            erase ({pcode, &player});
    player.StepMove (y, x);
    if (!ValidPos (player.BoardPos (), board))
        player.StepMove (-y, -x);
    board[player.BoardPos ().first][player.BoardPos ().second].
            insert ({pcode, &player});
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
                    this->board[i][j].insert ({255, NULL});
                    break;
                }
            }
        }
        init = false;
    }
    if (KEYS[SDLK_LEFT & (~ (1<<30))])
        KEYS[SDLK_LEFT & (~ (1<<30))] = false,
        MovePlayer (0, -1, 2, this->player2, this->board);

    if (KEYS[SDLK_RIGHT & (~ (1<<30))])
        KEYS[SDLK_RIGHT & (~ (1<<30))] = false,
        MovePlayer (0, 1, 2, this->player2, this->board);

    if (KEYS[SDLK_DOWN & (~ (1<<30))])
        KEYS[SDLK_DOWN & (~ (1<<30))] = false,
        MovePlayer (1, 0, 2, this->player2, this->board);

    if (KEYS[SDLK_UP & (~ (1<<30))])
        KEYS[SDLK_UP & (~ (1<<30))] = false,
        MovePlayer (-1, 0, 2, this->player2, this->board);

    if (KEYS[SDLK_a & (~ (1<<30))])
        KEYS[SDLK_a & (~ (1<<30))] = false,
        MovePlayer (0, -1, 1, this->player1, this->board);

    if (KEYS[SDLK_d & (~ (1<<30))])
        KEYS[SDLK_d & (~ (1<<30))] = false,
        MovePlayer (0, 1, 1, this->player1, this->board);

    if (KEYS[SDLK_s & (~ (1<<30))])
        KEYS[SDLK_s & (~ (1<<30))] = false,
        MovePlayer (1, 0, 1, this->player1, this->board);

    if (KEYS[SDLK_w & (~ (1<<30))])
        KEYS[SDLK_w & (~ (1<<30))] = false,
        MovePlayer (-1, 0, 1, this->player1, this->board);
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
