#include "src/app.hpp"
#include <exception>

int main(void)
{

    try {
        App app;
        app.run();
    } catch(std::exception& ex) {
        ex.what();
    }

    return 0;
}
