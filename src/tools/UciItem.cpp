//
// Created by mengjie on 5/22/20.
//

#include "UciItem.h"

#include <utility>
#include <regex>
namespace dd{
    UciItem::UciItem(const std::string& line){
        std::regex r_handle_line(R"(^\s*(\w+)\s+([^\s]+|'.*'|".*")\s*([^\s]*|'.*'|".*")\s*$)");
        std::smatch match_result;
        std::regex_match(line, match_result, r_handle_line);
        this->config_type = match_result.str(1);
        this->config_name = remove_quota(match_result.str(2));
        this->config_value = remove_quota(match_result.str(3));
    }

    UciItem::UciItem(std::string config_type, std::string config_name, std::string config_value)
            :config_name(std::move(config_name)), config_type(std::move(config_type)), config_value(std::move(config_value)) {
    }

    std::string UciItem::remove_quota(const std::string &str) {
        if(str.empty()) return str;
        if (str[0]=='\''|| str[0]=='"')
            return str.substr(1, str.size()-2);
        return str;
    }

    std::string UciItem::get_line() const {
        return  this->config_type+" "+this->config_name+" "+this->config_value;
    }

    std::string UciItem::get_key() const {
        return this->config_name+":"+this->config_value;
    }

    std::string UciItem::get_value() const {
        return this->config_value;
    }
}
