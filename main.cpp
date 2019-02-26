#include <iostream>
#include "redis.h"
#include "spiderHandler.h"
#include "./thirdparty/boost/threadpool.hpp"
using namespace std;

int main(int argc, char**argv)
{

    string url = "http://www.youyuan.com/v30/find/beijing/mm18-40/advance-0-0-0-0-0-0-0/";
    //设置允许开启的线程数
    int threadNum = 4;
	boost::threadpool::pool tp(threadNum);
	for(int i = 0; i < threadNum; i++){
        tp.schedule(boost::bind(task, url));
    }
    
 
    return 0;
}
