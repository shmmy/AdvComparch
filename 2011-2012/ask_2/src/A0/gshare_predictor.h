// gshare_predictor.h
// This file contains a sample my_predictor class.
// It is a simple 32,768-entry gshare with a history length of 15.

#ifndef GSHARE_PREDICTOR_H
#define GSHARE_PREDICTOR_H

#include "predictor.h"

class gshare_update : public branch_update
{
public:
    unsigned int index;
};

/*
 * H klash gshare_predictor klhronomei thn klash
 * branch_predictor kai kanei override tis me8odous
 * predict kai update
 */

class gshare_predictor : public branch_predictor
{
public:
#define HISTORY_LENGTH	15
#define GSP_TABLE_BITS	15
    gshare_update u;
    branch_info bi;
    unsigned int history;
    unsigned char tab[1<<GSP_TABLE_BITS];

    gshare_predictor (void);
    branch_update *predict (branch_info & b);

    void update (branch_update *u, bool taken, unsigned int target);
};
#endif
