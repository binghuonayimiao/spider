#ifndef _SPIDERHANDLER_H
#define _SPIDERHANDLER_H

#include <iostream>
#include <string>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <regex>
#include <vector>
#include "../redis/redis.h"
#include <unistd.h>
using namespace std;
extern int socketFd;

void GetUrlAndPath(const string url, string &HostUrl, string &PagePath);
void setSocketFd(const string url);
void getInfoAndWriteToRedis(vector<string> &profileIDVec, ccx::Redis &redis);
void setProfileIDVec(vector<string> &profileIDVec, string &baseUrl);
string getpagecontent(const string url);
vector<string> getRegularResult(string &str, regex &reg);
#endif
