#include <iostream>

int intPlusTwoInt(int *intA, int *intB);

int main() {
    int
            intA,
            intB,
            *pointerIntA = &intA,
            *pointerIntB = &intB;

    printf("the result of intA plus intB:\n");
    printf("please input intA:\n");
    scanf("%d", &intA);
    printf("please input intB:\n");
    scanf("%d", &intB);
    printf("intA:%d\n", intA);
    printf("intB:%d\n", intB);
    printf("pointerIntA:%d\n",pointerIntA);
    printf("pointerIntB:%d\n",pointerIntB);
    printf("intAintB:%d\n", intPlusTwoInt(pointerIntA, pointerIntB));

    return 0;
}

int intPlusTwoInt(int *intA, int *intB) {
    return *intA + *intB;
}

