#pragma once

#include <chrono>
#include <vector>
#include <memory>
#include <shared_mutex>

#include "Position.hpp"

using namespace std::chrono_literals;

using Duration = std::chrono::nanoseconds;

class ChessBoard
{

    using Box = std::unique_ptr<std::shared_timed_mutex>;
    using BoardRow = std::vector<Box>;
    using Board = std::vector<BoardRow>;
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

public:
    ChessBoard(size_t size, Duration default_deadline_duration);

    ChessBoard(ChessBoard &board) = delete;

    bool Move(const Position &current_position, const Position &desired_position);

    void InitialMove(const Position &desired_position);

    void Finish(const Position &desired_position);

private:
    bool CheckPath(const Position &current_position, const Position &desired_position, const TimePoint &deadline);

    bool ReserveBox(const Position &desired_position, const TimePoint &deadline);

    void ReserveFirstBox(const Position &desired_position);

    void UnlockBox(const Position &desired_position);

    bool ReservePathBox(const Position &desired_position, const TimePoint &deadline);

    void UnlockPathBox(const Position &desired_position);

    const size_t size_;
    Board board_ = Board(size_);
    const Duration default_deadline_duration_;
};
