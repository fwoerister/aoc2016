#include <iostream>
#include <cstdint>
#include <bit>
#include <bitset>
#include <sstream>

#include "md5.hpp"

const std::vector<uint32_t> K = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

const std::vector<uint32_t> s = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

void MD5Hash::clear()
{
    a0 = 0x67452301;
    b0 = 0xefcdab89;
    c0 = 0x98badcfe;
    d0 = 0x10325476;
}

void MD5Hash::digestBlock(std::vector<uint32_t> block)
{
    uint32_t a = a0, b = b0, c = c0, d = d0;
    uint32_t F, g;

    for (int i = 0; i < 64; ++i)
    {
        if (i <= 15)
        {

            F = (b & c) | ((~b) & d);
            g = i;
        }
        else if (i <= 31)
        {
            F = (d & b) | ((~d) & c);
            g = (5 * i + 1) % 16;
        }
        else if (i <= 47)
        {
            F = b ^ c ^ d;
            g = (3 * i + 5) % 16;
        }
        else if (i <= 63)
        {
            F = c ^ (b | (~d));
            g = (7 * i) % 16;
        }

        F = F + a + K[i] + block[g];
        a = d;
        d = c;
        c = b;
        b = b + std::__rotl(F, s[i]);
    }

    a0 = a0 + a;
    b0 = b0 + b;
    c0 = c0 + c;
    d0 = d0 + d;
}

void MD5Hash::digestMessage(std::string msg)
{
    int idx = 0;
    std::vector<uint8_t> byteStream;
    std::vector<uint32_t> block;

    for (char c : msg)
        byteStream.push_back(uint8_t(c));

    byteStream.push_back(uint8_t(0x80));

    while (byteStream.size() % 64 != 56)
        byteStream.push_back(uint8_t(0x00));

    uint64_t msgSize = uint64_t(msg.length() * 8);

    byteStream.push_back(uint8_t(msgSize));
    byteStream.push_back(uint8_t(msgSize >> 8));
    byteStream.push_back(uint8_t(msgSize >> 16));
    byteStream.push_back(uint8_t(msgSize >> 24));

    while (idx < byteStream.size())
    {
        while (block.size() < 16)
        {
            uint32_t chunk = 0x0;
            chunk |= byteStream[idx];
            chunk |= byteStream[idx + 1] << 8;
            chunk |= byteStream[idx + 2] << 16;
            chunk |= byteStream[idx + 3] << 24;
            block.push_back(chunk);

            idx += 4;
        }

        digestBlock(block);
        block.clear();
    }
}

std::string MD5Hash::getHash()
{
    std::stringstream ssA, ssB, ssC, ssD, hash;
    std::stringstream prefixA, prefixB, prefixC, prefixD;

    ssA << std::hex << swap_endian(a0);

    for (int i = 0; i < 8 - ssA.str().length(); ++i)
        prefixA << '0';

    ssB << std::hex << swap_endian(b0);

    for (int i = 0; i < 8 - ssB.str().length(); ++i)
        prefixB << '0';

    ssC << std::hex << swap_endian(c0);

    for (int i = 0; i < 8 - ssC.str().length(); ++i)
        prefixC << '0';

    ssD << std::hex << swap_endian(d0);

    for (int i = 0; i < 8 - ssD.str().length(); ++i)
        prefixD << '0';

    return prefixA.str() + ssA.str() + prefixB.str() + ssB.str() + prefixC.str() + ssC.str() + prefixD.str() + ssD.str();
}