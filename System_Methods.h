/* ======================================== */
/* Author       : Mahmoud Sayed
 * Date         : 9 April 2023
 * Description  : Declaring the functions
 *                prototype used for the bank
 *                management system program
 * Email        : Thetr619@gmail.com
 */
/* ======================================== */


#ifndef BANK_MANAGEMENT_SYSTEM_SYSTEM_METHODS_H
#define BANK_MANAGEMENT_SYSTEM_SYSTEM_METHODS_H


/* =========== Important declarations and macro definition (Don't change them) =========== */
#define WITHDRAW                0
#define DEPOSIT                 1


/* =========== The following macros can be configured =========== */
#define SYS_PASSWORD            "bank12ftj"     // You can type your desired password here
#define PASSWORD_MAX_LENGTH     50              // The password maximum length


/* =========== Function prototypes =========== */
void System_Init(void);                         // Initialize the list
void System_Menu(void);                         // To show the menu of the program
int System_CreateAccount(void);
void System_DeleteAccount(void);
void System_ShowAccountInfo(void);
void System_EditAccountInfo(void);
void System_Transact(_Bool);                    // To withdraw/deposit money
void System_SaveData(void);                     // To save the current list's data in a file
void System_LoadData(void);                     // To load the last saved data into a list


#endif //BANK_MANAGEMENT_SYSTEM_SYSTEM_METHODS_H
