//
// Created by heijo on 17/05/31.
//

#ifndef MYBANK_DEFS_H
#define MYBANK_DEFS_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX 5 				//入金処理を繰り返す回数
#define NUM 2
void *thread(void *arg); 	//スレッドの処理
void print_help();

typedef struct threadArgs
{
    int thread_id;
    int deposite;
    int sync;
}ARGS;

#endif //MYBANK_DEFS_H
