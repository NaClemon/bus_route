#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>
#include <gtk/gtk.h>

/* ���� ������ ����ü */
typedef struct bus {
	char station[255];
	double longitude;
	double latitude;
}Bus;

/* ���� ���� ��ŭ ���� ���� ���� */
Bus* A;

/* ���� �Ϸ� �Լ� */
void Read_File(char*, Bus*);		// ���� �б� �Լ�
char* EncodingKR(char*);				// ���ڵ� �Լ�

gint count = 0;
char buf[5];

GtkWidget* mainwindow;
GtkWidget* secondwindow;

void increase(GtkWidget* widget, gpointer label)
{
	count++;

	sprintf(buf, "%d", count);
	gtk_label_set_text(label, buf);
}

void decrease(GtkWidget* widget, gpointer label)
{
	count--;

	sprintf(buf, "%d", count);
	gtk_label_set_text(label, buf);
}

void close_window(GtkWidget* widget, gpointer window)
{
	gtk_widget_destroy(GTK_WIDGET(window));
	gtk_widget_show(mainwindow);
}

void open_window(GtkWidget* widget, gpointer window)
{
	GtkBuilder* builder;
	GtkWidget* frame;
	GtkWidget* closeButton;

	gtk_widget_hide(window);

	secondwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(secondwindow), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(secondwindow), 400, 400);
	gtk_window_set_title(GTK_WINDOW(secondwindow), "new");

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(secondwindow), frame);

	closeButton = gtk_button_new_with_label("close");
	gtk_widget_set_size_request(closeButton, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), closeButton, 50, 80);

	g_signal_connect(closeButton, "clicked", G_CALLBACK(close_window), secondwindow);

	gtk_window_set_modal(GTK_WINDOW(secondwindow), TRUE);
	gtk_widget_show_all(secondwindow);
}

int main(int argc, char** argv) {

	GtkWidget* label;
	
	GtkWidget* frame;
	GtkWidget* plus;
	GtkWidget* minus;
	
	GtkWidget* a;
	GdkRGBA c;
	int i;

	// gtk �ʱ�ȭ
	gtk_init(&argc, &argv);

	// ���� ���� ����
	A = (Bus*)malloc(sizeof(Bus) * 100);
	Read_File("512.csv", A);

	// ���� ������ ����
	mainwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(mainwindow), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(mainwindow), 400, 400);
	gtk_window_set_title(GTK_WINDOW(mainwindow), "+-");

	// ������ �߰�
	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(mainwindow), frame);

	// ��ư �߰�
	plus = gtk_button_new_with_label("+");
	gtk_widget_set_size_request(plus, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), plus, 50, 20);

	// ��ư �߰� �� �ѱ� ���ڵ�
	char* temp = EncodingKR("�ѱ�");
	minus = gtk_button_new_with_label(temp);
	gtk_widget_set_size_request(minus, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), minus, 50, 80);

	// �� �߰�
	label = gtk_label_new("0");
	gtk_fixed_put(GTK_FIXED(frame), label, 190, 58);

	// ���� ���� ����
	c.red = 1.0;
	c.green = 0.0;
	c.blue = 0.0;
	c.alpha = 1.0;

	// ���� ������ ���
	for (i = 0; i < 5; i++)
	{
		a = gtk_button_new_with_label(A[i].station);
		gtk_widget_override_color(GTK_WIDGET(a), GTK_STATE_NORMAL, &c);
		gtk_widget_set_size_request(a, 80, 35);
		gtk_fixed_put(GTK_FIXED(frame), a, 50, 130 + i * 50);
	}

	// ��ư Ŭ�� �̺�Ʈ
	gtk_widget_show_all(mainwindow);

	g_signal_connect(mainwindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect(plus, "clicked",
		G_CALLBACK(increase), label);

	g_signal_connect(minus, "clicked",
		G_CALLBACK(open_window), mainwindow);

	gtk_main();

	return 0;
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

/// <summary>
/// �ѱ� ���ڵ��� ���� �Լ�
/// �ѱ� ������� �� �Լ� ���
/// </summary>
/// <param name="input">��ȯ�ϰ��� �ϴ� �ѱ���</param>
char* EncodingKR(char* input)
{
	char* output;
	char* pOutput;
	char k[255];
	size_t nSrc, nTgt;
	iconv_t it = iconv_open("UTF-8//TRANSLIT//IGNORE", "CP949//TRANSLIT//IGNORE");

	if (it == (iconv_t)-1)
	{
		return NULL;
	}

	nSrc = strlen(input) + 1;
	nTgt = nSrc * 3;
	output = (char*)malloc(nTgt);
	pOutput = output;

	if (iconv(it, (char**)& input, &nSrc, &pOutput, &nTgt) == (size_t)-1)
	{
		return NULL;
	}

	iconv_close(it);

	return output;
}