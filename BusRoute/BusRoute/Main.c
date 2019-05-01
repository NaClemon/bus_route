#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

/* 버스 정거장 구조체 */
typedef struct bus {
	char station[255];
	double longitude;
	double latitude;
}Bus;

/* 주요 장소 구조체 */
typedef struct place {
	char name[50];
	double longitude;
	double latitude;
}Place;

/* 버스 개수 만큼 전역 변수 설정 */
Bus* A;

/* 구현 완료 함수 */

void Read_File(char*, Bus*);		// 파일 읽기 함수
void gotoxy(int x, int y);


/* 구현 미완료 함수 */

void Mainmenu();		// 메인 화면 출력 함수
void Menu_station();	// 버스 목록 출력 함수
void Bus_station();		// 버스 정류장 출력 함수
void Menu_place();		// 주요 장소 출력 함수
void Place_Bus();		// 주요 장소 근처 정류장 출력 함수
void Result();			// 결과 화면 출력 함수
void Detail_result();	// 결과 자세히 보기 함수
void Click();

void draw_square(int bus_num, int x);
void draw_line();
void bus_line(int bus_num);
void Menu_place();

int main()
{
	A = (Bus*)malloc(sizeof(Bus) * 100);
	Read_File("512.csv", A);

	int bus_num;
	draw_square(823, 0);
	gotoxy(10, 1);
	draw_square(717, 10);
	gotoxy(1, 10);
	printf("버스 번호를 입력하시오 : ");
	scanf_s("%d", &bus_num);
	system("cls");

	draw_square(bus_num, 0);
	gotoxy(10, 1);
	draw_line();


	free(A);
	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw_square(int bus_num, int x)
{
	unsigned char a = 0xa6, b[7], i;
	for (i = 1; i < 7; i++)
		b[i] = 0xa0 + i;
	printf("%c%c", a, b[3]);
	for (int x = 0; x < 3; x++) {
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
	}
	printf("%c%c", a, b[4]);
	printf("\n");
	gotoxy(x, 2);
	printf("%c%c", a, b[2]);
	for (int x = 0; x < 3; x++) {
		printf("  ");
	}
	printf("%c%c", a, b[2]);
	printf("\n");
	gotoxy(x, 3);
	printf("%c%c", a, b[2]);
	printf("  %d ", bus_num);
	printf("%c%c", a, b[2]);
	printf("\n");
	gotoxy(x, 4);
	printf("%c%c", a, b[2]);
	for (int x = 0; x < 3; x++) {
		printf("  ");
	}
	printf("%c%c", a, b[2]);
	printf("\n");
	gotoxy(x, 5);
	printf("%c%c", a, b[6]);
	for (int x = 0; x < 3; x++) {
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
	}
	printf("%c%c", a, b[5]);
	printf("\n");
}
void draw_line()
{
	unsigned char a = 0xa6, b[7], i;
	for (i = 1; i < 7; i++)
		b[i] = 0xa0 + i;
	for (int j = 0; j < 20; j++) {
		gotoxy(10, j + 1);
		printf("%c%c", a, b[2]);
		printf("\n");
	}
}

void bus_line(int bus_num)
{
	unsigned char a = 0xa6, b[7], i;
	for (i = 1; i < 7; i++)
		b[i] = 0xa0 + i;
	printf("%c%c", a, b[3]);
	for (int x = 0; x < 5; x++) {
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
	}
	printf("%c%c", a, b[4]);
	printf("\n");
	printf("%c%c", a, b[2]);
	printf(" 동부종점 ");
	printf("%c%c", a, b[2]);
	printf("\n");
	printf("%c%c", a, b[6]);
	for (int x = 0; x < 5; x++) {
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
	}
	printf("%c%c", a, b[5]);
}

/// <summary>
/// 파일 읽기 함수
/// </summary>
/// <param name="name">읽어올 파일 이름</param>
/// <param name="bus_num">버스 정보를 저장할 구조체</param>
void Read_File(char* name, Bus* bus_num)
{
	FILE* bus_inform;
	char str[255];
	char* temp;
	char* temp_station, * temp_longitude, * temp_latitude;
	int i = 0;

	fopen_s(&bus_inform, name, "rb");

	if (bus_inform != NULL)
	{
		while (!feof(bus_inform))
		{
			temp = NULL;
			temp = fgets(str, sizeof(str), bus_inform);

			if (temp == NULL)
				break;

			temp_station = strtok_s(temp, ",\r\n", &temp);
			temp_longitude = strtok_s(temp, ",\r\n", &temp);
			temp_latitude = strtok_s(temp, ",\r\n", &temp);

			strcpy_s(bus_num[i].station, sizeof(bus_num[i].station), temp_station);
			bus_num[i].longitude = atof(temp_longitude);
			bus_num[i].latitude = atof(temp_latitude);

			i++;
		}
		fclose(bus_inform);
	}
}

void Menu_place()
{
	int item = 0;
	Place* place;
	int num = 0; //y좌표
	//파일 불러오기
	//불러온 파일 이용하여 place 동적할당 및 내용저장 \
	  item 수 저장 후 파일 클로즈
	//k=2 현재 스탭
	//설명 출력
	while (1) // strat==end일 경우 반복 
	{
		//클릭 함수 호출
		for (int j = 0; j < item * 10; j += 10) //리스트 시작부터 끝까지 간격만큼 확인
		{
			if (j < num && num < j + 10)  //해당되는 인덱스 발견
			{

			}

		}
	}

}
