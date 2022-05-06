#include <stdio.h>
typedef struct{  
  char nikename[20];    // �ۼ��� �г���
  char content[200];    // ���� ����
  int recommend;       // ��õ ����
  int rating;           // ���� (1 ~ 5)
}Review;

void write(Review** review);            // ���並 �ۼ��Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
void read_all(Review* review[], int count);         // ���� ����� ��ü ��ȸ. �Է°��� ���� ����ü �迭�� �����̴�.
void read_recommend(Review* review[], int count);   // ���� ����� ��õ ���ΰ� true�� ��ϸ� ��ȸ. �Է°��� ���� ����ü �迭�� �����̴�.
void read_conditional(Review* review[], int count); // ���� ����� ������ �������� ���Ǻη� ��ȸ�Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
void read(Review* review[], int count);             // ���� ����� ��ȸ�Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
void search(Review* review[], int count);           // ������ �ۼ��ڸ� �˻��Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
void edit(Review** review);             // ���並 �����Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
void del(Review** review);              // ���並 �����Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
void save(Review* review[], int count);             // ���� ����� ���Ͽ� �����Ѵ�. �Է°��� ���� ����ü �迭�� �����̴�.
int load(Review* review[]);                         // ���� ����� ���Ͽ��� �ҷ��´�. �Է°��� ���� ����ü �迭�̴�.
int select_index(Review* review[], int count);