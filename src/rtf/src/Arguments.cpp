// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <rtf/Arguments.h>

#include <string.h>

#define C_MAXARGS           128         // max number of the command parametes

using namespace RTF;

void Arguments::split(char *line, char **args)
{
     char *pTmp = strchr(line, ' ');

    if (pTmp) {
        *pTmp = '\0';
        pTmp++;
        while ((*pTmp) && (*pTmp == ' ')) {
            pTmp++;
        }
        if (*pTmp == '\0') {
            pTmp = NULL;
        }
    }
    *args = pTmp;
}

void Arguments::parse(char *azParam ,
                      int *argc, char **argv)
{
    char *pNext = azParam;
    size_t i;
    int j;
    int quoted = 0;
    size_t len = strlen(azParam);

    // Protect spaces inside quotes, but lose the quotes
    for(i = 0; i < len; i++) {
        if ((!quoted) && ('"' == azParam [i])) {
            quoted = 1;
            azParam [i] = ' ';
        } else if ((quoted) && ('"' == azParam [i])) {
            quoted = 0;
            azParam [i] = ' ';
        } else if ((quoted) && (' ' == azParam [i])) {
            azParam [i] = '\1';
        }
    }

    // init
    memset(argv, 0x00, sizeof(char*) * C_MAXARGS);
    *argc = 1;
    argv[0] = azParam ;

    while ((NULL != pNext) && (*argc < C_MAXARGS)) {
        split(pNext, &(argv[*argc]));
        pNext = argv[*argc];

        if (NULL != argv[*argc]) {
            *argc += 1;
        }
    }

    for(j = 0; j < *argc; j++) {
        len = strlen(argv[j]);
        for(i = 0; i < len; i++) {
            if('\1' == argv[j][i]) {
                argv[j][i] = ' ';
            }
        }
    }
}
