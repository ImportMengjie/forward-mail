//
// Created by mengjie on 5/20/20.
//

#ifndef FORWARD_MAIL_PRODUCER_H
#define FORWARD_MAIL_PRODUCER_H

#include <memory>
#include <vector>

#include "Task.h"

namespace dd{

    class Producer {

    public:
        virtual std::vector<std::shared_ptr<Task>> product() = 0;

    };
}


#endif //FORWARD_MAIL_PRODUCER_H
