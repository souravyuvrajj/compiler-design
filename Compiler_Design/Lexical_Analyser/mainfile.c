#include<stdio.h>
#include<stdlib.h>
#include"rmcomment.h"
#include<string.h>
#include"SymbolTable.h"
void main()
{
	FILE *fp,*ot;
	removecomment("input.c");
	fp = fopen("input.c","r");
	int isInt=0, isFloat=0,  ischar=0;
	char word[100],ldt[100]=" ";
	int flag=0;
	ot = fopen("output.txt","w");
	do
    	{	
		flag = 0;
		//printf("hi");
		isInt=0; isFloat=0;  ischar=0;
        	fscanf(fp,"%s", word);
        	printf("%s ---------- ", word);
		fprintf(ot,"%s ---------- ",word);
		int i = 0;

		// Checking printf or scanf function
		
		if( strcmp(word,"printf")==0 || strcmp(word,"printf(")==0){
			char new_string[100]="";
			printf("PRINTF FUNCTION DETECTED\n");
			fprintf(ot,"%s","PRINTF FUNCTION DETECTED\n");
			fscanf(fp,"%s", word);
			while(strcmp(word,")")!=0){
				if(strcmp(word,"(")==0){
					printf("%s --------- BRACES DETECTED\n",word);
					printf(ot,"%s --------- BRACES DETECTED\n",word);}
				else{
					strcat(new_string,word);
					strcat(new_string," ");}
				fscanf(fp,"%s", word);
			}
			printf("%s -------- IS LITERAL\n",new_string);
			fprintf(ot,"%s -------- IS LITERAL\n",new_string);
			printf("%s -------- BRACES DETECTED",word);
			printf(ot,"%s -------- BRACES DETECTED",word);
		}

		else if( strcmp(word,"scanf")==0 || strcmp(word,"scanf(")==0){
			char new_string2[100]="";
			printf("SCANF FUNCTION DETECTED\n");
			fprintf(ot,"SCANF FUNCTION DETECTED\n");
			fscanf(fp,"%s", word);
			while(strcmp(word,")")!=0){
				if(strcmp(word,"(")==0){
					printf("%s --------- BRACES DETECTED\n",word);
					fprintf(ot,"%s --------- BRACES DETECTED\n",word);}
				else{
					strcat(new_string2,word);
					strcat(new_string2," ");}
				fscanf(fp,"%s", word);
			}
			printf("%s -------- IS LITERAL\n",new_string2);
			fprintf(ot,"%s -------- IS LITERA\n",new_string2);
			printf("%s -------- BRACES DETECTED",word);
			printf(ot,"%s -------- BRACES DETECTED",word);
		}

		//Checking auto keyword

		else if(word[i]=='a'){
			i++;
			if(word[i]=='u'){
				i++;
				if(word[i]=='t'){
					i++;
					if(word[i]=='o'){
						i++;
						if(word[i]=='\0'){
							printf("KEYWORD AUTO DETECTED");
							fprintf(ot,"KEYWORD AUTO DETECTED");
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

		//Checking break keyword

		else if(word[i]=='b'){
			i++;
			if(word[i]=='r'){
				i++;
				if(word[i]=='e'){
					i++;
					if(word[i]=='a'){
						i++;
						if(word[i]=='k'){
							i++;
							if(word[i]=='\0'){
								printf("KEYWORD BREAK DETECTED");
								fprintf(ot,"KEYWORD BREAK DETECTED");
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

		//Checking char / case / continue / const Keyword

		else if(word[i]=='c'){
			i++;
			if(word[i]=='h'){
				i++;
				if(word[i]=='a'){
					i++;
					if(word[i]=='r'){
						i++;
						if(word[i]=='\0'){
							printf("KEYWORD CHAR DETECTED");
							fprintf(ot,"KEYWORD CHAR DETECTED");
							strcpy(ldt,word);
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}
			else if(word[i]=='a'){
				i++;
				if(word[i]=='s'){
					i++;
					if(word[i]=='e'){
						i++;
						if(word[i]=='\0'){
							printf("KEYWORD CASE DETECTED");
							fprintf(ot,"KEYWORD CASE DETECTED");
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}
			else if(word[i]=='o'){
				i++;
				if(word[i]=='n'){
					i++;
					if(word[i]=='s'){
						i++;
						if(word[i]=='t'){
							i++;
							if(word[i]=='\0'){
								printf("KEYWORD CONST DETECTED");
								fprintf(ot,"KEYWORD CONST DETECTED");
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else if(word[i]=='t'){
						i++;
						if(word[i]=='i'){
							i++;
							if(word[i]=='n'){
								i++;
								if(word[i]=='u'){
									i++;
									if(word[i]=='e'){
										i++;
										if(word[i]=='\0'){
											printf("KEYWORD CONTINUE DETECTED");
											fprintf(ot,"KEYWORD CONTINUE DETECTED");
										}else{
											i--;
											flag = 1;
										}
									}else{
										i--;
										flag = 1;
									}
								}else{
									i--;
									flag = 1;
								}
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

		// Checking default / do / double keyword

		else if(word[i]=='d'){
			i++;
			if(word[i]=='e'){
				i++;
				if(word[i]=='f'){
					i++;
					if(word[i]=='a'){
						i++;
						if(word[i]=='u'){
							i++;
							if(word[i]=='l'){
								i++;
								if(word[i]=='t'){
									i++;
									if(word[i]=='\0'){
										printf("KEYWORD DEFAULT DETECTED");
										fprintf(ot,"KEYWORD DEFAULT DETECTED");
									}else{
										i--;
										flag = 1;
									}
								}else{
									i--;
									flag = 1;
								}		
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else if(word[i]=='o'){
				i++;
				if(word[i]=='\0' || word[i]=='('){
					printf("KEYWORD DO DETECTED");
					fprintf(ot,"KEYWORD DO DETECTED");
				}else if(word[i]=='u'){
					i++;
					if(word[i]=='b'){
						i++;
						if(word[i]=='l'){
							i++;
							if(word[i]=='e'){
								i++;
								if(word[i]=='\0'){
									printf("KEYWORD DOUBLE DETECTED");
									fprintf(ot,"KEYWORD DOUBLE DETECTED");
									strcpy(ldt,word);
								}else{
									i--;
									flag = 1;
								}
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

		//Checking else / enum / extern Keyword

		else if(word[i]=='e'){
			i++;
			if(word[i]=='l'){
				i++;
				if(word[i]=='s'){
					i++;
					if(word[i]=='e'){
						i++;
						if(word[i]=='\0' || word[i]=='('){
							printf("KEYWORD ELSE DETECTED");
							fprintf(ot,"KEYWORD ELSE DETECTED");
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else if(word[i]=='n'){
				i++;
				if(word[i]=='u'){
					i++;
					if(word[i]=='m'){
						i++;
						if(word[i]=='\0'){
							printf("KEYWORD ENUM DETECTED");
							fprintf(ot,"KEYWORD ENUM DETECTED");
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else if(word[i]=='x'){
				i++;
				if(word[i]=='t'){
					i++;
					if(word[i]=='e'){
						i++;
						if(word[i]=='r'){
							i++;
							if(word[i]=='n'){
								i++;
								if(word[i]=='\0'){
									printf("KEYWORD EXTERN DETECTED");
									fprintf(ot,"KEYWORD EXTERN DETECTED");
								}else{
									i--;
									flag = 1;
								}
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

		//Checking float / for keyword

		else if(word[i]=='f'){
			i++;
			if(word[i]=='l'){
				i++;
				if(word[i]=='o'){
					i++;
					if(word[i]=='a'){
						i++;
						if(word[i]=='t'){
							i++;
							if(word[i]=='\0'){
								printf("KEYWORD FLOAT DETECTED");
								fprintf(ot,"KEYWORD FLOAT DETECTED");
								strcpy(ldt,word);
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else if(word[i]=='o'){
				i++;
				if(word[i]=='r'){
					i++;
					if(word[i]=='\0' || word[i]=='('){
						printf("KEYWORD FOR DETECTED");
						fprintf(ot,"KEYWORD FOR DETECTED");
					}else{	
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

		//Checking goto keyword

		else if(word[i]=='g'){
			i++;
			if(word[i]=='o'){
				i++;
				if(word[i]=='t'){
					i++;
					if(word[i]=='o'){
						i++;
						if(word[i]=='\0'){
							printf("KEYWORD GOTO DETECTED");
							fprintf(ot,"KEYWORD GOTO DETECTED");
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

		//Checking int or if keyword

		else if(word[i]=='i'){
			i++;
			if(word[i]=='n'){
				i++;
				if(word[i]=='t'){
					i++;
					if(word[i]=='\0'){
						printf("KEYWORD INT DETECTED");
						fprintf(ot,"KEYWORD INT DETECTED");
						strcpy(ldt,word);
						
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}
			else if(word[i]=='f'){
				i++;
				if(word[i]=='\0' || word[i]=='('){
					printf("KEYWORD IF DETECTED");
					fprintf(ot,"KEYWORD IF DETECTED");
				}
				else{
					i--;
					flag = 1;
				}	
			}
			else{
				flag = 1;
			}
		}
		
		//Checking long keyword

		else if(word[i]=='l'){
			i++;
			if(word[i]=='o'){
				i++;
				if(word[i]=='n'){
					i++;
					if(word[i]=='g'){
						i++;
						if(word[i]=='\0'){
							printf("KEYWORD LONG DETECTED");
							fprintf(ot,"KEYWORD LONG DETECTED");
							strcpy(ldt,word);
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

		// Checking register / return keyword

		else if(word[i]=='r'){
			i++;
			if(word[i]=='e'){
				i++;
				if(word[i]=='g'){
					i++;
					if(word[i]=='i'){
						i++;
						if(word[i]=='s'){
							i++;
							if(word[i]=='t'){
								i++;
								if(word[i]=='e'){
									i++;
									if(word[i]=='r'){
										i++;
										if(word[i]=='\0'){
											printf("KEYWORD REGISTER DETECTED");
											fprintf(ot,"KEYWORD REGISTER DETECTED");
										}else{
											i--;
											flag = 1;
										}
									}else{
										i--;
										flag = 1;
									}
								}else{
									i--;
									flag = 1;
								}		
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else if(word[i]=='t'){
					i++;
					if(word[i]=='u'){
						i++;
						if(word[i]=='r'){
							i++;
							if(word[i]=='n'){
								i++;
								if(word[i]=='\0'){
									printf("KEYWORD RETURN DETECTED");
									fprintf(ot,"KEYWORD RETURN DETECTED");
								}else{
									i--;
									flag = 1;
								}
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}
		
		//Checking short / struct / switch / static / signed / sizeof Keyword

		else if(word[i]=='s'){
			i++;
			if(word[i]=='t'){
				i++;
				if(word[i]=='r'){
					i++;
					if(word[i]=='u'){
						i++;
						if(word[i]=='c'){
							i++;
							if(word[i]=='t'){
								i++;
								if(word[i]=='\0'){
									printf("KEYWORD STRUCT DETECTED");
									fprintf(ot,"KEYWORD STRUCT DETECTED");
								}
								else{
									i--;
									flag = 1;
								}
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else if(word[i]=='a'){
					i++;
					if(word[i]=='t'){
						i++;
						if(word[i]=='i'){
							i++;
							if(word[i]=='c'){
								i++;
								if(word[i]=='\0'){
									printf("KEYWORD STATIC DETECTED");
									fprintf(ot,"KEYWORD STATIC DETECTED");
								}else{
									i--;
									flag = 1;
								}
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}
			else if(word[i]=='w'){
				i++;
				if(word[i]=='i'){
					i++;
					if(word[i]=='t'){
						i++;
						if(word[i]=='c'){
							i++;
							if(word[i]=='h'){
								i++;
								if(word[i]=='\0'){
									printf("KEYWORD SWITCH DETECTED");
									fprintf(ot,"KEYWORD SWITCH DETECTED");
								}
								else{
									i--;
									flag = 1;
								}
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}
			else if(word[i]=='i'){
				i++;
				if(word[i]=='g'){
					i++;
					if(word[i]=='n'){
						i++;
						if(word[i]=='e'){
							i++;
							if(word[i]=='d'){
								i++;
								if(word[i]=='\0'){
									printf("KEYWORD SIGNED DETECTED");
									fprintf(ot,"KEYWORD SIGNED DETECTED");
								}else{
									i--;
									flag = 1;
								}
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else if(word[i]=='z'){
					i++;
					if(word[i]=='e'){
						i++;
						if(word[i]=='o'){
							i++;
							if(word[i]=='f'){
								i++;
								if(word[i]=='\0'){
									printf("KEYWORD SIZEOF DETECTED");
									fprintf(ot,"KEYWORD SIZEOF DETECTED");
								}else{
									i--;
									flag = 1;
								}
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}
			else if(word[i]=='h'){
				i++;
				if(word[i]=='o'){
					i++;
					if(word[i]=='r'){
						i++;
						if(word[i]=='t'){
							i++;
							if(word[i]=='\0'){
								printf("KEYWORD SHORT DETECTED");
								fprintf(ot,"KEYWORD SHORT DETECTED");
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}	
		}

	// Checking typedef keyword

	else if(word[i]=='t'){
			i++;
			if(word[i]=='y'){
				i++;
				if(word[i]=='p'){
					i++;
					if(word[i]=='e'){
						i++;
						if(word[i]=='d'){
							i++;
							if(word[i]=='e'){
								i++;
								if(word[i]=='f'){
									i++;
									if(word[i]=='\0'){
										printf("KEYWORD TYPEDEF DETECTED");
										fprintf(ot,"KEYWORD TYPEDEF DETECTED");
									}else{
										i--;
										flag = 1;
									}
								}else{
									i--;
									flag = 1;
								}
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}
		
	// Checking union / unsigned keyword

		else if(word[i]=='u'){
			i++;
			if(word[i]=='n'){
				i++;
				if(word[i]=='s'){
					i++;
					if(word[i]=='i'){
						i++;
						if(word[i]=='g'){
							i++;
							if(word[i]=='n'){
								i++;
								if(word[i]=='e'){
									i++;
									if(word[i]=='d'){
										i++;
										if(word[i]=='\0'){
											printf("KEYWORD UNSIGNED DETECTED");
											fprintf(ot,"KEYWORD UNSIGNED DETECTED");
										}else{
											i--;
											flag = 1;
										}
									}else{
										i--;
										flag = 1;
									}
								}else{
									i--;
									flag = 1;
								}		
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else if(word[i]=='i'){
					i++;
					if(word[i]=='o'){
						i++;
						if(word[i]=='n'){
							i++;
							if(word[i]=='\0'){
								printf("KEYWORD UNION DETECTED");
								fprintf(ot,"KEYWORD UNION DETECTED");
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

	// Checking void / volatile keyword

		else if(word[i]=='v'){
			i++;
			if(word[i]=='o'){
				i++;
				if(word[i]=='l'){
					i++;
					if(word[i]=='a'){
						i++;
						if(word[i]=='t'){
							i++;
							if(word[i]=='i'){
								i++;
								if(word[i]=='l'){
									i++;
									if(word[i]=='e'){
										i++;
										if(word[i]=='\0'){
											printf("KEYWORD VOLATILE DETECTED");
											fprintf(ot,"KEYWORD VOLATILE DETECTED");
										}else{
											i--;
											flag = 1;
										}
									}else{
										i--;
										flag = 1;
									}
								}else{
									i--;
									flag = 1;
								}		
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else if(word[i]=='i'){
					i++;
					if(word[i]=='d'){
						i++;
						if(word[i]=='\0'){
							printf("KEYWORD VOID DETECTED");
							fprintf(ot,"KEYWORD VOID DETECTED");
						}else{
							i--;
							flag = 1;
						}		
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

	//Checking while keyword

		else if(word[i]=='w'){
			i++;
			if(word[i]=='h'){
				i++;
				if(word[i]=='i'){
					i++;
					if(word[i]=='l'){
						i++;
						if(word[i]=='e'){
							i++;
							if(word[i]=='\0' || word[i]=='('){
								printf("KEYWORD WHILE DETECTED");
								fprintf(ot,"KEYWORD WHILE DETECTED");
							}else{
								i--;
								flag = 1;
							}
						}else{
							i--;
							flag = 1;
						}
					}else{
						i--;
						flag = 1;
					}
				}else{
					i--;
					flag = 1;
				}
			}else{
				i--;
				flag = 1;
			}
		}

		

	// CHECKING OPERATORS
	
	else if(word[i]=='<'){
		i++;
		if(word[i]=='\0'){
			printf(" < DETCETED");
			fprintf(ot," < DETCETED");
		}
		else if(word[i]=='='){
			i++;
			if(word[i]=='\0'){
				printf(" <= DETECTED");
				fprintf(ot," <= DETECTED");
			}else
				i--;
		}
	}
	else if(word[i]=='>'){
		i++;
		if(word[i]=='\0'){
			printf(" > DETECTED");
			fprintf(ot," > DETECTED");
		}
		else if(word[i]=='='){
			i++;
			if(word[i]=='\0'){
				printf(" >= DETECTED");
				fprintf(ot," >= DETECTED");
			}else
				i--;
		}
	}
	else if(word[i]=='='){
		i++;
		if(word[i]=='='){
			i++;
			if(word[i]=='\0'){
				printf(" == DETECTED");
				fprintf(ot," == DETECTED");
			}else
				i--;
		}
		else if(word[i]=='\0'){
			printf(" = DETECETED");
			fprintf(ot," = DETECETED");
		}
	}
	else if(word[i]=='!'){
		i++;
		if(word[i]=='='){
			i++;
			if(word[i]=='\0'){
				printf(" != DETECTED");
				fprintf(ot," != DETECTED");
			}else
				i--;
		}
	}
	
	//CHECKING NUMBERS
	
	else if(isdigit(word[i])){
		for(int j=0 ; j<strlen(word); j++){
			if(isdigit(word[j]))
				isInt=1;
			else if(word[j] == '.')
				isFloat=2;
			else 
				ischar=1;
		}

		if(isInt == 1 && isFloat ==2 &&ischar==0)
			{printf("THIS IS A FLOAT"); fprintf(ot,"THIS IS A FLOAT");}
 		else if(isInt == 1 && isFloat ==0&&ischar==0)
			{printf("THIS IS AN INTEGER"); fprintf(ot,"THIS IS AN INTEGER");}
		else if(ischar==1) 
			{printf("VARIABLE DETECTED"); fprintf(ot,"VARIABLE DETECTED");}		

	}

	//CHECKING MAIN FUNCTION

	else if(word[i]=='m'){
			i++;
			if(word[i]=='a'){
				i++;
				if(word[i]=='i'){
					i++;
					if(word[i]=='n'){
						i++;
						if(word[i]=='('){
							printf("MAIN FUNCTION DETECTED");
							fprintf(ot,"MAIN FUNCTION DETECTED");
						}
						else{
							i--;
						}
					}
					else{
						i--;
						flag = 1;
					}
				}
				else{
					i--;
					flag = 1;
				}
			}
			else{
				i--;
				flag = 1;
			}
		}

	// Checking "+,-,/*"

	else if(word[i]=='+' || word[i]=='-' || word[i]=='*' || word[i]=='/'){
		printf(" MATHEMATICAL OPERATOR DETECTED");
		fprintf(ot," MATHEMATICAL OPERATOR DETECTED");
	}

	// Checking Braces 

	else if(word[i]=='{' || word[i]=='(' || word[i]==')' || word[i]=='}'){
		printf("BRACES DETECTED");
		fprintf(ot,"BRACES DETECTED");
	}
	
	// Checking Delimeters

	else if(word[i]==';'){
		printf(" DELIMETER DETECTED");
		fprintf(ot," DELIMETER DETECTED");
	}

	// Checking Variables

	else{
		flag = 1;
	}
	if(flag==1){
		printf(" VARIABLE DETECTED ");
		printf(" %s ",ldt);
		fprintf(ot," VARIABLE DETECTED ");
		if(strcmp(ldt," ")!=0){
			Insert(word,ldt);
		}
		strcpy(ldt," ");
	}	
	printf("\n");
	fprintf(ot,"%s","\n");
    	}while(!feof(fp));
	
	Display();
	fclose(fp);
		

}
