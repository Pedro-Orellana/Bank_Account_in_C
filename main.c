// INCLUDES ///////////////////////////////////////
#include <stdint.h>
#include <stdio.h>

//DEFINES //////////////////////////////
#define NUM_ACCOUNTS 50


// PROTOTYPES ///////////////////////////////////
int get_main_menu_option();
int check_input_is_valid(int input, uint8_t range_start, uint8_t range_end);
void clear_input_buffer();

//account functions
void create_new_account(int *main_menu);
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
    printf("WELCOME!\n");
    printf("This is the C bank app!\n");
    printf("\n\n");
    int main_menu;
    main_menu = get_main_menu_option();



    while(main_menu > 0 && main_menu <= 3) {
        switch (main_menu)
        {
        case 1:
            create_new_account(&main_menu);
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
    clear_input_buffer();
    return 1;
}

int get_main_menu_option() {
    int ret = 0;
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
void create_new_account(int *main_menu) {
    char full_name[20];
    int pin_number;
    printf("Create a new account today!\n\n");
    printf("Please provide the following information: \n");
    printf("Full name (no longer than 20 characters): ");
    while(scanf("%19[^\n]", full_name) != 1) {
        clear_input_buffer();
        printf("Please provide a valid full name\n");
        printf("Full name (no longer than 20 characters): ");
    }
    clear_input_buffer();
    printf("Thank you, %s\n", full_name);
    printf("Now create a pin to access your account (exactly 4 digits):\n");
    printf("pin number: ");

    while(scanf("%d", &pin_number) != 1 || pin_number < 1000 || pin_number > 9999) {
        clear_input_buffer();
        printf("Please provide a valid pin number\n");
        printf("pin number: ");
    }

    clear_input_buffer();
    printf("Going back to main menu...\n");
    printf("\n\n");
    *main_menu = get_main_menu_option();
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

