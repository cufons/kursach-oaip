
#include "procedures.h"

//TODO implement entries list on edit
using namespace std;
void data_load(abiturient*& arr, unsigned& size){
	cout << "Введите имя файла, из которого нужно произвести ввод данных:";
	char filename[30];
	cin >> filename;
	cout << "Загрузка..." << endl;
	std::ifstream datafile(filename,std::ifstream::in);
	if (!datafile.is_open()) {
		cout << "Что-то пошло не так" << endl;
		return;
	}
	delete[] arr;
	size = 0;
	while(datafile.good()) {
		abiturient a;
		bool g;
		datafile.get(a.surname,20,' ');
		datafile >> a.birthyear >> a.avgmark >> a.ct_mark;
		datafile >> g;
		datafile.ignore();
		a.gender = (abiturient::GenderInfo)g;
		append((void**)&arr,size,sizeof(abiturient),&a);
	}
	list_elems(arr, size); // required
	datafile.close();
}
void append_entry(abiturient*& arr, unsigned& size){
	abiturient a;
	cout << "Введите фамилию:";
	cin >> a.surname;
	cout << endl;
	cout << "Введите год рождения:";
	cin >> a.birthyear;
	cout << endl;
	cout << "Введите средний балл аттестата:";
	cin >> a.avgmark;
	cout << endl;
	cout << "Введите балл ЦТ:";
	cin >> a.ct_mark;
	cout << endl;
	cout << "Введите пол абитуриента(0-мужской 1-женский):";
	unsigned choice;
	cin >> choice;
	if (choice) {
		a.gender = abiturient::female;
	} else {
		a.gender = abiturient::male;
	}
	cout << endl;
	append((void**)&arr,size,sizeof(abiturient),&a);
	list_elems(arr, size); // required
}
void list_elems(abiturient*& arr, unsigned& size){
	cout << "Информация о абитуриентах" << endl;
	cout << "ИД, Фамилия, Балл аттестата, Балл ЦТ, Пол" << endl;
	cout << "-----------------------------------------" << endl;
	for(unsigned i = 0;i<size;i++) {
		abiturient* ab = arr + i;
		printf("%3d, %20s, %4d, %4f, %3d, %c\n",i,ab->surname,ab->birthyear,ab->avgmark,ab->ct_mark,ab->gender == abiturient::male ? 'M' : 'F');
	}
}
void data_dump(abiturient*& arr, unsigned& size){
	cout << "Введите имя файла, в который нужно сохранить данные:";
	char filename[30];
	cin >> filename;
	cout << "Загрузка..." << endl;
	ofstream datafile(filename,ios::trunc | ios::out);
	if (!datafile) {
		cout << "Что-то пошло не так" << endl;
		return;
	}
	for(unsigned i = 0; i < size-1; i++) {
		abiturient* ab = arr + i;
		datafile << ab->surname << " "
				 << ab->birthyear << " "
				 << ab->avgmark << " "
				 << ab->ct_mark << " "
				 << ab->gender << "\n";
	}
	abiturient* ab = arr + size-1;
	datafile << ab->surname << " "
			 << ab->birthyear << " "
			 << ab->avgmark << " "
			 << ab->ct_mark << " "
			 << ab->gender;
	datafile.close();
}
void edit_entry(abiturient*& arr, unsigned& size){
	unsigned to_edit;
	bool modified = false;
	cout << "Введите ИД записи, которую нужно изменить:";
	cin >> to_edit;
	cout << endl;
	if (to_edit >= size || cin.fail()) {
		cout << "Неправильный ИД записи" << endl;
		cin.clear();
		return;
	}
	cin.ignore();
	abiturient& edited = arr[to_edit];
	cout << "Оставьте поле ввода пустым для сохранения исходного значения" << endl;
	cout << "Введите фамилию [" << edited.surname << "]:";
	char buf[30];
	cin.get(buf,30);
	if (strlen(buf)) {
		strcpy(edited.surname,buf);
		modified = true;
	}
	if(cin.fail()) cin.clear();
	cin.ignore();
	cout << endl;
	cout << "Введите год рождения [" << edited.birthyear << "]:";
	if(cin.peek() != '\n' || cin.fail()){
		cin >> edited.birthyear;
		modified = true;
	} else {
		cin.clear();
	}
	cin.ignore();
	cout << endl;
	cout << "Введите средний балл аттестата [" << edited.avgmark << "]:";
	if (cin.peek() != '\n') {
		cin >> edited.avgmark;
		modified = true;
	}else{
		cin.clear();
	}
	cin.ignore();
	cout << endl;
	cout << "Введите балл ЦТ [" << edited.ct_mark << "]:";
	if (cin.peek() != '\n') {
		cin >> edited.ct_mark;
		modified = true;
	}else {
		cin.clear();
	}
	cin.ignore();
	cout << endl;
	cout << "Введите пол абитуриента(0-мужской 1-женский) [" << edited.gender << "]:";
	bool choice;
	if(cin.peek() != '\n') {
		cin >> choice;
		edited.gender = (abiturient::GenderInfo)choice;
		modified = true;
	} else {
		cin.clear();
	}
	cout << endl;
	if(modified) list_elems(arr,size);
}
void delete_entry(abiturient*& arr, unsigned& size){
	unsigned to_del;
	cout << "Введите ИД записи, которую нужно удалить:";
	cin >> to_del;
	cout << endl;
	if (to_del < size) {
		remove((void**)&arr,size,sizeof(abiturient),to_del);
		list_elems(arr,size);
	} else {
		cout << "Запрошенной записи не существует!" << endl;
	}
}
void delete_matching(abiturient*& arr, unsigned& size){
	ab_predicate pred;
	bool minmax;
	cval val;
	int choice;
	bool hasDataChanged = false;
	cout << "Выберите поле, по которому будет осуществлятся сравнение удаляемого элемента." << endl <<
			"0 - год рождения" << endl <<
			"1 - средний балл аттестата" << endl <<
			"2 - средний балл ЦТ" << endl <<
			">";
	cin >> choice;
	cout << endl <<
			"Выберите тип сравнения (0 - поле < значение, 1 - поле > значение";
	cin >> minmax;
	cout << endl;
	cout << "Введите значение, с которым будет осуществлятся сравнение:";
	switch (choice) {
	case 0:
		pred = year_pred;
		cin >> val.ival;
		break;
	case 1:
		pred = mark_pred;
		cin >> val.fval;
		break;
	case 2:
		pred = ct_pred;
		cin >> val.ival;
		break;
	}
	for(int i = size-1;i>=0;i--) {
		abiturient& ab = arr[i];
		if (pred(ab,val,minmax)) {
			remove((void**)&arr,size,sizeof(abiturient),i);
			hasDataChanged = true;
		}
	}
	if (hasDataChanged) list_elems(arr,size);
}
void replace_entry(abiturient*& arr, unsigned& size){
	unsigned idx;
	cout << "Введите ИД элемента для замены:";
	cin >> idx;
	cout << endl;
	if (idx < 0 || idx > size-1 || !size) {
		cout << "Неправильный ИД";
		return;
	}
	abiturient& a = arr[idx];
	cout << "Введите фамилию:";
	cin >> a.surname;
	cout << endl;
	cout << "Введите год рождения:";
	cin >> a.birthyear;
	cout << endl;
	cout << "Введите средний балл аттестата:";
	cin >> a.avgmark;
	cout << endl;
	cout << "Введите балл ЦТ:";
	cin >> a.ct_mark;
	cout << endl;
	cout << "Введите пол абитуриента(0-мужской 1-женский):";
	unsigned choice;
	cin >> choice;
	if (choice) {
		a.gender = abiturient::female;
	} else {
		a.gender = abiturient::male;
	}
	cout << endl;
	list_elems(arr, size); // required
}
void delete_entries(abiturient*& arr, unsigned& size){
	unsigned idx1,idx2;
	cout << "Введите ИД первого элемента для удаления:";
	cin >> idx1;
	cout << "Введите ИД последнего элемента для удаления:";
	cin >> idx2;
	if (idx1 > idx2 || idx1 < 0 || idx1 > size-1 || !size) {
		cout << "Неправильные ИД" << endl;
		return;
	}
	for (unsigned i = idx2; i>=idx1 && i <= idx2;i--) {
		remove((void**)&arr,size,sizeof(abiturient),i);
	}
	list_elems(arr,size);
}

bool year_pred(abiturient& ab, cval val,bool minmax){
	return minmax ? ab.birthyear > val.ival : ab.birthyear < val.ival;
}
bool mark_pred(abiturient& ab, cval val,bool minmax){
	return minmax ? ab.avgmark > val.fval : ab.avgmark < val.fval;
}
bool ct_pred(abiturient& ab, cval val,bool minmax) {
	return minmax ? ab.ct_mark > val.ival : ab.ct_mark < val.ival;
}

