/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : nt_predictor.h
* Creation Date : 19-05-2012
* Last Modified : Sat 19 May 2012 10:09:02 PM EEST
* Created By : Greg Liras <gregliras@gmail.com>
_._._._._._._._._._._._._._._._._._._._._.*/

// nt_predictor.h

#ifndef NT_PREDICTOR_H
#define NT_PREDICTOR_H
#include "predictor.h"


class nt_update : public branch_update
{
public:
    unsigned int index;
};
class nt_predictor: public branch_predictor
{
    nt_update u;
    branch_update *predict (branch_info & b);
    void update (branch_update *u, bool taken, unsigned int target);
};

#endif
