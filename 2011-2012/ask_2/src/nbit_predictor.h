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
    nbit_update u;
    branch_info bi;
    int counter_limit;
    int N_COUNTER_LENGTH;
	unsigned int NBP_TABLE_BITS;	/* number of entries = 15 for 32k (2^15) */

    unsigned char *tab;

    nbit_predictor (int length = 2, int nbpbits = 15); /* default values 2bit 2^15 entries */
    branch_update *predict (branch_info & b);
    void update (branch_update *u, bool taken, unsigned int target);
};

#endif
