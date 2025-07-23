#include <iostream>
#include <cstdint>
#include <bit>
#include <bitset>
#include <sstream>

class MD5Hash
{
private:
    std::vector<uint32_t> payload;

    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    uint32_t swap_endian(uint32_t value)
    {
        uint32_t result = 0x0;

        result = value >> 24;
        result = result | (0x0000FF00 & (value >> 8));
        result = result | (0x00FF0000 & (value << 8));
        result = result | (0xFF000000 & (value << 24));

        return result;
    }

public:
    void digestBlock(std::vector<uint32_t> chunk);
    void digestMessage(std::string msg);
    std::string getHash();
    void clear();
};