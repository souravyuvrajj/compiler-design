#include <stdio.h>
#include <string.h>
#define MAX 50

  void removecomment(char *fname) {
        int  i , j=0, flag = 0, prev = '\0';
	char ch;
        FILE *fp1, *fp2 , *fp;
        char temp[] = "temp";
     
        fp1 = fopen(fname, "r");
        if (!fp1) {
                printf(" error while opening the file \n");
                return 0;
        }
        fp2 = fopen(temp, "w");
        if (!fp2) {
                printf("error while opening the  temporary file\n");
                return 0;
        }


        prev = fgetc(fp1);
        while ((ch = fgetc(fp1)) != EOF) {
                if (flag == 1) {
                        /* skip the contents until you detect \n */
                        if (ch == '\n') {
                                flag = 0;
                                prev = fgetc(fp1);
                        }
                        continue;
                }
                if (flag == 2) {
                        /* skip the contents until you detect asterix slash */
                        if (ch == '/' && prev == '*') {
                                flag = 0;
                                prev = fgetc(fp1);
                        }
                        continue;
                }
                if (ch == '/' && prev == '/') {
                        flag = 1;
                } else if (prev == '/' && ch == '*') {
                        flag = 2;
                } else {
                        fputc(prev, fp2);
                }
                prev = ch;
        }
 
        fclose(fp1);
        fclose(fp2);
        remove(fname);
        rename(temp, fname);


}
       
