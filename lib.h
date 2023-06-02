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

// nome do preceptor, email do residente, nome da atividade, nota do critério 1, resposta1(tag),nota2, resposta2(tag), nota3,resposta3(tag)...,comentario-opcional
//estrutura das avaliações
typedef struct Evaluations {  
  struct User * preceptor; // preceptor que vai dar a nota
  struct User * residente; // residente que vai receber a nota
  char *activityName; // nome da atividade
  char *grade; 
  char *tag; 
  struct Evaluations *next; // ponteiro para a próxima struct atividade
} Evaluations;

//Estrutura dos feedbacks
typedef struct Feedbacks {
  struct User * sender;
  struct User * receiver;
  char * comment;    
  char * tag;
  struct Feedbacks * next; 
} Feedbacks;


// limpa o buffer
void clearInputBuffer();

// aloca memória para os tipos de dado da estrutura User
void allocMemoryForUser(User * usr);

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
// deve-se lembrar de utilizar a função 'savelist()' para salvar a nova lista no txt
void deleteByName(User** head, char name[]);

//encontra o nome do user na lista pelo nome e retorna o user
User * findUserByName(User* head, const char* name);

// recebe a head da lista e uma string que representa o cargo 
// imprime os elementos da lista filtrando pelo cargo
//bool_cpf: se for 1, imprime os cpfs dos usuarios, se for 0 nao imprime
void printList(User *head, char role[], int bool_cpf);

// recebe a head da lista e salva a lista atual no arquivo txt
void saveList(User **head, char * filename);

// Confere o nome do residente no user
void lookingResident(User **head,char email[50],char role[], char namePreceptor[], Evaluations *Epointer);

// Altera um usuário pelo email
void changeUser(User **head, char *email);

//Alocar dos atributos da avaliação
void CreateEvaluationsAttributes(Evaluations *Epointer);

//Valida e-mail e nome pra deletar um usuário 
int check_delete(const char* name, const char* email, User* head);

void send_feedback(Feedbacks **feedback, int *cont, User * sender, User * receiver);

int check_email( const char *email, User *head);


#endif