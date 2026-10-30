/*
 * Part 3: CGPA Computation & Sorting Algorithms
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

float computeCGPA(const StudentRecord *rec) {
    float cumulative_sum = 0.0f;
    int evaluated_semesters = 0;

    for (int i = 0; i < TOTAL_SEMS; i++) {
        if (rec->sem_sgpa[i] > 0.0f) {
            cumulative_sum += rec->sem_sgpa[i];
            evaluated_semesters++;
        }
    }
    if (evaluated_semesters > 0) {
        return cumulative_sum / (float)evaluated_semesters;
    }
    return 0.0f;
}

void swapRecords(StudentRecord *first, StudentRecord *second) {
    StudentRecord temp = *first;
    *first = *second;
    *second = temp;
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
    printf("\n Computed CGPA : %.2f\n", computeCGPA(rec));
    printf("**************************************************\n");
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
    printf("Enter Roll Number: "); fgets(new_entry.roll_number, sizeof(new_entry.roll_number), stdin); stripNewline(new_entry.roll_number);
    printf("Enter Full Name: "); fgets(new_entry.student_name, sizeof(new_entry.student_name), stdin); stripNewline(new_entry.student_name);
    printf("Enter Contact Number: "); fgets(new_entry.contact_no, sizeof(new_entry.contact_no), stdin); stripNewline(new_entry.contact_no);
    printf("Enter Email Address: "); fgets(new_entry.email_address, sizeof(new_entry.email_address), stdin); stripNewline(new_entry.email_address);

    do { printf("Enter Academic Year (1 to 4): "); scanf("%d", &new_entry.academic_year); flushInput(); } while (new_entry.academic_year < 1 || new_entry.academic_year > 4);
    do { printf("Enter Current Semester (1 to 8): "); scanf("%d", &new_entry.current_sem); flushInput(); } while (new_entry.current_sem < 1 || new_entry.current_sem > 8);

    printf("\nInput SGPA for all completed semesters (input 0 for upcoming):\n");
    for (int sem = 0; sem < TOTAL_SEMS; sem++) {
        float val = 0.0f;
        do { printf("  Semester %d SGPA [0.0 - 10.0]: ", sem + 1); scanf("%f", &val); flushInput(); } while (val < 0.0f || val > 10.0f);
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
    if (found_index == -1) printf("[Notice] No record found.\n");
    else showStudentCard(&record_db[found_index]);
}

void showStudentCGPA() {
    long long target_id;
    printf("\n>>> INDIVIDUAL CGPA INQUIRY <<<\n");
    printf("Enter Student SAP ID: ");
    scanf("%lld", &target_id);
    flushInput();

    int idx = locateRecord(target_id);
    if (idx == -1) printf("[Notice] Student not found.\n");
    else {
        printf("\nStudent : %s\nSAP ID  : %lld\nCGPA    : %.2f\n",
               record_db[idx].student_name, record_db[idx].sap_id, computeCGPA(&record_db[idx]));
    }
}

void showYearWiseCGPA() {
    printf("\n>>> YEAR-WISE COHORT CGPA AVERAGE <<<\n");
    for (int yr = 1; yr <= 4; yr++) {
        float year_total = 0.0f;
        int count_in_year = 0;
        for (int i = 0; i < total_records; i++) {
            if (record_db[i].academic_year == yr) {
                year_total += computeCGPA(&record_db[i]);
                count_in_year++;
            }
        }
        if (count_in_year > 0) printf("  Year %d Cohort -> Average CGPA: %.2f (%d enrolled)\n", yr, year_total / (float)count_in_year, count_in_year);
        else printf("  Year %d Cohort -> No active student records\n", yr);
    }
}

void showAllStudents() {
    printf("\n>>> COMPLETE STUDENT DIRECTORY <<<\n");
    if (total_records == 0) {
        printf("[Info] Directory is empty.\n");
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
    if (pos == -1) { printf("[Notice] Record not found.\n"); return; }
    printf("Confirm deletion of %s? [y/n]: ", record_db[pos].student_name);
    char decision; scanf("%c", &decision); flushInput();

    if (decision == 'y' || decision == 'Y') {
        for (int i = pos; i < total_records - 1; i++) record_db[i] = record_db[i + 1];
        total_records--;
        printf("[Success] Record removed.\n");
    } else printf("[Cancelled] Removal terminated.\n");
}

void sortStudentsBySAP() {
    printf("\n>>> STUDENTS SORTED BY SAP ID (INSERTION SORT) <<<\n");
    if (total_records == 0) { printf("[Info] No profiles to sort.\n"); return; }
    StudentRecord buffer[CAPACITY];
    for (int i = 0; i < total_records; i++) buffer[i] = record_db[i];

    for (int i = 1; i < total_records; i++) {
        StudentRecord key = buffer[i];
        int j = i - 1;
        while (j >= 0 && buffer[j].sap_id > key.sap_id) {
            buffer[j + 1] = buffer[j];
            j = j - 1;
        }
        buffer[j + 1] = key;
    }
    for (int i = 0; i < total_records; i++) showStudentCard(&buffer[i]);
}

void sortStudentsByName() {
    printf("\n>>> STUDENTS SORTED BY NAME (ALPHABETICAL BUBBLE SORT) <<<\n");
    if (total_records == 0) { printf("[Info] No profiles to sort.\n"); return; }
    StudentRecord buffer[CAPACITY];
    for (int i = 0; i < total_records; i++) buffer[i] = record_db[i];

    for (int pass = 0; pass < total_records - 1; pass++) {
        for (int i = 0; i < total_records - pass - 1; i++) {
            if (strcmp(buffer[i].student_name, buffer[i + 1].student_name) > 0) {
                swapRecords(&buffer[i], &buffer[i + 1]);
            }
        }
    }
    for (int i = 0; i < total_records; i++) showStudentCard(&buffer[i]);
}

int main() {
    int user_action;

    do {
        printf("\n==================================================\n");
        printf("    STUDENT ACADEMIC & RESULT MANAGEMENT SYSTEM   \n");
        printf("    Course: PRC1001 (Programming in C) - Part 3   \n");
        printf("==================================================\n");
        printf(" [ 1 ] Register New Student Profile\n");
        printf(" [ 2 ] Search Student Record by SAP ID\n");
        printf(" [ 3 ] Display Cumulative GPA (CGPA) of Student\n");
        printf(" [ 4 ] Show Average CGPA by Academic Year\n");
        printf(" [ 5 ] View Complete Student Directory\n");
        printf(" [ 6 ] Delete Student Record from System\n");
        printf(" [ 7 ] Sort Directory by SAP ID (Insertion Sort)\n");
        printf(" [ 8 ] Sort Directory by Student Name (Bubble Sort)\n");
        printf(" [ 9 ] AI-Assisted Academic Advisory Module (Coming in Part 4)\n");
        printf(" [ 0 ] Exit Application\n");
        printf("==================================================\n");
        printf("Select action (0-9): ");
        scanf("%d", &user_action);
        flushInput();

        switch (user_action) {
            case 1: registerStudent(); break;
            case 2: findStudent(); break;
            case 3: showStudentCGPA(); break;
            case 4: showYearWiseCGPA(); break;
            case 5: showAllStudents(); break;
            case 6: removeStudent(); break;
            case 7: sortStudentsBySAP(); break;
            case 8: sortStudentsByName(); break;
            case 0: printf("\nSession closed. Program exited cleanly.\n"); break;
            default: printf("\nFeature introduced in Part 4.\n");
        }

        if (user_action != 0) {
            printf("\nPress [Enter] to return to main menu...");
            getchar();
        }

    } while (user_action != 0);

    return 0;
}
