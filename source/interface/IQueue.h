#pragma once

template<class V> 
class IQueue
{
public:
    virtual int size() = 0;

    virtual void insert(V element, int key) = 0;

    virtual void decreaseKey(V element, int old, int key) = 0;

    virtual void deleteMin(V& element, int& key) = 0;
};