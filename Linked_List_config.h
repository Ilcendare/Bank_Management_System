/* ======================================== */
/* Author       : Mahmoud Sayed
 * Date         : 9 April 2023
 * Description  : This file contain configuration
 *                used in the functions of
 *                Linked_List.c
 * Email        : Thetr619@gmail.com
 */
/* ======================================== */


#ifndef BANK_MANAGEMENT_SYSTEM_LINKED_LIST_CONFIG_H
#define BANK_MANAGEMENT_SYSTEM_LINKED_LIST_CONFIG_H


/* =========== Define the data structure for each node =========== */
typedef struct Account {
    char FirstName[21];
    char LastName[21];
    char DateOfBirth[11];        // It should be in the form of -> dd/mm/yyyy
    char CitizenshipNumber[15];  // It should contain only 14 digits
    char Address[31];            // Long descriptive address
    char PhoneNumber[12];        // The phone number should contain only 11 numbers
    double MoneyAmount;    // To hold the amount of money the account has
} account_t;


/* =========== Configure important macros for the Linked List's functions =========== */
#define DATA        account_t                       // The list node's data it holds
#define COMP_VAR    char ComparedVariable[]         // Used as the key to find/delete a specific node
#define COMP_DATA   CitizenshipNumber               /* The data to be compared with COMP_VAR in each node (it is
                                                       to be selected from the above structure). */


#endif //BANK_MANAGEMENT_SYSTEM_LINKED_LIST_CONFIG_H
