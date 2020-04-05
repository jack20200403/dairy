//
// Created by tom on 4/5/2020.
//

#include <cstdio>

int main()
{

    int intA = 100;
    int *pointerIntA = &intA;
    printf("input a varible:\n");
    scanf("%d", &intA);
    printf("pointIntA:%d\n",*pointerIntA);
    printf("intA:%d\n", intA);
    return 0;
}
