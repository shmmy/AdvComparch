#ifndef localhistory_predictor_H
#define localhistory_predictor_H

#include <cmath>
#include "predictor.h"

class localhistory_update : public branch_update
{
public:
    unsigned int phtindex;
    unsigned int bhtindex;
};

class localhistory_predictor : public branch_predictor 
{ 
public:
				
    localhistory_update u;
    branch_info bi;
    
	int p_counter_limit;
	int b_counter_limit;
	
	int pht_entries;
	int pht_nbit;
	
	int bht_entries;
	int bht_entry_length;

    unsigned char *pht; 
    unsigned char *bht;

	unsigned int pht_mask;


    localhistory_predictor (int x,int z);
    branch_update *predict (branch_info & b);

    void update (branch_update *u, bool taken, unsigned int target);
};
#endif
