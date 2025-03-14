#include <iostream>
#if __cplusplus >= 202300L
    #include <print>
#endif

int main() {
    std::cout << __cplusplus << std::endl;

    std::cout << "Hello, World!" << std::endl;
    #if __cplusplus >= 202300L
        std::print("Hello, World!\n");
    #else
        std::cout << "C++23 is not supported" << std::endl;
    #endif

    return 0;
}

