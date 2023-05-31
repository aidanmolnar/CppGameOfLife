#include "bitpack.hpp"

BitpackBoard::BitpackBoard(int x_len, int y_len)
{
    x_dim = x_len + 2;
    y_dim = y_len + 2;
    board = std::vector<uint8_t>(x_dim * y_dim, false);
    previous_board = std::vector<uint8_t>(x_dim * y_dim, false);
};

bool BitpackBoard::read_cell(int x, int y)
{
    // Account for border
    x++;
    y++;

    return board[y * x_dim + x] & 0b10000000;
};

bool BitpackBoard::read_previous_cell(int x, int y)
{
    // Account for border
    x++;
    y++;

    return previous_board[y * x_dim + x] & 0b10000000;
};

int BitpackBoard::count_previous_neighbors(int x, int y)
{
    // Account for border
    x++;
    y++;

    return previous_board[y * x_dim + x] & 0b01111111;
};

void BitpackBoard::set_cell(int x, int y)
{
    // Account for border
    x++;
    y++;

    int cell_index = y * x_dim + x;
    int top_index = cell_index - x_dim;
    int bot_index = cell_index + x_dim;

    board[cell_index] |= 0b10000000; // Set last bit to 1

    // Increment count of all neighbor cells
    board[top_index + 1]++;
    board[top_index]++;
    board[top_index - 1]++;
    board[cell_index + 1]++;
    board[cell_index - 1]++;
    board[bot_index + 1]++;
    board[bot_index]++;
    board[bot_index - 1]++;
};

void BitpackBoard::kill_cell(int x, int y)
{
    // Account for border
    x++;
    y++;

    int cell_index = y * x_dim + x;
    int top_index = cell_index - x_dim;
    int bot_index = cell_index + x_dim;

    board[cell_index] &= 0b01111111; // Set last bit to 0

    // Decrement count of all neighbor cells
    board[top_index + 1]--;
    board[top_index]--;
    board[top_index - 1]--;
    board[cell_index + 1]--;
    board[cell_index - 1]--;
    board[bot_index + 1]--;
    board[bot_index]--;
    board[bot_index - 1]--;
};

SequenceBitpackGame::SequenceBitpackGame(int x_len, int y_len) : BitpackBoard(x_len, y_len), ConwayBaseGame(x_len, y_len){};

void SequenceBitpackGame::iterate()
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

ParallelBitpackGame::ParallelBitpackGame(int x_len, int y_len) : BitpackBoard(x_len, y_len), ConwayBaseGame(x_len, y_len){};
// Because the bitpacking method also edits neighboring cells and we can't have threads editing cells with the same neighbor at the same time,
// edit cells in stripes at least 2 wide
void ParallelBitpackGame::iterate()
{
    previous_board = board;

    const int stripe_thick = 2;

#pragma omp parallel for
    for (int y0 = 0; y0 < y_len; y0 += 2 * stripe_thick)
    {
        for (int y_off = 0; y_off < stripe_thick; y_off++)
        {
            int y = y0 + y_off;
            if (y < y_len)
            {
                iterate_row(y);
            }
        }
    }

#pragma omp parallel for
    for (int y0 = 0; y0 < y_len; y0 += 2 * stripe_thick)
    {
        for (int y_off = stripe_thick; y_off < 2 * stripe_thick; y_off++)
        {
            int y = y0 + y_off;
            if (y < y_len)
            {
                iterate_row(y);
            }
        }
    }
}

void ParallelBitpackGame::iterate_row(int y)
{
    for (int x = 0; x < x_len; x++)
    {
        iterate_cell(x, y);
    }
};
