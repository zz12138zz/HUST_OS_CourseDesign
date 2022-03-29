#ifndef DEF_H
#define DEF_H

#include<cstring>
#define MAX_FILE_NUM 65536
#define MAX_BLOCK_NUM 196000
//#define BLOCK_SIZE 516
#define BLOCK_SIZE 36
#define __IS_FOLDER__ 1
#define __IS_FILE__ 0
#define __ONLY_OWNER__ 0
#define __EVERYONE__ 1
typedef struct inode
{
    char i_uid[44];  //owner of the file
    int i_size;     //size of the file
    int i_mode;     //0:only owner 1:everyone
    int first_block;
    int last_block;
    bool i_type;    //file:0,folder:1
    int block_num
;    inode():i_size(-1),i_mode(-1),first_block(-1),last_block(-1),i_type(0),block_num(0){
    }
}inode;
typedef struct menu{
    char name[12];
    int inode;
    menu():inode(-1){
        memset(name,0,sizeof(name));
    }
    menu(const char *s,int n){
        int i=0;
        for( ; i<12&&s[0]!='\0';i++)
            name[i]=s[i];
        name[i]='\0';
        inode=n;
    }
}menu;
#endif // DEF_H
