#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "lib.h"

int login(char email[50], char password[50], User * usr){

  int usrFound = 0;
  if (usr == NULL) {
    printf("Erro na alocação de memória.\n");
    return 1;
  }
  FILE *users;
  // lê o txt e armazena em users
  users = fopen("Register.txt", "r");

  //printf("\nRegister.txt aberto\n");
  // lê users
  while (fscanf(users, "%[^,],%[^,],%[^,],%[^,],%s\n", usr->name, usr->email, usr->password, usr->cpf, usr->role) == 5) {

    // printf("\n\n%s e %s\n\n", usr -> name, usr -> password);
    if (strcmp(email, usr->email) == 0) {
      usrFound = 1;
      
      if(strcmp(password, usr->password) == 0) {
        fclose(users);
        return 1;
      } else {
        printf("Senha incorreta!");
      }
    }
  }
  // caso o usuário não tenha sido encontrado
  if(!usrFound) printf("\nUsuario nao encontrado!\n");
  //printf("\nRegister.txt fechado\n");
  fclose(users);
  return 0;
}

void storeRegister(User* usr) {
  FILE* Register = fopen("Register.txt", "a");
  if (Register == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return;
  }

  // escreve usuário no txt
  fprintf(Register, "%s,%s,%s,%s,%s\n", usr->name, usr->email, usr->password, usr->cpf, usr->role);

  printf("Usuário cadastrado com sucesso!\n");

  fclose(Register);
}

void freeProfile(User* usr) {
  free(usr->name);
  free(usr->email);
  free(usr->password);
  free(usr->cpf);
  free(usr->role);
  free(usr);
  }

  User * createProfile(char *name, char *email, char *password, char *cpf, char *role) {
    User * usr = malloc(sizeof(User));
    if (usr == NULL) {
      printf("Erro ao tentar criar um novo perfil.\n");
      return NULL;
    }

    usr->name = malloc(strlen(name) + 1);
    strncpy(usr->name, name, strlen(name) + 1);

    usr->email = malloc(strlen(email) + 1);
    strncpy(usr->email, email, strlen(email) + 1);

    usr->password = malloc(strlen(password) + 1);
    strncpy(usr->password, password, strlen(password) + 1);

    usr->cpf = malloc(strlen(cpf) + 1);
    strncpy(usr->cpf, cpf, strlen(cpf) + 1);

    usr->role = malloc(strlen(role) + 1);
    strncpy(usr->role, role, strlen(role) + 1);

    return usr;
  }

void list(char * role) {

  FILE *users;
  User * usr = malloc(sizeof(User));
  usr->name = malloc(51 * sizeof(char));
  usr->email = malloc(51 * sizeof(char));
  usr->password = malloc(51 * sizeof(char));
  usr->cpf = malloc(12 * sizeof(char));
  usr->role = malloc(51 * sizeof(char));

  // lê o txt e armazena em users
  users = fopen("Register.txt", "r");

  while (fscanf(users, "%[^,],%[^,],%[^,],%[^,],%s\n", usr->name, usr->email, usr->password, usr->cpf, usr->role) == 5) {
    if(!strcmp(usr->role, role) && !strcmp(role, "residente")) {
      printf("\n\nNome do residente: %s\n", usr->name);
      printf("Email do residente: %s\n", usr->email);
      printf("CPF do residente: %s\n", usr->cpf);
      printf("----------------------------------------------------------------------------------");

    } else if(!strcmp(usr->role, role) && !strcmp(role, "preceptor")) {
      printf("\n\nNome do preceptor: %s\n", usr->name);
      printf("Email do preceptor: %s\n", usr->email);
      printf("CPF do preceptor: %s\n", usr->cpf);
      printf("----------------------------------------------------------------------------------");
    }
  }
  fclose(users);
  return;
}