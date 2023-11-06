#include <stdio.h>
#include <stdlib.h>
#include "chainchart.h"
/*数据类型修改: 在header文件中修改对tartype的定义(默认为double)*/

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
struct ccnode* ccnodecreate(tartype val)
{
    struct ccnode* root = (struct ccnode*)malloc(sizeof(struct ccnode));
    root->data =val;
    return root;
}
struct ccnode* ccnodeinsert(struct ccnode* root,int tar,tartype val)
{
    struct ccnode* newnode = (struct ccnode*)malloc(sizeof(struct ccnode));
    struct ccnode* proot = root;
    newnode->data = val;
    if(tar == 0){
        newnode->p[0] = proot;
        if(proot->p[1] != NULL){
            proot->p[1]->p[0] = newnode;
            newnode->p[1] = proot->p[1];
            proot->p[1] = newnode;
        }
        else{
            proot->p[1] = newnode;
        }
    }
    else{
        newnode->p[1] = proot;
        if(proot->p[0] != NULL){
            proot->p[0]->p[1] = newnode;
            newnode->p[0] = proot->p[0];
            proot->p[0] = newnode;
        }
        else{
            proot->p[0] = newnode;
        }
    }
    return newnode;
}
struct ccnode* ccnodedelete(struct ccnode** root,tartype val){
    struct ccnode* target = ccnodesearch(*root,val);
    if(target->p[1]==NULL && target->p[0] == NULL){
        free(target);
        *root = NULL;
    }
    else if (target->p[0] == NULL)
    {
        *root = target->p[1];
        target->p[1]->p[0] = NULL;
        free(target);
    }
    else if (target->p[1] == NULL){
        target->p[0]->p[1] == NULL;
        free(target);
    }
    else{
        target->p[0]->p[1] = target->p[1];
        target->p[1]->p[0] = target->p[0];
        free(target);
    }
    return target;
    
}
tartype ccnodeforeach(struct ccnode* root,int stat,tartype r[]){
    struct ccnode* oriroot = root;
    int i = 0;
    if(stat == 0){
        do
        {
            r[i] = root->data;
            i++;
            root = root->p[1];
        } while (root!=NULL);
        return 0;
    }
    else{
        do
        {
            r[i] = root->data;
            i++;
            root = root->p[1];
        } while (root!=oriroot);
        return 0;
    }

}
struct ccnode* ccnodesearch(struct ccnode* root,tartype val){
    struct ccnode* pointer = root;
    do
    {
        if(val == pointer->data){
            break;
        }
        pointer = pointer->p[1];
    } while (pointer != root || pointer != NULL);
    return pointer;
}
struct ccnode* ccnodereround(struct ccnode* root,struct ccnode* end){
    if(end == NULL){
        end = root;
        while (end->p[1]!=NULL){
            end = end->p[1];
        }
    }
    if(end == root){
        return NULL;
    }
    else{
        end->p[1] = root;
        root->p[0] = end;
        return root;
    }
}
struct ccnode* ccnodeunround(struct ccnode* root,tartype key){
    struct ccnode* target = ccnodesearch(root,key);
    target->p[0]->p[1] = NULL;
    target->p[0] = NULL;
    return target;
}
struct ccnode* ccnodeclear(struct ccnode* root){
    struct ccnode* oriroot = root;
    do
    {
        root->data = 0;
        root = root->p[1];
    } while (root!=NULL || root != oriroot);
    return oriroot;
}
void ccnodedestory(struct ccnode* root){
    while(root->p[1] != NULL){
        root = root->p[1];
        free(root->p[0]);
    }
    free(root);
}