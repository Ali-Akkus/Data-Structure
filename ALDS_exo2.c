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

int pushFront(Position head, char *name, char *surname, int yearofbirth) {
    Position ne =(Position) malloc(sizeof(Person)); //ne means new element

    if(ne == NULL){
        return -1;
    }

    strcpy(ne->name, name);
    strcpy(ne->surname, surname);
    ne->yearofbirth = yearofbirth;

    ne->next = head->next;
    head->next = ne;
    return 0;
}


int pushBack(Position head, char *name, char *surname, int yearofbirth){
    Position ne = (Position) malloc(sizeof(Person));

    if(ne == NULL) {
        return -1;
    }

    strcpy(ne->name, name);
    strcpy(ne->surname, surname);
    ne->yearofbirth = yearofbirth;

    ne->next = NULL;

    if(head == NULL){
        head = ne;
    }
    else {
        Position current = head;
        while (current->next !=NULL){
            current = current->next;
        }
        current->next = ne;
        
    }

    return 0;
}



int deleteList(Position head) { 
    Position temp = head;
    Position toDelete = head->next;

    while (head->next != NULL) {
        toDelete = head->next;
        temp->next = toDelete->next;
        free(toDelete);
    }
    
}

int main() {
    int isAppRunning = 1;
    int choice;
    int result;
    Person head = {.name = {0},.surname = {0},.yearofbirth = {0}, .next = NULL};

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
                        deletelist(&head);
                        return 1;
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
                        deletelist(&head);
                        return 1;
                    }
                }
                break;

            case 3:
                // Print the list
                printList(&head);
                break;

            case 4:
                // Find by surname
                {
                    char searchSurname[NAME_LEN];
                    Person resultPerson;

                    printf("Enter the surname to search for: ");
                    scanf("%s", searchSurname);

                    result = findbySurname(&head, searchSurname, &resultPerson);
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


    deletelist(&head);

    return 0;
}

