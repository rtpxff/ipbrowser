//
// Copyright (c) 2020-2027 Robert T. Palka. All rights reserved.
// @author Robert T. Palka (rtpxff)
//

#include "util.h"

util::util(void)
{
}

util::~util(void)
{
}

void util::converter_ip(uint base, uchar ip[4])
{
    for (int i = 1; i < 5; i++)
        ip[i - 1] = base >> (32 - (i * 8));
}

uint util::converter_ip(uchar ip[4])
{
    uint base_res = 0;
    for (int i = 1; i < 5; i++)
        base_res += ip[i - 1] << (32 - (i * 8));
    return base_res;

}

void util::converter_ip(uchar ip[4], std::string& binary_str, std::string& ulong_str)
{
    for (int i = 1; i < 5; i++)
    {
        binary_str += std::bitset<8>(ip[i - 1]).to_string();
        ulong_str += std::to_string(std::bitset<8>(ip[i - 1]).to_ulong());
        if (i < 4)
        {
            binary_str += ".";
            ulong_str += ".";
        }
    }
}

void util::converter_mask(uint mask, uchar ip[4], uint& count, uint& neg)
{
    count = 0;
    for (int i = 31 - mask; i >= 0; i--)
        count |= 1 << i;

    neg = count;
    count = ~count;

    for (int i = 1; i < 5; i++)
        ip[i - 1] = count >> (32 - (i * 8));
}

uint util::converter_mask(uint mask)
{
    uint count = 0;
    for (int i = 31 - mask; i >= 0; i--)
        count |= 1 << i;
    return ~count;
}

void util::converter_mask(uint base, std::string& binary_str, std::string& neg_str)
{
    unsigned int count = 0;
    for (int i = 31 - base; i >= 0; i--)
        count |= 1 << i;
    neg_str = std::bitset<32>(count).to_string();
    count = ~count;
    binary_str = std::bitset<32>(count).to_string();
}
