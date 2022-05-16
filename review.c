#include "review.h"

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
	strcpy(dest->nickname,sour->nickname);
	dest->rating = sour->rating;
	dest->recommend = sour->recommend;
}

void write(Review** review){						// 리뷰를 작성한다. 입력값은 리뷰 구조체 배열과 갯수이다.
	*review = (Review *)malloc(sizeof(Review));
	printf("작성자 이름\n> ");
	scanf("%s",(*review)->nickname);
	getchar();
	printf("내용\n> ");
	gets_((*review)->content,200);
	printf("추천하시면 1을, 아니면 0을 입력해주세요\n> ");
	(*review)->recommend = (int)right_input_float(check_0or1,"ERROR) 1 또는 0을 입력해주세요\n> ");
	printf("별점을 1점부터 5점까지 입력해주세요\n> ");
	(*review)->rating = (int)2*right_input_float(check_1to5,"ERROR) 1 에서 5의 값을 .5단위로 입력해주세요\n> ");
}

void read_all(Review* review[], int count) {       // 리뷰 목록을 전체 조회. 입력값은 리뷰 구조체 배열과 갯수이다.
	for(int i=1; i<=count; i++) {
		if(review[i-1] != NULL) {
			printf("No. %d\n", i);
			read(review[i-1]);
		}
	}	
}

void read_by_condition(Review* review[], int count, int func(Review)){	// 특정 조건을 만족하는 리뷰만 READ
	int c = 0;
	for(int i = 0; i<count; i++){
		if(review[i]!=NULL&&func(*review[i])){
			printf("No. %d\n",i+1);
			read(review[i]);
			c++;
		}
	}
	if(!c)
		printf("조건을 만족하는 데이터가 존재하지 않습니다.\n");
}

int rtmp = 0;
char ntmp[20] = "";

int recommend(Review rev){
	return rev.recommend == rtmp;
}

int rating(Review rev){
	return rev.rating >= rtmp;
}

int nickname(Review rev){
	return !strcmp(rev.nickname,ntmp);
}

void read_recommend(Review* review[], int count) {  // 리뷰 목록중 추천 여부가 true인 목록만 조회. 입력값은 리뷰 구조체 배열과 갯수이다.
	rtmp = 1;
	read_by_condition(review,count,recommend);
}

void read_notrecommend(Review* review[], int count) {  // 리뷰 목록중 추천 여부가 false인 목록만 조회. 입력값은 리뷰 구조체 배열과 갯수이다.
	rtmp = 0;
	read_by_condition(review,count,recommend);
}

void read_conditional(Review* review[], int count) { // 리뷰 목록중 별점을 기준으로 조건부로 조회한다. 입력값은 리뷰 구조체 배열과 갯수이다.
	printf("몇 점 이상의 리뷰를 보시겠습니까? (1~5)\n> ");
	rtmp = (int)2*right_input_float(check_1to5,"ERROR) 1 에서 5의 값을 .5단위로 입력해주세요\n> ");
	read_by_condition(review,count,rating);
}

void read(Review* review) {            // 리뷰 목록을 조회한다. 입력값은 리뷰 구조체이다.
	if(review != NULL) {
		printf("\t작성자 : %s\n", review->nickname);
		printf("\t%s\n", review->content);
		if(review->recommend==1) printf("\t추천!\t");
		else printf("\t추천 안함...\t");
		printf("별점 : %.1f\n", review->rating/2.0);
	}
	else printf("데이터가 없습니다.\n");
}

void search(Review* review[], int count) {          // 리뷰의 작성자를 검색한다. 입력값은 리뷰 구조체 배열과 갯수이다.
	printf("검색할 작성자의 이름을 입력하세요.\n> ");
	scanf("%s",ntmp);
	read_by_condition(review,count,nickname);
}

int edit_menu(){									// 리뷰 수정 메뉴. 리턴값은 선택한 메뉴
	printf("1. 작성자 수정\n");
	printf("2. 내용 수정\n");
	printf("3. 추천 수정\n");
	printf("4. 평점 수정\n");
	printf("5. 완료\n");
	printf("0. 취소\n");
	printf("> ");
	return (int)right_input_float(check_0to5,"ERROR) 0 에서 5의 값을 입력해주세요\n> ");
}

void edit(Review** review){							// 리뷰를 수정한다. 입력값은 리뷰 구조체 배열과 갯수이다.
	Review *temp = (Review *)malloc(sizeof(Review));
	copy_review(temp,(*review));

	int select = -1;
	while(select!=0&&select!=5){
		read(temp);
		select = edit_menu();
		switch(select){
			case 1:
				printf("작성자 이름\n> ");
				scanf("%s",temp->nickname);
				getchar();
				break;
			case 2:
				printf("내용\n> ");
				gets_(temp->content,200);
				break;
			case 3:
				printf("추천 : 1 / 비추천 : 0\n> ");
				temp->recommend = (int)right_input_float(check_0or1,"ERROR) 1 또는 0을 입력해주세요\n> ");
				break;
			case 4:
				printf("별점을 1점부터 5점까지 입력해주세요\n> ");
				temp->rating = (int)2*right_input_float(check_1to5,"ERROR) 1 에서 5의 값을 .5단위로 입력해주세요\n> ");
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
}

void del(Review** review){							// 리뷰를 삭제한다. 입력값은 리뷰 구조체 배열과 갯수이다.
	printf("정말로 이 항목을 삭제하시겠습니까?\n");
	printf("확인 1 / 취소 0\n> ");
	int select = (int)right_input_float(check_0or1,"ERROR) 1 또는 0을 입력해주세요\n> ");
	if(select==1){
		free(*review);
		*review = NULL;
	}
}

void save(Review* review[], int count){             // 리뷰 목록을 파일에 저장한다. 입력값은 리뷰 구조체 배열과 갯수이다.
	FILE *fp = fopen("data.txt","w");
	for(int i = 0; i<count; i++){
		fprintf(fp,"%s %d %d %s\n",review[i]->nickname,review[i]->recommend,review[i]->rating,review[i]->content);
	}
	fclose(fp);
}

int load(Review* review[], int count){                         // 리뷰 목록을 파일에서 불러온다. 입력값은 리뷰 구조체 배열이다.
	if(count>0) {
		printf("현재 목록은 삭제됩니다. 계속 하시려면 1을 입력해주세요. ");
		int sel = (int) right_input_float(check_0or1,"0 또는 1을 입력해주세요\n> ");
		if(sel) {
			for(int i = 0; i<count; i++) {
				review[i] = NULL;
				free(review[i]);
			}
		}
		else return count;
	}
	FILE *fp = fopen("data.txt","r");
	count = 0;
	while(1){
		Review *tmp = (Review*)malloc(sizeof(Review));
		fscanf(fp,"%s",tmp->nickname);
		if(feof(fp))
			break;
		fscanf(fp,"%d %d %[^\n]",&tmp->recommend,&tmp->rating,tmp->content);
		review[count] = tmp;
		count++;
	}
	fclose(fp);
	return count;
}

int check1tocount(float input){
	return input == (int) input && input>=1 && input<=rtmp;
}

int select_index(Review* review[], int count,const char *prompt){
	int idx = 0;
	char txt[50];
	sprintf(txt,"1부터 %d까지의 번호를 입력해주세요\n>",count);
	rtmp = count;
	while(1){
		printf(prompt);
		idx = (int)right_input_float(check1tocount,(const char*)txt)-1;
		if(review[idx]!=NULL)
			break;
		printf("존재하지 않는 항목입니다.");
	}
	return idx;
}

int check0to7(float input){
	return (int) input == input && input>=0 &&input<=7;
}

int showMenu() {									// 메뉴를 보여주고 입력받은 값을 리턴한다.
	printf("\nOSS 강의에 대해 느낀 점이나 바라는 점을 자유롭게 작성하고 공유할 수 있습니다.\n");
	printf("===============================================================================\n");
	printf("1. 리뷰 작성\t\t\t5. 리뷰 검색\n");
	printf("2. 리뷰 조회\t\t\t6. 리뷰 파일 저장\n");
	printf("3. 리뷰 수정\t\t\t7. 리뷰 파일 불러오기\n");
	printf("4. 리뷰 삭제\t\t\t0. 종료\n");
	printf("===============================================================================\n");
	printf("원하시는 메뉴를 입력해 주세요.  ");
	return (int)right_input_float(check0to7,"0 부터 7 까지의 숫자를 입력해 주세요\n>");
}

int showReadMenu() {                    // Read의 메뉴를 보여주고 입력받은 값을 리턴한다.
	int menu;
	printf("===============================\n");
	printf("1. 하나만 조회\n");
	printf("2. 전체 조회\n");
	printf("3. 추천한 리뷰만 조회\n");
	printf("4. 추천하지 않은 리뷰만 조회\n");
	printf("5. 별점으로 조회\n");
	printf("===============================\n");
	printf("원하시는 메뉴를 입력해 주세요.  ");
	return (int)right_input_float(check_1to5,"1 부터 5 까지의 숫자를 입력해 주세요\n>");
}

#ifdef TESTWRITE
int main(){
	Review *a;
	write(&a);
	read(a);
	free(a);
}
#endif

#ifdef TESTEDIT
int main(){
	Review *a;
	a = (Review *)malloc(sizeof(Review));
	strcpy(a->nickname,"닉네임");
	strcpy(a->content,"강의에 대한 리뷰");
	a->recommend = 1;
	a->rating = 3;
	printf("%s %s %d %d\n",a->nickname,a->content,a->recommend,a->rating);
	edit(&a);
	printf("%s %s %d %d\n",a->nickname,a->content,a->recommend,a->rating);
	free(a);
}
#endif

#ifdef TESTDEL
int main(){
	Review *a;
	a = (Review *)malloc(sizeof(Review));
	strcpy(a->nickname,"닉네임");
	strcpy(a->content,"강의에 대한 리뷰");
	a->recommend = 1;
	a->rating = 3;
	printf("%s %s %d %d\n",a->nickname,a->content,a->recommend,a->rating);
	del(&a);
	if(a==NULL)
		printf("Deleted!\n");
	else{
		printf("Not deleted!\n");
		printf("%s %s %d %d\n",a->nickname,a->content,a->recommend,a->rating);
		free(a);
	}
}
#endif

#ifdef TESTREAD
int main(){
	Review *a[3];
	
	a[0] = (Review *)malloc(sizeof(Review));
	strcpy(a[0]->nickname,"닉네임");
	strcpy(a[0]->content,"강의에 대한 리뷰");
	a[0]->recommend = 1;
	a[0]->rating = 3;
	
	a[1] = (Review *)malloc(sizeof(Review));
	strcpy(a[1]->nickname,"닉네임2");
	strcpy(a[1]->content,"강의에 대한 리뷰2");
	a[1]->recommend = 1;
	a[1]->rating = 8;

	a[2] = (Review *)malloc(sizeof(Review));
	strcpy(a[2]->nickname,"닉네임3");
	strcpy(a[2]->content,"강의에 대한 리뷰3");
	a[2]->recommend = 1;
	a[2]->rating = 4;

	read_all(a,3);
}
#endif

#ifdef TESTCONDI
int main(){	
	Review *a[3];
	
	a[0] = (Review *)malloc(sizeof(Review));
	strcpy(a[0]->nickname,"bob");
	strcpy(a[0]->content,"강의에 대한 리뷰");
	a[0]->recommend = 1;
	a[0]->rating = 3;
	
	a[1] = (Review *)malloc(sizeof(Review));
	strcpy(a[1]->nickname,"steve");
	strcpy(a[1]->content,"강의에 대한 리뷰2");
	a[1]->recommend = 1;
	a[1]->rating = 8;

	a[2] = (Review *)malloc(sizeof(Review));
	strcpy(a[2]->nickname,"dave");
	strcpy(a[2]->content,"강의에 대한 리뷰3");
	a[2]->recommend = 1;
	a[2]->rating = 4;
	
	read_recommend(a,3);
	printf("=========\n");
	read_notrecommend(a,3);
	printf("=========\n");
	read_conditional(a,3);
	printf("=========\n");
	search(a,3);
}
#endif

#ifdef TESTFILE
int main(){
	Review *a[3];
	
	a[0] = (Review *)malloc(sizeof(Review));
	strcpy(a[0]->nickname,"bob");
	strcpy(a[0]->content,"강의에 대한 리뷰");
	a[0]->recommend = 1;
	a[0]->rating = 3;
	
	a[1] = (Review *)malloc(sizeof(Review));
	strcpy(a[1]->nickname,"steve");
	strcpy(a[1]->content,"강의에 대한 리뷰2");
	a[1]->recommend = 1;
	a[1]->rating = 8;

	a[2] = (Review *)malloc(sizeof(Review));
	strcpy(a[2]->nickname,"dave");
	strcpy(a[2]->content,"강의에 대한 리뷰3");
	a[2]->recommend = 1;
	a[2]->rating = 4;

	save(a,3);

	Review *b[3];
	load(b);

	read_all(b,3);
}
#endif