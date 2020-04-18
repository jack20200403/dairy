//
// Created by tom on 04/11/2020.
//

#include <stdio.h>
#include "../header/demoMultithread.h"

void demoMultithread::say() {
    for (int i = 0; i < 50; ++i) {
        printf("%d\n", i);
    }
}

void demoMultithread::create() {
    this->say();
}