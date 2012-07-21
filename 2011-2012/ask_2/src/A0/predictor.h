// predictor.h
// This file declares branch_update and branch_predictor classes.

#ifndef PREDICTOR_H
#define PREDICTOR_H

#include "branch.h"

class branch_update
{
    bool _direction_prediction; // H problepsh gia to apotelesma tou branch
    unsigned int _target_prediction; // H problepsh gia to target tou branch

public:
    bool direction_prediction () {
        return _direction_prediction;
    }
    void direction_prediction (bool b) {
        _direction_prediction = b;
    }

    unsigned int target_prediction () {
        return _target_prediction;
    }
    void target_prediction (unsigned int t) {
        _target_prediction = t;
    }


    branch_update (void) :
        _direction_prediction(false), _target_prediction(0) {}
};

class branch_predictor
{
public:

    /*
     * Oi me8odoi autoi ginontai overriden apo ton ka8e predictor
     * 3exwrista, epitrepontas etsi diaforetikes ulopoihseis, oi
     * opoies omws kalountai me ton idio tropo.
     */

    virtual branch_update *predict (branch_info &) = 0;
    virtual void update (branch_update *, bool, unsigned int) {}
    virtual ~branch_predictor (void) {}
};

#endif
