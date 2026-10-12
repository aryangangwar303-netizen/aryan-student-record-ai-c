/*
 * Part 2: Student Record Functions (Add, Search, Display, Delete)
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

void stripNewline(char *buffer) {
    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    }
}

int locateRecord(long long id) {
    for (int i = 0; i < total_records; i++) {
        if (record_db[i].sap_id == id) return i;
    }
    return -1;
}

void showStudentCard(const StudentRecord *rec) {
    printf("\n**************************************************\n");
    printf(" SAP ID        : %lld\n", rec->sap_id);
    printf(" Roll Number   : %s\n",   rec->roll_number);
    printf(" Student Name  : %s\n",   rec->student_name);
    printf(" Contact Phone : %s\n",   rec->contact_no);
    printf(" Email Address : %s\n",   rec->email_address);
    printf(" Academic Year : Year %d\n", rec->academic_year);
    printf(" Semester      : Semester %d\n", rec->current_sem);
    printf(" SGPA Scores   : ");
    for (int i = 0; i < TOTAL_SEMS; i++) {
        if (rec->sem_sgpa[i] > 0.0f) printf("[S%d: %.2f] ", i + 1, rec->sem_sgpa[i]);
        else printf("[S%d: N/A] ", i + 1);
    }
    printf("\n**************************************************\n");
}

void registerStudent() {
    if (total_records >= CAPACITY) {
        printf("\n[Alert] Database capacity reached.\n");
        return;
    }
    StudentRecord new_entry;
    printf("\n>>> REGISTER NEW STUDENT PROFILE <<<\n");

    printf("Enter SAP ID: ");
    scanf("%lld", &new_entry.sap_id);
    flushInput();

    if (locateRecord(new_entry.sap_id) != -1) {
        printf("[Error] A student with SAP ID %lld already exists.\n", new_entry.sap_id);
        return;
    }

    printf("Enter Roll Number: ");
    fgets(new_entry.roll_number, sizeof(new_entry.roll_number), stdin);
    stripNewline(new_entry.roll_number);

    printf("Enter Full Name: ");
    fgets(new_entry.student_name, sizeof(new_entry.student_name), stdin);
    stripNewline(new_entry.student_name);

    printf("Enter Contact Number: ");
    fgets(new_entry.contact_no, sizeof(new_entry.contact_no), stdin);
    stripNewline(new_entry.contact_no);

    printf("Enter University Email ID: ");
    fgets(new_entry.email_address, sizeof(new_entry.email_address), stdin);
    stripNewline(new_entry.email_address);

    do {
        printf("Enter Academic Year (1 to 4): ");
        scanf("%d", &new_entry.academic_year);
        flushInput();
    } while (new_entry.academic_year < 1 || new_entry.academic_year > 4);

    do {
        printf("Enter Current Semester (1 to 8): ");
        scanf("%d", &new_entry.current_sem);
        flushInput();
    } while (new_entry.current_sem < 1 || new_entry.current_sem > 8);

    printf("\nInput SGPA for all completed semesters (input 0 for upcoming):\n");
    for (int sem = 0; sem < TOTAL_SEMS; sem++) {
        float val = 0.0f;
        do {
            printf("  Semester %d SGPA [0.0 - 10.0]: ", sem + 1);
            scanf("%f", &val);
            flushInput();
        } while (val < 0.0f || val > 10.0f);
        new_entry.sem_sgpa[sem] = val;
    }

    record_db[total_records] = new_entry;
    total_records++;
    printf("\n[Success] Student record registered successfully!\n");
}

void findStudent() {
    long long target_id;
    printf("\n>>> QUERY STUDENT RECORD <<<\n");
    printf("Enter SAP ID to locate: ");
    scanf("%lld", &target_id);
    flushInput();

    int found_index = locateRecord(target_id);
    if (found_index == -1) printf("[Notice] No record matching SAP ID %lld was found.\n", target_id);
    else {
        printf("\n[Match Found] Profile Details:");
        showStudentCard(&record_db[found_index]);
    }
}

void showAllStudents() {
    printf("\n>>> COMPLETE STUDENT DIRECTORY <<<\n");
    if (total_records == 0) {
        printf("[Info] Directory is empty. Please add records first.\n");
        return;
    }
    printf("Total Enrolled Students: %d\n", total_records);
    for (int i = 0; i < total_records; i++) showStudentCard(&record_db[i]);
}

void removeStudent() {
    long long target_id;
    printf("\n>>> DELETE STUDENT PROFILE <<<\n");
    printf("Enter SAP ID to remove: ");
    scanf("%lld", &target_id);
    flushInput();

    int pos = locateRecord(target_id);
    if (pos == -1) {
        printf("[Notice] Record not found. Deletion aborted.\n");
        return;
    }

    printf("Confirm deletion of %s (SAP ID: %lld)? [y/n]: ", record_db[pos].student_name, record_db[pos].sap_id);
    char decision;
    scanf("%c", &decision);
    flushInput();

    if (decision == 'y' || decision == 'Y') {
        for (int i = pos; i < total_records - 1; i++) record_db[i] = record_db[i + 1];
        total_records--;
        printf("[Success] Record removed from database.\n");
    } else {
        printf("[Cancelled] Removal operation terminated.\n");
    }
}

int main() {
    int user_action;

    do {
        printf("\n==================================================\n");
        printf("    STUDENT ACADEMIC & RESULT MANAGEMENT SYSTEM   \n");
        printf("    Course: PRC1001 (Programming in C) - Part 2   \n");
        printf("==================================================\n");
        printf(" [ 1 ] Register New Student Profile\n");
        printf(" [ 2 ] Search Student Record by SAP ID\n");
        printf(" [ 3 ] Display Cumulative GPA (Coming in Part 3)\n");
        printf(" [ 4 ] Show Average CGPA by Year (Coming in Part 3)\n");
        printf(" [ 5 ] View Complete Student Directory\n");
        printf(" [ 6 ] Delete Student Record from System\n");
        printf(" [ 7 ] Sort Directory by SAP ID (Coming in Part 3)\n");
        printf(" [ 8 ] Sort Directory by Student Name (Coming in Part 3)\n");
        printf(" [ 9 ] AI Academic Advisor (Coming in Part 4)\n");
        printf(" [ 0 ] Exit Application\n");
        printf("==================================================\n");
        printf("Select action (0-9): ");
        scanf("%d", &user_action);
        flushInput();

        switch (user_action) {
            case 1: registerStudent(); break;
            case 2: findStudent(); break;
            case 5: showAllStudents(); break;
            case 6: removeStudent(); break;
            case 0: printf("\nSession closed. Program exited cleanly.\n"); break;
            default: printf("\nFeature introduced in next part.\n");
        }

        if (user_action != 0) {
            printf("\nPress [Enter] to return to main menu...");
            getchar();
        }

    } while (user_action != 0);

    return 0;
}
