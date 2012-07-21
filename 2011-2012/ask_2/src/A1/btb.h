// btb.h
//
//

#ifndef BTB_H
#define BTB_H

#include <math.h>

class btb_update : public branch_update
{
public:
    unsigned int index;
    unsigned int branch_address;
    int way;
};

class btb_predictor : public branch_predictor
{
public:
    btb_update u;
    branch_info bi;

    int table_lines;
    int table_assoc;
    int PC_BITS;

    unsigned int ** btb_table;
    int **btb_table_lru;

    btb_predictor (int btb_lines, int btb_assoc) : table_lines(btb_lines),table_assoc(btb_assoc) {
        PC_BITS = (int) (log(table_lines)/log(2));

        btb_table = new unsigned int*[table_lines];
        btb_table_lru = new int*[table_lines];
        for(int i = 0; i < table_lines; i++) {
            btb_table[i] = new unsigned int[table_assoc * 2];
            btb_table_lru[i] = new int[table_assoc];
            for(int j = 0; j < table_assoc; j++) {
                btb_table_lru[i][j] = j;
                btb_table[i][2*j] = btb_table[i][2*j+1] = 0;
            }
        }
    }

    branch_update *predict (branch_info & b) {
        bi = b;
        /*
         * H ulopoihsh auth tou BTB agnoei ta returns.
         */

        if (!(b.br_flags & BR_RETURN)) {
            u.index =  (b.address & ((1<<PC_BITS)-1));
            u.way = -1;
            for(int i = 0; i < table_assoc; i++) {
                if (btb_table[u.index][i * 2] == b.address)  {//entry present in BTB
                    u.direction_prediction(true);
                    u.target_prediction(btb_table[u.index][(i * 2)+1]);
                    u.way = i;
                    u.branch_address = b.address;
                    return &u;
                }
            }
            if (u.way == -1)	{
                u.direction_prediction(false);
                u.target_prediction(0);
            }
            u.branch_address = b.address;
        } else {
            u.direction_prediction (true);
            u.target_prediction(0);
        }
        return &u;
    }

    void update (branch_update *u, bool taken, unsigned int target) {
        if (!(bi.br_flags & BR_RETURN)) {
            if (((btb_update*)u)->way != -1) {
                if (taken) {
                    btb_table[((btb_update*)u)->index][2 * ((btb_update*)u)->way] = ((btb_update*)u)->branch_address;
                    btb_table[((btb_update*)u)->index][(2 * (((btb_update*)u)->way))+1] = target;
                    update_lru(((btb_update*)u)->index, ((btb_update*)u)->way);
                } else {
                    btb_table[((btb_update*)u)->index][2 * ((btb_update*)u)->way] = 0;
                    btb_table[((btb_update*)u)->index][(2 * (((btb_update*)u)->way))+1] = 0;
                    invalidate(((btb_update*)u)->index, (((btb_update*)u)->way));
                }
            } else {
                if(taken) {
                    int sel_way = get_lru(((btb_update*)u)->index);
                    btb_table[((btb_update*)u)->index][sel_way * 2] = ((btb_update*)u)->branch_address;
                    btb_table[((btb_update*)u)->index][(sel_way * 2) + 1] = target;
                    update_lru(((btb_update*)u)->index, sel_way);
                }
            }
        }
    }

    void invalidate(int line, int way) {
        btb_table_lru[line][way] = -1;
    }

    void update_lru(int line, int way) {
        for(int i = 0; i < table_assoc; i++) {
            if((i != way) && (btb_table_lru[line][i] > btb_table_lru[line][way]) && (btb_table_lru[line][i] >0))
                btb_table_lru[line][i] -= 1;
        }
        btb_table_lru[line][way] = table_assoc - 1;
    }

    int get_lru(int line) {
        for(int i = 0; i < table_assoc; i++)
            if(btb_table_lru[line][i] == -1)
                return i;

        for(int i = 0; i < table_assoc; i++)
            if(btb_table_lru[line][i] == 0)
                return i;

        return -1;
    }
};
#endif
