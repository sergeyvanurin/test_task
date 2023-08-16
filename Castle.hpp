#pragma once

#include <random>
#include <memory>

#include "ChessBoard.hpp"

class Castle
{
public:
    Castle(const size_t &move_count, const size_t id, const Position &position, std::shared_ptr<ChessBoard> board, const Duration &base_sleep_duration, const size_t &board_size);

    void StartGame();

private:
    bool Move();

    Position GeneratePosition();

    Position current_position_;
    size_t move_count_;
    std::shared_ptr<ChessBoard> board_;
    const size_t id_;
    const Duration base_sleep_duration_;

    std::random_device rd;
    std::mt19937_64 gen_ = std::mt19937_64(rd());
    std::uniform_int_distribution<size_t> board_generator_;
    std::uniform_int_distribution<size_t> direction_generator_ = std::uniform_int_distribution<size_t>(0, 1);
    std::uniform_int_distribution<size_t> cooldown_generator_ = std::uniform_int_distribution<size_t>(0, 100);
};
