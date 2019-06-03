/*
 * Robot Testing Framework
 *
 * Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef ROBOTTESTINGFRAMEWORK_VOCAB_H
#define ROBOTTESTINGFRAMEWORK_VOCAB_H

#include <string>

namespace shlibpp {
class Vocab;

// We need a macro for efficient switching.
constexpr int32_t VOCAB(char a, char b = 0, char c = 0, char d = 0)
{
    return ((((int32_t)(d)) << 24) + (((int32_t)(c)) << 16) + (((int32_t)(b)) << 8) + ((int32_t)(a)));
}
}


class shlibpp::Vocab
{
public:
    static int encode(const std::string& s)
    {
        char a = '\0';
        char b = '\0';
        char c = '\0';
        char d = '\0';
        if (s.length() >= 1) {
            a = s[0];
            if (s.length() >= 2) {
                b = s[1];
                if (s.length() >= 3) {
                    c = s[2];
                    if (s.length() >= 4) {
                        d = s[3];
                    }
                }
            }
        }
        return VOCAB(a, b, c, d);
    }


    static std::string decode(int code)
    {
        std::string s;
        for (int i = 0; i < 4; i++) {
            int ch = code % 256;
            if (ch > 0) {
                s += ((char)ch);
            }
            code /= 256;
        }
        return s;
    }
};

#endif // ROBOTTESTINGFRAMEWORK_VOCAB_H
