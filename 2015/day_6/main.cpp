//
// Created by LucasVanDam on 07/11/2026.
//

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct PairHash {
    std::size_t operator()(const std::pair<int, int> &p) const noexcept {
        // Combine hashes of both integers
        // This uses a simple but effective hash combination
        return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
    }
};

std::array<std::pair<uint16_t, uint16_t>, 2> get_operands(std::string_view input) {
    std::string_view left_operand = input.substr(0, input.find_first_of(' '));
    std::string_view right_operand = input.substr(input.find_last_of(' ') + 1);

    std::pair<uint16_t, uint16_t> left_operand_pair;
    std::from_chars(left_operand.data(),
                    left_operand.data() + static_cast<long long>(left_operand.find_first_of(',')),
                    left_operand_pair.first);
    std::from_chars(left_operand.data() + static_cast<long long>(left_operand.find_first_of(',') + 1),
        left_operand.data() + left_operand.size(),
        left_operand_pair.second);

    std::pair<uint16_t, uint16_t> right_operand_pair;

    std::from_chars(right_operand.data(),
        right_operand.data() + static_cast<long long>(right_operand.find_first_of(',')),
        right_operand_pair.first);
    std::from_chars(right_operand.data() + static_cast<long long>(right_operand.find_first_of(',') + 1),
        right_operand.data() + right_operand.size(),
        right_operand_pair.second);

    return {left_operand_pair, right_operand_pair};
}

int main() {
    std::vector<std::string> input_strings;

    std::string line;
    while (!std::cin.eof()) {
        std::getline(std::cin, line);

        if (std::cin.fail()) {
            //error
            return EXIT_FAILURE;
        }

        input_strings.push_back(line);
    }

    std::unordered_set<std::pair<uint16_t, uint16_t>, PairHash> on_lights;
    //using unordered set for O(1) insert/delete speeds

    std::unordered_map<std::pair<uint16_t, uint16_t>, std::uint16_t, PairHash> on_lights_map;

    for (const auto &input: input_strings) {
        if (input.starts_with("turn on ")) {
            std::string_view constraints = std::string_view(input).substr(8);

            auto coords = get_operands(constraints);

            for (int i = coords[0].first; i <= coords[1].first; ++i) {
                for (int j = coords[0].second; j <= coords[1].second; ++j) {
                    if (!on_lights.contains({i,j})) {
                        on_lights.insert({i, j});
                    }

                    if (on_lights_map.contains({i,j})) {
                        on_lights_map.at({i,j})++;
                    }
                    else {
                        on_lights_map.insert({{i,j}, 1});
                    }
                }
            }
        }
        else if (input.starts_with("turn off ")) {
            std::string_view constraints = std::string_view(input).substr(9);

            auto coords = get_operands(constraints);

            for (int i = coords[0].first; i <= coords[1].first; ++i) {
                for (int j = coords[0].second; j <= coords[1].second; ++j) {
                    if (on_lights.contains({i,j})) {
                        on_lights.erase({i, j});
                    }

                    if (on_lights_map.contains({i,j})) {
                        if (on_lights_map.at({i,j}) >= 1) {
                            on_lights_map.at({i,j})--;
                        }
                    }
                }
            }
        }
        else if (input.starts_with("toggle ")) {
            const std::string_view constraints = std::string_view(input).substr(7);

            auto coords = get_operands(constraints);

            for (int i = coords[0].first; i <= coords[1].first; ++i) {
                for (int j = coords[0].second; j <= coords[1].second; ++j) {
                    if (on_lights.contains({i,j})) {
                        on_lights.erase({i, j});
                    }
                    else {
                        on_lights.insert({i, j});
                    }

                    if (on_lights_map.contains({i,j})) {
                        on_lights_map.at({i,j})+=2;
                    }
                    else {
                        on_lights_map.insert({{i,j}, 2});
                    }
                }
            }
        }
    }

    std::printf("lights on: %llu\n", on_lights.size());

    std::uint64_t total_brightness = 0;

    std::ranges::for_each(on_lights_map, [&total_brightness](std::pair<std::pair<std::uint16_t, std::uint16_t>, std::uint16_t> value) {
        total_brightness += value.second;
    });

    std::printf("total brightness: %llu\n", total_brightness);

    return 1;
}
