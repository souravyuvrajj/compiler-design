#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int size=0;
void Insert(char var[],char type[]);
void Display();
int Search(char var[]);


struct SymbTab
{
 char var[100],type[100];
 int size;
struct SymbTab *next;
};

struct SymbTab *first,*last;

void Insert(char var[],char type[])
{
  int n;
  char l[100];
  strcpy(l,var);
  n=Search(l);
  if(n==1);
   //printf("\n\tThe label exists already in the symbol table\n\tDuplicate can't be inserted");
  else
   {
    struct SymbTab *p;
    p=malloc(sizeof(struct SymbTab));
    strcpy(p->var,l);
    strcpy(p->type,type);
    if(strcmp(type,"int")==0){
	p->size = 2;
    }else if(strcmp(type,"char")==0){
	p->size = 1;
    }else if(strcmp(type,"long")==0 || strcmp(type,"double")==0 || strcmp(type,"float")==0){
	p->size = 4;
    }
    p->next=NULL;
    if(size==0)
     {
      first=p;
      last=p;
     }
    else
     {
      last->next=p;
      last=p;
     }
    size++;
   }
   //printf("\n\tLabel inserted\n");
}

void Display()
{
 
  int i;
  struct SymbTab *p;
  p=first;
  printf("\n\tVARIABLE\t\tTYPE\t\tSIZE\n");

  for(i=0;i<size;i++)
   {
    printf("\t%s\t\t%s\t\t%d\n",p->var,p->type,p->size);

    p=p->next;
   }
  
}

int Search(char lab[])
{
 int i,flag=0;
 struct SymbTab *p;
 p=first;
  for(i=0;i<size;i++)
   {
    if(strcmp(p->var,lab)==0)
     flag=1;
    p=p->next;
   }
 return flag;
}

