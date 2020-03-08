set(SOURCES 
    ./main.cpp
)

set(HEADERS
    ./interface/IQueue.h
)

add_executable(priority_queues ${HEADERS} ${SOURCES})