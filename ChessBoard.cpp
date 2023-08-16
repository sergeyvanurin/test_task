#include "ChessBoard.hpp"

ChessBoard::ChessBoard(size_t size, Duration default_deadline_duration) : size_(size), default_deadline_duration_(default_deadline_duration)
{
    for (auto &row : board_)
    {
        for (size_t i = 0; i < size_; i++)
        {
            row.push_back(std::make_unique<std::shared_timed_mutex>());
        }
    }
}

bool ChessBoard::Move(const Position &current_position, const Position &desired_position)
{
    const auto deadline = std::chrono::high_resolution_clock::now() + default_deadline_duration_;
    if (ReserveBox(desired_position, deadline))
    {
        auto is_success = CheckPath(current_position.NextMove(desired_position), desired_position, deadline);
        UnlockBox(is_success ? current_position : desired_position);

        return is_success;
    }

    return false;
}

void ChessBoard::InitialMove(const Position &desired_position)
{
    ReserveFirstBox(desired_position);
}

void ChessBoard::Finish(const Position &desired_position)
{
    UnlockBox(desired_position);
}

bool ChessBoard::CheckPath(const Position &current_position, const Position &desired_position, const TimePoint &deadline)
{
    if (current_position == desired_position)
        return true;
    bool is_success = false;

    if (ReservePathBox(current_position, deadline))
    {
        is_success = CheckPath(current_position.NextMove(desired_position), desired_position, deadline);
        UnlockPathBox(current_position);
    }

    return is_success;
}

bool ChessBoard::ReserveBox(const Position &desired_position, const TimePoint &deadline)
{
    return board_[desired_position.y][desired_position.x]->try_lock_until(deadline);
}

void ChessBoard::ReserveFirstBox(const Position &desired_position)
{
    return board_[desired_position.y][desired_position.x]->lock();
}

void ChessBoard::UnlockBox(const Position &desired_position)
{
    board_[desired_position.y][desired_position.x]->unlock();
}

bool ChessBoard::ReservePathBox(const Position &desired_position, const TimePoint &deadline)
{
    return board_[desired_position.y][desired_position.x]->try_lock_shared_until(deadline);
}

void ChessBoard::UnlockPathBox(const Position &desired_position)
{
    board_[desired_position.y][desired_position.x]->unlock_shared();
}
