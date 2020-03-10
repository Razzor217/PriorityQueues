using namespace queue;

template<class V>
RadixHeap<V>::RadixHeap(int weight)
{
    max = 1 + static_cast<int>(std::floor(std::log(weight)));
    min = 0;
    buckets.resize(max + 2);
}

template<class V>
int RadixHeap<V>::size()
{
    int count = 0;
    for (auto b : buckets)
    {
        count += b.size();
    }

    return count;
}

template<class V>
PairPtr<V> RadixHeap<V>::insert(V element, int key)
{
    auto handle = std::make_shared<std::pair<V, int>>(element, key);

    // compute bucket and insert element with key
    int d = msd(min, key);
    if (d)
    {
        buckets[std::min(d, max) + 1].push_back(handle);
    }
    else
    {
        buckets[0].push_back(handle);
    }

    return handle;
}

template<class V>
void RadixHeap<V>::decreaseKey(PairPtr<V> handle, int key)
{
    // compute old bucket
    int d = msd(min, handle->second);
    int b = 0;
    
    if (d)
    {
        b = std::min(d, max) + 1;
    }

    // find element in old bucket
    auto it = std::find(buckets[b].begin(), buckets[b].end(), handle);
    assert(it  != buckets[b].end());

    // remove element from old bucket
    buckets[b].erase(it);

    // insert element into new bucket
    handle = insert(handle->first, key);
}

template<class V>
PairPtr<V> RadixHeap<V>::deleteMin()
{
    if (buckets[0].empty)
    {
        // find smallest non-empty bucket
        int i;
        for (i = 1; i < max + 2; ++i)
        {
            if (!buckets[i].empty())
            {
                break;
            }
        }

        // retreive smallest element of bucket i 
        auto it = std::min_element(buckets[i].begin(), buckets[i].end(), 
            [] (PairPtr<V> a, PairPtr<V> b) 
            { 
                return a->second < b->second; 
            });

        int minKey = it->second;

        do 
        {
            // move smallest element in bucket i to bucket 0
            buckets[0].push_back(*it);
            buckets[i].erase(it);

            it = std::find_if(buckets[i].begin(), buckets[i].end(),
                [] (PairPtr<V> handle)
                {
                    return handle->second == minKey;
                });
        }
        while (it != buckets[i].end());

        // update min
        min = it->second;

        std::list<std::pair<V, int>> temp(buckets[i].begin(), buckets[i].end());
        buckets[i].clear();

        // Reorder heap
        for (auto e : temp)
        {
            insert(e.first, e.second);
        }
    }

    // delete minimum element
    return buckets[0].pop_front();
}

template<class V>
int RadixHeap<V>::msd(int a, int b)
{
    return static_cast<int>(std::floor(std::log(a ^ b)));
}