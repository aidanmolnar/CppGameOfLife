#include "naive.hpp"

NaiveBoard::NaiveBoard(int x_len, int y_len)
{
    this->x_dim = x_len;
    this->y_dim = y_len;
    board = std::vector<uint8_t>(x_len * y_len, false);
    previous_board = std::vector<uint8_t>(x_len * y_len, false);
}

bool NaiveBoard::read_cell(int x, int y)
{
    return board[y * x_dim + x];
};

bool NaiveBoard::read_previous_cell(int x, int y)
{
    return previous_board[y * x_dim + x];
};

int NaiveBoard::count_previous_neighbors(int x, int y)
{
    int total = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (x + i >= 0 && x + i < x_dim && y + j >= 0 && y + j < y_dim && !(i == 0 && j == 0))
            {
                if (read_previous_cell(x + i, y + j))
                {
                    total++;
                }
            }
        }
    }
    return total;
};

void NaiveBoard::set_cell(int x, int y)
{
    board[y * x_dim + x] = 1;
};

void NaiveBoard::kill_cell(int x, int y)
{
    board[y * x_dim + x] = 0;
};

SequenceNaiveGame::SequenceNaiveGame(int x_len, int y_len) : NaiveBoard(x_len, y_len), ConwayBaseGame(x_len, y_len){};

void SequenceNaiveGame::iterate()
{
    previous_board = board;

    for (int y = 0; y < y_len; y++)
    {
        for (int x = 0; x < x_len; x++)
        {
            iterate_cell(x, y);
        }
    }
};

ParallelNaiveGame::ParallelNaiveGame(int x_len, int y_len) : NaiveBoard(x_len, y_len), ConwayBaseGame(x_len, y_len){};

void ParallelNaiveGame::iterate()
{
    previous_board = board;

#pragma omp parallel for
    for (int y = 0; y < y_len; y++)
    {
        for (int x = 0; x < x_len; x++)
        {
            iterate_cell(x, y);
        }
    }
};
