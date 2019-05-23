﻿#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>
#include <gtk/gtk.h>
#include <gmodule.h>

#define _USE_MATH_DEFINES
#include <math.h>

/* 버스 정거장 구조체 */
typedef struct bus {
	struct bus* next;
	char station[255];
	double longitude;
	double latitude;
}Bus;

/* 주요 장소 구조체 */
typedef struct place {
	struct place* next;
	char name[255];
	double longitude;
	double latitude;
}Place;

/* 근처 정류장 구조체 */
typedef struct nearp {
	struct nearp* next;
	char bus_name[50];
	char station[255];
	double longitude;
	double latitude;
}Near;

/* 버스 개수 만큼 전역 변수 설정 */
Bus* A, * B, * C, * D;

/* 주요 장소 */
Place* main_place;

/* 출발, 도착 */
char start[100];
char end[100];

/* 화면 */
GtkWidget* main_window;
GtkWidget* bus_window;
GtkWidget* place_window;

/* 스크롤 윈도우 */
GtkWidget* place_scrolled_window;
GtkWidget* bus_scrolled_window;

/* 버튼 확인 */
GPtrArray* place_button_num;
GPtrArray* bus_button_num;

// 주요 장소 선택 버튼 확인 시 사용
GPtrArray* place_station_button;

/* 구현 완료 함수 */
void Read_File_Bus(char*, Bus*);				// 파일 읽기 함수(버스)
void Read_File_Place(char*, Place*);			// 파일 읽기 함수(장소)
char* EncodingKR(char*);						// 한글 인코딩 함수
void Close_Window(GtkWidget*, GPtrArray*);		// 이전 화면 돌아가는 함수
void Main_Menu();								// 메인 화면 출력
void Bus_Menu(GtkWidget*, gpointer);			// 버스 선택 출력
void Bus_Station(GtkWidget*);					// 버스 선택 후 해당 정류장 출력
void Place_Menu(GtkWidget*, gpointer);			// 주요 장소 출력
void Place_Bus_Station(GtkWidget*);				// 주요 장소 근처 정류장 출력
double deg2rad(double);							// 각도를 라디안으로 변환
void KnowToButton(GtkWidget*, int);				// 클릭 주요장소 확인
void KnowToButtonBUS(GtkWidget*, int);			// 클릭 버스 확인
double Calc_Dis(double, double, double, double);	// 거리 계산
void Dis_Result(double, double, Near*, Bus*);		// 거리 판정 결과
void Label_Inform(GtkWidget*);				// 선택 버튼 정류장 정보 저장
void KnowToLabel(GtkWidget*, int);			// 정류장 선택 확인

/* 스크롤 윈도우 중복 확인 */
char check_frame = 0;

// 현재 누른 버튼이 start, end 인지 확인
char check_start = 0;
char check_end = 0;

/// <summary>
/// 메인 함수. 파일 읽기 실행
/// </summary>
int main(int argc, char** argv)
{
	GtkWidget* label;
	
	#pragma region 버스 정보 저장

	A = (Bus*)malloc(sizeof(Bus) * 100);
	Read_File_Bus("512.csv", A);
	
	#pragma endregion


	#pragma region 주요 장소 정보 저장

	main_place = (Place*)malloc(sizeof(Place));
	Read_File_Place("place.csv", main_place);

	#pragma endregion

	// gtk 초기화
	gtk_init(&argc, &argv);

	Main_Menu();

	//// 색상 정보 설정 테스트
	//c.red = 1.0;
	//c.green = 0.0;
	//c.blue = 0.0;
	//c.alpha = 1.0;

	gtk_main();

	return 0;
}

/// <summary>
/// 초기 화면(메인 화면) 출력
/// </summary>
void Main_Menu()
{
	GtkWidget* frame;
	GtkWidget* bus_button;
	GtkWidget* place_button;

	// GtkStyleContext* context;

	char* temp_string;

	// 버튼 ui 테스트
	/*GtkCssProvider* provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, "../GTKBusRoute/test.css", NULL);*/

	#pragma region 윈도우 창 생성

	// 윈도우 창 생성 및 설정
	temp_string = EncodingKR("버스 노선도");
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(main_window), temp_string);

	// 프레임 생성
	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(main_window), frame);

	#pragma endregion

	#pragma region 버튼 생성

	// 버튼 생성 후 프레임에 고정
	temp_string = EncodingKR("버스 정류장");
	bus_button = gtk_button_new_with_label(temp_string);
	/*context = gtk_widget_get_style_context(bus_button);
	gtk_style_context_add_class(context, "enter_button");*/
	gtk_widget_set_size_request(bus_button, 100, 75);
	gtk_fixed_put(GTK_FIXED(frame), bus_button, 250, 400);
	
	// 원형 버튼 테스트
	/*gtk_style_context_add_class(
		gtk_widget_get_style_context(GTK_WIDGET(bus_button)),
		"circular"
	);*/

	temp_string = EncodingKR("주요 장소");
	place_button = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(place_button, 100, 75);
	gtk_fixed_put(GTK_FIXED(frame), place_button, 450, 400);

	#pragma endregion

	gtk_widget_show_all(main_window);

	g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	#pragma region 버튼 클릭

	g_signal_connect(bus_button, "clicked", G_CALLBACK(Bus_Menu), main_window);
	g_signal_connect(place_button, "clicked", G_CALLBACK(Place_Menu), main_window);

	#pragma endregion
}

/// <summary>
/// 버스 선택 화면을 출력
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

	// 이전 창을 숨김
	gtk_widget_hide(window);

	check_frame = 0;

	#pragma region 새 창 생성

	temp_string = EncodingKR("버스 정류장");
	bus_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(bus_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(bus_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(bus_window), temp_string);

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(bus_window), frame);

	#pragma endregion

	#pragma region 버스 버튼 생성

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

	#pragma endregion

	#pragma region 출도착 정류장 정보 표시

	temp_string = EncodingKR("출발 지점: ");
	start_label = gtk_label_new(temp_string);
	gtk_fixed_put(GTK_FIXED(frame), start_label, 200, 500);

	temp_string = EncodingKR("도착 지점: ");
	end_label = gtk_label_new(temp_string);
	gtk_fixed_put(GTK_FIXED(frame), end_label, 480, 500);

	#pragma endregion

	#pragma region 뒤로 가기 버튼

	temp_string = EncodingKR("뒤로 가기");
	closeButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(closeButton, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), closeButton, 680, 550);

	#pragma endregion

	#pragma region 뒤로 가기

	temp = g_ptr_array_new();
	g_ptr_array_add(temp, bus_window);
	g_ptr_array_add(temp, main_window);

	g_signal_connect(closeButton, "clicked", G_CALLBACK(Close_Window), temp);

	#pragma endregion

	#pragma region 버스 클릭

	bus_button_num = g_ptr_array_new();
	g_ptr_array_add(bus_button_num, frame);

	for (int j = 0; j < 4; j++) {
		g_signal_connect(busButton[j], "clicked", G_CALLBACK(KnowToButtonBUS), j);
	}

	#pragma endregion

	gtk_window_set_modal(GTK_WINDOW(bus_window), TRUE);
	gtk_widget_show_all(bus_window);
}

/// <summary>
/// 버스 선택 후 해당 버스 정류장 출력
/// </summary>
/// <param name="widget"></param>
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

	#pragma region 스크롤 윈도우 생성

	bus_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(bus_scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

	table = gtk_table_new(10, 10, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_scrolled_window_add_with_viewport(
		GTK_SCROLLED_WINDOW(bus_scrolled_window), table);

	#pragma endregion

	curr = A->next;
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
/// 주요 장소 선택 화면을 출력
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

	#pragma region 새 창 생성

	temp_string = EncodingKR("주요 장소");
	place_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(place_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(place_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(place_window), temp_string);

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(place_window), frame);

	#pragma endregion

	#pragma region 주요 장소 버튼 생성

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

	#pragma endregion

	#pragma region 출도착 정류장 정보 표시

	temp_string = EncodingKR("출발 지점: ");
	start_label = gtk_label_new(temp_string);
	gtk_fixed_put(GTK_FIXED(frame), start_label, 200, 500);

	temp_string = EncodingKR("도착 지점: ");
	end_label = gtk_label_new(temp_string);
	gtk_fixed_put(GTK_FIXED(frame), end_label, 480, 500);

	#pragma endregion

	#pragma region 버튼 생성

	temp_string = EncodingKR("결과 확인");
	resultButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(resultButton, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), resultButton, 680, 500);

	temp_string = EncodingKR("뒤로 가기");
	closeButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(closeButton, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), closeButton, 680, 550);

	#pragma endregion

	#pragma region 뒤로 가기

	temp = g_ptr_array_new();
	g_ptr_array_add(temp, place_window);
	g_ptr_array_add(temp, main_window);

	g_signal_connect(closeButton, "clicked", G_CALLBACK(Close_Window), temp);

	#pragma endregion

	#pragma region 주요 장소 클릭

	place_button_num = g_ptr_array_new();
	g_ptr_array_add(place_button_num, frame);

	curr = main_place->next;
	while (curr != NULL)
	{
		g_signal_connect(placeButton[j], "clicked", G_CALLBACK(KnowToButton), j);
		curr = curr->next;
		j++;
	}

	#pragma endregion

	// 결과 확인 버튼 테스트
	if (check_start == 1 && check_end == 1)
		g_signal_connect(resultButton, "clicked", G_CALLBACK(Main_Menu), NULL);

	gtk_window_set_modal(GTK_WINDOW(place_window), TRUE);
	gtk_widget_show_all(place_window);
}

/// <summary>
/// 주요 장소 근처의 정류장 출력
/// </summary>
/// <param name="widget"></param>
/// <param name="window"></param>
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

	#pragma region 스크롤 윈도우 생성

	place_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(place_scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

	table = gtk_table_new(10, 10, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_scrolled_window_add_with_viewport(
		GTK_SCROLLED_WINDOW(place_scrolled_window), table);

	#pragma endregion

	#pragma region 근처 장소 출력

	// 선택한 장소 찾기 위함
	curr = main_place->next;
	for (i = 0; i < g_ptr_array_index(place_button_num, 1); i++)
	{
		curr = curr->next;
	}
	temp_lat = curr->latitude;
	temp_lon = curr->longitude;

	near_station = (Near*)malloc(sizeof(Near) * 5);


	/* 버스 개수 만큼 */
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

	#pragma endregion

	// gptrarray사용 버튼 출력 테스트
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

	#pragma region 출도착 라벨 변경

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

	#pragma endregion

	/*temp = g_ptr_array_new();
	g_ptr_array_add(temp, place_window);
	g_ptr_array_add(temp, main_window);*/
	/*gtk_widget_grab_default(button);
	gtk_widget_show(button);
	gtk_widget_show(scrolled_window);*/

	#pragma region 출도착 정보 저장

	place_station_button = g_ptr_array_new();
	g_ptr_array_add(place_station_button, startlb);
	g_ptr_array_add(place_station_button, endlb);
	g_ptr_array_add(place_station_button, near_station);

	// 수정 중
	curr_result = near_station->next;
	j = 0;
	while (curr_result != NULL)
	{
		g_signal_connect(button[j], "clicked", G_CALLBACK(KnowToLabel), j);
		curr_result = curr_result->next;
		j++;
	}

	#pragma endregion

	/*for (j = 0; j < i; j++)
	{
		g_signal_connect(button[j], "clicked", G_CALLBACK(Close_Window), temp);
	}*/

	gtk_widget_show_all(place_window);
	g_ptr_array_remove_index(place_button_num, 1);
	check_frame = 1;



	/*
	클릭한 장소(num)의 위도 및 경도
	모든 버스 노선도와 비교 일정 값 이하 값 출력
	버튼으로 출력
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

	temp_string = EncodingKR("뒤로 가기");
	closeButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(closeButton, 80, 35);
	gtk_fixed_put(GTK_FIXED(tree_view), closeButton, 300, 300);
	gtk_widget_show(tree_view);
	
	gtk_fixed_put(GTK_FIXED(frame), subwindow, 200, 35);*/

}

/// <summary>
/// 클릭한 버튼의 이름을 받아와 라벨에 적용 및 저장
/// 주요 장소 기준 코딩
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
		strcpy_s(start, sizeof(start), EncodingKR(curr->station));
		gtk_label_set_text(g_ptr_array_index(place_station_button, 0), start);
		check_start = 1;
	}
	else if (check_start == 1 && check_end == 0)
	{
		strcpy_s(end, sizeof(end), EncodingKR(curr->station));
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

/// <summary>
/// 거리를 계산 하여 근처 정류장 정보 저장
/// </summary>
/// <param name="temp_lat">기준이 되는 위도</param>
/// <param name="temp_lon">기준이 되는 경도</param>
/// <param name="checking">근처 정류장을 저장할 구조체 연결리스트</param>
/// <param name="ch_bus">비교할 버스</param>
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

/// <summary>
/// 주요 장소 선택 화면에서
/// 클릭한 정류장의 정보를 파악
/// </summary>
/// <param name="widget"></param>
/// <param name="button_num">클릭한 버튼의 인덱스 정보</param>
void KnowToLabel(GtkWidget* widget, int button_num)
{
	g_ptr_array_add(place_station_button, (gpointer)button_num);
	Label_Inform(widget);
}

/// <summary>
/// 반복으로 출력한 버튼을 클릭했을 때
/// 어떤 버튼을 클릭했는지 확인
/// 주요 장소에서 사용
/// </summary>
/// <param name="widget"></param>
/// <param name="button_num">클릭한 버튼의 인덱스 정보</param>
void KnowToButton(GtkWidget* widget, int button_num)
{
	g_ptr_array_add(place_button_num, (gpointer)button_num);
	Place_Bus_Station(widget);
}

/// <summary>
/// 반복으로 출력한 버튼을 클릭했을 때
/// 어떤 버튼을 클릭했는지 확인
/// 버스 선택에서 사용
/// </summary>
/// <param name="widget"></param>
/// <param name="button_num">클릭한 버튼의 인덱스 정보</param>
void KnowToButtonBUS(GtkWidget* widget, int button_num)
{
	g_ptr_array_add(bus_button_num, (gpointer)button_num);
	Bus_Station(widget);
}

/// <summary>
/// 이전 화면으로 돌아가는 기능
/// </summary>
/// <param name="widget"></param>
/// <param name="window">gpointer 여러개를 받아오기 위한 gpointer 배열</param>
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
/// 좌표간 거리를 계산하여 리턴
/// </summary>
/// <param name="clicked_lat">클릭한 장소의 위도</param>
/// <param name="clicked_lon">클릭한 장소의 경도</param>
/// <param name="check_lat">비교할 정류장의 위도</param>
/// <param name="check_lon">비교할 정류장의 경도</param>
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
/// 라디안 변환 함수
/// </summary>
/// <param name="degree">변환할 각도 값</param>
double deg2rad(double degree)
{
	return degree * M_PI / 180;
}

/// <summary>
/// 버스 정보 파일 읽기 함수
/// </summary>
/// <param name="name">읽어올 파일 이름</param>
/// <param name="bus_num">버스 정보를 저장할 구조체</param>
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
/// 주요 장소 파일 읽기 함수
/// </summary>
/// <param name="name">읽어올 파일 이름</param>
/// <param name="place">장소 정보를 저장할 구조체</param>
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
/// 한글 인코딩을 위한 함수
/// 한글 사용전에 본 함수 사용
/// </summary>
/// <param name="input">변환하고자 하는 한국어</param>
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