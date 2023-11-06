#ifndef BTREECLASS_H_
#define BTREECLASS_H_

#include "btree.h"
#include<iostream>

namespace ZC
{

class Btree
{
    private:
        BTNODE *root;       //B树根节点
        BTNODE *poi;        //search()可能会用到的位置指针
        void deleteNode(BTNODE *);
    public:
        Btree();
        ~Btree();
        void insert(int);   //B树插入函数
        bool search(int);   //B树查找函数，返回查找是否成功，若成功则修改poi使其指向节点
        void printTree();   //打印B树
        void deleteKey(int);//删除B树特定值
};

}
#endif