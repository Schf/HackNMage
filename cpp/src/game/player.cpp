#include "player.hpp"

Player::Player ()
{
    this->board_pos = {0, 0};
}

Player::~Player ()
{
    
}

void Player::AbsoluteMove (int new_destination_y, int new_destination_x)
{
    this->board_pos = {new_destination_y, new_destination_x};
}

void Player::StepMove (int step_y, int step_x)
{
    this->board_pos.first += step_y;
    this->board_pos.second += step_x;
}

std::pair <int, int> Player::BoardPos () const
{
    return this->board_pos;
}
