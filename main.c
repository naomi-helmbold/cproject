
#include <stdio.h>

struct Student {
    int id;
    char name[40];
    char program[30];
    float gpa;
};

struct Professor {
    int id;
    char name[40];
    char department[30];
    struct Student students[10];
    int num_students;
};

void add_student(struct Student *students, int *student_count) {
    if (*student_count >= 30) {
        printf("Student list is full.\n");
        return;
    }

    struct Student s;
    getchar();

    printf("Enter name of student: ");
    fgets(s.name, sizeof(s.name), stdin);

    do {
        printf("Enter student id: ");
        scanf("%d", &s.id);
    } while (s.id <= 0);

    getchar();

    printf("Enter program name: ");
    fgets(s.program, sizeof(s.program), stdin);

    do {
        printf("Enter GPA of student: ");
        scanf("%f", &s.gpa);
    } while (s.gpa < 0.0 || s.gpa > 4.0);

    students[*student_count] = s;
    (*student_count)++;
}

void add_prof(struct Professor *profs, int *prof_count) {

    struct Professor p;
    getchar();

    printf("Enter name of professor: ");
    fgets(p.name, sizeof(p.name), stdin);

    do {
        printf("Enter professor id: ");
        scanf("%d", &p.id);
    } while (p.id <= 0);

    getchar();

    printf("Enter department name: ");
    fgets(p.department, sizeof(p.department), stdin);

    p.num_students = 0;
    profs[*prof_count] = p;
    (*prof_count)++;
}

void display_students(struct Student *students, int student_count) {
    printf("\n--- Students ---\n");
    for (int i = 0; i < student_count; i++) {
        printf("Student ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Program: %s\n", students[i].program);
        printf("GPA: %.2f\n", students[i].gpa);
    }
}


void display_professors(struct Professor *profs, int prof_count) {
    printf("\n--- Professors ---\n");
    for (int i = 0; i < prof_count; i++) {
        printf("Professor ID: %d\n", profs[i].id);
        printf("Name: %s\n", profs[i].name);
        printf("Department: %s\n", profs[i].department);
    }
}

void modify_students(struct Student *students, int *student_count) {
    int id_of;
    printf("Which student would you like to modify? Enter ID:");
    scanf("%d", &id_of);

    int found = 0;
    for (int i = 0; i < *student_count; i++) {
        if (students[i].id == id_of) {found = 1;
            getchar ();
            printf("Current Name: %s", students[i].name);
            printf("Enter new name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            getchar ();
            printf("Current Program: %s", students[i].program);
            printf("\nEnter new program: ");
            fgets(students[i].program, sizeof(students[i].program), stdin);
            getchar ();
            printf("Current GPA: %.2f\n", students[i].gpa);
            do {
                printf("Enter new GPA: ");
                scanf("%f", &students[i].gpa);
            } while (students[i].gpa < 0.0 || students[i].gpa > 4.0);

            printf("\nStudent modified");
            }
        }
        if (!found) {
            printf("Student with ID %d not found.\n", id_of);
        }
}


void delete_student(struct Student *students, int *student_count) {
    int id_of;
    printf("Which student would you like to delete? Enter ID:");
    scanf("%d", &id_of);

    int found = 0;
    for (int i = 0; i < *student_count; i++) {
        if (students[i].id == id_of) {
            found = 1;
            for (int j = i; j < *student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*student_count)--;

            printf("Student with ID %d deleted.\n", id_of);
        }
    }
    if (!found) {
        printf("Student with ID %d not found.\n", id_of);
    }
}


void search_student(struct Student *students, int *student_count) {
    int id_of;
    printf("Which student would you like to see? Enter ID:");
    scanf("%d", &id_of);

    int found = 0;
    for (int i = 0; i < *student_count; i++) {
        if (students[i].id == id_of) {
            found = 1;
            printf("Name: %s", students[i].name);
            printf("Program: %s", students[i].program);
            printf("GPA: %.2f\n", students[i].gpa);
        }
    }
    if (!found) {
        printf("Student with ID %d not found.\n", id_of);
    }
}

void assign_student(struct Professor *profs, struct Student *students, int *student_count, int *prof_count) {
    int id_prof, id_of;
    printf("Enter the id of the professor you would like to assign a student to: ");
    scanf("%d", &id_prof);

    int prof_index = -1;
    for (int i = 0; i < *prof_count; i++) {
        if (profs[i].id == id_prof) {
            prof_index = i;
            break;
        }
    }

    if (prof_index == -1) {
        printf("Professor with ID %d not found.\n", id_prof);
        return;
    }

    printf("Enter the ID of the student you would like to assign to %s: ", profs[prof_index].name);
    scanf("%d", &id_of);

    for (int i = 0; i < *student_count; i++) {
        if (students[i].id == id_of) {
            if (profs[prof_index].num_students >= 10) {
                printf("This professor cannot take more students.\n");
                return;
            }
            profs[prof_index].students[profs[prof_index].num_students++] = students[i];
            printf("Student assigned to %s.\n", profs[prof_index].name);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id_of);
}

void display_student_of(struct Professor *profs, int *prof_count) {
    int id_prof;
    printf("Enter the ID of the professor: ");
    scanf("%d", &id_prof);

    for (int i = 0; i < *prof_count; i++) {
        if (profs[i].id == id_prof) {
            printf("Students of Professor %s:\n", profs[i].name);
            for (int j = 0; j < profs[i].num_students; j++) {
                printf("Student Name: %s\n", profs[i].students[j].name);
                printf("Student ID: %d\n", profs[i].students[j].id);
                printf("Program: %s\n", profs[i].students[j].program);
                printf("GPA: %.2f\n", profs[i].students[j].gpa);
                printf("\n");
            }
            return;
        }
    }
    printf("Professor with ID %d not found.\n", id_prof);
}

int main() {
    struct Student students[30];
    struct Professor profs[10];
    int student_count = 0;
    int prof_count = 0;

    int menu;


    do {
        printf("What would you like to do?\n"
           "1. Add student\n"
           "2. Add professor\n"
           "3. Display students\n"
           "4. Display professors\n"
           "5. Search a student\n"
           "6. Assign a student to a professor\n"
           "7. Display a professor's students.\n"
           "8. Modify a student.\n"
           "9. Delete a student.\n"
           "10. Exit the program.\n");
        scanf("%d", &menu);
        switch (menu) {
            case 1: add_student(students, &student_count); break;
            case 2: add_prof(profs, &prof_count); break;
            case 3: display_students(students, student_count); break;
            case 4: display_professors(profs, prof_count); break;
            case 5: search_student(students, &student_count); break;
            case 6: assign_student(profs,students,&student_count, &prof_count); break;
            case 7: display_student_of(profs, &prof_count); break;
            case 8: modify_students(students, &student_count); break;
            case 9: delete_student(&students[0],&student_count); break;
            case 10: printf("exit program");
        }
    } while (menu != 10);

    return 0;
}


