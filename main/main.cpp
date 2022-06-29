#include "base/include/context.h"
#include <QApplication>
#include <cstdint>
#include <QMainWindow>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    base::IContext::Option option{
        {
            5,
            {"thread_pool"},
            10,
            true
        },
        {
            0,
            "main",
            "desktop.log",
            0xffffffff,
            10
        }
    };
    base::context_builder::createContext(option);
    base::IContext::get()->defaultLogger()->info("desktop start.");
    base::IContext::get()->defaultScheduler()->start();
    base::IContext::get()->defaultLogger()->info("thread pool start.");
    QMainWindow window;
    window.resize(1024 , 768);
    window.show();

    base::IContext::get()->mainThreadScheduler()->start();
    base::IContext::get()->defaultLogger()->info("mainThreadScheduler exit.");
    base::context_builder::destroyContext();
    return 0;
}