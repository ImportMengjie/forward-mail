//
// Created by mengjie on 5/22/20.
//

#ifndef FORWARD_MAIL_UCISECTION_H
#define FORWARD_MAIL_UCISECTION_H

#include <string>
#include <unordered_map>
#include <vector>

#include "UciItem.h"

namespace dd{

    class UciSection {

    private:
        std::string section_type;
        std::string section_name;

        std::unordered_map<std::string, UciItem> options;
        std::unordered_map<std::string, std::vector<UciItem>> lists;

    };
}


#endif //FORWARD_MAIL_UCISECTION_H
