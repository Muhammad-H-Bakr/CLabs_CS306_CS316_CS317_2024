#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct P {
    __attribute__((unused)) int p_id;
    int burst_T;
    int arrival_T;
    int finish_T;
    int remain_T;
    __attribute__((unused)) int wait_T;
    bool queue; //A flag that is later used to identify whether a process has entered the CPU or not.
};

int firstArrive(struct P *, int);

int minTime(struct P *, int);

void enqueue(struct P *, int, int);

double avgWaitTime(struct P *arr, int size, int total) {
    int begin = firstArrive(arr, size), end = begin + total, curr;
    for (int i = begin; i < end; i++) { //Sys_T = 0 -> Sys_T = the last second of performance.
        enqueue(arr, size, i); //A new process has entered at this second?
        curr = minTime(arr, size); //Search for the minimum process index in terms of Remain_T.
        if (curr != -1) { //A process Found.
            arr[curr].remain_T -= 1; //Reduce its time.
            if (arr[curr].remain_T <= 0) { //Check if it finished.
                arr[curr].queue = false; //Get it out of the queue.
                arr[curr].finish_T = i + 1; //Assign its finish time.
            }
        }
    }
    int sumTime = 0;
    for (int j = 0; j < size; j++) {
        sumTime += arr[j].finish_T - arr[j].arrival_T - arr[j].burst_T; //Eq to find wait_T.
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

int minTime(struct P *arr, int size) { //Checks for current minimum in the processes queue.
    int index = -1, time = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i].remain_T != 0 && arr[i].queue) { // search for a valid RMTime.
            time = arr[i].remain_T;
            index = i;
            break;
        }
    }
    for (int i = 0; i < size; i++) {
        /*Does this process have undone work? is that work less than current? and is it
         even in the queue or not*/
        if (arr[i].remain_T != 0 && time > arr[i].remain_T && arr[i].queue) {
            time = arr[i].remain_T;
            index = i;
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
    int total_Time = 0;
    for (int i = 0; i < size; i++) {
        arr[i].p_id = i;
        printf("Enter arrival time for process %d:\n", i);
        scanf("%d", &arr[i].arrival_T); // NOLINT(*-err34-c)
        printf("Enter burst time for process %d:\n", i);
        scanf("%d", &arr[i].burst_T); // NOLINT(*-err34-c)
        total_Time += arr[i].burst_T;
        arr[i].remain_T = arr[i].burst_T;
    }
    printf("Average Waiting time is: %f\n", avgWaitTime(arr, size, total_Time));
    return 0;
}
