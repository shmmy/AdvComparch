// gshare_predictor.h
// This file contains a sample my_predictor class.
// It is a simple 32,768-entry gshare with a history length of 15.

#ifndef GSHARE_PREDICTOR_H
#define GSHARE_PREDICTOR_H
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

    gshare_predictor (void) : history(0) {
        memset (tab, 0, sizeof (tab));
    }

    branch_update *predict (branch_info & b) {
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

    void update (branch_update *u, bool taken, unsigned int target) {
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
};
#endif
