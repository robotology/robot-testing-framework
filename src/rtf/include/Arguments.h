// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_ARGUMENTS_H
#define _RTF_ARGUMENTS_H


namespace RTF {
    class Arguments;
}


/**
 * \ingroup key_class
 *
 * \brief A class to implememnt a arguments parser.
 */
class RTF::Arguments {
public:
    /**
     * @brief parse Parses a string paramters into argc, argv format
     * @param azParam Input string parmater
     * @param argc  The parsed argument count
     * @param argv The parsed arguments
     */
    static void parse(char *azParam,
                      int *argc, char **argv);

private:
    /**
     * @brief split Splits a line into arguments
     * @param line A line
     * @param args Splited arguments
     */
    static void split(char *line, char **args);

};
#endif // _RTF_ARGUMENTS_H
