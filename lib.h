#ifndef __LIB__
#define __LIB__

typedef struct User {
  char *name;
  char *email;
  char *password;
  char *cpf;
  char *role; // residente, preceptor, gestor
} User;

void list(char *role);

// função para realizar login - retorna 1 se login OK, retorna 0 se erro
int login(char name[50], char password[50], User *usr);

// insere um novo "usuário"
User *createUser(char *newName, char *newEmail, char *newPassword, char *newCpf,
                 char *newRole);

void removeProfile(const char *name, const char *email);

// libera a memoria do ponteiro do usuario atual
void freeUser(User *usr);
// libera a memoria do ponteiro do novo usuario
void freeNewUser(User *newUser);

// salva o usuário no arquivo
void storeRegister(User *newUser);

#endif //__LIB.H__
