#include <stdio.h>
#include <error_correction_algorithms.h>
#include "safe_input.h"

/*New functions come here*/

void error_correction_algorithms_demo(void)
{
    while (1)
    {
        int ECA_choice;
        /*Change the prompt and the range accordingly when new functions get added*/
        int ECA_status = safe_input_int(&ECA_choice, "\nAlgorithms yet to be added. Enter -1 to exit: ",0 , 0);

        if(ECA_status == INPUT_EXIT_SIGNAL)
        {
            printf("Exiting Error Correction Algorithm Demo....");
            return;
        }

        if(ECA_status == 0)
            continue;
        
        switch(ECA_choice)
        {

            /*Newly implemented functions will be called here*/

            default:
                printf("Wrong choice entered");
                break;
        }
    }
}