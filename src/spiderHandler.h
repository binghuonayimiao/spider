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
#include <thread>
using namespace std;

void GetUrlAndPath(const string url, string &HostUrl, string &PagePath);
void task(string url);
int  getSocketFd(const string url);
void getInfoAndWriteToRedis(vector<string> &profileIDVec, ccx::Redis &redis, int &socketFd);
void setProfileIDVec(vector<string> &profileIDVec, string &baseUrl, int &socketFd);
string getpagecontent(const string url, int &socketFd);
vector<string> getRegularResult(string &str, regex &reg);
#endif
