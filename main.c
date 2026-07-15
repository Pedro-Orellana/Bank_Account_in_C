#include <stdio.h>

// prototypes


//account struct
struct account {
    char owner[20];
    float balance;
};

int main() {
    
    int ret = 0;
    struct account account1 = {.balance = 0, .owner = ""};
    printf("This is the Electronic bank app!\n");
    
    while(!ret) {

        printf("Please provide your full name: \n");

        ret = scanf("%19[^\n]", account1.owner);
        if(!ret) {
            printf("You did not provide your full name...\n");
            getchar();
        }

        
    }

    
    printf("Thank you, %s\n", account1.owner);
  
    
   
    return 0;
}