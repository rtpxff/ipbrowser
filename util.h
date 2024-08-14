//
// Copyright (c) 2020-2027 Robert T. Palka. All rights reserved.
// @author Robert T. Palka (rtpxff)
//

#pragma once

#include <string>
#include <map>
#include <vector>
#include <bitset>

typedef unsigned int uint;
typedef unsigned char uchar;

class util
{
public:
    util(void);
    ~util(void);

public:
    static void converter_ip(uint base, uchar ip[4]);
    static uint converter_ip(uchar ip[4]);
    

    static void converter_ip(uchar ip[4], std::string& binary_str, std::string& ulong_str);

    static void converter_mask(uint base, uchar ip[4], uint& count, uint& neg);
    static void converter_mask(uint base, std::string& binary_str, std::string& ulong_str);
    
    static uint converter_mask(uint mask);
};
