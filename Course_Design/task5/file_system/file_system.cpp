#include "file_system.h"
#include <cstdio>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
file_system::file_system(string name):
    block_number(MAX_BLOCK_NUM),
    block_size(BLOCK_SIZE),
    BLOCK_OFFSET(sizeof (int)*2+sizeof(inode)*MAX_FILE_NUM+sizeof(bool)*MAX_BLOCK_NUM),
    MENU_SIZE(sizeof(menu)),
    pwd("/"),user(name),pwd_menu_inode(0)
{
    this->inode_table=new inode[MAX_FILE_NUM];
    this->block_used=new bool[MAX_BLOCK_NUM];
    memset(this->block_used, 0,MAX_BLOCK_NUM);
    FILE *fp = fopen("disk", "r");
    if (fp == nullptr)
    {
        this->free_nblock=MAX_BLOCK_NUM-1;
        this->free_ninode=MAX_FILE_NUM-1;
        FILE *newfs = fopen("disk", "w");
        //set root dir
        this->inode_table[0].i_type=__IS_FOLDER__;
        this->inode_table[0].i_mode=__EVERYONE__;
        this->inode_table[0].i_size=0;
        strcpy(this->inode_table[0].i_uid,"root");
        this->inode_table[0].first_block=this->inode_table[0].last_block=0;
        this->block_used[0]=true;
        this->inode_table[0].block_num=1;
        //save
        fwrite(&this->free_nblock,sizeof(int),1,newfs);
        fwrite(&this->free_ninode,sizeof(int),1,newfs);
        fwrite(this->inode_table, sizeof(inode), MAX_FILE_NUM, newfs);
        fwrite(this->block_used, sizeof(bool), MAX_BLOCK_NUM, newfs);
        fseek(newfs, 100 * 1024 * 1024 - 1, SEEK_SET);
        const char END_OF_FILE = EOF;
        fwrite(&END_OF_FILE, 1, 1, newfs);
        fclose(newfs);
    }
    else
    {
        fread(&this->free_nblock, sizeof(int), 1, fp);
        fread(&this->free_ninode, sizeof(int), 1, fp);
        fread(this->inode_table, sizeof(inode), MAX_FILE_NUM, fp);
        fread(this->block_used, sizeof(bool), MAX_BLOCK_NUM, fp);
        fclose(fp);
    }
    cout << "load file system done." << endl;
}

file_system::~file_system(){
    delete this->inode_table;
    delete this->block_used;
}

void file_system::help(){
    cout << endl;
    cout << "Yizumi file system,version 1.0" << endl;
    cout << "touch <filename>\t\t\tCreate a new file named <filename>" << endl;
    cout << "mkdir <dirname>\t\t\t\tCreate a new folder named <dirname>" << endl;
    cout << "read <filename>\t\t\t\tread txt file named <filename>" << endl;
    cout << "write <filename>\t\t\twrite to txt file named <filename>" << endl;
    cout << "cp <src> <target>\t\t\tcopy <src> to <target>" << endl;
    cout << "rm <filename>\t\t\t\tremove file or folder named <filename>" << endl;
    cout << "ls\t\t\t\t\tlist all files and folders in current menu" << endl;
    cout << "cd <dirname>\t\t\t\tgo to folder named <dirname>" << endl;
    cout << "help\t\t\t\t\tlist command of Yizumi File System" << endl;
    cout << "exit\t\t\t\t\tback to login page" << endl;
    cout << endl;
    cout << endl;
}

bool file_system::check_pwd()
{
    return !(this->inode_table[this->pwd_menu_inode].i_mode == __ONLY_OWNER__ && strcmp(this->user.c_str(),this->inode_table[this->pwd_menu_inode].i_uid)!=0);
}

bool file_system::check_file(int inode){
    if(this->inode_table[inode].i_type==__IS_FILE__)
        return !(this->inode_table[inode].i_mode == __ONLY_OWNER__ && strcmp(this->user.c_str(),this->inode_table[inode].i_uid)!=0);
    return false;
}

int file_system::find_file_pwd(string name)
{
    if(name.length()==0)    return -1;
    FILE *fp = fopen("disk", "r");
    menu temp;
    int block_iter = inode_table[this->pwd_menu_inode].first_block;
    int menu_file_size_to_search = inode_table[pwd_menu_inode].i_size;
    int blocks_to_search = inode_table[pwd_menu_inode].block_num;
    int ans=-1;
    while (blocks_to_search)
    {
        fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * block_iter, SEEK_SET);
        for (int i = 0; i < min((BLOCK_SIZE - 4) / MENU_SIZE, menu_file_size_to_search / MENU_SIZE); ++i)
        {
            fread(&temp, MENU_SIZE, 1, fp);
            if (temp.inode == -1) continue;
            string temp_file_name = string(temp.name);
            if (temp_file_name == name)
            {
                ans = temp.inode;
                break;
            }
        }
        if (ans != -1) break;
        blocks_to_search--;
        if (blocks_to_search!=0)
        {
            menu_file_size_to_search -= (BLOCK_SIZE - 4);
            fread(&block_iter, sizeof(int), 1, fp);
        }
    }

    fclose(fp);
    return ans;
}

int file_system::find_free_inode(){
    for (int i = 0; i < MAX_FILE_NUM; ++i)
    {
        if (this->inode_table[i].i_size == -1)
            return i;
    }
    return -1;
}

int file_system::find_free_block()
{
    for (int i = 0; i < MAX_BLOCK_NUM; ++i){
        if (!this->block_used[i])
            return i;
    }
    return -1;
}

void file_system::save(FILE*& fp){
    fseek(fp, 0, SEEK_SET);
    fwrite(&this->free_nblock,sizeof(int),1,fp);
    fwrite(&this->free_ninode,sizeof(int),1,fp);
    fwrite(this->inode_table, sizeof(inode), MAX_FILE_NUM, fp);
    fwrite(this->block_used, sizeof(bool), MAX_BLOCK_NUM, fp);
    fclose(fp);
}

int file_system::creat_file(string name,int type)
{
    if (name == "")
    {
        cout << "input a file name first!" << endl;
        return -1;
    }
    if(name.length()>11){
        cout<<"filename is too long ,please limit length to 11 bytes!"<<endl;
        return -1;
    }
    if(!check_pwd())
    {
        cout<<"Permission denied!"<<endl;
    }
    if (this->free_nblock==0 || this->free_nblock==0)
    {
        cout << "file system is full!" << endl;
        return -1;
    }
    if(this->find_file_pwd(name)!=-1)
    {
        cout<<name<<" has already exist!"<<endl;
        return -1;
    }
    int new_file_inode=find_free_inode();
    int new_file_block=find_free_block();
    this->free_nblock--;
    this->free_ninode--;
    this->inode_table[new_file_inode].block_num=1;
    this->inode_table[new_file_inode].i_size=0;
    this->block_used[new_file_block]=true;
    menu t(name.c_str(),new_file_inode);
    FILE *fp = fopen("disk", "r+");

    //add menu of new file to pwd
    int last_block_of_pwd=this->inode_table[this->pwd_menu_inode].last_block;
    int offset_in_last_block=inode_table[pwd_menu_inode].i_size%(this->block_size-4);
    //need new block
    if(inode_table[pwd_menu_inode].i_size!=0&&offset_in_last_block==0)
    {
        if(this->free_nblock==0)
        {
            cout<<"file system is full!"<<endl;
            return -1;
        }
        int new_menu_block=find_free_block();
        this->block_used[new_menu_block]=true;
        this->free_nblock--;
        this->inode_table[this->pwd_menu_inode].block_num++;
        this->inode_table[this->pwd_menu_inode].last_block=new_menu_block;
        fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * last_block_of_pwd + BLOCK_SIZE - 4, SEEK_SET);
        fwrite(&new_menu_block, sizeof(int), 1, fp);
        fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * new_menu_block, SEEK_SET);
        fwrite(&t,MENU_SIZE,1,fp);
    }
    //not need new block
    else
    {
        fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * last_block_of_pwd + offset_in_last_block, SEEK_SET);
        fwrite(&t,MENU_SIZE,1,fp);
    }
    this->inode_table[this->pwd_menu_inode].i_size+=MENU_SIZE;
    //add menu to pwd success,now change filesystem argument and set inode of new file
    strcpy(this->inode_table[new_file_inode].i_uid,this->user.c_str());
    this->inode_table[new_file_inode].i_mode=__ONLY_OWNER__;
    this->inode_table[new_file_inode].i_type=type;
    this->inode_table[new_file_inode].first_block=this->inode_table[new_file_inode].last_block=new_file_block;
    save(fp);
    cout<<"success!"<<endl;
    return 0;
}

int file_system::remove_single_file(int target_file_inode,int index,FILE *fp){
    //copy old index without taget file
    vector<menu> copy;
    int block_iter = inode_table[index].first_block;
    int menu_file_size_to_search = inode_table[index].i_size;
    int blocks_to_search = inode_table[index].block_num;
    while (blocks_to_search)
    {
        this->free_nblock++;
        this->block_used[block_iter]=false;
        fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * block_iter, SEEK_SET);
        for (int i = 0; i < min((BLOCK_SIZE - 4) / MENU_SIZE, menu_file_size_to_search / MENU_SIZE); ++i)
        {
            menu temp;
            fread(&temp, MENU_SIZE, 1, fp);
            if(temp.inode!=target_file_inode){
                copy.emplace_back(temp);
            }
        }
        blocks_to_search--;
        if (blocks_to_search!=0)
        {
            menu_file_size_to_search -= (BLOCK_SIZE - 4);
            fread(&block_iter, sizeof(int), 1, fp);
        }
    }//copy complete
//    for(menu m:copy){
//        cout<<m.name<<" "<<m.inode<<endl;
//    }
    //set new pwd inode
    inode_table[index].i_size=copy.size()*MENU_SIZE;
    inode_table[index].block_num=ceil((double)(inode_table[index].i_size)/(this->block_size-4));
    if(inode_table[index].i_size==0){
        inode_table[index].block_num=1;
    }
    //write new pwd
    int new_block_for_menu = find_free_block();
    this->free_nblock--;
    block_used[new_block_for_menu] = true;
    inode_table[index].first_block = new_block_for_menu;
    int offset = 0;
    int menu_cnt=copy.size();
    while (1)
    {
        if (menu_cnt <= (BLOCK_SIZE - 4) / 4)
        {
            fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * new_block_for_menu, SEEK_SET);
            fwrite(&copy[0] + offset, MENU_SIZE, menu_cnt, fp);
            inode_table[index].last_block = new_block_for_menu;
            break;
        }
        else
        {
            fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * new_block_for_menu, SEEK_SET);
            fwrite(&copy[0] + offset, sizeof(int), (BLOCK_SIZE - 4) / 4, fp);
            menu_cnt -= (BLOCK_SIZE - 4) / 4;
            offset += (BLOCK_SIZE - 4) / 4;
            new_block_for_menu = find_free_block();
            this->free_nblock--;
            block_used[new_block_for_menu] = 1;
            fwrite(&new_block_for_menu, sizeof(int), 1, fp);
        }
    }
    //rm target file
    block_iter=inode_table[target_file_inode].first_block;
    int last_block_of_target_file = inode_table[target_file_inode].last_block;
    while (1)
    {
        this->free_nblock++;
        block_used[block_iter] = 0;
        if (block_iter == last_block_of_target_file)
        {
            break;
        }
        else
        {
            fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * block_iter + BLOCK_SIZE - 4, SEEK_SET);
            fread(&block_iter, sizeof(int), 1, fp);
        }
    }
    this->free_ninode++;
    inode_table[target_file_inode].i_size=-1;
    return 0;
}

int file_system::remove_file(int target,int index,FILE *fp)
{
    if(inode_table[target].i_type==__IS_FILE__ || (inode_table[target].i_type==__IS_FOLDER__&&inode_table[target].i_size==0))
    {
        return this->remove_single_file(target,index,fp);
    }

    else
    {
        menu temp;
        int block_iter = inode_table[target].first_block;
        int menu_file_size_to_search = inode_table[target].i_size;
//        cout<<block_iter<<endl;
        for (int i = 0; i < menu_file_size_to_search / MENU_SIZE; ++i)
        {
            fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * block_iter, SEEK_SET);
            fread(&temp, MENU_SIZE, 1, fp);
//            cout<<temp.name<<" "<<temp.inode<<endl;
            if(this->remove_file(temp.inode,target,fp)!=0){
                cout<<"remove "<<temp.name<<" failed! Something wrong happened!"<<endl;
                return -1;
            }
        }
        return this->remove_single_file(target,index,fp);
        return 0;
    }
}

int file_system::read_to_s(string name,string& s)
{
    if (name == "")
    {
        cout << "input a file name first!" << endl;
        return -1;
    }
    if(name.length()>11)
    {
        cout<<"filename is too long ,please limit length to 11 bytes!"<<endl;
        return -1;
    }
    int target_file_inode=find_file_pwd(name);
    if(target_file_inode==-1)
    {
        cout<<"file not exist!"<<endl;
        return -1;
    }
    if(!check_file(target_file_inode))
    {
        cout<<"permission denied!"<<endl;
        return -1;
    }
    int block_iter=inode_table[target_file_inode].first_block;
    int last_block=inode_table[target_file_inode].last_block;
    char buf[this->block_size];
    FILE *fp = fopen("disk", "r");
    s="";
    while(1)
    {
//        cout<<block_iter<<endl;
        if(block_iter==last_block)
        {
            int offset=inode_table[target_file_inode].i_size%(this->block_size-4);
            if(offset==0){
                offset=this->block_size;
            }
            fseek(fp,BLOCK_OFFSET+this->block_size*block_iter,SEEK_SET);
            memset(buf,0,sizeof(buf));
            fread(buf,sizeof(char),offset,fp);
//            cout<<buf<<endl;
            s+=buf;
            break;
        }
        else
        {
            fseek(fp,BLOCK_OFFSET+this->block_size*block_iter,SEEK_SET);
            memset(buf,0,sizeof(buf));
            fread(buf,sizeof(char),this->block_size-4,fp);
//            cout<<buf<<endl;
            s+=buf;
            fread(&block_iter,sizeof(int),1,fp);
        }
    }
    save(fp);
    return 0;
}

int file_system::write_from_s(string name,string s)
{
    if (name == "")
    {
        cout << "input a file name first!" << endl;
        return -1;
    }
    if(name.length()>11)
    {
        cout<<"filename is too long ,please limit length to 11 bytes!"<<endl;
        return -1;
    }
    int target_file_inode=find_file_pwd(name);
    if(target_file_inode==-1)
    {
        cout<<"file not exist!"<<endl;
        return -1;
    }
    if(!check_file(target_file_inode))
    {
        cout<<"permission denied!"<<endl;
        return -1;
    }
    const char *buf=s.c_str();
    int len=s.length();
    int offset=this->inode_table[target_file_inode].i_size%(BLOCK_SIZE-4);
    int max_free_byte = BLOCK_SIZE - 4 - offset + this->free_nblock * (BLOCK_SIZE - 4);
    if(max_free_byte< len ){
        cout<<"file system is full!"<<endl;
        return -1;
    }
    FILE *fp = fopen("disk", "r+");
    inode_table[target_file_inode].i_size += len;
    int char_pos=0;
    while(len>0)
    {
        if (len <= BLOCK_SIZE - offset - 4)
        {
            fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * this->inode_table[target_file_inode].last_block + offset, SEEK_SET);
            fwrite(buf + char_pos, sizeof(char), len, fp);
            break;
        }
        else
        {
            fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * this->inode_table[target_file_inode].last_block + offset, SEEK_SET);
            fwrite(buf + char_pos, sizeof(char), BLOCK_SIZE - offset - 4, fp);
            char_pos+=BLOCK_SIZE - offset - 4;
            int new_block=this->find_free_block();
//            cout<<new_block<<endl;
            fwrite(&new_block,sizeof(int),1,fp);
            inode_table[target_file_inode].block_num++;
            inode_table[target_file_inode].last_block=new_block;
            this->free_nblock--;
            this->block_used[new_block]=true;
            len-=BLOCK_SIZE - offset - 4;
            offset=0;
        }
    }
    save(fp);
    return 0;
}

vector<string> file_system::simplify_path(string path) {
    auto split = [](const string& s, char delim) -> vector<string> {
        vector<string> ans;
        string cur;
        for (char ch: s) {
            if (ch == delim) {
                ans.push_back(move(cur));
                cur.clear();
            }
            else {
                cur += ch;
            }
        }
        ans.push_back(move(cur));
        return ans;
    };

    vector<string> names = split(path, '/');
    vector<string> stack;
    for (string& name: names) {
        if (name == "..") {
            if (!stack.empty()) {
                stack.pop_back();
            }
        }
        else if (!name.empty() && name != ".") {
            stack.push_back(move(name));
        }
    }
    return stack;
}


int file_system::touch(string name){
    return this->creat_file(name,__IS_FILE__);
}

int file_system::rm(string name){
    if (name == "")
    {
        cout << "input a file name first!" << endl;
        return -1;
    }
    if(name.length()>11){
        cout<<"filename is too long ,please limit length to 11 bytes!"<<endl;
        return -1;
    }
    int target=find_file_pwd(name);
    if(target==-1)
    {
        cout<<"file not exist!"<<endl;
        return -1;
    }
    FILE* fp=fopen("disk","r+");
    int ret = this->remove_file(target,this->pwd_menu_inode,fp);
    save(fp);
    return ret;

}

int file_system::mkdir(string name){
    return this->creat_file(name,__IS_FOLDER__);
}

int file_system::read(string name){
    string buf;
    int res=this->read_to_s(name,buf);
    if(res!=0){
        return res;
    }
    cout<<buf<<endl;
    return 0;
}

int file_system::write(string name)
{
    if(find_file_pwd(name)==-1){
        cout<<"file not exist!"<<endl;
        return -1;
    }
    string s;
    cout << "please input your text" << endl;
    getline(cin,s);
    return this->write_from_s(name,s);
}

void file_system::ls()
{
    FILE *fp = fopen("disk", "r");
    menu temp;
    int block_iter = inode_table[this->pwd_menu_inode].first_block;
    int menu_file_size_to_search = inode_table[pwd_menu_inode].i_size;
    int blocks_to_search = inode_table[pwd_menu_inode].block_num;
//    cout<<"menu size:"<<menu_file_size_to_search<<endl;
//    cout<<"menu blocks:"<<blocks_to_search<<endl;
    while (blocks_to_search)
    {
//        cout<<"block iter:"<<block_iter<<endl;
        fseek(fp, BLOCK_OFFSET + BLOCK_SIZE * block_iter, SEEK_SET);
        for (int i = 0; i < min((BLOCK_SIZE - 4) / MENU_SIZE, menu_file_size_to_search / MENU_SIZE); ++i)
        {
            fread(&temp, MENU_SIZE, 1, fp);
            string temp_file_name = string(temp.name);
            if(inode_table[temp.inode].i_type==__IS_FILE__)
                cout<<temp_file_name<<endl;
            else
                cout  << "\033[34m"<<temp_file_name<<"\033[0m"<< endl ;
        }
        blocks_to_search--;
        if (blocks_to_search!=0)
        {
            menu_file_size_to_search -= (BLOCK_SIZE - 4);
            fread(&block_iter, sizeof(int), 1, fp);
        }
    }

    fclose(fp);
}

int file_system::cd(string dest)
{
    int old_pwd_inode=this->pwd_menu_inode;
    string old_path=this->pwd;
    if(dest.substr(0,2)== "./")
        dest=pwd+dest.substr(1);
    else if(dest.substr(0,2)==".."){
        if (pwd == "/")
            return 0;
        for (int i = pwd.length(); i >= 0; --i)
        {
            if (pwd[i] == '/')
            {
                if (i == 0) pwd = "/";
                else pwd.erase(i);
                break;
            }
        }
        dest=pwd+dest.substr(2);
    }
    else if(dest[0]!='/')
        dest=pwd+'/'+dest;
//    cout<<dest<<endl;
    vector<string> path=this->simplify_path(dest);
    this->pwd="";
//    for(string s:path){
//        cout<<s<<" ";
//    }
    cout<<endl;
    if (path.empty()) {
        this->pwd = "/";
        this->pwd_menu_inode=0;
    }
    else {
        this->pwd_menu_inode=0;
        for (string& name: path) {
            this->pwd += "/" + name;
            int temp=this->find_file_pwd(name);
            if(inode_table[temp].i_type!=__IS_FOLDER__){
                cout<<"path not exist!"<<endl;
                this->pwd=old_path;
                this->pwd_menu_inode=old_pwd_inode;
                return -1;
            }
            this->pwd_menu_inode=temp;
        }
    }
    return 0;
}

int file_system::cp(string src,string target){
//    cout<<src<<" "<<target<<endl;
    string filename=src;
    int old_menu_inode=this->pwd_menu_inode;
    string old_pwd=this->pwd;
    bool is_file_in_pwd=true;
    for (int i = src.length(); i >= 0; --i)
    {
        if (src[i] == '/')
        {
            is_file_in_pwd=false;
            filename=src.substr(i+1);
            src.erase(i);
            break;
        }
    }
    if(!is_file_in_pwd){
        if(this->cd(src)!=0){
            cout<<"open source file failed!"<<endl;
            return -1;
        }
    }
    string content;
    if(this->read_to_s(filename,content)!=0){
        cout<<"open source file failed!"<<endl;
        return -1;
    }
//    cout<<content<<endl;
    this->pwd=old_pwd;
    this->pwd_menu_inode=old_menu_inode;
    filename=target;
    is_file_in_pwd=true;
    for (int i = src.length(); i >= 0; --i)
    {
        if (target[i] == '/')
        {
            is_file_in_pwd=false;
            filename=target.substr(i+1);
            target.erase(i);
            break;
        }
    }
    if(!is_file_in_pwd){
        if(this->cd(target)!=0){
            cout<<"open source file failed!"<<endl;
            return -1;
        }
    }
    if(this->touch(filename)!=0){
        cout<<"create target file failed!"<<endl;
        return -1;
    }
    if(this->write_from_s(filename,content)!=0)
    {
        cout<<"open target file failed!"<<endl;
        return -1;
    }
    this->pwd=old_pwd;
    this->pwd_menu_inode=old_menu_inode;
    return 0;
}

void file_system::start(){
    system("clear");
    cout<<"Welcome to Yizumi File System,input \"help\" to get the usage of the system"<<endl;
    while (1)
    {
        cout << endl;
        cout << "\033[32m"<<this->user<<"@YizumiFileSystem\033[0m"<<":"<< "\033[34m"<<pwd<<"\033[0m" << "$ ";
        string order;
        string opt = "";
        getline(cin, order);
        if (order == "") continue;
        int tempLoc = -1;
        int len=order.length();
        for (int i = 0; i < len; ++i)
            if (order[i] == ' ')
            {
                tempLoc = i;
                break;
            }
            else opt += order[i];

        string temp = "";
        if (opt == "touch")
        {
            if (tempLoc != -1)
                temp = order.substr(tempLoc + 1, order.length() - tempLoc);
            touch(temp);
        }
        else if(opt=="mkdir"){
            if (tempLoc != -1)
                temp = order.substr(tempLoc + 1, order.length() - tempLoc);
            mkdir(temp);
        }
        else if (opt == "rm")
        {
            if (tempLoc != -1)
                temp = order.substr(tempLoc + 1, order.length() - tempLoc);
            rm(temp);
        }
        else if (opt == "read")
        {
            if (tempLoc != -1)
                temp = order.substr(tempLoc + 1, order.length() - tempLoc);
            read(temp);
        }
        else if (opt == "write")
        {
            if (tempLoc != -1)
                temp = order.substr(tempLoc + 1, order.length() - tempLoc);
            write(temp);
        }
        else if (opt == "cp")
        {
            if (tempLoc == -1)
                cout << "cp: missing file operand" << endl;
            else
            {
                int _tempLoc = -1;
                for (int i = tempLoc + 2; i < len; ++i)
                    if (order[i] != ' ' && order[i - 1] == ' ')
                    {
                        _tempLoc = i - 1;
                        break;
                    }
                if (_tempLoc == -1)
                    cout << "cp: missing file operand" << endl;
                else
                {
                    string tempS = order.substr(tempLoc + 1, _tempLoc - tempLoc - 1);
                    string tempT = order.substr(_tempLoc + 1, order.length() - _tempLoc);
                    cp(tempS, tempT);
                }
            }
        }
        else if (opt == "ls")
        {
            ls();
        }
        else if (opt == "cd")
        {
            if (tempLoc == -1)
            {
                pwd = "/";
                this->pwd_menu_inode = 0;
            }
            else
            {
                if (tempLoc != -1)
                    temp = order.substr(tempLoc + 1, order.length() - tempLoc);
                cd(temp);
            }
        }
        else if (opt == "exit")
        {
                break;
        }
        else if (opt == "help")
        {
            help();
        }
        else if(opt == "d"){
            if (tempLoc != -1)
                temp = order.substr(tempLoc + 1, order.length() - tempLoc);
            debug(temp);
        }
        else
        {
            cout << opt << ": command not found" << endl;
        }
    }
    cout << endl;
}

void file_system::debug(string name){
    cout<<this->free_nblock<<" "<<MAX_BLOCK_NUM<<endl;
    cout<<this->free_ninode<<" "<<MAX_FILE_NUM<<endl;
    cout<<"pwd info:"<<endl;
    cout<<"inode:"<<this->pwd_menu_inode<<endl;
    cout<<"first block:"<<inode_table[pwd_menu_inode].first_block<<endl;
    cout<<"last block:"<<inode_table[pwd_menu_inode].last_block<<endl;
    cout<<"top 20 block"<<endl;
    for(int i=0 ; i<20;i++){
        cout<<block_used[i]<<" ";
    }
    cout<<endl;
    cout<<"file "<<name<<" :"<<endl;
    int index=find_file_pwd(name);
    if(index==-1)   cout<<"not exist"<<endl;
    else{
        cout<<"type:"<<inode_table[index].i_type<<endl;;
        cout<<"first block:"<<inode_table[index].first_block<<endl;
        cout<<"block number:"<<inode_table[index].block_num<<endl;
        cout<<"size:"<<inode_table[index].i_size<<endl;
    }
}
