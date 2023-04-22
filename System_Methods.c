/* ======================================== */
/* Author       : Mahmoud Sayed
 * Date         : 9 April 2023
 * Description  : Defining the functions (methods)
 *                of System Methods header file.
 * Email        : Thetr619@gmail.com
 */
/* ======================================== */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linked_List_config.h"
#include "Linked_List.h"
#include "System_Methods.h"


/* ========== Important declarations ========== */
list_t *System_List = NULL;


/* ========== Functions declarations ========== */
void AccountDisplayFormat(lnode_t* node) {
    printf("\nName: %s %s\nBirth Date: %s\nCitizenship number: %s\nAddress: %s\nPhone number: %s\nAmount of money:%.2lf\n",
           node->dataPtr->FirstName, node->dataPtr->LastName, node->dataPtr->DateOfBirth, node->dataPtr->CitizenshipNumber,
           node->dataPtr->Address, node->dataPtr->PhoneNumber, node->dataPtr->MoneyAmount);
}


void System_SaveData(void) {
    FILE *System_File;
    lnode_t *ptr = System_List->first;
    int counter = 0;
    System_File = fopen("Bank_Management_System.txt","w");
    while(ptr != NULL) {
        fseek(System_File,(long)(counter * sizeof(DATA)),SEEK_SET);
        fwrite(ptr->dataPtr, sizeof(DATA),1,System_File);
        counter++;
        ptr = ptr->NextNode;
    }
    fclose(System_File);
}


void System_LoadData(void) {
    FILE *System_File;
    System_File = fopen("Bank_Management_System.txt","rb");
    if(System_File != NULL) {
        DATA *DataLoaded;
        while(!feof(System_File)) {
            DataLoaded = (DATA *) malloc(sizeof(DATA));
            int res = (int) fread(DataLoaded,sizeof(DATA),1,System_File);
            if(res != 0) {
                Linked_List_AddNode(System_List,DataLoaded);
            }
        }
        fclose(System_File);
    }
}


void System_Init(void) {
    System_List = (list_t*) malloc(sizeof(list_t));
    Linked_List_Init(System_List);
}


void System_Menu(void) {
    char select;
    _Bool QUIT = 0;
    int tries = 3;
    char password[PASSWORD_MAX_LENGTH];
    /* Password Lock System */
    printf("Please enter the password: ");
    while(tries--) {
        scanf("%s", password);
        if (strcmp(password, SYS_PASSWORD) != 0) {
            if (tries == 0) exit(0);
            printf("Wrong password, you have %d time/s left.\n>", tries);
        }
        else break;
    }

    printf("\n\n===============================================================\n");
    printf("###########          Bank Management System          ##########\n");
    printf("===============================================================\n");
    printf("#########   Please Choose from the following options   ########\n");
    printf("===============================================================\n\n");
    printf("\t(+)\ta) Add account\t\t\t(+)\n");
    printf("\t(+)\td) Delete account\t\t(+)\n");
    printf("\t(+)\tl) List account's information\t(+)\n");
    printf("\t(+)\te) Edit account's information\t(+)\n");
    printf("\t(+)\tw) Withdraw from account\t(+)\n");
    printf("\t(+)\tp) Deposit to account\t\t(+)\n");
    printf("\t(+)\tq) Quit program\t\t\t(+)\n");

    do {
        char Continue;
        printf("\nType Here: ");
        scanf("%c", &select);
        switch (select) {
            case 'a':
                do {
                    int result = System_CreateAccount();
                    if(result) printf("The Account has added successfully.\n");
                    else printf("The process has aborted.\n");
                    printf("Do you want to add another account? (y - yes, n - no)\n");
                    do {
                        printf(">");
                        fflush(stdin);
                        scanf("%c", &Continue);
                        if ((Continue != 'y') && (Continue != 'n')) {
                            printf("Please enter a valid answer.\n");
                        }
                    } while((Continue != 'y') && (Continue != 'n'));
                } while(Continue == 'y');
                break;
            case 'd':
                do {
                    System_DeleteAccount();
                    printf("Do you want to delete another account? (y - yes, n - no)\n");
                    do {
                        printf(">");
                        fflush(stdin);
                        scanf("%c", &Continue);
                        if ((Continue != 'y') && (Continue != 'n')) {
                            printf("Please enter a valid answer.\n");
                        }
                    } while((Continue != 'y') && (Continue != 'n'));
                } while(Continue == 'y');
                break;
            case 'l':
                do {
                    System_ShowAccountInfo();
                    printf("Do you want to list another account? (y - yes, n - no)\n");
                    do {
                        printf(">");
                        fflush(stdin);
                        scanf("%c", &Continue);
                        if ((Continue != 'y') && (Continue != 'n')) {
                            printf("Please enter a valid answer.\n");
                        }
                    } while((Continue != 'y') && (Continue != 'n'));
                } while(Continue == 'y');
                break;
            case 'w':
                System_Transact(WITHDRAW);
                break;
            case 'p':
                System_Transact(DEPOSIT);
                break;
            case 'e':
                do {
                    System_EditAccountInfo();
                    printf("Do you want to edit another account? (y - yes, n - no)\n");
                    do {
                        printf(">");
                        fflush(stdin);
                        scanf("%c", &Continue);
                        if ((Continue != 'y') && (Continue != 'n')) {
                            printf("Please enter a valid answer.\n");
                        }
                    } while((Continue != 'y') && (Continue != 'n'));
                } while(Continue == 'y');
                break;
            case 'q':
                QUIT = 1;
                break;
            default:
                printf("Please enter one of the shown settings (a, d, l, e, p, w, or q lowercase)\n");
        }
        fflush(stdin);
    } while(!QUIT);
}


int System_CreateAccount(void) {
    DATA *NewAccount;
    NewAccount = (DATA *) malloc(sizeof(DATA));
    printf("Please enter the first and last name:");
    scanf("%20s %20s",NewAccount->FirstName,NewAccount->LastName);
    fflush(stdin);
    printf("Please enter the birth date (dd/mm/yyyy):");
    fflush(stdin);
    scanf("%s",NewAccount->DateOfBirth);
    printf("Please enter the citizenship number:");
    fflush(stdin);
    /* This step is done to check if the citizenship number entered is already registered in the system or not */
    char CS[15];
    int Abort = 0;
    lnode_t *ptr = System_List->first;
    scanf("%s",CS);
    while(ptr != NULL) {
        if((strcmp(ptr->dataPtr->CitizenshipNumber,CS)) == 0) {
            printf("You cannot enter citizenship numbers that belong to other accounts.\n");
            Abort = 1;
            break;
        }
        ptr = ptr->NextNode;
    }
    if(Abort == 1) {
        free(NewAccount);
        return 0;
    }
    /* End of checking step */
    strcpy(NewAccount->CitizenshipNumber,CS);
    printf("Please enter the address:");
    fflush(stdin);
    scanf("%s",NewAccount->Address);
    printf("Please enter the phone number: ");
    fflush(stdin);
    scanf("%s",NewAccount->PhoneNumber);
    NewAccount->MoneyAmount = 0.0;

    Linked_List_AddNode(System_List,NewAccount);
    return 1;
}


void System_DeleteAccount(void) {
    char citizenshipNum[15];
    int result;
    printf("Please enter the citizenship number of the account:");
    fflush(stdin);
    scanf("%s",citizenshipNum);

    result = Linked_List_DeleteNode(System_List,citizenshipNum);
    if(result)
        printf("The account has deleted successfully.\n");
    else
        printf("The account does not included in the system.\n");
}


void System_ShowAccountInfo(void) {
    char citizenshipNum[15];
    lnode_t *Account;
    printf("Please enter the citizenship number of the account:");
    fflush(stdin);
    scanf("%14s",citizenshipNum);

    Account = Linked_List_FindNode(System_List,citizenshipNum);
    if (Account != NULL) AccountDisplayFormat(Account);
    else printf("The account does not included in the system.\n");
}


void System_EditAccountInfo(void) {
    char citizenshipNum[15];
    lnode_t *Account;
    printf("Please enter the citizenship number of the account:");
    fflush(stdin);
    scanf("%14s",citizenshipNum);

    Account = Linked_List_FindNode(System_List,citizenshipNum);
    if (Account != NULL) {
        char firstName[21] = "0";
        char lastName[21] = "0";
        char dateOfBirth[11] = "0";
        char address[31] = "0";
        char phoneNumber[12] = "0";

        printf("Enter the new account info you want to edit in the following order: first name, last name, birth date,"
               " address, and phone number.\nIf one of the mentioned you don't want to alter,"
               "enter 0 instead.");
        scanf("%20s %20s %10s %30s %11s", firstName, lastName, dateOfBirth, address, phoneNumber);
        if(strcmp(firstName, "0") != 0) {
            strcpy(Account->dataPtr->FirstName , firstName);
        }
        if(strcmp(lastName, "0") != 0) {
            strcpy(Account->dataPtr->LastName , lastName);
        }
        if(strcmp(address, "0") != 0) {
            strcpy(Account->dataPtr->Address , address);
        }
        if(strcmp(dateOfBirth, "0") != 0) {
            strcpy(Account->dataPtr->DateOfBirth , dateOfBirth);
        }
        if(strcmp(phoneNumber, "0") != 0) {
            strcpy(Account->dataPtr->PhoneNumber , phoneNumber);
        }
    }
    else printf("The account does not included in the system.\n");
}


void System_Transact(_Bool MACRO) {
    char citizenshipNum[15];
    char proceed;
    double amount = 0;
    lnode_t *Account;
    printf("Please enter the citizenship number of the account:");
    fflush(stdin);
    scanf("%14s",citizenshipNum);
    Account = Linked_List_FindNode(System_List,citizenshipNum);
    if(Account != NULL) {
        if (MACRO == WITHDRAW) {
            repeat_W:       // This label is used to repeat the process if the user entered a zero/negative value.
            printf("\nPlease enter the amount of money you want to withdraw (make sure it is positive): ");
            fflush(stdin);
            scanf("%lf", &amount);
            if (Account->dataPtr->MoneyAmount == 0) {
                printf("The amount of money of this account is empty (0). Make sure you deposit before attempting "
                       "to withdraw.");
            }
            else {
                if (amount > 0) {
                    if (amount <= Account->dataPtr->MoneyAmount) {
                        Account->dataPtr->MoneyAmount -= amount;
                        printf("The amount of money (%.2lf) has withdrawn successfully.\n", amount);
                    } else if (amount > (Account->dataPtr->MoneyAmount)) {
                        printf("You've entered an amount of (%.2lf) which is greater than the account's money amount"
                               " (%.2lf). All account's money will be withdrawn. Do you want to proceed? (y - yes, n - no)\n",
                               amount, Account->dataPtr->MoneyAmount);
                        do {
                            printf(">");
                            fflush(stdin);
                            scanf("%c", &proceed);
                            if ((proceed != 'y') && (proceed != 'n')) {
                                printf("Please enter a valid answer. (y - yes, n - no)\n");
                            }
                        } while ((proceed != 'y') && (proceed != 'n'));
                        if (proceed == 'y') {
                            amount = Account->dataPtr->MoneyAmount;
                            Account->dataPtr->MoneyAmount = 0;
                            printf("The amount of money (%.2lf) has withdrawn successfully.\n", amount);
                        }
                    }
                } else if (amount <= 0) {
                    printf("Zero/Negative amount of money is not allowed.\n");
                    goto repeat_W;
                }
            }
        } else if (MACRO == DEPOSIT) {
            repeat_D:       // This label is used to repeat the process if the user entered a zero/negative value.
            printf("\nPlease enter the amount of money you want to deposit (make sure it is positive): ");
            fflush(stdin);
            scanf("%lf", &amount);
            if(amount > 0) {
                Account->dataPtr->MoneyAmount += amount;
                printf("The amount of money (%.2lf) has deposited successfully.\n",amount);
            } else {
                printf("Zero/Negative amount of money is not allowed.\n");
                goto repeat_D;
            }
        }
    } else printf("The account does not included in the system.\n");
}
