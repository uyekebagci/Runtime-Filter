#include <fcntl.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mutex>
#include <vector>
#include <string.h>
#include <thread>
#include <iostream>
#include <pthread.h>
using namespace std;
string input;
static void* userInput_thread(void*)
{
    while(true) {
        cin>>input;  //Thread does wait for input always and it doesnt block the main thread that way main thread can read always and take the new income
    }
}

int main() {

    pthread_t tId;
    (void) pthread_create(&tId, 0, userInput_thread, 0);
    int file_desc = open("/home/umut/test3.txt", O_RDONLY);
    int copy_desc = dup(file_desc);
    cout<< "CLI**************************\n\n1          :INFO\n2          :DEBUG\n3          :Trace:"<< endl;
    cout << "******************************************************" << endl;
    cout << "--->Command:";
    string one = "1";
    string two = "2";
    string three = "3";
    string delimiter = "\n";          //Filter delimiter
    /*FILTER ELEMENTS
    string info = "INFO:";              
    string debug = "DEBUG:";
    string trace = "TRACE:";
    string fatal ="FATAL:";
    string warn ="WARN:";
    string error = "ERROR:";            
    */
    if (file_desc < 0)
        cout << file_desc << endl;
    vector<string> vectorInfo;
    vector<string> vectorDebug;
    vector<string> vectorTrace;
    string x = "";
    vector<string> vectorFatal;
    vector<string> vectorWarn;
    vector<string> vectorError;
    size_t pos = 0;
    string token;
    string substrFilter;
    char data[10000];
    while (1) {
        usleep(5000);
        read(copy_desc, data, 10000);
        x = data;
        while ((pos = x.find(delimiter)) != std::string::npos) {
            token = x.substr(0, pos);
            if (token.find(info, 0) != std::string::npos) {
                substrFilter = token;
                vectorInfo.push_back(substrFilter);
            } else if (token.find(debug, 0) != std::string::npos) {
                substrFilter = token;
                vectorDebug.push_back(substrFilter);
            } else if (token.find(trace, 0) != std::string::npos) {
                substrFilter = token;
                vectorTrace.push_back(substrFilter);
            }

            x.erase(0, pos + delimiter.length());
        }
        memset(data, 0, sizeof(data));
        if (input == one) {
            for (int i = 0; i < vectorInfo.size(); i++) {
                cout << vectorInfo.at(i) << endl;
            }
            vectorInfo.clear();
        } else if (input == two) {
            for (int k = 0; k < vectorDebug.size(); k++) {
                cout << vectorDebug.at(k) << endl;
            }
            vectorDebug.clear();
        } else if (input == three) {
            for (int h = 0; h < vectorTrace.size(); h++) {
                cout << vectorTrace.at(h) << endl;
            }
            vectorTrace.clear();
        }
    }
    (void) pthread_join(tId, NULL);
    return 0;
}
