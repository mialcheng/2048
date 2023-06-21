#include "controller.hxx"
#include <iostream>
Controller::Controller()
        : view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}
View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void Controller::on_key_down(ge211::events::Key key) {
    if (key == ge211::events::Key::left()){
        direction = 'l';

        model_.play_move(direction);

        //do play_move
    } else if (key == ge211::events::Key::right()){
        direction = 'r';

        model_.play_move(direction);

        //play_move
    } else if (key == ge211::events::Key::up()){
        direction = 'u';

        model_.play_move(direction);

    } else if (key == ge211::events::Key::down()){
        direction = 'd';

        model_.play_move(direction);

    }

}




