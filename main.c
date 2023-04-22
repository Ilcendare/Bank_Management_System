/* ======================================== */
/* Author       : Mahmoud Sayed
 * Date         : 9 April 2023
 * Description  : Bank management system
 *                program.
 * Email        : Thetr619@gmail.com
 *
 */
/* ======================================== */


#include "System_Methods.h"


int main() {
    System_Init();      // Initialize the list
    System_LoadData();  // Next, load the last saved data into it
    System_Menu();      // Then, run the program
    System_SaveData();  // Finally, when the program is closed by entering (q) the data will be saved.
    return 0;
}