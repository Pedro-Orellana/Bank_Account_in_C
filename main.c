#include <stdint.h>
#include <stdio.h>

// PROTOTYPES ///////////////////////////////////
int get_initial_option();
int check_input_is_valid(int input, uint8_t range_start, uint8_t range_end);
void clear_input_buffer();

//account functions
void create_new_account();
void account_login();
void account_logout();
void exit_program();

// account struct
struct account
{
    uint16_t acc_number;
    char owner[20];
    uint16_t pin_number;
    float balance;
};

int main()
{
    int initial;
    initial = get_initial_option();

    while(initial > 0 && initial <= 3) {
        switch (initial)
        {
        case 1:
            create_new_account();
            break;
        
        case 2:
            account_login();
            break;
        
        case 3:
            account_logout();
            break;
        }
    }

    exit_program();
    return 0;

}



//HELPER FUNCTIONS
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int check_input_is_valid(int input, uint8_t range_start, uint8_t range_end) {

    if(input == EOF || input == '\n'){
        printf("Please provide an answer and not an empty line\n");
        return -1;
    }

    if (input < '0' || input > '9') {
        printf("Please type a number\n");
        clear_input_buffer();
        return 0;
    }

    //from this line on, we know the input is an actual digit
    //get the real digit and not the ASCII code
    input -= '0';
    if(input < range_start || input > range_end) {
        printf("The number you typed is not in the options\n");
        clear_input_buffer();
        return 0;
    }
    return 1;
}

int get_initial_option() {
    int ret = 0;
    printf("This is the C bank app!\n");
    printf("Please choose an option from the following menu:\n");
    printf("1. Create a new account\n");
    printf("2. Log in to your account\n");
    printf("3. log out from your account\n");
    printf("4. Exit the program\n");

    while(!ret) {
        printf("Please type your option: ");
        int answer = getchar();
        int check = check_input_is_valid(answer, 1, 4);
        if(check > 0) {
            ret = (answer - '0');
        }
        
    }

    return ret;
}



//BANK FUNCTIONS
void create_new_account() {
    printf("create_new_account function\n");
}
void account_login() {
    printf("account_login function\n");
}
void account_logout() {
    printf("account_logout function\n");
}
void exit_program() {
    printf("Thank you for using the C bank app!\n");
    printf("Goodbye!\n");
}

