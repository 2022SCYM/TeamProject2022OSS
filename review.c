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

void copy_review(Review *dest, Review *sour){		// ���� ����ü�� ���빰�� �����Ͽ� dest�� ����
	strcpy(dest->content,sour->content);
	strcpy(dest->nickname,sour->nickname);
	dest->rating = sour->rating;
	dest->recommend = sour->recommend;
}

void write(Review** review){						// ���並 �ۼ��Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
	*review = (Review *)malloc(sizeof(Review));
	printf("�ۼ��� �̸�\n> ");
	scanf("%s",(*review)->nickname);
	getchar();
	printf("����\n> ");
	gets_((*review)->content,200);
	printf("��õ�Ͻø� 1��, �ƴϸ� 0�� �Է����ּ���\n> ");
	(*review)->recommend = (int)right_input_float(check_0or1,"ERROR) 1 �Ǵ� 0�� �Է����ּ���\n> ");
	printf("������ 1������ 5������ �Է����ּ���\n> ");
	(*review)->rating = (int)2*right_input_float(check_1to5,"ERROR) 1 ���� 5�� ���� .5������ �Է����ּ���\n> ");
}

void read_all(Review* review[], int count) {       // ���� ����� ��ü ��ȸ. �Է°��� ���� ����ü �迭�� �����̴�.
	for(int i=1; i<=count; i++) {
		if(review[i-1] != NULL) {
			printf("No. %d\n", i);
			read(review[i-1]);
		}
	}	
}

void read_by_condition(Review* review[], int count, int func(Review)){	// Ư�� ������ �����ϴ� ���丸 READ
	int c = 0;
	for(int i = 0; i<count; i++){
		if(review[i]!=NULL&&func(*review[i])){
			printf("No. %d\n",i+1);
			read(review[i]);
			c++;
		}
	}
	if(!c)
		printf("������ �����ϴ� �����Ͱ� �������� �ʽ��ϴ�.\n");
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

void read_recommend(Review* review[], int count) {  // ���� ����� ��õ ���ΰ� true�� ��ϸ� ��ȸ. �Է°��� ���� ����ü �迭�� �����̴�.
	rtmp = 1;
	read_by_condition(review,count,recommend);
}

void read_notrecommend(Review* review[], int count) {  // ���� ����� ��õ ���ΰ� false�� ��ϸ� ��ȸ. �Է°��� ���� ����ü �迭�� �����̴�.
	rtmp = 0;
	read_by_condition(review,count,recommend);
}

void read_conditional(Review* review[], int count) { // ���� ����� ������ �������� ���Ǻη� ��ȸ�Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
	printf("�� �� �̻��� ���並 ���ðڽ��ϱ�? (1~5)\n> ");
	rtmp = (int)2*right_input_float(check_1to5,"ERROR) 1 ���� 5�� ���� .5������ �Է����ּ���\n> ");
	read_by_condition(review,count,rating);
}

void read(Review* review) {            // ���� ����� ��ȸ�Ѵ�. �Է°��� ���� ����ü�̴�.
	if(review != NULL) {
		printf("\t�ۼ��� : %s\n", review->nickname);
		printf("\t%s\n", review->content);
		if(review->recommend==1) printf("\t��õ!\t");
		else printf("\t��õ ����...\t");
		printf("���� : %.1f\n", review->rating/2.0);
	}
	else printf("�����Ͱ� �����ϴ�.\n");
}

void search(Review* review[], int count) {          // ������ �ۼ��ڸ� �˻��Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
	printf("�˻��� �ۼ����� �̸��� �Է��ϼ���.\n> ");
	scanf("%s",ntmp);
	read_by_condition(review,count,nickname);
}

int edit_menu(){									// ���� ���� �޴�. ���ϰ��� ������ �޴�
	printf("1. �ۼ��� ����\n");
	printf("2. ���� ����\n");
	printf("3. ��õ ����\n");
	printf("4. ���� ����\n");
	printf("5. �Ϸ�\n");
	printf("0. ���\n");
	printf("> ");
	return (int)right_input_float(check_0to5,"ERROR) 0 ���� 5�� ���� �Է����ּ���\n> ");
}

void edit(Review** review){							// ���並 �����Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
	Review *temp = (Review *)malloc(sizeof(Review));
	copy_review(temp,(*review));

	int select = -1;
	while(select!=0&&select!=5){
		read(temp);
		select = edit_menu();
		switch(select){
			case 1:
				printf("�ۼ��� �̸�\n> ");
				scanf("%s",temp->nickname);
				getchar();
				break;
			case 2:
				printf("����\n> ");
				gets_(temp->content,200);
				break;
			case 3:
				printf("��õ : 1 / ����õ : 0\n> ");
				temp->recommend = (int)right_input_float(check_0or1,"ERROR) 1 �Ǵ� 0�� �Է����ּ���\n> ");
				break;
			case 4:
				printf("������ 1������ 5������ �Է����ּ���\n> ");
				temp->rating = (int)2*right_input_float(check_1to5,"ERROR) 1 ���� 5�� ���� .5������ �Է����ּ���\n> ");
				break;
			case 0:
				printf("����մϴ�.\n");
				break;
			case 5:
				printf("�����մϴ�.\n");
				break;
		}
	}
	if(select==5)
		copy_review((*review),temp);
	free(temp);
}

void del(Review** review){							// ���並 �����Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
	printf("������ �� �׸��� �����Ͻðڽ��ϱ�?\n");
	printf("Ȯ�� 1 / ��� 0\n> ");
	int select = (int)right_input_float(check_0or1,"ERROR) 1 �Ǵ� 0�� �Է����ּ���\n> ");
	if(select==1){
		free(*review);
		*review = NULL;
	}
}

void save(Review* review[], int count){             // ���� ����� ���Ͽ� �����Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
	FILE *fp = fopen("data.txt","w");
	for(int i = 0; i<count; i++){
		fprintf(fp,"%s %d %d %s\n",review[i]->nickname,review[i]->recommend,review[i]->rating,review[i]->content);
	}
	fclose(fp);
}

int load(Review* review[], int count){                         // ���� ����� ���Ͽ��� �ҷ��´�. �Է°��� ���� ����ü �迭�̴�.
	if(count>0) {
		printf("���� ����� �����˴ϴ�. ��� �Ͻ÷��� 1�� �Է����ּ���. ");
		int sel = (int) right_input_float(check_0or1,"0 �Ǵ� 1�� �Է����ּ���\n> ");
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
	sprintf(txt,"1���� %d������ ��ȣ�� �Է����ּ���\n>",count);
	rtmp = count;
	while(1){
		printf(prompt);
		idx = (int)right_input_float(check1tocount,(const char*)txt)-1;
		if(review[idx]!=NULL)
			break;
		printf("�������� �ʴ� �׸��Դϴ�.");
	}
	return idx;
}

int check0to7(float input){
	return (int) input == input && input>=0 &&input<=7;
}

int showMenu() {									// �޴��� �����ְ� �Է¹��� ���� �����Ѵ�.
	printf("\nOSS ���ǿ� ���� ���� ���̳� �ٶ�� ���� �����Ӱ� �ۼ��ϰ� ������ �� �ֽ��ϴ�.\n");
	printf("===============================================================================\n");
	printf("1. ���� �ۼ�\t\t\t5. ���� �˻�\n");
	printf("2. ���� ��ȸ\t\t\t6. ���� ���� ����\n");
	printf("3. ���� ����\t\t\t7. ���� ���� �ҷ�����\n");
	printf("4. ���� ����\t\t\t0. ����\n");
	printf("===============================================================================\n");
	printf("���Ͻô� �޴��� �Է��� �ּ���.  ");
	return (int)right_input_float(check0to7,"0 ���� 7 ������ ���ڸ� �Է��� �ּ���\n>");
}

int showReadMenu() {                    // Read�� �޴��� �����ְ� �Է¹��� ���� �����Ѵ�.
	int menu;
	printf("===============================\n");
	printf("1. �ϳ��� ��ȸ\n");
	printf("2. ��ü ��ȸ\n");
	printf("3. ��õ�� ���丸 ��ȸ\n");
	printf("4. ��õ���� ���� ���丸 ��ȸ\n");
	printf("5. �������� ��ȸ\n");
	printf("===============================\n");
	printf("���Ͻô� �޴��� �Է��� �ּ���.  ");
	return (int)right_input_float(check_1to5,"1 ���� 5 ������ ���ڸ� �Է��� �ּ���\n>");
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
	strcpy(a->nickname,"�г���");
	strcpy(a->content,"���ǿ� ���� ����");
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
	strcpy(a->nickname,"�г���");
	strcpy(a->content,"���ǿ� ���� ����");
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
	strcpy(a[0]->nickname,"�г���");
	strcpy(a[0]->content,"���ǿ� ���� ����");
	a[0]->recommend = 1;
	a[0]->rating = 3;
	
	a[1] = (Review *)malloc(sizeof(Review));
	strcpy(a[1]->nickname,"�г���2");
	strcpy(a[1]->content,"���ǿ� ���� ����2");
	a[1]->recommend = 1;
	a[1]->rating = 8;

	a[2] = (Review *)malloc(sizeof(Review));
	strcpy(a[2]->nickname,"�г���3");
	strcpy(a[2]->content,"���ǿ� ���� ����3");
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
	strcpy(a[0]->content,"���ǿ� ���� ����");
	a[0]->recommend = 1;
	a[0]->rating = 3;
	
	a[1] = (Review *)malloc(sizeof(Review));
	strcpy(a[1]->nickname,"steve");
	strcpy(a[1]->content,"���ǿ� ���� ����2");
	a[1]->recommend = 1;
	a[1]->rating = 8;

	a[2] = (Review *)malloc(sizeof(Review));
	strcpy(a[2]->nickname,"dave");
	strcpy(a[2]->content,"���ǿ� ���� ����3");
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
	strcpy(a[0]->content,"���ǿ� ���� ����");
	a[0]->recommend = 1;
	a[0]->rating = 3;
	
	a[1] = (Review *)malloc(sizeof(Review));
	strcpy(a[1]->nickname,"steve");
	strcpy(a[1]->content,"���ǿ� ���� ����2");
	a[1]->recommend = 1;
	a[1]->rating = 8;

	a[2] = (Review *)malloc(sizeof(Review));
	strcpy(a[2]->nickname,"dave");
	strcpy(a[2]->content,"���ǿ� ���� ����3");
	a[2]->recommend = 1;
	a[2]->rating = 4;

	save(a,3);

	Review *b[3];
	load(b);

	read_all(b,3);
}
#endif