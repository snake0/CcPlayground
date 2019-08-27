//
// Created by SNAKE on 2019-08-27.
//

#include "include_for_c.h"

int main() {
    pid_t pid;
    if ((pid = fork()) == 0) {
        pause();
        printf("control never reach here\n");
        exit(0);
    }
    kill(pid, SIGKILL);
    exit(0);
}