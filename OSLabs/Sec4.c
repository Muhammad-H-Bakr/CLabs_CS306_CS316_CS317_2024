#include <unistd.h>

int main() {
    int parent = getpid();
    int temp;
    fork();
    fork();
    if (getpid() == parent) {
        temp = fork();
        if (temp == 0) {
            fork();
        }
    }
    sleep(45);
    return 0;
}