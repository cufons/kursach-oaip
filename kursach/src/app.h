
#ifndef APP_H_
#define APP_H_
#include "procedures.h"

typedef struct {
    const char* label;
    void (*callback)(abiturient*&,unsigned&);
}menu_option;

void kursapp();
void do_menu(menu_option* opts,unsigned entries,const char* title,abiturient*& arr,unsigned& absize);
void exit_wrapper(abiturient*& arr,unsigned& size);


#endif /* APP_H_ */
