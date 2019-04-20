//#include "Gpio/GpioManager.h"
#include <chrono>
#include <thread>
#include "Core/App.h"

int main()
{
    App app;
    app.init();
    app.start();
    /*
    GPIO::GpioManager manager;
    manager.setupController(18);
    manager.setPinOn(18);
    std::this_thread::sleep_for(std::chrono::seconds(4));
    manager.setPinOff(18);
    */
    return 0;
}
