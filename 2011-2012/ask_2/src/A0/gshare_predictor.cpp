/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : gshare_predictor.cpp
* Creation Date : 20-05-2012
* Last Modified : Sun 20 May 2012 03:34:58 PM EEST
* Created By : Greg Liras <gregliras@gmail.com>
_._._._._._._._._._._._._._._._._._._._._.*/

#include "gshare_predictor.h"
#include <algorithm>
gshare_predictor::gshare_predictor (void) : history(0)
{
    std::fill (tab, tab+sizeof (tab),0);
}
branch_update *gshare_predictor::predict (branch_info & b)
{
    bi = b;

    /*
     * O gshare xrhsimopoieitai mono gia conditional branches.
     * Ta uncoditional ginontai predicted panta TAKEN
     */

    if (b.br_flags & BR_CONDITIONAL) {
        u.index =
            (history << (GSP_TABLE_BITS - HISTORY_LENGTH))
            ^ (b.address & ((1<<GSP_TABLE_BITS)-1));
        u.direction_prediction (tab[u.index] >> 1);
    } else {
        u.direction_prediction (true);
    }

    // O gshare den kanei target prediction, gia auto to 8etoume sto 0.

    u.target_prediction (0);
    return &u;
}
void gshare_predictor::update (branch_update *u, bool taken, unsigned int target)
{
    //O gshare xrhsimopoieitai mono gia conditional branches
    if (bi.br_flags & BR_CONDITIONAL) {
        unsigned char *c = &tab[((gshare_update*)u)->index];
        if (taken) {
            if (*c < 3) (*c)++;
        } else {
            if (*c > 0) (*c)--;
        }
        history <<= 1;
        history |= taken;
        history &= (1<<HISTORY_LENGTH)-1;
    }
}

