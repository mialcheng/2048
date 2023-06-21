#include "view.hxx"


using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;
//const int grid_size = 50;


static Color const red_color  = Color::medium_red();
static Color const orange_color = Color(255, 165, 0, 255 );
static Color const yellow_color = Color(255,255,0,255);
static Color const green_color = Color::medium_green();
static Color const blue_color = Color::medium_blue();
static Color const indigo_color = Color(75, 0, 130, 255);
static Color const violet_color = Color(238, 130, 238, 255);
static Color const white_color = Color::white();
static Color const grey_color = Color(220, 220, 220, 255);
static Color const black_color = Color::black();


View::View(Model const& model)
        : model_(model),
          red_sprite_{{grid_size, grid_size}, red_color},
          orange_sprite_{{grid_size, grid_size}, orange_color},
          yellow_sprite_{{grid_size, grid_size}, yellow_color},
          green_sprite_{{grid_size, grid_size}, green_color},
          blue_sprite_{{grid_size, grid_size}, blue_color},
          indigo_sprite_{{grid_size, grid_size}, indigo_color},
          violet_sprite_{{grid_size, grid_size}, violet_color},
          white_sprite_{{grid_size, grid_size}, white_color},
          grey_sprite_{{grid_size, grid_size}, grey_color},
          score_bar_{{grid_size*3, grid_size}, white_color},
          winner_sprite{},
          loser_sprite{},
          score_text_{}


{ }



void
View::draw(ge211::Sprite_set& set)
{
    //draw score bar at bottom
    set.add_sprite(score_bar_,{0,grid_size*3}, 2);



    //sprites are not displaying
    if (model_.win()) {
        //display "You won!"
        ge211::Text_sprite::Builder name_builder(sans15);
        name_builder.color(black_color) << "You won!";
        //reconfigure() modifies that sprite
        winner_sprite.reconfigure(name_builder);
        set.add_sprite(winner_sprite, {25, grid_size*3 + 25}, 3);

    }else if(model_.loser){
        //display "You lose!"
        ge211::Text_sprite::Builder name_builder(sans15);
        name_builder.color(black_color) << "You lose!";
        //reconfigure() modifies that sprite
        loser_sprite.reconfigure(name_builder);
        set.add_sprite(loser_sprite, {25,grid_size*3 + 25}, 3);

    }
    //calculate the new score everytime you draw
    int score = 0;

    //adds a colored sprite that corresponds to the board position's value
    for(int i = 0; i< 3; i++){
        for (int j = 0; j <3; j++){
            int pos_number = model_.number_at(i,j);

            //update the score
            score += pos_number;

            if(pos_number == 0){
                set.add_sprite(grey_sprite_, Position{i*grid_size,
                                                      j*View::grid_size},0);
            }else if(pos_number == 2){
                set.add_sprite(red_sprite_, Position{i*grid_size,
                                                     j*grid_size},1);
            }else if(pos_number == 4){
                set.add_sprite(orange_sprite_, Position{i*grid_size,
                                                        j*grid_size},1);
            }else if(pos_number == 8){
                set.add_sprite(yellow_sprite_, Position{i*grid_size,
                                                        j*grid_size},1);
            }else if(pos_number == 16){
                set.add_sprite(green_sprite_, Position{i*grid_size,
                                                       j*grid_size},1);
            }else if(pos_number == 32){
                set.add_sprite(blue_sprite_, Position{i*grid_size,
                                                      j*grid_size},1);
            }else if(pos_number == 64){
                set.add_sprite(indigo_sprite_, Position{i*grid_size,
                                                        j*grid_size},1);
            }else if(pos_number == 128){
                set.add_sprite(violet_sprite_, Position{i*grid_size,
                                                        j*grid_size},1);
            }else if(pos_number == 256){
                set.add_sprite(white_sprite_, Position{i*grid_size,
                                                       j*grid_size},1);
            }

        }

        //draw the score text sprite
        ge211::Text_sprite::Builder score_builder(sans15);
        score_builder.color(black_color) << "Score: " << score;
        //reconfigure() modifies that sprite
        score_text_.reconfigure(score_builder);
        set.add_sprite(score_text_, {15, grid_size*3 }, 3);
        //draw score in text in the middle of score bar
    }

}

View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * Dimensions{3, 4};
}

View::Position
View::screen_to_board(View::Position pos) const
{
    return {pos.x / grid_size, pos.y / grid_size};
}


