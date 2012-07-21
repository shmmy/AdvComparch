// predict.cpp
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
#include "globalhistory_predictor.h"

#include "hybrid_predictor.h"
#include "hybrid_2bit_GH2_predictor.h"
#include "hybrid_2bit_GH4_predictor.h"
#include "hybrid_2bit_GS_predictor.h"
#include "hybrid_GS_GH2_predictor.h"
#include "hybrid_GS_GH4_predictor.h"
#include "hybrid_GH2_GH4_predictor.h"


#define NR_PREDICTORS 6

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

    p[0] = new hybrid_2bit_GS_predictor(512);
    p[1] = new hybrid_2bit_GH2_predictor(512);
    p[2] = new hybrid_2bit_GH4_predictor(512);
    p[3] = new hybrid_GS_GH2_predictor(512);
    p[4] = new hybrid_GS_GH4_predictor(512);
    p[5] = new hybrid_GH2_GH4_predictor(512);

    long long int
    tmiss[NR_PREDICTORS],	// number of target mispredictions
          dmiss[NR_PREDICTORS]; 	// number of direction mispredictions

    fill( tmiss, tmiss+NR_PREDICTORS, 0);
    fill( dmiss, dmiss+NR_PREDICTORS, 0);
    // keep looping until end of file

    for (;;) {

        // get a trace

        trace *t = read_trace ();

        // NULL means end of file

        if (!t) break;

        // send this trace to the competitor's code for prediction

        branch_update *u;

		/* static not taken */
        u = p[0]->predict(t->bi);
        p[0]->update(u, t->taken, t->target);
        dmiss[0] += u->direction_prediction() != t->taken;
        tmiss[0] += u->target_prediction() != t->target;


		/* 4 bit predictor */
        u = p[1]->predict(t->bi);
        p[1]->update(u, t->taken, t->target);
        dmiss[1] += u->direction_prediction() != t->taken;
        tmiss[1] += u->target_prediction() != t->target;

		/* 4 bit predictor */
        u = p[2]->predict(t->bi);
        p[2]->update(u, t->taken, t->target);
        dmiss[2] += u->direction_prediction() != t->taken;
        tmiss[2] += u->target_prediction() != t->target;

		/* gshare predictor */
        u = p[3]->predict(t->bi);
        p[3]->update(u, t->taken, t->target);
        dmiss[3] += u->direction_prediction() != t->taken;
        tmiss[3] += u->target_prediction() != t->target;

		/* local history 2 level predictor X=2048 */
        u = p[4]->predict(t->bi);
        p[4]->update(u, t->taken, t->target);
        dmiss[4] += u->direction_prediction() != t->taken;
        tmiss[4] += u->target_prediction() != t->target;

		/* local history 2 level predictor X=4096 */
        u = p[5]->predict(t->bi);
        p[5]->update(u, t->taken, t->target);
        dmiss[5] += u->direction_prediction() != t->taken;
        tmiss[5] += u->target_prediction() != t->target;
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
