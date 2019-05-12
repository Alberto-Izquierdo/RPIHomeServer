#include <Core/App.h>

int main()
{
    App &app = App::getInstance();
    if (app.init()) {
        app.start();
    }
    return 0;
}
