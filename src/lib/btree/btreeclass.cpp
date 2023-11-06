#include "btreeclass.h"
namespace ZC
{

//普通构造函数
Btree::Btree()
{
    //初始化root
    root=new BTNODE;
    root->father=nullptr;
    root->nKeys=1;
    root->isLeaf=1;
    for(int i=0;i<MAX*2;i++)    root->key[i]=0;
    for(int i=0;i<MAX*2+2;i++)  root->child[i]=nullptr;
    //初始化poi
    poi=nullptr;
}
//析构函数
Btree::~Btree()
{
    deleteNode(root);
}
//插入函数
void Btree::insert(int val)
{
    root=btreeinsert(root,val);
}
//查找函数
bool Btree::search(int val)
{
    btreesearchkey *temp=new btreesearchkey{nullptr,-1};
    *temp=btreesearch(root,val);
    if(temp->key!=-1)
    {
        poi=temp->node;
        delete temp;
        return true;
    }
    else
    {
        poi=nullptr;
        delete temp;
        return false;
    }
    

}
//打印函数
void Btree::printTree()
{
    printBtNode(root,0);
}
//删除特定值
void Btree::deleteKey(int val)
{
    btreedelete(root,val);
}
//删除节点
void Btree::deleteNode(BTNODE *node)
{
    using std::cout,std::endl;
    for(int i=0;i<node->nKeys;i++)
        if(node->child[i]!=nullptr)
            deleteNode(node->child[i]);
            
    //输出提示消息
    cout<<" $$ "<<endl;
    for(int i=0;i<node->nKeys;i++)
        cout<<node->key[i]<<" ";
    cout<<endl<<" $$ "<<"has deleted."<<endl<<endl;

    delete node;
}

}