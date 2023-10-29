#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node Node;

struct Student {
    int studentNumber;
    char name[50];
    int age;
    struct Student* next;
};

typedef struct Student Student;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addToFront(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void addToEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void processNumbers(Node** head) {
    int num;
    
    printf("Enter numbers (-1 to stop):\n");
    
    while (1) {
        scanf("%d", &num);
        
        if (num == -1) {
            break;
        }
        
        if (num % 2 != 0) {
            // çiftse listenin baþýna ekler
            addToFront(head, num);
        } else {
            tekse listenin sonuna ekler
            addToEnd(head, num);
        }
    }
    printf("Numbers in the list: ");
    printList(*head); // numaralarý girdikten sonra sayýlarý sýralar
    
}
// Bubble sýrlamasýný kullanarak sayýlalarý azalarak sýralar
void bubbleSort(Node* head) {
    int swapped, i;
    Node* ptr1;
    Node* lptr = NULL;

    // listenin boþ oldugunu kontrol ettirir
    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data < ptr1->next->data) {
                // gelen element sonrakinden küçükse yer deðiþtirir
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void generateRandomNumbers(Node** head, int count) {
    srand(time(NULL)); // rastgele sayý üreten fonksiyon
    for (int i = 0; i < count; i++) {
        int num = rand() % 1000;  // 0 la 999 arasý sayý üretir
        addToFront(head, num);
    }
}

Student* createStudent(int studentNumber, const char* name, int age) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newStudent->studentNumber = studentNumber;
    strcpy(newStudent->name, name);
    newStudent->age = age;
    newStudent->next = NULL;
    return newStudent;
}

void addStudent(Student** head, int studentNumber, const char* name, int age) {
    Student* newStudent = createStudent(studentNumber, name, age);
    if (*head == NULL) {
        // Eðer liste boþsa, yeni öðrenci ismi listenin baþýna geçer
        *head = newStudent;
    } else {
        // Liste boþ deðilse, listenin sonuna gidip yeni öðrenci düðümünü ekler
        Student* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
}

void printStudents(Student* head) {
    int count = 0;
    Student* temp = head;
    printf("Student Information:\n");
    while (temp != NULL) {
        printf("Student Number: %d, Name: %s, Age: %d\n", temp->studentNumber, temp->name, temp->age);
        temp = temp->next;
        count++;
    }
    printf("Total number of students: %d\n", count);
}

void searchStudent(Student* head, const char* name) {
    Student* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Student Number: %d, Name: %s, Age: %d\n", temp->studentNumber, temp->name, temp->age);
            return;
        }
        temp = temp->next;
    }
    printf("Student not found.\n");
}

void deleteNextNode(Student* head, const char* name) {
    Student* temp = head;

    // istenilen öðrenciyi bulmak için döngü kullandýk hepsini taramasý için
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    
    if (temp != NULL && temp->next != NULL) {
        Student* toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
        printf("Next node after %s deleted.\n", name);
    } else {
        printf("Node not found or no next node to delete.\n");
    }
    
}

void printLongestName(Student* head) {
    Student* temp = head;
    int maxLength = 0;
    Student* longestNameStudent = NULL;
    while (temp != NULL) {
        int nameLength = strlen(temp->name);
        if (nameLength > maxLength) {
            maxLength = nameLength;
            longestNameStudent = temp;
        }
        temp = temp->next;
    }
    if (longestNameStudent != NULL) {
        printf("Student with the longest name: Student Number: %d, Name: %s, Age: %d\n", 
               longestNameStudent->studentNumber, longestNameStudent->name, longestNameStudent->age);
    } else {
        printf("No students in the list.\n");
    }
}

int main() {
    Node* numbersList = NULL;
    Student* studentsList = NULL;
    int choice;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add numbers to the list (odd at the beginning, even at the end)\n");
        printf("2. Add 100 random numbers and sort them (largest to smallest)\n");
        printf("3. Add student information\n");
        printf("4. Search student by name\n");
        printf("5. Delete next node after student by name\n");
        printf("6. Print student with the longest name\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                processNumbers(&numbersList);
                break;
            case 2:
                generateRandomNumbers(&numbersList, 100);
                printf("Generated random numbers:\n");
                printList(numbersList);
                bubbleSort(numbersList); // sayýlarý büyükten küçüðe sýralar
                printf("Sorted numbers (largest to smallest):\n");
                printList(numbersList);
                break;
            case 3: {
                int studentNumber, age;
                char name[50];
                printf("Enter student information (Student Number, Name, Age): ");
                scanf("%d %s %d", &studentNumber, name, &age);
                addStudent(&studentsList, studentNumber, name, age);
                printf("Student added to the list.\n");
                break;
            }
            case 4: {
                char name[50];
                printf("Enter student name to search: ");
                scanf("%s", name);
                searchStudent(studentsList, name);
                break;
            }
            case 5: {
                char name[50];
                printf("Enter student name to delete next node: ");
                scanf("%s", name);
                deleteNextNode(studentsList, name);
                break;
            }
            case 6:
                printLongestName(studentsList);
                break;
            case 7:
            
                while (numbersList != NULL) {
                    Node* temp = numbersList;
                    numbersList = numbersList->next;
                    free(temp);
                }
                while (studentsList != NULL) {
                    Student* temp = studentsList;
                    studentsList = studentsList->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
