//
// Created by mengjie on 5/22/20.
//

#ifndef FORWARD_MAIL_UCIPACKAGE_H
#define FORWARD_MAIL_UCIPACKAGE_H

#include <string>
#include <unordered_map>
#include <vector>

#include "UciItem.h"
#include "UciSection.h"

namespace dd{

    class UciPackage {

    private:
        std::string config_data;
        std::vector<std::string> list_config_data;
        std::vector<UciItem> list_config_items;
        std::vector<UciSection> list_config_sections;

    public:

        UciPackage() = default;

        UciPackage(std::string config_data);


    };
}



#endif //FORWARD_MAIL_UCIPACKAGE_H
