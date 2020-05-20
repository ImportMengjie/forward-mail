//
// Created by mengjie on 5/20/20.
//

#include "task.h"
using namespace dd;

template<typename... Ts>
std::shared_ptr<task> task::create(Ts &&... params) {
    return std::shared_ptr<task>();
}
