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
    printf("hello world\n");
    BigDecimal a("-12.345"),b("9876.54321");
    a.print();
    b.print();
    a+b;
}
