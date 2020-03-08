#pragma once

#include "../interface/IQueue.h"

#include <memory>
#include <vector>
#include <list>
#include <utility>

namespace bq
{
    template<class V>
    using BucketVector = std::vector<std::list<std::pair<V, int>>>;

    template<class V>
    class BucketQueue : public IQueue<V>
    {
    public:
        BucketQueue(int max)
        {
            _init(max);
        }

        int size();

        void insert(V element, int key);

        void decreaseKey(V element, int old, int key);

        void deleteMin(V& element, int& key);

    private:
        void _init(int max);

        BucketVector<V> buckets;
        int max;
        int min;
    };
};

#include "BucketQueue.hpp"