#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <algorithm>

class Player
{
private:
    std::pair <int, int> board_pos;

public:
    Player ();
    ~ Player ();

    void AbsoluteMove (int new_destination_y, int new_destination_x);
    void StepMove (int step_y, int step_x);

    std::pair <int, int> BoardPos () const;
};

#endif
