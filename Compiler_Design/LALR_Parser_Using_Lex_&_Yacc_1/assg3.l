%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assg3.tab.h"
void yyerror(char *);

char identifier[50][50];
int total_id = 0;
int lineNum = 0;
int sb=0,lg=0,bg=0;
int variable=0,total_var=0;
char datatype[20];
FILE *out,*tk;
int st=0;

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
		out=fopen("token.txt","w");
		tk=fopen("symbolTable.txt","w");
		fprintf(out,"-------------Tokens-------------\n");
		fprintf(tk,"-----------------Symbol Table-----------------\n\n\n");
		fprintf(tk,"----------------------------------------------\n");
		fclose(out);
		fclose(tk);
		st=1;
	}

"if" {
	out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return IF;

}
"else" {
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
	     
return ELSE;
}
"while" {
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return WHILE;
}
"for" {

out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return FOR;
}
"repeat" {
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return REPEAT;
}
"until" {
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return UNTIL;
}
"return" {
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return RETURN;
}
"main" {
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return MAIN;
}
int|char|double|float|long {

out = fopen("token.txt","a");
		
		variable=1;
		strcpy(datatype,yytext);

	        	 
	    
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext);
fclose(out);
return TYPE;
}

"end"    { if(sb==0 && lg==0 && bg==0)
	{
	printf("\nParanthesis are balanced!!\n");
}
else printf("ERROR: paranthesis are not balanced!!\n");
return END;
}
{letter}({letter}|{digit}|"_")({letter}|{digit}|"_")({letter}|{digit}|"_")({letter}|{digit}|"_")({letter}|{digit}|"_")+ {

{yyerror("Identifier greater than 5 characters");
}

}
	
{letter}({letter}|{digit}|"_")?({letter}|{digit}|"_")?({letter}|{digit}|"_")?({letter}|{digit}|"_")?		{
	    int i;
	    int flag=0; 
	out = fopen("token.txt","a");
	tk=fopen("symbolTable.txt","a");
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
	    	printf("\n%s\t%s\t%d\n",var[total_var].type,var[total_var].a,var[total_var].s);
		fprintf(tk,"%s\t|\t%s\t|\t%d\t|\n",var[total_var].type,var[total_var].a,var[total_var].s);
	    	total_var++;

	    }
	    for (i = 0; i<total_id; i++) 
	    {
		if (strcmp(identifier[i], yytext)==0)
		 {
		     flag=1;
		     break;
		 }
	    }
	        	 
	    if(flag==0)	
	     {
			if(total_id==0) puts("");
			
			strcpy(identifier[total_id++],yytext);
		
	     }
	     fprintf(out,"%s\n", yytext);
fclose(out);
fclose(tk); 
		return ID;
		
    }


{digit}+|({digit}+("."){digit}+) 	{
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return NUM;
} 
"=="|">="|"<="|">"|"<"|"!="		{
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return RELOP;
}
{addop}|("||")			{
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return ADDOP;
}

{mulop}|("&&") 				{
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return MULOP;
}
"="|"+="|"-="|"*="|"/="				{
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return ASSIGN;
}
";"					{
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
variable=0;
					return END;
				}
"!"					{
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return NOT;
}
"["					{
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
bg++;
					return SQRBO;
				}
","					{out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return COMM;
}
"]"					{out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
bg--;
return SQRBC;
}
"("					{out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
sb++;
return STRBO;}
")"					{out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
sb--;
return STRBC;
}
"{"					{
out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
lg++; 
return CO;
}
"}"					{out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
lg--;
return CC;
}
"++"|"--" 	{out = fopen("token.txt","a");
	
			
			strcpy(identifier[total_id++],yytext);
		
	     
	     fprintf(out,"%s\n", yytext); 
fclose(out);
return INR;}
"\n"				{lineNum++;}
[._]+				{yyerror("Invalid character");}

[ \t]+;
%%





