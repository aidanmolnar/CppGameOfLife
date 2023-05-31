#include "bitpack.hpp"
#include "naive.hpp"

#include <iostream>
#include <chrono>

template <class T>
void time(int n = 200, int x_len = 1000, int y_len = 1000, int seed = 500)
{
    using namespace std::chrono;

    auto game = T::random(x_len, y_len, seed);
    auto start = high_resolution_clock::now();
    game.iterate_times(n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start).count();
    std::cout << "Time: " << duration << " (ms)\n"
              << std::flush;
}

int main()
{
    // time<SequenceNaiveGame>(200, 1000, 1000, 500);
    // time<ParallelNaiveGame>(200, 1000, 1000, 500);
    // time<SequenceBitpackGame>(200, 1000, 1000, 500);
    // time<ParallelBitpackGame>(200, 1000, 1000, 500);

    auto game = ParallelBitpackGame::random(50, 50, 10160);
    game.play(10);
}
