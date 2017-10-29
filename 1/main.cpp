/*
 * main.cpp
 * This is only a demo of BigDecimal test program. 
 * The one which grades your homework will be more complete and more strict.
 */

#include "bigDecimal.h"

#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

char str[1024];

int main(){
//    printf("hello world\n");
//    BigDecimal a("90000"),b("12345");
//    BigDecimal c(a+b);
//    c.print();

//    BigDecimal a("12.3450"),b("2.4690");
//    BigDecimal c(a*-2.4690);
//    cout<<"c:";
//    c.print();

    BigDecimal a("45.678"),b("11");
    BigDecimal c(a/b);
    cout<<"c:";
    c.print();

//    BigDecimal a("4556"),b("-4400");
//    BigDecimal c(a+b);
//    cout<<"c:";
//    c.print();

//    BigDecimal a("-10.234"),b("-10.234");
//    cout<<(a>b);
}
