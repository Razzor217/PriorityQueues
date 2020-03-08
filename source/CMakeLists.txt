set(SOURCES 
    ./main.cpp
)

set(HEADERS
    ./interface/IQueue.h

    ./BucketQueue/BucketQueue.h
    ./BucketQueue/BucketQueue.hpp

    ./RadixHeap/RadixHeap.h
    ./RadixHeap/RadixHeap.hpp
)

add_executable(priority_queues ${HEADERS} ${SOURCES})