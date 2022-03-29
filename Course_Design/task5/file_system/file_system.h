#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include "def.h"
#include <string>
#include <vector>
using namespace std;
class file_system
{
    //system
    const int block_number;
    const int block_size;
    int free_nblock;
    int free_ninode;
    inode *inode_table;
    bool *block_used;
    const int BLOCK_OFFSET;
    const int MENU_SIZE;
    //user
    string pwd;
    string user;
    int pwd_menu_inode;
public:
    void debug(string name);
    file_system(string s);
    ~file_system();
    void start();
private:
    void help();
    int find_file_pwd(string name);
    bool check_pwd();
    bool check_file(int inode);
    void save(FILE* &fp);
    int creat_file(string name,int type);
    int remove_single_file(int target_file_inode,int index,FILE* fp);
    int remove_file(int target_file_inode,int index,FILE* fp);
    int read_to_s(string name,string& s);
    int write_from_s(string name,string s);
    vector<string> simplify_path(string path);

    int touch(string name);
    int rm(string name);
    int mkdir(string name);
    int read(string name);
    int write(string name);
    void ls();
    int cd(string dest);
    int cp(string src,string tar);

    string char_to_string(char *s);
    void string_to_char(char *s, string t);
    int find_free_inode();
    int find_free_block();
    int find_menuID(string fileName);
};


#endif // FILE_SYSTEM_H
