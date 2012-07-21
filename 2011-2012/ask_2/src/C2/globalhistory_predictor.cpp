#include "globalhistory_predictor.h"
#include <algorithm>

globalhistory_predictor::globalhistory_predictor (int x , int y, int z) :pht_entries(x), pht_nbit(y), bhr_length(z)
{

	bhr=0;
	
	pht = new unsigned char *[1<<bhr_length]; 
	
	for( int i = 0; i < (1<<bhr_length); i++)
	{
		pht[i] = new unsigned char [pht_entries>>bhr_length]; 
	}
	
	for (int i = 0; i < (1<<bhr_length); i++)
	{
		memset(pht[i], 0, sizeof (pht[i])); 
	}	
	
	p_counter_limit = (1<<pht_nbit); 
	b_counter_limit = (1<<bhr_length);
	pht_mask = ((pht_entries>>bhr_length)-1);
}

branch_update *globalhistory_predictor::predict (branch_info & b)
{
	bi=b;
	if (b.br_flags & BR_CONDITIONAL) {
			
		u.index = (b.address & pht_mask);
		
		u.direction_prediction(pht[bhr][u.index]>>(pht_nbit-1));
	} else {
		u.direction_prediction (true);
	}
	u.target_prediction (0); 
	return &u;
}

void globalhistory_predictor::update (branch_update *u, bool taken, unsigned int target)
{
    if (bi.br_flags & BR_CONDITIONAL) {
		
		unsigned char *c = &pht[bhr][((globalhistory_update*)u)->index]; 
		
		if (taken) {
			if (*c < p_counter_limit) 
				(*c)++;
		} 
		else {
			if (*c > 0)
				(*c)--;
		}
		bhr <<= 1;
		bhr |= taken;
		bhr &= b_counter_limit;

	}
}

