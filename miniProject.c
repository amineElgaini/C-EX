#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct livre {
  char name[100];
  int quantity;
  bool exist;
};
void printLivres(struct livre livres[],int size);
void searchLivre(struct livre livres[],int size, char name[]);
void deleteLivre(struct livre livres[],int size, char name[]);
void updateLivre(struct livre livres[],int size, int index, struct livre updatedLivre);
void totalLivres(struct livre livres[],int size);

int main() {
  struct livre livres[10] = {{"test", 1, 1}}; // default values '\0' and 0

  int size=sizeof(livres)/sizeof(livres[0]);
  printLivres(livres, size);
  searchLivre(livres, size, "test");
  struct livre updatedLivre = {"test1", 1, true};
  updateLivre(livres, size, 0, updatedLivre);
  printLivres(livres, size);
  deleteLivre(livres, size, "test1");
  totalLivres(livres, size);
  // addLivre(livres, size, "test");
  return 0;
}

void printLivres(struct livre livres[],int size) {
  for (int i = 0; i<size; i++) {
    if (livres[i].exist)
      printf("livre numero: %d\n-name: %s\n-quantity: %d\n\n",i+1, livres[i].name, livres[i].quantity);
  }
}

void searchLivre(struct livre livres[], int size, char name[]) {
  for (int i = 0; i<size; i++) {
    if (strcmp(livres[i].name, name) == 0) {
      printf("livre numero: %d\n-name: %s\n-quantity: %d\n\n",i+1, livres[i].name, livres[i].quantity);
    }
  }
}

void deleteLivre(struct livre livres[], int size, char name[]) {
  for (int i = 0; i<size; i++) {
    if (strcmp(livres[i].name, name) == 0) {
      livres[i].exist = 0;
    }
  }
}

void updateLivre(struct livre livres[], int size, int index,  struct livre updatedLivre) {
  livres[index] = updatedLivre;
}

void totalLivres(struct livre livres[],int size) {
  int total = 0;
  for (int i = 0; i<size; i++) {
    if (livres[i].exist)
      total++;
  }
  printf("Total: %d\n", total);
}

