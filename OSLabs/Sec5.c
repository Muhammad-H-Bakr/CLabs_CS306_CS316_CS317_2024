#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
    int filedes[2];
    int filedes2[2];
    char ans[10];
    pipe(filedes);
    pipe(filedes2);
    int p_id = fork();
    if (p_id == 0) {
        int p2 = fork();
        char x[] = "lab", y[10];
        if (p2 == 0) {
            close(filedes2[0]);
            write(filedes2[1], x, sizeof(x));
            printf("This is child2 writing the string: %s\n", x);
        } else {
            close(filedes2[1]);
            read(filedes2[0], y, sizeof(y));
            printf("This is child1 reading the string: %s\n", y);
            strcat(y, " CS 306");
            close(filedes[0]);
            write(filedes[1], y, sizeof(y));
            printf("This is child1 writing the string: %s\n", y);
        }
    } else {
        close(filedes[1]);
        read(filedes[0], ans, sizeof(ans));
        printf("This is the parent reading the string: %s\n", ans);
    }
    return 0;
}