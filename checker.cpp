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

uint checker::get_limit(uint base, char mask)
{
    uchar ip_base[4];
    util::converter_ip(base, ip_base);

    uchar ip_mask[4];
    uint real_mask = util::converter_mask(mask);
    util::converter_ip(real_mask, ip_mask);

    uchar ip_limit[4];
    for (int i = 0; i < 4; i++)
        ip_limit[i] = 0xff - ip_mask[i] + ip_base[i];
    return util::converter_ip(ip_limit);
}

int checker::add(uint base, char mask)
{
    if (mask < 0 || mask > 32)
        return -1;
    uint limit = get_limit(base, mask);
    m_map_pref[limit].insert({ base, mask });

    for (uint i = base; i <= limit; i+=256)
        m_map_bounders[i].insert({ limit, mask });
    m_map_bounders[limit].insert({ limit, mask });
    return 0;
}

int checker::del(uint base, char mask)
{
    uint limit = get_limit(base, mask);

    t_map_pref::iterator it = m_map_pref.find(limit);
    if (it == m_map_pref.end())
        return -1;

    size_t res = it->second.erase(base) > 0 ? 0 : -1;
    if (it->second.size() == 0)
        m_map_pref.erase(limit);

    for (uint i = base; i <= limit; i += 256)
    {
        t_map_bounders::iterator itx = m_map_bounders.find(i);
        itx->second.erase(limit);
        if (itx->second.size() == 0)
            m_map_bounders.erase(i);
    }
    t_map_bounders::iterator itx = m_map_bounders.find(limit);
    itx->second.erase(limit);
    if (itx->second.size() == 0)
        m_map_bounders.erase(limit);

    return res;
}

char checker::check(uint ip)
{
    typedef std::map<uint, std::vector<uint>> t_map_pref2;
    t_map_pref2 m_map_pref_tmp;

    std::map<uint, char> tmp_mask;
    uint test = ip;

    auto itb = m_map_bounders.lower_bound(test);
    if (itb == m_map_bounders.end())
        return -1;

    for (auto itxv = itb->second.begin(); itxv != itb->second.end(); ++itxv)
    {
        if (ip <= itxv->first)
        {
            uchar ip_baset[4];
            util::converter_ip(ip, ip_baset);
            uchar ip_basetf[4];
            util::converter_ip(itxv->first, ip_basetf);

            auto itx = m_map_pref.find(itxv->first);
            if (itx == m_map_pref.end())
                continue;

            for (auto it = itx->second.begin(); it != itx->second.end(); ++it)
            {
                if (ip >= it->first)
                {
                    m_map_pref_tmp[itxv->first].push_back(it->first);
                    tmp_mask[itxv->first] = it->second;
                }
            }
        }
    }

    typedef std::map<uint, uint> t_map_pref_tmp2;
    t_map_pref_tmp2 m_map_pref_tmp2;
    t_vec_tmp keys;
    for (auto ity = m_map_pref_tmp.begin(); ity != m_map_pref_tmp.end(); ++ity)
    {
        t_vec_tmp::iterator result = std::min_element(ity->second.begin(), ity->second.end());
        m_map_pref_tmp2.insert({ ity->first, *result });
        keys.push_back(ity->first);
    }
    if (keys.size() == 0 || tmp_mask.size() == 0)
        return -1;
    t_vec_tmp::iterator result = std::max_element(keys.begin(), keys.end());

    auto itz = m_map_pref_tmp2.find(*result);
    if (itz != m_map_pref_tmp2.end())
    {
        return tmp_mask[*result];
    }
    return -1;
}
