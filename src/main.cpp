#include <chrono>
#include <thread>
#include <Core/App.h>

int main()
{
    App &app = App::getInstance();
    app.init();
    app.start();
    return 0;
}
