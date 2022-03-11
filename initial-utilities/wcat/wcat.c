#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//[Name] wcat 
//[DESC] 인자로 받은 파일을 열어서 안에 있는 문자열 데이터를 출력

int main(int argc, char* argv[]){
    
    if (argc < 2) { // 인자가 없으면 프로그램 종료
	    exit(0);
    }
    int i;
    for(i = 1; i < argc; i++){ // 인자로 받은 갯수 만큼 파일을 읽어서 출력한다.
        FILE *fp = fopen(argv[i],"r");
        char* buffer;
        int size;
        
        if(fp == NULL){ // 파일 읽가 실패 하면 예외처리
            printf("wcat: cannot open file\n");
            exit(1);
        }

        fseek(fp, 0, SEEK_END); // 파일 크기를 읽기 위해 파일 포인터를 파일의 맨 끝으로 이동
        
        size = ftell(fp); // 파일 크기를 저장

        buffer = malloc(size+1); // 파일 크기에 따라 알맞는 크기로 동적 할당
        
        memset(buffer, 0, size + 1); // 동적할당된 변수를 0으로 초기화


        fseek(fp, 0, SEEK_SET); // 파일 데이터를 읽기 위해 파일 포인터를 다시 파일의 맨 처음으로 이동

        if(fgets(buffer,size,fp) != NULL){ //만약 fgets의 값이 NULL이 아니면 feof를 이용해서 파일 끝까지 데이터를 계속 출력한다
             while(!feof(fp))
            { 
                printf("%s" , buffer);
                fgets(buffer,size,fp); // 그 다음 개행 문자 까지 값을 읽음
            }
        }else{ //fgets이 NULL 이면 그냥 처음 읽은 값만 출력 (빈값)
            printf("%s", buffer);  
        }

        fclose(fp);

        free(buffer);
    }


    return 0;
}