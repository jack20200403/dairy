//#include <iostream>
//
//int main() {
//    int intArrA[10];
//    const int ARR_SIZE = 10;
//    int intTemp;
//    for (int i = 0; i < ARR_SIZE; ++i) {
//        intArrA[i] = rand();
//    }
//    for (int k = 0; k < ARR_SIZE; ++k) {
//        for (int l = 0; l < ARR_SIZE - k; ++l) {
//            if (intArrA[l] > intArrA[l + 1]) {
//                intTemp = intArrA[l];
//                intArrA[l] = intArrA[l + 1];
//                intArrA[l + 1] = intTemp;
//            }
//        }
//    }
//    for (int j = 0; j < ARR_SIZE; ++j) {
//        printf("%d\n", intArrA[j]);
//    }
//    return 0;
//}