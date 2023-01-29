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

char* sexName(int sex);

ContactList* createContactList(int capacity);

void addContactList(ContactList* list, ContactItem* item);

void printContact(ContactItem* item);

void printContactList(ContactList* list);

ContactItem* createContact();

ContactItem* readContact(ContactItem* value);

bool updateContactList(ContactList* list, char* hash, ContactItem* item);

ContactItem* searchContactList(ContactList* list, char* query);

bool deleteContactList(ContactList* list, char* hash);
