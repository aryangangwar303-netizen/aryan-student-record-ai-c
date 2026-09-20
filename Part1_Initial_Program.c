/*
 * Part 1: Initial C Program (Skeleton & Data Structure)
 * Course: Programming in C (PRC1001) - UPES
 * Student: Aryan Gangwar | SAP ID: 590042393
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define TOTAL_SEMS 8

typedef struct {
    long long sap_id;
    char roll_number[18];
    char student_name[60];
    char contact_no[16];
    char email_address[60];
    int academic_year;
    int current_sem;
    float sem_sgpa[TOTAL_SEMS];
} StudentRecord;

StudentRecord record_db[CAPACITY];
int total_records = 0;

void flushInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int main() {
    int user_action;

    do {
        printf("\n==================================================\n");
        printf("    STUDENT ACADEMIC & RESULT MANAGEMENT SYSTEM   \n");
        printf("    Course: PRC1001 (Programming in C) - UPES     \n");
        printf("==================================================\n");
        printf(" [ 1 ] Register New Student Profile\n");
        printf(" [ 2 ] Search Student Record by SAP ID\n");
        printf(" [ 3 ] Display Cumulative GPA (CGPA) of Student\n");
        printf(" [ 4 ] Show Average CGPA by Academic Year\n");
        printf(" [ 5 ] View Complete Student Directory\n");
        printf(" [ 6 ] Delete Student Record from System\n");
        printf(" [ 7 ] Sort Directory by SAP ID (Insertion Sort)\n");
        printf(" [ 8 ] Sort Directory by Student Name (Bubble Sort)\n");
        printf(" [ 9 ] AI-Assisted Academic Advisory Module\n");
        printf(" [10 ] Load Sample Test Cohort (5 Students)\n");
        printf(" [ 0 ] Exit Application\n");
        printf("==================================================\n");
        printf("Select action (0-10): ");
        scanf("%d", &user_action);
        flushInput();

        if (user_action != 0) {
            printf("\n[Stage 1] Initial structure defined. Function logic implemented in subsequent stages.\n");
            printf("\nPress [Enter] to return to main menu...");
            getchar();
        }

    } while (user_action != 0);

    printf("\nSession closed. Program exited cleanly.\n");
    return 0;
}
