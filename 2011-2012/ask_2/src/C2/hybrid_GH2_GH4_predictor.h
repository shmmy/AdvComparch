/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : hybrid_GH2_GH4_predictor.h
* Creation Date : 27-05-2012
* Last Modified : Sun 27 May 2012 11:16:25 PM EEST
* Created By : Greg Liras <gregliras@gmail.com>
_._._._._._._._._._._._._._._._._._._._._.*/




#ifndef HYBRID_GH2_GH4_PREDICTOR_H
#define HYBRID_GH2_GH4_PREDICTOR_H

#include "predictor.h"
#include "gshare_predictor.h"
#include "nbit_predictor.h"
#include "hybrid_predictor.h"

class hybrid_GH2_GH4_predictor : public hybrid_predictor
{
public:

	hybrid_GH2_GH4_predictor(int entries);


};


#endif
