#include "nbit_predictor.h"

nbit_predictor::nbit_predictor (int length, int nbpbits)
{
	N_COUNTER_LENGTH = length;
	NBP_TABLE_BITS = nbpbits;
    tab = new unsigned char[1<<NBP_TABLE_BITS];
    memset (tab, 0, sizeof (tab));
    counter_limit = ((int) pow(2.0, N_COUNTER_LENGTH)) - 1;
}

branch_update *nbit_predictor::predict (branch_info & b)
{
    bi = b;
    if (b.br_flags & BR_CONDITIONAL) {
        u.index =  (b.address & ((1<<NBP_TABLE_BITS)-1));
        u.direction_prediction (tab[u.index] >> (N_COUNTER_LENGTH-1));
    } else {
        u.direction_prediction (true);
    }
    u.target_prediction (0);
    return &u;
}

void nbit_predictor::update (branch_update *u, bool taken, unsigned int target)
{
    if (bi.br_flags & BR_CONDITIONAL) {
        unsigned char *c = &tab[((nbit_update*)u)->index];
        if (taken) {
            if (*c < counter_limit) (*c)++;
        } else {
            if (*c > 0) (*c)--;
        }
    }
}
