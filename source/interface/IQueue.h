#pragma once

template<class V, class K> 
class IQueue
{
public:
    virtual int size() = 0;

    virtual void insert(V element) = 0;

    virtual void decreaseKey(V element, K key) = 0;

    virtual V deleteMin() = 0;
};