#ifndef GAME_HPP
#define GAME_HPP

#include <set>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "player.hpp"

class Game
{
private:
    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;

    bool is_running = false;

    std::vector <SDL_Rect> graphic_textures;
    SDL_Texture * graphic_texture_source;
    std::vector <SDL_Rect> font_textures;
    SDL_Texture * font_texture_source;

    std::vector <std::vector <std::set <std::pair <int, void *>>>> board;

public:
    Game (std::string title="", int xpos=0, int ypos=0, int width=0,
            int height=0, bool fullscreen=0);
    ~Game ();

    bool Running ();
    void Update ();
    void Render ();
    void HandleEvents ();

};

#endif
