
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

int slist_display(slist *head)
{
  slist *p = head;
  while (p != NULL) {
    printf("%d ", p->value);
    p = p->next;
  }
  printf("\n");
}


int main(void)
{
  slist *head = NULL;
  slist_append(&head, 1);
  slist_append(&head, 3);
  slist_append(&head, 5);
  slist_append(&head, 3);
  slist_display(head);
  printf("3: %d¥n", slist_count(head, 3));
  printf("5: %d¥n", slist_count(head, 5));
  slist_free(&head);
}