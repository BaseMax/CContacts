#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    char* hash;
    char* name;
    char* family;
    char* phone;
    char* email;
    int age;
    int sex; // 0 = Male, 1 = Female, -1 = none
    char* birthDate;
} ContactItem;

typedef struct
{
    int size;
    int capacity;
    ContactItem** items;
} ContactList;

char* sexName(int sex)
{
    return sex == 1 ? "Male" : (sex == 2 ? "Female" : "None");
}

ContactList* createContactList(int capacity)
{
    ContactList* list = (ContactList*) malloc(sizeof(ContactList));
    list->size = 0;
    list->capacity = capacity;
    list->items = (ContactItem**) malloc(sizeof(ContactItem*) * capacity);
    return list;
}

void addContactList(ContactList* list, ContactItem* item)
{
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->items = (ContactItem**) realloc(list->items, sizeof(ContactItem*) * list->capacity);
    }
    list->items[list->size++] = item;
}

void printContact(ContactItem* item)
{
    printf("Name: %s %s\n", item->name, item->family);
    printf("Phone: %s\n", item->phone);
    printf("Email: %s\n", item->email);
    printf("Age: %d\n", item->age);
    printf("Sex: %s\n", sexName(item->sex));
    printf("Birth Date: %s\n", item->birthDate);
}

void printContactList(ContactList* list)
{
    for (int i = 0; i < list->size; i++) {
        printContact(list->items[i]);
        printf("\n");
    }
}

ContactItem* createContact()
{
    ContactItem* item = malloc(sizeof(ContactItem));

    item->hash = malloc(sizeof(char)*512);
    item->name = malloc(sizeof(char)*512);
    item->family = malloc(sizeof(char)*512);
    item->phone = malloc(sizeof(char)*512);
    item->email = malloc(sizeof(char)*512);
    item->birthDate = malloc(sizeof(char)*512);
    item->age = 0;
    item->sex = -1;

    return item;
}

ContactItem* readContact(ContactItem* value)
{
    ContactItem* item = value == NULL ? createContact() : value;
    char input[100];

    if (strlen(item->name) != 0) printf("Enter name (default: %s): ", item->name);
    else printf("Enter name: ");
    if (scanf("%[^\n]%*c", input) > 0) strcpy(item->name, input);

    if (strlen(item->family) != 0) printf("Enter family (default: %s): ", item->family);
    else printf("Enter family: ");
    if (scanf("%[^\n]%*c", input) > 0) strcpy(item->family, input);

    if (strlen(item->phone) != 0) printf("Enter phone (default: %s): ", item->phone);
    else printf("Enter phone: ");
    if (scanf("%[^\n]%*c", input) > 0) strcpy(item->phone, input);

    if (strlen(item->email) != 0) printf("Enter email (default: %s): ", item->email);
    else printf("Enter email: ");
    if (scanf("%[^\n]%*c", input) > 0) strcpy(item->email, input);

    if (strlen(item->birthDate) != 0) printf("Enter birthDate (default: %s): ", item->birthDate);
    else printf("Enter birthDate: ");
    if (scanf("%[^\n]%*c", input) > 0) strcpy(item->birthDate, input);

    if (item->age != 0) printf("Enter age (default: %d): ", item->age);
    else printf("Enter age: ");
    if (scanf("%[^\n]%*c", input) > 0) item->age = atoi(input);

    if (item->sex != -1) printf("Enter sex (default: %s): ", sexName(item->sex));
    else printf("Enter sex: ");
    printf("1 for Male, 2 for Female ");
    if (scanf("%[^\n]%*c", input) > 0) item->age = atoi(input);

    return item;
}

bool updateContactList(ContactList* list, char* hash, ContactItem* item)
{
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->items[i]->hash, hash) == 0) {
            list->items[i] = item;
            return true;
        }
    }
    return false;
}

ContactItem* searchContactList(ContactList* list, char* query)
{
    ContactItem* item = NULL;

    for (int i = 0; i < list->size; i++) {
        if (list->items[i] == NULL) continue;

        if (strcmp(list->items[i]->hash, query) == 0) {
            item = list->items[i];
            break;
        }
        else if (strcmp(list->items[i]->name, query) == 0) {
            item = list->items[i];
            break;
        }
        else if (strcmp(list->items[i]->family, query) == 0) {
            item = list->items[i];
            break;
        }
        else if (strcmp(list->items[i]->phone, query) == 0) {
            item = list->items[i];
            break;
        }
        else if (strcmp(list->items[i]->email, query) == 0) {
            item = list->items[i];
            break;
        }
        else if (strcmp(list->items[i]->birthDate, query) == 0) {
            item = list->items[i];
            break;
        }
    }

    return item;
}

bool deleteContactList(ContactList* list, char* hash)
{
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->items[i]->hash, hash)  == 0) {
            free(list->items[i]->hash);
            free(list->items[i]->name);
            free(list->items[i]->family);
            free(list->items[i]->phone);
            free(list->items[i]->email);
            free(list->items[i]->birthDate);
            free(list->items[i]);
            for (int j = i; j < list->size - 1; j++) {
                list->items[j] = list->items[j + 1];
            }
            list->size--;
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    char input[100];
    ContactList* list = createContactList(10);

    ContactItem* item = createContact();
    strcpy(item->name, "Ali");
    strcpy(item->family, "Rezaei");
    strcpy(item->phone, "09123456789");
    strcpy(item->email, "max@asrez.com");
    strcpy(item->birthDate, "1990/01/01");
    item->sex = 1;
    item->age = 22;
    addContactList(list, item);

    char s2[100] = "max@asrez.com";
    item = searchContactList(list, s2);
    if (item != NULL) {
        printContact(item);
        ContactItem* item = readContact(item);
        if (item == NULL) printf("Error in entered new values!\n");
        else {
            updateContactList(list, item->hash, item);
            printf("The selected contact updated.\n");
        }
    }

    while (1) {
        printf("Menu:\n");
        printf("1. List\n");
        printf("2. Insert entry\n");
        printf("3. Search entry\n");
        printf("4. Delete entry\n");
        printf("5. Exit\n\n");
        printf("Enter a choice: ");
        scanf("%[^\n]%*c", input);

        int choice = atoi(input);
        switch (choice) {
            case 1: {
                if (list->size == 0) {
                    printf("Contact list is empty!\n");
                } else {
                    printf("Contact list(%d):\n", list->size);
                    for (int i = 0; i < list->size; i++) {
                        printContact(list->items[i]);
                    }
                }
            } break;

            case 2: {
                ContactItem* item = readContact(NULL);
                if (item != NULL) addContactList(list, item);
            } break;

            case 3: {
                printf("Enter value of one of fields: ");
                scanf("%[^\n]%*c", input);
                ContactItem* item = searchContactList(list, input);
                if (item != NULL) {
                    printContact(item);
                    ContactItem* item = readContact(item);
                    if (item == NULL) printf("Error in entered new values!\n");
                    else {
                        updateContactList(list, item->hash, item);
                        printf("The selected contact updated.\n");
                    }
                }
                else printf("Contact not found!\n");
            } break;

            case 4: {
                printf("Enter value of one of fields: ");
                scanf("%[^\n]%*c", input);
                ContactItem* item = searchContactList(list, input);
                if (item != NULL) {
                    deleteContactList(list, item->hash);
                    printf("The selected contact deleted.\n");
                }
                else printf("Contact not found!\n");
            } break;

            case 5: {
                printf("Goodbye!\n");
                return 0;
            } break;

            default: {
                printf("Unknown choice!\n");
            } break;
        }

        printf("\n\n");
    }

    return 0;
}