#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <curl/curl.h>
#include "base/Queue_s.h"
using namespace std;
//ZNFEJFBUGWLGEUYA

using namespace std;


/* This is a simple example showing how to send mail using libcurl's IMAP
 * capabilities.
 *
 * Note that this example requires libcurl 7.30.0 or above.
 */
struct MemoryStruct {
    char *memory;
    size_t size;
    MemoryStruct(){
        memory = (char*)malloc(1);
        memory[0] = '\0';
        size = 0;
    }
};

void split(const string& s, vector<string>& tokens, const string& delimiters = " ")
{
    string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos) {
        tokens.push_back(s.substr(lastPos, pos - lastPos));//use emplace_back after C++11
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}

struct OutputLines{
    string data;
    vector<string> lines;
    int count = 0;
    size_t size = 0;

    OutputLines(char* str):data(str){
        split(data, lines, "\n");
        for(string& line:lines){
            line.append("\n");
        }
        updatesize();
    }

    void handleData(string from, string to){
        for(string& line: lines){
            if(line.substr(0, 5)=="From:"){
                line = "From: \""+from+"\" <"+from+">\r\n";
            }
            if(line.substr(0, 3)=="To:"){
                line = "To: \""+to+"\" <"+to+">\r\n";
            }
        }
        updatesize();
    }

    void updatesize(){
        size = 0;
        for(string& line: lines){
            size+=line.size();
        }
    }

    const char* nextLine(){
        if(count<lines.size())
            return lines[count++].c_str();
        else
            return NULL;
    }

};

static size_t write_data(void* content, size_t size, size_t nmemb, void* userp){
    size_t realSize = size*nmemb;
    MemoryStruct* memoryStruct = (MemoryStruct*) userp;

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
    OutputLines* outputLines = (OutputLines*) userp;
    const char* data;
    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }
    data = outputLines->nextLine();
    if(data){
        size_t len = strlen(data);
        memcpy(content, data, len);

        return len;
    }
    return 0;
}

void send_mail(OutputLines& outputLines, string from, string to){
    CURL* curl = curl_easy_init();
    struct curl_slist *recipients = NULL;

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(curl, CURLOPT_USERNAME, "l253637141");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "ZNFEJFBUGWLGEUYA");
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.163.com");

    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from.c_str());

    /* Add two recipients, in this particular case they correspond to the
     * To: and Cc: addressees in the header, but they could be any kind of
     * recipient. */
    recipients = curl_slist_append(recipients, to.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);


    curl_easy_setopt(curl, CURLOPT_READFUNCTION, output_data);
    curl_easy_setopt(curl, CURLOPT_READDATA, &outputLines);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_INFILESIZE, outputLines.size);

    CURLcode  res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
}

void recive_mail(MemoryStruct &memoryStruct){
    CURL* curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(curl, CURLOPT_USERNAME, "l253637141");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "ZNFEJFBUGWLGEUYA");
    curl_easy_setopt(curl, CURLOPT_URL, "imap://imap.163.com/INBOX/;UID=3");
    curl_easy_setopt(curl, CURLOPT_URL, "imap://imap.163.com/INBOX");

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SEARCH NEW");

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &memoryStruct);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    CURLcode  res = curl_easy_perform(curl);

    if(res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    else
    {
        /*
        here is where you can work with the data inside the chunk...
        */
//        printf("%s\n",memoryStruct.memory); //here is the information
//        printf("%lu bytes retrieved\n", (long)memoryStruct.size);
    }
    curl_easy_cleanup(curl);
}

int main(){
    dd::Queue_s<int> q;
    MemoryStruct memoryStruct;
    curl_global_init(CURL_GLOBAL_ALL);
    recive_mail(memoryStruct);
    printf("%s\n",memoryStruct.memory); //here is the information
    printf("%lu bytes retrieved\n", (long)memoryStruct.size);
    OutputLines outputLines(memoryStruct.memory);

    string from = "l253637141@163.com";
    string to = "253637141@qq.com";
    outputLines.handleData(from,to);
//    send_mail(outputLines,from, to);
    return 0;

}
