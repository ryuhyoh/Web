#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

// 연락처 구조체 정의
typedef struct Contact {
    char name[100];
    char phone[20];
} Contact;

// 이진 트리 노드 구조체 정의
typedef struct TreeNode {
    Contact contact;
    struct TreeNode *left, *right;
} TreeNode;

// 이진 트리 노드 생성 함수
TreeNode* createNode(Contact contact) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->contact = contact;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 이진 트리에 노드 삽입 함수
TreeNode* insertNode(TreeNode* root, Contact contact) {
    if (root == NULL) return createNode(contact);
    if (strcmp(contact.name, root->contact.name) < 0)
        root->left = insertNode(root->left, contact);
    else if (strcmp(contact.name, root->contact.name) > 0)
        root->right = insertNode(root->right, contact);
    return root;
}

// 해시 테이블 크기 정의
#define TABLE_SIZE 100

// 해시 테이블 구조체 정의
typedef struct HashTable {
    Contact *table[TABLE_SIZE];
} HashTable;

// 해시 함수 정의
int hashFunction(char *name) {
    int hash = 0;
    while (*name) hash = (hash + *name++) % TABLE_SIZE;
    return hash;
}

// 해시 테이블에 연락처 삽입 함수
void insertHashTable(HashTable* ht, Contact contact) {
    int index = hashFunction(contact.name);
    while (ht->table[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
    }
    ht->table[index] = (Contact*)malloc(sizeof(Contact));
    *(ht->table[index]) = contact;
}

// 해시 테이블에서 연락처 검색 함수
Contact* searchHashTable(HashTable* ht, char *name) {
    int index = hashFunction(name);
    while (ht->table[index] != NULL) {
        if (strcmp(ht->table[index]->name, name) == 0)
            return ht->table[index];
        index = (index + 1) % TABLE_SIZE;
    }
    return NULL;
}

// 이진 트리 중위 순회 함수 (정렬된 출력)
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Name: %s, Phone: %s\n", root->contact.name, root->contact.phone);
        inorderTraversal(root->right);
    }
}

// 메인 함수
int main() {
    TreeNode *root = NULL;
    HashTable ht;
    memset(&ht, 0, sizeof(HashTable));

    // 예시 연락처 정의
    Contact contact1 = {"Alice", "123-456-7890"};
    Contact contact2 = {"Bob", "987-654-3210"};
    Contact contact3 = {"Charlie", "555-555-5555"};

    // 연락처를 이진 트리에 삽입
    root = insertNode(root, contact1);
    root = insertNode(root, contact2);
    root = insertNode(root, contact3);

    // 연락처를 해시 테이블에 삽입
    insertHashTable(&ht, contact1);
    insertHashTable(&ht, contact2);
    insertHashTable(&ht, contact3);

    // 정렬된 연락처 출력
    printf("Sorted Contacts:\n");
    inorderTraversal(root);

    // 연락처 검색
    char searchName[100];
    printf("\nEnter name to search: ");
    scanf("%s", searchName);
    Contact *found = searchHashTable(&ht, searchName);
    if (found != NULL) {
        printf("Found: Name: %s, Phone: %s\n", found->name, found->phone);
    } else {
        printf("Contact not found\n");
    }

    return 0;
}