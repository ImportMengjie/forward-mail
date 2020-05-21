//
// Created by mengjie on 5/21/20.
//

#ifndef FORWARD_MAIL_FORWARDMAILTASK_H
#define FORWARD_MAIL_FORWARDMAILTASK_H

#include "base/Task.h"

#include <utility>
#include "base/Mail.h"
#include "base/MailServer.h"

class ForwardMailTask : public dd::Task{
private:
    dd::Mail mail;
    dd::MailServer mailServer;

public:
    ForwardMailTask(dd::Mail mail, const dd::MailServer& mailServer):mail(std::move(mail)),mailServer(mailServer){}

    void doit() override {
        mailServer.send_mail(mail);
    }
};


#endif //FORWARD_MAIL_FORWARDMAILTASK_H
