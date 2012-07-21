#include "localhistory_predictor.h"
#include <algorithm>
#include <cstring>

localhistory_predictor::localhistory_predictor (int x , int z) : bht_entries(x), bht_entry_length(z)
{
	pht_entries=8192;
	pht_nbit=2;
	
	pht = new unsigned char [pht_entries]; 
	memset (pht, 0, sizeof (pht));
	
	bht = new unsigned char [x]; 
	memset (bht, 0, sizeof (bht));

	pht_mask = ((1<<(((int) log2(pht_entries))-bht_entry_length))-1);

	p_counter_limit = (1<<pht_nbit);
	b_counter_limit = (1<<bht_entry_length); 
}

branch_update *localhistory_predictor::predict (branch_info & b)
{
	bi=b;
	if (b.br_flags & BR_CONDITIONAL) {
	
		u.bhtindex = (b.address & (bht_entries-1));
		u.phtindex = ((b.address & pht_mask)<<bht_entry_length);
		u.phtindex |= bht[u.bhtindex];

		u.direction_prediction(pht[u.phtindex]>>(pht_nbit-1));
	} else {
		u.direction_prediction(true);
	}
	u.target_prediction (0); 
	return &u;
}

void localhistory_predictor::update (branch_update *u, bool taken, unsigned int target)
{
    if (bi.br_flags & BR_CONDITIONAL) {
		
		unsigned char *c = &pht[((localhistory_update*)u)->phtindex]; 
		unsigned char *d = &bht[((localhistory_update*)u)->bhtindex];
		
		if (taken) {
			if (*c < p_counter_limit) 
				(*c)++;
		} 
		else {
			if (*c > 0) 
				(*c)--;
		}
		(*d) <<= 1;
		(*d) |= taken;
		(*d) &= b_counter_limit;


	}
}

