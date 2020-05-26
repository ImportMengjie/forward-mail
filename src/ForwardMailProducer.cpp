//
// Created by mengjie on 5/21/20.
//

#include "ForwardMailProducer.h"
#include "base/utility.hpp"
#include "ForwardMailTask.h"

#include <thread>
#include <iostream>


dd::MailServer ForwardMailProducer::generate_new_mail_server(std::string url) {
    if(url.empty())
        return dd::MailServer(send_mailServer);
    else
        return dd::MailServer(send_mailServer.getMailAddress(), send_mailServer.getPassword(), std::move(url));
}

std::vector<std::shared_ptr<dd::Task>> ForwardMailProducer::product() {
    std::vector<std::shared_ptr<dd::Task>> ans;
    std::vector<int> new_mail_ids = search_marilServer.search_new_uid();
#ifdef DD_VERBOSE
    std::cout<<"get mail ids size: "<<new_mail_ids.size()<<std::endl;
#endif
    for(int& uid:new_mail_ids){
        dd::Mail new_mail = receive_mailServer.receive_mail(uid);
        new_mail.set_value("From", new_mail.get_value("To"));
        for(std::string& addr: to_mails_address){
//            new_mail.set_value("To", dd::replace_middle(new_mail.get_value("To"), addr, "<", ">"));
            new_mail.set_value("To", "<"+addr+">\r\n");
            ans.push_back(std::make_shared<ForwardMailTask>(new_mail, send_mailServer));
        }
    }
    return ans;
}

ForwardMailProducer::ForwardMailProducer(const std::string& mail_address, const std::string& password, std::string receive_url,
                                         std::string send_url, std::vector<std::string> &to_mails_address)
        : send_mailServer(mail_address, password,
                          std::move(send_url)),receive_mailServer(mail_address, password, std::move(receive_url)) ,
                          to_mails_address(to_mails_address), search_marilServer(receive_mailServer) {
#ifdef DD_VERBOSE
    std::cout<<"send mail server:"<<std::endl
    <<send_mailServer.toString()
    <<"receive mail server:"<<std::endl
    <<receive_mailServer.toString();

    std::cout<<"to mails address: "<<std::endl;
    for(auto& address:to_mails_address)
        std::cout<<address<<std::endl;
#endif
}



