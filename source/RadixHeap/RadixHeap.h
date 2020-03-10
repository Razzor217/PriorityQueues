#pragma once

#include "../interface/IQueue.h"

#include <algorithm>
#include <cmath>

namespace queue
{
    template<class V>
    class RadixHeap : public IQueue<V>
    {
    public:
        RadixHeap(int weight);

        int size();

        PairPtr<V> insert(V element, int key);

        void decreaseKey(PairPtr<V> handle, int key);

        PairPtr<V> deleteMin();

    private:
        int msd(int a, int b);

        BucketVector<V> buckets;
        int max;
        int min;
    };
};

#include "RadixHeap.hpp"