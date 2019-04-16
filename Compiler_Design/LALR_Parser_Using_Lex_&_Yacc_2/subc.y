%{
#include <stdio.h>
#include <string.h>
extern FILE *yyin;
FILE *fp;
extern int lineNum;
int ErrorRecovered = 0;
char message[100];
int tcost=0,i=0;

int yyerror(char *str);
%}


%start Start
%token ID NUM RELOP ADDOP MULOP ASSIGN NOT SQRBO SQRBC STRBO STRBC END NEWLINE IF FOR ELSE WHILE RETURN REPEAT UNTIL TYPE MAIN CO CC COMM

%%

Start			: Stmt_list END{}
				;

Stmt_list 		: Stmt {$$=$1;strcpy(message, "Missing expression!");}
				| Stmt_list END Stmt  {$$ = $1+$3;strcpy(message,"It's not the last line of the file!");}
				;

Stmt	  		: Variable ASSIGN Expression {tcost +=5; $$ = 5 + $3;if(ErrorRecovered!=1){printf("line %d - Cost = %d\n",lineNum,$$);fprintf(fp,"line %d - Cost = %d\n",lineNum,$$);} strcpy(message,"Variable or expression missing. Cannot assign anything!");}
				| F END Stmt
				| SelectStmt
				| Declaration END Stmt
				;

Declaration		: TYPE X;

X 			: ID X
			| empty
			| COMM X
			;

empty			: ;

SelectStmt		: IF STRBO Expression STRBC CO Stmts CC C Stmt;

Stmts			: Stmt END Stmts
			| empty
			;

C			: ELSE CO Stmts CC
			| empty
			;

F			: TYPE MAIN{strcpy(message,"\"main\" error");}
				;

Variable  		: ID {strcpy(message,"Expecting something else!");}
				| ID SQRBO Expression SQRBC {strcpy(message,"'[' or ']' missing OR expression not found!");}
				;

Expression		: Simple_expression {$$ = $1;strcpy(message,"Missing expression!");}
				| Simple_expression RELOP Simple_expression  {strcpy(message,"Conditional operation cannot be done");}
				;

Simple_expression	: Term {$$ = $1;}
				| Simple_expression ADDOP Term {tcost+=9; $$ = $1 + $3 + 9;strcpy(message,"Additive operation cannot be done");}
				;

Term			: Factor {$$ = $1;}
				| Term MULOP Factor {tcost+=12; $$ = $1 + $3  + 12;strcpy(message,"Multiplicative operation cannot be done!");}
				;

Factor			: ID {tcost+=3; $$ = 3;strcpy(message,"Expecting something else!");}
				| NUM {tcost+=3; $$ = 3; strcpy(message,"Unrecognized number format!");}
				| STRBO Expression STRBC {strcpy(message,"'(' or ')' missing OR expression not found!");}
				| ID SQRBO Expression SQRBC {strcpy(message,"'[' or ']' missing OR ID not found!");}

				;


%%

int yywrap()
{

        return 1;
}

int main()
{
    yyin=fopen("semantic_yacc_input.txt","r");
    fp = fopen("cost.txt","w");
    yyparse();
    fclose(yyin);
    fprintf(fp,"Total cost = %d\n",tcost);
    fclose(fp);
    if(ErrorRecovered==0) printf("Success!\n");
    return 0;
}


int yyerror(char *str)
{



						printf("Error Found @ line #%d: ", lineNum+1);
						if(strcmp(str,"Invalid character")==0 || strcmp(str,"Identifier greater than 5 characters")==0)
							printf("%s!", str);
						else if (strlen(str)) printf("%s\n", str);
						else
						printf("%s\n",message);


					printf("\n");
					ErrorRecovered = 1;



}
