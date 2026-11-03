//
// Created by LucasVanDam on 03/11/2026.
//

#include <iostream>
#include <string>

int main() {
    std::string input_string;
    std::printf("Please input the test string: \n");
    std::cin >> input_string;

    if (input_string.find_first_not_of("()") != std::string::npos) {
        std::printf("String did not only contain ( and ).");
        return EXIT_FAILURE;
    }

    int floor = 0;
    int first_basement = INT_MAX;

    for (int i = 0; i < input_string.length(); i++) {
        switch (input_string[i]) {
            case '(':
                floor++;
                break;
            case ')':
                floor--;
                break;
            default:
                std::printf("Wrong input.");
                return EXIT_FAILURE;
        }

        if (floor < 0 && first_basement == INT_MAX) {
            first_basement = i + 1; // 0 based vs 1 based in the question
        }
    }

    std::printf("We ended at floor: %d, first basement at: %d.", floor, first_basement);

    return 0;
}