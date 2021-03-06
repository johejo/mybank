/*
   スレッドによる入金＋残高確認
 */

#include "defs.h"

int balance = 0; 			//残高

static pthread_mutex_t MyMutex=PTHREAD_MUTEX_INITIALIZER;

/*-- スレッドの処理 --*/
void *thread(void *arg) {
    int i;
    int tmp;
    int deposite;
    int id;
    int sync;

    ARGS *threadArgs = (ARGS *) arg;

    deposite = threadArgs->deposite;
    id = threadArgs->thread_id;
    sync = threadArgs->sync;

    for(i=0; i<MAX; i++){

        /*-- 入金処理 --*/
        if (sync) {
            pthread_mutex_lock(&MyMutex);
        }

        tmp = balance;
        tmp += deposite;

        printf("thread[%d] %d円追加 現在%d円\n", id , deposite, tmp);

        balance = tmp;
        if (sync) {
            pthread_mutex_unlock(&MyMutex);
        }

        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t tids[NUM]; 	// スレッド識別変数
    int opt = 0;
    int opts = 0;
    int deposites[NUM];


    /*-- オプション処理 --*/
    while ((opt = getopt(argc, argv, "sh")) != -1) {

        switch (opt) {
            case 's':
                opts = 1;
                break;
            case 'h':
                print_help();
                return 0;
            default:
                print_help();
                return 0;
        }
    }

    if (argc == 2 || argc >= 5) {
        print_help();
        exit(1);
    }


    int i;
    for (i = 0; i < NUM; i++) {
        ARGS *threadArgs;
        if((threadArgs = (ARGS *)malloc(sizeof(ARGS))) == NULL){
            perror("pthread_create() failed\n");
            exit(1);
        }

        deposites[i] = atoi(argv[argc - NUM + i]);

        threadArgs->thread_id = i;
        threadArgs->deposite = deposites[i];
        threadArgs->sync = opts;

        if (pthread_create(&tids[i], NULL, thread, (void *)threadArgs) < 0){
            perror("pthread_create error\n");
            exit(1);
        }
    }

    printf("残高:%d\n", balance);


    for (i = 0; i < NUM; i++) {
        if (pthread_join((pthread_t) tids[i], NULL) < 0) {
            perror("pthread_join error");
            exit(1);
        }
    }

    return 0;
}



//print help
void print_help(){
    char *command = "cat help.txt";
    if(system(command) == -1){
        perror("help error");
    }
    return;
}