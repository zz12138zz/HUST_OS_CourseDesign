#ifndef LOGIN_H
#define LOGIN_H
#include<string>
#include<unordered_map>
using namespace std;

class login
{
    unordered_map<string,string> users;
public:
    login();
    bool user_register();
    string user_login();
};

#endif // LOGIN_H
