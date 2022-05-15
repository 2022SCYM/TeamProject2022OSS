#include "review.h"
#include "util.h"
#define MAX 100

int main(){
	Review *a[MAX];
    int menu;
    int count = 0;
    while(1) {
        menu = showMenu();
        if(menu == 1) {
            write(&a[count]);
            count++;
        }
        else if(menu == 2) {
            if(count == 0) {
                printf("\n리뷰가 없습니다.\n");
                continue;
            }
            int readMenu = showReadMenu();
            if(readMenu == 1) {
                int r;
                printf("조회할 번호를 입력해 주세요. ");
                printf("( 1 ~ %d ) ", count);
                scanf("%d", &r);
                if(r <= 0 || r > count) printf("1 부터 %d 까지의 숫자를 입력해 주세요\n\n", count);
                else read(a[r-1]);
            }
            else if(readMenu == 2) {
                read_all(a, count);
            }
            else if(readMenu == 3) {
                read_recommend(a, count);
            }
            else if(readMenu == 4) {
                read_notrecommend(a, count);
            }
            else if(readMenu == 5) {
                read_conditional(a, count);
            }
            else {
                printf("1 부터 5 까지의 숫자를 입력해 주세요\n\n");
            }
        }
        else if(menu == 3) {

        }
        else if(menu == 4) {

        }
        else if(menu == 5) {
            
        }
        else if(menu == 6) {
            
        }
        else if(menu == 7) {
            
        }
        else if(menu == 0) {
            break;
        }
        else {
            printf("0 부터 7 까지의 숫자를 입력해 주세요\n\n");
        }
    }
    printf("종료됨!\n");
    for(int i=0; i<count; i++) {
        free(a[count]);
    }

    return 0;
}