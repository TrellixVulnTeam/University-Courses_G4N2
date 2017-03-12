#include "repository.h"
#include <stdlib.h>
#include <assert.h>
OfferRepo *create_repo() {

	OfferRepo *r = (OfferRepo*)malloc(sizeof(OfferRepo));
	r->n = 0;
	return r;
}

void free_repo(OfferRepo *r) {
	
	int i;
	for (i = 0; i < r->n; i++)
		free_offer(r->vec[i]);

	free(r);
}

int find_offer(OfferRepo *r, char *dest, int d1, int m1, int y1) {
	
	int i;
	for (i = 0; i < r->n; i++)
		if (strcmp(r->vec[i]->destination, dest) == 0)
			if (r->vec[i]->day == d1)
				if (r->vec[i]->mounth == m1)
					if (r->vec[i]->year == y1)
						return i;
	return -1;
}

int update_offer_repo(OfferRepo *r, char *dest1, int d1, int m1, int y1, char *type2, char *dest2, int d2, int m2, int y2, int p2) {
	
	int idx = find_offer(r, dest1, d1, m1, y1);
	if (idx == -1)
		return 0;

	update_offer(r->vec[idx], type2, dest2, d2, m2, y2, p2);
	return 1;

}

int add_offer(OfferRepo *r, Offer *x) {
	
	if (find_offer(r, x->destination, x->day, x->mounth, x->year) != -1)
		return 0;
	
	r->vec[r->n] = x;
	r->n++;
	return 1;
}


int delete_offer(OfferRepo *r, char *dest, int d, int m, int y) {
	
	int poz = find_offer(r, dest, d, m, y);
	if (poz == -1)
		return 0;
	
	Offer *aux = r->vec[r->n - 1];
	r->vec[r->n - 1] = r->vec[poz];
	r->vec[poz] = aux;
	free_offer(r->vec[r->n - 1]);
	r->n--;

	return 1;
}

void print_repo(OfferRepo *r) {

	int i;
	for (i = 0; i < r->n; i++)
		print_offer(r->vec[i]);

}


void test_repo() {

	int idx;
	OfferRepo *r = create_repo();
	Offer *a = create_offer("Seaside", "Maldive", 11, 12, 2017, 825);
	Offer *b = create_offer("Mountain", "Cavnic", 12, 11, 2017, 350);
	Offer *c = create_offer("CityBreak", "London", 13, 10, 2017, 200);
	Offer *d = create_offer("Mountain", "Retezat", 14, 9, 2017, 250);

	add_offer(r, a);
	assert(r->n == 1);
	add_offer(r, b);
	assert(r->n == 2);
	add_offer(r, c);
	assert(r->n == 3);

	add_offer(r, c);
	assert(r->n == 3);
	add_offer(r, d);
	assert(r->n == 4);
	
	idx = find_offer(r, "Maldive", 11, 12, 2017, 825);
	assert(idx == 0);
	idx = find_offer(r, "Retezat", 14, 9, 2017, 250);
	assert(idx == 3);
	
	update_offer_repo(r, "Retezat", 14, 9, 2017, "Mountain", "Cluj", 1, 1, 1, 1);
	assert(strcmp(r->vec[3]->destination, "Cluj") == 0);
	assert(r->vec[3]->price == 1);
	assert(r->vec[3]->day == 1);
	assert(r->vec[3]->mounth == 1);
	assert(r->vec[3]->year == 1);
	
	delete_offer(r, "Maldive", 11, 12, 2017);
	assert(r->n == 3);
	delete_offer(r, "Maldive", 11, 12, 2017);
	assert(r->n == 3);
	delete_offer(r, "Cluj", 1, 1, 1, 1);
	assert(r->n == 2);
	
	free_repo(r);
}
