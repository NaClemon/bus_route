#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>
#include <gtk/gtk.h>
#include <gmodule.h>

/* ���� ������ ����ü */
typedef struct bus {
	struct bus* next;
	char station[255];
	double longitude;
	double latitude;
}Bus;

typedef struct place {
	struct place* next;
	char name[255];
	double longitude;
	double latitude;
}Place;

/* ���� ���� ��ŭ ���� ���� ���� */
Bus* A;

/* �ֿ� ��� */
Place* main_place;

/* ���, ���� */
char start[100];
char end[100];

/* ȭ�� */
GtkWidget* main_window;
GtkWidget* bus_window;
GtkWidget* place_window;

/* ���� �Ϸ� �Լ� */
void Read_File_Bus(char*, Bus*);				// ���� �б� �Լ�(����)
void Read_File_Place(char*, Place*);			// ���� �б� �Լ�(���)
char* EncodingKR(char*);				// ���ڵ� �Լ�
void Close_Window(GtkWidget*, GPtrArray*);	// ���� ��ư
void Main_Menu();						// ���� ȭ�� ���
void Bus_Menu(GtkWidget*, gpointer);	// ���� ���� ���
void Place_Menu(GtkWidget*, gpointer);	// �ֿ� ��� ���




gint count = 0;

GtkWidget* mainwindow;
GtkWidget* secondwindow;

//void increase(GtkWidget* widget, gpointer label)
//{
//	count++;
//
//	sprintf(buf, "%d", count);
//	gtk_label_set_text(label, buf);
//}
//
//void decrease(GtkWidget* widget, gpointer label)
//{
//	count--;
//
//	sprintf(buf, "%d", count);
//	gtk_label_set_text(label, buf);
//}

int main(int argc, char** argv)
{
	GtkWidget* label;
	
	// ���� ���� ����
	A = (Bus*)malloc(sizeof(Bus) * 100);
	Read_File_Bus("512.csv", A);

	// �ֿ� ��� ����
	main_place = (Place*)malloc(sizeof(Place));
	Read_File_Place("place.csv", main_place);

	// gtk �ʱ�ȭ
	gtk_init(&argc, &argv);

	Main_Menu();

	//// ���� ���� ����
	//c.red = 1.0;
	//c.green = 0.0;
	//c.blue = 0.0;
	//c.alpha = 1.0;

	//// ���� ������ ���
	//for (i = 0; i < 5; i++)
	//{
	//	a = gtk_button_new_with_label(A[i].station);
	//	gtk_widget_override_color(GTK_WIDGET(a), GTK_STATE_NORMAL, &c);
	//	gtk_widget_set_size_request(a, 80, 35);
	//	gtk_fixed_put(GTK_FIXED(frame), a, 50, 130 + i * 50);
	//}

	//// ��ư Ŭ�� �̺�Ʈ
	//gtk_widget_show_all(mainwindow);

	//g_signal_connect(mainwindow, "destroy", g_callback(gtk_main_quit), null);

	//g_signal_connect(plus, "clicked",
	//	g_callback(increase), label);

	//g_signal_connect(minus, "clicked",
	//	g_callback(open_window), mainwindow);

	gtk_main();

	return 0;
}

void Main_Menu()
{
	GtkWidget* frame;
	GtkWidget* bus_button;
	GtkWidget* place_button;

	// GtkStyleContext* context;

	char* temp_string;

	// ��ư ui �׽�Ʈ
	/*GtkCssProvider* provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, "../GTKBusRoute/test.css", NULL);*/
	
	temp_string = EncodingKR("���� �뼱��");
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(main_window), temp_string);

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(main_window), frame);

	temp_string = EncodingKR("���� ������");
	bus_button = gtk_button_new_with_label(temp_string);
	/*context = gtk_widget_get_style_context(bus_button);
	gtk_style_context_add_class(context, "enter_button");*/
	gtk_widget_set_size_request(bus_button, 100, 75);
	gtk_fixed_put(GTK_FIXED(frame), bus_button, 250, 400);
	
	// ���� ��ư �׽�Ʈ
	/*gtk_style_context_add_class(
		gtk_widget_get_style_context(GTK_WIDGET(bus_button)),
		"circular"
	);*/

	temp_string = EncodingKR("�ֿ� ���");
	place_button = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(place_button, 100, 75);
	gtk_fixed_put(GTK_FIXED(frame), place_button, 450, 400);

	gtk_widget_show_all(main_window);

	g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect(bus_button, "clicked", G_CALLBACK(Bus_Menu), main_window);
	g_signal_connect(place_button, "clicked", G_CALLBACK(Place_Menu), main_window);
}

void Bus_Menu(GtkWidget* widget, gpointer window)
{
	GtkWidget* frame;
	GtkWidget* closeButton;

	GPtrArray* temp;

	char* temp_string;

	gtk_widget_hide(window);

	temp_string = EncodingKR("���� ������");
	bus_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(bus_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(bus_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(bus_window), temp_string);

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(bus_window), frame);

	// ��ư ��ġ ���� �ʿ�
	temp_string = EncodingKR("�ڷ� ����");
	closeButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(closeButton, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), closeButton, 680, 550);

	temp = g_ptr_array_new();
	g_ptr_array_add(temp, bus_window);
	g_ptr_array_add(temp, main_window);

	g_signal_connect(bus_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(closeButton, "clicked", G_CALLBACK(Close_Window), temp);

	gtk_window_set_modal(GTK_WINDOW(bus_window), TRUE);
	gtk_widget_show_all(bus_window);
}

void Place_Menu(GtkWidget* widget, gpointer window)
{
	GtkWidget* frame;
	GtkWidget* closeButton;

	GPtrArray* temp;

	char* temp_string;
	int i = 0;
	//int struct_size = sizeof(main_place) / sizeof(Place);

	GtkWidget* placeButton[20];
	GtkWidget* label;

	GtkWidget* start_label;
	GtkWidget* end_label;

	gtk_widget_hide(window);

	temp_string = EncodingKR("�ֿ� ���");
	place_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(place_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(place_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(place_window), temp_string);

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(place_window), frame);

	/*for (i = 0; i < 5; i++)
	{
		placeButton[i] = gtk_button_new_with_label("");
		gtk_widget_set_size_request(placeButton[i], 1, 1);
		label = gtk_label_new(main_place[i].name);
		gtk_fixed_put(GTK_FIXED(frame), label, 10, 40 + i * 60);
		gtk_fixed_put(GTK_FIXED(frame), placeButton[i], 10, 5 + i * 60);
	}*/
	Place* curr = main_place->next;
	while (curr != NULL)
	{
		placeButton[i] = gtk_button_new_with_label("");
		gtk_widget_set_size_request(placeButton[i], 1, 1);
		label = gtk_label_new(curr->name);
		gtk_fixed_put(GTK_FIXED(frame), label, 10, 40 + i * 60);
		gtk_fixed_put(GTK_FIXED(frame), placeButton[i], 10, 5 + i * 60);
		curr = curr->next;
		i++;
	}

	temp_string = EncodingKR("��� ����: ");
	start_label = gtk_label_new(temp_string);
	gtk_fixed_put(GTK_FIXED(frame), start_label, 200, 500);

	temp_string = EncodingKR("���� ����: ");
	end_label = gtk_label_new(temp_string);
	gtk_fixed_put(GTK_FIXED(frame), end_label, 480, 500);

	// ��ư ��ġ ���� �ʿ�
	temp_string = EncodingKR("�ڷ� ����");
	closeButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(closeButton, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), closeButton, 680, 550);

	temp = g_ptr_array_new();
	g_ptr_array_add(temp, place_window);
	g_ptr_array_add(temp, main_window);

	g_signal_connect(place_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(closeButton, "clicked", G_CALLBACK(Close_Window), temp);

	gtk_window_set_modal(GTK_WINDOW(place_window), TRUE);
	gtk_widget_show_all(place_window);
}

/// <summary>
/// ���� ȭ������ ���ư��� ����� �Ѵ�.
/// </summary>
/// <param name="widget"></param>
/// <param name="window">gpointer �������� �޾ƿ��� ���� gpointer �迭</param>
void Close_Window(GtkWidget* widget, GPtrArray* window)
{
	gtk_widget_destroy(GTK_WIDGET(g_ptr_array_index(window, 0)));
	gtk_widget_show(g_ptr_array_index(window, 1));
}

/// <summary>
/// ���� ���� ���� �б� �Լ�
/// </summary>
/// <param name="name">�о�� ���� �̸�</param>
/// <param name="bus_num">���� ������ ������ ����ü</param>
void Read_File_Bus(char* name, Bus* bus_num)
{
	FILE* bus_inform;
	char str[255];
	char* temp;
	char* temp_station, * temp_longitude, * temp_latitude;
	int i = 0;
	//Bus** bus_list = (Bus * *)malloc(sizeof(Bus));
	Bus* bus_list[100];

	fopen_s(&bus_inform, name, "rb");

	if (bus_inform != NULL)
	{
		while (!feof(bus_inform))
		{
			bus_list[i] = (Bus*)malloc(sizeof(Bus));
			temp = NULL;
			temp = fgets(str, sizeof(str), bus_inform);

			if (temp == NULL)
				break;

			temp_station = strtok_s(temp, ",\r\n", &temp);
			temp_longitude = strtok_s(temp, ",\r\n", &temp);
			temp_latitude = strtok_s(temp, ",\r\n", &temp);

			if (i == 0)
				bus_num->next = bus_list[i];
			else
				bus_list[i - 1]->next = bus_list[i];

			strcpy_s(bus_list[i]->station, sizeof(bus_list[i]->station), temp_station);
			bus_list[i]->longitude = atof(temp_longitude);
			bus_list[i]->latitude = atof(temp_latitude);

			i++;
		}
		if (i != 0)
			bus_list[i - 1]->next = NULL;
		fclose(bus_inform);
	}
}

/// <summary>
/// �ֿ� ��� ���� �б� �Լ�
/// </summary>
/// <param name="name">�о�� ���� �̸�</param>
/// <param name="place">��� ������ ������ ����ü</param>
void Read_File_Place(char* name, Place* place)
{
	FILE* inform;
	char str[255];
	char* temp;
	char* temp_station, * temp_longitude, * temp_latitude;
	int i = 0;
	//Place** place_list = (Place * *)malloc(sizeof(Place));
	Place* place_list[20];

	fopen_s(&inform, name, "rb");

	if (inform != NULL)
	{
		while (!feof(inform))
		{
			place_list[i] = (Place*)malloc(sizeof(Place));
			temp = NULL;
			temp = fgets(str, sizeof(str), inform);

			if (temp == NULL)
				break;

			temp_station = strtok_s(temp, ",\r\n", &temp);
			temp_longitude = strtok_s(temp, ",\r\n", &temp);
			temp_latitude = strtok_s(temp, ",\r\n", &temp);

			if (i == 0)
				place->next = place_list[i];
			else
				place_list[i - 1]->next = place_list[i];

			strcpy_s(place_list[i]->name, sizeof(place_list[i]->name), temp_station);
			place_list[i]->longitude = atof(temp_longitude);
			place_list[i]->latitude = atof(temp_latitude);

			i++;
		}
		if (i != 0)
			place_list[i - 1]->next = NULL;
		fclose(inform);
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