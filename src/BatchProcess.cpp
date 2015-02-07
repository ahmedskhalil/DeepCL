// Copyright Hugh Perkins 2015 hughperkins at gmail
//
// This Source Code Form is subject to the terms of the Mozilla Public License, 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "GenericLoader.h"

#include "BatchProcess.h"

using namespace std;

template< typename T>
void BatchProcess::run(std::string filepath, int startN, int batchSize, int totalN, BatchAction<T> *batchAction) {
    int numBatches = ( totalN + batchSize - 1 ) / batchSize;
    int thisBatchSize = batchSize;
    for( int batch = 0; batch < numBatches; batch++ ) {
        int batchStart = batch * batchSize;
        if( batch == numBatches - 1 ) {
            thisBatchSize = totalN - batchStart;
            cout << "size of last batch: " << thisBatchSize << endl;
        }
        GenericLoader::load( filepath, batchAction->data, batchAction->labels, batchStart, thisBatchSize );
        batchAction->processBatch( thisBatchSize );
    }
}

template void BatchProcess::run<unsigned char>( std::string filepath, int startN, int batchSize, int totalN, BatchAction<unsigned char> *batchAction);

