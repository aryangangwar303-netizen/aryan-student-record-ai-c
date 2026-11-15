# AI Usage Log – PRC1001 C Programming Project
**Student:** Aryan Gangwar | **SAP ID:** 590042393  
**Course:** Programming in C (PRC1001) | UPES Semester I, 2026-27

---

## Entry 1 — September 20, 2026

**Tool Used:** ChatGPT (GPT-4)

**Prompt Given:**
> "In C, what is the correct way to validate that a user enters a float value between 0.0 and 10.0 without crashing the program when non-numeric input is given?"

**AI Response Summary:**  
AI suggested using a `do-while` loop with `scanf` and checking the return value. It also warned against using `fflush(stdin)` as it is undefined behavior in C, and suggested a manual flush pattern using `while ((ch = getchar()) != '\n' && ch != EOF)`. It showed how to combine the range check with the loop condition.

**How I Used It:**  
Applied the validated input loop in `registerStudent()` for SGPA entry in all 8 semester fields. This helped me avoid runtime crashes from invalid entries. I wrote the actual loop and integration myself.

**Code I Wrote After Learning:**
```c
do {
    printf("  Semester %d SGPA [0.0 - 10.0]: ", sem + 1);
    scanf("%f", &val);
    flushInput();
} while (val < 0.0f || val > 10.0f);
```

---

## Entry 2 — October 15, 2026

**Tool Used:** Google Gemini

**Prompt Given:**
> "Explain how insertion sort works for an array of structs in C, sorting by a numeric field. Show a simple example with integers first."

**AI Response Summary:**  
AI explained the Insertion Sort algorithm step by step — it picks each element from index 1 onwards, saves it as a "key", then shifts all larger elements one position to the right, and places the key in the correct position. It showed a dry run with 5 integers and then hinted at how to extend this to struct arrays.

**How I Used It:**  
I understood the shifting logic from the explanation and adapted it for my `StudentRecord` struct, using `sap_id` as the comparison field. The `sortStudentsBySAP()` function is entirely my own implementation — I used a local buffer copy to avoid modifying the global array.

**Code I Wrote After Learning:**
```c
for (int i = 1; i < total_records; i++) {
    StudentRecord key = buffer[i];
    int j = i - 1;
    while (j >= 0 && buffer[j].sap_id > key.sap_id) {
        buffer[j + 1] = buffer[j];
        j = j - 1;
    }
    buffer[j + 1] = key;
}
```

---

## Entry 3 — November 8, 2026

**Tool Used:** ChatGPT (GPT-4)

**Prompt Given:**
> "I am making an AI academic advisor section for my C project. I want to classify students into 4 performance tiers based on CGPA. What are good cutoff points and what advice can I give for each tier?"

**AI Response Summary:**  
AI suggested four tiers with cutoffs at 9.0, 7.5, and 6.0. For each tier, it recommended concise but specific advice — e.g., mentioning dean's honors and research for top students, targeting specific weak subjects for Tier 2, forming study groups and attending tutorials for Tier 3, and urgent counseling for Tier 4. It also suggested labeling them descriptively rather than just "Excellent/Good/Average/Poor".

**How I Used It:**  
I used the tier classification boundaries and the naming convention idea ("Outstanding Merit", "Meritorious Achievement", etc.) as the design blueprint. All the actual text, C code, printf statements, and the `getAcademicAdvisory()` and `runAdvisorModule()` functions were written entirely by me. I also added sub-menu options (individual vs whole cohort) which was not part of the AI suggestion.

---

## Entry 4 — November 15, 2026

**Tool Used:** Google Gemini

**Prompt Given:**
> "Give me 5 fictional Indian student names with realistic UPES email IDs for testing a C student database program. Make sure the CGPA values cover all 4 tier ranges."

**AI Response Summary:**  
AI provided 5 names (Kabir Mehta, Ananya Sen, Rohan Joshi, Divya Nair, Vikram Singhania) with sample SGPA values covering each of the four advisory tiers. It also suggested including students from different academic years to test the year-wise CGPA feature.

**How I Used It:**  
Used the student names and email format as the base for the `populateSampleRecords()` function. All SGPA values, SAP IDs, roll numbers, contact numbers, and academic year/semester values were assigned and hard-coded by me. The function itself including struct assignments is entirely my own work.

---

*Total AI interactions: 4 | All usage was for learning and design clarification only. All code was written by the student.*
