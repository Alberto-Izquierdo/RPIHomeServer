#ifndef APP_H
#define APP_H

#include <vector>
#include <memory>

namespace core
{
class BaseModule;
}  // namespace core

class App
{
public:
    App() noexcept;
    ~App() noexcept;

    void init() noexcept;

    void start() noexcept;

    // Delete copy/assign
    App(const App &) = delete;
    App &operator=(const App &) const = delete;

private:
    std::vector<std::unique_ptr<core::BaseModule>> m_modules;
};

#endif  // APP_H
