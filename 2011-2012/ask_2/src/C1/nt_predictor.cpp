/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
 * File Name : nt_predictor.cpp
 * Creation Date : 19-05-2012
 * Last Modified : Sat 19 May 2012 10:07:46 PM EEST
 * Created By : Greg Liras <gregliras@gmail.com>
 _._._._._._._._._._._._._._._._._._._._._.*/

#include "nt_predictor.h"

branch_update *nt_predictor::predict (branch_info & b)
{
    if (b.br_flags & BR_CONDITIONAL) {
        u.direction_prediction (false);
    } else {
        u.direction_prediction (true);
    }
    u.target_prediction (0);
    return &u;
}
void nt_predictor::update (branch_update *u, bool taken, unsigned int target)
{
}
