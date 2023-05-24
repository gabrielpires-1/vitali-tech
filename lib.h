#ifndef __LIB__
#define __LIB__

typedef struct User {
  char *name;
  char *email;
  char *password;
  char *cpf;
  char *role; // residente, preceptor, gestor
  struct User *next;
} User;

// função para solicitar que o usuário tecle alguma tecla para continuar
void pause();

void list(char *role);

// função para realizar login - retorna 1 se login OK, retorna 0 se erro
int login(char name[50], char password[50], User *usr);

// insere um novo "usuário"
User *createUser(char *newName, char *newEmail, char *newPassword, char *newCpf, char *newRole);

void removeProfile(const char *name, const char *email);

// libera a memoria do ponteiro do usuario atual
void freeUser(User *usr);
// libera a memoria do ponteiro do novo usuario
void freeNewUser(User *newUser);

// salva o usuário no arquivo
void storeRegister(User *newUser);
void append(User** head, char name[], char email[], char password[], char cpf[], char role[]);

void create_list( User **head);
void deleteByName(User** head, char name[]);
#endif //__LIB.H__
