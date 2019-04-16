%{
#include <stdio.h>
#include <string.h>
extern FILE *yyin;
extern int lineNum;
int ErrorRecovered = 0;
char message[100];

int yyerror(char *str);
%}


%start Start 
%token ID NUM RELOP ADDOP MULOP ASSIGN NOT SQRBO SQRBC STRBO STRBC END NEWLINE IF FOR ELSE WHILE RETURN REPEAT UNTIL TYPE MAIN CO CC COMM INR

%% 				
		
Start			: Stmt_list END
				;			
				
Stmt_list 		: Stmt {strcpy(message, "Missing expression!");}
				| Stmt_list END Stmt {strcpy(message,"It's not the last line of the file!");}
				;

Stmt	  		: Variable ASSIGN Expression {strcpy(message,"Variable or expression missing. Cannot assign anything!");}
				| F
				| SelectStmt {strcpy(message,"Error in the if statement!");}
				| Declaration {strcpy(message,"Error in the declaration statement!");}
				| ReturnStmt  {strcpy(message,"Error in the return statement!");}
				| FORStmt {strcpy(message,"Error in the for statement!");}
				| WHILEStmt {strcpy(message,"Error in the while statement!");}
				;

FORStmt			: FOR STRBO ID ASSIGN Expression END ID RELOP Expression END ID Inr STRBC CO Stmts CC Stmt;
WHILEStmt               : WHILE STRBO Expression STRBC CO Stmts CC Stmt;
Inr 			: INR ;

ReturnStmt             :  RETURN Z ;
Z                      : ID | NUM  ;
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

C			: ELSE CO Stmts CC {strcpy(message,"Error in the else statement!");}
			| empty 
			;

F			: TYPE MAIN STRBO STRBC CO Stmts CC {strcpy(message,"Error in the main statement!");}
				;

Variable  		: ID {strcpy(message,"Expecting something else!");}
				| ID SQRBO Expression SQRBC {strcpy(message,"'[' or ']' missing OR expression not found!");}
				;

Expression		: Simple_expression {strcpy(message,"Missing expression!");}
				| Simple_expression RELOP Simple_expression  {strcpy(message,"Conditional operation cannot be done");}
				;

Simple_expression	: Term {}
				| Simple_expression ADDOP Term {strcpy(message,"Additive operation cannot be done");}
				;

Term			: Factor {}
				| Term MULOP Factor {strcpy(message,"Multiplicative operation cannot be done!");}
				; 

Factor			: ID {strcpy(message,"Expecting something else!");}
				| NUM {strcpy(message,"Unrecognized number format!");}
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
    yyin=fopen("input.txt","r");
    yyparse();
    fclose(yyin);
	
    if(ErrorRecovered==0) printf("Success!\n");

    return 0;
}


int yyerror(char *str)
{
				if(ErrorRecovered==0){
					{
					
					
						printf("Error Found @ line #%d: ", lineNum+1);
						if(strcmp(str,"Invalid character")==0 || strcmp(str,"Identifier greater than 5 characters")==0)						
							printf("%s!", str);
						else if(strlen(message))
						printf("%s\n",message);
						else printf("%s\n", str);
					}
					printf("\n");
					ErrorRecovered = 1;

				}
		        
}
