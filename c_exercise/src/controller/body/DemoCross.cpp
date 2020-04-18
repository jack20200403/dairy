//
// Created by tom on 04/12/2020.
//

#include <stdio.h>
#include "../header/DemoCross.h"
int DemoCross::input() {
    for (int i = 0; i < DemoCross::THREE; ++i) {
        for (int j = 0; j < DemoCross::THREE; ++j) {
            printf("intArrA[%d][%d] = ", i, j);
            scanf("%d",&this->intArrA[i][j]);
        }
    }
    return 0;
}

int DemoCross::output() {
    for (int i = 0; i < DemoCross::THREE; ++i) {
        for (int j = 0; j < DemoCross::THREE; ++j) {
            if (1 == i || 1 == j) {
                printf("%-6d", intArrA[i][j]);
            } else {
                printf("%-6c", ' ');
            }
        }
        printf("\n");
    }
    return 0;
}