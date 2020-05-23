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
        UciItem section;

        std::unordered_map<std::string, UciItem> options;
        std::unordered_map<std::string, std::vector<UciItem>> lists;

    public:
        UciSection(const std::string& section_name, const std::string& section_value, const std::vector<UciItem>& items);

        UciSection(const std::string& section_name, const std::string& section_value);

        UciSection()=default;

        UciSection(const UciSection& section)=default;

        void add_item(const UciItem& item);

        void add_items(const std::vector<UciItem>& items);

        std::vector<std::string> get_lines() const;

    };
}


#endif //FORWARD_MAIL_UCISECTION_H
