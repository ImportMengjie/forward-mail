//
// Created by mengjie on 5/21/20.
//

#ifndef FORWARD_MAIL_MAILSERVER_H
#define FORWARD_MAIL_MAILSERVER_H

#include <string>
#include <curl/curl.h>
#include <cstring>

#include "Mail.h"

namespace dd{

    struct MemoryStruct {
        char *memory;
        size_t size;
        MemoryStruct(){
            memory = (char*)malloc(1);
            memory[0] = '\0';
            size = 0;
        }
    };

    class MailServer {
    private:
        std::string username;
        std::string mail_address;
        std::string password;
        std::string URL;
        CURL* curl;

        void init_login();

    public:
        MailServer(std::string  mail_address, std::string  password, std::string  url);

        MailServer(const MailServer& mailServer);

        MailServer& operator=(MailServer&)=delete;

        ~MailServer();

        bool send_mail(Mail& mail, std::string to_address="");

        std::vector<int> search_new_uid();

        Mail recive_mail(int uid);

    };


    static size_t write_data(void* content, size_t size, size_t nmemb, void* userp){
        size_t realSize = size*nmemb;
        auto* memoryStruct = (MemoryStruct*) userp;

        memoryStruct->memory = (char*) realloc(memoryStruct->memory, memoryStruct->size+realSize+1);
        if(!memoryStruct->memory){
            printf("realloc error \n");
            return 0;
        }
        memcpy(&memoryStruct->memory[memoryStruct->size], content, realSize);
        memoryStruct->size+=realSize;
        memoryStruct->memory[memoryStruct->size] = '\0';
        return realSize;
    }

    static size_t output_data(void* content, size_t size, size_t nmemb, void* userp){
        Mail* pMail = (Mail*)userp;
        const char* data;
        if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
            return 0;
        }
        data = pMail->next_line();
        if(data){
            size_t len = strlen(data);
            memcpy(content, data, len);
            return len;
        }
        return 0;
    }
}


#endif //FORWARD_MAIL_MAILSERVER_H
