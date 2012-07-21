#ifndef GLOBALHISTORY_PREDICTOR_H
#define GLOBALHISTORY_PREDICTOR_H

#include <cmath>
#include <cstring>
#include <cstdio>
#include "predictor.h"

class globalhistory_update : public branch_update
{
public:
    unsigned int index;
};

class globalhistory_predictor : public branch_predictor 
{ 
public:
				
    globalhistory_update u;
    branch_info bi;
    
	int p_counter_limit;
	int b_counter_limit;
	unsigned int pht_mask;
	
	int pht_entries;
	int pht_nbit;
	
	int bhr;
	int bhr_length;

    unsigned char **pht; 
	
    globalhistory_predictor (int x,int y, int z);
    branch_update *predict (branch_info & b);

    void update (branch_update *u, bool taken, unsigned int target);
};
#endif
