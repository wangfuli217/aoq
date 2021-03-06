#ifndef _INCLUDE_PARSER_H 
#define _INCLUDE_PARSER_H 1  
#include "parser.h"
#endif

int parse_comman_num(ChunkCursor *cursor)
{
    char *command_num_str = (char *)calloc(2, sizeof(char));
    int command_num = 0;
    memcpy(command_num_str, *(cursor->ptr), 2);
    moveCursor(cursor, 2);
    command_num =  atoi(command_num_str);
    free(command_num_str);
    command_num_str = NULL;
    return command_num;
}

int parse_head_len(ChunkCursor *cursor)
{
    char *head_len_str = (char *)calloc(2, sizeof(char));
    int head_len = 0;
    memcpy(head_len_str, *(cursor->ptr), 2);
    moveCursor(cursor, 2);
    head_len =  atoi(head_len_str);
    free(head_len_str);
    head_len_str = NULL;
    return head_len;
}

int parse_argn(ChunkCursor *cursor, int * argn)
{

    char *argn_str = (char *)malloc(7*sizeof(char));
    memset(argn_str, '\0', 7);
    char *p = *(cursor->ptr);
    int i = 0;

    while(i <5 && *p != '\0')
    {
        if(*p != ' ')
        {
            memcpy(argn_str, p, 6);
            argn[i++] = atoi(argn_str);
            p += 6;
        }else{
            p++;
            break;
        }
    }
    *(cursor->ptr) = p;
    free(argn_str);
    argn_str = NULL;
    return 1;
}

int parse_argv(int len, ChunkCursor *cursor, Arg *arg)
{
    arg->cursor = createCursor();
    *(arg->cursor->ptr) = *(cursor->ptr);
    arg->cursor->node = cursor->node;
    arg->cursor->slab = cursor->slab;
    arg->len = len;
    moveCursor(cursor, len);
    return 1;
}


int parse_args(MemSlab *memslab, int * command_num, Arg *args)
{

    ChunkCursor *cursor = createCursor();

    int argn[5] = {-1,-1,-1,-1,-1};
    
    *(cursor->ptr)= memslab->head->next->chunk;

    cursor->node = memslab->head->next;
    cursor->slab = memslab;

    int head_len = parse_head_len(cursor);

    *command_num = parse_comman_num(cursor);
    
    
    if(head_len <=0 || *command_num <=0 || *command_num > 6)
    {
        freeMemSlab(memslab);
        freeCursor(cursor);
        return -1;
    }
    

    parse_argn(cursor, argn);
    
    int i = 0;
    while(i < 5 && argn[i] >0)
    {
        parse_argv(argn[i++], cursor, args++);
    }
    
    
    if(i == 0)
    {
        freeMemSlab(memslab);
		freeCursor(cursor);
		return 0;
    }
    
    freeCursor(cursor);

    return 1;
}

Arg *createArgs(int num)
{
    Arg *args = (Arg *)malloc(num*sizeof(Arg));
    Arg *a = args;
	int i = 0;
    for(i = 0; i < num; i++)
    {
        a->cursor = NULL;
        a->len = 0;
        a++;
    }
	return args;
}


int freeArgs(Arg *args)
{
    int i = 0;
    if(args == NULL)
    {
        return 0;
    }
    
    Arg *a = args;  
    if( a->cursor !=NULL && a->cursor->slab != NULL)
    {

        freeMemSlab(a->cursor->slab);
        
    }
    

    for(i=0; i<5; i++){
        
        if( a->cursor !=NULL)
        {
        
            if(*(a->cursor->ptr) != NULL)
            {
                *(a->cursor->ptr) = NULL;
                a->cursor->ptr = NULL;
            }
            
                
            freeCursor(a->cursor);
            a->cursor = NULL;
        }
        a++;
    }
    
    
    free(args);
    args = NULL;
    return 1;
    
}


