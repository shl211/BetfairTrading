#include <iostream>
#include "BetfairAPI/date.h"

int main() {
    BetfairAPI::Date date {"2024-06-07T12:34:56Z"};
    std::cout << date.getIsoString() << "\n";
}