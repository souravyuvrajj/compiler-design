#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int leaders[100];
void trim(char * str)
{
    int index, i, j;
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }
    if(index != 0)
    {
        i = 0;
        while(str[i + index] != '\0')
        {
            str[i] = str[i + index];
            i++;
        }
        str[i] = '\0';
    }
}
int compare(const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int indexof(int Element){
  int Index;
  for (int i = 0; i < 10; i++)
{
     if (Element == leaders[i])
     {
         Index = i;
     }
}
 return Index;
}

void main()
{
  int count = 0;
  FILE *fp,*fp1;
  fp = fopen("input(3AC).txt","r");
  fp1 = fopen("output.txt","w");
  char word[50];

  int k = 0,line;
  leaders[k++]=1;
  do{
    fgets(word,50,fp);
    //printf("%s",word);
    int j = 1;
    for(int i=0;word[i]!='\n';i++){
      //printf("%c",word[i]);
      if(word[i]=='g'){
        //printf("%c\n",word[i+6]);
        int t = word[i+6]-48;
        if(word[i+7]!=')')
          t = t*10 + (word[i+7]-48);
        line = word[0]-48;
        if(word[1]!=':')
          line = line*10 + (word[1]-48);
        //printf("%d\t%d\n",line,t);
        leaders[k++]=t;
        //printf("%d\n", );
        leaders[k++]=line+1;

      }

    }

    count++;

  }while (!feof(fp));
  fclose(fp);
  qsort(leaders,k, sizeof(int), compare);

  for(int i = 0; i < k; i++)
    {
        for(int j = i+1; j < k; )
        {
            if(leaders[j] == leaders[i])
            {
                for(int p = j; p < k; p++)
                {
                    leaders[p] = leaders[p+1];
                }
                k--;
            }
            else
            {
                j++;
            }
        }
    }
  //char *block[count+k];
  //printf("Leaders :\n");
printf("\n\n*****************\nPrinting Basic Block\n*******************\n\n");
  for (int i = 0; i < k; i++) {
    //printf("%d\n",leaders[i] );
  }
  //printf("\n",count);
  char block[count+k][100];

  //for(int i=0;i<count+k;i++)
  //block[i] = (char *)malloc(100 * sizeof(char));
  int leadlen=k;
  fp = fopen("input(3AC).txt","r");
  int flag = 0;
   char sep[10] = "B0:\n",s1[10];
   int b=1;
  k = 0;
  int f;
  strcpy(block[k++],sep);
  for(int i=0;i<leadlen;i++){
    do{
      fgets(word,50,fp);
      line = word[0]-48;
      f = 0;
      if(word[1]!=':'){
        line = line*10 + (word[1]-48);f=1;}

      if(line==leaders[i+1]){
         sep[1] = '\0';
         char s = b + '0';
         s1[0]=s;
         s1[1]='\0';
         strcat(sep,s1);
         sep[2]=':';
	 sep[3]='\n';
        strcpy(block[k++],sep);
        b++;
        if (f==0){word[0]=' ';word[1]=' ';}
        else{word[0]=' ';word[1]=' ';word[2]=' ';}
        trim(word);
        strcpy(block[k++],word);
        break;
      }
      if (f==0){word[0]=' ';word[1]=' ';}
      else{word[0]=' ';word[1]=' ';word[2]=' ';}
      //char temp3[50];
      trim(word);
      strcpy(block[k++],word);
    }while (!feof(fp));
  }
  fclose(fp);
  //printf("%d\n",k);
  for(int i=0;i<k-1;i++){
    for(int j=0;block[i][j]!='\n';j++){
      if(block[i][j]=='('){
        int temp;
        temp = block[i][j+1]-48;
        if(block[i][j+2]!=')')
          temp = temp*10 + block[i][j+2]-48;

        int temp2 = indexof(temp);
        printf("%c",'B');
        fprintf(fp1,"%c",'B');
        printf("%d",temp2);
        fprintf(fp1,"%d",temp2);
        j = j+2;
      }
      else{if(block[i][j]!=')'){printf("%c",block[i][j]);fprintf(fp1,"%c",block[i][j]);}}
    }
    printf("\n");
    fprintf(fp1,"\n");
  }
	fclose(fp1);

}
