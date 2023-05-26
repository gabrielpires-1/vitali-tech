#ifndef __LIB__
#define __LIB__

// estrutura do usuário
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

// cria um novo usuário do tipo User, retorna um ponteiro User para esse usuário
User *createUser(char *newName, char *newEmail, char *newPassword, char *newCpf, char *newRole);

// retorna 1 se o login funcionou, 0 se não
int login(char email[50], char password[50], User *usr);

// salva o User no arquivo txt
void storeRegister(User *newUser);

// libera a memória de um tipo User
void freeUser(User *usr);

// insere usuários no final da lista encadeada
void append(User** head, char name[], char email[], char password[], char cpf[], char role[]);

// cria a lista a partir de um head, de acordo com o que tem no txt
void create_list( User **head);

// recene a head da lista e uma string que representa o nome do usuário
// deleta o usuáiro da lista encadeada
// deve-se lembrar de utilizar a função 'save_list()' para salvar a nova lista no txt
void deleteByName(User** head, char name[]);

// recebe a head da lista e uma string que representa o cargo 
// imprime os elementos da lista filtrando pelo cargo
void printList(User *head, char role[]);

// recebe a head da lista e salva a lista atual no arquivo txt
void saveList(User **head);

//Confere o nome do residente no user
void lookingResident(User **head,char name[50],char role[]);

#endif