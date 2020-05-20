//
// Created by mengjie on 5/20/20.
//

#ifndef FORWARD_MAIL_PRODUCER_H
#define FORWARD_MAIL_PRODUCER_H

#include <memory>
#include <vector>

#include "task.h"

namespace dd{

    class producer {

    public:
        virtual std::vector<std::shared_ptr<task>> product() = 0;

    };
}


#endif //FORWARD_MAIL_PRODUCER_H
