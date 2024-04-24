#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //Include to use boolean datatype.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"
struct P {
    __attribute__((unused)) int p_id;
    int burst_T;
    int arrival_T;
    int finish_T;
    int remain_T;
    __attribute__((unused)) int wait_T;
    bool queue; //A flag that is later used to identify whether a process is to be "queued" or not.
    int priority;
};

int firstArrive(struct P *, int);

int minPrior(struct P *, int);

void enqueue(struct P *, int, int);

double avgWaitTime(struct P *arr, int size) {
    int total = 0; //Get the total time of performance.
    for (int i = 0; i < size; i++) {
        total += arr[i].burst_T;
    }
    int begin = firstArrive(arr, size), end = begin + total, curr;
    for (int i = begin; i < end; i++) { //Sys_T = 0 -> Sys_T = the last second of performance.
        enqueue(arr, size, i); //A new process has entered at this second?
        curr = minPrior(arr, size); //Search for the minimum process index in terms of Remain_T.
        if (curr != -1) { //A process Found with minimum priority.
            arr[curr].remain_T -= 1; //Reduce its time.
            if (arr[curr].remain_T == 0) { //Check if it finished.
                arr[curr].queue = false; //Get it out of the queue.
                arr[curr].finish_T = i + 1; //Assign its finish time.
            }
        }
    }
    int sumTime = 0;
    for (int j = 0; j < size; j++) {
        arr[j].wait_T = arr[j].finish_T - arr[j].arrival_T - arr[j].burst_T;
        printf("process %d's wait_Time: %d\n",
               j + 1, arr[j].wait_T); //For debugging (Remove if not needed).
        sumTime += arr[j].wait_T; //Eq to find wait_T.
    }
    return (sumTime * 1.0) / size;
}

int firstArrive(struct P *arr, int size) { //Checks for the minimum time of arrival.
    int arrive = arr[0].arrival_T;
    for (int i = 0; i < size; i++) {
        if (arrive > arr[i].arrival_T) {
            arrive = arr[i].arrival_T;
        }
    }
    return arrive;
}

int minPrior(struct P *arr, int size) { //Checks for current minimum priority in the processes queue.
    int index = -1, prior = -1;
    for (int i = 0; i < size; i++) {
        //Process didn't finish and is queued:
        if (arr[i].remain_T > 0 && arr[i].queue) {
            //Check priority is unchanged or found higher priority:
            if (prior > arr[i].priority || prior == -1) {
                prior = arr[i].priority;
                index = i;
            }
        }
    }
    return index;
}

//Puts all processes having the same arrival time in the "queue".
void enqueue(struct P *arr, int size, int time) {
    for (int i = 0; i < size; i++) {
        if (arr[i].arrival_T == time) {
            arr[i].queue = true;
        }
    }
}

int main() {
    int size;
    printf("Enter the number of processes: \n");
    scanf("%d", &size); // NOLINT(*-err34-c)
    struct P *arr = (struct P *) malloc(size * sizeof(struct P));
    for (int i = 0; i < size; i++) {
        arr[i].p_id = i + 1;
        printf("Enter arrival time for process %d:\n", i + 1);
        scanf("%d", &arr[i].arrival_T); // NOLINT(*-err34-c)
        printf("Enter burst time for process %d:\n", i + 1);
        scanf("%d", &arr[i].burst_T); // NOLINT(*-err34-c)
        printf("Enter priority of process %d:\n", i + 1);
        scanf("%d", &arr[i].priority); // NOLINT(*-err34-c)
        arr[i].remain_T = arr[i].burst_T;
    }
    printf("Average Waiting time is: %f\n", avgWaitTime(arr, size));
    return 0;
}

#pragma clang diagnostic pop