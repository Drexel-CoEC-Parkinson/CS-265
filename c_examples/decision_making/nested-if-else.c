#include <stdio.h>

int main(){
    int age = 11;

    if (age >= 18) {
        if (age >= 60)
            printf("Eligible to vote (Senior Citizen)\n");
        else
            printf("Eligible for vote\n");
    }
    else {
        printf("Not eligible to vote (Under 18)\n");
        if (age >= 13) 
                printf("teenager\n");
            else
                printf("not a teenager\n");
        }

    return 0;
}
