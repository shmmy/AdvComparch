/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
 * File Name : t_predictor.cpp
 * Creation Date : 19-05-2012
 * Last Modified : Sat 19 May 2012 10:16:40 PM EEST
 * Created By : Greg Liras <gregliras@gmail.com>
 _._._._._._._._._._._._._._._._._._._._._.*/

#include "t_predictor.h"


branch_update *t_predictor::predict (branch_info & b)
{
    u.direction_prediction (true);
    u.target_prediction (0);
    return &u;
}

void t_predictor::update (branch_update *u, bool taken, unsigned int target)
{
}

