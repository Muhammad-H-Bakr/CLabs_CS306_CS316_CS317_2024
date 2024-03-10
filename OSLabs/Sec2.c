#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat"
#pragma ide diagnostic ignored "cert-err34-c"
#include <stdio.h>
#include <stdlib.h>

struct person {
    int age;
    double salary;
    char name[50];
};

int main() {
    int num;
    printf("Enter number of people:");
    scanf("%d", &num);
    struct person *people = (struct person *) (malloc(num * sizeof(struct person)));
    for (int i = 0; i < num; i++) {
        printf("Name:");
        scanf("%s", &people[i].name);
        printf("Age:");
        scanf("%d",&people[i].age);
        printf("Salary:");
        scanf("%f", &people[i].salary);
    }
    for (int i = 0; i < num; i++) {
        printf("Person: %s, Age: %d, Salary: %f\n",
               people[i].name, people[i].age, people[i].salary);
    }
    free(people);
    return 0;
}

#pragma clang diagnostic pop