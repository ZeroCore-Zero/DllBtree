#ifndef BTREE_H_
#define BTREE_H_

// #ifdef __cplusplus
// extern "C" {
// #endif

#define MAX 4
//数组形式的B树节点
struct BTNODE{
    struct BTNODE* father;          //父节点指针
    int nKeys;                      //已有的总键值数
    int key[2*MAX];                 //键值
    struct BTNODE* child[2*MAX+2];  //子节点指针组
    int isLeaf;                     //判定是否为末代节点
};
struct btreesearchkey{
	struct BTNODE * node;
	int key;
};
//b树查找函数，未找到时返回值为-1
struct btreesearchkey btreesearch(struct BTNODE* root,int val);
//b树分裂函数
struct BTNODE* btreesplit(struct BTNODE* root,struct BTNODE* pnode);
//b树插入函数
struct BTNODE* btreeinsert(struct BTNODE* root,int val);
//合并相邻的子节点
void btreemergenode(struct BTNODE* root,struct BTNODE* target1,struct BTNODE* target2);
//B树删除函数
void btreedelete(struct BTNODE* root,int val);
//打印B树
void printBtNode(struct BTNODE* root, int n);

// #ifdef __cplusplus
// }
// #endif

#endif