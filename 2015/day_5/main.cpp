//
// Created by LucasVanDam on 07/11/2026.
//

#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <__msvc_ranges_to.hpp>

inline bool is_nice_part_1(std::string_view line) {
    std::array<std::string_view, 4> badTokens = {"ab", "cd", "pq", "xy"};
    if (std::ranges::any_of(badTokens, [line](std::string_view token) {
        return std::ranges::contains_subrange(line, token); // playing with some new ranges features
    })) {
        return false;
    }

    std::array<char, 5> vowels = {'a', 'e', 'i', 'o', 'u'};
    bool nice = false;
    nice = std::ranges::count_if(line, [vowels](const char &token) {
        return std::ranges::contains(vowels, token);
    }) >= 3;
    nice &= std::ranges::adjacent_find(line) != std::ranges::end(line);

    return nice;
}

inline bool is_nice_part_2(std::string_view line) {
    bool nice = false;

    for (const auto &tokens: line | std::views::slide(3)) {
        if (tokens[0] == tokens[2]) {
            nice = true;
            break;
        }
    }

    if (!nice)
        return false;

    std::vector<std::string_view> subTokens;

    for (const auto &tokens: line | std::views::slide(2)) {
        std::string_view token(tokens.data(), tokens.size());

        if (!subTokens.empty() && subTokens.back() == token) {
            // needed for the case of four sequential chars that are the same so it doesnt trip again
            subTokens.emplace_back("divider");
            continue;
        }
        if (!std::ranges::contains(subTokens, token)) {
            subTokens.push_back(token);
        } else {
            return true;
        }
    }

    return false;
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

    std::uint64_t nice_strings = 0;

    for (const auto &input: input_strings) {
        if (is_nice_part_2(input))
            nice_strings++;
    }

    std::printf("%llu\n", nice_strings);
}
