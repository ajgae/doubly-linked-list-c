#include "doubly-linked-list.h"

int main(void) {
  tests();
}

// Returns pointer to first node of list, or NULL on error. The caller
// should always update the value of the first node with this return
// value upon calling this function.
struct Node *insert_node(struct Node *first, int index, char *string) {
  struct Node *result;
  if (first == NULL || index < 0) {
    // bad arguments
    result = NULL; 
  }
 
  char *s = calloc(strlen(string) + 1, sizeof(char));
  strcpy(s, string);
  struct Node *new = malloc(sizeof(struct Node));
  new->string = s;
  
  if (index == 0) {
    // update new node
    new->prev = NULL;
    new->next = first;

    // update surrounding nodes (i.e. the then-first node)
    first->prev = new;

    // first node is now new
    result = new;
  } else {
    // find where to insert the new node. We have to get the node
    // before the one we are about to insert, because getting the one
    // after would result in errors when inserting at the end of the
    // list
    struct Node *node_prev = find_node_by_index(first, index - 1);

    // update new node
    new->prev = node_prev;
    new->next = node_prev->next;

    // update surrounding nodes
    node_prev->next = new;
    if (!is_last_node(new)) {
      new->next->prev = new;
    }

    // first node hasn't changed
    result = first;
  }
  
  return result;
}

// Deletes the node at index and deallocates it from memory. Returns
// pointer to first node of list, or NULL on error or if the list is
// now empty. The caller should always update the value of the first
// node with this return value upon calling this function.
struct Node *delete_node(struct Node *first, int index) {
  struct Node *result = NULL;
  if (first == NULL || index < 0) {
    // bad arguments
    result = NULL;
  } else if (index == 0) {
    if (is_last_node(first)) {
      free(first);
      // list now empty
      result = NULL;
    } else {
      // update 2nd node to now be first node
      first->next->prev = NULL;
      struct Node *new_first = first->next;
      free(first);
      result = new_first;
    }
  } else {
    struct Node *deleted = find_node_by_index(first, index);
    if (deleted != NULL) {
      // update surrounding nodes
      deleted->prev->next = deleted->next;
      if (!is_last_node(deleted)) {
        deleted->next->prev = deleted->prev;
      }
      free(deleted);
    }
    result = first;
  }
  return result;
}

// Returns a pointer to the node at index, or NULL on error or if the
// index is out of bounds.
struct Node *find_node_by_index(struct Node *first, int index) {
  struct Node *result;
  if (first == NULL || index < 0) {
    // bad arguments
    result = NULL;
  } else if (index == 0) {
    // trivial
    result = first;
  } else {
    struct Node *n = first;
    int i = 0;
    while(i < index && n->next != NULL) {
      i += 1;
      n = n->next;
    }

    if (i < index) {
      // i is greater than list length -> error
      result = NULL;
    } else {
      // node was found
      result = n;
    }
  }
  return result;
}

struct Node *find_node_by_string(struct Node *first, char *string) {
  // TODO
  return NULL;
}

struct Node *make_first_node(char *string) {
  char *s = calloc(strlen(string) + 1, sizeof(char));
  strcpy(s, string);
  struct Node *first = malloc(sizeof(struct Node));
  first->prev = NULL;
  first->next = NULL;
  first->string = s;
  return first;
}

int is_first_node(struct Node *node) { return node->prev == NULL; }
int is_last_node(struct Node *node) { return node->next == NULL; }

void tests(void) {
  printf("inserting three nodes, third first then second...\n\n");
  struct Node *first = make_first_node("first");
  first = insert_node(first, 1, "third");
  first = insert_node(first, 1, "second");
  printf("%s\n", find_node_by_index(first, 0)->string);
  printf("%s\n", find_node_by_index(first, 1)->string);
  printf("%s\n", find_node_by_index(first, 2)->string);

  printf("\ndeleting node at index 1...\n\n");
  first = delete_node(first, 1);
  printf("%s\n", find_node_by_index(first, 0)->string);
  printf("%s\n", find_node_by_index(first, 1)->string);

  printf("\ndeleting node at index 1...\n\n");
  first = delete_node(first, 1);
  printf("%s\n", find_node_by_index(first, 0)->string);

  printf("\ninserting node at index 0...\n\n");
  first = insert_node(first, 0, "new first");
  printf("%s\n", find_node_by_index(first, 0)->string);
  printf("%s\n", find_node_by_index(first, 1)->string);

  printf("\ndeleting node at index 0...\n\n");
  first = delete_node(first, 0);
  printf("%s\n", find_node_by_index(first, 0)->string);

  printf("\ninserting three nodes, in order this time...\n\n");
  first = insert_node(first, 1, "second");
  first = insert_node(first, 2, "third");
  printf("%s\n", find_node_by_index(first, 0)->string);
  printf("%s\n", find_node_by_index(first, 1)->string);
  printf("%s\n", find_node_by_index(first, 2)->string);

  printf("\ndeleting last node...\n\n");
  first = delete_node(first, 2);
  printf("%s\n", find_node_by_index(first, 0)->string);
  printf("%s\n", find_node_by_index(first, 1)->string);
}
