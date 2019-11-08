#include <iostream>
#include "MyLog.h"
using namespace std;

int main() {
//    std::cout << "Hello, World!" << std::endl;

    init_mylog("e:/log/info.txt","e:/log/warn.txt","e:/log/error.txt");
    LOG(INFO) << "hello";
    cout<<"hello";
    return 0;
}