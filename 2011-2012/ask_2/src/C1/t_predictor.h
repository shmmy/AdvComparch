/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
 * File Name : t_predictor.h
 * Creation Date : 19-05-2012
 * Last Modified : Sat 19 May 2012 10:17:10 PM EEST
 * Created By : Greg Liras <gregliras@gmail.com>
 _._._._._._._._._._._._._._._._._._._._._.*/

// t_predictor.h
#ifndef T_PREDICTOR_H
#define T_PREDICTOR_H
#include "predictor.h"

class t_update : public branch_update
{
public:
    unsigned int index;
};
class t_predictor: public branch_predictor
{

    t_update u;
    branch_update *predict (branch_info & b);
    void update (branch_update *u, bool taken, unsigned int target);
};

#endif
