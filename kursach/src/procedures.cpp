
#include "procedures.h"

using namespace std;
void data_load(abiturient*& arr, unsigned& size){
	cout << "Введите имя файла, из которого нужно произвести ввод данных:";
	char filename[30];
	cin >> filename;
	cout << "Загрузка..." << endl;
	FILE* datafile = fopen(filename,"r");
	if (!datafile) {
		cout << "Что-то пошло не так" << endl;
		return;
	}
	fseek(datafile,0,SEEK_END);
	unsigned filesize = ftell(datafile);
	rewind(datafile);
	char* data = new char[filesize+10];
	fread(data,1,filesize,datafile);
	fclose(datafile);
	data[filesize-1] = '\0';
	char** token_data = &data;
	char* token = strtok_r(data,"\n",token_data);
	char** entry_data = &token;
	// erase old data
	free(arr);
	size = 0;
	while(token) {
		abiturient a;
		char* entries[5];
		entries[0] = strtok_r(token,", ",entry_data);
		for(int i =1;i<5;i++) entries[i] = strtok_r(NULL,", ",entry_data);
		strcpy(a.surname,entries[0]);
		sscanf(entries[1],"%d",&a.birthyear);
		sscanf(entries[2],"%f",&a.avgmark);
		sscanf(entries[3],"%d",&a.ct_mark);
		if(*entries[4] - 48) {
			a.gender = abiturient::female;
		} else {
			a.gender = abiturient::male;
		}
		append((void**)&arr,size,sizeof(abiturient),&a);
		token = strtok_r(NULL,"\n",token_data);
	}
	list_elems(arr, size); // required
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
	FILE* datafile = fopen(filename,"w+");
	if (!datafile) {
		cout << "Что-то пошло не так" << endl;
		return;
	}
	for(unsigned i = 0; i < size; i++) {
		abiturient* ab = arr + i;
		fprintf(datafile,"%s, %d, %f, %d, %d\n",ab->surname,ab->birthyear,ab->avgmark,ab->ct_mark,ab->gender == abiturient::female);
	}
	fclose(datafile);
}
void edit_entry(abiturient*& arr, unsigned& size){
	unsigned to_edit;
	cout << "Введите ИД записи, которую нужно изменить:";
	cin >> to_edit;
	cout << endl;
}
void delete_entry(abiturient*& arr, unsigned& size){
	unsigned to_del;
	cout << "Введите ИД записи, которую нужно удалить:";
	cin >> to_del;
	cout << endl;
	if (to_del < size) {
		remove((void**)&arr,size,sizeof(abiturient),to_del);
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
void set_match_year(bool& isinpfloat, ab_predicate& pred){

}
void set_match_mark(bool& isinpfloat, ab_predicate& pred){

}
void set_match_ct(bool& isinpfloat, ab_predicate& pred){

}

