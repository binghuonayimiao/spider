#include <iostream>
#include "redis.h"
#include "spiderHandler.h"
using namespace std;

int main(int argc, char**argv)
{
    ccx::Redis redis;
    redis.Connect();
    
    string baseUrl = "http://www.youyuan.com/v30/find/beijing/mm18-40/advance-0-0-0-0-0-0-0/";
    setSocketFd(baseUrl);
    vector<string> profileIDVec;
    setProfileIDVec(profileIDVec, baseUrl);
    getInfoAndWriteToRedis(profileIDVec, redis);

    redis.disConnect();
 
    return 0;
}
