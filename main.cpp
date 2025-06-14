#include <iostream>
#include "BetfairAPI/utils/date_utils.h"

int main() {
    std::cout << "Hello World!\n";

    BetfairAPI::Utils::Date date{"2025-06-14T15:04:05.123+02:00"};

    std::cout << date.toIsoString() << "\n";
} 