/* ======================================== */
/* Author       : Mahmoud Sayed
 * Date         : 9 April 2023
 * Description  : Declaring the functions
 *                prototype used for the
 *                linked list data structure.
 * Email        : Thetr619@gmail.com
 */
/* ======================================== */


#ifndef BANK_MANAGEMENT_SYSTEM_LINKED_LIST_H
#define BANK_MANAGEMENT_SYSTEM_LINKED_LIST_H


/* =========== Defining the structure of lists and nodes =========== */
typedef struct ListNode {
    DATA *dataPtr;
    struct ListNode *NextNode;
} lnode_t;

typedef struct List {
    lnode_t *first;
    lnode_t *last;
}list_t;


/* =========== Function prototypes =========== */
void Linked_List_Init(list_t *List);
void Linked_List_AddNode(list_t *List, DATA *NewData);
int Linked_List_DeleteNode(list_t *List, COMP_VAR);
void* Linked_List_FindNode(list_t *List, COMP_VAR);
void Linked_List_ListNodes(list_t *List, void (*DisplayFormatFunction) (lnode_t*));


#endif //BANK_MANAGEMENT_SYSTEM_LINKED_LIST_H
