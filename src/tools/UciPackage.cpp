//
// Created by mengjie on 5/22/20.
//
#include <fstream>
#include <iostream>

#include "UciPackage.h"
#include "../base/utility.hpp"

dd::UciPackage::UciPackage(const std::string& config_path) {
    std::ifstream file_stream(config_path);
    std::string line;
    std::vector<UciItem> items;
    if(file_stream.is_open()){
        while(getline(file_stream, line))
            if(!line.empty())
                items.emplace_back(line);
    }else
        std::cerr<<"failed open "<<config_path<<"!"<<std::endl;
    init(items);
}

dd::UciPackage::UciPackage(const std::vector<UciItem> &items) {
    init(items);
}

void dd::UciPackage::init(const std::vector<UciItem> &items) {
    std::string prev_config_name;
    for(auto& item:items){
        if(item.config_type=="package")
            this->name = item.config_name;
        else if(item.config_type=="config"){
            prev_config_name = item.get_key();
            if(!this->map_name_sections.count(prev_config_name))
                this->map_name_sections.insert({prev_config_name,UciSection(item.config_name, item.config_value)});
        } else if(item.config_type=="option"||item.config_type=="list")
            if(!prev_config_name.empty())
                this->map_name_sections[prev_config_name].add_item(item);
    }

}

dd::UciSection dd::UciPackage::get_section(const std::string& type, const std::string& name) {
    return this->map_name_sections[UciItem("config",type,name).get_key()];
}

