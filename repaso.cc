#include <iostream>
using namespace std;

int main() {
    int a;
    int b = 0;
    int c[4] = {25, 26, 27, 28};

    a = b;
    int* apuntador = &a;
    
    *apuntador = 7;        
    apuntador = &b;        
    *apuntador = 13;       

    apuntador = &c[3];     
    *apuntador = 20;     

    return 0;
}
