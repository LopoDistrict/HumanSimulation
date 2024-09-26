#include <iostream>
#include <fstream>
#include <library/dynamic.h>
#include <library/json.h>

int main() {
    

    for (const auto& i : data["inventory"]) {
        std::cout << i << std::endl;
    }

    return 0;
}

