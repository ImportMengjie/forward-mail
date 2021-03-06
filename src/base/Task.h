//
// Created by mengjie on 5/20/20.
//

#ifndef FORWARD_MAIL_TASK_H
#define FORWARD_MAIL_TASK_H
#include <memory>

namespace dd{

    class Task: public std::enable_shared_from_this<Task> {

    public:
        template<typename... Ts>
        static std::shared_ptr<Task> create(Ts&&... params);

        virtual void doit()=0;

    };

}


#endif //FORWARD_MAIL_TASK_H
