#include <string>
#include <vector>
#include <curl/curl.h>
#include "ForwardMailProducer.h"
#include "base/QueueManager.h"
//ZNFEJFBUGWLGEUYA
//#define DD_DEBUG

using namespace std;


int main(){
    curl_global_init(CURL_GLOBAL_ALL);

    dd::QueueManager queueManager;
    std::vector<std::string> to_address{"253637141@qq.com","limengjie@hotmail.com"};

    queueManager.addProducer<ForwardMailProducer>("l253637141@163.com", "ZNFEJFBUGWLGEUYA", "imap://imap.163.com", "smtp://smtp.163.com",to_address);

    queueManager.start(1, 10);
    queueManager.join();

    return 0;

}
