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
                printf("\n���䰡 �����ϴ�.\n");
                continue;
            }
            int readMenu = showReadMenu();
            if(readMenu == 1) {
                int r;
                printf("��ȸ�� ��ȣ�� �Է��� �ּ���. ");
                printf("( 1 ~ %d ) ", count);
                scanf("%d", &r);
                if(r <= 0 || r > count) printf("1 ���� %d ������ ���ڸ� �Է��� �ּ���\n\n", count);
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
                printf("1 ���� 5 ������ ���ڸ� �Է��� �ּ���\n\n");
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
            printf("0 ���� 7 ������ ���ڸ� �Է��� �ּ���\n\n");
        }
    }
    printf("�����!\n");
    for(int i=0; i<count; i++) {
        free(a[count]);
    }

    return 0;
}