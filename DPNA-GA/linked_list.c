#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* next;
    float value;
}node_t;

typedef struct{;
    struct node* head;
    struct node* tail;
    int count ;

} linked_list;

void create_linked_list(linked_list* list, float value);
void show_linked_list_values(linked_list list);

int main(){
    printf("linked list\n");
    linked_list list;
    create_linked_list(&list, 10.48);
    show_linked_list_values(list);

    return 0;
}

void create_linked_list(linked_list* list, float value){
    node_t head;
    head.value = value;
    head.next = NULL;

    list->head = &head;
    list->count = 1;
}

void add(linked_list* list, float value){
  node_t new_node;
  new_node.value = value;
  new_node.next = NULL;

  list->tail->next = &new_node;
  list->tail = &new_node;
}

void show_linked_list_values(linked_list list){
    node_t current_node = *list.head;
    printf("%f\n",current_node.value);
}
