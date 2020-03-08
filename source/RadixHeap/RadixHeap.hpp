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
void RadixHeap<V>::insert(V element, int key)
{
    // compute bucket and insert element with key
    int d = msd(min, key);
    if (d)
    {
        buckets[std::min(d, max) + 1].push_back(std::make_pair(element, key));
    }
    else
    {
        buckets[0].push_back(std::make_pair(element, key));
    }
}

template<class V>
void RadixHeap<V>::decreaseKey(V element, int old, int key)
{
    // compute old bucket
    int d = msd(min, key);
    int b = 0;
    
    if (d)
    {
        b = std::min(d, max) + 1;
    }

    // find element in old bucket
    auto it = std::find(buckets[b].begin(), 
                        buckets[b].end(), 
                        std::make_pair(element, old));
    assert(it  != buckets[b].end());

    // remove element from old bucket
    buckets[b].erase(it);

    // insert element into new bucket
    insert(element, key);
}

template<class V>
void RadixHeap<V>::deleteMin(V& element, int& key)
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
            [] (std::pair<V, int> a, std::pair<V, int> b) 
            { 
                return a.second < b.second; 
            });

        // move element to bucket 0
        buckets[i].erase(it);
        buckets[0].push_back(*it);

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
    auto result = buckets[0].pop_front();
    element = result.first;
    key = result.second;
}

template<class V>
int RadixHeap<V>::msd(int a, int b)
{
    return static_cast<int>(std::floor(std::log(a ^ b)));
}