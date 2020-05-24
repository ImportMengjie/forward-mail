//
// Created by mengjie on 5/22/20.
//

#include "UciSection.h"


dd::UciSection::UciSection(const std::string& section_name, const std::string& section_value, const std::vector<UciItem> &items)
    :section("config", section_name, section_value) {
    add_items(items);
}

std::vector<std::string> dd::UciSection::get_lines() const {
    std::vector<std::string> ret;
    for(auto& it:this->options)
        ret.push_back(it.second.get_line());
    for(auto& list:this->lists)
        for(auto& it:list.second)
            ret.push_back(it.get_line());
    return ret;
}

dd::UciSection::UciSection(const std::string &section_name, const std::string &section_value)
:section("config", section_name, section_value) {
}

void dd::UciSection::add_item(const dd::UciItem& item) {
    if(item.config_type=="option")
        this->options[item.config_name] = item;
    else if(item.config_type=="list"){
        if(!this->lists.count(item.config_name))
            this->lists[item.config_name] = {item};
        else
            this->lists[item.config_name].push_back(item);
    }
}

void dd::UciSection::add_items(const std::vector<UciItem>& items) {
    for(auto& item:items)
        add_item(item);
}

dd::UciItem dd::UciSection::getOption(const std::string &name) {
    return this->options[name];
}

std::vector<dd::UciItem> dd::UciSection::getList(const std::string &name) {
    return this->lists[name];
}

std::string dd::UciSection::getValue(const std::string &name) {
    return this->getOption(name).get_value();
}

std::vector<std::string> dd::UciSection::getValues(const std::string &name) {
    std::vector<std::string> ret;
    for(auto& item: this->getList(name))
        ret.push_back(item.get_value());
    return ret;
}
