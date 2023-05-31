#include "base.hpp"

class NaiveBoard : public Board<NaiveBoard>
{
public:
    NaiveBoard(int x_len, int y_len);
    bool read_cell(int x, int y);
    bool read_previous_cell(int x, int y);
    int count_previous_neighbors(int x, int y);
    void set_cell(int x, int y);
    void kill_cell(int x, int y);
};

class SequenceNaiveGame : public ConwayBaseGame<SequenceNaiveGame>, public NaiveBoard
{
public:
    SequenceNaiveGame(int x_len, int y_len);
    void iterate();
};

class ParallelNaiveGame : public ConwayBaseGame<ParallelNaiveGame>, public NaiveBoard
{
public:
    ParallelNaiveGame(int x_len, int y_len);
    void iterate();
};