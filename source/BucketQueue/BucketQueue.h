#pragma once

#include "../interface/IQueue.h"

namespace queue
{
    template<class V>
    class BucketQueue : public IQueue<V>
    {
    public:
        BucketQueue(int max);

        int size();

        PairPtr<V> insert(V element, int key);

        void decreaseKey(PairPtr<V> handle, int key);

        PairPtr<V> deleteMin();

    private:
        BucketVector<V> buckets;
        int max;
        int min;
    };
};

#include "BucketQueue.hpp"