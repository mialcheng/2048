#pragma once

#include "model.hxx"

class View
{
public:
    static int const grid_size = 50;

    using Dimensions = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;

    Position
    screen_to_board(Position screen_pos) const;

private:
    Model const& model_;

    //rectangle sprites
    ge211::Rectangle_sprite const red_sprite_, orange_sprite_,
            yellow_sprite_, green_sprite_, blue_sprite_, indigo_sprite_,
            violet_sprite_, white_sprite_, grey_sprite_, score_bar_;

    //text sprites
    ge211::Font sans15{"sans.ttf", 15};

    ge211::Text_sprite winner_sprite, loser_sprite, score_text_;


};
