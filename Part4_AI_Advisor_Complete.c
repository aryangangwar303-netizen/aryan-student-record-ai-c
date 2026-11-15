/*
 * Course: Programming in C (Course Code: PRC1001)
 * Project: Student Record and Result Management System
 * Name: Aryan Gangwar
 * SAP ID: 590042393
 * University of Petroleum and Energy Studies (UPES)
 * Semester I, B.Tech Computer Science & Engineering
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define TOTAL_SEMS 8

// Structure representing an individual student's academic record
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

// Global array and current size tracker
StudentRecord record_db[CAPACITY];
int total_records = 0;

// Utility to clear standard input stream
void flushInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Utility to strip trailing newline character
void stripNewline(char *buffer) {
    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    }
}

// Linear lookup for student record index by SAP ID
int locateRecord(long long id) {
    for (int i = 0; i < total_records; i++) {
        if (record_db[i].sap_id == id) {
            return i;
        }
    }
    return -1;
}

// Calculate cumulative GPA from valid semester entries
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

// Helper to swap two student records
void swapRecords(StudentRecord *first, StudentRecord *second) {
    StudentRecord temp = *first;
    *first = *second;
    *second = temp;
}

// Display formatted details for a single student profile
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
        if (rec->sem_sgpa[i] > 0.0f) {
            printf("[S%d: %.2f] ", i + 1, rec->sem_sgpa[i]);
        } else {
            printf("[S%d: N/A] ", i + 1);
        }
    }
    printf("\n Computed CGPA : %.2f\n", computeCGPA(rec));
    printf("**************************************************\n");
}

// Feature 1: Add new student entry
void registerStudent() {
    if (total_records >= CAPACITY) {
        printf("\n[Alert] Database capacity reached (%d records max).\n", CAPACITY);
        return;
    }

    StudentRecord new_entry;
    printf("\n>>> REGISTER NEW STUDENT PROFILE <<<\n");

    printf("Enter SAP ID: ");
    scanf("%lld", &new_entry.sap_id);
    flushInput();

    if (locateRecord(new_entry.sap_id) != -1) {
        printf("[Error] A student with SAP ID %lld already exists in the system.\n", new_entry.sap_id);
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

    printf("\nInput SGPA for all completed semesters (input 0 for upcoming semesters):\n");
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

// Feature 2: Search student record by SAP ID
void findStudent() {
    long long target_id;
    printf("\n>>> QUERY STUDENT RECORD <<<\n");
    printf("Enter SAP ID to locate: ");
    scanf("%lld", &target_id);
    flushInput();

    int found_index = locateRecord(target_id);
    if (found_index == -1) {
        printf("[Notice] No record matching SAP ID %lld was found.\n", target_id);
    } else {
        printf("\n[Match Found] Profile Details:");
        showStudentCard(&record_db[found_index]);
    }
}

// Feature 3: Calculate and show individual student CGPA
void showStudentCGPA() {
    long long target_id;
    printf("\n>>> INDIVIDUAL CGPA INQUIRY <<<\n");
    printf("Enter Student SAP ID: ");
    scanf("%lld", &target_id);
    flushInput();

    int idx = locateRecord(target_id);
    if (idx == -1) {
        printf("[Notice] Student not found.\n");
    } else {
        printf("\nStudent : %s\n", record_db[idx].student_name);
        printf("SAP ID  : %lld\n", record_db[idx].sap_id);
        printf("CGPA    : %.2f\n", computeCGPA(&record_db[idx]));
    }
}

// Feature 4: Compute average CGPA grouped by year of study
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

        if (count_in_year > 0) {
            printf("  Year %d Cohort -> Average CGPA: %.2f (%d enrolled)\n",
                   yr, year_total / (float)count_in_year, count_in_year);
        } else {
            printf("  Year %d Cohort -> No active student records\n", yr);
        }
    }
}

// Feature 5: Display all student profiles
void showAllStudents() {
    printf("\n>>> COMPLETE STUDENT DIRECTORY <<<\n");
    if (total_records == 0) {
        printf("[Info] Directory is empty. Please add records first.\n");
        return;
    }

    printf("Total Enrolled Students: %d\n", total_records);
    for (int i = 0; i < total_records; i++) {
        showStudentCard(&record_db[i]);
    }
}

// Feature 6: Delete a student record by SAP ID
void removeStudent() {
    long long target_id;
    printf("\n>>> DELETE STUDENT PROFILE <<<\n");
    printf("Enter SAP ID of the student to remove: ");
    scanf("%lld", &target_id);
    flushInput();

    int pos = locateRecord(target_id);
    if (pos == -1) {
        printf("[Notice] Record not found. Deletion aborted.\n");
        return;
    }

    printf("Confirm deletion of %s (SAP ID: %lld)? [y/n]: ",
           record_db[pos].student_name, record_db[pos].sap_id);
    char decision;
    scanf("%c", &decision);
    flushInput();

    if (decision == 'y' || decision == 'Y') {
        for (int i = pos; i < total_records - 1; i++) {
            record_db[i] = record_db[i + 1];
        }
        total_records--;
        printf("[Success] Record removed from database.\n");
    } else {
        printf("[Cancelled] Removal operation terminated by user.\n");
    }
}

// Feature 7: Sort by SAP ID in ascending order using Insertion Sort
void sortStudentsBySAP() {
    printf("\n>>> STUDENTS SORTED BY SAP ID (INSERTION SORT) <<<\n");
    if (total_records == 0) {
        printf("[Info] No student profiles available to sort.\n");
        return;
    }

    // Work on a duplicate buffer to preserve original sequence
    StudentRecord buffer[CAPACITY];
    for (int i = 0; i < total_records; i++) {
        buffer[i] = record_db[i];
    }

    // Insertion Sort implementation
    for (int i = 1; i < total_records; i++) {
        StudentRecord key = buffer[i];
        int j = i - 1;

        while (j >= 0 && buffer[j].sap_id > key.sap_id) {
            buffer[j + 1] = buffer[j];
            j = j - 1;
        }
        buffer[j + 1] = key;
    }

    for (int i = 0; i < total_records; i++) {
        showStudentCard(&buffer[i]);
    }
}

// Feature 8: Sort by Name in alphabetical order using Bubble Sort with swap helper
void sortStudentsByName() {
    printf("\n>>> STUDENTS SORTED BY NAME (ALPHABETICAL BUBBLE SORT) <<<\n");
    if (total_records == 0) {
        printf("[Info] No student profiles available to sort.\n");
        return;
    }

    StudentRecord buffer[CAPACITY];
    for (int i = 0; i < total_records; i++) {
        buffer[i] = record_db[i];
    }

    // Bubble Sort with string comparison
    for (int pass = 0; pass < total_records - 1; pass++) {
        for (int i = 0; i < total_records - pass - 1; i++) {
            if (strcmp(buffer[i].student_name, buffer[i + 1].student_name) > 0) {
                swapRecords(&buffer[i], &buffer[i + 1]);
            }
        }
    }

    for (int i = 0; i < total_records; i++) {
        showStudentCard(&buffer[i]);
    }
}

// Part B: AI-Assisted Academic Advisor Module
// Categories designed with AI guidance, implemented with structured if-else ladder
void getAcademicAdvisory(float cgpa) {
    printf("\n==================================================\n");
    printf("        ACADEMIC ADVISORY ASSESSMENT REPORT       \n");
    printf("==================================================\n");
    printf(" Evaluated CGPA: %.2f\n", cgpa);

    if (cgpa >= 9.0f) {
        printf(" Classification : Tier 1 - Outstanding Merit\n");
        printf(" Recommendation : Exemplary academic standing! You qualify for dean's\n");
        printf("                  honors and campus research opportunities. Maintain\n");
        printf("                  your rigorous study habits and consider technical publishing.\n");
    } else if (cgpa >= 7.5f) {
        printf(" Classification : Tier 2 - Meritorious Achievement\n");
        printf(" Recommendation : Commendable performance across semesters! Address minor\n");
        printf("                  dips in specific theory/lab subjects to push your\n");
        printf("                  overall score into the distinction bracket (9.0+).\n");
    } else if (cgpa >= 6.0f) {
        printf(" Classification : Tier 3 - Satisfactory / Growth Focus\n");
        printf(" Recommendation : Satisfactory academic progress, but there is significant\n");
        printf("                  potential for improvement. Form study groups, attend\n");
        printf("                  tutorial hours, and allocate more time to foundational courses.\n");
    } else {
        printf(" Classification : Tier 4 - Academic Warning Notice\n");
        printf(" Recommendation : Performance requires urgent intervention! Schedule an\n");
        printf("                  immediate counseling session with your faculty advisor\n");
        printf("                  and follow a structured daily revision schedule.\n");
    }
    printf("==================================================\n");
}

void runAdvisorModule() {
    printf("\n>>> AI-ASSISTED ACADEMIC ADVISOR <<<\n");
    if (total_records == 0) {
        printf("[Info] No active records found in database.\n");
        return;
    }

    printf(" [1] Generate advisory for an individual student (by SAP ID)\n");
    printf(" [2] Generate advisory summary for entire cohort\n");
    printf(" Enter option: ");
    int mode;
    scanf("%d", &mode);
    flushInput();

    if (mode == 1) {
        long long search_id;
        printf(" Enter SAP ID: ");
        scanf("%lld", &search_id);
        flushInput();

        int idx = locateRecord(search_id);
        if (idx == -1) {
            printf("[Notice] Student profile not found.\n");
        } else {
            printf("\nStudent: %s | SAP ID: %lld", record_db[idx].student_name, record_db[idx].sap_id);
            float current_cgpa = computeCGPA(&record_db[idx]);
            getAcademicAdvisory(current_cgpa);
        }
    } else if (mode == 2) {
        for (int i = 0; i < total_records; i++) {
            printf("\nStudent: %s | SAP ID: %lld", record_db[i].student_name, record_db[i].sap_id);
            float current_cgpa = computeCGPA(&record_db[i]);
            getAcademicAdvisory(current_cgpa);
        }
    } else {
        printf("[Error] Invalid selection.\n");
    }
}

// Populate database with 5 distinct sample student records
void populateSampleRecords() {
    // Record 1 - Outstanding Merit (CGPA >= 9.0)
    record_db[0].sap_id = 59002001;
    strcpy(record_db[0].roll_number, "R2001");
    strcpy(record_db[0].student_name, "Kabir Mehta");
    strcpy(record_db[0].contact_no, "9823456781");
    strcpy(record_db[0].email_address, "kabir.mehta@stu.upes.ac.in");
    record_db[0].academic_year = 2;
    record_db[0].current_sem = 4;
    record_db[0].sem_sgpa[0] = 9.30f;
    record_db[0].sem_sgpa[1] = 9.10f;
    record_db[0].sem_sgpa[2] = 9.40f;
    record_db[0].sem_sgpa[3] = 9.20f;

    // Record 2 - Meritorious Achievement (CGPA 7.5 - 8.9)
    record_db[1].sap_id = 59002002;
    strcpy(record_db[1].roll_number, "R2002");
    strcpy(record_db[1].student_name, "Ananya Sen");
    strcpy(record_db[1].contact_no, "9812345672");
    strcpy(record_db[1].email_address, "ananya.sen@stu.upes.ac.in");
    record_db[1].academic_year = 1;
    record_db[1].current_sem = 2;
    record_db[1].sem_sgpa[0] = 7.90f;
    record_db[1].sem_sgpa[1] = 8.10f;

    // Record 3 - Satisfactory / Growth Focus (CGPA 6.0 - 7.4)
    record_db[2].sap_id = 59002003;
    strcpy(record_db[2].roll_number, "R2003");
    strcpy(record_db[2].student_name, "Rohan Joshi");
    strcpy(record_db[2].contact_no, "9712345673");
    strcpy(record_db[2].email_address, "rohan.joshi@stu.upes.ac.in");
    record_db[2].academic_year = 3;
    record_db[2].current_sem = 5;
    record_db[2].sem_sgpa[0] = 6.60f;
    record_db[2].sem_sgpa[1] = 6.20f;
    record_db[2].sem_sgpa[2] = 6.50f;
    record_db[2].sem_sgpa[3] = 6.30f;
    record_db[2].sem_sgpa[4] = 6.70f;

    // Record 4 - Academic Warning Notice (CGPA < 6.0)
    record_db[3].sap_id = 59002004;
    strcpy(record_db[3].roll_number, "R2004");
    strcpy(record_db[3].student_name, "Divya Nair");
    strcpy(record_db[3].contact_no, "9612345674");
    strcpy(record_db[3].email_address, "divya.nair@stu.upes.ac.in");
    record_db[3].academic_year = 1;
    record_db[3].current_sem = 1;
    record_db[3].sem_sgpa[0] = 5.40f;

    // Record 5 - Meritorious Achievement
    record_db[4].sap_id = 59002005;
    strcpy(record_db[4].roll_number, "R2005");
    strcpy(record_db[4].student_name, "Vikram Singhania");
    strcpy(record_db[4].contact_no, "9512345675");
    strcpy(record_db[4].email_address, "vikram.singh@stu.upes.ac.in");
    record_db[4].academic_year = 4;
    record_db[4].current_sem = 7;
    record_db[4].sem_sgpa[0] = 7.60f;
    record_db[4].sem_sgpa[1] = 8.20f;
    record_db[4].sem_sgpa[2] = 7.80f;
    record_db[4].sem_sgpa[3] = 8.00f;
    record_db[4].sem_sgpa[4] = 7.90f;
    record_db[4].sem_sgpa[5] = 8.10f;
    record_db[4].sem_sgpa[6] = 7.70f;

    total_records = 5;
    printf("\n[Success] 5 diverse cohort student profiles loaded into memory.\n");
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

        switch (user_action) {
            case 1:
                registerStudent();
                break;
            case 2:
                findStudent();
                break;
            case 3:
                showStudentCGPA();
                break;
            case 4:
                showYearWiseCGPA();
                break;
            case 5:
                showAllStudents();
                break;
            case 6:
                removeStudent();
                break;
            case 7:
                sortStudentsBySAP();
                break;
            case 8:
                sortStudentsByName();
                break;
            case 9:
                runAdvisorModule();
                break;
            case 10:
                populateSampleRecords();
                break;
            case 0:
                printf("\nSession closed. Program exited cleanly.\n");
                break;
            default:
                printf("\n[Warning] Invalid selection. Please choose an option between 0 and 10.\n");
        }

        if (user_action != 0) {
            printf("\nPress [Enter] to return to main menu...");
            getchar();
        }

    } while (user_action != 0);

    return 0;
}
