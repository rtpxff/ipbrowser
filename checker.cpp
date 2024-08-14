//
// Copyright (c) 2020-2027 Robert T. Palka. All rights reserved.
// @author Robert T. Palka (rtpxff)
//

#include "checker.h"

checker::checker(void)
{
}

checker::~checker(void)
{
}

int checker::add(uint base, char mask)
{
    uchar ip_base[4];
    util::converter_ip(base, ip_base);

    uchar ip_mask[4];
    uint real_mask = util::converter_mask(mask);
    util::converter_ip(real_mask, ip_mask);


    uchar ip_limit[4];
    for(int i = 0; i < 4; i++)
        ip_limit[i] = 0xff - ip_mask[i] + ip_base[i];
    uint limit = util::converter_ip(ip_limit);

    m_map_pref[limit].insert({ base, mask });
    return 0;
}

int checker::del(uint base, char mask)
{
    t_map_pref::iterator it = m_map_pref.find(mask);
    if (it == m_map_pref.end())
        return -1;

    size_t res = it->second.erase(base) > 0 ? 0 : -1;
    if (it->second.size() == 0)
        m_map_pref.erase(mask);

    return res;
}

char checker::check(uint ip)
{
    std::map<uchar, uchar> tmp_mask;
    uint test = ip;

    for(auto itx = m_map_pref.begin(); m_map_pref.end() != itx; ++itx)
    {
        //uchar ip_baset[4];
        //util::converter_ip(ip, ip_baset);
        //uchar ip_basetf[4];
        //util::converter_ip(itx->first, ip_basetf);

        if (ip <= itx->first)
        {
            for (auto it = itx->second.begin(); it != itx->second.end(); ++it)
            {
                if (ip >= it->first)
                {
                    m_map_pref_tmp[itx->first].push_back(it->first);
                    tmp_mask[itx->first] = it->second;
                }
            }
        }
    }

    t_vec_tmp keys;
    for (auto ity = m_map_pref_tmp.begin(); ity != m_map_pref_tmp.end(); ++ity)
    {
        t_vec_tmp::iterator result = std::min_element(ity->second.begin(), ity->second.end());
        m_map_pref_tmp2.insert({ ity->first, *result });
        keys.push_back(ity->first);
    }
    if (keys.size() == 0)
        return -1;
    t_vec_tmp::iterator result = std::max_element(keys.begin(), keys.end());

    auto itz = m_map_pref_tmp2.find(*result);
    if (itz != m_map_pref_tmp2.end())
    {
        return tmp_mask[*result];
    }
    return -1;
}
