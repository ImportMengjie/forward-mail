//
// Created by mengjie on 5/22/20.
//

#include "UciItem.h"

#include <utility>
#include <regex>
namespace dd{
    UciItem::UciItem(std::string line):line(std::move(line)) {
        std::regex r_handle_line(R"(^\s*(\w+)\s+(\w+|'[\w\s]*'|"[\w\s]*")\s+(\w+|'[\w\s]*'|"[\w\s]*")\s*$)");
        std::smatch match_result;
        std::regex_match(this->line, match_result, r_handle_line);
        this->config_type = match_result.str(1);
        this->config_name = remove_quota(match_result.str(2));
        this->config_value = remove_quota(match_result.str(3));
    }

    UciItem::UciItem(std::string config_type, std::string config_name, std::string config_value)
            :config_name(std::move(config_name)), config_type(std::move(config_type)), config_value(std::move(config_value)) {
        this->line = this->config_type+" "+this->config_name+" "+this->config_value;
    }

    std::string UciItem::remove_quota(const std::string &str) {
        if (str[0]=='\''|| str[0]=='"')
            return str.substr(1, str.size()-2);
        return str;
    }
}
