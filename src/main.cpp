#include "Gpio/GpioManager.h"
#include <chrono>
#include <thread>

int main()
{
    GPIO::GpioManager manager;
    manager.setupController(18);
    manager.setPinOn(18);
    std::this_thread::sleep_for(std::chrono::seconds(4));
    manager.setPinOff(18);
    return 0;
}
