//
// Created by mengjie on 5/20/20.
//

#ifndef FORWARD_MAIL_QUEUEMANAGER_H
#define FORWARD_MAIL_QUEUEMANAGER_H

#include <memory>
#include <thread>

#include "queue_s.h"
#include "task.h"

namespace dd{

    class QueueManager {

    private:
        queue_s<std::shared_ptr<task>> queue;

        std::thread product_t;
        std::thread consume_t;

    protected:
        bool live = true;

    public:
        virtual void product()=0;

        virtual void consume();

        void start();

        void join();

    };
}


#endif //FORWARD_MAIL_QUEUEMANAGER_H
