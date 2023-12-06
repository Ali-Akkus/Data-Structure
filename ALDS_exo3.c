#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
struct Person;
typedef struct Person Person;
typedef Person* Position;

struct Person {
    char name[NAME_LEN];
    char surname[NAME_LEN];
    int yearofbirth;
    Person *next;
};

int pushFront(Position *head, char *name, char *surname, int yearofbirth) {
    Position ne =(Position) malloc(sizeof(Person)); //ne means new element

    if(ne == NULL){
        return -1;
    }

    strcpy(ne->name, name);
    strcpy(ne->surname, surname);
    ne->yearofbirth = yearofbirth;

    ne->next = *head;
    *head = ne;
    return 0;
}


int insertBehind(Position head,char *name, char *surname, int yearofbirth, char *targetname) {
    Position current = head;

    while (current != NULL) {
        if (strcmp(current->name, targetname) == 0) {
            Position ne = (Position)malloc(sizeof(Person));

            if (ne == NULL) {
                return -1;
            }

            strcpy(ne->name, name);
            strcpy(ne->surname, surname);
            ne->yearofbirth = yearofbirth;

            ne->next = current->next;
            current->next = ne;

            return 0;
        }

        current = current->next;
    }

    return -1;
}


int pushBack(Position *head, char *name, char *surname, int yearofbirth){
    Position ne = (Position) malloc(sizeof(Person));

    if(ne == NULL) {
        return -1;
    }

    strcpy(ne->name, name);
    strcpy(ne->surname, surname);
    ne->yearofbirth = yearofbirth;

    ne->next = NULL;

    if(*head == NULL){
        *head = ne;
    }
    else {
        Position current = *head;
        while (current->next !=NULL){
            current = current->next;
        }
        current->next = ne;
        
    }

    return 0;
}

int insertInFrontOf(Position *head, char *name, char *surname, int yearofbirth, char *targetname) {
    Position current = *head;
    Position previous = NULL;

    while (current != NULL) {
        if (strcmp(current->name, targetname) == 0) {
            Position ne = (Position)malloc(sizeof(Person));

            if (ne == NULL) {
                return -1;
            }

            strcpy(ne->name, name);
            strcpy(ne->surname, surname);
            ne->yearofbirth = yearofbirth;

            ne->next = current;
            if (previous == NULL) {
                *head = ne;
            } else {
                previous->next = ne;
            }

            return 0;
        }

        previous = current;
        current = current->next;
    }

    return -1;
}


void printList(Person *head) {
    Person *current = head;
    while (current != NULL) {
        printf("Name: %s, Surname: %s, Year of birth: %d\n", current->name, current->surname, current->yearofbirth);
        current = current->next;
    }
}




int findbySurname(Person *head, char *surname, Person *result){
    Person *current = head;
    while (current !=NULL){
        if(strcmp(current->surname, surname) == 0) {
            *result = *current;
            return 1;
        }
        current = current->next;

    }
    return -1;
}

int deleteItem(Person **head, char *surname) {
    Person *current = *head;
    Person *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0) {
            *head = current->next;
            free(current);
            return 0;
        }
        else{
            previous->next = current->next;
            free(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }
    return -1;
    
}


int main() {
    int isAppRunning = 1;
    int choice;
    int result;
    Person *head = NULL;

    do {
        printf("Enter your choice:\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Push front
                {
                    char name[NAME_LEN];
                    char surname[NAME_LEN];
                    int yearOfBirth;

                    printf("Enter name: ");
                    scanf("%s", name);
                    printf("Enter surname: ");
                    scanf("%s", surname);
                    printf("Enter year of birth: ");
                    scanf("%d", &yearOfBirth);

                    result = pushFront(&head, name, surname, yearOfBirth);
                    
                    if (result == -1) {
                        printf("Memory allocation failed.\n");
                    }
                }
                break;

            case 2:
                // Push back
                {
                    char name[NAME_LEN];
                    char surname[NAME_LEN];
                    int yearOfBirth;

                    printf("Enter name: ");
                    scanf("%s", name);
                    printf("Enter surname: ");
                    scanf("%s", surname);
                    printf("Enter year of birth: ");
                    scanf("%d", &yearOfBirth);

                    result = pushBack(&head, name, surname, yearOfBirth);
                    if (result == -1) {
                        printf("Memory allocation failed.\n");
                    }
                }
                break;

            case 3:
                // Print the list
                printList(head);
                break;

            case 4:
                // Find by surname
                {
                    char searchSurname[NAME_LEN];
                    Person resultPerson;

                    printf("Enter the surname to search for: ");
                    scanf("%s", searchSurname);

                    result = findbySurname(head, searchSurname, &resultPerson);
                    if (result == -1) {
                        printf("Person with the specified surname not found.\n");
                    } else {
                        printf("Found person: Name: %s, Surname: %s, Year of birth: %d\n",
                            resultPerson.name, resultPerson.surname, resultPerson.yearofbirth);
                    }
                }
                break;

            case 5:
                // Delete by surname
                {
                    char deleteSurname[NAME_LEN];

                    printf("Enter the surname to delete: ");
                    scanf("%s", deleteSurname);

                    result = deleteItem(&head, deleteSurname);
                    if (result == -1) {
                        printf("Person with the specified surname not found.\n");
                    } else {
                        printf("Person with the specified surname deleted.\n");
                    }
                }
                break;

            case 0:
                isAppRunning = 0;
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (isAppRunning);


    while (head != NULL) {
        Person *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

