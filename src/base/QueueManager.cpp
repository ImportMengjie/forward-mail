//
// Created by mengjie on 5/20/20.
//

#include "QueueManager.h"

void dd::QueueManager::consume() {
    while (live){
        auto data = queue.wait_and_pop();
        data->doit();
    }
}

void dd::QueueManager::start() {
    consume_t = std::thread(&QueueManager::consume, this);
    product_t = std::thread(&QueueManager::product, this);
}

void dd::QueueManager::join() {
    if(consume_t.joinable())
        consume_t.join();
    if(product_t.joinable())
        product_t.join();
}
