#include <iostream>
int main() {
    int intArrA[100] = {0};
    const int INT_A = 100;
//    for (int i = 0; i < INT_A; ++i) {
//        intArrA[i] = i;
//    }
    for (int j = 0; j < sizeof(intArrA) / sizeof(int); ++j) {
        printf("intArrA[%d]:%d\n", j, intArrA[j]);
    }
    return 0;
}