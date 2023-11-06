#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
void insertsort(tartype val[],int num){
    struct ccnode* root = ccnodecreate(val[0]);
    struct ccnode* pointer = root;
    for(int i = 1;i<num;i++){
        pointer = root;
        while (pointer->data<=val[i])
        {
            if(pointer->p[1]!=NULL){
                pointer = pointer->p[1];
            }
            else{
                break;
            }
        }
        if(pointer == root && pointer->data>val[i]){
            struct ccnode* rt = ccnodeinsert(pointer,1,val[i]);
            root = rt;
        }
        else if (pointer == root && pointer->data<=val[i])
        {
            struct ccnode* rt = ccnodeinsert(pointer,0,val[i]);
        }
        else if (pointer->p[1] == NULL && pointer->data<=val[i]){
            struct ccnode* rt = ccnodeinsert(pointer,0,val[i]);
        }
        else{
            struct ccnode* rt = ccnodeinsert(pointer,1,val[i]);
        }
    }
    ccnodeforeach(root,0,val);
    ccnodedestory(root);
}
void bbsort(tartype val[],int num){
    for(int i = 0;i<num;i++){
        for(int r = 0;r<num-1;r++){
            if(val[r]>val[r+1]){
                tartype temp = val[r];
                val[r] = val[r+1];
                val[r+1] = temp;
            }
        }
    }
}
// tartype shellsort(tartype val[],int num){
    
// }
void quicksort(tartype number[], int first, int last) {
	int i, j, pivot;
	int temp;
	if (first<last) {
		pivot = first;
		i = first;
		j = last;
		while (i<j) {
			while (number[i] <= number[pivot] && i<last)
				i++;
			while (number[j]>number[pivot])
				j--;
			if (i<j) {
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
			}
		}
		temp = number[pivot];
		number[pivot] = number[j];
		number[j] = temp;
		quicksort(number, first, j - 1);
		quicksort(number, j + 1, last);
	}
}