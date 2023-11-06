#ifndef CHAINCHART_H_
#define CHAINCHART_H_

#ifndef tartype
#define tartype double
#endif
struct ccnode
{
    struct ccnode* p[2];
    tartype data;
};
/*
函数定义:
ccnodecreate: 创建一个链表节点，传入一个定义类型的数，返回节点的指针
ccnodeinsert: 在已有链表中插入新值，传入插入点的节点指针的指针(IMPORTANT!!!!!!)、需插入的一个数据、前插或者后插(1/0)，返回新节点的指针
ccnodedelete: 在已有链表中删除指定值，传入已有链表的根节点指针的地址(IMPORTANT!!!!!!)、需删除的数据，返回被删除节点的指针
ccnodeforeach: 遍历已有链表，传入已有链表的根节点指针、该链表是否为环形链表(1为是，0为否)、用于写入数据的数组
ccnodesearch: 在已有链表中搜索数值，传入已有链表的根节点指针、需搜索的值，返回第一个满足条件的节点的指针
ccnodereround: 环化链表，传入已有链表的根节点指针、末节点指针(此项非必须，可传入空指针)，返回根节点的指针
ccnodeunround: 反环化链表，传入环状链表的根节点指针，分割key值，在第一个等于key值的节点前分割，返回根节点指针
ccnodeclear: 清空数组，将全部节点重置为0，传入根节点指针，返回根节点指针
ccnodedestory: 销毁数组，将销毁所有节点，传入根节点指针，返回0
*/
struct ccnode* ccnodecreate(tartype val);
struct ccnode* ccnodeinsert(struct ccnode* root,int tar,tartype val);
struct ccnode* ccnodedelete(struct ccnode** root,tartype val);
tartype ccnodeforeach(struct ccnode* root,int stat,tartype r[]);
struct ccnode* ccnodesearch(struct ccnode* root,tartype val);
struct ccnode* ccnodereround(struct ccnode* root,struct ccnode* end);
struct ccnode* ccnodeunround(struct ccnode* root,tartype key);
struct ccnode* ccnodeclear(struct ccnode* root);
void ccnodedestory(struct ccnode* root);
#endif