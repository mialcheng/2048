#include "model.hxx"
#include "view.hxx"
#include <iostream>
using namespace ge211;

Model::Model()

{
    all_zeros();
    initial_tiles();

}
//write getter function to return value of board
int Model::get_board(Position pos){
    return board_[pos.x][pos.y];
}
void Model::set_board(Position pos, int num){
    board_[pos.x][pos.y] = num;
}
void Model::set_board_equal(int board1[3][3])
{
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            board1[i][j] = board_[i][j];
        }
    }
}
bool Model::check_board_equal(int board1[3][3])
{
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            if (board1[i][j] != board_[i][j]){
                return false;
            }
        }
    }
    return true;
}



//generate 2 tiles (either red/orange) at 2 random spots in the board
void Model::initial_tiles(){
    ge211::Random_source<int> pos(0,2);
    int pos_x = pos.next();
    int pos_y = pos.next();
    ge211::Random_source<int> tile_rand(0,1);
    int two_or_four = tile_rand.next();

    if(two_or_four == 1){
        // generate red tile in position
        board_[pos_x][pos_y] = 2;
        //return 2;
    } else{
        //generate orange tile in emptyspots[empty pos]
        board_[pos_x][pos_y] = 4;
        //return 4;
    }
    int pos_x2 = pos.next();
    int pos_y2 = pos.next();

    //make sure second tile is not at the same position
    while((pos_x ==pos_x2) && (pos_y == pos_y2)){
        pos_x2 = pos.next();
        pos_y2 = pos.next();
    }
    two_or_four = tile_rand.next();
    if(two_or_four == 1){
        // generate red tile in position
        board_[pos_x2][pos_y2] = 2;

    } else{
        //generate orange tile in position
        board_[pos_x2][pos_y2] = 4;

    }
}

//creates a board of all zeros (used in constructor)
void Model::all_zeros(){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board_[i][j] = 0;
        }
    }
}

//checks if there are any possible moves
void Model::play_move(char direct) {

    //if loser is false (game hasn't ended), then move tiles accordingly
    if (!loser) {
        //save the old board (temp_) before any moves happen
        int temp_[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp_[i][j] = board_[i][j];
            }
        }
        //play moves
        shift_tiles(direct);

        collide(direct);

        shift_tiles(direct);

        //check if any positions are different before generating a new tile
        if(!boards_equal(temp_)){
            generate_tile();
        }

    //losing condition: if board is full and no tiles can collide in any way
    }
    if (is_board_full() && cannot_collide()) {
        loser = true;
    }
}

//helper for play_move
bool Model::boards_equal(int b[3][3]){

    //check if input board is same as current board_
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
           if( b[i][j] != board_[i][j])
           {
               return false;
           }
        }
    }
    return true;
}


//returns false if any board vals are zero
bool Model::is_board_full(){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board_[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}


//needs to check for all 4 directions (up-down, left-right)
//helper for play_move
bool Model::cannot_collide(){

    //check for collisions up and down
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            //tiles can collide even if they are separated by a space
            if(board_[i][j] == board_[i][j+1]){
                return false;
            }
        }
    }
    //check for collisions left and right
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if(board_[i][j] == board_[i+1][j]){
                return false;
            }
        }
    }
    return true;
}

//probably not useful
bool Model::isgood(int boardval){
    if (boardval >= 0) {
        return true;
    }else{
        return false;
    }
}

//checks if there is a white tile (corresponding to value of 256)
bool Model::win() const{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board_[i][j] == 256) {
                return true;
            }
        }
    }
    return false;
}

//helper for generate_tile
bool Model::is_empty(int i, int j)
{
    if(number_at(i,j) == 0){
        return true;
    }else {
        return false;
    }

}

//generate a new tile after each keyboard key event
void Model::generate_tile()
{
    //create empty array
    std::vector<ge211::Posn<int>> emptyspots;
    int count = 0;

    //don't generate tile if no existing tiles move despite on_key_down
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            //if board position is 0
            if (is_empty(i,j)) {
                emptyspots.push_back({i,j});
                count ++;
            }
        }
    }

    //generate a random index from 0 to the # of empty board pos
    ge211::Random_source<int> pos_rand(0,count-1);
    int empty_pos = pos_rand.next();

    Position pos = emptyspots[empty_pos];

    //generate whether we will add a red or orange tile
    ge211::Random_source<int> tile_rand(0,1);
    int two_or_four = tile_rand.next();

    if(two_or_four == 1){
        // generate red tile in position
        board_[pos.x][pos.y] = 2;
        return;
    } else{
        //generate orange tile in position
        board_[pos.x][pos.y] = 4;
        return;

    }


}

//when detecting an adjacent tile that is equal, add or "collide"
void Model::collide(char direct)
{
    if (direct == 'l') {
        for(int i=1;i<3;i++){
            for(int j=0;j<3;j++){
                if(board_[i][j] !=0 && (board_[i][j] == board_[i-1][j])){
                    board_[i-1][j] = board_[i][j]*2;
                    board_[i][j] = 0;
                }
            }
        }

    }
    if (direct == 'r') {
        for(int i=2;i>=0;i--){
            for(int j=0;j<3;j++){
                if(board_[i][j] && (board_[i][j] == board_[i+1][j])){
                    board_[i+1][j] = board_[i][j] *2;
                    board_[i][j] = 0;
                }
            }
        }

    }
    if (direct == 'u') {
        for(int i=0;i<3;i++){
            for(int j=1;j<3;j++){
                if(board_[i][j] != 0 && (board_[i][j]==board_[i][j-1])){
                    board_[i][j-1] = board_[i][j] *2;
                    board_[i][j] = 0;

                }
            }
        }

    }
    if (direct == 'd') {
        for(int i=0;i<3;i++){
            for(int j=2;j>=0;j--){
                if(board_[i][j] != 0 && (board_[i][j] == board_[i][j+1])){
                    board_[i][j+1] = board_[i][j] *2;
                    board_[i][j] = 0;

                }
            }
        }

    }
}

//pushes all tiles to direction given
void Model::shift_tiles(char direct) {

    //the down key is pressed, shift everything down
    if(direct == 'd'){
        for(int i = 0; i<3; i++){
            for(int j = 2; j>=0; j--){
                if(board_[i][j] != 0 ){
                    for(int k = j+1; k< 3; k++){
                        if(board_[i][k] == 0){
                            board_[i][k] =board_[i][j];
                            board_[i][j] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
    //shifting up
    if(direct == 'u'){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board_[i][j] != 0){
                    for(int k=j-1;k>=0;k--){
                        if(board_[i][k] == 0){
                            board_[i][k] = board_[i][j];
                            //board_[j][i]=board_[k][i];
                            board_[i][j]=0;
                            break;
                        }
                    }
                }
            }
        }
    }
    //shifting to the left
    if(direct == 'l'){
        for(int i=1;i<3;i++){ //can only use 2 rightmost columns
            for(int j=0;j<3;j++){
                if(board_[i][j]  != 0){
                    for(int k=i-1;k>=0;k--){
                        if(board_[k][j] == 0){
                            board_[k][j] = board_[i][j];
                            board_[i][j] = 0;
                            break;
                        }
                    }
                }
            }
        }

    }
    //shifting to the right
    if(direct == 'r'){
        for(int i=2;i>=0;i--){
            for(int j=0;j<3;j++){
                if(board_[i][j] != 0){
                    for(int k=i+1;k<3;k++){
                        if(board_[k][j] == 0){
                            board_[k][j] = board_[i][j];
                            board_[i][j] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }
}

