//
// Created by LucasVanDam on 06/11/2026.
//

#include <algorithm>
#include <array>
#include <bit>
#include <format>
#include <string>
#include <numeric>
#include <span>
#include <type_traits>
#include <vector>

inline std::string MD5(const std::vector<std::byte>& input) {
    constexpr std::uint32_t K[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122,
        0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
        0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9,
        0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244,
        0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
        0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };
   constexpr std::uint32_t s[64] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14,
        20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6,
        10, 15, 21
    };

    std::uint32_t a0 = 0x67452301;
    std::uint32_t b0 = 0xefcdab89;
    std::uint32_t c0 = 0x98badcfe;
    std::uint32_t d0 = 0x10325476;

    std::vector<std::byte> processedInput = input;;

    processedInput.push_back(static_cast<std::byte>(0x80));

    while ((processedInput.size() * 8) % 512 < 448) {
        processedInput.push_back(static_cast<std::byte>(0x00));
    }

    std::uint64_t sizeBits = (input.size() * 8) & 0xffffffffffffffff;

    auto bytes = std::bit_cast<std::array<std::byte, 8>>(sizeBits);
    processedInput.insert(processedInput.end(), bytes.begin(), bytes.end());

    for (int i = 0; i < processedInput.size() / 64; ++i) {
        std::vector<std::byte> chunkBytes(64);
        std::memcpy(chunkBytes.data(), processedInput.data() + i * 64, 64);
        std::vector<std::uint32_t> chunkInt(16);

        for (int j = 0; j < chunkBytes.size() / 4; ++j) {
            std::memcpy(&chunkInt[j], &chunkBytes[j * 4], 4);
        }

        std::uint32_t A = a0;
        std::uint32_t B = b0;
        std::uint32_t C = c0;
        std::uint32_t D = d0;

        for (int j = 0; j < 64; ++j) {
            std::uint32_t F, g;
            if (j <= 15) {
                F = (B & C) | (~B & D);
                g = j;
            }
            else if (j <= 31) {
                F = (D & B) | (~D & C);
                g = (5 * j + 1) % 16;
            }
            else if (j <= 47) {
                F = B ^ C ^ D;
                g = (3 * j + 5) % 16;
            }
            else {
                F = C ^ (B | (~D));
                g = (7 * j) % 16;
            }

            F = F + A + K[j] + chunkInt[g];
            A = D;
            D = C;
            C = B;
            B = B + ((F << s[j]) | (F >> (32 - s[j])));
        }

        a0 = a0 + A;
        b0 = b0 + B;
        c0 = c0 + C;
        d0 = d0 + D;
    }

    std::vector<std::byte> digestBytes(16);
    std::memcpy(digestBytes.data(), &a0, 4);
    std::memcpy(digestBytes.data() + 4, &b0, 4);
    std::memcpy(digestBytes.data() + 8, &c0, 4);
    std::memcpy(digestBytes.data() + 12, &d0, 4);

    std::string result;

    for (const auto& byte : digestBytes) {
        result += (std::format("{:02x}", static_cast<uint8_t>(byte)));
    }

    return result;
}

int main() {
    std::string testInput = "ckczppom";
    for (int i = 0;; ++i) {
        std::string input = testInput + std::to_string(i);
        std::vector<std::byte> inputBytes(input.size());
        std::ranges::transform(input, inputBytes.begin(), [](char c) {return static_cast<std::byte>(c);});
        auto result = MD5(inputBytes);

        if (result.starts_with("000000")) {
            std::printf("%d", i);
            break;
        }
    }

    

    return 0;
}
