using namespace queue;

template<class V>
BucketQueue<V>::BucketQueue(int max)
{
    this->max = max;
    min = 0;
    buckets.resize(max + 1);
}

template<class V> 
int BucketQueue<V>::size()
{
    int count = 0;

    for (auto b : buckets)
    {
        count += b->size();
    }

    return count;
}

template<class V>
PairPtr<V> BucketQueue<V>::insert(V element, int key)
{
    auto handle = std::make_shared<std::pair<V, int>>(element, key);

    buckets[key % (max + 1)].push_back(handle);

    return handle;
}

template<class V>
void BucketQueue<V>::decreaseKey(PairPtr<V> handle, int key)
{
    auto b = buckets[handle->second % (max + 1)];

    // find element in bucket b
    auto it = std::find(b.begin(), b.end(), handle);
    assert(it != b.end());

    // erase element with old key
    b.erase(it);

    // insert element with new key
    handle = insert(handle->first, key);
}

template<class V> 
PairPtr<V> BucketQueue<V>::deleteMin()
{
    if (size())
    {
        auto it = buckets.begin();
        std::advance(it, min % (max + 1));

        // advance until bucket is not empty
        while(it->empty())
        {
            // cycle through buckets
            if (it == buckets.end())
            {
                it = buckets.begin();
            }
            else
            {
                ++it;
                ++min;
            }
        }

        // remove element with smallest key
        return buckets[min % (max + 1)].pop_front();
    }

    return NULL;
}