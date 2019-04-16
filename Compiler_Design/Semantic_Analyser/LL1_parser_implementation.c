#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"     // Ass-1 code to get the tokens i.e.  ( int will give type, = will give op, etc....)
#include "reverse_mapping.h"
#define MAXSIZE 50000



struct Stack
{
    char stk[MAXSIZE];
    int top;
};
typedef struct Stack Stack;
Stack s;                   // Stack named s is created.

/*void push(char s);     //    Stack
char pop(void);       //     FUNCTIONS
void display(void);  //       DECLERATION

//finds the array index of the given symbol in the given array
int get_index_of_symbol(char symbol_array[], char symbol);

//generates the parsing table when provided with the first and follow manually.
void generate_parsing_table(int no_nt,int no_t,int no_productions,char non_term[no_productions],char term[no_t],char productions[no_productions][100],char first[no_nt][no_t+1],char follow[no_nt][no_t+1], int parser[no_nt][no_t+1]);
*/


int get_index_of_symbol(char s_array[], char sym)
{
	int i, s_array_index;
	for(i=0;i<strlen(s_array);i++)
	{
		if (s_array[i] == sym)
		{
			s_array_index = i;
			return (s_array_index);
		}
	}
	return -1;
}

void generate_parsing_table(int no_nt,int no_t,int no_productions,char non_term[],char term[],
	char productions[][100],char first[][100],char follow[][100], int parser[][100])
{
	char left_nt;  //left non_terminal
	int i,j,k;  // j to keeps track of production lenght count. and i to keeps track of production no.
	char first_t, t_count;
	int first_t_index, code, left_nt_index;
	char *rule_rhs;
	char req_term[no_t+1];
	int prev_exist, does_exist, is_nullable;
	int code_index,ntc;       // ntc - non_terminal_count

	req_term[0] = '\0'; //Initially its empty
	for(i = 0;i<no_productions;i++)
	{
		req_term[0] = '\0';
		left_nt = productions[i][0];
		left_nt_index = get_index_of_symbol(non_term,left_nt);
		rule_rhs = &(productions[i][2]);
		for(j = 0;j<strlen(rule_rhs);j++)
		{
			code = (int)rule_rhs[j];
			if (code == 101)           //epsilon
			{
				strcpy(req_term,&(follow[left_nt_index][0]));       // take follow if rhs of production is epsilon
				break;
			}
			else if (!((code>=65)&&(code<=90)))         //Terminal
			{
				prev_exist= 0;does_exist = 0;
				for (prev_exist=0;prev_exist<strlen(req_term);prev_exist++)
				{
					if (code == req_term[prev_exist])
					{
						does_exist = 1;                                // If terminal is already present in req_term
					}                                                //       than does not include that terminal
				}
				if (does_exist == 0)
				{
					strncat(req_term,&(rule_rhs[j]),1);            //       else include that.
					break;
				}
			}
			else if ((code>=65) && (code<=90))      //Non-Terminal
			{
				code_index = get_index_of_symbol(non_term,rule_rhs[j]);             // if production is of
				is_nullable = 0;                                                    // type A->B
				for (k=0;k<strlen(first[code_index]);k++)                           // than it will be stored
				{                                                                   // under first(B) if B is not
					first_t = first[code_index][k];                                   // nullable else it will be
					if (first_t != 'e')                                               // stored under follow(B)
					{                                                                 // This portion implement
						prev_exist= 0;does_exist = 0;                                   // this type of scenario.
						for (prev_exist=0;prev_exist<strlen(req_term);prev_exist++)   //  .
						{                                                               //  .
							if (first_t == req_term[prev_exist])                        //  .
							{                                                            //
								does_exist = 1;                                           //
							}                                                           //
						}                                                               //
						if (does_exist == 0)                                              //
						{                                                                //
							strncat(req_term,&first_t,1);                               //
						}                                                              //
					}                                                               //
					else if (first_t == 'e')                                          //
					{                                                                   //
						is_nullable = 1;                                                //
						if(j == strlen(rule_rhs)-1)                                   //
						{                                                               //
							for (t_count=0;t_count<strlen(follow[left_nt_index]);t_count++) //
							{                                                                 //
								prev_exist= 0;does_exist = 0;                                  //
								for (prev_exist=0;prev_exist<strlen(req_term);prev_exist++) //
								{                                                            //
									if (first_t == req_term[prev_exist])                    //
									{                                                        //
										does_exist = 1;                                         //
									}                                                           //
								}                                                            //
								if (does_exist == 0)                                        //
								{                                                          //
									strncat(req_term,&(follow[left_nt_index][t_count]),1);//
								}                                                          //
							}                                                             //
						}                                                                //
					}                                                                   //
				}                                                                      //
				if (is_nullable == 0)                                                 //
				{                                                                    //
					break;                                                            //
				}                                                                  //
			}                                                                      //
		}                                                                           // ..till here.
		for (k=0;k<strlen(req_term);k++)
		{
			first_t = req_term[k];
			first_t_index = get_index_of_symbol(term,first_t);              // Store the correct production number
			parser[left_nt_index][first_t_index] = i;                       // in the parser table.
		}
	}
  parser[0][no_t-1]=1;
  // Printing The Parser Table......
	printf(ANSI_COLOR_GREEN"\n\nPrinting Parsing Table......  \n\n"ANSI_COLOR_RESET);
  printf("\t");
	for (t_count=0;t_count<no_t;t_count++)
	{
		//printf("%c\t",term[t_count]);
    get_token_of_symbol(term[t_count]);
    printf("\t");
	}
	printf("\n\n");
	for (ntc=0;ntc<no_nt;ntc++)
	{
    //printf("%c\t",non_term[ntc]);
    get_token_of_symbol(non_term[ntc]);
    printf("\t");
		for (t_count=0;t_count<no_t;t_count++)
		{
			if (parser[ntc][t_count] == -1)
			{
				printf("\t",parser[ntc][t_count]);
			}else
			{
				printf(ANSI_COLOR_GREEN"%d\t"ANSI_COLOR_RESET,parser[ntc][t_count]);
			}
		}
		printf("\n\n");
	}

}

void push (char a)
{
    if (s.top == (MAXSIZE - 1))
    {
        printf ("Stack is Full\n");
        return;
    }
    else
    {
        s.top = s.top + 1;
        s.stk[s.top] = a;
    }
    return;
}
/*  Function to delete an element from the Stack */
char pop ()
{
    char sym;
    if (s.top == - 1)
    {
        printf ("Stack is Empty\n");
        return (s.top);
    }
    else
    {
        sym = s.stk[s.top];
        s.top = s.top - 1;
    }
    return(sym);
}
/*  Function to display the status of the Stack */
void display ()
{
    int i;
    if (s.top == -1)
    {
        //printf ("Stack is empty\n");
        return;
    }
    else
    {
        printf ("Stack: ");
        for (i = 0; i <= s.top; i++)
        {
            get_token_of_symbol(s.stk[i]);
            printf (" ");
        }
    }
    printf ("\n");
}

int parse()
{
	int no_nt=0, no_t=50, no_productions=0; // # of non-terminals , terminals, productions.
	FILE *fp,*fp1; // file pointers (1st for reading grammar and 2nd for reading input C code)

	char file[20]; //to store file name.
	strcpy(file,"grammar.txt");
	//printf("Enter the file name containing grammar (Give grammar.txt): ");
	//scanf("%s",file);

	fp = fopen(file,"r");

	if (fp == NULL)
	{
		puts("Could not open the file");
		return -1;
	}

	no_productions = 37;        // No. of Productions are given manually.
	printf(ANSI_COLOR_GREEN"Number of productions: %d \n\n"ANSI_COLOR_RESET,no_productions);

	char productions[no_productions][100];   // String array to store productions.
	char non_term[no_productions]; // # of variables cant exceed no. of productions.
	char term[no_t];

  printf(ANSI_COLOR_GREEN"\n\nPrinting Productions ...... \n\n"ANSI_COLOR_RESET);
	for  (int i=0;i<no_productions;i++)
	{
		fgets(productions[i],100,fp);
			//Because fgets() adds a newline at the end of the string
			productions[i][strlen(productions[i])-1] = '\0';
			printf(ANSI_COLOR_GREEN"%d.\t"ANSI_COLOR_RESET,i);
      for(int j=0;j<strlen(productions[i]);j++){
        if(j!=1){
        get_token_of_symbol(productions[i][j]);
        printf(" ");}
        else
        printf(ANSI_COLOR_RED" -> "ANSI_COLOR_RESET);
      }
      printf("\n");
	}

	fclose(fp);

//Give terminals and non-terminals manually in the array term and non-term
	strcpy(term,"abcdfghijklmnopqr$");     // Assumption e will only be mapped to epsilon.
	strcpy(non_term,"SABDCEFQMJGHKILNPORTU");
	no_nt=21; // no_nt = strlen(non_term)
	no_t=18;  // no_t = strlen(term)
	printf("\n");

	char first[no_nt][100];          // Arrays to store,
	char follow[no_nt][100];         // first and follow.

	for (int i = 0;i<no_nt;i++)
	{
		first[i][0] = '\0';
		follow[i][0] = '\0';
	}

  //Give first and follow manually in arrays first and follow.

  strcpy(first[0],"ae");
	strcpy(first[1],"a");         // first[0] = first[A] or first[MD] as MD is mapped to A.
	strcpy(first[2],"fdc"); //  Here index 0-16 are given in a manner that are given in non_term array at line 70
	strcpy(first[3],"f");               // eg-  A-0,B-1,D-2,C-3  and so on...
	strcpy(first[4],"de");
	strcpy(first[5],"earpmbf");
  strcpy(first[6],"arpmbf");
	strcpy(first[7],"r");
	strcpy(first[8],"p");
	strcpy(first[9],"m");
	strcpy(first[10],"bf");
  strcpy(first[11],"je");
	strcpy(first[12],"lbf");
	strcpy(first[13],"k");
	strcpy(first[14],"no");
	strcpy(first[15],"bf");
  strcpy(first[16],"eq");
	strcpy(first[17],"je");
  strcpy(first[18],"ea");
  strcpy(first[19],"de");
  strcpy(first[20],"bf");

  strcpy(follow[0],"$");
	strcpy(follow[1],"airpmbf");
	strcpy(follow[2],"airpmbf");
	strcpy(follow[3],"iarpmbf");
	strcpy(follow[4],"c");
	strcpy(follow[5],"i");
  strcpy(follow[6],"iarpmbf");
  strcpy(follow[7],"iarpmbf");
  strcpy(follow[8],"iarpmbf");
  strcpy(follow[9],"iarpmbf");
  strcpy(follow[10],"iarpmbf");
  strcpy(follow[11],"ck");
  strcpy(follow[12],"jcjk");
  strcpy(follow[13],"c");
  strcpy(follow[14],"g");
  strcpy(follow[15],"k");
  strcpy(follow[16],"iarpmbf");
  strcpy(follow[17],"k");
  strcpy(follow[18],"g");
  strcpy(follow[19],"g");
  strcpy(follow[20],"fdcjckno");


	int table[no_nt][100];        // 2-D array to store parsing_table.

	for (int i = 0;i<no_nt;i++)
	{
		for (int j = 0;j<=no_nt;j++)
		{
			table[i][j] = -1;               //Initialise all the entries to -1.
		}
	}

	generate_parsing_table(no_nt,no_t,no_productions,non_term,term,productions,first,follow,table);

	for  (int i=0;i<no_productions;i++)
	{
		if (productions[i][strlen(productions[i])-1] == 101)
		{
			productions[i][strlen(productions[i])-1] = '\0';       // If we encoumtered 'e' (epsilon), change it to NULL
		}
	}

	char cfile[20];
	strcpy(cfile,"input2.txt");
	//printf("Enter the file name containing code (Give input.c) : ");
	//scanf("%s",cfile);

	fp1 = fopen(cfile,"r");
  if (fp1 == NULL)
	{
		puts("Could not open the file");
		return -1;
	}

  char buffer[20];  // buffer array to store the token_type of each word of our input file by passing in lexer.
	char input_stream[5000];   //Array to store the stream of tokens/terminals we get by passing in lexer.
	int i=0;

  do {
    fscanf(fp1,"%s", buffer);
    input_stream[i] = get_token_type(buffer);   //name of the functions tells all about it.
    i+=1;
  } while(!feof(fp1));

  input_stream[i-1] = '$'; // Attaching '$' at the end to know input string is ended.
  int wc = i-1;   // # of words in input file.

  s.top=-1;   // Initialise Stack
  push('$');  //
  push('S');  //
  printf("\n");

	char cis;    // current_input_symbol
	int t=0,pn,flag=0;  // 't' keeps the track of input_stream. pn stores the prod num we get from table.
                      // flag to check if string was passed or not.
	int Stack_index, input_index, code;    //code stores the asccii value of terminals/non_terminals
	char Stack_top;
	char insert_prod[20];      // Production that would be pushed in Stack.

  printf(ANSI_COLOR_BLUE"Parsing ....\n"ANSI_COLOR_RESET);
  //display();

	while(s.top!=-1){
		Stack_top = s.stk[s.top];
		cis = input_stream[t];
		//printf("%c\n",cis);
		code = (int)Stack_top;
		if (!((code>=65)&&(code<=90))){          // Its a Terminal.
			Stack_index = get_index_of_symbol(term,Stack_top);
		}
		else{                                   // Its a Non-Terminal
			Stack_index = get_index_of_symbol(non_term,Stack_top);
		}

		input_index = get_index_of_symbol(term,cis);      // input will always be aterminal.

		if(cis==Stack_top){    //Matched terminals
      //printf("\nMatch\t");
      //get_token_of_symbol(cis);
      //printf("\n\n");
			pop();
			t++;

		}
		else if((pn = table[Stack_index][input_index])!=-1){      // Table Entry was not Empty.
			pop();
			strcpy(insert_prod,&(productions[pn][2]));
			//printf("\t\t\tUse production: ");
      //get_token_of_symbol(productions[pn][0]);
      //printf("-> ");
      int len = strlen(insert_prod);
      if(len==0)
      {

      }
        //get_token_of_symbol('e');
      else{
        for (int k = 0; k < len; k++){
          //get_token_of_symbol(insert_prod[k]);
          //printf (" ");
        }
      }
      //printf("\n\n");
      //if(insert_prod[0]!='e'){
			     for(int j = strlen(insert_prod)-1;j>=0;j--){
				         push(insert_prod[j]);
			     }
      //}
		}
		else{
			flag=1;
      printf(ANSI_COLOR_RED"\nERROR:\n"ANSI_COLOR_RESET);
      //printf("%c\n",Stack_top);
      code = (int)Stack_top;
      char q;                                                                   // Error Handling:
  		if ((code>=65)&&(code<=90)){
      if(Stack_top=='I')
        q = first[get_index_of_symbol(non_term,Stack_top)][0];
      else                                                                  // If Stack_top is non_terminal
        q = follow[get_index_of_symbol(non_term,Stack_top)][0];             // and an Error occured
      printf("\t");                                                         // then the entries in the follow of that
      get_token_of_symbol(q);                                               // non_terminal may be missing.
      printf(" was missing after ");}
      else{                                                                 // Else if Stack_top was terminal
        get_token_of_symbol(Stack_top);                                     // and an Error occured then
        printf(" was missing after ");                                      // that terminal may be missing from
      }                                                                     // the code.
      get_token_of_symbol(input_stream[t-1]);
      printf("\n");

      break;

		}
	/*printf("\nHello There!, Want to see the STACK TRACE ? (1/0)\n");
	int ch;
	scanf("%d",&ch);
	if(ch==1)
    	display();*/
	}
	if(flag==0)
	{
		printf(ANSI_COLOR_GREEN"\nCODE ACCEPTED.\n"ANSI_COLOR_RESET);      // Whole Code was parsed Successfully
		return 1;
	}
	else return 0;

}


