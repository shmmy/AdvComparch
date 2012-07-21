/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : hybrid_GS_GH2_predictor.cpp
* Creation Date : 27-05-2012
* Last Modified : Sun 27 May 2012 11:12:22 PM EEST
* Created By : Greg Liras <gregliras@gmail.com>
_._._._._._._._._._._._._._._._._._._._._.*/




#include "hybrid_GS_GH2_predictor.h"


hybrid_GS_GH2_predictor::hybrid_GS_GH2_predictor(int entries): hybrid_predictor(entries)
{
	preds[0] = new gshare_predictor();
	preds[1] = new globalhistory_predictor(8192,2,2);
}




