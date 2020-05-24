#include <string>
#include <vector>
#include <curl/curl.h>

#include "ForwardMailProducer.h"
#include "base/QueueManager.h"
#include "tools/UciPackage.h"
//ZNFEJFBUGWLGEUYA
//#define DD_DEBUG

using namespace std;


int main(int argc, char** argv){
    if(argc<2) return 0;
    string config_path(argv[1]);
    curl_global_init(CURL_GLOBAL_ALL);
    dd::UciPackage uciPackage(config_path);

    dd::UciSection user_mail = uciPackage.get_section("user_mail","my_config");
    dd::UciSection others_mail = uciPackage.get_section("others_mail","others_config");

    dd::QueueManager queueManager;
    std::vector<std::string> to_address(others_mail.getValues("to_address"));
    string temp = "address";
    string address = user_mail.getValue(temp);

    queueManager.addProducer<ForwardMailProducer>(user_mail.getValue("address"),
            user_mail.getValue("password"), user_mail.getValue("imap_url"),
                    user_mail.getValue("smtp_url"),
                            to_address);

    queueManager.start(1, 10);
    queueManager.join();

    return 0;

}
