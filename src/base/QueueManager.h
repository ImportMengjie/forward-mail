//
// Created by mengjie on 5/20/20.
//

#ifndef FORWARD_MAIL_QUEUEMANAGER_H
#define FORWARD_MAIL_QUEUEMANAGER_H

#include <memory>
#include <thread>
#include <vector>
#include <initializer_list>

#include "Queue_s.h"
#include "Task.h"
#include "Producer.h"

namespace dd{

    class QueueManager {

    private:
        Queue_s<std::shared_ptr<Task>> queue;

        std::vector<std::unique_ptr<Producer>> producers;

        std::vector<std::thread> product_ts;
        std::vector<std::thread> consume_ts;

    protected:
        bool live = true;

    public:

        template<typename InputIterator>
        void addProducer(InputIterator first, InputIterator last);
//        void addProducer(std::initializer_list<std::unique_ptr<Producer>>&& list);
        void addProducer(std::unique_ptr<Producer>& producer);

        template<typename T, typename... Ts>
        void addProducer(Ts&&... params){
            producers.push_back(new T(std::forward<Ts>(params)...));
        }

        virtual void product(int ids);

        virtual void consume();

        bool start(int number_of_consumer_thread_count=1);

        void join();

    };
}


#endif //FORWARD_MAIL_QUEUEMANAGER_H
