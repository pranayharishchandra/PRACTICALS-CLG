#include <stdio.h>


// k -> pointing to curr pg where value will be stored in curr iteration
int main() {
    int page_array[50];
    int page_frames[20];
    int frame_count = 0;
    int frame_index, i, j, k = 0;
    int num_pages, total_frames, num_faults = 0;
    int distance_array[20];
    int temp_array[20], temp_distance;

    printf("Enter number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter the reference string: ");
    for (i = 0; i < num_pages; i++) {
        scanf("%d", &page_array[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &total_frames);

    // Initialize the first frame
    page_frames[k] = page_array[k];
    printf("\n\t%d\n", page_frames[k]);
    frame_count++;
    k++;

    // Loop through the remaining pages
    for (i = 1; i < num_pages; i++) {
        int is_page_fault = 1;

        // Check if the page is already in a frame
        for (j = 0; j < total_frames; j++) {
            if (page_array[i] == page_frames[j]) {
                is_page_fault = 0;
                break;
            }
        }

        // If the page is not already in a frame, determine which page to replace
        if (is_page_fault) {
            num_faults++;

            // If there are empty frames, use the next one
            if (k < total_frames) {
                page_frames[k] = page_array[i];
                k++;
            }
            // If all frames are in use, use the page with the farthest next reference
            else {
                // Calculate the distance to the next reference for each page in a frame
                for (j = 0; j < total_frames; j++) {
                    distance_array[j] = 0;
                    for (frame_index = i - 1; frame_index < num_pages; frame_index--) {
                        if (page_frames[j] != page_array[frame_index]) {
                            distance_array[j]++;
                        }
                        else {
                            break;
                        }
                    }
                }

                // Sort the distance array in descending order
                for (j = 0; j < total_frames; j++) {
                    temp_array[j] = distance_array[j];
                }
                for (j = 0; j < total_frames; j++) {
                    for (frame_index = j; frame_index < total_frames; frame_index++) {
                        if (temp_array[j] < temp_array[frame_index]) {
                            temp_distance = temp_array[j];
                            temp_array[j] = temp_array[frame_index];
                            temp_array[frame_index] = temp_distance;
                        }
                    }
                }

                // Replace the page with the farthest next reference
                for (j = 0; j < total_frames; j++) {
                    if (distance_array[j] == temp_array[0]) {
                        page_frames[j] = page_array[i];
                    }
                }
            }
        }

        // Print the current set of frames
        for (j = 0; j < total_frames; j++) {
            printf("\t%d", page_frames[j]);
        }
        printf("\n");
    }

    // Print the total number of page faults
    printf("\nThe number of page faults is: %d\n", num_faults);

    return 0;
}


/*

[root@localhost~]# gedit lru.c
root@localhost~]# cc lru.c
[root@localhost ~]# ./a.out

Enter number of pages: 10 
Enter the reference string: 7 5 9 4 3 7 9 6 2 1
Enter number of frames: 3
7 
7             5 
7              5              9 
4              5              9 
4              3              9 
4              3              7 
9              3              7 
9              6              7 
9              6              2
1              6              2
The number of page faults is 10

*/