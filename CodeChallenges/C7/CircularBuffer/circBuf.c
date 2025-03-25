#include <stdio.h>
#include <stdlib.h>

struct circular_buffer_t
{
    void* data;
    struct circular_buffer_t* next;
};

typedef struct circular_buffer_t circular_buffer_t;

// Create a circular buffer with a size of n
circular_buffer_t* circular_buffer_create(int n)
{
    if(n < 2)
    {
        printf("N < 2. Exiting...\n");
        exit(-1);
    }

    // Get the "head"
    circular_buffer_t* head = (circular_buffer_t*)malloc(sizeof(circular_buffer_t));

    // Check for malloc failure
    if(!head)
    {
        return NULL;
    }

    circular_buffer_t* prevNode = head;
    // Create additional nodes, starting at 1 because we already made head
    for(int i = 1; i < n; i++)
    {
        circular_buffer_t* newNode = (circular_buffer_t*)malloc(sizeof(circular_buffer_t));
        if(!newNode)
        {
            printf("Failed to malloc!\n");
            exit(-1);
        }

        // Assign default values
        newNode -> data = NULL;
        newNode -> next = NULL;

        // Connect
        prevNode -> next = newNode;
        prevNode = newNode;
    }

    // Complete the loop
    prevNode -> next = head;

    return head;
}

void print_circular_buffer(circular_buffer_t* head)
{
    if(head == NULL)
    {
        printf("head is null\n");
        return;
    }
    
    circular_buffer_t* p = head;

    do
    {
        if(p -> data)
        {
            printf("%i\n", *(int*)(p -> data));
        }

        else
        {
            printf("NULL\n");
        }
        
        p = p -> next;
    } while (p != head);
}

void circular_buffer_enqueue(circular_buffer_t** head, void* data)
{
    if(head == NULL || (*head) == NULL)
    {
        printf("Empty buffer!\n");
        return;
    }

    circular_buffer_t* p = *head;

    // Find first open slot and insert
    do
    {
        if(!(p -> data))
        {
            p -> data = data;
            return;
        }
        
        p = p -> next;
    } while (p != *head);

    // Went through whole list, meaning the thing is full
    // head should always be oldest, then head -> next
    (*head) -> data = data;
    (*head) = (*head) -> next;
}

int circular_buffer_dequeue(circular_buffer_t** head, void** retrieved)
{
    if(head == NULL || (*head) == NULL)
    {
        printf("Empty buffer!\n");
        return 0;
    }

    *retrieved = (*head) -> data;
    (*head) -> data = NULL;

    return 1;
}

int circular_buffer_is_empty(circular_buffer_t* head)
{
    if(head == NULL)
    {
        printf("head is null\n");
        return -1;
    }

    circular_buffer_t* p = head;

    do
    {
        if(p -> data)
        {
            return 0;
        }
        p = p -> next;
    } while (p != head);

    return 1;
}

int circular_buffer_is_full(circular_buffer_t* head)
{
    if(head == NULL)
    {
        printf("head is null\n");
        return -1;
    }

    circular_buffer_t* p = head;

    do
    {
        if(!(p -> data))
        {
            return 0;
        }
        p = p -> next;
    } while (p != head);

    return 1;
}

void circular_buffer_destroy(circular_buffer_t** head)
{
    if(head == NULL || *head == NULL)
    {
        printf("head is null\n");
        return;
    }

    circular_buffer_t* p = (*head) -> next;

    do
    {
        circular_buffer_t* n = p -> next;
        p -> next = NULL;
        free(p);
        p = n;
    } while (p != (*head));

    p -> next = NULL;
    free(p);
}

int main()
{
    circular_buffer_t* bufHead = circular_buffer_create(5);
    if(!bufHead)
    {
        printf("Failed to make new buffer\n");
        exit(-1);
    }
    
    int data[6] = {10, 20, 30, 40, 50, 60};

    for(int i = 0; i < 6; i++)
    {
        circular_buffer_enqueue(&bufHead, (void*)(&(data[i])));
    }
    print_circular_buffer(bufHead);

    void* received;
    if(circular_buffer_dequeue(&bufHead, &received))
    {
        printf("Retreived %i\n", *(int*)received);
    }

    circular_buffer_destroy(&bufHead);
}

