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

    int64_t x_santa = 0;
    int64_t y_santa = 0;
    int64_t x_robo = 0;
    int64_t y_robo = 0;

    std::unordered_map<std::pair<int, int>, int, PairHash> map;

    map[{0,0}]++;

    bool santa_turn = true;

    for (const char &c: input) {
        switch (c) {
            case '<':
                santa_turn ? x_santa-- : x_robo--;
                break;
            case '>':
                santa_turn ? x_santa++ : x_robo++;
                break;
            case '^':
                santa_turn ? y_santa++ : y_robo++;
                break;
            case 'v':
                santa_turn ? y_santa-- : y_robo--;
                break;
        }

        santa_turn ? map[{x_santa,y_santa}]++ : map[{x_robo, y_robo}]++;
        santa_turn = !santa_turn;
    }

    std::cout << map.size() << std::endl;

    return 1;
}
