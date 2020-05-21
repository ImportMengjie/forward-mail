//
// Created by mengjie on 5/21/20.
//

#include "MailServer.h"

#include "utility.hpp"

using namespace dd;

void MailServer::init_login() {
    curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
//#ifdef DD_DEBUG
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
//#endif
}

MailServer::MailServer(std::string mail_address, std::string password, std::string url)
    :mail_address(std::move(mail_address)),password(std::move(password)), URL(std::move(url)),curl(curl_easy_init()) {
    username = this->mail_address.substr(0,this->mail_address.find('@'));
}

MailServer::MailServer(const MailServer & mailServer)
    :MailServer(mailServer.mail_address,mailServer.password,mailServer.URL) {
}

MailServer::~MailServer() {
    curl_easy_cleanup(curl);
}

bool MailServer::send_mail(Mail &mail, std::string to_address) {
    curl_easy_reset(curl);
    init_login();
    struct curl_slist *recipients = NULL;

    if(to_address.empty())
        to_address = dd::get_middle(mail.get_value("To"), "<", ">");
    else
        mail.set_value("To", dd::replace_middle(mail.get_value("To"),to_address,"<",">"));
    mail.set_value("From", dd::replace_middle(mail.get_value("From"),this->mail_address,"<",">"));

    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, this->mail_address.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

    // TODO: add cc supports
    recipients = curl_slist_append(recipients, to_address.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, output_data);
    curl_easy_setopt(curl, CURLOPT_READDATA, &mail);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_INFILESIZE, mail.get_size());
    CURLcode  res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    mail.reset();
    curl_slist_free_all(recipients);
    return false;
}

std::vector<int> MailServer::search_new_uid() {
    MemoryStruct memoryStruct;
    vector<int> ans;
    curl_easy_reset(curl);
    init_login();
    curl_easy_setopt(curl, CURLOPT_URL, std::string(URL+"/INBOX").c_str());

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SEARCH NEW");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &memoryStruct);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    CURLcode  res = curl_easy_perform(curl);
    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }else{
        string data(memoryStruct.memory);
        vector<std::string> chuck;
        std::string t = data.substr(data.find("SEARCH")+7, data.find('\r')-data.find("SEARCH")+7);
        int find_r = data.find('\r');
        int find_s = data.find("SEARCH");
        dd:split(data.substr(data.find("SEARCH")+6,data.find('\r') - data.find("SEARCH")-6),chuck," ");
        for(auto& str:chuck)
            ans.push_back(std::stoi(str));
    }
    return ans;
}

Mail MailServer::receive_mail(int uid) {
    MemoryStruct memoryStruct;
    curl_easy_reset(curl);
    init_login();
    curl_easy_setopt(curl, CURLOPT_URL, std::string(URL+"/INBOX/;UID="+std::to_string(uid)).c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &memoryStruct);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    CURLcode  res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    Mail mail(memoryStruct.memory);
    return mail;
}


