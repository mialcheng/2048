#include "model.hxx"
#include <catch.hxx>

struct Test_access
{
    Model& model;

    void set_board(Model::Position pos, int num){
        model.set_board(pos, num);
    }
    // Sets the position as belonging to the player
    void all_zeros(){
        model.all_zeros();
    }
    void generate_tile(){
        model.generate_tile();
    }
    void shift_tiles(char direct){ //HELP WHY IS DIRECT GREY
        model.shift_tiles(direct);
    }
    void play_move(char direct){
        model.play_move(direct);
    }

    void collide(char direct){
        model.collide(direct);
    }
    bool check_board_equal(int board1[3][3]){
        return model.check_board_equal(board1);
    }
    void set_board_equal(int board1[3][3])
    {
        model.set_board_equal(board1);
    }
    int num_tiles_on_board(){
        int count = 0;
        for (int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){
                if (model.get_board({i,j})!= 0){
                    count++;
                }
            }
        }
        return count;
    }

};

TEST_CASE("collide for 3 same in a row") //1
{
    Model m;
    Test_access t{m};
    t.all_zeros();

    //create board empty w top row filled w twos
    t.set_board({0,0}, 2);
    t.set_board({1,0}, 2);
    t.set_board({2,0}, 2);

    //play move but without random tile generation
    t.shift_tiles('l');
    t.collide('l');
    t.shift_tiles('l');

    CHECK(m.get_board({0,0}) == 4);
    CHECK(m.get_board({1,0}) == 2);
    CHECK(m.get_board({2,0}) == 0);

}

TEST_CASE("full board but moves still possible") //2
{
    Model m;
    Test_access t{m};
    t.set_board({0,0}, 2);
    t.set_board({0,1}, 2);
    t.set_board({0,2}, 4);
    t.set_board({1,0}, 8);
    t.set_board({1,1}, 16);
    t.set_board({1,2}, 32);
    t.set_board({2,0}, 64);
    t.set_board({2,1}, 2);
    t.set_board({2,2}, 4);

    CHECK(m.loser == false);

}
TEST_CASE("no new tile generated when move doesnt work") //3
{
    Model m;
    Test_access t{m};
    t.all_zeros();

    //set board empty w bottom row filled
    t.set_board({0,2}, 2);
    t.set_board({1,2}, 2);
    t.set_board({2,2}, 4);

    //save board in board1
    int board1[3][3];
    t.set_board_equal(board1);

    //play move down
    t.play_move('d');
    CHECK(m.get_board({0,2}) == 2);
    CHECK(m.get_board({1,2}) == 2);
    CHECK(m.get_board({2,2}) == 4);
    CHECK(t.check_board_equal(board1));
    CHECK(t.num_tiles_on_board()==3);


}
TEST_CASE("shift tiles two spaces") //4
{
    Model m;
    Test_access t{m};
    t.all_zeros();
    t.set_board({0,2}, 2);
    t.set_board({1,2}, 2);
    t.set_board({2,2}, 2);

    t.play_move('u');
    CHECK(m.get_board({0,0}) == 2);
    CHECK(m.get_board({1,0}) == 2);
    CHECK(m.get_board({2,0}) == 2);

}
TEST_CASE("generate tiles") //5
{
    Model m;
    Test_access t{m};
    t.all_zeros();
    t.set_board({0,2}, 2);
    t.set_board({1,2}, 4);

    t.play_move('u');
    CHECK(t.num_tiles_on_board() == 3);
    t.generate_tile();
    t.generate_tile();
    CHECK(t.num_tiles_on_board() == 5);

}

