#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>
#include <gtk/gtk.h>
#include <gmodule.h>

#define _USE_MATH_DEFINES
#include <math.h>

/* ���� ������ ����ü */
typedef struct bus {
	struct bus* next;
	char station[255];
	double longitude;
	double latitude;
}Bus;

/* �ֿ� ��� ����ü */
typedef struct place {
	struct place* next;
	char name[255];
	double longitude;
	double latitude;
}Place;

typedef struct nearp {
	struct nearp* next;
	char bus_name[50];
	char station[255];
	double longitude;
	double latitude;
}Near;

/*
	�Ÿ� ��� ���� -> 0.8 ����
	long = lon2 - lon1;
	lati = lat2 - lat1;
	a = sin^2(lati/2) + cos(lat1)cos(lat2)sin^2(long/2)
	c = 2arctan(sqrt(a)/sqrt(1-a))
	d = 6371 * c
*/

/* ���� ���� ��ŭ ���� ���� ���� */
Bus* A, * B, * C, * D;

/* �ֿ� ��� */
Place* main_place;

/* ���, ���� */
char start[100];
char end[100];

/* ȭ�� */
GtkWidget* main_window;
GtkWidget* bus_window;
GtkWidget* place_window;

GtkWidget* place_scrolled_window;
GtkWidget* bus_scrolled_window;

GPtrArray* place_button_num;
GPtrArray* bus_button_num;

// �ֿ� ��ҿ��� ���� ���� ������ ���� ��ư�� ã�� ����
GPtrArray* place_station_button;

/* ���� �Ϸ� �Լ� */
void Read_File_Bus(char*, Bus*);				// ���� �б� �Լ�(����)
void Read_File_Place(char*, Place*);			// ���� �б� �Լ�(���)
char* EncodingKR(char*);						// ���ڵ� �Լ�
void Close_Window(GtkWidget*, GPtrArray*);		// ���� ��ư
void Main_Menu();								// ���� ȭ�� ���
void Bus_Menu(GtkWidget*, gpointer);			// ���� ���� ���
void Place_Menu(GtkWidget*, gpointer);			// �ֿ� ��� ���
void Place_Bus_Station(GtkWidget*);	// �ֿ� ��� ��ó ������ ���
double deg2rad(double);							// ������ �������� ��ȯ
void KnowToButton(GtkWidget*, int);				// Ŭ�� ��ư Ȯ��
void KnowToButtonBUS(GtkWidget*, int);         // Ŭ�� ��ư Ȯ��
double Calc_Dis(double, double, double, double);	// �Ÿ� ���
void Dis_Result(double, double, Near*, Bus*);		// �Ÿ� ���� ���
void Label_Inform(GtkWidget*);				// ���� ��ư ������ ���� ����
void KnowToLabel(GtkWidget*, int);			// �����ӿ��� Ŭ�� ��ư Ȯ��

int check_frame = 0;

// �ֿ� ��ҿ��� start, end ��ư Ȯ��
char check_start = 0;
char check_end = 0;

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

/// <summary>
/// ���� �Լ�. ���� �б� ����
/// </summary>
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

/// <summary>
/// �ʱ� ȭ��(���� ȭ��) ���
/// </summary>
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

	// ������ â ���� �� ����
	temp_string = EncodingKR("���� �뼱��");
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(main_window), temp_string);

	// ������ ����
	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(main_window), frame);

	// ��ư ���� �� �����ӿ� ����
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

	// ��ư Ŭ�� �̺�Ʈ
	g_signal_connect(bus_button, "clicked", G_CALLBACK(Bus_Menu), main_window);
	g_signal_connect(place_button, "clicked", G_CALLBACK(Place_Menu), main_window);
}

/// <summary>
/// ���� ���� ȭ���� ���
/// </summary>
/// <param name="widget"></param>
/// <param name="window"></param>
void Bus_Menu(GtkWidget* widget, gpointer window)
{
	GtkWidget* frame;
	GtkWidget* closeButton;
	GtkWidget* busButton[10];
	GtkWidget* label;

	GPtrArray* temp;

	GtkWidget* start_label;
	GtkWidget* end_label;

	char* temp_string;

	// ���� â�� ����
	gtk_widget_hide(window);

	// ���ο� â ����
	temp_string = EncodingKR("���� ������");
	bus_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(bus_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(bus_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(bus_window), temp_string);

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(bus_window), frame);

	busButton[0] = gtk_button_new_with_label("");
	gtk_widget_set_size_request(busButton[0], 1, 1);
	label = gtk_label_new("105");
	gtk_fixed_put(GTK_FIXED(frame), label, 10, 40);
	gtk_fixed_put(GTK_FIXED(frame), busButton[0], 10, 5);

	busButton[1] = gtk_button_new_with_label("");
	gtk_widget_set_size_request(busButton[1], 1, 1);
	label = gtk_label_new("512");
	gtk_fixed_put(GTK_FIXED(frame), label, 10, 100);
	gtk_fixed_put(GTK_FIXED(frame), busButton[1], 10, 65);

	busButton[2] = gtk_button_new_with_label("");
	gtk_widget_set_size_request(busButton[2], 1, 1);
	label = gtk_label_new("717");
	gtk_fixed_put(GTK_FIXED(frame), label, 10, 160);
	gtk_fixed_put(GTK_FIXED(frame), busButton[2], 10, 125);

	busButton[3] = gtk_button_new_with_label("");
	gtk_widget_set_size_request(busButton[3], 1, 1);
	label = gtk_label_new("823");
	gtk_fixed_put(GTK_FIXED(frame), label, 10, 220);
	gtk_fixed_put(GTK_FIXED(frame), busButton[3], 10, 185);

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
	g_ptr_array_add(temp, bus_window);
	g_ptr_array_add(temp, main_window);

	g_signal_connect(closeButton, "clicked", G_CALLBACK(Close_Window), temp);

	bus_button_num = g_ptr_array_new();
	g_ptr_array_add(bus_button_num, frame);

	for (int j = 0; j < 4; j++) {
		g_signal_connect(busButton[j], "clicked", G_CALLBACK(KnowToButtonBUS), j);
	}

	gtk_window_set_modal(GTK_WINDOW(bus_window), TRUE);
	gtk_widget_show_all(bus_window);
}
void Bus_Station(GtkWidget* widget)
{
	GtkWidget* frame;
	GtkWidget* table;
	GtkWidget* button[100];

	GPtrArray* temp;
	Bus* curr;
	GdkColor color;

	Near* near_station = NULL;
	Near* curr_result = NULL;
	char buffer[32];
	double temp_lat, temp_lon;
	double comp_dis;
	int i = 0;
	int j;

	if (check_frame == 1)
		gtk_container_remove(GTK_CONTAINER(g_ptr_array_index(bus_button_num, 0)), bus_scrolled_window);

	bus_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(bus_scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

	table = gtk_table_new(10, 10, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_scrolled_window_add_with_viewport(
		GTK_SCROLLED_WINDOW(bus_scrolled_window), table);

	curr = B->next;
	while (curr != NULL)
	{
		button[i] = gtk_button_new_with_label(EncodingKR(curr->station));
		gtk_widget_set_size_request(button[i], 20, 3);
		gtk_table_attach_defaults(GTK_TABLE(table), button[i], 0, 1, i, i + 1);
		gtk_widget_show(button[i]);
		curr = curr->next;
		i++;
	}

	gtk_fixed_put(GTK_FIXED(g_ptr_array_index(bus_button_num, 0)), bus_scrolled_window, 200, 10);
	gtk_widget_set_size_request(bus_scrolled_window, 400, 400);

	temp = g_ptr_array_new();
	g_ptr_array_add(temp, bus_window);
	g_ptr_array_add(temp, main_window);

	for (j = 0; j < i; j++)
	{
		g_signal_connect(button[j], "clicked", G_CALLBACK(Close_Window), temp);
	}

	gtk_widget_show_all(bus_window);
	g_ptr_array_remove_index(bus_button_num, 1);
	check_frame = 1;

}
/// <summary>
/// �ֿ� ��� ���� ȭ���� ���
/// </summary>
/// <param name="widget"></param>
/// <param name="window"></param>
void Place_Menu(GtkWidget* widget, gpointer window)
{
	GtkWidget* frame;
	GtkWidget* closeButton;

	GPtrArray* temp;

	char* temp_string;
	int i = 0;
	int j = 0;

	GtkWidget* placeButton[20];
	GtkWidget* resultButton;
	GtkWidget* label;

	GtkWidget* start_label;
	GtkWidget* end_label;

	Place* curr;

	gtk_widget_hide(window);

	check_frame = 0;

	temp_string = EncodingKR("�ֿ� ���");
	place_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(place_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(place_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(place_window), temp_string);

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(place_window), frame);

	// �ֿ� ��� ��ư ����
	curr = main_place->next;
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

	// ��� �� ���� ������ ���� ǥ��
	temp_string = EncodingKR("��� ����: ");
	start_label = gtk_label_new(temp_string);
	gtk_fixed_put(GTK_FIXED(frame), start_label, 200, 500);

	temp_string = EncodingKR("���� ����: ");
	end_label = gtk_label_new(temp_string);
	gtk_fixed_put(GTK_FIXED(frame), end_label, 480, 500);

	temp_string = EncodingKR("��� ����");
	resultButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(resultButton, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), resultButton, 680, 500);

	// ��ư ��ġ ���� �ʿ�
	temp_string = EncodingKR("�ڷ� ����");
	closeButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(closeButton, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), closeButton, 680, 550);

	temp = g_ptr_array_new();
	g_ptr_array_add(temp, place_window);
	g_ptr_array_add(temp, main_window);

	g_signal_connect(closeButton, "clicked", G_CALLBACK(Close_Window), temp);

	place_button_num = g_ptr_array_new();
	g_ptr_array_add(place_button_num, frame);

	curr = main_place->next;
	while (curr != NULL)
	{
		g_signal_connect(placeButton[j], "clicked", G_CALLBACK(KnowToButton), j);
		curr = curr->next;
		j++;
	}

	gtk_window_set_modal(GTK_WINDOW(place_window), TRUE);
	gtk_widget_show_all(place_window);
}

// ���� ������ �׽�Ʈ ��
// http://hoyoung2.blogspot.com/2011/06/gtk-tutorial.html ���� ��
void Place_Bus_Station(GtkWidget* widget)
{
	GtkWidget* table;
	GtkWidget* button[10];

	GtkWidget* startlb;
	GtkWidget* endlb;

	GdkColor color;

	Place* curr;
	Near* near_station = NULL;
	Near* curr_result = NULL;
	char buffer[32];
	double temp_lat, temp_lon;
	double comp_dis;
	char* temp_string;
	int i;
	int j;

	//gtk_widget_hide(g_ptr_array_index(place_button_num, 0));
	//g_object_unref(scrolled_window);
	
	if (check_frame == 1)
		gtk_container_remove(GTK_CONTAINER(g_ptr_array_index(place_button_num, 0)), place_scrolled_window);

	place_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(place_scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

	table = gtk_table_new(10, 10, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_scrolled_window_add_with_viewport(
		GTK_SCROLLED_WINDOW(place_scrolled_window), table);

	// ������ ��� ã�� ����
	curr = main_place->next;
	for (i = 0; i < g_ptr_array_index(place_button_num, 1); i++)
	{
		curr = curr->next;
	}
	temp_lat = curr->latitude;
	temp_lon = curr->longitude;

	near_station = (Near*)malloc(sizeof(Near) * 5);


	/* ���� ���� ��ŭ */
	Dis_Result(temp_lat, temp_lon, near_station, A);

	curr_result = near_station->next;
	i = 0;
	while (curr_result != NULL)
	{
		button[i] = gtk_button_new_with_label(EncodingKR(curr_result->station));
		gtk_table_attach_defaults(GTK_TABLE(table), button[i],
			0, 1, i, i + 1);
		gtk_widget_show(button[i]);
		curr_result = curr_result->next;
		i++;
	}
	// gptrarray��� ��ư ��� �׽�Ʈ
	/*if (g_ptr_array_index(place_button_num, 1) == 0)
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++) {
				sprintf(buffer, "button (%d,%d)\n", i, j);
				button = gtk_button_new_with_label(buffer);
				gtk_table_attach_defaults(GTK_TABLE(table), button,
					i, i + 1, j, j + 1);
				gtk_widget_show(button);
			}
	else
	{
		button = gtk_button_new_with_label("");
		gtk_table_attach_defaults(GTK_TABLE(table), button,
			0, 1, 0, 1);
		gtk_widget_show(button);
	}*/

	/*button = gtk_button_new_with_label("close");
	gtk_widget_set_can_default(button, TRUE);*/

	//gdk_color_parse("red", &color);
	
	gtk_fixed_put(GTK_FIXED(g_ptr_array_index(place_button_num, 0)), place_scrolled_window, 200, 10);
	gtk_widget_set_size_request(place_scrolled_window, 400, 400);
	//gtk_widget_modify_bg(table, GTK_STATE_NORMAL, &color);
	//gtk_widget_override_color(table, GTK_STATE_NORMAL, &color);

	if (check_start == 0)
	{
		temp_string = EncodingKR("");
		startlb = gtk_label_new(temp_string);
	}
	else
		startlb = gtk_label_new(start);
	gtk_fixed_put(GTK_FIXED(g_ptr_array_index(place_button_num, 0)), startlb, 270, 500);

	if (check_end== 0)
	{
		temp_string = EncodingKR("");
		endlb = gtk_label_new(temp_string);
	}
	else
		endlb = gtk_label_new(end);
	gtk_fixed_put(GTK_FIXED(g_ptr_array_index(place_button_num, 0)), endlb, 550, 500);

	/*temp = g_ptr_array_new();
	g_ptr_array_add(temp, place_window);
	g_ptr_array_add(temp, main_window);*/
	/*gtk_widget_grab_default(button);
	gtk_widget_show(button);
	gtk_widget_show(scrolled_window);*/

	place_station_button = g_ptr_array_new();
	g_ptr_array_add(place_station_button, startlb);
	g_ptr_array_add(place_station_button, endlb);
	g_ptr_array_add(place_station_button, near_station);

	// ���� ��
	curr_result = near_station->next;
	j = 0;
	while (curr_result != NULL)
	{
		g_signal_connect(button[j], "clicked", G_CALLBACK(KnowToLabel), j);
		curr_result = curr_result->next;
		j++;
	}
	/*for (j = 0; j < i; j++)
	{
		g_signal_connect(button[j], "clicked", G_CALLBACK(Close_Window), temp);
	}*/

	gtk_widget_show_all(place_window);
	g_ptr_array_remove_index(place_button_num, 1);
	check_frame = 1;



	/*
	Ŭ���� ���(num)�� ���� �� �浵
	��� ���� �뼱���� �� ���� �� ���� �� ���
	��ư���� ���
	*/
	/*int i;
	double temp_lat;
	double temp_lon;

	curr = A->next;
	for (i = 0; i < num; i++)
	{
		curr = curr->next;
	}
	temp_lat = curr->latitude;
	temp_lon = curr->longitude;*/

	
	
	//Bus* curr;


	/*curr = A->next;
	while (curr != NULL)
	{
		
	}*/


	/*GtkWidget* subwindow;
	GtkWidget* tree_view;
	GtkWidget* closeButton;
	char* temp_string;
	GtkListStore* model;

	subwindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(subwindow),
		GTK_POLICY_AUTOMATIC,
		GTK_POLICY_AUTOMATIC);

	model = gtk_list_store_new(1, G_TYPE_STRING);
	tree_view = gtk_tree_view_new();
	gtk_container_add(GTK_CONTAINER(subwindow), tree_view);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(model));

	temp_string = EncodingKR("�ڷ� ����");
	closeButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(closeButton, 80, 35);
	gtk_fixed_put(GTK_FIXED(tree_view), closeButton, 300, 300);
	gtk_widget_show(tree_view);
	
	gtk_fixed_put(GTK_FIXED(frame), subwindow, 200, 35);*/

}

/// �ձ�ȣ
/// <summary>
/// Ŭ���� ��ư�� �̸��� �޾ƿ� �󺧿� ����
/// </summary>
/// <param name="widget"></param>
/// <param name="window"></param>
void Label_Inform(GtkWidget* widget)
{
	Near* temp;
	Near* curr;
	char* t;
	int i;
	temp = g_ptr_array_index(place_station_button, 2);
	curr = temp->next;
	for (i = 0; i < g_ptr_array_index(place_station_button, 3); i++)
	{
		curr = curr->next;
	}
	if (check_start == 0 && check_end == 0)
	{
		strcpy_s(start, sizeof(start), curr->station);
		gtk_label_set_text(g_ptr_array_index(place_station_button, 0), start);
		check_start = 1;
	}
	else if (check_start == 1 && check_end == 0)
	{
		strcpy_s(end, sizeof(end), curr->station);
		if (strcmp(start, end) == 0)
		{
			strcpy_s(start, sizeof(start), "");
			gtk_label_set_text(g_ptr_array_index(place_station_button, 0), start);
			check_start = 0;
		}
		else
		{
			gtk_label_set_text(g_ptr_array_index(place_station_button, 1), end);
			check_end = 1;
		}
	}
	g_ptr_array_remove_index(place_station_button, 3);
}

void Dis_Result(double temp_lat, double temp_lon, Near* checking, Bus* ch_bus)
{
	Bus* curr;
	Near* temp_near[10];

	int i;
	double comp_dis;

	curr = ch_bus->next;
	i = 0;
	while (curr != NULL)
	{
		comp_dis = Calc_Dis(temp_lat, temp_lon, curr->latitude, curr->longitude);
		if (comp_dis < 0.8)
		{
			temp_near[i] = (Near*)malloc(sizeof(Near));
			if (i == 0)
				checking->next = temp_near[i];
			else
				temp_near[i - 1]->next = temp_near[i];

			strcpy_s(temp_near[i]->bus_name, sizeof(temp_near[i]->bus_name), "A");
			strcpy_s(temp_near[i]->station, sizeof(temp_near[i]->station), curr->station);
			temp_near[i]->latitude = curr->latitude;
			temp_near[i]->longitude = curr->longitude;

			i++;
		}
		curr = curr->next;
	}

	if (i != 0)
		temp_near[i - 1]->next = NULL;
	else
		checking->next = NULL;
}

// �ձ�ȣ
// ���� �������� �� Ȯ��
void KnowToLabel(GtkWidget* widget, int button_num)
{
	g_ptr_array_add(place_station_button, (gpointer)button_num);
	Label_Inform(widget);
}

/// <summary>
/// �ݺ����� ����� ��ư�� Ŭ������ ��
/// � ��ư�� Ŭ���ߴ��� Ȯ��
/// </summary>
/// <param name="widget"></param>
/// <param name="window"></param>
void KnowToButton(GtkWidget* widget, int button_num)
{
	g_ptr_array_add(place_button_num, (gpointer)button_num);
	Place_Bus_Station(widget);
}
void KnowToButtonBUS(GtkWidget* widget, int button_num)
{
	g_ptr_array_add(bus_button_num, (gpointer)button_num);
	Bus_Station(widget);
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
	strcpy_s(start, sizeof(start), "");
	strcpy_s(end, sizeof(end), "");
	check_start = 0;
	check_end = 0;
}

/// <summary>
/// ��ǥ�� �Ÿ� ����Ͽ� ����
/// </summary>
/// <param name="clicked_lat">Ŭ���� ����� ����</param>
/// <param name="clicked_lon">Ŭ���� ����� �浵</param>
/// <param name="check_lat">���� �������� ����</param>
/// <param name="check_lon">���� �������� �浵</param>
double Calc_Dis(double clicked_lat, double clicked_lon, double check_lat, double check_lon)
{
	double longitude = deg2rad(clicked_lon - check_lon);
	double latitude = deg2rad(clicked_lat - check_lat);

	double a, c, d;

	a = sin(latitude / 2) * sin(latitude / 2) + cos(deg2rad(clicked_lat)) * cos(deg2rad(check_lat))
		* sin(longitude / 2) * sin(longitude / 2);
	c = 2 * atan(sqrt(a) / sqrt(1 - a));
	d = 6371 * c;

	return d;
}

/// <summary>
/// ���� ��ȯ �Լ�
/// </summary>
/// <param name="degree">��ȯ�� ���� ��</param>
double deg2rad(double degree)
{
	return degree * M_PI / 180;
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
			temp_latitude = strtok_s(temp, ",\r\n", &temp);
			temp_longitude = strtok_s(temp, ",\r\n", &temp);

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
			temp_latitude = strtok_s(temp, ",\r\n", &temp);
			temp_longitude = strtok_s(temp, ",\r\n", &temp);

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