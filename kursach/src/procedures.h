

#ifndef PROCEDURES_H_
#define PROCEDURES_H_
#include <iostream>
#include <fstream>
#include <string.h>
#include "util.h"
struct abiturient{
	char surname[20];
	int birthyear;
	float avgmark;
	int ct_mark;
	enum GenderInfo {male,female} gender;
} ;
union cval {int ival;float fval;};
typedef bool (*ab_predicate)(abiturient&,cval,bool);


void data_load(abiturient*&  arr, unsigned& size);
void append_entry(abiturient*&  arr, unsigned& size);
void list_elems(abiturient*&  arr, unsigned& size);
void data_dump(abiturient*&  arr, unsigned& size);
void edit_entry(abiturient*&  arr, unsigned& size);
void delete_entry(abiturient*&  arr, unsigned& size);
void delete_matching(abiturient*&  arr, unsigned& size);
void replace_entry(abiturient*&  arr, unsigned& size);
void delete_entries(abiturient*&  arr, unsigned& size);

bool year_pred(abiturient& ab, cval val,bool minmax);
bool mark_pred(abiturient& ab, cval val,bool minmax);
bool ct_pred(abiturient& ab, cval val,bool minmax);

#endif /* PROCEDURES_H_ */
