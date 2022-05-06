#include "review.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_0or1(float input){
	return input==1||input==0;
}

int check_1to5(float input){
	float tmp = input;
	tmp -= (int)input;
	return (tmp == 0.5 || tmp == 0.0) && input>=1&&input<=5;
}

int check_0to5(float input){
	return input>=0&&input<=5;
}

void copy_review(Review *dest, Review *sour){		// 리뷰 구조체의 내용물을 복사하여 dest에 저장
	strcpy(dest->content,sour->content);
	strcpy(dest->nikename,sour->nikename);
	dest->rating = sour->rating;
	dest->recommend = sour->recommend;
}

void write(Review** review){						// 리뷰를 작성한다. 입력값은 리뷰 구조체 배열과 갯수이다.
	*review = (Review *)malloc(sizeof(Review));
	printf("작성자 이름\n>");
	scanf("%s",(*review)->nikename);
	getchar();
	printf("내용\n>");
	gets((*review)->content);
	printf("추천하시면 1을, 아니면 0을 입력해주세요\n>");
	(*review)->recommend = (int)right_input_float(check_0or1,"ERROR) 1 또는 0을 입력해주세요\n>");
	printf("별점을 1점부터 5점까지 입력해주세요\n>");
	(*review)->rating = (int)2*right_input_float(check_1to5,"ERROR) 1 에서 5의 값을 .5단위로 입력해주세요\n>");
};

void read_all(Review* review[], int count);         // 리뷰 목록을 전체 조회. 입력값은 리뷰 구조체 배열과 갯수이다.
void read_recommend(Review* review[], int count);   // 리뷰 목록중 추천 여부가 true인 목록만 조회. 입력값은 리뷰 구조체 배열과 갯수이다.
void read_conditional(Review* review[], int count); // 리뷰 목록중 별점을 기준으로 조건부로 조회한다. 입력값은 리뷰 구조체 배열과 갯수이다.
void read(Review* review[], int count);             // 리뷰 목록을 조회한다. 입력값은 리뷰 구조체 배열과 갯수이다.
void search(Review* review[], int count);           // 리뷰의 작성자를 검색한다. 입력값은 리뷰 구조체 배열과 갯수이다.

int edit_menu(){									// 리뷰 수정 메뉴. 리턴값은 선택한 메뉴
	printf("1. 작성자 수정\n");
	printf("2. 내용 수정\n");
	printf("3. 추천 수정\n");
	printf("4. 평점 수정\n");
	printf("5. 완료\n");
	printf("0. 취소\n");
	printf(">");
	return (int)right_input_float(check_0to5,"ERROR) 0 에서 5의 값을 입력해주세요\n>");
}

void edit(Review** review){							// 리뷰를 수정한다. 입력값은 리뷰 구조체 배열과 갯수이다.
	Review *temp = (Review *)malloc(sizeof(Review));
	copy_review(temp,(*review));

	int select = -1;
	while(select!=0&&select!=5){
		select = edit_menu();
		switch(select){
			case 1:
				printf("작성자 이름\n>");
				scanf("%s",temp->nikename);
				getchar();
				break;
			case 2:
				printf("내용\n>");
				gets(temp->content);
				break;
			case 3:
				printf("추천 : 1 / 비추천 : 0\n>");
				temp->recommend = (int)right_input_float(check_0or1,"ERROR) 1 또는 0을 입력해주세요\n>");
				break;
			case 4:
				printf("별점을 1점부터 5점까지 입력해주세요\n>");
				temp->rating = (int)2*right_input_float(check_1to5,"ERROR) 1 에서 5의 값을 .5단위로 입력해주세요\n>");
				break;
			case 0:
				printf("취소합니다.\n");
				break;
			case 5:
				printf("저장합니다.\n");
				break;
		}
	}
	if(select==5)
		copy_review((*review),temp);
	free(temp);
};

void del(Review** review){							// 리뷰를 삭제한다. 입력값은 리뷰 구조체 배열과 갯수이다.
	printf("정말로 이 항목을 삭제하시겠습니까?\n");
	printf("확인 1 / 취소 0\n>");
	int select = (int)right_input_float(check_0or1,"ERROR) 1 또는 0을 입력해주세요\n>");
	if(select==1){
		free(*review);
		*review = NULL;
	}
};

void save(Review* review[], int count);             // 리뷰 목록을 파일에 저장한다. 입력값은 리뷰 구조체 배열과 갯수이다.
int load(Review* review[]);                         // 리뷰 목록을 파일에서 불러온다. 입력값은 리뷰 구조체 배열이다.
int select_index(Review* review[], int count);

#ifdef TESTWRITE
int main(){
	Review *a;
	write(&a);
	printf("%s %s %d %d",a->nikename,a->content,a->recommend,a->rating);
	free(a);
}
#endif

#ifdef TESTEDIT
int main(){
	Review *a;
	a = (Review *)malloc(sizeof(Review));
	strcpy(a->nikename,"닉네임");
	strcpy(a->content,"강의에 대한 리뷰");
	a->recommend = 1;
	a->rating = 3;
	printf("%s %s %d %d\n",a->nikename,a->content,a->recommend,a->rating);
	edit(&a);
	printf("%s %s %d %d\n",a->nikename,a->content,a->recommend,a->rating);
	free(a);
}
#endif

#ifdef TESTDEL
int main(){
	Review *a;
	a = (Review *)malloc(sizeof(Review));
	strcpy(a->nikename,"닉네임");
	strcpy(a->content,"강의에 대한 리뷰");
	a->recommend = 1;
	a->rating = 3;
	printf("%s %s %d %d\n",a->nikename,a->content,a->recommend,a->rating);
	del(&a);
	if(a==NULL)
		printf("Deleted!\n");
	else{
		printf("Not deleted!\n");
		printf("%s %s %d %d\n",a->nikename,a->content,a->recommend,a->rating);
		free(a);
	}
}
#endif