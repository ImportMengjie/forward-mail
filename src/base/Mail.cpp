//
// Created by mengjie on 5/21/20.
//
#include <regex>

#include "Mail.h"
#include "utility.hpp"

Mail::Mail(const char *str):data(str) {
    dd::split(data,lines,"\n");
    rehash();
}

void Mail::resize() {
    total_size = 0;
    for(auto& line:lines)
        total_size+=line.size();
}

std::string Mail::get_line(const std::string &key) {
    return lines[table_k_ids[key][0]];
}

bool Mail::set_line(const std::string &key, const std::string& value) {
    if(contain_key(key)){
        lines[table_k_ids[key][0]] = value;
        resize();
    }
    return false;
}

bool Mail::contain_key(const std::string &key) {
    return table_k_ids.count(key) != 0;
}

int Mail::delete_line(const std::string &key) {
    if(contain_key(key)){
        int count = table_k_ids[key].size();
        for(auto& ids:table_k_ids[key])
            delete_line(ids);
        rehash();
        return count;
    }
    return 0;
}

void Mail::rehash() {
    std::string prev_keyword;
    std::regex regex(R"(^\w*:\s.*\r\n$)");
    for(int i=0;i<lines.size();i++){
        lines[i].append("\n");
        total_size+=lines[i].size();
        if(std::regex_match(lines[i],regex)){
            std::vector<std::string> tokens;
            dd::split(lines[i],tokens,":");
            table_k_ids[tokens[0]] = std::vector<int>{i};
            prev_keyword = tokens[0];
        }else if(!prev_keyword.empty()&&(lines[i][0]==' '||lines[i][0]=='\t'))
            table_k_ids[prev_keyword].push_back(i);
        else
            prev_keyword = "";
    }
}

bool Mail::delete_line(const int &ids) {
    if(ids<lines.size()){
        lines.erase(lines.begin()+ids);
        return true;
    }
    return false;
}

std::string Mail::get_value(const std::string &key) {
    std::string value = get_line(key);
    std::vector<std::string> tokens;
    dd::split(value, tokens, ": ");
    if(tokens.size()>=2)
        return tokens[1];
    return std::__cxx11::string();
}

bool Mail::set_value(const std::string &key, const std::string &value) {
    return set_line(key, key + ": " + value);
}

const char *Mail::next_line() {
    if(current_line<lines.size())
        return lines[current_line++].c_str();
    return nullptr;
}

void Mail::reset() {
    current_line = 0;
}
