#pragma once

#include <ge211.hxx>

class Model
{
public:
    using Position = ge211::Posn<int>;

    Model();
    void all_zeros();
    void play_move(char direct);
    bool is_empty(int i, int j);
    // plays a turn

    void collide(char direct);
    // for each direction
    // for every tile, check the tile to the direction
    // if the tiles next to current tile are NOT the same color, return
    // else (same color) --> put the positions [ij] &&  in the array
    // get to end of loop --> return false

    bool isgood(int boardval);
    // checks tile position is valid

    bool win() const;  //what does const do -- not supposed to change
    //if a white tile on the board --> true
    bool loser = false;
    bool boards_equal(int b[3][3]);
    void initial_tiles();

    bool is_board_full();
    //true if board has no empties(0)

    bool cannot_collide();
    //true if no two of the same value are next to each other

    void generate_tile();
    // generates a red or orange tile in a random empty spot

    void shift_tiles(char direct);
    //pushes all tiles to one side -- need HELP w this one

    int get_board(Position pos);
    void set_board(Position pos, int num);
    void set_board_equal(int board1[3][3]);
    bool check_board_equal(int board1[3][3]);

    //getter of board position's value for view
    int number_at(int i, int j) const {
        return board_[i][j];
    }


private:
    int board_[3][3];

};
