// btb.h
//
//

#ifndef BTB_H
#define BTB_H

#include <math.h>
#include "predictor.h"

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

    btb_predictor (int btb_lines, int btb_assoc);

    branch_update *predict (branch_info & b);

    void update (branch_update *u, bool taken, unsigned int target);

    void invalidate(int line, int way);
    void update_lru(int line, int way);
    int get_lru(int line);
};
#endif
