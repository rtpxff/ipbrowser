//
// Copyright (c) 2020-2027 Robert T. Palka. All rights reserved.
// @author Robert T. Palka (rtpxff)
//

#pragma once

#include "util.h"

class checker
{
public:
    checker(void);
    ~checker(void);

public:
    //
    // Adding a prefix to the set.
    // Returns 0 for success or -1 for invalid call arguments.
    //
    int add(uint base, char mask);

    //
    // Removes a prefix from the set.
    // Returns 0 for success or -1 for invalid call arguments.
    //
    int del(uint base, char mask);

    //
    // Checks if the IP address is included in the prefix set.
    // Returns the mask of the smallest prefix (with the highest mask value) 
    // in the set that contains the specified address.
    // Returns - 1 if the IP is not included in the prefix set,
    //
    char check(uint ip);

private:
    uint get_limit(uint base, char mask);

private:
    typedef std::map<uint, uint> t_mu;
    typedef std::map<uint, t_mu > t_map_pref;
    t_map_pref m_map_pref;
    typedef std::vector<uint> t_vec_tmp;
    typedef std::map<uint, char> t_map_tmp;

    typedef std::map<uint, t_map_tmp > t_map_bounders;
    t_map_bounders m_map_bounders;
};
