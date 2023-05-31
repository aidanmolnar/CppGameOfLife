#include "vector"
#include <iostream>
#include <random>
#include <cstdint>
#include <algorithm>

#ifndef CONWAY_BASE_GAME
#define CONWAY_BASE_GAME

#include "animator.hpp"

std::vector<uint8_t> generate_random_boolean_vector(int length, unsigned int seed = 0);

template <typename T>
// T must define
//    read_cell
//    iterate
class ConwayBaseGame : public Animator
{
public:
    int x_len;
    int y_len;

    ConwayBaseGame(int x_len, int y_len)
    {
        this->x_len = y_len;
        this->y_len = y_len;
    }

    static T random(int x_len, int y_len, unsigned int seed = 0)
    {
        auto new_board = generate_random_boolean_vector(x_len * y_len, seed);

        auto game = T(x_len, y_len);
        for (int x = 0; x < x_len; x++)
        {
            for (int y = 0; y < y_len; y++)
            {
                if (new_board[x_len * y + x])
                {
                    game.set_cell(x, y);
                }
            }
        }

        return game;
    };

    void iterate_times(int n)
    {
        for (int i = 0; i < n; i++)
        {
            static_cast<T *>(this)->iterate();
        }
    }

    void draw() override
    {
        static_cast<T *>(this)->iterate();

        for (int y = 0; y < y_len; y++)
        {
            for (int x = 0; x < x_len; x++)
            {
                if (static_cast<T *>(this)->read_cell(x, y))
                {
                    std::cout << "⬛ ";
                }
                else
                {
                    std::cout << "⬜ ";
                }
            }
            std::cout << "\n";
        }
        std::cout << std::flush;
    }
};

template <typename T>
// T must define:
//   count_previous_neighbors
//   read_previous_cell
//   kill_cell
//   preserve_cell
//   set_cell
class Board
{
public:
    int x_dim;
    int y_dim;

    std::vector<uint8_t> board;
    std::vector<uint8_t> previous_board;

    void iterate_cell(int x, int y)
    {
        int neighbors = static_cast<T *>(this)->count_previous_neighbors(x, y);

        if (static_cast<T *>(this)->read_previous_cell(x, y))
        {
            if (!(neighbors == 3 || neighbors == 2))
            {
                static_cast<T *>(this)->kill_cell(x, y);
            }
        }
        else
        {
            if (neighbors == 3)
            {
                static_cast<T *>(this)->set_cell(x, y);
            }
        }
    }
};

#endif