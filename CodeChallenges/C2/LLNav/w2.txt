#include <stdio.h>
#include <stdlib.h>

// Def for singly linked list


struct Node
{
   int data;
   struct Node* next;
};

typedef struct Node Node;

Node* RemoveDuplicates(Node* head)
{
   Node* prev = head;
   Node* cur = head -> next;

   while(cur != NULL)
   {
      if(prev -> data == cur -> data)
      {
         // Jump the node
         prev -> next = cur -> next;

         // Break link
         cur -> next = NULL;

         // Free
         free(cur);

         cur = prev -> next;
      }

      else
      {
         prev = cur;
         cur = cur -> next;
      }
   }
   
   return head;
}

int main()
{
   Node* head = (Node*)malloc(sizeof(Node)); // Now requires separate initialization
   head->data = 1;
   head->next = (Node*)malloc(sizeof(Node));
   head->next->data = 2;
   head->next->next = (Node*)malloc(sizeof(Node));
   head->next->next->data = 2;
   head->next->next->next = (Node*)malloc(sizeof(Node));
   head->next->next->next->data = 3;
   head->next->next->next->next = (Node*)malloc(sizeof(Node));
   head->next->next->next->next->data = 3;
   head->next->next->next->next->next = NULL; // Explicitly set the last node's next to NULL

   head = RemoveDuplicates(head);

   // Print modified list
   Node* cur = head;
   while(cur != NULL)
   {
      printf("%i ", cur -> data);
      cur = cur -> next;
   }

   printf("\n");
}
