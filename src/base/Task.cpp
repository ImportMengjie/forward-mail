//
// Created by mengjie on 5/20/20.
//

#include "Task.h"
using namespace dd;

template<typename... Ts>
std::shared_ptr<Task> Task::create(Ts &&... params) {
    return std::shared_ptr<Task>(std::forward<Ts>(params)...);
}
