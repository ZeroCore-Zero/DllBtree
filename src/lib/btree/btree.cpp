#include <stdio.h>
#include <malloc.h>
#include "btree.h"

struct btreesearchkey btreesearch(struct BTNODE* root,int val){
	/*b树查找函数，未找到时返回值为-1*/
	struct btreesearchkey bKey = {NULL,-1};
	int i;
	for(i=0;i<root->nKeys;i++){
		if(val == root->key[i]){
			bKey.node = root;
			bKey.key = i;
			break;
		}
		if(val < root->key[i]){
			root = root->child[i];
			i = -1;
		}
		if(i==(root->nKeys-1) && val>root->key[i]){
			root = root->child[i+1];
			i = -1;
		}
	}
	return bKey;
}
struct BTNODE* btreesplit(struct BTNODE* root,struct BTNODE* pnode){
	/*b树分裂函数，大致分为建立新节点，分配数据，认父三个环节*/
	/*定义新节点*/
	struct BTNODE* qnode = (struct BTNODE*)malloc(sizeof(struct BTNODE));

	/*定义pq的父节点*/
	struct BTNODE* gnode;

	/*如果p是root节点，则更新root节点*/
	if(pnode->father == NULL){
		gnode = (struct BTNODE*)malloc(sizeof(struct BTNODE));
		gnode->father = NULL;
		gnode->isLeaf = 0;
		gnode->nKeys = 0;
		pnode->father = gnode;
		root =  gnode;
	}
	else{
		gnode = pnode->father;
	}

	/*给g加入新键值以分割p，q节点*/
	/*寻找新键值插入点*/
	int i = 0;
	for(i=0;i<gnode->nKeys;i++){
		if(gnode->key[i]>pnode->key[MAX-2]){
			break;
		}
	}
	/*后移插入点后的键值和子节点*/
	for(int j=gnode->nKeys;j>i;j--){
		gnode->key[j] = gnode->key[j-1];
	}
	for(int j=gnode->nKeys;j>i;j--){
		gnode->child[j+1] = gnode->child[j];
	}
	/*写入键值,为q认父并更新键数*/
	/*将p中溢出的区间分给q*/
	gnode->child[i+1] = qnode;
	for(int r=MAX;r<2*MAX-1;r++){
		qnode->key[r-MAX] = pnode->key[r-1];
	}
	for(int r=MAX;r<2*MAX;r++){
		qnode->child[r-MAX] = pnode->child[r-1];
	}
	qnode->isLeaf = 1;
	gnode->key[i] = pnode->key[MAX/2];
	pnode->key[MAX] = 0;
	gnode->nKeys++;
	qnode->nKeys = MAX/2;
	pnode->nKeys = MAX/2;
	qnode->father = gnode;
	gnode->child[i] = pnode;
	if(gnode->nKeys>MAX){
    	root=btreesplit(root,gnode);
	}
    return root;
}
struct BTNODE* btreeinsert(struct BTNODE* root,int val){
	struct BTNODE* oriroot = root;
	int i = 0;
	while (root->isLeaf!=1)
	{
		i = 0;
		while (i<root->nKeys && val>root->key[i])
		{
			i++;
		}
		root = root->child[i];
	}
	i = 0;
	while (i<root->nKeys)
	{
		if(root->key[i]>val){
			break;
		}
		i++;
	}
	for(int j=root->nKeys;j>i;j--){
		root->key[j]=root->key[j-1];
	}
	root->key[i] = val;
	root->nKeys++;
	if(root->nKeys>MAX){
		oriroot = btreesplit(oriroot,root);
	}
	printf("%d is inserted successfully",val);
	return oriroot;
}
//合并相邻的子节点
void btreemergenode(struct BTNODE* root,struct BTNODE* target1,struct BTNODE* target2){
	int i;
	for(i = 0;i<target2->nKeys;i++){
		target1->key[target1->nKeys+i+1] = target2->key[i];
		target1->child[target1->nKeys+i+1] = target2->child[i];
	}
	target1->child[target1->nKeys+i+1] = target2->child[i];
	if(target1->child[target1->nKeys]!=NULL && target1->child[target1->nKeys+1] != NULL){
		btreemergenode(root,target1->child[target1->nKeys],target1->child[target1->nKeys+1]);
	}
	for(i=0;i<target2->nKeys;i++){
		target1->key[target1->nKeys+i] = target1->key[target1->nKeys+i+1];
		target1->child[target1->nKeys+i+1] = target1->child[target1->nKeys+i+2];
	}
	target1->nKeys = target1->nKeys + target2->nKeys;
	free(target2);
	if(target1->nKeys>MAX){
		btreesplit(root,target1);
	}
}
//B树删除函数
void btreedelete(struct BTNODE* root,int val){
	struct btreesearchkey result = btreesearch(root,val);
	result.node->key[result.key] = 0;
	result.node->nKeys--;
	if(result.node->child[result.key]!=NULL&&result.node->child[result.key+1]!=NULL){
		//如果有子节点，则取左区最大键值作为替代，并合并两个子节点为一个超级节点(大小为普通节点的两倍)，中间区域持续合并至结束
		btreemergenode(root,result.node->child[result.key],result.node->child[result.key+1]);
	}
}
//打印B树
void printBtNode(struct BTNODE* root, int n){
    printf("the %dth has %d keys:",n,root->nKeys);
    for (int i = 0; i < root->nKeys; i++)
        printf("%d,",root->key[i]);
    printf("\n");
    if (root->isLeaf)
        return;
    for (int i = 0; i < root->nKeys+1; i++){
        printBtNode(root->child[i],n+1);
    }
}