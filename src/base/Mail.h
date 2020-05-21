//
// Created by mengjie on 5/21/20.
//

#ifndef FORWARD_MAIL_MAIL_H
#define FORWARD_MAIL_MAIL_H

#include <string>
#include <vector>
#include <unordered_map>

class Mail {
private:
    std::string data;
    std::vector<std::string> lines;
    int current_line = 0;
    size_t total_size = 0;

    std::unordered_map<std::string,std::vector<int>> table_k_ids;

    void resize();

    void rehash();

    std::string get_line(const std::string& key);

    bool set_line(const std::string& key, const std::string& value);


    bool delete_line(const int& ids);

public:
    explicit Mail(const char* str);

    int delete_line(const std::string& key);

    bool contain_key(const std::string& key);

    bool set_value(const std::string& key, const std::string& value);

    std::string get_value(const std::string& key);

    const char* next_line();

    void reset();

    size_t get_size() const{return total_size;};

};


#endif //FORWARD_MAIL_MAIL_H
