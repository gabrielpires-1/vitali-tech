#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

// função para solicitar que o usuário tecle alguma tecla para continuar
void pause(){
  printf("\n\nPressione qualquer tecla para continuar...\n");
  getch();
}

User *createUser(char *newName, char *newEmail, char *newPassword, char *newCpf,
                 char *newRole) {
  User *newUser = malloc(sizeof(User));
  if (newUser == NULL) {
    printf("Erro ao tentar criar um novo perfil.\n");
    return NULL;
  }

  newUser->name = malloc(strlen(newName) + 1);
  strcpy(newUser->name, newName);

  newUser->email = malloc(strlen(newEmail) + 1);
  strcpy(newUser->email, newEmail);

  newUser->password = malloc(strlen(newPassword) + 1);
  strcpy(newUser->password, newPassword);

  newUser->cpf = malloc(strlen(newCpf) + 1);
  strcpy(newUser->cpf, newCpf);

  newUser->role = malloc(strlen(newRole) + 1);
  strcpy(newUser->role, newRole);

  return newUser;
}
void removeProfile(const char *name, const char *email) {
  FILE *users = fopen("Register.txt", "r");
  FILE *temp = fopen("temp.txt", "w");

  if (users == NULL || temp == NULL) {
    printf("Falha ao abrir arquivo.\n");
    return;
  }

  User *usr = malloc(sizeof(User));

  while (fscanf(users, "%m[^,],%m[^,],%m[^,],%m[^,],%ms\n", &usr->name,
                &usr->email, &usr->password, &usr->cpf, &usr->role) == 5) {
    if (strcmp(email, usr->email) == 0 && strcmp(name, usr->name) == 0) {
      printf("Perfil encontrado e removido:\n");
      printf("Nome: %s\n", usr->name);
      printf("Email: %s\n", usr->email);
      printf("Senha: %s\n", usr->password);
      printf("CPF: %s\n", usr->cpf);
      printf("Role: %s\n", usr->role);
    } else {
      fprintf(temp, "%s,%s,%s,%s,%s\n", usr->name, usr->email, usr->password,
              usr->cpf, usr->role);
    }
  }

  fclose(users);
  fclose(temp);
  remove("Register.txt");
  rename("temp.txt", "Register.txt");

  freeUser(usr);
}

int login(char email[50], char password[50], User *usr) {
  setlocale(LC_ALL, "Portuguese_Brazil");

  int usrFound = 0;
  if (usr == NULL) {
    printf("Erro na alocação de memória.\n");
    return 1;
  }
  FILE *users;
  // lê o txt e armazena em users
  users = fopen("Register.txt", "r");

  // printf("\nRegister.txt aberto\n");
  //  lê users e verifica se os 5 que foram lidos correspondem com os de entrada
  while (fscanf(users, "%[^,],%[^,],%[^,],%[^,],%s\n", usr->name, usr->email,
                usr->password, usr->cpf, usr->role) == 5) {

    // printf("\n\n%s e %s\n\n", usr -> name, usr -> password);
    if (strcmp(email, usr->email) == 0) {
      usrFound = 1;

      if (strcmp(password, usr->password) == 0) {
        fclose(users);
        return 1;
      } else {
        printf("\nSenha incorreta!\n");
      }
    }
  }
  // caso o usuário não tenha sido encontrado
  if (!usrFound)
    printf("\nUsuário não encontrado!\n");
  // printf("\nRegister.txt fechado\n");
  fclose(users);
  return 0;
}

void storeRegister(User *newUser) {
  FILE *Register = fopen("Register.txt", "a");
  if (Register == NULL) {
    printf("Falha ao abrir arquivo.\n");
    return;
  }

  fprintf(Register, "%s,%s,%s,%s,%s\n", newUser->name, newUser->email,
          newUser->password, newUser->cpf, newUser->role);

  fclose(Register);
}

void freeUser(User *usr) {
  free(usr->name);
  free(usr->email);
  free(usr->password);
  free(usr->cpf);
  free(usr->role);
  free(usr);
}

void freeNewUser(User *newUser) {
  free(newUser->name);
  free(newUser->email);
  free(newUser->password);
  free(newUser->cpf);
  free(newUser->role);
  free(newUser);
}

void list(char *role) {

  FILE *users;
  User *usr = malloc(sizeof(User));
  usr->name = malloc(51 * sizeof(char));
  usr->email = malloc(51 * sizeof(char));
  usr->password = malloc(51 * sizeof(char));
  usr->cpf = malloc(12 * sizeof(char));
  usr->role = malloc(51 * sizeof(char));

  // lê o txt e armazena em users
  users = fopen("Register.txt", "r");

  while (fscanf(users, "%[^,],%[^,],%[^,],%[^,],%s\n", usr->name, usr->email,
                usr->password, usr->cpf, usr->role) == 5) {
    if (!strcmp(usr->role, role) && !strcmp(role, "residente")) {
      printf("\n\nNome do residente: %s\n", usr->name);
      printf("Email do residente: %s\n", usr->email);
      printf("CPF do residente: %s\n", usr->cpf);

    } else if (!strcmp(usr->role, role) && !strcmp(role, "preceptor")) {
      printf("\n\nNome do preceptor: %s\n", usr->name);
      printf("Email do preceptor: %s\n", usr->email);
      printf("CPF do preceptor: %s\n", usr->cpf);
      printf("-----------------------------------------------------------------"
             "-----------------");
    }
  }
  fclose(users);
  return;
}
