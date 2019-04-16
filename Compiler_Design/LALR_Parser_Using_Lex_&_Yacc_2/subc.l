%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"
void yyerror(char *);
extern int cost;
char identifier[50][50];
int total_id = 0;
int lineNum = 0;
int sb=0,lg=0,bg=0;
int variable=0,total_var=0;
char datatype[20];
int nowcheck=0;
FILE *out,*sy;
int st=0;
char numType[20][20];
int num = 0,n=0;
int er=0;
char stab[20][20];
struct table
{
	char type[20];
	char a[20];
	int s;
}var[100];


%}
digit  [0-9]
letter [a-zA-Z]
mulop	[*/%]
addop	[+-]
white [ \t]+


%%{
	if(st==0)
	{

		out=fopen("output.txt","w");
		sy=fopen("symbol.txt","w");
		fprintf(out,"------Tokens------\n");
		fprintf(sy,"-----------------Symbol Table-----------------\n\n\n");
		fprintf(sy,"----------------------------------------------\n");
		fclose(out);
		fclose(sy);
		st=1;
	}

"if" {
	out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return IF;

}
"else" {
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);

return ELSE;
}
"while" {
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return WHILE;
}
"for" {

out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return FOR;
}
"repeat" {
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return REPEAT;
}
"until" {
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return UNTIL;
}
"return" {
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return RETURN;
}
"main" {
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return MAIN;
}
int|char|double|long|float {

out = fopen("output.txt","a");

		variable=1;
		strcpy(datatype,yytext);




			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return TYPE;
}


{letter}({letter}|{digit}|"_")({letter}|{digit}|"_")({letter}|{digit}|"_")({letter}|{digit}|"_")({letter}|{digit}|"_")+ {

{yyerror("Identifier greater than 5 characters");
}

}

{letter}({letter}|{digit}|"_")?({letter}|{digit}|"_")?({letter}|{digit}|"_")?({letter}|{digit}|"_")?		{
	    int i;
	    int flag=0;
		sy=fopen("symbol.txt","a");
		for(i=0;i<total_var;i++)
		{
			if(strcmp(var[i].a,yytext)==0)
			{
			//printf("%s\t%s\n",var[i].a,var[i].type);
			strcpy(stab[num],var[i].type);
			num++;

	}
		}
	out = fopen("output.txt","a");
		
	    for (i = 0; i<total_id; i++)
	    {
		if (strcmp(identifier[i], yytext)==0)
		 {
		     flag=1;
		     break;
		 }
	    }
			if(flag==0 && strlen(datatype)==0)
			{
				yyerror("Variable is not declared earlier!!");
			}
	else if (flag==0 && strlen(datatype)>0){
	    if(variable==1)
	    {
	    	strcpy(var[total_var].type,datatype);
	    	strcpy(var[total_var].a,yytext);
	    	if(strcmp(datatype,"int")==0)
	    	var[total_var].s=sizeof(int);
	    	else if(strcmp(datatype,"char")==0)
	    	var[total_var].s=sizeof(char);
	    	else if(strcmp(datatype,"long")==0)
	    	var[total_var].s=sizeof(long);
	    	else if(strcmp(datatype,"double")==0)
	    	var[total_var].s=sizeof(double);
		else if(strcmp(datatype,"float")==0)
	    	var[total_var].s=sizeof(float);
	    	fprintf(sy,"%s\t|\t%s\t|\t%d\t|\n",var[total_var].type,var[total_var].a,var[total_var].s);
	    	total_var++;

	    }
}
if(variable==1 && flag==1)
{
	printf("WARNING : %s is already declared!!\n",yytext);
}

	    if(flag==0)
	     {
			if(total_id==0) puts("");

			strcpy(identifier[total_id++],yytext);

	     }
	     fprintf(out,"%s\n", yytext);
fclose(out);
fclose(sy);
		return ID;

    }


{digit}+|({digit}+("."){digit}+)   	{
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);
		int fx=0;
	     for(int i=0;i<strlen(yytext);i++)
	{
	if(yytext[i]=='.')
	{
	fx=1;
	break;
}
}
if(fx==1)
{
	strcpy(numType[n++],"float");
}
else strcpy(numType[n++],"int");
	   fprintf(out,"%s\n", yytext);
fclose(out);
return NUM;
}
"=="|">="|"<="|">"|"<"|"!="		{
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	     fprintf(out,"%s\n", yytext);
fclose(out);
return RELOP;
}
{addop}|("||") 				{
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return ADDOP;
}

{mulop}|("&&") 				{
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return MULOP;
}
"="				{
out = fopen("output.txt","a");
	nowcheck=1;

			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return ASSIGN;
}
";"					{

int check=0,error=0;

if(nowcheck==1)
{

if(strcmp(stab[0],"int")==0)
check=1;
if(strcmp(stab[0],"float")==0)
check=2;

if(check==1)
{
for(int i=1;i<num;i++)
{
	//printf("\n%s\n",stab[i]);
	if(strcmp(stab[i],"float")==0 || strcmp(stab[i],"long")==0 || strcmp(stab[i],"double")==0 || strcmp(stab[i],"char")==0)
	{
error=1;
}
}

for(int i=0;i<n;i++)
{
	if(strcmp(numType[i],"float")==0)
{
	error=1;
}
}
}
if(check==2)
{
	for(int i=1;i<num;i++)
	{
		if(strcmp(stab[i],"long")==0 || strcmp(stab[i],"double")==0)
			error=1;
	}
}
}
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
for(int i=0;i<20;i++)
{
for(int j=0;j<20;j++)
{
	numType[i][j]='\0';
	stab[i][j]='\0';
}
}
variable=0;
nowcheck=0;
num=0;
n=0;
strcpy(datatype,"");
if(error==1)
{
	yyerror("Type mismatch");
}
					return END;
				}
"!"					{
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return NOT;
}
"["					{
out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
bg++;
					return SQRBO;
				}
","					{
			out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
return COMM;
}
"]"					{
			out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
bg--;
return SQRBC;
}
"("					{
			out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
sb++;
return STRBO;}
")"					{
			out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
sb--;
return STRBC;
}
"{"					{
			out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
lg++;
return CO;
}
"}"					{
			out = fopen("output.txt","a");


			strcpy(identifier[total_id++],yytext);


	    fprintf(out,"%s\n", yytext);
fclose(out);
lg--;
return CC;
}
"\n"				{lineNum++;}
[._]+				{yyerror("Invalid character");}
[ \t]+;
%%
