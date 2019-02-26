#include "spiderHandler.h"

int socketFd;
void GetUrlAndPath(const string url, string &HostUrl, string &PagePath)
{
    HostUrl = url;
    PagePath = "/";
    //去除 http:// 字符串
    int pos = HostUrl.find("http://");
    if(pos != -1)
    {
        HostUrl = HostUrl.replace(pos, 7, "");
    }
 
    //去除 https:// 字符串
    pos = HostUrl.find("https://");
    if(pos != -1)
    {
        HostUrl = HostUrl.replace(pos, 8, "");
    }
 
    //提取主机端口和路径
    pos = HostUrl.find("/");
    if(pos != -1)
    {
        PagePath = HostUrl.substr(pos);
        HostUrl = HostUrl.substr(0, pos);
    }
}
void setSocketFd(const string url){
    //记录主机的信息，包括主机名、别名、地址类型、地址长度和地址列表
    struct hostent *host;
    string HostUrl, PagePath;
 
    //从url获取主机url和路径
    GetUrlAndPath(url, HostUrl, PagePath);
 
    //通过主机名连接主机
    host = gethostbyname(HostUrl.c_str());
    if(host == 0)
    {
        cout<<"gethostbyname error";
        exit(1);
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = ((struct in_addr*) (host->h_addr))->s_addr;
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFd == -1)
    {
        cout<<"create socketFd error"<<endl;
        exit(1);
    }
    int ret = connect(socketFd, (const sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        cout<<"connect error"<<endl;
        exit(1);
    }
}
string getpagecontent(const string url)
{
    //记录主机的信息，包括主机名、别名、地址类型、地址长度和地址列表
    struct hostent *host;
    string HostUrl, PagePath;
 
    //从url获取主机url和路径
    GetUrlAndPath(url, HostUrl, PagePath);
 
    string requestHeader;
    requestHeader   = "GET " + PagePath + " HTTP/1.1\r\n";
    requestHeader += "Host: " + HostUrl + "\r\n";
    requestHeader += "Accept: */*\r\n";
    requestHeader += "User-Agent: Mozilla/4.0(compatible)\r\n";
    requestHeader += "connection:Keep-Alive\r\n";
    requestHeader += "\r\n";

    int ret = send(socketFd, requestHeader.c_str(), requestHeader.size(), 0);
    if(ret == -1)
    {
        cout<<"send error"<<endl;
        exit(1);
    }
 
    struct timeval timeout = {1, 0};
    setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(struct timeval));
    char c;
    bool flag = true;
    while(recv(socketFd, &c, 1, 0))
    {
        if(c == '\r')
        {
            continue;
        }
        else if(c == '\n')
        {
            if(flag == false)
                break;
            flag = false;
        }
        else
        {
            flag = true;
        }
    }
 
    int len, BUFFERSIZE = 512;
    char buffer[BUFFERSIZE];
    string pagecontent = "";
    while((len = recv(socketFd, buffer, BUFFERSIZE-1, 0)) > 0)
    {
        buffer[len] = '\0';
        pagecontent += buffer;
    }
 
    return pagecontent;
}
vector<string> getRegularResult(string &str, regex &reg){
    vector<string> vec;
    sregex_iterator ite(str.begin(), str.end(), reg);
    sregex_iterator end;
    for(; ite != end; ++ite)
    {
        //cout << ite->str() << endl;
        vec.push_back(ite->str());
    }
    return vec;
}
void getInfoAndWriteToRedis(vector<string> &profileIDVec, ccx::Redis &redis){
    if(profileIDVec.empty()){
        cout<<"funName = getInfo, profileIDVec is empty"<<endl;
        return;
    }
    string baseUrl = "http://www.youyuan.com/";
    for(auto &ite: profileIDVec){
        string url = baseUrl + ite;
        string responseStr = getpagecontent(url);
        cout<<ite<<endl;
        regex nameRegxTemp("main\"><strong>[\u4e00-\u9fa5a-zA-Z0-9]{1,100}</strong><span><a href");
        vector<string> nameVecTemp = getRegularResult(responseStr, nameRegxTemp);
        if(!nameVecTemp.empty()){
            regex nameRegx("[\u4e00-\u9fa5]{1,100}");
            vector<string> nameVec = getRegularResult(nameVecTemp[0], nameRegx);

            if(!nameVec.empty()){
                    redis.setString("zgs_test", nameVec[0]);
					cout<<"name= "<< nameVec[0]<<endl;
            }else{
                cout<<"funName = getResponseInfo, nameVec is empty"<<endl;
            }

        }else{
            cout<<"funName = getResponseInfo, nameVecTemp is empty"<<endl;
        }
        
    }

}
void setProfileIDVec(vector<string> &profileIDVec, string &baseUrl){
    //爬取100页信息
    for(int i = 1; i < 10; i++){
        string url = baseUrl + "p" + to_string(i) +"/";
        string responseStr = getpagecontent(url);
        regex reg("\\d{1,10}-profile");
        vector<string> profileIDVecTemp = getRegularResult(responseStr, reg);
        cout<<"profileIDVecTemp.size= "<< profileIDVecTemp.size()<<endl;
        profileIDVec.insert(profileIDVec.end(), profileIDVecTemp.begin(), profileIDVecTemp.end());
    }
    
    //profileID正则匹配两个，去重处理
    profileIDVec.erase(unique(profileIDVec.begin(), profileIDVec.end()), profileIDVec.end());
    cout<<"profileIDVec.size= "<< profileIDVec.size()<<endl;

}
