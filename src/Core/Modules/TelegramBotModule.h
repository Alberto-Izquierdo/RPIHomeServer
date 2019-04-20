#ifndef TELEGRAMBOTMODULE_H
#define TELEGRAMBOTMODULE_H

#include <Core/BaseModule.h>

namespace core
{
class TelegramBotModule : public BaseModule
{
public:
    TelegramBotModule(std::shared_ptr<MultithreadQueue<std::shared_ptr<Message>>> &outputQueue) noexcept;
    ~TelegramBotModule() noexcept final;

    void specificStart() noexcept final;
    void update() noexcept final;
    void specificExit() noexcept final;
    const std::string &getModuleName() const noexcept final;

    void turnOnLight() noexcept;
    void turnOffLight() noexcept;

private:
    static const std::string m_moduleName;
};
}  // namespace core

#endif
