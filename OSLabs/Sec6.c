#include <stdio.h>
#include <stdlib.h>

struct P {
    __attribute__((unused)) int p_id;
    int burst_T;
    __attribute__((unused)) int arrival_T;
};

double avgTime(struct P *ptr, int size) {
    int arr[size];
    double avg = 0;
    int elapsed;
    arr[0] = 0;
    elapsed = ptr[0].burst_T;
    for (int i = 1; i < size; i++) {
        arr[i] = elapsed;
        elapsed += ptr[i].burst_T;
    }
    for (int i = 0; i < size; i++) {
        avg += arr[i];
    }
    return avg / size;
}

int main() {
    int size;
    printf("Enter the number of processes: \n");
    scanf("%d", &size); // NOLINT(*-err34-c)
    struct P *arr = (struct P *) malloc(size * sizeof(struct P));
    for (int i = 0; i < size; i++) {
        arr[i].p_id = i;
        arr[i].arrival_T = 0;
        printf("Enter burst time for process %d:\n", i);
        scanf("%d", &arr[i].burst_T); // NOLINT(*-err34-c)
    }
    printf("The average time: %f\n", avgTime(arr, size));
    return 0;
}