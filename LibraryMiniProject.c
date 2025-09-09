#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void cleanBuffer() {
  while (getchar() != '\n');
}

struct livre {
  char name[100];
  int quantity;
  bool exist;
};

enum MenuOption {
    READ = 1,
    SEARCH,
    DELETE,
    UPDATE,
    ADD,
    TOTAL,
    EXIT
};

int size = 0;

void totalLivres(struct livre livres[]);
void printLivres(struct livre livres[]);
void searchLivre(struct livre livres[]);
void addLivre(struct livre livres[]);
void updateLivre(struct livre livres[]);
void deleteLivre(struct livre livres[]);

int main() {
  struct livre *livres = calloc(1, sizeof(struct livre));
  int choice;
  bool exit = false;

  while (!exit) {
    printf("Choose an option:\n");
    printf("1. Read all livres\n");
    printf("2. Search a livre\n");
    printf("3. Delete a livre\n");
    printf("4. Update a livre\n");
    printf("5. Add a livre\n");
    printf("6. Total livres\n");
    printf("7. EXIT\n");
    printf("Enter your choice (1-7): ");
    scanf("%d", &choice);
    cleanBuffer();


    switch (choice) {
          case READ:
              printLivres(livres);
              break;
          case SEARCH:
              searchLivre(livres);
              break;
          case DELETE:
              deleteLivre(livres);
              break;
          case UPDATE:
              updateLivre(livres);
              break;
          case ADD:
              addLivre(livres);
              break;
          case TOTAL:
              totalLivres(livres);
              break;
          case EXIT:
              exit = true;
              break;
          default:
              printf("Invalid choice\n");
      }
    };

  return 0;
}

void totalLivres(struct livre livres[]) {
  int total = 0;
  for (int i = 0; i<size; i++) {
    if (livres[i].exist)
      total++;
  }
  printf("Total: %d\n", total);
}

void printLivres(struct livre livres[]) {
  for (int i = 0; i<size; i++) {
    if (livres[i].exist)
      printf("livre numero: %d\n-name: %s\n-quantity: %d\n\n",i+1, livres[i].name, livres[i].quantity);
  }
}

void searchLivre(struct livre livres[]) {
  char name[100];

  printf("Enter the name to search: ");
  fgets(name, sizeof(name), stdin);
  if (name[strlen(name) - 1] == '\n') {
      name[strlen(name) - 1] = '\0';
  }

  for (int i = 0; i<size; i++) {
    if (strcmp(livres[i].name, name) == 0 && livres[i].exist==1) {
      printf("livre numero: %d\n-name: %s\n-quantity: %d\n\n",i+1, livres[i].name, livres[i].quantity);
    }
  }
}

void deleteLivre(struct livre livres[]) {
  char name[100];

  printf("Enter the name to delete: ");
  fgets(name, sizeof(name), stdin);
  if (name[strlen(name) - 1] == '\n') {
    name[strlen(name) - 1] = '\0';
  }

  // cleanBuffer();

  for (int i = 0; i<size; i++) {
    if (strcmp(livres[i].name, name) == 0) {
      livres[i].exist = 0;
    }
  }
}

void addLivre(struct livre livres[]) {
  struct livre livre;
  printf("name: ");
  fgets(livre.name, sizeof(livre.name), stdin);
  if (livre.name[strlen(livre.name) - 1] == '\n') {
    livre.name[strlen(livre.name) - 1] = '\0';
  }

  printf("quantity: ");
  scanf("%d", &livre.quantity);
  cleanBuffer();

  livre.exist = 1;

  
  livres = realloc(livres, (size+1) * sizeof(struct livre));
  livres[size] = livre;
  size++;
  
}

int findLivreIndexByName(struct livre livres[], char name[]) {
    for (int i = 0; i <= size; i++) {
        if (strcmp(livres[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void updateLivre(struct livre livres[]) {
  char name[100];
  printf("Enter the name to update: ");
  fgets(name, sizeof(name), stdin);
  if (name[strlen(name) - 1] == '\n') {
    name[strlen(name) - 1] = '\0'; 
  }

  int index = findLivreIndexByName(livres, name);
  if (index == -1) {
      printf("Livre not found!\n");
      return;
  }

  printf("Name: ");
  fgets(livres[index].name, sizeof(livres[index].name), stdin);

  if (livres[index].name[strlen(livres[index].name) - 1] == '\n') {
    livres[index].name[strlen(livres[index].name) - 1] = '\0';
  }

  printf("Quantity: ");
  scanf("%d", &livres[index].quantity);
  cleanBuffer();
}

