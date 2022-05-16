#include "review.h"
#include "util.h"
#define MAX 100

int main(){
	Review *a[MAX];
    int menu = -1;
    int count = load(a);
    while(menu) {
        menu = showMenu();
		switch(menu){
        case 1:
            write(&a[count]);
            count++;
			break;
        case 2:
            if(count == 0) {
                printf("\n���䰡 �����ϴ�.\n");
                continue;
            }
            int readMenu = showReadMenu();
			switch(readMenu){
				case 1:
					read(a[select_index(a,count,"��ȸ�� ��ȣ�� �Է��� �ּ���.\n")]);
					break;
				case 2:
					read_all(a,count);
					break;
				case 3:
					read_recommend(a,count);
					break;
				case 4:
					read_notrecommend(a,count);
					break;
				case 5:
					read_conditional(a,count);
					break;
			}
			break;
        case 3:
			read_all(a,count);
			edit(&a[select_index(a,count,"������ ��ȣ�� �Է��ϼ���.")]);
			break;
        case 4:
			read_all(a,count);
			del(&a[select_index(a,count,"������ ��ȣ�� �Է��ϼ���.")]);
			break;
		case 5:
			search(a,count);
			break;
		case 6:
			save(a,count);
			break;
		case 7:
			count = load(a);
			break;
		case 0:
			break;
		default:
			break;
		}
    }
    printf("�����!\n");
    for(int i=0; i<count; i++) {
        free(a[count]);
    }

    return 0;
}