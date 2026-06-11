#include "advanced_searching.h"
#include "history_logger.h"
#include "safe_input.h"
#include <stdio.h>
#include <time.h>

/*
 * Interpolation Search
 *
 * Works on sorted arrays.
 *
 * Instead of always checking the middle element like Binary Search,
 * it estimates the likely position of the target based on its value.
 *
 * Best Case: O(1)
 * Average Case: O(log log n)
 * Worst Case: O(n)
 */

int interpolation_search(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high &&
           target >= arr[low] &&
           target <= arr[high])
    {
        if (arr[low] == arr[high])
        {
            if (arr[low] == target)
                return low;
            return -1;
        }

        int pos = low +
                  ((double)(high - low) /
                   (arr[high] - arr[low])) *
                      (target - arr[low]);

        if (arr[pos] == target)
            return pos;

        if (arr[pos] < target)
            low = pos + 1;
        else
            high = pos - 1;
    }

    return -1;
}

void interpolation_search_demo(void)
{
    int length_of_array;

    while (1)
    {
        printf("\n\nInterpolation Search Demo");

        int length_status =
            safe_input_int(&length_of_array,
                           "\nEnter number of elements "
                           "(between 1 and 100), enter '-1' to exit:- ",
                           1,
                           100);

        if (length_status == 0)
            continue;

        if (length_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Interpolation Search Demo....\n");
            return;
        }

        int arr[length_of_array];

        printf("\nEnter elements in SORTED ASCENDING order:\n");

        for (int i = 0; i < length_of_array; i++)
        {
        retry:

            printf("\nEnter element %d, "
                   "(between 1 and 1000), enter '-1' to exit:- ",
                   i);

            int element_status =
                safe_input_int(&arr[i],
                               NULL,
                               1,
                               1000);

            if (element_status == INPUT_EXIT_SIGNAL)
            {
                printf("\nExiting Interpolation Search Demo.....\n");
                return;
            }

            if (element_status == 0)
                goto retry;

            if (i > 0 && arr[i] < arr[i - 1])
            {
                printf("\nArray must be sorted in ascending order.\n");
                goto retry;
            }
        }

        int target;

    target_retry:

        printf("\nEnter target element to search "
               "(between 1 and 1000), enter '-1' to exit:- ");

        int target_status =
            safe_input_int(&target,
                           NULL,
                           1,
                           1000);

        if (target_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Interpolation Search Demo.....\n");
            return;
        }

        if (target_status == 0)
            goto target_retry;

        clock_t start_t = clock();

        int result =
            interpolation_search(arr,
                                 length_of_array,
                                 target);

        clock_t end_t = clock();

        double total_t =
            (double)(end_t - start_t) /
            CLOCKS_PER_SEC;

        if (result != -1)
        {
            printf("\nElement %d found at index %d",
                   target,
                   result);
        }
        else
        {
            printf("\nElement %d not found in array",
                   target);
        }

        printf("\nTotal CPU time taken:- %f seconds",
               total_t);

        add_to_history("Interpolation Search",
                       length_of_array,
                       total_t);
    }
}
