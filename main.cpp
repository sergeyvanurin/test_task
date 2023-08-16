#include <iostream>
#include <chrono>
#include <vector>
#include <memory>
#include <future>

#include "Castle.hpp"
#include "ChessBoard.hpp"

using namespace std::chrono_literals;

using Duration = std::chrono::nanoseconds;

void StartCastle(const size_t& move_count, const size_t id, const Position position, std::shared_ptr<ChessBoard>& board, const Duration& base_sleep_duration, const size_t& board_size) {
    std::cout << "starting a game with id: " << id << std::endl;
    auto castle = Castle(move_count, id, position, board, base_sleep_duration, board_size);
    castle.StartGame();
}

int main() {
    size_t board_size;
    size_t move_count;
    size_t pieces_count;

    std::cout << "Input board size, move count, pieces count:" << std::endl;
    std::cin >> board_size >> move_count >> pieces_count;

    std::vector<std::future<void>> tasks;

    const auto game_start = std::chrono::high_resolution_clock::now();

    auto board = std::make_shared<ChessBoard>(board_size, 5s);
    for (size_t i = 0; i < pieces_count; i++) {
        tasks.push_back(std::async(std::launch::async, StartCastle, std::ref(move_count), i, Position{.x=i, .y=i}, std::ref(board), 200ms, std::ref(board_size)));
    }

    for (const auto& task: tasks) {
        task.wait();
    }

    std::cout << "Game finished in: " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - game_start).count() << " seconds" << std::endl;
}
