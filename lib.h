#ifndef __LIB__
#define __LIB__

typedef struct User{
  char * name;
  char * email;
  char * password;
  char * cpf;
  char * role; // residente, preceptor, gestor
}User;

void list(char * role);

// função para realizar login - retorna 1 se login OK, retorna 0 se erro
int login(char name[50], char password[50], User * usr);

//insere um novo "usuário"
User * createProfile(char *name, char *email, char *password, char *cpf, char *role);

//libera a memoria do ponteiro e libera da senha pq strdup() duplica a string
void freeProfile(User* usr);

//salva o usuário no arquivo
void storeRegister(User* usr);
#endif //__LIB.H__

