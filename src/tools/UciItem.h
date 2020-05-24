//
// Created by mengjie on 5/22/20.
//

#ifndef FORWARD_MAIL_UCIITEM_H
#define FORWARD_MAIL_UCIITEM_H
#include <string>

namespace dd{

    struct UciItem {
    public:
        std::string config_type;
        std::string config_name;
        std::string config_value;

        explicit UciItem(const std::string& line);

        UciItem()=default;

        UciItem(std::string config_type, std::string config_name, std::string config_value);

        std::string get_line() const;

        std::string get_key() const;

        std::string get_value() const;

    private:
        static std::string remove_quota(const std::string& str);

    };
}


#endif //FORWARD_MAIL_UCIITEM_H
