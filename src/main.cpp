#include <iostream>
#include <map>
#include <curl/curl.h>

using namespace std;

int main()
{
    cout << "Hello, It's work!" << endl;

    auto i = 1;
    auto d = 0.57;
    auto str = "Hello";

    //-----------------------------------------------
    map<string, int> m {{"a",1}, {"b",2}};
    for (const auto &p : m) {
        cout << p.first << "=" << p.second << endl;
    }

    //-----------------------------------------------
    int count = 0;
    auto print_num = [&count] (int num) {
        cout << "num : " << num << endl;
        count += num;
    };
    print_num(12);
    print_num(32);
    cout << "count=" << count << endl;

     CURL *curl;
  CURLcode res = CURLE_OK;
 
  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */ 
    curl_easy_setopt(curl, CURLOPT_USERNAME, "user");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "secret");
 
    /* This will fetch message 1 from the user's inbox */ 
    curl_easy_setopt(curl, CURLOPT_URL,
                     "imap://imap.example.com/INBOX/;UID=1");
 
    /* Perform the fetch */ 
    res = curl_easy_perform(curl);
 
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* Always cleanup */ 
    curl_easy_cleanup(curl);
  }
 
  return (int)res;
}