
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
  int value;
  struct list *next;
} slist;

void slist_append(slist **head, int value)
{
  slist *node = (slist *) malloc(sizeof(slist));
  node->value = value;
  node->next = NULL;
  if (*head == NULL) {
    *head = node;
  } else {
    slist *p = *head;
    while (p->next != NULL)
      p = p->next;
      p->next = node;
  }
}

void slist_free(slist **head)
{
  slist *p = *head;
  slist *q;
  while (p != NULL) {
    q = p;
    p = p->next;
    free(q);
  }
}
void slist_display(slist *head)
{
  slist *p = head;
  while (p != NULL) {
    printf("%d ", p->value);
    p = p->next;
  }
  printf("\n");
}

void slist_remove(slist **head, int x)
{
  slist *remv = *head;
  slist *p = *head; 
  if(p->value == x){
    *head = p->next;
    free(p);
  }else{
    while(p != NULL){
      if(p->value == x){
        remv->next = p->next;
        free(p);
        break;
      }
      remv = p;
      p = p->next;
    }
  }
}

int main(void)
{
  slist *head = NULL;
  slist_append(&head, 1);
  slist_append(&head, 2);
  slist_append(&head, 3);
  slist_append(&head, 4);
  slist_append(&head, 5);
  slist_display(head);

  slist_remove(&head, 3);
  slist_display(head);
  slist_remove(&head, 5);
  slist_display(head);
  slist_remove(&head, 1);
  slist_display(head);

  slist_free(&head);
}
