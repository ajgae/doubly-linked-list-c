#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  struct Node *prev;
  struct Node *next;
  char* string;
};

void tests(void);
struct Node *insert_node(struct Node *first, int index, char *string);
struct Node *delete_node(struct Node *first, int index);
struct Node *find_node_by_index(struct Node *first, int index);
struct Node *find_node_by_string(struct Node *first, char *string);
int is_first_node(struct Node *node);
int is_last_node(struct Node *node);
