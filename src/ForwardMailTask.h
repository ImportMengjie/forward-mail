//
// Created by mengjie on 5/21/20.
//

#ifndef FORWARD_MAIL_FORWARDMAILTASK_H
#define FORWARD_MAIL_FORWARDMAILTASK_H

#include "base/Task.h"
#include "base/Mail.h"
#include "base/MailServer.h"
#include "base/utility.hpp"

#include <iostream>
#include <utility>

class ForwardMailTask : public dd::Task{
private:
    dd::Mail mail;
    dd::MailServer mailServer;

public:
    ForwardMailTask(dd::Mail mail, const dd::MailServer& mailServer):mail(std::move(mail)),mailServer(mailServer){}

    void doit() override {
#ifdef DD_VERBOSE
        std::cout<<"attempt to send mail form "<<mailServer.getMailAddress()
        <<"to "<<dd::get_middle(mail.get_value("To"), "<", ">")<<std::endl;
#endif
        mailServer.send_mail(mail);
#ifdef DD_VERBOSE
        std::cout<<"send success!"<<std::endl;
#endif
    }
};


#endif //FORWARD_MAIL_FORWARDMAILTASK_H
