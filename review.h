typedef struct{  
  char nickname[20];    // 작성자 닉네임
  char content[200];    // 리뷰 내용
  int recommend;       // 추천 여부(1 : 추천 / 2 : 비추천)
  int rating;           // 별점 (1 ~ 5)
}Review;

void write(Review** review);            // 리뷰를 작성한다. 입력값은 리뷰 구조체 배열과 갯수이다.
void read_all(Review* review[], int count);         // 리뷰 목록을 전체 조회. 입력값은 리뷰 구조체 배열과 갯수이다.
void read_recommend(Review* review[], int count);   // 리뷰 목록중 추천 여부가 true인 목록만 조회. 입력값은 리뷰 구조체 배열과 갯수이다.
void read_notrecommend(Review* review[], int count);// 리뷰 목록중 추천 여부가 false인 목록만 조회. 입력값은 리뷰 구조체 배열과 갯수이다.
void read_conditional(Review* review[], int count); // 리뷰 목록중 별점을 기준으로 조건부로 조회한다. 입력값은 리뷰 구조체 배열과 갯수이다.
void read(Review* review);             // 리뷰 목록을 조회한다. 입력값은 리뷰 구조체이다.
void search(Review* review[], int count);           // 리뷰의 작성자를 검색한다. 입력값은 리뷰 구조체 배열과 갯수이다.
void edit(Review** review);             // 리뷰를 수정한다. 입력값은 리뷰 구조체 배열과 갯수이다.
void del(Review** review);              // 리뷰를 삭제한다. 입력값은 리뷰 구조체 배열과 갯수이다.
void save(Review* review[], int count);             // 리뷰 목록을 파일에 저장한다. 입력값은 리뷰 구조체 배열과 갯수이다.
int load(Review* review[], int count);                         // 리뷰 목록을 파일에서 불러온다. 입력값은 리뷰 구조체 배열이다.
int select_index(Review* review[], int count, const char *prompt);
int showMenu();                         // 메뉴를 보여주고 입력받은 값을 리턴한다.
int showReadMenu();                     // Read의 메뉴를 보여주고 입력받은 값을 리턴한다.