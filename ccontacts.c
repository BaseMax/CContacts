#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char* hash;
    char* name;
    char* family;
    char* phone;
    char* email;
    int age;
    bool sex; // TRUE = Male, FALSE = Female
    char* birthDate;
} ContactItem;

typedef struct {
    ContactItem** items;
    int size;
    int capacity;
} ContactList;

ContactList* createContactList(int capacity) {
    ContactList* list = (ContactList*) malloc(sizeof(ContactList));
    list->items = (ContactItem**) malloc(sizeof(ContactItem*) * capacity);
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void addContactList(ContactList* list, ContactItem* item) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->items = (ContactItem**) realloc(list->items, sizeof(ContactItem*) * list->capacity);
    }
    list->items[list->size++] = item;
}

void printContact(ContactItem* item) {
    printf("Name: %s %s\n", item->name, item->family);
    printf("Phone: %s\n", item->phone);
    printf("Email: %s\n", item->email);
    printf("Age: %d\n", item->age);
    printf("Sex: %s\n", item->sex == true ? "Make" : "Female");
    printf("Birth Date: %s\n", item->birthDate);
}

void printContactList(ContactList* list) {
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

    return item;
}

ContactItem* readContact(ContactItem* value)
{
    ContactItem* item = value == NULL ? createContact() : value;
    char input[100];

    if (item->name != NULL) printf("Enter name (default: %s): ", item->name);
    else printf("Enter name: ");
    scanf("%s", input);
    if (strcmp(input, "") != 0) strcpy(item->name, input);

    if (item->family != NULL) printf("Enter family (default: %s): ", item->family);
    else printf("Enter family: ");
    scanf("%s", input);
    if (strcmp(input, "") != 0) strcpy(item->family, input);

    if (item->phone != NULL) printf("Enter phone (default: %s): ", item->phone);
    else printf("Enter phone: ");
    scanf("%s", input);
    if (strcmp(input, "") != 0) strcpy(item->phone, input);

    if (item->email != NULL) printf("Enter email (default: %s): ", item->email);
    else printf("Enter email: ");
    scanf("%s", input);
    if (strcmp(input, "") != 0) strcpy(item->email, input);

    if (item->age != NULL) printf("Enter age (default: %d): ", item->age);
    else printf("Enter age: ");
    scanf("%s", input);
    if (strcmp(input, "") != 0) strcpy(item->age, input);

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

void deleteContactList(ContactList* list, char* hash)
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

    while (1) {
        printf("Menu:\n");
        printf("1. Insert entry\n");
        printf("2. Search entry\n");
        printf("3. Delete entry\n");
        printf("4. Exit\n\n");
        printf("Enter a choice: ");
        scanf("%s", input);

        int choice = atoi(input);
        switch (choice) {
            case 1: {
                ContactItem* item = readContact(NULL);
                if (item != NULL) addContactList(list, item);
            } break;

            case 2: {
                printf("Enter value of one of fields: ");
                scanf("%s", input);
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

            case 3: {
                printf("Enter value of one of fields: ");
                scanf("%s", input);
                ContactItem* item = searchContactList(list, input);
                if (item != NULL) {
                    deleteContactList(list, item->hash);
                    printf("The selected contact deleted.\n");
                }
                else printf("Contact not found!\n");
            } break;

            case 4: {
                printf("Goodbye!\n");
                return 0;
            } break;

            default: {
                printf("Unknown choice!\n");
            } break;
        }
    }

    return 0;
}