// INCLUDES ///////////////////////////////////////
#include <stdint.h>
#include <stdio.h>
#include <string.h>

//DEFINES //////////////////////////////
#define NUM_ACCOUNTS 10

// PROTOTYPES ///////////////////////////////////
int get_main_menu_option();
int get_user_menu_option();
int check_input_is_valid(int input, uint8_t range_start, uint8_t range_end);
int logged_account_index(const char *full_name, int pin_number);
void clear_input_buffer();


//account functions
void create_new_account(int *main_menu_option);
void account_login(int *main_menu_option);
void make_deposit(int account_index);
void make_withdrawal(int account_index);
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

// GLOBAL VARIABLES ////////////////////////////////////////
static int account_number_count = 5000;
static int account_index = 0;
static struct account accounts[NUM_ACCOUNTS];

int main()
{
    printf("WELCOME!\n");
    printf("This is the C bank app!\n");
    printf("\n");

    
    int main_menu_option;
    while(main_menu_option != 4) {
        main_menu_option = get_main_menu_option();

        switch (main_menu_option)
        {
        case 1:
            create_new_account(&main_menu_option);
            break;
        
        case 2:
            account_login(&main_menu_option);
            break;
        
        case 3:
            account_logout();
            break;
        
        case 4:
            exit_program();
            break;
        }
    }
    
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
    printf("\n");

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

int get_user_menu_option() {

    int user_menu_option = 0;
    printf("Please choose an option from the following menu:\n");
    printf("1. Make a deposit\n");
    printf("2. Make a withdrawal\n");
    printf("3. Logout fron your account\n");
    printf("Please type your option: ");

    //get the input from the user
    while(!user_menu_option) {
        int answer = getchar();
        if(check_input_is_valid(answer, 1, 3) != 1) {
            printf("Please type your option: ");
            continue;
        }
        user_menu_option = answer - '0';
    }

    return user_menu_option;
}



//BANK FUNCTIONS
void create_new_account(int *main_menu_option) {
    printf("\n\n");

    if(account_index >= NUM_ACCOUNTS) {
        printf("Database is full, cannot create a new account at this moment...\n");
        return;
    } 

    char full_name[20];
    int pin_number;
    float initial_amount;

    printf("Create a new account today!\n\n");
    printf("Please provide the following information: \n");
    printf("Full name (no longer than 20 characters): ");

    while(scanf("%19[^\n]", full_name) != 1) {
        clear_input_buffer();
        printf("Please provide a valid full name\n");
        printf("Full name (no longer than 20 characters): ");
    }

    clear_input_buffer();
    printf("\n");
    printf("Thank you, %s\n", full_name);
    printf("Now create a pin to access your account (exactly 4 digits):\n");
    printf("pin number: ");

    while(scanf("%d", &pin_number) != 1 || pin_number < 1000 || pin_number > 9999) {
        clear_input_buffer();
        printf("Please provide a valid pin number\n");
        printf("pin number: ");
    }
    printf("\n");
    printf("Now, do you want to open an account with an intial dollar amount? (if not, enter 0)\n");
    printf("Initial amount: ");
    while(scanf("%f", &initial_amount) != 1 || initial_amount < 0) {
        clear_input_buffer();
        printf("Please enter a valid number (or just type 0)\n");
        printf("Initial amount: ");
    }
    clear_input_buffer();

    //create new account
    struct account new_account = {
        .acc_number = account_number_count++,
        .pin_number = pin_number,
        .balance = initial_amount
    };

    //copy the name obtained from scanf into the array in the struct
    strcpy(new_account.owner, full_name);


    //add struct into the "database" (the struct account array)
    accounts[account_index++] = new_account;
    printf("\n");
    printf("Congratulations! you have successfully created your new account!\n");
    printf("These are your account details:\n");
    printf("Account number: %d\n", new_account.acc_number);
    printf("Account owner: %s\n", new_account.owner);
    printf("pin number: %d\n", new_account.pin_number);
    printf("current balance: $%.2f\n", new_account.balance);
    printf("\n");
    printf("Going back to main menu...\n");
    printf("\n");

}


void account_login(int *main_menu_option) {
    printf("\n");
    printf("Access your account today!\n");
    printf("\n");
    if(account_index == 0) {
        printf("There are no registered accounts. Please create an account first.\n");
        printf("\n");
        return;
    } 

    //get information for account here
    int ret;
    char full_name[20];
    int pin_number;


    printf("Please provide your full name (or type \"CANCEL\" to go back): ");
    while(scanf("%19[^\n]", full_name) != 1) {
        clear_input_buffer();
        printf("Please provide a valid name\n");
        printf("Please provide your full name (or type \"CANCEL\" to go back): ");
    }

    if(strcmp(full_name, "CANCEL") == 0) {
        clear_input_buffer();
        printf("Going back to main menu...\n");
        printf("\n");
        return;
        }
    
    printf("\n");
    printf("Please enter the pin number of your account (or type \"-1\" to go back): ");


    while(true) {
        ret = scanf("%d", &pin_number);
        clear_input_buffer();
        if(ret != 1) {
            printf("Please provide a valid pin number\n");
            printf("Please enter the pin number of your account (or type \"-1\" to go back): ");
            continue;
        }
        if(pin_number == -1) {
             printf("\n");
            printf("Going back to main menu...\n");
            printf("\n");
            return;
        }

        if(pin_number < 1000 || pin_number > 9999) {
            printf("Pin number does not comply with standards (it needs to be a 4-digit number)\n");
            printf("Please enter the pin number of your account (or type \"-1\" to go back): ");
            continue;
        }
        printf("\n");
        break;
    }

    int index = logged_account_index(full_name, pin_number);

    if(index == -1) {
        printf("No user exists with that combination of name/pin number\n");
        printf("\n");
        printf("Going back to main menu...\n");
        printf("\n");
        return;
    }

 
    //show the menu of what a logged in user can do
    printf("Successfully logged in!\n");
    printf("Welcome back, %s\n", full_name);
    printf("\n");

    int user_menu_option = 0;
    while(user_menu_option != 3) {

        user_menu_option = get_user_menu_option();

        switch (user_menu_option)
        {
        case 1:
            make_deposit(index);
            break;
        
        case 2:
            make_withdrawal(index);
            break;

        case 3:
            printf("You have successfully logged out of your account!\n");
            break;
        }
    }

    printf("Going back to main menu...\n");
    return;
    
}


int logged_account_index(const char *full_name, int pin_number) {
    struct account current;
    for(int i = 0; i < account_index; i ++) {
        current = accounts[i];
        int name_match = strcmp(full_name, current.owner);
        if(name_match != 0){
            continue;
        } else {
            if(pin_number == current.pin_number) {
                return i;
            }
        }
    }
    return -1;
}

void make_deposit(int account_index) {
    float amount = 0;
    printf("Make a deposit to your account!\n");
    printf("\n");
    printf("Type the amount you want to deposit: ");
    while(scanf("%f", &amount) != 1 || amount < 0) {
        clear_input_buffer();
        printf("Please type a amount (it has to be a number greater than 0)\n");
        printf("Type the amount you want to deposit: ");
    }
    clear_input_buffer();

    //make the deposit
    struct account *user_account = &accounts[account_index];
    user_account->balance += amount;

    //show the user the new amount
    printf("Deposit is successful!\n");
    printf("Your new balance: %.2f\n", user_account->balance);
    printf("\n");
}

void make_withdrawal(int account_index) {
    printf("Make a withdrawal from your account!\n");
    printf("\n");
    printf("Enter the amount you want to withdraw: ");
}


void account_logout() {
    printf("\n");
    printf("You have successfully logged out of your account!\n");
    printf("\n");
}
void exit_program() {
    printf("Thank you for using the C bank app!\n");
    printf("Goodbye!\n");
}

