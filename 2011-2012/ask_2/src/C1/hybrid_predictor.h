/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* File Name : hybrid_predictor.h
* Creation Date : 27-05-2012
* Last Modified : Sun 27 May 2012 04:44:35 AM EEST
* Created By : Greg Liras <gregliras@gmail.com>
_._._._._._._._._._._._._._._._._._._._._.*/

#ifndef HYBRID_PREDICTOR_H
#define HYBRID_PREDICTOR_H

#include "predictor.h"
#include "globalhistory_predictor.h"

class hybrid_update : public branch_update
{
public:
	globalhistory_update *ups[2];
	int index;
	int pred;

};
class hybrid_predictor : public branch_predictor
{
public:

	hybrid_update u;
	branch_info bi;
	int counter_limit;

	branch_predictor **preds;
	

	int pht_entries;
	int pht_bits_length;

	unsigned char *tab;

	hybrid_predictor(int entries);
    branch_update *predict (branch_info & b);
    void update (branch_update *u, bool taken, unsigned int target);




};


#endif
