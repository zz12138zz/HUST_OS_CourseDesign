#include "login.h"
#include <iostream>
#include <cstdio>
login::login()
{
    FILE *fp;
    if ((fp = fopen("user.ini", "r")) == nullptr) {
        printf("File client.txt could not be opened\n");
        fclose(fp);
        return;
    }
    char user[44];
    char pass[256];
    while (!feof(fp)) {
        fscanf(fp, "%s%s", user, pass);
        this->users[string(user)]=string(pass);
    }
    fclose(fp);
}

bool login::user_register()
{
    string name,pass;
    cout << "Please input your name:";
    cin >> name;
    cout << "Please input your password: ";
    cin >> pass;
    if(name.length()>43){
        cout<<"user's name is too long ,please limit length to 43 bytes!"<<endl;
        getchar();
        getchar();
        return false;
    }
    if(this->users.find(name)!=this->users.end()){
        cout<<"name has already existed!"<<endl;
        getchar();
        getchar();
        return false;
    }
    this->users[name]=pass;
    FILE *fp;
    if ((fp = fopen("user.ini", "r+")) == nullptr) {
        printf("File client.txt could not be opened\n");
        getchar();
        getchar();
        fclose(fp);
        return false;
    }
    for(auto& p:this->users){
        fprintf(fp,"%s %s\n",p.first.c_str(),p.second.c_str());
    }
    fclose(fp);
    cout<<"sign up success!"<<endl;
    getchar();
    getchar();
    return true;
}

string login::user_login(){
    string name,pass;
    cout << "Please input your name:";
    cin >> name;
    cout << "Please input your password: ";
    cin >> pass;
    if(this->users.find(name)==this->users.end()){
        cout<<"sign up first!"<<endl;
        getchar();
        getchar();
        return "";
    }
    if(this->users[name]==pass){
        cout<<"success!"<<endl;
        getchar();
        getchar();
        return name;
    }
    return "";
}



