#include "stdio.h"  
#include "stdlib.h"  
  
#define OK 1  
#define ERROR 0  
#define TRUE 1  
#define FALSE 0  
  
typedef int Status;  
typedef int ElemType;  
  
typedef struct Node{  
    ElemType data;  
    struct Node* next;  
}Node;  
  
Status initList(Node** L){  
      
    *L = (Node*)malloc(sizeof(Node));  
    if(!(*L)){  
        return ERROR;  
    }  
      
    (*L)->next = NULL;  
    return OK;  
}  
  
  
int listLength(Node* L){  
      
    int i = 0;  
    Node* p = L->next;  
    while(p){  
        i++;  
        p = p->next;  
    }  
    return i;  
}  
  
// Non-Chain  
void createListHead(Node** L, int n){  
      
    Node* p;  
    int i;  
      
    srand(time(0));  
      
    *L = (Node*)malloc(sizeof(Node));  
    (*L)->next = NULL;  
      
    for(i=0; i<n; i++){  
        p = (Node*)malloc(sizeof(Node));  
        // p->data = rand()%100+1;  
        p->data = i+1;  
        p->next = (*L)->next;  
        (*L)->next = p;  
    }  
}  
  
// Chain  
void createListTail(Node** L, int n){  
      
    Node* p, *r;  
    int i;  
      
    srand(time(0));  
    *L = (Node*)malloc(sizeof(Node));  
    r = *L;  
      
    for(i=0; i<n; i++){  
        p = (Node*)malloc(sizeof(Node));  
        // p->data = rand()%100+1;  
        p->data = i+1;  
        r->next = p;  
        r = p;  
    }  
      
    // 把尾节点与第二个节点连接起来  
    r->next = (*L)->next->next;  
}  
  
// 用两个指针cur1，cur2， cur1每次前进一个pos，cur2每次重头前进直到和cur1指向相同的节点，  
// 再比较两者经过的步数是否相等  
int hasLoop1(Node* L){  
      
    Node* cur1 = L;  
    int pos1 = 0;  
      
    while(cur1){  
        Node* cur2 = L;  
        int pos2 = 0;  
        while(cur2){  
            if(cur2 == cur1){  
                if(pos1 == pos2){  
                    break;  
                }  
                else{  
                    printf("Chain is in the %d place\n\n", pos2);  
                    return 1;  
                }  
            }  
            cur2 = cur2->next;  
            pos2++;  
        }  
        cur1 = cur1->next;  
        pos1++;  
    }  
      
    return 0;  
}  
  
// 快慢指针，如果相等则说明有环  
int hasLoop2(Node* L){  
      
    int step1 = 1;  
    int step2 = 2;  
    Node* p = L;  
    Node* q = L;  
      
    while(p!=NULL && q!=NULL && q->next!=NULL){  
        p = p->next;  
        q = q->next->next;  
          
        printf("p:%d, q:%d \n", p->data, q->data);  
          
        // 找到相碰点  
        if(p == q){  
            return 1;  
        }  
    }  
      
    return 0;  
}  
  
// 寻找环连接点（入口点）  
Node* findLoopEntry(Node* L){  
      
    Node* slow = L, *fast=L;  
      
    while(fast && slow && fast->next){  
        slow = slow->next;  
        fast = fast->next->next;  
          
        // 找到相碰点  
        if(slow == fast){  
            printf("Collision point value is %d\n", slow->data);  
            break;  
        }  
    }  
      
    if(fast==NULL || fast->next==NULL){  
        return NULL;  
    }  
      
    // 碰撞点p到连接点的距离=头指针到连接点的距离  
    slow = L;  
    while(slow != fast){  
        slow = slow->next;  
        fast = fast->next;  
    }  
      
    return slow;  
}  
  
  
  
int main(){  
      
    Node* L;  
    Status i;  
    char opp;  
    ElemType e;  
    int find;  
    int tmp;  
      
    i = initList(&L);  
    printf("After initialization, listLength(L)=%d\n", listLength(L));  
      
    printf("\n1.Create Chain Linked list(Tail Insert) \n2.Create Non-Chain Linked List(Head Insert) \n3.Judge if a chain exists \n0.Exit\n\n");  
      
    while(opp != '0'){  
        scanf("%c", &opp);  
        switch(opp){  
            case '1':  
                createListTail(&L, 10);  
                printf("Create Chain LinkedList L(Tail Insert) OK\n");  
                printf("\n");  
                break;  
              
            case '2':  
                createListHead(&L, 10);  
                printf("Create Non-Chain Linked List(Head Insert) OK\n");  
                printf("\n");  
                break;  
                  
            case '3':  
                printf("Solution 1: \n\n");  
                if(hasLoop1(L)){  
                    printf("Summary: Chain exists\n\n");  
                }  
                else{  
                    printf("Summary: No Chain\n\n");  
                }  
                  
                printf("---------------------------\n\n");  
                  
                printf("Solution 2: \n\n");  
                if(hasLoop2(L)){  
                    printf("Summary: Chain exists\n\n");  
                    Node* entry = findLoopEntry(L);  
                    printf("Entry value is: %d\n", entry->data);  
                }  
                else{  
                    printf("Summary: No Chain\n\n");  
                }  
        }  
    }  
} 