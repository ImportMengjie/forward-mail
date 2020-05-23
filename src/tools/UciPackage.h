//
// Created by mengjie on 5/22/20.
//

#ifndef FORWARD_MAIL_UCIPACKAGE_H
#define FORWARD_MAIL_UCIPACKAGE_H

#include <string>
#include <unordered_map>

#include "UciItem.h"
#include "UciSection.h"

namespace dd{

    class UciPackage {

    private:
        std::unordered_map<std::string, UciSection> map_name_sections;

        std::string name;

        void init(const std::vector<UciItem>& items);

    public:

        UciPackage() = default;

        explicit UciPackage(const std::string& config_path);

        explicit UciPackage(const std::vector<UciItem>& items);

    };
}



#endif //FORWARD_MAIL_UCIPACKAGE_H
