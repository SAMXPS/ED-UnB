#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char name[20];
	double price;
} item;

struct s_list {
	item e;
	struct s_list *next;
};
typedef struct s_list list;

int list_add(list **l, item e) {
	list *ne = malloc(sizeof(list));
	if (ne) {
		ne->next = *l;
		ne->e = e;
		*l = ne;
		return 1;
	}
	return 0;
}

int list_remove(list **l, char* busc) {
	if (*l) {
		if (strcmp(busc, (*l)->e.name) == 0) {
			list *aux = *l;
			(*l) = aux->next;
			free(aux);
			return 1;
		} else return list_remove(&((*l)->next), busc);
	}
	return 0;
}

int main () {
	item aux;
	list *list = NULL, *laux = NULL;
	int i = 0;
	double s = 0;

	/* SCAN PART */
	while (scanf("%s", aux.name) && strcmp(aux.name, "fim")) {
		if (strcmp(aux.name,  "-")) {
			scanf("%lf", &(aux.price));
			list_add(&list, aux);
		} else {
			scanf("%s", aux.name);
			list_remove(&list, aux.name);
		}
	}

	/* PROCESS&PRINT PART */

	while(list) {
		printf("%s %.2lf\n", list->e.name, list->e.price);
		s+= list->e.price;
		laux = list;
		list = list->next;
		free(laux);
		i++;
	}

	printf("----------------------\n");
	printf("%d item(ns): R$ %.2lf\n", i, s);

	return 0;
}