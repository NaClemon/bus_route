#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

/* ���� ������ ����ü */
typedef struct bus {
	char station[255];
	double longitude;
	double latitude;
}Bus;

/* �ֿ� ��� ����ü */
typedef struct place {
	char name[50];
	double longitude;
	double latitude;
}Place;

/* ���� ���� ��ŭ ���� ���� ���� */
Bus* A;

/* ���� �Ϸ� �Լ� */

void Read_File(char*, Bus*);		// ���� �б� �Լ�
void gotoxy(int x, int y);


/* ���� �̿Ϸ� �Լ� */

void Mainmenu();		// ���� ȭ�� ��� �Լ�
void Menu_station();	// ���� ��� ��� �Լ�
void Bus_station();		// ���� ������ ��� �Լ�
void Menu_place();		// �ֿ� ��� ��� �Լ�
void Place_Bus();		// �ֿ� ��� ��ó ������ ��� �Լ�
void Result();			// ��� ȭ�� ��� �Լ�
void Detail_result();	// ��� �ڼ��� ���� �Լ�
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
	printf("���� ��ȣ�� �Է��Ͻÿ� : ");
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

/// <summary>
/// ���� �б� �Լ�
/// </summary>
/// <param name="name">�о�� ���� �̸�</param>
/// <param name="bus_num">���� ������ ������ ����ü</param>
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
	int num = 0; //y��ǥ
	//���� �ҷ�����
	//�ҷ��� ���� �̿��Ͽ� place �����Ҵ� �� �������� \
	  item �� ���� �� ���� Ŭ����
	//k=2 ���� ����
	//���� ���
	while (1) // strat==end�� ��� �ݺ� 
	{
		//Ŭ�� �Լ� ȣ��
		for (int j = 0; j < item * 10; j += 10) //����Ʈ ���ۺ��� ������ ���ݸ�ŭ Ȯ��
		{
			if (j < num && num < j + 10)  //�ش�Ǵ� �ε��� �߰�
			{

			}

		}
	}

}
