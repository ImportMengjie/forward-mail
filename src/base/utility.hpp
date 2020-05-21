//
// Created by mengjie on 5/21/20.
//

#ifndef FORWARD_MAIL_UTILITY_HPP
#define FORWARD_MAIL_UTILITY_HPP
#include <string>
#include <vector>

namespace dd{
    using std::string;
    using std::vector;

    void split(const string& s, vector<string>& tokens, const string& delimiters = " ")
    {
        string::size_type lastPos = s.find_first_not_of(delimiters, 0);
        string::size_type pos = s.find_first_of(delimiters, lastPos);
        while (string::npos != pos || string::npos != lastPos) {
            tokens.emplace_back(s.substr(lastPos, pos - lastPos));
            lastPos = s.find_first_not_of(delimiters, pos);
            pos = s.find_first_of(delimiters, lastPos);
        }
    }

    std::string get_middle(const string& str, const string& left, const string& right){
        int l = str.find(left);
        int r = str.find(right, l);
        if(l!=string::npos&&r!=string::npos)
            return str.substr(l+left.size(), r-l+1+left.size());
        return "";
    }

    std::string replace_middle(const string& src, const std::string& mid, const string& left, const string& right){
        int l = src.find(left);
        int r = src.find(right, l);
        if(l!=string::npos&&r!=string::npos)
            return src.substr(0,l+left.size())+mid+src.substr(r);
        return "";
    }
}


#endif //FORWARD_MAIL_UTILITY_HPP
