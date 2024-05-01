#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct Data {
    int a;
    char *msg;

};

void *thread_function(__attribute__((unused)) void *arg) {
    struct Data *data = (struct Data *) (malloc(sizeof(struct Data)));
    (*data).a = 123;
    (*data).msg = "Hello World";
    return data;
}

/* Mutex to be later used */
int main() {
    pthread_t my_thread;
    void *data = NULL;
    pthread_create(&my_thread, NULL, thread_function, NULL);
    pthread_join(my_thread, &data);
    struct Data *data1 = (struct Data *) data;
    printf("Message number: %d\nMessage content: %s\n", data1->a,
           data1->msg);
    return 0;
}