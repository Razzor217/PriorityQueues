using namespace bq;

template<class V>
void BucketQueue<V>::_init(int max)
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
void BucketQueue<V>::insert(V element, int key)
{
    buckets[key % (max + 1)].push_back(std::make_pair(element, key));
}

template<class V>
void BucketQueue<V>::decreaseKey(V element, int old, int key)
{
    auto b = buckets[old % (max + 1)];

    // find element in bucket b
    auto it = std::find(b.begin(), b.end(), std::make_pair(element, old));
    assert(it != b.end());

    // erase element with old key
    b.erase(it);

    // insert element with new key
    insert(element, key);
}

template<class V> 
void BucketQueue<V>::deleteMin(V& element, int& key)
{
    if (size())
    {
        // advance until bucket is not empty
        int i;
        for (i = min % (max + 1); i < (max + 1); ++i)
        {
            if (!buckets[i].empty())
            {
                break;
            }
            ++min;
        }

        // remove element with smallest key
        auto p = buckets[i].pop_front();
        element = p.first;
        key = p.second;
    }
}