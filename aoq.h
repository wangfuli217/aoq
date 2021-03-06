#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _INCLUDE_PARSER_H 
#define _INCLUDE_PARSER_H 1  
#include "parser.h"
#endif


typedef struct _qnode
{
	unsigned int uniqid;
	struct _arg *arg;
	struct _qnode *next;
}Qnode;

typedef struct _aoq
{
	char *name;
	int total;
	struct _qnode *head;
	struct _qnode *tail;
}AOQ;

AOQ * createQueue(char *qname);
int pushQueue(AOQ *aoq, Qnode *qnode);
int popQueue(AOQ *aoq, Qnode **qnode);
int deleteQueue(AOQ *aoq);
Qnode * createQnode(Arg *arg);
AOQ * getQueue(char *qname, HashTable *ht, void **result);