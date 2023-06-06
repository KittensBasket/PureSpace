#include "src/app.hpp"
#include <exception>

int main(void)
{

    try {
        App app;
        app.run();
    } catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
