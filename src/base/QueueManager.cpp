//
// Created by mengjie on 5/20/20.
//

#include "QueueManager.h"

#ifdef DD_VERBOSE
#include <iostream>
#endif

void dd::QueueManager::consume() {
    while (live||!queue.empty()){
        auto data = queue.wait_and_pop();
        data->doit();
    }
}


void dd::QueueManager::join() {
    for(std::thread& t:product_ts)
        if(t.joinable())
            t.join();
    live = false;
    for(std::thread& t:consume_ts)
        if(t.joinable())
            t.join();
}

template<typename InputIterator>
void dd::QueueManager::addProducer(InputIterator first, InputIterator last) {
    for(auto itor=first;itor!=last;++itor){
        this->producers.push_back(std::move(*itor));
    }

}

//void dd::QueueManager::addProducer(std::initializer_list<std::unique_ptr<Producer>>&& list) {
////    addProducer(list.begin(), list.end());
//    for(const auto & it : list)
//        this->producers.push_back(std::move(it));
//
//}

void dd::QueueManager::addProducer(std::unique_ptr<Producer> &producer) {
    this->producers.push_back(std::move(producer));
}


void dd::QueueManager::product(int ids, int interval_seconds) {
    if(producers.size()>ids){
        while (true){
            auto tasks = producers[ids]->product();
#ifdef DD_VERBOSE
            std::cout<<"get task num: "<<tasks.size()<<std::endl;
#endif
            for(auto& task: tasks)
                queue.push(task);
            std::this_thread::sleep_for(std::chrono::seconds(interval_seconds));
        }
    }
}

bool dd::QueueManager::start(int number_of_consumer_thread_count, int interval_product_seconds) {
    if(!producers.empty()&&number_of_consumer_thread_count>0){
        product_ts.clear();
        consume_ts.clear();
        for(int i=0;i<producers.size();i++)
            product_ts.emplace_back(&QueueManager::product,this,i, interval_product_seconds);
        for(int i=0;i<number_of_consumer_thread_count;i++)
            consume_ts.emplace_back(&QueueManager::consume, this);
        return true;
    }
    return false;
    return false;
}
