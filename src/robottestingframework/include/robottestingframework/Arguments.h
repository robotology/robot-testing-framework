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


#ifndef ROBOTTESTINGFRAMEWORK_ARGUMENTS_H
#define ROBOTTESTINGFRAMEWORK_ARGUMENTS_H

namespace robottestingframework {

/**
 * \ingroup key_class
 *
 * \brief A class to implememnt a arguments parser.
 */
class Arguments
{
public:
    /**
     * @brief parse Parses a string paramters into argc, argv format
     * @param azParam Input string parmater
     * @param argc  The parsed argument count
     * @param argv The parsed arguments
     */
    static void parse(char* azParam,
                      int* argc,
                      char** argv);

private:
    /**
     * @brief split Splits a line into arguments
     * @param line A line
     * @param args Splited arguments
     */
    static void split(char* line, char** args);
};

} // robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_ARGUMENTS_H
