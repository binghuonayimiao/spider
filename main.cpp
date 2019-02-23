#include <iostream>
#include <string>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <regex>
#include <vector>
#include <unistd.h>
#include "spiderHandler.h"
using namespace std;
 
#define ERROR    -1
#define OK          0
#define PORT      80

int main(int argc, char**argv)
{
    
    string baseUrl = "http://www.youyuan.com/v30/find/beijing/mm18-40/advance-0-0-0-0-0-0-0/";
    setSocketFd(baseUrl);
    vector<string> profileIDVec;
    setProfileIDVec(profileIDVec, baseUrl);
    
    getResponseInfo(profileIDVec);
 
    return 0;
}
