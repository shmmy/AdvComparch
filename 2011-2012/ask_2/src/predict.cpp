// predict.cc
// This file contains the main function.  The program accepts a single
// parameter: the name of a trace file.  It drives the branch predictor
// simulation by reading the trace file and feeding the traces one at a time
// to the branch predictor.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include <algorithm>

#include "branch.h"
#include "trace.h"
#include "predictor.h"
#include "nbit_predictor.h"		//the .h files of the branch predictors' implementations
#include "gshare_predictor.h"
#include "btb.h"


#define NR_PREDICTORS 7

using namespace std;

int main (int argc, char *argv[])
{

    // make sure there is one parameter

    if (argc != 2) {
        fprintf (stderr, "Usage: %s <filename>.gz\n", argv[0]);
        exit (1);
    }

    // open the trace file for reading

    init_trace (argv[1]);

    // initialize competitor's branch prediction code

    // you can use more than one predictor in an array of predictors!!!

    branch_predictor **p = new branch_predictor*[NR_PREDICTORS];

    for ( int i = 0 ; i < NR_PREDICTORS ; ++i ) {
        p[i] = new gshare_predictor();
    }
    // some statistics to keep, currently just for conditional branches

    long long int
    tmiss[NR_PREDICTORS],	// number of target mispredictions
          dmiss[NR_PREDICTORS]; 	// number of direction mispredictions

    fill( tmiss, tmiss+NR_PREDICTORS, 0);
    fill( dmiss, dmiss+NR_PREDICTORS, 0);
    //for(int i = 0; i < 2; i++)
    //	dmiss[i] = tmiss[i] = 0;
    //// keep looping until end of file

    for (;;) {

        // get a trace

        trace *t = read_trace ();

        // NULL means end of file

        if (!t) break;

        // send this trace to the competitor's code for prediction

        branch_update *u;

        for(int i = 0; i < NR_PREDICTORS; i++) {
            u = p[i]->predict(t->bi);
            dmiss[i] += u->direction_prediction() != t->taken;
            p[i]->update(u, t->taken, t->target);
        }

        //u = p[1]->predict(t->bi);
        //if (!(t->bi.br_flags & BR_RETURN)) {
        //	dmiss[1] += u->direction_prediction() != t->taken;
        //	if((t->taken == u->direction_prediction()) && (u->direction_prediction() ==true)) {
        //		tmiss[1] += u->target_prediction() != t->target;
        //	}
        //}
        //p[1]->update(u, t->taken, t->target);
    }

    // done reading traces

    end_trace ();

    // give final mispredictions per kilo-instruction and exit.
    // each trace represents exactly 100 million instructions.

    for(int i = 0; i < NR_PREDICTORS; i++) {
        printf("%d\t%0.3f\n",i+1,1000.0 * (dmiss[i]/1e8));
        delete p[i];
    }
    delete [] p;

    exit (0);
}
