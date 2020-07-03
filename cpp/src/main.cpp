#include "game/game.hpp"

int main (int argc, char * argv[])
{
    Game game ("Hack N Mage", 0, 0, 600, 400, false);

    int graphic_FPS = 60;
    const int graphic_frame_delay = 1000/graphic_FPS;

    int input_FPS = graphic_FPS;
    const int input_frame_delay = 1000/input_FPS;

    const int frame_delay = 1000/std::max (graphic_FPS, input_FPS);

    long last_graphic_time = SDL_GetTicks ();
    long last_input_time = SDL_GetTicks ();
    long frame_start;
    int frame_time;

    while (game.Running ())
    {
        frame_start = SDL_GetTicks ();

        if (frame_start - last_input_time >= input_frame_delay)
            last_input_time = frame_start,
            game.HandleEvents ();

        game.Update ();

        if (frame_start - last_graphic_time >= graphic_frame_delay)
            last_graphic_time = frame_start,
            game.Render ();

        frame_time = SDL_GetTicks () - frame_start;
        SDL_Delay (std::max (0, frame_delay  - frame_time));
    }

    return 0;
}