#pragma once

#include "../interface/IQueue.h"

#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <cmath>

namespace queue
{
    template<class V>
    using BucketVector = std::vector<std::list<std::pair<V, int>>>;

    template<class V>
    class RadixHeap : public IQueue<V>
    {
    public:
        RadixHeap(int weight);

        int size();

        void insert(V element, int key);

        void decreaseKey(V element, int old, int key);

        void deleteMin(V& element, int& key);

    private:
        int msd(int a, int b);

        BucketVector<V> buckets;
        int max;
        int min;
    };
};

#include "RadixHeap.hpp"