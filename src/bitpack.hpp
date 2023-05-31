#include "base.hpp"

class BitpackBoard : public Board<BitpackBoard>
{
public:
    BitpackBoard(int x_len, int y_len);
    bool read_cell(int x, int y);
    bool read_previous_cell(int x, int y);
    int count_previous_neighbors(int x, int y);
    void set_cell(int x, int y);
    void kill_cell(int x, int y);
};

class SequenceBitpackGame : public ConwayBaseGame<SequenceBitpackGame>, public BitpackBoard
{
public:
    SequenceBitpackGame(int x_len, int y_len);

    void iterate();
};

class ParallelBitpackGame : public ConwayBaseGame<ParallelBitpackGame>, public BitpackBoard
{
public:
    ParallelBitpackGame(int x_len, int y_len);

    void iterate();

    void iterate_row(int y);
};
