#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char get_token_type(char *word)
{

	int flag=0;
	// int l = strlen(word);
	// word[l]='\0';
    //printf("%s", word);
		int i = 0;

		//Checking char Keyword

		if(word[i]=='c'){
			i++;
			if(word[i]=='h'){
				i++;
				if(word[i]=='a'){
					i++;
					if(word[i]=='r'){
						i++;
						if(word[i]=='\0'){
							return 'a';
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

		// Checking  double keyword

		else if(word[i]=='d'){
			i++;
			if(word[i]=='o'){
				i++;
				if(word[i]=='u'){
					i++;
					if(word[i]=='b'){
						i++;
						if(word[i]=='l'){
							i++;
							if(word[i]=='e'){
								i++;
								if(word[i]=='\0'){
									return 'a';
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
						if(word[i]=='\0'){
							return 'q';
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

		//Checking  for keyword

		else if(word[i]=='f'){
			i++;
			if(word[i]=='o'){
				i++;
				if(word[i]=='r'){
					i++;
					if(word[i]=='\0'){
						return 'm';
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
						return 'a';
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
				if(word[i]=='\0'){
					return 'p';
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
							return 'a';
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

		// Checking return keyword

		else if(word[i]=='r'){
			i++;
			if(word[i]=='e'){
				i++;
				if(word[i]=='t'){
					i++;
					if(word[i]=='u'){
						i++;
						if(word[i]=='r'){
							i++;
							if(word[i]=='n'){
								i++;
								if(word[i]=='\0'){
									return 'r';
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


	// Checking void keyword

		else if(word[i]=='v'){
			i++;
			if(word[i]=='o'){
				i++;
			 if(word[i]=='i'){
					i++;
					if(word[i]=='d'){
						i++;
						if(word[i]=='\0'){
							return 'a';
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

	else if(word[i]=='<' ){
		i++;
		if(word[i]=='\0'){
			return 'k';
		}
		else if(word[i]=='='){
			i++;
			if(word[i]=='\0'){
				return 'k';
			}else
				i--;
		}
	}
	else if(word[i]=='>'){
		i++;
		if(word[i]=='\0'){
			return 'k';
		}
		else if(word[i]=='='){
			i++;
			if(word[i]=='\0'){
				return 'k';
			}else
				i--;
		}
	}
	else if(word[i]=='='){
		i++;
		if(word[i]=='='){
			i++;
			if(word[i]=='\0'){
				return 'k';
			}else
				i--;
		}
		else if(word[i]=='\0'){
			return 'j';
		}
	}
	else if(word[i]=='!'){
		i++;
		if(word[i]=='='){
			i++;
			if(word[i]=='\0'){
				return 'k';
			}else
				i--;
		}
	}

	//CHECKING NUMBERS

	else if(isdigit(word[i])){
		return 'l';
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
						if(word[i]=='\0'){
							return 'b';
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

	// Checking ++ or --
		else if(strcmp(word,"++")==0)
			return 'n';

		else if(strcmp(word,"--")==0)
			return 'o';

	// Checking "+,-,/*"

	else if(word[i]=='+' || word[i]=='-' || word[i]=='*' || word[i]=='/' || word[i]=='%'){
		return 'j';
	}

	// Checking Braces

	else if(word[i]=='{')
	 	return 'h';
	else if(word[i]=='(')
		return 'f';
	else if(word[i]==')')
		return 'g';
	else if(word[i]=='}')
		return 'i';

	// Checking Delimeters

	else if(word[i]==';'){
		return 'c';
	}

	// Checking ,

	else if(word[i]==',')
		return 'd';

	// Checking Variables

	else{
		flag = 1;
	}

	if(flag==1){
		return 'b';
	}
}
