#include <thread>
#include <iostream>

#include "Castle.hpp"

Castle::Castle(const size_t &move_count, const size_t id, const Position &position, std::shared_ptr<ChessBoard> board, const Duration &base_sleep_duration, const size_t &board_size) : move_count_(move_count), id_(id), current_position_(position), board_(board), base_sleep_duration_(base_sleep_duration)
{
    board_generator_ = std::uniform_int_distribution<size_t>(0, board_size - 1);
}

void Castle::StartGame()
{
    board_->InitialMove(current_position_);
    while (move_count_ > 0)
    {
        if (Move())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200 + cooldown_generator_(gen_)));
        }
        else
        {
            std::cout << "id: " << id_ << ": Failed! Choosing other box" << std::endl;
        }
    }

    std::cout << "id: " << id_ << ": Done!" << std::endl;
    board_->Finish(current_position_);
}

bool Castle::Move()
{
    std::cout << "id: " << id_ << ": current position is: " << current_position_.x << " " << current_position_.y << std::endl;
    const auto new_position = GeneratePosition();
    std::cout << "id: " << id_ << ": trying to move to: " << new_position.x << " " << new_position.y << std::endl;
    if (board_->Move(current_position_, new_position))
    {
        std::cout << "id: " << id_ << ": moved to: " << new_position.x << " " << new_position.y << std::endl;
        current_position_ = new_position;
        move_count_--;
        return true;
    }

    return false;
}

Position Castle::GeneratePosition()
{
    auto direction = direction_generator_(gen_);
    Position new_position{.x = direction ? board_generator_(gen_) : current_position_.x, .y = direction ? current_position_.y : board_generator_(gen_)};

    while (new_position == current_position_)
    {
        direction = direction_generator_(gen_);
        new_position = {.x = direction ? board_generator_(gen_) : current_position_.x, .y = direction ? current_position_.y : board_generator_(gen_)};
    }

    return new_position;
}
