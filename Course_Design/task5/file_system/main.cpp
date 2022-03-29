#include <iostream>
#include<login.h>
#include<file_system.h>
using namespace std;
int main() {
    cout<<endl;
    system("clear");
    int choice;
    string name,pass;
    login tool;
    while (true) {
        system("clear");
        cout << "\t\t————————————————————————————————————————\t" << endl;
        cout << "\t\t           Yizumi File System           \t" << endl;
        cout << "\t\t               1. sign up               \t" << endl;
        cout << "\t\t               2. login                 \t" << endl;
        cout << "\t\t               3. sign out              \t" << endl;
        cout << "\t\t————————————————————————————————————————\t" << endl;
        cout << "\t\tPlease input your choice:" ;
        cin>>choice;
        switch (choice) {
            case 1:
                tool.user_register();
                break;
            case 2: {
                string name = tool.user_login();
                if (name.length()!=0){
                    file_system f(name);
                    f.start();
                }
                break;
            }
            case 3: {
                cout << "Farewell......" << endl;
                return 0;
                break;
            }
            default:
                cout << "invalid choice!"<< endl;
                break;
        }
    }
    return 0;
}
