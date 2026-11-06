//
// Created by LucasVanDam on 06/11/2026.
//

#include <iostream>
#include <string>
#include <unordered_map>

struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
        // Combine hashes of both integers
        // This uses a simple but effective hash combination
        return std::hash<int>{}(p.first) ^ (std::hash<int>{}(p.second) << 1);
    }
};

int main() {
    std::string input;
    std::getline(std::cin, input);

    int64_t x = 0;
    int64_t y = 0;

    std::unordered_map<std::pair<int, int>, int, PairHash> map;

    map[{0,0}]++;

    for (const char &c: input) {
        switch (c) {
            case '<':
                x--;
                break;
            case '>':
                x++;
                break;
            case '^':
                y++;
                break;
            case 'v':
                y--;
                break;
        }

        map[{x,y}]++;
    }

    std::cout << map.size() << std::endl;

    return 1;
}
