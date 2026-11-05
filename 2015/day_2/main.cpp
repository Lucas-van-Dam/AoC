//
// Created by LucasVanDam on 03/11/2026.
//

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> input_strings;

    std::string line;
    while (!std::cin.eof())
    {
        std::getline(std::cin, line);

        if (std::cin.fail())
        {
            //error
            break;
        }

        input_strings.push_back(line);
    }

    int footOfPaper = 0;
    int footOfRibbon = 0;

    for (int i = 0; i < input_strings.size(); i++) {
        std::string dimensions = input_strings.at(i);
        int length = 0;
        int width;
        size_t pos;
        size_t offset;
        if (pos = dimensions.find('x'); pos != std::string::npos) {
            length = std::stoi(dimensions.substr(0, pos));
            offset = pos + 1;
        }
        else {
            return 1;
        }
        if (pos = dimensions.find('x', offset); pos != std::string::npos) {
            width = std::stoi(dimensions.substr(offset, offset - pos));
            offset = pos + 1;
        }
        else {
            return 1;
        }
        int height = std::stoi(dimensions.substr(offset, dimensions.size() - offset));

        int component1 = length * width;
        int component2 = height * width;
        int component3 = length * height;

        footOfPaper += 2 * component1 + 2 * component2 + 2 * component3 + std::min(component1, std::min(component2, component3));
        footOfRibbon += length * width * height + std::min(2 * length + 2 * height, std::min(2 * length + 2 * width, 2 * width + 2 * height));
    }

    std::cout << std::to_string(footOfPaper) << ", " << std::to_string(footOfRibbon) << std::endl;

    return 0;
}
