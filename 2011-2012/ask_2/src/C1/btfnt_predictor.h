/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
 * File Name : btfnt_predictor.h
 * Creation Date : 19-05-2012
 * Last Modified : Sat 26 May 2012 06:02:21 PM EEST
 * Created By : Greg Liras <gregliras@gmail.com>
 _._._._._._._._._._._._._._._._._._._._._.*/
// btfnt_predictor.h

#ifndef BTFNT_PREDICTOR_H
#define BTFNT_PREDICTOR_H

#include <math.h>
#include "predictor.h"

class btfnt_predictor : public branch_predictor
{
public:

    branch_update u;
    branch_info bi;
    bool jump;

	void set_target(bool t);
    branch_update *predict (branch_info & b);
    void update (branch_update *u, bool taken, unsigned int target);
};

#endif
