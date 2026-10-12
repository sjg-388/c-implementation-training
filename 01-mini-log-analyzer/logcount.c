/* Mini Log Analyzer */
// 파일을 읽고 로그의 종류별 개수를 출력하는 프로그램
// 핵심 개념: 문자열, 배열, struct, 파일 입출력, 함수

#include <stdio.h>
#include <string.h>

struct summary {
    int total;
    int info;
    int warn;
    int error;
    int other;
} smr = {0,0,0,0,0};

void printlog(){
    printf("=== Log Summary ===\n");
    printf("Total : %d\n", smr.total);
    printf("INFO : %d\n", smr.info);
    printf("WARN : %d\n", smr.warn);
    printf("ERROR : %d\n", smr.error);
    printf("OTHER : %d\n", smr.other);
}

int main(int argc, char** argv){
    FILE *fp;
    char* first = NULL;
    char buf[121] = {0};
    if(argc != 2){
        fprintf(stderr, "사용법: %s 파일명\n", argv[0]);
        return 1;
    }

    if(!(fp = fopen(argv[1], "r"))) {
        fprintf(stderr, "%s 파일이 존재하지 않습니다.\n", argv[1]);
        return 2;
    }

    else{
        while(1){
            if(fgets(buf, sizeof(buf), fp) != NULL) {
                first = strtok(buf, " \r\t\n");
                if(first == NULL) {
                    printf("Empty line\n"); 
                    continue;
                }
                else{
                    smr.total++;
                    if(!strcmp(first, "INFO")) smr.info++;
                    else if(!strcmp(first, "WARN")) smr.warn++;
                    else if(!strcmp(first, "ERROR")) smr.error++;
                    else smr.other++;
                }
                printf("first = [%s]\n", first);
            }
            else {
                break;
            }
        }
    }

    printlog();

    fclose(fp);
    return 0;
}