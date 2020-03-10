#pragma once

#include <vector>
#include <list>
#include <memory>
#include <utility>

template<class V>
using PairPtr = std::shared_ptr<std::pair<V, int>>;

template<class V>
using BucketVector = std::vector<std::list<PairPtr<V>>>;

template<class V> 
class IQueue
{
public:
    virtual int size() = 0;

    virtual PairPtr<V> insert(V element, int key) = 0;

    virtual void decreaseKey(PairPtr<V> handle, int key) = 0;

    virtual PairPtr<V> deleteMin() = 0;
};