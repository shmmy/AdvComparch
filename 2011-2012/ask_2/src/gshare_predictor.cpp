#include "gshare_predictor.h"
#include <cstring>

gshare_predictor::gshare_predictor (int hist_length)
{
	history = 0;
	history_length = hist_length;
	memset(tab, 0, sizeof tab);
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
            (history << (GSP_TABLE_BITS - history_length))
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
        history &= (1<<history_length)-1;
    }
}

