#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define ITEM_TYPE 0
#define MEMBER_TYPE 1
#define CART_TYPE 2
#define TRANSACTION_TYPE 3

typedef struct item_t {
    int ID, price, stock;
    char name[101];
} Item;

typedef struct member_t {
    int ID, balance;
    char username[101], password[101];
    char name[101], phoneNum[20], address[101];
    char registDate[15], registTime[15];
} Member;

typedef struct cart_t {
    int ID, price, amount, stock;
    char name[101];
} Cart;

typedef struct transaction_t {
    int ID, memberID, totalPrice;
    char name[101], transactionDate[15], transactionTime[15];
} Transaction;

/* NODE DAN LINKED LIST */
typedef struct node_t {
    union {
        Item item_data;
        Member member_data;
        Cart cart_data;
        Transaction transaction_data;
    };
    struct node_t *next;
} ListNode;

typedef struct list_t {
    unsigned _size;
    ListNode *_head;
} List;

/* DEKLARASI LINKED LIST*/
List itemList;
List memberList;
List cartList;
List transactionList;

/* DAFTAR FUNGSI YANG TERSEDIA */

void list_init(List *list);
bool list_isEmpty(List *list);
void list_pushFront(List *list, const void *data, size_t dataSize, int dataType);
void list_popFront(List *list);
void list_pushBack(List *list, const void *data, size_t dataSize, int dataType);
void list_popBack(List *list);
void list_insertAt(List *list, int index, const void *data, size_t dataSize, int dataType);
void list_removeAt(List *list, int index);
void list_remove(List *list, int value);
int list_front(List *list);
int list_back(List *list);
int list_getAt(List *list, int index);

/* Function definition below */
void list_init(List *list) {
    list->_head = NULL;
    list->_size = 0;
}

bool list_isEmpty(List *list) {
    return (list->_head == NULL);
}

void list_pushFront(List *list, const void *data, size_t dataSize, int dataType) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode) {
        list->_size++;
        switch (dataType) {
        case ITEM_TYPE:
            newNode->item_data = *(Item *)data;
            break;
        case MEMBER_TYPE:
            newNode->member_data = *(Member *)data;
            break;
        case CART_TYPE:
            newNode->cart_data = *(Cart *)data;
            break;
        case TRANSACTION_TYPE:
            newNode->transaction_data = *(Transaction *)data;
            break;
        default:
            free(newNode);
            printf("Invalid data type\n");
            return;
        }

        if (list_isEmpty(list))
            newNode->next = NULL;
        else
            newNode->next = list->_head;
        list->_head = newNode;
    }
}
void list_popFront(List *list) {
    if (!list_isEmpty(list)) {
        ListNode *temp = list->_head;
        list->_head = list->_head->next;
        free(temp);
        list->_size--;
    }
}

void list_pushBack(List *list, const void *data, size_t dataSize, int dataType) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode) {
        list->_size++;

        switch (dataType) {
        case ITEM_TYPE:
            newNode->item_data = *(Item *)data;
            break;
        case MEMBER_TYPE:
            newNode->member_data = *(Member *)data;
            break;
        case CART_TYPE:
            newNode->cart_data = *(Cart *)data;
            break;
        case TRANSACTION_TYPE:
            newNode->transaction_data = *(Transaction *)data;
            break;
        default:
            free(newNode);
            printf("Invalid data type\n");
            return;
        }

        newNode->next = NULL;

        if (list_isEmpty(list))
            list->_head = newNode;
        else {
            ListNode *temp = list->_head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }
}

void list_popBack(List *list) {
    if (!list_isEmpty(list)) {
        ListNode *nextNode = list->_head->next;
        ListNode *currNode = list->_head;

        if (currNode->next == NULL) {
            free(currNode);
            list->_head = NULL;
            return;
        }

        while (nextNode->next != NULL) {
            currNode = nextNode;
            nextNode = nextNode->next;
        }
        currNode->next = NULL;
        free(nextNode);
        list->_size--;
    }
}

void list_insertAt(List *list, int index, const void *data, size_t dataSize, int dataType) {
    if (list_isEmpty(list) || index >= list->_size) {
        list_pushBack(list, data, dataSize, dataType);
        return;
    } else if (index == 0 || index < 0) {
        list_pushFront(list, data, dataSize, dataType);
        return;
    }

    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode) {
        ListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index - 1) {
            temp = temp->next;
            _i++;
        }

        switch (dataType) {
        case ITEM_TYPE:
            newNode->item_data = *(Item *)data;
            break;
        case MEMBER_TYPE:
            newNode->member_data = *(Member *)data;
            break;
        case CART_TYPE:
            newNode->cart_data = *(Cart *)data;
            break;
        case TRANSACTION_TYPE:
            newNode->transaction_data = *(Transaction *)data;
            break;
        default:
            free(newNode);
            printf("Invalid data type\n");
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
        list->_size++;
    }
}

void list_removeAt(List *list, int index) {
    if (!list_isEmpty(list)) {
        if (index >= list->_size) {
            list_popBack(list);
            return;
        } else if (index == 0 || index < 0) {
            list_popFront(list);
            return;
        }

        ListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index - 1) {
            temp = temp->next;
            _i++;
        }
        ListNode *nextTo = temp->next->next;
        free(temp->next);
        temp->next = nextTo;
        list->_size--;
    }
}

void list_remove(List *list, int value) {
    if (!list_isEmpty(list)) {
        ListNode *temp, *prev;
        temp = list->_head;

        if (temp->data == value) {
            list_popFront(list);
            return;
        }
        while (temp != NULL && temp->data != value) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) return;
        prev->next = temp->next;
        free(temp);
        list->_size--;
    }
}

int list_front(List *list) {
    if (!list_isEmpty(list)) {
        return list->_head->data;
    }
    return 0;
}

int list_back(List *list) {
    if (!list_isEmpty(list)) {
        ListNode *temp = list->_head;
        while (temp->next != NULL)
            temp = temp->next;
        return temp->data;
    }
    return 0;
}

int list_getAt(List *list, int index) {
    if (!list_isEmpty(list)) {
        ListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index) {
            temp = temp->next;
            _i++;
        }
        return temp->data;
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    // Buat objek List
    List myList;

    // PENTING! Jangan lupa diinisialisasi
    list_init(&myList);

    // Gunakan operasi linked list
    list_pushBack(&myList, 1);
    list_pushBack(&myList, 2);
    list_pushBack(&myList, 3);
    list_pushBack(&myList, 4);

    list_pushFront(&myList, 10);
    list_pushFront(&myList, 9);
    list_pushFront(&myList, 8);
    list_pushFront(&myList, 7);

    list_popBack(&myList);
    list_popFront(&myList);

    // Isi List => [8, 9, 10, 1, 2, 3]

    list_removeAt(&myList, 3);

    list_insertAt(&myList, 1, 13);
    list_pushBack(&myList, 1);
    list_remove(&myList, 1);

    // Isi List => [8, 13, 9, 10, 2, 3]
    // printlist reversed
    while (myList._head != NULL) {
        printf("%d ", list_back(&myList));
        list_popBack(&myList);
    }
    puts("");
    return 0;
}