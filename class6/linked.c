#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    struct node *prev;
    struct node *next;
    int value;
} node_t;

typedef struct list {
    node_t *start;
    node_t *end;
} list_t;

list_t *list_create(void) {
  list_t *list = malloc(sizeof(*list));
  list->start = malloc(sizeof(*(list->start)));
  list->end = malloc(sizeof(*(list->end)));
  list->start->prev = NULL;
  list->start->next = list->end;
  list->end->prev = list->start;
  list->end->next = NULL;
  return list;
}

void list_push_start(list_t *list, int value) {
  node_t *node = malloc(sizeof(*node));
  node->value = value;
  node->prev = list->start;
  node->next = list->start->next;
  list->start->next->prev = node;
  list->start->next = node;
}

void list_push_end(list_t *list, int value) {
  node_t *node = malloc(sizeof(*node));
  node->value = value;
  node->next = list->end;
  node->prev = list->end->prev;
  list->end->prev->next = node;
  list->end->prev = node;
}

int list_pop_start(list_t *list) {
  if(list->start->next != list->end) {
    node_t *pop = list->start->next;
    list->start->next = list->start->next->next;
    list->start->next->prev = list->start;
    pop->next = NULL;
    pop->prev = NULL;
    int value = pop->value;
    free(pop);
    return value;
  }
}

int list_pop_end(list_t *list) {
  if (list->end->prev != list->start) {
    node_t *pop = list->end->prev;
    list->end->prev = list->end->prev->prev;
    list->end->prev->next = list->end;
    pop->next = NULL;
    pop->prev = NULL;
    int value = pop->value;
    free(pop);
    return value;
  }
}

void list_destroy(list_t *list) {
  while(list->start->next->next != NULL) {
    int t = list_pop_start(list);
  }
  free(list->start);
  free(list->end);
  free(list);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "could not open %s: ", argv[1]);
        perror("");
        return 1;
    }

    list_t *list = list_create();

    while (!feof(f)) {
        char command[16];
        int res = fscanf(f, "%10s", command);
        if (res != 1) {
            if (!feof(f)) {
                fprintf(stderr, "trouble parsing command. stopping.\n");
            }
            break;
        }

        if (strcmp("push_start", command) == 0) {
            int value = 0;
            res = fscanf(f, "%d", &value);
            if (res != 1) {
                fprintf(stderr, "trouble parsing value. stopping.\n");
                break;
            }

            list_push_start(list, value);
        } else if (strcmp("push_end", command) == 0) {
            int value = 0;
            res = fscanf(f, "%d", &value);
            if (res != 1) {
                fprintf(stderr, "trouble parsing value. stopping.\n");
                break;
            }

            list_push_end(list, value);
        } else if (strcmp("pop_start", command) == 0) {
            int v = list_pop_start(list);
            printf("%d\n", v);
        } else if (strcmp("pop_end", command) == 0) {
            int v = list_pop_end(list);
            printf("%d\n", v);
        } else {
            fprintf(stderr, "did not recognize command '%s'. stopping.\n", command);
            break;
        }
    }

    list_destroy(list);

    fclose(f);

    return 0;
}
