#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define ANSI_COLOR_RED     "\x1b[1;31m"
#define ANSI_COLOR_GREEN   "\x1b[1;32m"
#define ANSI_COLOR_RESET   "\x1b[1;0m"
#define ANSI_COLOR_BLUE    "\x1b[1;34m"


int main(){
		FILE *fp,*fp2;
		fp = fopen("output.txt","r");
		fp2 = fopen("output.txt","r");

		char line[50];
		int cr=0,prev=0,fl=0;


		//pass 1 to get the information of the blocks which are being used as jump target
		char u_block[100][100];															//stores the info about the used basic block
		int cu=0;

		do{
			char word[100][100];
			int cw = 0;
			fgets(line,50,fp2);
			//printf("%s\n",line);
			//puts(line);
			char *token = strtok(line," ");
			while(token!=NULL){
				//printf("%s\t",token);
				strcpy(word[cw++],token);
				token = strtok(NULL," ");
			}
			if(cw>1)
			{
				if(word[cw-1][0] == 'B')
				{
					char *l_num = word[cw-1];
					/*printf("in1");
					char *label_num;
					strcpy(label_num,"b");
					label_num[1] = l_num;
					label_num[2]='\0';*/
					//strcat(label_num,l_num);
					strcpy(u_block[cu++],l_num);
				}
				
			}

			
		}while(!feof(fp2));
		fclose(fp2);

		int i,j;
		for(i=0;i<cu;i++)
		{
			int l = strlen(u_block[i]);
			u_block[i][l-1]='\0';
			strcat(u_block[i],":\n");
			//printf("%s\n",u_block[i]);
		}




		//********************************************************************************************************
		//NOTE:-
		//RAW = true dependency (flow Dependecny)
		//B=1
		//A=B
		

		//WAR = false dependency (Anti Dependency)
		//B=1
		//B=B+1
		/*In case of false dependency, since we assumed that we have infinite number of registers. The case of WAR is not covered.
		Because in both statements we are loading into a new register. 

		SO THE ENTIRE CODE ONLY CONTAINS TRUE DEPENDENCY.*/
		//*********************************************************************************************************



		
		//2nd pass, entering 2nd pass with the info about the labels.
		do{
			char word[100][100];
			int cw = 0;
			fgets(line,50,fp);
			//puts(line);
			char *token = strtok(line," ");
			while(token!=NULL){
				//printf("%s\t",token);
				strcpy(word[cw++],token);
				token = strtok(NULL," ");
			}


			//the labels
			if(word[0][0]=='B')
			{
				int flag = 0;
				//printf("%s",word[0]);
				if(fl==1){
					printf(ANSI_COLOR_RED"\n ****************************************************\nNo of reg in prev block - %d\n "ANSI_COLOR_RESET,cr-prev);
					for(i=prev;i<cr;i++)
						printf(ANSI_COLOR_BLUE"r%d\n",i);
					printf(ANSI_COLOR_RED"****************************************************\n"ANSI_COLOR_RESET);
					prev=cr;
				}
				if(fl==0)fl=1;
	
				for(i=0;i<cu;i++)
				{
					if(strcmp(word[0],u_block[i])==0)
					{
						flag=1;
						//printf("Hi");
						break;
					}
				}
				if(flag==1)
				{
					printf("\n%s\n",word[0]);
				}
			}

			else if(strcmp(word[1],"=")==0){
					if(cw==3){
						//Assignment

						int f=0;
						char offset[5];
						char base;
						if(word[2][1]=='['){
							f=1;
							base = word[2][0];
							int j=2,k=0;
							while(word[2][j]!=']'){
								offset[k++]=word[2][j];
								j++;
							}
							offset[k]='\0';
						}
						printf("LD r%d, ",cr++);
						if (f){
							printf("%c\n",base);
							printf("LD r%d, %s\n",cr++,offset);
							printf("mul r%d, r%d, 4\n",cr++,cr-1);
							printf("add r%d, r%d, r%d\n",cr++,cr-1,cr-3);
						}
						else
							{printf("%s",word[2]);
							printf("ST %s,r%d\n\n",word[0],cr-1);}
					}
					else if(strcmp(word[3],"+")==0){
						//addr
						printf("LD r%d, %s\n",cr++,word[2]);
						printf("LD r%d, %s\n",cr++,word[4]);
						printf("add r%d, r%d, r%d\n",cr++,cr-2,cr-1);
						printf("ST %s, r%d\n\n",word[0],cr-1);
					}
					else if(strcmp(word[3],"-")==0){
						//sub
						printf("LD r%d, %s\n",cr++,word[2]);
						printf("LD r%d, %s\n",cr++,word[4]);
						printf("sub r%d, r%d, r%d\n",cr++,cr-2,cr-1);
						printf("ST %s, r%d\n\n",word[0],cr-1);
					}
					else if(strcmp(word[3],"*")==0){
						//mul
						printf("LD r%d, %s\n",cr++,word[2]);
						printf("LD r%d, %s\n",cr++,word[4]);
						printf("mul r%d, r%d, r%d\n",cr++,cr-2,cr-1);
						printf("ST %s, r%d\n\n",word[0],cr-1);
					}
					else if(strcmp(word[3],"/")==0){
						//div
						printf("LD r%d, %s\n",cr++,word[2]);
						printf("LD r%d, %s\n",cr++,word[4]);
						printf("div r%d, r%d, r%d\n",cr++,cr-2,cr-1);
						printf("ST %s, r%d\n\n",word[0],cr-1);
					}
			}

			else if(strcmp(word[0],"if")==0)
			{
				if(word[2][0]=='>')
				{
					printf("bgt %s, %s, jump %s\n",word[1],word[3],word[cw-1]);

				}
				else if(word[2][0]=='<')
				{
					printf("blt %s, %s, jump %s\n",word[1],word[3],word[cw-1]);
				}
				else if(strcmp(word[2],">="))
				{
					printf("bge %s, %s, jump %s\n",word[1],word[3],word[cw-1]);
				}
			}
		}while(!feof(fp));
		fclose(fp);

}
