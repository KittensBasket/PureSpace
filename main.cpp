#include "src/app.hpp"
#include <exception>

int main(void)
{

    try {
        App app;
        app.run();
    } catch(std::exception& ex) {
        return 1;
    }

    return 0;
}
