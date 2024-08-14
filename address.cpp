//
// Copyright (c) 2020-2027 Robert T. Palka. All rights reserved.
// @author Robert T. Palka (rtpxff)
//

#include "util.h"
#include "checker.h"

//#include <iostream>


int main()
{
    checker dk;

    {
        uchar ip_base[4] = { 10, 20, 0, 0 };
        uint base = util::converter_ip(ip_base);
        dk.add(base, 16);
    }

    {
        uchar ip_base[4] = { 32, 64, 128, 0 };
        uint base = util::converter_ip(ip_base);
        dk.add(base, 15);
    }

    {
        uchar ip_base[4] = { 32, 64, 128, 0 };
        uint base = util::converter_ip(ip_base);
        dk.add(base, 20);
    }


    char mask2 = 0;
    {
        uchar ip_base2[4] = { 32, 64, 129, 255 };
        uint base2 = util::converter_ip(ip_base2);
        mask2 = dk.check(base2);
    }

    {
        uchar ip_base2[4] = { 10, 20, 255, 255 };
        uint base2 = util::converter_ip(ip_base2);
        mask2 = dk.check(base2);
    }



    printf("");
}
