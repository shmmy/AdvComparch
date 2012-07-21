// nbit_predictor.h
//
//

#ifndef N_BIT_PREDICTOR_H
#define N_BIT_PREDICTOR_H


#include <math.h>
#include <string.h>
#include "predictor.h"

class nbit_update : public branch_update
{
public:
    unsigned int index;
};

class nbit_predictor : public branch_predictor
{
public:
#define NBP_TABLE_BITS	13  //number of entries = 2^15
    nbit_update u;
    branch_info bi;
    int counter_limit;
    int N_COUNTER_LENGTH;

    unsigned char tab[1<<NBP_TABLE_BITS];

    nbit_predictor (int length);
    branch_update *predict (branch_info & b);
    void update (branch_update *u, bool taken, unsigned int target);
};

#endif
