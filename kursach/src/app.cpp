

#include "app.h"
using namespace std;

void kursapp() {
	abiturient* abiturients = nullptr;
	unsigned absize = 0;
	setlocale(LC_ALL,"RU_ru");
	const char* title = "База данных абитуриентов";
	menu_option entries[10];
	entries[0].label = "Загрузка данных из файла";
	entries[0].callback = data_load;
	entries[1].label = "Добавление данных в конец базы данных";
	entries[1].callback = append_entry;
	entries[2].label = "Вывод записей на экран";
	entries[2].callback = list_elems;
	entries[3].label = "Сохранение данных в файл";
	entries[3].callback = data_dump;
	entries[4].label = "Редактирование записей";
	entries[4].callback = edit_entry;
	entries[5].label = "Удаление записи";
	entries[5].callback = delete_entry;
	entries[6].label = "Удаление по условию";
	entries[6].callback = delete_matching;
	entries[7].label = "Замена записи";
	entries[7].callback = replace_entry;
	entries[8].label = "Удаление элементов начиная с n-го";
	entries[8].callback = delete_entries;
	entries[9].label = "Выход";
	entries[9].callback = exit_wrapper;
	while(true) do_menu(entries,10,title,abiturients,absize);
}
void do_menu(menu_option* opts,unsigned entries,const char* title,abiturient*& arr,unsigned &absize) {
	cout << "\033[2J\033[1;1H";
	cout << title << endl;
	cout << "-------------------------" << endl;
	for (unsigned i=0;i<entries;i++) {
		cout << i << " " << opts[i].label;
		cout << endl;
	}
	cout << "-------------------------" << endl;
	cout << ">";
	unsigned selected_option;
	cin >> selected_option;
	//scanf("%d",&selected_option);
	cout << "\033[2J\033[1;1H";
	//fflush(stdin);
	if (selected_option < entries){
		opts[selected_option].callback(arr,absize);
	} else {
		return;
	}
	cout << "Нажмите Enter для продолжения...";
	cin.get();
	cin.ignore(1);
}
void exit_wrapper(abiturient*& arr,unsigned& size){
	exit(0);
}

