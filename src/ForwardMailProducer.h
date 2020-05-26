//
// Created by mengjie on 5/21/20.
//

#ifndef FORWARD_MAIL_FORWARDMAILPRODUCER_H
#define FORWARD_MAIL_FORWARDMAILPRODUCER_H

#include <string>
#include <utility>

#include "base/Producer.h"
#include "base/Task.h"
#include "base/MailServer.h"


class ForwardMailProducer: public dd::Producer {
private:
    dd::MailServer send_mailServer;
    dd::MailServer receive_mailServer;
    dd::MailServer search_marilServer;

    std::vector<std::string> to_mails_address;

public:

    ForwardMailProducer(const std::string& mail_address, const std::string& password, std::string receive_url, std::string send_url, std::vector<std::string> &to_mails_address);

    dd::MailServer generate_new_mail_server(std::string url="");

    std::vector<std::shared_ptr<dd::Task>> product() override;

};


#endif //FORWARD_MAIL_FORWARDMAILPRODUCER_H
