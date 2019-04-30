#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

struct bus {
	char* bus_name = (char*)malloc(sizeof(char) * 100);
	double longitude;
	double latitude;
}BUS;

void Mainmenu();		// ���� ȭ�� ��� �Լ�
void Menu_station();	// ���� ��� ��� �Լ�
void Bus_station();		// ���� ������ ��� �Լ�
void Menu_place();		// �ֿ� ��� ��� �Լ�
void Place_Bus();		// �ֿ� ��� ��ó ������ ��� �Լ�
void Result();			// ��� ȭ�� ��� �Լ�
void Detail_result();	// ��� �ڼ��� ���� �Լ�
void Read_File(char *);		// ���� �б� �Լ�
void Click();

struct place {
	char name[50];
	double longitude;
	double latitude;
};

void gotoxy(int x, int y);
void draw_square(int bus_num, int x);
void draw_line();
void bus_line(int bus_num);
void Menu_place();

int main()
{
	int bus_num;
	draw_square(823, 0);
	gotoxy(10, 1);
	draw_square(717, 10);
	gotoxy(1, 10);
	printf("���� ��ȣ�� �Է��Ͻÿ� : ");
	scanf_s("%d", &bus_num, sizeof(int));
	system("cls");

	draw_square(bus_num, 0);
	gotoxy(10, 1);
	draw_line();



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
	printf(" �������� ");
	printf("%c%c", a, b[2]);
	printf("\n");
	printf("%c%c", a, b[6]);
	for (int x = 0; x < 5; x++) {
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
	}
	printf("%c%c", a, b[5]);
}

void Read_File(char* name)
{
	FILE* fl;
}
void Menu_place()
{
	int item = 0;
	place* Place;
	place start, finish;
	int num; //y��ǥ
	//���� �ҷ�����
	//�ҷ��� ���� �̿��� place �����Ҵ� �� �������� \
	  item �� ���� �� ���� Ŭ����
	//k=2 ���� ����
	//���� ��� 
	while (1) // strat==end�ϰ�� �ݺ� 
	{
		//Ŭ�� �Լ� ȣ�� 
		for (int j = 0; j < item * 10; j += 10) //����Ʈ ó�� ���ۺ��� ������ ���ݸ�ŭ Ȯ��
		{
			if (j < num && num < j + 10)  //�ش�Ǵ� �ε��� �߰�
			{

			}

		}
	}

}
