#include "app.hpp"
#include "text.hpp"
#include "timer.hpp"

int main(int argc, char** argv)
{
    App::init();

    Text text = Text("0:00", "font", 50);
    text.set_center({0, 1});
    text.pos.x = App::get_window_width() / 2;
    text.pos.y = App::get_window_height();

    Timer timer = Timer(text);

    App::main_loop();

    return 0;
}
