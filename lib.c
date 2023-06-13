#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

#define MAX_TAGS 4

// limpa o buffer
#if (1)
void clearInputBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}
#endif

// limpa a tela
void clearScreen()
{
#ifdef __linux__
  system("clear");
#elif _WIN32
  system("CLS");
#else
  system("clear");
#endif
}

// aloca memória para os tipos de dado da estrutura User
void allocMemoryForUser(User *usr)
{
  usr->name = malloc(51 * sizeof(char));
  usr->email = malloc(51 * sizeof(char));
  usr->password = malloc(51 * sizeof(char));
  usr->cpf = malloc(12 * sizeof(char));
  usr->role = malloc(51 * sizeof(char));
}

// função para solicitar que o usuário tecle alguma tecla para continuar
void pause()
{
  printf("\n\nPressione qualquer tecla para continuar...\n");
  getch(); // curses.h no linux multipass
}

// cria um novo usuário do tipo User, retorna um ponteiro User para esse usuário
User *createUser(char *newName, char *newEmail, char *newPassword, char *newCpf, char *newRole)
{
  User *newUser = malloc(sizeof(User));
  if (newUser == NULL)
  {
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

void CreateEvaluationsAttributes(Evaluations *Epointer)
{
  Epointer->activityName = malloc(strlen(Epointer->activityName) + 1);
  Epointer->grade = malloc(strlen(Epointer->grade) + 1);
}

// retorna 1 se o login funcionou, 0 se não
int login(char email[50], char password[50], User *usr)
{
  setlocale(LC_ALL, "Portuguese_Brazil");

  int usrFound = 0;
  if (usr == NULL)
  {
    printf("Erro na alocaçao de memoria.\n");
    return 1;
  }
  FILE *users;
  // l� o txt e armazena em users
  users = fopen("Register.txt", "r");

  // printf("\nRegister.txt aberto\n");
  //  l� users e verifica se os 5 que foram lidos correspondem com os de entrada
  while (fscanf(users, "%[^,],%[^,],%[^,],%[^,],%s\n", usr->name, usr->email, usr->password, usr->cpf, usr->role) == 5)
  {

    // printf("\n\n%s e %s\n\n", usr -> name, usr -> password);
    if (strcmp(email, usr->email) == 0)
    {
      usrFound = 1;

      if (strcmp(password, usr->password) == 0)
      {
        fclose(users);
        return 1;
      }
      else
      {
        printf("\nSenha incorreta!\n");
      }
    }
  }
  // caso o usu�rio n�o tenha sido encontrado
  if (!usrFound)
    printf("\nUsuario nao encontrado!\n");
  // printf("\nRegister.txt fechado\n");
  fclose(users);
  return 0;
}

// salva o User no arquivo txt
void storeRegister(User *newUser)
{
  FILE *Register = fopen("Register.txt", "a");
  if (Register == NULL)
  {
    printf("Falha ao abrir arquivo.\n");
    return;
  }

  fprintf(Register, "%s,%s,%s,%s,%s\n", newUser->name, newUser->email, newUser->password, newUser->cpf, newUser->role);

  fclose(Register);
}

// libera a memória de um tipo User
void freeUser(User *usr)
{
  free(usr->name);
  free(usr->email);
  free(usr->password);
  free(usr->cpf);
  free(usr->role);
  free(usr);
}

// insere usuários no final da lista encadeada
void append(User **head, char name[], char email[], char password[], char cpf[], char role[])
{

  // lista vazia
  if (*head == NULL)
  {

    *head = (User *)malloc(sizeof(User));
    (*head)->next = NULL;
    (*head)->name = (char *)malloc(strlen(name) + 1);
    (*head)->email = (char *)malloc(strlen(email) + 1);
    (*head)->password = (char *)malloc(strlen(password) + 1);
    (*head)->cpf = (char *)malloc(strlen(cpf) + 1);
    (*head)->role = (char *)malloc(strlen(role) + 1);
    strcpy((*head)->name, name);
    strcpy((*head)->email, email);
    strcpy((*head)->password, password);
    strcpy((*head)->cpf, cpf);
    strcpy((*head)->role, role);
  }
  else
  { // lista não vazia
    User *current = *head;

    while (current->next != NULL)
    { // chega ao final da lista
      current = current->next;
    }

    current->next = (User *)malloc(sizeof(User)); // novo
    current->next->name = (char *)malloc(strlen(name) + 1);
    current->next->email = (char *)malloc(strlen(email) + 1);
    current->next->password = (char *)malloc(strlen(password) + 1);
    current->next->cpf = (char *)malloc(strlen(cpf) + 1);
    current->next->role = (char *)malloc(strlen(role) + 1);
    strcpy(current->next->name, name);
    strcpy(current->next->email, email);
    strcpy(current->next->password, password);
    strcpy(current->next->cpf, cpf);
    strcpy(current->next->role, role);
    current->next->next = NULL;
  }
}

// cria a lista a partir de um head, de acordo com o que tem no txt
void create_list(User **head)
{
  FILE *fp;
  fp = fopen("Register.txt", "r");
  // Caso não seja possível abrir o arquivo de usuários
  if (fp == NULL)
  {
    pause();
    return;
  }

  char name[51], email[51], password[51], cpf[12], role[21];
  while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%s\n", name, email, password, cpf, role) == 5)
  {
    append(head, name, email, password, cpf, role);
  }
  fclose(fp);
}

// recene a head da lista e uma string que representa o nome do usuário
// deleta o usuáiro da lista encadeada
// deve-se lembrar de utilizar a função 'save_list()' para salvar a nova lista no txt
void deleteByName(User **head, char name[])
{
  User *current = (User *)malloc(sizeof(User));
  current = *head;
  User *temp = (User *)malloc(sizeof(User));
  temp = NULL;
  User *temp2 = (User *)malloc(sizeof(User));
  temp2 = NULL;
  if (current != NULL && strcmp(current->name, name) == 0)
  { // se for o primeiro elemento
    *head = current->next;
    free(current);
    return;
  }

  while (current != NULL && strcmp(current->name, name) != 0)
  { // procurando o usuario pra deletar
    temp = current;
    current = current->next;
  }

  if (current == NULL)
  {
    printf("O elemento com o nome '%s' nao foi encontrado.\n", name);
    pause();
    return;
  }

  temp->next = current->next;
  free(current);
  printf("O elemento com o nome '%s' foi removido.\n", name);
  pause();
}

User *findUserByName(User *head, const char *name)
{
  User *current = head;
  while (current != NULL)
  {
    if (strcmp(current->name, name) == 0)
    {
      return current; // Retorna o usuário quando o nome corresponde
    }
    current = current->next;
  }
  return NULL; // Retorna NULL se o usuário não for encontrado
}

// recebe a head da lista e uma string que representa o cargo
// imprime os elementos da lista filtrando pelo cargo

void printList(User *head, char role[], int bool_cpf)
{
  User *usr = head;
  while (usr != NULL)
  {
    if (!strcmp(usr->role, role) && !strcmp(role, "residente"))
    {
      printf("\n\nNome do residente: %s\n", usr->name);
      printf("Email do residente: %s\n", usr->email);
      if (bool_cpf)
        printf("CPF do residente: %s\n", usr->cpf);
    }
    else if (!strcmp(usr->role, role) && !strcmp(role, "preceptor"))
    {
      printf("\n\nNome do preceptor: %s\n", usr->name);
      printf("Email do preceptor: %s\n", usr->email);
      if (bool_cpf)
        printf("CPF do preceptor: %s\n", usr->cpf);
      printf("-----------------------------------------------------------------"
             "-----------------");
    }
    usr = usr->next;
  }
  printf("\n");
}

// recebe a head da lista e salva a lista atual no arquivo txt
void saveList(User **head, char *filename)
{
  if (*head == NULL)
  {
    return;
  }
  else
  {
    User *temp = *head;
    FILE *Register = fopen(filename, "w");

    if (Register == NULL)
    {
      printf("Falha ao abrir arquivo.\n");
      return;
    }

    while (temp != NULL)
    {
      fprintf(Register, "%s,%s,%s,%s,%s\n", temp->name, temp->email, temp->password, temp->cpf, temp->role);
      temp = temp->next;
    }
    fclose(Register);
  }
}

void residentEvaluation(User **head, char email[], char role[], char namePreceptor[], Evaluations *Epointer)
{
  // nome do preceptor, nome do residente, nome da atividade, nota do critério 1, resposta1(tag),nota2, resposta2(tag), nota3,resposta3(tag).......,comentario-opcional
  // não precisa alocar memoria para a variavel current, sera atribuida ao ponteiro *head

  // Criterios e perguntas norteadoras
  char criterios[12][50] = {"Assisuidade", "Pontualidade", "Vestuario", "Iniciativa", "Postura Etico-Profissional", "Relacionamento em equipe", "Espirito Critico",
                            "Comunicaçao", "Planejamento das atividades de enfermagem", "Dominio dos procedimentos", "Evoluçao", "Liderança"};
  char norteadoras[12][200] = {"O residente cumpre suas açoes e obrigaçoes com frequencia e esforço? Avalie de 1 a 10", "O residente frequentemente cumpre seus horarios e e presente nas horas exigidas? Avalie de 1 a 10",
                               "O residente demonstra cuidado com as normas de prevençao a infecçoes equipando-se adequadamente? Avalie de 1 a 10", "O residente lida bem com situaçoes imprevistas propondo situaçoes viaveis? Avalie de 1 a 10",
                               "O residente trabalha respeitando os valores do paciente e seu sigilo profissional? Avalie de 1 a 10", "O residente trabalha com exelencia com seus pacientes, superiores e profissionais de saude? Avalie de 1 a 10",
                               "O residente lida bem com criticas e possui um bom senso critico? Avalie de 1 a 10", "O residente comunica bem seus pensamentos? Avalie de 1 a 10",
                               "O residente estabelece prioridades e estrutura suas atividades bem? Avalie de 1 a 10", "O residente demonstra habilidade e segurança nos procedimentos realizados? Avalie de 1 a 10",
                               "O residente registra de maneira clara e concisa as sua observaçoes? Avalie de 1 a 10", "O residente partilha bem seu conhecimento e lidera bem sua equipe? Avalie de 1 a 10"};
  char taglistGood[24][200] = {"O residente cumpre seus açoes consistentemente e com excelencia", "O residente desempenha bem suas tarefas",
                               "O residente cumpre seus horarios e dias.", "O residente falta ocasionalmente as suas atividades porem continua acima da media",
                               "O residente veste-se apropriadamente.", "O residente quase sempre veste-se apropriadamente.",
                               "O residente e nato em lidar com situaçoes do hospital no dia-a-dia.", "O residente desempenha normalmente suas funçoes.",
                               "O residente respeita os valores de seus pacientes e trata informaçoes com cuidado e sigilo", "O residente poderia demonstrar mais atençao ao sigilo profissional e com os valores do paciente",
                               "O residente trabalha excelentemente com seus superiores e pacientes", "O residente tem dificuldade em trabalhar com seus superiores. Apesar disso, trabalha bem de forma geral",
                               "O residente lida tranquilamente com criticas e possui tambem um bom senso critico", "O residente aceita criticas de forma construtiva.",
                               "O residente transmite suas ideias perfeitamente e escuta as ideias de seus colegas de trabalho", "O residente transmite bem suas ideias.",
                               "O residente planeja sua rotina muito bem", "O residente planeja sua rotina bem",
                               "O residente demonstra segurança e habilidade nas suas atividades", "O residente tem bom dominio das praticas.",
                               "O residente realiza detalhadas e curtas observaçoes", "O residente realiza boas observaçoes.",
                               "O residente lidera seu grupo com eficiencia e respeito", "O residente lidera seu grupo com respeito mas de forma pouco eficiente"};
  char taglistBad[24][200] = {"O residente poderia se empenhar mais nas tarefas de seu dia-a-dia", "O residente deixa a desejar no compromisso com a instituiçao",
                              "O residente falta mais dias que o aceito", "O residente nao cumpre seus dias ou horarios",
                              "O residente as vezes se esquece do vestimento adequado.", "O residente frequentemente ignora as regras de prevençao de infecçoes.",
                              "O residente poderia lidar melhor com situaçoes habituais", "O residente gerencia mal as complexidades de sua rotina",
                              "O residente nao respeita o sigilo profissional", "O residente demonstra descaso com as informaçoes dos pacientes e da instituiçao e falta profissionalismo",
                              "O residente possui dificuldade em trabalhar com pacientes trabalhando abaixo do esperado", "O residente nao trabalha bem com pacientes e superiores",
                              "O residente possui a habilidade de criticar mas nao lida bem com criticas", "O residente lida mal com criticas de forma geral.",
                              "O residente compreende ideias transmitidas pelos colegas mas possui dificuldade em se comunicar", "O residente transmite mal suas ideias.",
                              "O residente planeja sua rotina mal", "O residente planeja sua rotina muito mal",
                              "O residente possui alguns problemas no dominio das tarefas.", "O residente demonstra problemas graves no entendimento e segurança com os procedimentos.",
                              "O residente deixa a desejar nas observaçoes sendo elas muito longas ou muito confusas", "O residente escreve observaçoes longas e confusas",
                              "O residente nao respeita seus integrantes comprometendo o desempenho da equipe", "O residente nao lidera bem os integrantes do seu grupo e falta respeito com eles."};
  float PesoArray[12] = {0.03, 0.03, 0.04, 0.05, 0.1, 0.05, 0.1, 0.05, 0.15, 0.15, 0.15, 0.1};
  User *current = *head;
  FILE *notas;
  notas = fopen("notas.txt", "a");
  if (notas == NULL)
  {
    printf("Erro ao abrir o arquivo!");
    return;
  }

  // Printando o nome do preceptor
  Epointer->preceptor = malloc(strlen(namePreceptor) + 1); // armazendo o nome do preceptor na Struct
  strcpy(Epointer->preceptor, namePreceptor);
  fprintf(notas, "%s", namePreceptor);

  while (current != NULL)
  {
    if (strcmp(current->email, email) == 0 && strcmp(current->role, role) == 0)
    {
      // Se o nome for encontrado e role for "residente", ele entra e printa o nome
      Epointer->residente = malloc(strlen(current->email) + 1); // Armazenando o nome do residente na Struct
      strcpy(Epointer->residente, current->email);
      fprintf(notas, ";%s", current->email);
      break;
    }
    current = current->next;
  }
  // Chamando a função
  CreateEvaluationsAttributes(Epointer);
  if (Epointer == NULL)
  {
    // Erro ao iniciar o ponteiro
    printf("\nErro ao ler as notas");
    return;
  }
  printf("\t\tVamos iniciar a avaliaçao, preceptor!\n Insira o nome da atividade:\n");

  // Lendo o nome da avaliação
  scanf(" %[^\n]", Epointer->activityName);

  system("cls");
  // Printando o nome da avaliação no arquivo notas.txt
  fprintf(notas, ";%s", Epointer->activityName);

  // codigo incompleto
  int j = 0;
  int cont_tag = 0;
  int index, ToInt;
  float acumulador = 0;

  for (int i = 0; i < 12; i++)
  {
    float notafinal;
    system("cls");
    printf("Criterio %i: %s\n", i + 1, criterios[i]);
    printf("%s\n", norteadoras[i]);
    scanf("%s", Epointer->grade);
    ToInt = atoi(Epointer->grade);
    printf("Agora vamos inserir tags, preceptor! escolha baseado no indicie a esquerda!\n");
    if (ToInt > 5)
    {
      printf("0: %s\n 1: %s\n", taglistGood[j], taglistGood[j + 1]);
    }
    else
    {
      printf("0: %s\n 1: %s\n", taglistBad[j], taglistBad[j + 1]);
    }
    scanf("%d", &index);
    index = index + cont_tag;
    acumulador = acumulador + (atoi(Epointer->grade) * PesoArray[i]);
    if (index != j && index != j + 1)
    {
      while (index != j && index != j + 1)
      {
        printf("Tag invalida! selecione uma tag conforme os criterios.\n");
        if (ToInt > 5)
        {
          printf("0: %s\n 1: %s\n", taglistGood[j], taglistGood[j + 1]);
        }
        else
        {
          printf("0: %s\n 1: %s\n", taglistBad[j], taglistBad[j + 1]);
        }
        scanf("%d", &index);
        index = index + cont_tag;
      }
    }
    if (ToInt > 5)
    {
      Epointer->tag = malloc(strlen(taglistGood[index]) + 1);
      strcpy(Epointer->tag, taglistGood[index]);
    }
    else
    {
      Epointer->tag = malloc(strlen(taglistBad[index]) + 1);
      strcpy(Epointer->tag, taglistBad[index]);
    }
    fprintf(notas, ";%s", Epointer->grade);
    fprintf(notas, ";%s", Epointer->tag);
    Epointer->next;
    j = j + 2;

    cont_tag += 2;
  }
  char choice = 'b';
  fprintf(notas, ";%.2f", acumulador);
  printf("Otimo. Estamos quase la! Voce gostaria de deixar um comentario opcional? (s/n)\n");
  while(choice!='s'&&choice!='n'){
    scanf(" %c", &choice);
    if (choice == 's')
    {
      printf("Insira seu comentario! (maximo de 200 caracteres):\n");
      scanf(" %[^\n]", Epointer->comentario);
      fprintf(notas, ";%s", Epointer->comentario);
    }else if (choice == 'n'){
      fprintf(notas,";Nao existe comentario opcional.");
    }else{
      printf("Escolha invalida\n");
    }
  }

  fprintf(notas, "\n");
 
  free(Epointer->preceptor);
  free(Epointer->residente);
  free(Epointer->tag);
  free(Epointer->grade);
  free(Epointer);
  fclose(notas);
}
int check_email(const char *email, User *head)
{
  User *current = head;
  int arroba = 0, ponto = 0;

  // checando email e nome de usuario
  for (int i = 0; email[i] != '\0'; i++)
  {
    if (email[i] == '@')
    {
      arroba++;
    }
    else if (email[i] == '.')
    {
      ponto++;
    }
  }
  if (arroba != 1 || ponto != 1)
  {
    return 0;
  }
  while (current != NULL)
  {
    if (strcmp(current->email, email) == 0)
    {
      return 1;
    }
    current = current->next;
  }
  return 0;
}

int check_delete(const char *name, const char *email, User *head)
{
  User *current = head;
  int arroba = 0, ponto = 0;

  // checando email e nome de usuario
  for (int i = 0; email[i] != '\0'; i++)
  {
    if (email[i] == '@')
    {
      arroba++;
    }
    else if (email[i] == '.')
    {
      ponto++;
    }
  }
  if (arroba != 1 || ponto != 1)
  {
    printf("Email invalido. Insira um email valido.\n");
    return 0;
  }
  while (current != NULL)
  {
    if (strcmp(current->name, name) == 0 && strcmp(current->email, email) == 0)
    {
      printf("Usuario encontrado no arquivo.\n");
      return 1;
    }
    current = current->next;
  }
  printf("Usuario nao encontrado no sistema.\n");
  free(current);
  return 0;
}

void create_feedback(Feedbacks **feedback, User *sender, User *receiver)
{
  char tag_list[4][20] = {"Comunicativo", "Dedicado", "Atencioso", "Descuidado"};
  char add_comment, add_tag;
  int selected_tags[4];
  char input[200];
  int num_tags = 0;

  for (int i = 0; i < MAX_TAGS; i++)
  {
    printf("%d - %s\n", i, tag_list[i]);
  }
  printf("Quantas tags voce gostaria de inserir?\n");
  scanf("%d", &num_tags);
  if (num_tags > MAX_TAGS)
  {
    printf("Voce so pode inserir ate %d tags!\n", MAX_TAGS);
    return;
  }

  int j = 0;
  while (j < num_tags)
  {
    printf("Digite a tag %d: ", j+1);
    scanf("%d", &selected_tags[j]);
    
    if(selected_tags[j] > 3 || selected_tags[j] < 0){
      printf("Digite um valor entre 0 e 3.\n");
      continue;
    }
    
    j++; // Increment j to move to the next iteration
  }

  clearScreen();

  printf("Tags selecionadas:\n");
  for (int i = 0; i < num_tags; i++)
  {
    printf("%d - %s\n", i + 1, tag_list[selected_tags[i]]);
  }

  printf("Deseja inserir um comentario extra?[s/n]\n");
  scanf(" %c", &add_comment);

  char comment[100];
  if (add_comment == 's' || add_comment == 'S')
  {
    printf("Digite o comentario com ate 100 caracteres:\n");
    scanf(" %[^\n]", comment);
  }
  else strcpy(comment, "sem comentario");// Comentário vazio

  clearScreen();
  printf("\t\t\tSeu feedback para o usuario %s", receiver->name);
  printf("\n\nTags:\n");
  for (int i = 0; i < num_tags; i++)
  {
    printf("%s\n", tag_list[selected_tags[i]]);
  }
  printf("\nSeu comentario: %s", comment);

  Feedbacks *new_feedback = (Feedbacks *)malloc(sizeof(Feedbacks));
  new_feedback->sender = sender;
  new_feedback->receiver = receiver;
  new_feedback->comment = (char *)malloc(sizeof(char) * 500);
  strcpy(new_feedback->comment, comment);
  new_feedback->tags = (char **)malloc(sizeof(char *) * num_tags);

  for (int i = 0; i < num_tags; i++)
  {
    new_feedback->tags[i] = (char *)malloc(sizeof(char) * (strlen(tag_list[i]) + 1));
    strcpy(new_feedback->tags[i], tag_list[i]);
  }

  new_feedback->next = NULL;

  saveFeedbackInFile(new_feedback, num_tags);

  printf("\nFeedback enviado com sucesso!\n");
  // ver se precisa tirar o free
  free(new_feedback);
}

// printando no arquivo feedback.txt
void saveFeedbackInFile(Feedbacks *feedback, int num_tags)
{
  FILE *feedbackFile = fopen("feedback.txt", "a");

  if (feedbackFile == NULL)
  {
    printf("Erro ao abrir o arquivo feedback.txt!\n");
    return;
  }

  fprintf(feedbackFile, "%s;%s;%s;", feedback->sender->name, feedback->receiver->name, feedback->comment);

  for (int i = 0; i < num_tags; i++)
  {
    fprintf(feedbackFile, "%s;", feedback->tags[i]);
  }
  fprintf(feedbackFile, "\n");

  fclose(feedbackFile);
  return;
}

void printFeedbacksByName(const char *user)
{
  FILE *feedbackFile = fopen("feedback.txt", "r");
  char line[500];

  if (feedbackFile == NULL)
  {
    printf("Erro ao abrir o arquivo feedback.txt!\n");
    return;
  }

  while (fgets(line, sizeof(line), feedbackFile))
  {
    char *sender = strtok(line, ";");
    char *receiver = strtok(NULL, ";");
    char *comment = strtok(NULL, ";");

    // Verifica se o usuário é o receiver
    if (strcmp(receiver, user) == 0)
    {
      printf("Comentario: %s\n", comment);

      printf("Tags: ");
      char *tag = strtok(NULL, ";");

      while (tag != NULL)
      {
        printf("%s ", tag);
        tag = strtok(NULL, ";");
      }
      printf("\n\n");
    }
  }

  fclose(feedbackFile);
}

#if (1)
void changeUser(User **head, char *email)
{
  User *current = (User *)malloc(sizeof(User));
  current = *head;
  char choice;
  char newName[100];    // será usado como novo nome
  char newEmail[50];    // será usado como novo email
  char newCpf[12];      // será usado como novo CPF
  char newPassword[50]; // será usado como nova senha
  char newRole[50];     // será usado como novo cargo

  if (current != NULL && strcmp(current->email, email) == 0)
  { // se for o primeiro elemento
    *head = current->next;
    printf("\n\nNome do residente: %s\n", current->name);
    printf("Email do residente: %s\n", current->email);
    printf("CPF do residente: %s\n", current->cpf);
    printf("\nVoce gostaria de alterar o nome desse usuario?(s/n)\n");
    clearInputBuffer();
    scanf("%c", &choice);
    clearInputBuffer();
    if (choice == 's')
    {
      printf("\nInforme o novo nome desse usuario: ");
      fgets(newName, sizeof(newName), stdin);
      newName[strcspn(newName, "\n")] = '\0';
      strcpy(current->name, newName);
    }
    else
      printf("\nOk! O nome permanecera %s!\n", current->name);
    printf("\nVoce gostaria de alterar o email desse usuario?(s/n)\n");
    scanf("%c", &choice);
    clearInputBuffer();
    if (choice == 's')
    {
      printf("\nInforme o novo email desse usuario: ");
      fgets(newEmail, sizeof(newEmail), stdin);
      newEmail[strcspn(newEmail, "\n")] = '\0';
      strcpy(current->email, newEmail);
    }
    else
      printf("\nOk! O email permanecera %s!\n", current->email);
    printf("\nVoce gostaria de alterar o cpf desse usuario?(s/n)\n");
    scanf("%c", &choice);
    clearInputBuffer();
    if (choice == 's')
    {
      int cpfAux = 0;
      do
      {
        printf("Informe o novo cpf desse usuario: ");
        fgets(newCpf, sizeof(newCpf), stdin);
        newCpf[strcspn(newCpf, "\n")] = '\0';
        if (strlen(newCpf) != 11)
        {
          printf("\nCPF invalido!\n");
          cpfAux = 1;
        }
        else
        {
          cpfAux = 0;
        }
      } while (cpfAux);
      strcpy(current->cpf, newCpf);
    }
    else
      printf("\nOk! O CPF permanecera %s\n", current->cpf);
    printf("\nVoce gostaria de alterar o cargo desse usuario?(s/n)\n");
    scanf("%c", &choice);
    clearInputBuffer();
    if (choice == 's')
    {
      do
      {
        printf("\nInforme o novo cargo desse usuario:(residente/preceptor) ");
        fgets(newRole, sizeof(newRole), stdin);
        newRole[strcspn(newRole, "\n")] = '\0';
        if (strcmp(newRole, "residente") != 0 && strcmp(newRole, "preceptor") != 0)
          printf("\nCargo invalido! Digite novamente!\n");
      } while (strcmp(newRole, "residente") != 0 && strcmp(newRole, "preceptor") != 0);
      strcpy(current->role, newRole);
    }
    else
      printf("\nOk! O cargo permanecera %s!\n", current->role);
    printf("\nVocê gostaria de alterar a senha desse usuario?(s/n)\n");
    scanf("%c", &choice);
    clearInputBuffer();
    if (choice == 's')
    {
      printf("Informe a nova senha desse usuario: ");
      fgets(newPassword, sizeof(newPassword), stdin);
      newPassword[strcspn(newPassword, "\n")] = '\0';
      strcpy(current->password, newPassword);
    }
    else
      printf("\nOk! A senha permanecera %s!", current->password);
    return;
  }

  while (current != NULL && strcmp(current->email, email) != 0)
  { // procurando o usuario para alterar
    current = current->next;
  }

  if (current == NULL)
  {
    printf("O usuario com o email '%s' nao foi encontrado.\n", email);
    return;
  }

  printf("\n\nNome do residente: %s\n", current->name);
  printf("Email do residente: %s\n", current->email);
  printf("CPF do residente: %s\n", current->cpf);
  printf("\nVoce gostaria de alterar o nome desse usuario?(s/n)\n");
  clearInputBuffer();
  scanf("%c", &choice);
  clearInputBuffer();
  if (choice == 's')
  {
    printf("\nInforme o novo nome desse usuario: ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0';
    strcpy(current->name, newName);
  }
  else
    printf("\nOk! O nome permanecera %s!\n", current->name);
  printf("\nVoce gostaria de alterar o email desse usuario?(s/n)\n");
  scanf("%c", &choice);
  clearInputBuffer();
  if (choice == 's')
  {
    printf("\nInforme o novo email desse usuario: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';
    strcpy(current->email, newEmail);
  }
  else
    printf("\nOk! O email permanecera %s!\n", current->email);
  printf("\nVoce gostaria de alterar o cpf desse usuario?(s/n)\n");
  scanf("%c", &choice);
  clearInputBuffer();
  if (choice == 's')
  {
    int cpfAux = 0;
    do
    {
      printf("Informe o novo cpf desse usuario: ");
      fgets(newCpf, sizeof(newCpf), stdin);
      if (strlen(newCpf) != 11)
      {
        printf("\nCPF invalido!\n");
        cpfAux = 1;
      }
      else
      {
        cpfAux = 0;
      }
    } while (cpfAux);
    strcpy(current->cpf, newCpf);
  }
  else
    printf("\nOk! O CPF permanecera %s\n", current->cpf);
  printf("\nVocê gostaria de alterar o cargo desse usuario?(s/n)\n");
  scanf(" %c", &choice);
  clearInputBuffer();
  if (choice == 's')
  {
    do
    {
      printf("\nInforme o novo cargo desse usuario:(residente/preceptor) ");
      fgets(newRole, sizeof(newRole), stdin);
      newRole[strcspn(newRole, "\n")] = '\0';
      if (strcmp(newRole, "residente") != 0 && strcmp(newRole, "preceptor") != 0)
        printf("\nCargo invalido! Digite novamente!\n");
    } while (strcmp(newRole, "residente") != 0 && strcmp(newRole, "preceptor") != 0);
    strcpy(current->role, newRole);
  }
  else
    printf("\nOk! O cargo permanecera %s!\n", current->role);
  printf("\nVoce gostaria de alterar a senha desse usuario?(s/n)\n");
  scanf("%c", &choice);
  clearInputBuffer();
  if (choice == 's')
  {
    printf("Informe a nova senha desse usuario: ");
    fgets(newPassword, sizeof(newPassword), stdin);
    newPassword[strcspn(newPassword, "\n")] = '\0';
    strcpy(current->password, newPassword);
  }
  else
    printf("\nOk! A senha permanecera %s!", current->password);

  return;
}
#endif

void printEvaluations(char *residenteEmail)
{
  char criterios_nomes[12][50] = {"Assisuidade", "Pontualidade", "Vestuario", "Iniciativa", "Postura Etico-Profissional", "Relacionamento em equipe", "Espirito Cretico",
                                  "Comunicaçao", "Planejamento das atividades de enfermagem", "Dominio dos procedimentos", "Evoluçao", "Liderança"};
  FILE *fileActivities;
  fileActivities = fopen("notas.txt", "r");
  char line[2000];
  int activiesNumber = 0;

  if (fileActivities == NULL)
  {
    printf("Impossivel abrir arquivo.\n");
    return;
  }

  while (fgets(line, sizeof(line), fileActivities))
  {
    char *token = strtok(line, ";");
    int i = 0;

    char preceptor[100];
    char residente[100];
    char atividade[100];
    char tags[12][100];
    char comentarioFinal[200];
    int notas[12];
    float notaFinal;
    int posNotas = 0;
    int posTag = 0;

    while (token != NULL)
    {
      switch (i)
      {
      case 0:
        strcpy(preceptor, token);
        break;
      case 1:
        strcpy(residente, token);
        break;
      case 2:
        strcpy(atividade, token);
        break;
      default:
        if (i % 2 == 1 && i != 27)
        {
          notas[posNotas] = atoi(token);
          posNotas++;
        }
        else if (i % 2 == 0 && i != 28)
        {
          strcpy(tags[posTag], token);
          posTag++;
        }
        else if (i == 27)
        {
          notaFinal = atof(token);
        }
        else if (i == 28){
          strcpy(comentarioFinal, token);
        }
        break;
      }

      token = strtok(NULL, ";");
      i++;
    }

    if (strcmp(residente, residenteEmail) == 0)
    {
      activiesNumber++;
      printf("\nPreceptor: %s | Residente: %s | Nome da atividade: %s\n\n", preceptor, residente, atividade);
      for (int j = 0; j < 12; j++)
      {
        printf("%s: %s, Nota: %d\n", criterios_nomes[j], tags[j], notas[j]);
      }
      printf("Nota Final: %.2f\n", notaFinal);
      printf("Comentario: %s\n", comentarioFinal);
    }
    printf("--------------------------------------------------------------------------------------------------------------");
  }
  if (activiesNumber == 0)
  {
    printf("Voce nao possui nenhuma atividade no momento!\n");
  }
  fclose(fileActivities);
}

void freelist(User **head)
{
  User *current = *head;
  User *next;

  while (current != NULL)
  {
    next = current->next;
    freeUser(current);
    current = next;
  }

  *head = NULL;
}

// nome do preceptor, email do residente, nome da atividade, nota do critério 1, resposta1(tag),nota2, resposta2(tag), nota3,resposta3(tag).......,comentario-opcional

/*printf("Qual o email do residente que voce deseja avaliar?\n");
scanf(emailDoResidente);
Atividade * atvd;
atvd -> preceptor_da_atvd = email do preceptor que está logado;
atividade->emailResidente = userFound(&head, residente);
lembra de alocar memória
printf("Qual o nome da atividade?");
scanf(atvd -> nome_da_atividade);
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio1)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag1)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio2)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag2)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio);
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag3)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag4)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag5)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag6)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag7)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag8)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag9)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag10)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag11)
printf("Qual a nota do critério 1?\nCritério 1: Vestimenta");
scanf(atvd -> nota_criterio)
printf("Selecione a tag de comentário\n1-Bom, 2-Ruim,3-Muito ruim");
scanf(atvd ->tag12)
printf("\nDeseja adicionar um comentário opcional?");
fgets(atvd -> comentarioDaAtividade);*/
