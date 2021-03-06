#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>




int main(int argc, char* argv[]){
    if (argc > 3) { // 인자가 너무 많으면 프로그램 종료
	    
        fprintf(stderr,"usage: reverse <input> <output>\n");
        exit(1);
    }

    int size;
    char* tmp;
    
    int i = 0;
    // char a,b;

    FILE *fp = NULL;
    FILE *fp2 = NULL;
    struct stat sb1;
    struct stat sb2;

    if(argc == 1 ){
        fp = stdin;
        fp2 = stdout;
    }
    else{
        fp = fopen(argv[1],"r");

        if(fp == NULL){ // 파일 읽가 실패 하면 예외처리
            fprintf(stderr,"reverse: cannot open file '%s'\n",argv[1]);
            exit(1);
        }

        fp2 = fopen(argv[2],"w");

        if(!strcmp(argv[1], argv[2])){ // 파일 읽가 실패 하면 예외처리
            fprintf(stderr,"reverse: input and output file must differ\n");
            exit(1);
        }

    }

    if(stat(argv[1],&sb1) == 0 && stat(argv[2],&sb2) == 0){
        if(sb1.st_ino == sb2.st_ino){
            fprintf(stderr,"reverse: input and output file must differ\n");
            exit(1);
        }
    }
    
    //     while(1){
    //     //두개의 파일 모두 끝에 도달하지 않을 경우
    //     if (feof(fp) == 0 && feof(fp2) == 0){
                    
    //         a = fgetc(fp);
    //         b = fgetc(fp2);

    //         if (a != b){
                        
    //             break;
    //         }
    //     }
    //     //두개의 파일 모두 끝에 도달한 경우.
    //     //(첫 번째 조건문에서 각 파일의 문자는 검사했기 때문에
    //     //두 파일이 동시에 feof에 의해 탈출하면 동일한 파일인 것)
    //     else{
    //         fprintf(stderr,"reverse: input and output file must differ\n");
    //         exit(1);
    //     }  
    // }
    fseek(fp,0,SEEK_END);
    size = ftell(fp);
    char buffer[size+1];
    char* reverse[size+1];
    memset(buffer, 0, size+1);

    fseek(fp, 0, SEEK_SET);

    fread(buffer, size , 1 , fp); // 실제 파일 데이터를 읽음
    tmp = strtok(buffer, "\n");
    while (tmp != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
    {
                
            reverse[i] = tmp;
            tmp = strtok(NULL, "\n");     // 다음 문자열을 잘라서 포인터를 반환
            i++;
    }
            
    int j;
    for(j=i-1; j>=0; j--){
        if(reverse[j] != NULL){
            fprintf(fp2,"%s\n",reverse[j]);
        }
    }
            

    fclose(fp);
    fclose(fp2);
    return 0;



}

