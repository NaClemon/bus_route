#pragma warning(disable:4996)

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
	struct bus* back;
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

/* 결과 구조체 */
typedef struct detale_p
{
	Bus* search1; //출발
	Bus* search2; //도착
	Bus* search_s; //환승
	Bus* search_f; //환승
	int min;      //소요시간
	int min_d;
	char check_start; //출발에대해 back확인
	char check_end;   

}Detale_p;

/* 버스 개수 만큼 전역 변수 설정 */
Bus* A, * B, * C, * D;

/* 주요 장소 */
Place* main_place;

/* 출발, 도착 */
char start[255];
char end[255];
Detale_p a;

/* 화면 */
GtkWidget* main_window;
GtkWidget* bus_window;
GtkWidget* place_window;
GtkWidget* result_window;

/* 스크롤 윈도우 */
GtkWidget* place_scrolled_window;
GtkWidget* bus_scrolled_window;
GtkWidget* detale_scrolled_window;


/* 버튼 확인 */
GPtrArray* place_button_num;
GPtrArray* bus_button_num;
GPtrArray* detale_num;

// 주요 장소 선택 버튼 확인 시 사용
GPtrArray* place_station_button;
GPtrArray* bus_station_button;

/* 화면 출력*/
void Close_Window(GtkWidget*, GPtrArray*);		// 이전 화면 돌아가는 함수
void Main_Menu();								// 메인 화면 출력
void Bus_Menu(GtkWidget*, gpointer);			// 버스 선택 출력
void Bus_Station(GtkWidget*);					// 버스 선택 후 해당 정류장 출력
void Place_Menu(GtkWidget*, gpointer);			// 주요 장소 출력
void Place_Bus_Station(GtkWidget*);				// 주요 장소 근처 정류장 출력
void Result_Menu(GtkWidget*, gpointer);			// 결과 화면 출력
void Detail_Result(GtkWidget*);					// 자세한 결과 화면
void KnowToButton(GtkWidget*, int);				// 클릭 주요장소 확인
void KnowToButtonBUS(GtkWidget*, int);			// 클릭 버스 확인
void Label_Inform(GtkWidget*);					// 선택 버튼 정류장 정보 저장(주요 장소)
void Label_Inform_bus(GtkWidget*);				// 선택 버튼 정류장 정보 저장(버스 선택)
void KnowToLabel(GtkWidget*, int);				// 정류장 선택 확인(주요 장소)
void KnowToLabelBUS(GtkWidget*, int);			// 정류장 선택 확인(버스 선택)
void KnowToButtondetale(GtkWidget* , int );

/* 기능 관련 */
void Read_File_Bus(char*, Bus*);					// 파일 읽기 함수(버스)
void Read_File_Place(char*, Place*);				// 파일 읽기 함수(장소)
char* EncodingKR(char*);							// 한글 인코딩 함수
double deg2rad(double);								// 각도를 라디안으로 변환
double Calc_Dis(double, double, double, double);	// 거리 계산
void Dis_Result(double, double, Near*, Bus*, int);		// 거리 판정 결과
void myCSS(void);									// css 파일 로드
void Calc_Detale();                       // 거리계산 

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
	#pragma region 버스 정보 저장

	A = (Bus*)malloc(sizeof(Bus) * 100);
	Read_File_Bus("512.csv", A);
	B = (Bus*)malloc(sizeof(Bus) * 100);
	Read_File_Bus("105.csv", B);
	C = (Bus*)malloc(sizeof(Bus) * 100);
	Read_File_Bus("717.csv", C);
	D = (Bus*)malloc(sizeof(Bus) * 100);
	Read_File_Bus("823.csv", D);
	
	#pragma endregion


	#pragma region 주요 장소 정보 저장

	main_place = (Place*)malloc(sizeof(Place));
	Read_File_Place("place.csv", main_place);

	#pragma endregion

	// gtk 초기화
	gtk_init(&argc, &argv);

	myCSS();
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
	GtkWidget* image;

	char* temp_string;

	#pragma region 윈도우 창 생성

	// 윈도우 창 생성 및 설정
	temp_string = EncodingKR("버스 노선도");
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(main_window), temp_string);

	// 프레임 생성
	frame = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(main_window), frame);

	image = gtk_image_new_from_file("backGI.png");
	gtk_layout_put(GTK_LAYOUT(frame), image, 0, 0);

	#pragma endregion

	#pragma region 버튼 생성

	// 버튼 생성 후 프레임에 고정
	temp_string = EncodingKR("버스 정류장");
	bus_button = gtk_button_new_with_label(temp_string);
	gtk_widget_set_name(bus_button, "bus_button");
	gtk_widget_set_size_request(bus_button, 100, 75);
	gtk_layout_put(GTK_LAYOUT(frame), bus_button, 145, 395);
	
	// 원형 버튼 테스트
	/*gtk_style_context_add_class(
		gtk_widget_get_style_context(GTK_WIDGET(bus_button)),
		"circular"
	);*/

	temp_string = EncodingKR("주요 장소");
	place_button = gtk_button_new_with_label(temp_string);
	gtk_widget_set_name(place_button, "place_button");
	gtk_widget_set_size_request(place_button, 100, 75);
	gtk_layout_put(GTK_LAYOUT(frame), place_button, 465, 395);

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
	GtkWidget* resultButton;
	GtkWidget* image;

	GPtrArray* temp;

	GtkWidget* start_label;
	GtkWidget* end_label;

	GtkStyleContext* cancel;
	GtkStyleContext* result;
	GtkStyleContext* labelstyle;

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

	frame = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(bus_window), frame);

	image = gtk_image_new_from_file("menu.jpg");
	gtk_layout_put(GTK_LAYOUT(frame), image, 0, 0);

	#pragma endregion

	#pragma region 버스 버튼 생성

	busButton[0] = gtk_button_new_with_label("");
	gtk_widget_set_size_request(busButton[0], 1, 1);
	gtk_widget_set_name(busButton[0], "bus105");
	label = gtk_label_new("105");
	gtk_layout_put(GTK_LAYOUT(frame), label, 25, 40);
	gtk_layout_put(GTK_LAYOUT(frame), busButton[0], 10, 5);

	busButton[1] = gtk_button_new_with_label("");
	gtk_widget_set_size_request(busButton[1], 1, 1);
	gtk_widget_set_name(busButton[1], "bus512");
	label = gtk_label_new("512");
	gtk_layout_put(GTK_LAYOUT(frame), label, 25, 100);
	gtk_layout_put(GTK_LAYOUT(frame), busButton[1], 10, 65);

	busButton[2] = gtk_button_new_with_label("");
	gtk_widget_set_size_request(busButton[2], 1, 1);
	gtk_widget_set_name(busButton[2], "bus717");
	label = gtk_label_new("717");
	gtk_layout_put(GTK_LAYOUT(frame), label, 25, 160);
	gtk_layout_put(GTK_LAYOUT(frame), busButton[2], 10, 125);

	busButton[3] = gtk_button_new_with_label("");
	gtk_widget_set_size_request(busButton[3], 1, 1);
	gtk_widget_set_name(busButton[3], "bus823");
	label = gtk_label_new("823");
	gtk_layout_put(GTK_LAYOUT(frame), label, 25, 220);
	gtk_layout_put(GTK_LAYOUT(frame), busButton[3], 10, 185);

	#pragma endregion

	#pragma region 출도착 정류장 정보 표시

	temp_string = EncodingKR("출발 지점: ");
	start_label = gtk_label_new(temp_string);
	labelstyle = gtk_widget_get_style_context(start_label);
	gtk_style_context_add_class(labelstyle, "label");
	//gtk_layout_put(GTK_LAYOUT(frame), start_label, 190, 450);
	gtk_layout_put(GTK_LAYOUT(frame), start_label, 120, 550);

	temp_string = EncodingKR("도착 지점: ");
	end_label = gtk_label_new(temp_string);
	labelstyle = gtk_widget_get_style_context(end_label);
	gtk_style_context_add_class(labelstyle, "label");
	//gtk_layout_put(GTK_LAYOUT(frame), end_label, 460, 450);
	gtk_layout_put(GTK_LAYOUT(frame), end_label, 400, 550);

	#pragma endregion

	#pragma region 기능 버튼

	temp_string = EncodingKR("결과 확인 ▶");
	resultButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(resultButton, 80, 35);
	result = gtk_widget_get_style_context(resultButton);
	gtk_style_context_add_class(result, "result");
	gtk_layout_put(GTK_LAYOUT(frame), resultButton, 685, 500);

	temp_string = EncodingKR("◀ 뒤로 가기");
	closeButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(closeButton, 80, 35);
	cancel = gtk_widget_get_style_context(closeButton);
	gtk_style_context_add_class(cancel, "back");
	gtk_layout_put(GTK_LAYOUT(frame), closeButton, 675, 550);

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

	// 결과 확인 버튼 테스트
	g_signal_connect(resultButton, "clicked", G_CALLBACK(Result_Menu), bus_window);

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

	GtkWidget* startlb;
	GtkWidget* endlb;

	GPtrArray* temp;
	Bus* curr;
	GdkColor color;

	GtkStyleContext* listbt;
	GtkStyleContext* labelstyle;

	char* temp_string;
	int i = 0;
	int j, bus = g_ptr_array_index(bus_button_num, 1);

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

	#pragma region 버스 정류장 출력

	if (bus == 0) { //105
		curr = B->next;
		i = 0;
		while (curr != NULL)
		{
			button[i] = gtk_button_new_with_label(EncodingKR(curr->station));
			gtk_widget_set_size_request(button[i], 20, 3);
			listbt = gtk_widget_get_style_context(button[i]);
			gtk_style_context_add_class(listbt, "105list");
			gtk_table_attach_defaults(GTK_TABLE(table), button[i], 0, 1, i, i + 1);
			gtk_widget_show(button[i]);
			curr = curr->next;
			i++;
		}
	}
	if (bus == 1) { //512
		curr = A->next;
		i = 0;
		while (curr != NULL)
		{
			button[i] = gtk_button_new_with_label(EncodingKR(curr->station));
			gtk_widget_set_size_request(button[i], 20, 3);
			listbt = gtk_widget_get_style_context(button[i]);
			gtk_style_context_add_class(listbt, "512list");
			gtk_table_attach_defaults(GTK_TABLE(table), button[i], 0, 1, i, i + 1);
			gtk_widget_show(button[i]);
			curr = curr->next;
			i++;
		}
	}
	if (bus == 2) { //717
		curr = C->next;
		i = 0;
		while (curr != NULL)
		{
			button[i] = gtk_button_new_with_label(EncodingKR(curr->station));
			gtk_widget_set_size_request(button[i], 20, 3);
			listbt = gtk_widget_get_style_context(button[i]);
			gtk_style_context_add_class(listbt, "717list");
			gtk_table_attach_defaults(GTK_TABLE(table), button[i], 0, 1, i, i + 1);
			gtk_widget_show(button[i]);
			curr = curr->next;
			i++;
		}
	}
	if (bus == 3) { //823
		curr = D->next;
		i = 0;
		while (curr != NULL)
		{
			button[i] = gtk_button_new_with_label(EncodingKR(curr->station));
			gtk_widget_set_size_request(button[i], 20, 3);
			listbt = gtk_widget_get_style_context(button[i]);
			gtk_style_context_add_class(listbt, "823list");
			gtk_table_attach_defaults(GTK_TABLE(table), button[i], 0, 1, i, i + 1);
			gtk_widget_show(button[i]);
			curr = curr->next;
			i++;
		}
	}

	#pragma endregion

	if (check_start == 0)
	{
		temp_string = EncodingKR("");
		startlb = gtk_label_new(temp_string);
	}
	else
		startlb = gtk_label_new(EncodingKR(start));
	labelstyle = gtk_widget_get_style_context(startlb);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(g_ptr_array_index(bus_button_num, 0)), startlb, 200, 551);

	if (check_end == 0)
	{
		temp_string = EncodingKR("");
		endlb = gtk_label_new(temp_string);
	}
	else
		endlb = gtk_label_new(EncodingKR(end));
	labelstyle = gtk_widget_get_style_context(endlb);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(g_ptr_array_index(bus_button_num, 0)), endlb, 480, 551);

	bus_station_button = g_ptr_array_new();
	g_ptr_array_add(bus_station_button, startlb);
	g_ptr_array_add(bus_station_button, endlb);
	g_ptr_array_add(bus_station_button, bus);

	gtk_layout_put(GTK_LAYOUT(g_ptr_array_index(bus_button_num, 0)), bus_scrolled_window, 200, 10);
	gtk_widget_set_size_request(bus_scrolled_window, 400, 400);

	temp = g_ptr_array_new();
	g_ptr_array_add(temp, bus_window);
	g_ptr_array_add(temp, main_window);

	for (j = 0; j < i; j++)
	{
		g_signal_connect(button[j], "clicked", G_CALLBACK(KnowToLabelBUS), j);
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
	GtkWidget* image;

	GtkWidget* start_label;
	GtkWidget* end_label;

	GtkStyleContext* cancel;
	GtkStyleContext* result;
	GtkStyleContext* labelstyle;
	GtkStyleContext* plstyle;

	Place* curr;
	GtkWidget* table;

	gtk_widget_hide(window);

	check_frame = 0;

	#pragma region 새 창 생성

	temp_string = EncodingKR("주요 장소");
	place_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(place_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(place_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(place_window), temp_string);

	frame = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(place_window), frame);

	image = gtk_image_new_from_file("menu.jpg");
	gtk_layout_put(GTK_LAYOUT(frame), image, 0, 0);

	table = gtk_table_new(10, 10, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 25);
	gtk_table_set_col_spacings(GTK_TABLE(table), 15);

	#pragma endregion

	#pragma region 주요 장소 버튼 생성

	curr = main_place->next;
	while (curr != NULL)
	{
		placeButton[i] = gtk_button_new_with_label(curr->name);
		gtk_widget_set_size_request(placeButton[i], 10, 10);
		plstyle = gtk_widget_get_style_context(placeButton[i]);
		gtk_style_context_add_class(plstyle, "place_btn");
		gtk_table_attach_defaults(GTK_TABLE(table), placeButton[i],
			0, 1, i, i + 1);
		gtk_widget_show(placeButton[i]);
		curr = curr->next;
		i++;
	}
	gtk_layout_put(GTK_LAYOUT(frame), table, 10, 10);

	#pragma endregion

	#pragma region 출도착 정류장 정보 표시

	temp_string = EncodingKR("출발 지점: ");
	start_label = gtk_label_new(temp_string);
	labelstyle = gtk_widget_get_style_context(start_label);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(frame), start_label, 120, 550);

	temp_string = EncodingKR("도착 지점: ");
	end_label = gtk_label_new(temp_string);
	labelstyle = gtk_widget_get_style_context(end_label);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(frame), end_label, 400, 550);

	#pragma endregion

	#pragma region 버튼 생성

	temp_string = EncodingKR("결과 확인 ▶");
	resultButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(resultButton, 80, 35);
	result = gtk_widget_get_style_context(resultButton);
	gtk_style_context_add_class(result, "result");
	gtk_layout_put(GTK_LAYOUT(frame), resultButton, 685, 500);

	temp_string = EncodingKR("◀ 뒤로 가기");
	closeButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(closeButton, 80, 35);
	cancel = gtk_widget_get_style_context(closeButton);
	gtk_style_context_add_class(cancel, "back");
	gtk_layout_put(GTK_LAYOUT(frame), closeButton, 675, 550);

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
	g_signal_connect(resultButton, "clicked", G_CALLBACK(Result_Menu), place_window);

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
	GtkWidget* button[30];

	GtkWidget* startlb;
	GtkWidget* endlb;

	GdkColor color;

	GtkStyleContext* listbt;
	GtkStyleContext* labelstyle;

	Place* curr;
	Near* near_station = NULL;
	Near* curr_result = NULL;
	char buffer[32];
	double temp_lat, temp_lon;
	double comp_dis;
	char* temp_string;
	int i;
	int j;
	
	if (check_frame == 1)
		gtk_container_remove(GTK_CONTAINER(g_ptr_array_index(place_button_num, 0)), place_scrolled_window);

	#pragma region 스크롤 윈도우 생성

	place_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(place_scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

	table = gtk_table_new(10, 10, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 40);
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


	/* 근처 정류장 체크 */
	Dis_Result(temp_lat, temp_lon, near_station, A, 1);

	curr_result = near_station->next;
	i = 0;
	while (curr_result != NULL)
	{
		button[i] = gtk_button_new_with_label(EncodingKR(curr_result->station));
		listbt = gtk_widget_get_style_context(button[i]);
		gtk_style_context_add_class(listbt, "near_btn");
		gtk_table_attach_defaults(GTK_TABLE(table), button[i],
			0, 1, i, i + 1);
		gtk_widget_show(button[i]);
		curr_result = curr_result->next;
		i++;
	}

	#pragma endregion
	
	gtk_layout_put(GTK_LAYOUT(g_ptr_array_index(place_button_num, 0)), place_scrolled_window, 200, 10);
	gtk_widget_set_size_request(place_scrolled_window, 400, 400);

	#pragma region 출도착 라벨 변경

	if (check_start == 0)
	{
		temp_string = EncodingKR("");
		startlb = gtk_label_new(temp_string);
	}
	else
		startlb = gtk_label_new(EncodingKR(start));
	labelstyle = gtk_widget_get_style_context(startlb);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(g_ptr_array_index(place_button_num, 0)), startlb, 200, 551);

	if (check_end== 0)
	{
		temp_string = EncodingKR("");
		endlb = gtk_label_new(temp_string);
	}
	else
		endlb = gtk_label_new(EncodingKR(end));
	labelstyle = gtk_widget_get_style_context(endlb);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(g_ptr_array_index(place_button_num, 0)), endlb, 480, 551);

	#pragma endregion

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

	gtk_widget_show_all(place_window);
	g_ptr_array_remove_index(place_button_num, 1);
	check_frame = 1;
}

/// <summary>
/// 결과 화면 출력
/// </summary>
/// <param name="widget"></param>
/// <param name="window"></param>
void Result_Menu(GtkWidget* widget, gpointer* window)
{
	char s[20];
	GtkWidget* frame;
	GtkWidget* closeButton;
	GtkWidget* detailButton;
	GtkWidget* image;

	GtkWidget* resultlb;
	GtkWidget* startb;
	GtkWidget* startb1;
	GtkWidget* endb;
	GtkWidget* endb1;
	GtkWidget* trans;
	GtkWidget* trans1;
	GtkWidget* arrow[20];

	GtkWidget* min;
	GtkWidget* min1;

	GPtrArray* temp;

	GtkStyleContext* cancel;
	GtkStyleContext* labelstyle;

	char* temp_string;
	int ai = 0;

	check_frame = 0;
	
	if (check_start != 1 || check_end != 1)
		return;
	gtk_widget_hide(window);

	#pragma region 윈도우 창 생성

	Calc_Detale();
	sprintf(s, "%d", a.min);

	temp_string = EncodingKR("결과");
	result_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(result_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(result_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(result_window), temp_string);

	frame = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(result_window), frame);
	
	image = gtk_image_new_from_file("resultbg.png");
	gtk_layout_put(GTK_LAYOUT(frame), image, 0, 0);

	temp_string = EncodingKR("경로");
	resultlb = gtk_label_new(temp_string);
	labelstyle = gtk_widget_get_style_context(resultlb);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(frame), resultlb, 75, 20);

	temp_string = EncodingKR("출발: ");
	startb = gtk_label_new(temp_string);
	labelstyle = gtk_widget_get_style_context(startb);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(frame), startb, 20, 55);

	temp_string = EncodingKR(a.search1->station);
	startb1 = gtk_label_new(temp_string);
	labelstyle = gtk_widget_get_style_context(startb1);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(frame), startb1, 63, 56);

	for (ai = 0; ai < 5; ai++)
	{
		arrow[ai] = gtk_label_new("|");
		labelstyle = gtk_widget_get_style_context(arrow[ai]);
		gtk_style_context_add_class(labelstyle, "label");
		gtk_layout_put(GTK_LAYOUT(frame), arrow[ai], 85, 70 + ai*13);
	}

	if (a.check_end != '2')
	{
		arrow[5] = gtk_label_new(EncodingKR("▼"));
		labelstyle = gtk_widget_get_style_context(arrow[5]);
		gtk_style_context_add_class(labelstyle, "label");
		gtk_layout_put(GTK_LAYOUT(frame), arrow[5], 80.5, 70 + 5 * 13);

		temp_string = EncodingKR("환승: ");
		trans = gtk_label_new(temp_string);
		labelstyle = gtk_widget_get_style_context(trans);
		gtk_style_context_add_class(labelstyle, "label");
		gtk_layout_put(GTK_LAYOUT(frame), trans, 20, 150);

		temp_string = EncodingKR(a.search_s->station);
		trans1 = gtk_label_new(temp_string);
		labelstyle = gtk_widget_get_style_context(trans1);
		gtk_style_context_add_class(labelstyle, "label");
		gtk_layout_put(GTK_LAYOUT(frame), trans1, 63, 151);

		for (ai = 6; ai < 11; ai++)
		{
			arrow[ai] = gtk_label_new("|");
			labelstyle = gtk_widget_get_style_context(arrow[ai]);
			gtk_style_context_add_class(labelstyle, "label");
			gtk_layout_put(GTK_LAYOUT(frame), arrow[ai], 85, 73 + (ai+1) * 13);
		}

		arrow[12] = gtk_label_new(EncodingKR("▼"));
		labelstyle = gtk_widget_get_style_context(arrow[12]);
		gtk_style_context_add_class(labelstyle, "label");
		gtk_layout_put(GTK_LAYOUT(frame), arrow[12], 80.5, 70 + 12 * 13);
	}
	else
	{
		for (ai = 5; ai < 12; ai++)
		{
			arrow[ai] = gtk_label_new("|");
			labelstyle = gtk_widget_get_style_context(arrow[ai]);
			gtk_style_context_add_class(labelstyle, "label");
			gtk_layout_put(GTK_LAYOUT(frame), arrow[ai], 85, 70 + ai * 13);
		}

		arrow[12] = gtk_label_new(EncodingKR("▼"));
		labelstyle = gtk_widget_get_style_context(arrow[12]);
		gtk_style_context_add_class(labelstyle, "label");
		gtk_layout_put(GTK_LAYOUT(frame), arrow[12], 80.5, 70 + 12 * 13);
	}

	temp_string = EncodingKR("도착: ");
	endb = gtk_label_new(temp_string);
	labelstyle = gtk_widget_get_style_context(endb);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(frame), endb, 20, 250);

	
	temp_string = EncodingKR(a.search2->station);
	endb1 = gtk_label_new(temp_string);
	labelstyle = gtk_widget_get_style_context(endb1);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(frame), endb1, 63, 251);

	temp_string = EncodingKR("소요시간: ");
	min = gtk_label_new(temp_string);
	labelstyle = gtk_widget_get_style_context(min);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(frame), min, 20, 300);

	strcat(s, "분");
	min1 = gtk_label_new(EncodingKR(s));
	labelstyle = gtk_widget_get_style_context(min1);
	gtk_style_context_add_class(labelstyle, "label");
	gtk_layout_put(GTK_LAYOUT(frame), min1, 98, 300);

	#pragma endregion

	#pragma region 버튼

	temp_string = EncodingKR("◀ 뒤로 가기");
	closeButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(closeButton, 80, 35);
	cancel = gtk_widget_get_style_context(closeButton);
	gtk_style_context_add_class(cancel, "back");
	gtk_layout_put(GTK_LAYOUT(frame), closeButton, 680, 550);
	
	// 위치 수정 필요
	temp_string = EncodingKR("자세히 보기");
	detailButton = gtk_button_new_with_label(temp_string);
	gtk_widget_set_size_request(detailButton, 80, 35);
	gtk_widget_set_name(detailButton, "3dbtn");
	gtk_layout_put(GTK_LAYOUT(frame), detailButton, 20, 325);



	#pragma endregion

	// 수정 중
	#pragma region 뒤로 가기

	temp = g_ptr_array_new();
	g_ptr_array_add(temp, result_window);
	g_ptr_array_add(temp, main_window);

	detale_num= g_ptr_array_new();
	g_ptr_array_add(detale_num, frame);
	
	g_signal_connect(closeButton, "clicked", G_CALLBACK(Close_Window), temp);
	g_signal_connect(detailButton, "clicked", G_CALLBACK(Detail_Result), NULL);

	#pragma endregion

	gtk_window_set_modal(GTK_WINDOW(result_window), TRUE);
	gtk_widget_show_all(result_window);
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
		strcpy_s(start, sizeof(start), curr->station);
		gtk_label_set_text(g_ptr_array_index(place_station_button, 0), EncodingKR(start));
		check_start = 1;
	}
	else if (check_start == 1 && check_end == 0)
	{
		strcpy_s(end, sizeof(end), curr->station);
		if (strcmp(start, end) == 0)
		{
			strcpy_s(start, sizeof(start), "");
			gtk_label_set_text(g_ptr_array_index(place_station_button, 0), EncodingKR(start));
			check_start = 0;
		}
		else
		{
			gtk_label_set_text(g_ptr_array_index(place_station_button, 1), EncodingKR(end));
			check_end = 1;
		}
	}
	g_ptr_array_remove_index(place_station_button, 3);
}

/// <summary>
/// 클릭한 버튼의 이름을 받아와 라벨에 적용 및 저장
/// 버스 선택 기준 코딩
/// </summary>
/// <param name="widget"></param>
/// <param name="window"></param>
void Label_Inform_bus(GtkWidget* widget)
{
	Bus* curr = NULL;
	Bus* tmp = NULL;

	char* t;
	tmp = g_ptr_array_index(bus_station_button, 2);

	if (tmp == 0) { //105
		curr = B->next;
		for (int i = 0; i < g_ptr_array_index(bus_station_button, 3); i++)
		{
			curr = curr->next;
		}
	}
	if (tmp == 1) { //512
		curr = A->next;
		for (int i = 0; i < g_ptr_array_index(bus_station_button, 3); i++)
		{
			curr = curr->next;
		}
	}
	if (tmp == 2) { //717
		curr = C->next;
		for (int i = 0; i < g_ptr_array_index(bus_station_button, 3); i++)
		{
			curr = curr->next;
		}
	}
	if (tmp == 3) { //823
		curr = D->next;
		for (int i = 0; i < g_ptr_array_index(bus_station_button, 3); i++)
		{
			curr = curr->next;
		}
	}
	if (check_start == 0 && check_end == 0) {
		strcpy_s(start, sizeof(start), curr->station);
		gtk_label_set_text(g_ptr_array_index(bus_station_button, 0), EncodingKR(start));
		check_start = 1;
	}

	else if (check_start == 1 && check_end == 0)
	{
		strcpy_s(end, sizeof(end), curr->station);
		if (strcmp(start, end) == 0)
		{
			strcpy_s(start, sizeof(start), "");
			gtk_label_set_text(g_ptr_array_index(bus_station_button, 0), EncodingKR(start));
			check_start = 0;
		}
		else
		{
			gtk_label_set_text(g_ptr_array_index(bus_station_button, 1), EncodingKR(end));
			check_end = 1;
		}
	}
	g_ptr_array_remove_index(bus_station_button, 3);
}

/// <summary>
/// 거리를 계산 하여 근처 정류장 정보 저장
/// </summary>
/// <param name="temp_lat">기준이 되는 위도</param>
/// <param name="temp_lon">기준이 되는 경도</param>
/// <param name="checking">근처 정류장을 저장할 구조체 연결리스트</param>
/// <param name="ch_bus">비교할 버스</param>
void Dis_Result(double temp_lat, double temp_lon, Near* checking, Bus* ch_bus, int num)
{
	Bus* curr;
	Near* temp_near[20];

	int i;
	double comp_dis;
	int check = 0;

	curr = A->next;
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

			switch (check)
			{
			case 1:
				strcpy_s(temp_near[i]->bus_name, sizeof(temp_near[i]->bus_name), "A");
				break;
			case 2:
				strcpy_s(temp_near[i]->bus_name, sizeof(temp_near[i]->bus_name), "B");
				break;
			case 3:
				strcpy_s(temp_near[i]->bus_name, sizeof(temp_near[i]->bus_name), "C");
				break;
			case 4:
				strcpy_s(temp_near[i]->bus_name, sizeof(temp_near[i]->bus_name), "D");
				break;
			default:
				break;
			}
			
			strcpy_s(temp_near[i]->station, sizeof(temp_near[i]->station), curr->station);
			temp_near[i]->latitude = curr->latitude;
			temp_near[i]->longitude = curr->longitude;

			i++;
		}
		curr = curr->next;
		if (curr == NULL && check != 3)
		{
			switch (check)
			{
			case 0:
				curr = B->next;
				check = 1;
				break;
			case 1:
				curr = C->next;
				check = 2;
				break;
			case 2:
				curr = D->next;
				check = 3;
				break;
			}
		}
		else if (curr == NULL && check == 3)
			break;
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
/// 버스 선택 화면에서
/// 클릭한 정류장의 정보를 파악
/// </summary>
/// <param name="widget"></param>
/// <param name="button_num">클릭한 버튼의 인덱스 정보</param>
void KnowToLabelBUS(GtkWidget* widget, int button_num)
{
	g_ptr_array_add(bus_station_button, (gpointer)button_num);
	Label_Inform_bus(widget);
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


void KnowToButtondetale(GtkWidget* widget, int button_num)
{
	g_ptr_array_add(detale_num, (gpointer)button_num);
	Detail_Result(widget);
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
/// css 파일 로드
/// </summary>
void myCSS(void) {
	GtkCssProvider* provider;
	GdkDisplay* display;
	GdkScreen* screen;

	provider = gtk_css_provider_new();
	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen(display);
	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	const gchar* myCssFile = "test.css";
	GError* error = 0;

	gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
	g_object_unref(provider);
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
			{
				bus_num->next = bus_list[i];
				bus_list[i]->back = NULL;
			}
			else
			{
				bus_list[i]->back = bus_list[i - 1];
				bus_list[i - 1]->next = bus_list[i];
			}

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

void Calc_Detale()
{
	Bus* search1 = A;       //start
	Bus* search2 = A;       //end
	int min = 9999;         //최단경로
	int min_s = 1;          //최단경로 비교용 시간
	double s_distence = 0;    //버스 이동거리
	double f_distence = 0;    //버스 이동거리
	double w_distence = 0;    //환승역까지 걸어가는 길이
	Bus* Start = NULL;      //반복문1 ~4 
	Bus* Finish = NULL;
	Bus* Start_back = NULL;
	Bus* Finish_back = NULL;
	Bus* stemp = NULL;
	Bus* ftemp = NULL;
	char sp = '0', fp = '0';//환승여부

	a.search1 = NULL;
	a.search2 = NULL;
	a.search_f = NULL;
	a.search_s = NULL;
	a.min = 0;
	a.min_d = 0;
	a.check_end = 0;
	a.check_start = 0;

	/*Bus* a = (Bus*)malloc(sizeof(Bus));
	strcpy_s(a->station, sizeof(A->station), A->station);
	Bus* a1 = a;
	for (int i = 0; i < 80; i++)
	{
		if (search->next)
		{
			search = search->next;
			Bus* a2 = (Bus*)malloc(sizeof(Bus));
			strcpy_s(a2->station, sizeof(search->station), search->station);
			a1->next = a2;
		}
		else
			break;

	}
	a1->next = a;
	//이작업을 A부터 모든 버스에 적용켜야 함 5/20 이종영


	s_state = (char**)malloc(sizeof(char*)*80);
	f_state = (char**)malloc(sizeof(char*) * 80);

	for (int i = 0; i < 80; i++)
	{
		s_state[i] = (char*)malloc(sizeof(char) * 255);
		f_state[i] = (char*)malloc(sizeof(char) * 255);
	}
	*/
	
	//이작업을 A~모든 버스에 적용시켜야 함5/20 이종영
	//시작 정류장 해당 버스찾기
	search1 = A;
	while (1)
	{
		if (!strncmp(search1->station, start, sizeof(char) * 255))
		{
			Start = search1;
			Start_back = search1;
			stemp = search1;
			a.search1 = search1;
			sp = 'A';
			break;
		}
		search1 = search1->next;
		if (search1 == NULL)
			break;
	}
    if (sp == '0')
	{
		search1 = B;
		while (1)
		{
			if (!strncmp(search1->station, start, sizeof(char) * 255))
			{
				Start = search1;
				Start_back = search1;
				stemp = search1;
				a.search1 = search1;
				sp = 'B';
				break;
			}
			search1 = search1->next;
			if (search1 == NULL)
				break;
		}
	}
	if (sp == '0')
	{
		search1 = C;
		while (1)
		{
			if (!strncmp(search1->station, start, sizeof(char) * 255))
			{
				Start = search1;
				Start_back = search1;
				stemp = search1;
				a.search1 = search1;
				sp = 'C';
				break;
			}
			search1 = search1->next;
			if (search1 == NULL)
				break;
		}
	}
	if (sp == '0' )
	{
		search1 = D;
		while (1)
		{
			if (!strncmp(search1->station, start, sizeof(char) * 255))
			{
				Start = search1;
				Start_back = search1;
				stemp = search1;
				a.search1 = search1;
				sp = 'D';
				break;
			}
			search1 = search1->next;
			if (search1 == NULL)
				break;
		}
	}

	//이작업을 A~모든 버스에 적용시켜야 함5/20 이종영
	//도착 정류장 해당 버스찾기
	search2 = A;
	while (1)
	{
		if (!strncmp(search2->station, end, sizeof(char) * 255))
		{
			Finish = search2;
			Finish_back = search2;
			ftemp = search2;
			a.search2 = search2;
			fp = 'A';
			break;
		}
		search2 = search2->next;
		if (search2 == NULL)
			break;
	}
	if (fp == '0')
	{
		search2 = B;
		while (1)
		{
			if (!strncmp(search2->station, end, sizeof(char) * 255))
			{
				Finish = search2;
				Finish_back = search2;
				ftemp = search2;
				a.search2 = search2;
				fp = 'B';
				break;
			}
			search2 = search2->next;
			if (search2 == NULL)
				break;
		}
	}
	if (fp == '0' )
	{
		search2 = C;
		while (1)
		{
			if (!strncmp(search2->station, end, sizeof(char) * 255))
			{
				Finish = search2;
				Finish_back = search2;
				ftemp = search2;
				a.search2 = search2;
				fp = 'C';
				break;
			}
			search2 = search2->next;
			if (search2 == NULL)
				break;
		}
	}
	if (fp == '0')
	{
		search2 = D;
		while (1)
		{
			if (!strncmp(search2->station, end, sizeof(char) * 255))
			{
				Finish = search2;
				Finish_back = search2;
				ftemp = search2;
				a.search2 = search2;
				fp = 'D';
				break;
			}
			search2 = search2->next;
			if (search2==NULL)
				break;
		}
	}
	if (sp == fp) //환승없을때 
	{
		a.check_end = '2';
		//start~finish까지 출력
		while (1) //back으로 가야할지 next로 가야할지
		{
			if (Start == NULL)//반대편에 있을 것이다.
			{
				a.check_start = '1';
				while (Start_back != Finish)
				{
					stemp = Start_back;
					Start_back = Start_back->back;
					s_distence += Calc_Dis(Start_back->latitude, Start_back->longitude, stemp->latitude, stemp->longitude) + 1;
				}
				break;
			}
			if (Start == Finish)
			{
				a.check_start = '0';
				break;
			}
			stemp = Start;
			Start = Start->next;
			if (Start == NULL)
				s_distence = 0;
			else
				s_distence += Calc_Dis(Start->latitude, Start->longitude, stemp->latitude, stemp->longitude) + 1;
		}
		min = s_distence;
		a.search_f = NULL;
		a.search_s = NULL;
		a.min = min;
	}
	else//환승없을때
	{
		//환승 정류장 찾기
		while (1)
		{
			Start = search1;
			Start_back = search1;
			stemp = search1;
			if (Finish)
			{
				while (1)
				{
					if (Start != NULL)
					{
						s_distence += Calc_Dis(Start->latitude, Start->longitude, stemp->latitude, stemp->longitude) +0.5;
						w_distence = Calc_Dis(Start->latitude, Start->longitude, Finish->latitude, Finish->longitude);
						min_s = s_distence + f_distence + w_distence * 15;
						if (min_s < min)
						{
							min = min_s;
							a.check_start = '0'; // 출발 정류장에 대해 환승 정류장의 위치가 next 방향일때
							a.check_end = '0';
							a.min = min_s;
							a.min_d = w_distence * 10;
							a.search_s = Start;
							a.search_f = Finish;
						}
						stemp = Start;
						Start = Start->next;
						if (Start == NULL)
						{
							stemp = search1;
							s_distence = -1;
						}
					}
					else if (Start_back != NULL)
					{
						s_distence += Calc_Dis(Start_back->latitude, Start_back->longitude, stemp->latitude, stemp->longitude) +0.5;
						w_distence = Calc_Dis(Start_back->latitude, Start_back->longitude, Finish->latitude, Finish->longitude);
						min_s = s_distence + f_distence + w_distence * 15;
						if (min_s < min)
						{
							min = min_s;
							a.check_start = '1'; // 출발 정류장에 대해 환승 정류정의 위치가 back방향일때
							a.check_end = '0';
							a.min = min_s;
							a.min_d = w_distence * 10;
							a.search_s = Start_back;
							a.search_f = Finish;
						}
						stemp = Start_back;
						Start_back = Start_back->back;
						if (Start_back == NULL)
							s_distence = -1;
					}
					else
						break;
				}
				ftemp = Finish;
				Finish = Finish->next;
				if (Finish == NULL)
				{
					ftemp = search2;
					f_distence = 0;
				}
				else
					f_distence += Calc_Dis(Finish->latitude, Finish->longitude, ftemp->latitude, ftemp->longitude) + 1;
			}
			else if (Finish_back)
			{
				while (1)
				{
					if (Start)
					{
						s_distence += Calc_Dis(Start->latitude, Start->longitude, stemp->latitude, stemp->longitude) +0.5;
						w_distence = Calc_Dis(Start->latitude, Start->longitude, Finish_back->latitude, Finish_back->longitude);
						min_s = s_distence + f_distence + w_distence * 15;
						if (min_s < min)
						{
							min = min_s;
							a.check_start = '0';
							a.check_end = '1';
							a.min = min;
							a.min_d = w_distence * 10;
							a.search_s = Start;
							a.search_f = Finish_back;
						}
						stemp = Start;
						Start = Start->next;
						if (Start == NULL)
						{
							stemp = search1;
							s_distence = -1;
						}
					}
					else if (Start_back)
					{
						s_distence += Calc_Dis(Start_back->latitude, Start_back->longitude, stemp->latitude, stemp->longitude) +0.5;
						w_distence = Calc_Dis(Start_back->latitude, Start_back->longitude, Finish_back->latitude, Finish_back->longitude);
						min_s = s_distence + f_distence + w_distence * 15;
						if (min_s < min)
						{
							min = min_s;
							a.check_start = '1';
							a.check_end = '1';
							a.min = min_s;
							a.min_d = w_distence * 10;
							a.search_s = Start_back;
							a.search_f = Finish_back;
						}
						stemp = Start_back;
						Start_back = Start_back->back;
					}
					else
						break;
				}
				ftemp = Finish_back;
				Finish_back = Finish_back->back;
				if(Finish_back!=NULL)
				f_distence += Calc_Dis(Finish_back->latitude, Finish_back->longitude, ftemp->latitude, ftemp->longitude) + 1;
			}
			else
				break;

		}

	}
}
void Detail_Result(GtkWidget* widget)
{
	GtkWidget* frame;
	GtkWidget* table;
	GtkWidget* button[100];
	GtkWidget* button2[100];
	GtkWidget* labels[100];
	GtkWidget* sublabels[100];

	GtkWidget* trans;
	GtkWidget* trans1;
	char* temp_string;
	char* s[50];
	char tempstr[255];
	Bus* curr;
	
	GtkStyleContext* listbt;
	GtkStyleContext* listbt1;
	GtkStyleContext* listbt2;

	int tempi = 0;
	int i = 0;
	int j;

	if (check_frame == 1)
		gtk_container_remove(GTK_CONTAINER(g_ptr_array_index(detale_num, 0)), detale_scrolled_window);

#pragma region 스크롤 윈도우 생성

	detale_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(detale_scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

	table = gtk_table_new(10, 10, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 40);
	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_scrolled_window_add_with_viewport(
		GTK_SCROLLED_WINDOW(detale_scrolled_window), table);



#pragma endregion

	curr = a.search1;
	if (a.check_end == '2')
	{
		while (curr != a.search2)
		{
			if (i != 0 && i % 5 == 0)
				tempi += 1;
			if (i == 0)
				sprintf(tempstr, "%s", curr->station);
			else
				sprintf(tempstr, "-----▶   %s", curr->station);
			labels[i] = gtk_label_new(EncodingKR(tempstr));
			listbt2 = gtk_widget_get_style_context(labels[i]);
			gtk_style_context_add_class(listbt2, "label");
			gtk_table_attach_defaults(GTK_TABLE(table), labels[i], i - (tempi * 5), i - (tempi * 5) + 1, tempi, tempi + 1);

			if (a.check_start == '0')
				curr = curr->next;
			else
				curr = curr->back;
			i++;
		}
		i++;
		sprintf(tempstr, "-----▶   %s", curr->station);
		labels[i] = gtk_label_new(EncodingKR(tempstr));
		listbt2 = gtk_widget_get_style_context(labels[i]);
		gtk_style_context_add_class(listbt2, "label");
		gtk_table_attach_defaults(GTK_TABLE(table), labels[i], (i - 1) - (tempi * 5), i - (tempi * 5), tempi, tempi + 1);
	}
	else
	{
		while (curr != a.search_s)
		{
			if (i != 0 && i % 5 == 0)
				tempi += 1;
			if (i == 0)
				sprintf(tempstr, "%s", curr->station);
			else
				sprintf(tempstr, "-----▶   %s", curr->station);
			labels[i] = gtk_label_new(EncodingKR(tempstr));
			listbt2 = gtk_widget_get_style_context(labels[i]);
			gtk_style_context_add_class(listbt2, "label");
			gtk_table_attach_defaults(GTK_TABLE(table), labels[i], i - (tempi * 5), i - (tempi * 5) + 1, tempi, tempi + 1);

			if (a.check_start == '0')
				curr = curr->next;
			else
				curr = curr->back;
			i++;
		}
		i++;
		sprintf(tempstr, "-----▶   %s", curr->station);
		labels[i] = gtk_label_new(EncodingKR(tempstr));
		listbt2 = gtk_widget_get_style_context(labels[i]);
		gtk_style_context_add_class(listbt2, "label");
		gtk_table_attach_defaults(GTK_TABLE(table), labels[i], (i - 1) - (tempi * 5), i - (tempi * 5), tempi, tempi + 1);

		temp_string = EncodingKR("도보 이동:");
		trans = gtk_label_new(temp_string);
		gtk_widget_set_size_request(trans, 5, 3);
		listbt2 = gtk_widget_get_style_context(trans);
		gtk_style_context_add_class(listbt2, "label");
		gtk_table_attach_defaults(GTK_LAYOUT(table), trans, 0, 1, 3, 4);

		sprintf(s, "%d분", a.min_d);
		trans1 = gtk_label_new(EncodingKR(s));
		gtk_widget_set_size_request(trans1, 5, 3);
		listbt2 = gtk_widget_get_style_context(trans1);
		gtk_style_context_add_class(listbt2, "label");
		gtk_table_attach_defaults(GTK_LAYOUT(table), trans1, 1, 2, 3, 4);

		i = 0;
		tempi = 0;
		curr = a.search_f;
		while (curr != a.search2)
		{
			if (i != 0 && i % 5 == 0)
				tempi += 1;
			if (i == 0)
				sprintf(tempstr, "%s", curr->station);
			else
				sprintf(tempstr, "-----▶   %s", curr->station);
			sublabels[i] = gtk_label_new(EncodingKR(tempstr));
			listbt2 = gtk_widget_get_style_context(sublabels[i]);
			gtk_style_context_add_class(listbt2, "label");
			gtk_table_attach_defaults(GTK_TABLE(table), sublabels[i], i - (tempi * 5), i - (tempi * 5) + 1, tempi + 4, tempi + 5);

			if (a.check_end == '1')
				curr = curr->next;
			else
				curr = curr->back;
			i++;
		}
		
		i++;
		sprintf(tempstr, "-----▶   %s", curr->station);
		sublabels[i] = gtk_label_new(EncodingKR(tempstr));
		listbt2 = gtk_widget_get_style_context(sublabels[i]);
		gtk_style_context_add_class(listbt2, "label");
		gtk_table_attach_defaults(GTK_TABLE(table), sublabels[i], (i - 1) - (tempi * 5), i - (tempi * 5), tempi + 4, tempi + 5);
	}

	gtk_layout_put(GTK_LAYOUT(g_ptr_array_index(detale_num, 0)), detale_scrolled_window, 200, 40);
	gtk_widget_set_size_request(detale_scrolled_window, 600, 400);

	gtk_widget_show_all(result_window);
	check_frame = 1;
}