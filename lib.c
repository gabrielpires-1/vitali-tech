#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

#define MAX_COMMENTS 10
#define MAX_TAGS 10

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
void clearScreen() {
  #ifdef __linux__
    system("clear");
  #elif _WIN32
    system("CLS");
  #else
    system("clear");
  #endif  
}

// aloca memória para os tipos de dado da estrutura User
void allocMemoryForUser(User * usr){
  usr->name = malloc(51 * sizeof(char));
  usr->email = malloc(51 * sizeof(char));
  usr->password = malloc(51 * sizeof(char));
  usr->cpf =  malloc(12 * sizeof(char));
  usr->role = malloc(51 * sizeof(char));
}

// função para solicitar que o usuário tecle alguma tecla para continuar
void pause()
{
  printf("\n\nPressione qualquer tecla para continuar...\n");
  getch();
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
    printf("Erro na alocação de memória.\n");
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
    printf("\nUsu�rio n�o encontrado!\n");
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

User * findUserByName(User* head, const char* name) {
  User* current = head;
  while (current != NULL) {
    if (strcmp(current->name, name) == 0) {
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
    User *temp = (User *)malloc(sizeof(User));
    temp = *head;
    FILE *Register = fopen(filename, "w");
    while (temp != NULL)
    {
      if (Register == NULL)
      {
        printf("Falha ao abrir arquivo.\n");
        return;
      }

      fprintf(Register, "%s,%s,%s,%s,%s\n", temp->name, temp->email, temp->password, temp->cpf, temp->role);

      temp = temp->next;
    }
    fclose(Register);
  }
}

void lookingResident(User **head, char email[], char role[], char namePreceptor[], Evaluations *Epointer)
{
  // nome do preceptor, nome do residente, nome da atividade, nota do critério 1, resposta1(tag),nota2, resposta2(tag), nota3,resposta3(tag).......,comentario-opcional
  // não precisa alocar memoria para a variavel current, sera atribuida ao ponteiro *head

  // Criterios e perguntas norteadoras
  char criterios[12][50] = {"Assisuidade", "Pontualidade", "Vestuario", "Iniciativa", "Postura Ético-Profissional", "Relacionamento em equipe", "Espirito Crítico",
                            "Comunicação", "Planejamento das atividades de enfermagem", "Dominio dos procedimentos", "Evolução", "Liderança"};
  char norteadoras[12][200] = {"O residente cumpre suas ações e obrigações com frequencia e esforço? Avalie de 1 a 100", "O residente frequentemente cumpre seus horários e é presente nas horas exigidas? Avalie de 1 a 100",
                               "O residente demonstra cuidado com as normas de prevenção á infecções equipando-se adequadamente? Avalie de 1 a 100", "O residente lida bem com situações imprevistas propondo situações viaveis? Avalie de 1 a 100",
                               "O residente trabalha respeitando os valores do paciente e seu sigilo profissional? Avalie de 1 a 100", "O residente trabalha com exelencia com seus pacientes, superiores e profissionais de saúde? Avalie de 1 a 100",
                               "O residente lida bem com críticas e possui um bom senso crítico? Avalie de 1 a 100", "O residente comunica bem seus pensamentos? Avalie de 1 a 100",
                               "O residente estabelece prioridades e estrutura suas atividades bem? Avalie de 1 a 100", "O residente demonstra habilidade e segurança nos procedimentos realizados? Avalie de 1 a 100",
                               "O residente registra de maneira clara e concisa as sua observações? Avalie de 1 a 100", "O residente partilha bem seu conhecimento e lidera bem sua equipe? Avalie de 1 a 100"};
  char taglist[48][200] = {"0 :O residente cumpre seus ações consistentemente e com excelência", "1 :O residente poderia se empenhar mais nas tarefas de seu dia-a-dia, mas não falta com as entregas", "2: O residente desempenha bem suas tarefas, porém falta consistência", "3: O residente deixa a desejar no compromisso com a instituição",
                           "4: O residente falta mais dias que o aceito, porém não falta as atividade", "5: O residente falta muito às suas atividades, porém comparece frequentemente no hospital", "6: O residente cumpre seus horários e dias.", "7: O residente não cumpre seus dias ou hoários",
                           "8: O residente veste-se apropriadamente, cumprindo as regras de prevenção à infecções", "9: O residente quase sempre veste-se apropriadamente.", "10: O residente as vezes se esquece do vestimento adequado.", "11: O residente frequentemente ignora às regras de prevenção de infecções, comprometendo o bem-estar de todos",
                           "12: O residente é nato em lidar com situações do hospital no dia-a-dia.", "13: O residente poderia lidar melhor com situações habituais", "14: O residente desempenha normalmente suas funções, porém lida com mal com imprevistos", "15: O residente gerencia mal as complexidades de sua rotina",
                           "16: O residente respeita os valores de seus pacientes e trata informações com cuidado e sigilo", "17: O residente possui dificuldades em empatizar com os valores dos pacientes", "18:O residente não respeita o sigilo profissional", "19: O residente demonstra descaso com as informações dos pacientes e da instituição e falta profissionalismo",
                           "20: O residente trabalha excelentemente com seus superiores e pacientes", "21: O residente tem dificuldade em trabalhar com seus superiores", "22: O residente possui dificuldade em trabalhar com pacientes", "23: O residente não trabalha bem com pacientes e superiores",
                           "24: O residente lida tranquilamente com críticas e possui também um bom senso crítico", "25: O residente possui a habilidade de criticar mas não lida bem com críticas", "26: O residente aceita críticas de forma construtiva, mas não possui bom senso crítico", "27: O residente lida mal com críticas de forma geral, faltando senso crítico e a habilidade de receber críticas ",
                           "28: O residente transmite suas ideias perfeitamente e escuta as ideias de seus colegas de trabalho", "29: O residente transmite bem suas ideias, mas não escuta outras bem", "30: O residente compreende ideias transmitidas pelos colegas, mas possui dificuldade em se comunicar", "31: O residente transmite mal suas ideias e não compreende o que seus colegas propõem",
                           "32: O residente planeja sua rotina muito bem", "33: O residente planeja sua rotina bem", "34: O residente planeja sua rotina mal", "35: O residente planeja sua rotina muito mal",
                           "36: O residente demonstra segurança e habilidade nas suas atividades", "37: O residente tem bom domínio das práticas, mas falta a segurança de um bom profissional", "38: O residente é confiante e seguro, porém falta domíno das atividades", "39: O residente demonstra problemas graves no entendimento e segurança com os procedimentos.",
                           "40: O residente realiza boas e curtas observações", "41: o residente realiza boas observações, mas podiam ser mais concisas", "42: O residente realiza observações concisas, porém pouco claras", "43: O residente escreve observações longas e confusas",
                           "44: O residente lidera seu grupo com eficiência e respeito", "45: O residente lidera seu grupo com respeito, mas de forma pouco eficiente", "46: O residente lidera seu grupo com eficiência, mas não respeita seus integrantes", "47: O residente não lidera bem os integrantes do seu grupo e falta respeito com eles."};
  User *current = *head;
  FILE *notas;
  notas = fopen("notas.txt", "a");
  if (notas == NULL)
  {
    printf("Erro ao abrir o arquivo!");
    return;
  }

  // Printando o nome do preceptor
  Epointer->preceptor = malloc(strlen(namePreceptor)+1);//armazendo o nome do preceptor na Struct
  strcpy(Epointer->preceptor,namePreceptor);
  fprintf(notas, "Preceptor: %s", namePreceptor);

  while (current != NULL)
  {
    if (strcmp(current->email, email) == 0 && strcmp(current->role, role) == 0)
    {
      // Se o nome for encontrado e role for "residente", ele entra e printa o nome
      Epointer->residente = malloc(strlen(current->email)+1);//Armazenando o nome do residente na Struct
      strcpy(Epointer->residente,current->email);
      fprintf(notas, ", Residente: %s", current->email);
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
  printf("\t\tVamos iniciar a avaliação, preceptor!\n Insira o nome da atividade:\n");

  // Lendo o nome da avaliação
  scanf(" %[^\n]", Epointer->activityName);

  system("cls");
  // Printando o nome da avaliação no arquivo notas.txt
  fprintf(notas, ", Nome da atividade: %s", Epointer->activityName);

  // codigo incompleto
  int j = 0;
  int index, ToInt,acumulador;
  acumulador =0;
  ToInt =0;
  for (int i=0;i<12;i++){
    system("cls");
    printf("Criterio %i: %s\n",i+1,criterios[i]);
    printf("%s\n",norteadoras[i]);
    scanf("%s",Epointer->grade);
    ToInt = atoi(Epointer->grade);
    printf("Agora vamos inserir tags, preceptor! escolha baseado no índicie à esquerda!\n");
    printf("%s\n %s\n %s\n %s\n",taglist[j],taglist[j+1],taglist[j+2],taglist[j+3]);
    scanf("%d",&index);
    acumulador = acumulador+ToInt;
    if(index != j && index!=j+1 && index!= j+2 && index!=j+3){
      while(index != j && index!=j+1 && index!= j+2 &&index!=j+3){
      printf("Tag inválida! selecione uma tag conforme os critérios.\n");
      printf("%s\n %s\n %s\n %s\n",taglist[j],taglist[j+1],taglist[j+2],taglist[j+3]);
      scanf("%d",&index);
      }
    }
      Epointer->tag = malloc(strlen(taglist[index])+1);
      strcpy(Epointer->tag,taglist[index]);
      fprintf(notas, ", CRITÉRIO %i: %s NOTA: %s", i+1, criterios[i], Epointer->grade);
      fprintf(notas,", TAG AVALIATIVA: %s",Epointer->tag);
      Epointer->next;
      j=j+4;
  
      
  }
  fprintf(notas,", NOTA FINAL: %d\n",acumulador/12);
  fclose(notas);
}
int check_email( const char *email, User *head)
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
  }else{
    return 1;
  }
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
    printf("Email inválido. Insira um email válido.\n");
    free(current);
    return 0;
  }
  while (current != NULL)
  {
    if (strcmp(current->name, name) == 0 && strcmp(current->email, email) == 0)
    {
      printf("Usuário encontrado no arquivo.\n");
      return 1;
    }
    current = current->next;
  }
  printf("Usuário não encontrado no sistema.\n");
  free(current);
  return 0;
}

void send_feedback(Feedbacks **feedback, int *cont, User * sender, User * receiver)
{
  char tags[4][20] = {"Comunicativo", "Dedicado", "Atencioso", "Disperso"};
  char add_comment, add_tag;
  //limite de comentarios
  if (*cont < 10)
  {
    // Solicitar o nome do residente
    printf("Digite o nome do residente que gostaria de enviar um feedback:\n");

    printf("Gostaria de adicionar uma tag?[s/n]\n");
    for (int i = 0; i < 4; i++)
    {
      printf("%d - %s\n", i, tags[i]);
    }
    scanf(" %c", &add_tag);
    if(add_tag == 's'){
      //inserir tag
    }
    //else if (add_tag == 'n')
    
    
    // Verificar se deseja inserir um comentário extra
    printf("Deseja inserir um comentário extra?[s/n]\n");
    scanf(" %c", &add_comment);

    char comment[100];
    if (add_comment == 's')
    {
      // Solicitar o comentário extra
      printf("Digite o comentário extra:\n");
      scanf(" %[^\n]", comment);
    }
    else
    {
      // Comentário vazio
      strcpy(comment,"");
    }

    // Adicionar o feedback à estrutura Feedbacks
    Feedbacks *new_feedback = (Feedbacks *)malloc(sizeof(Feedbacks));
    new_feedback->sender = sender;
    new_feedback->receiver = receiver;
    strcpy(new_feedback->comment, comment);
    new_feedback->tag = ""; // Definir a tag corretamente
    new_feedback->next = NULL;

    // Escrever no arquivo feedback.txt
    FILE *fp = fopen("feedback.txt", "a");
    if (fp != NULL)
    {
      // Obtendo a data atual do feedback
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      char date[20];
      sprintf(date, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

      // Escrever no arquivo no formato: nome_sender, nome_receiver, comentário, tag, data
      fprintf(fp, "%s, %s, %s, %s, %s\n", sender->name, receiver->name, comment, new_feedback->tag, date);

      // Fechar o arquivo
      fclose(fp);
    }
    else
    {
      printf("Erro ao abrir o arquivo feedback.txt\n");
    }

    printf("\nComment added successfully.\n");
  }
  else
  {
    printf("\nNúmero de comentários máximo atingido! Caso deseje enviar mais comentários espere até amanhã!\n");
  }
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
    printf("\nVocê gostaria de alterar o nome desse usuário?(s/n)\n");
    clearInputBuffer();
    scanf("%c", &choice);
    clearInputBuffer();
    if (choice == 's')
    {
      printf("\nInforme o novo nome desse usuário: ");
      fgets(newName, sizeof(newName), stdin);
      newName[strcspn(newName, "\n")] = '\0';
      strcpy(current->name, newName);
    }
    else
      printf("\nOk! O nome permanecerá %s!\n", current->name);
    printf("\nVocê gostaria de alterar o email desse usuário?(s/n)\n");
    scanf("%c", &choice);
    clearInputBuffer();
    if (choice == 's')
    {
      printf("\nInforme o novo email desse usuário: ");
      fgets(newEmail, sizeof(newEmail), stdin);
      newEmail[strcspn(newEmail, "\n")] = '\0';
      strcpy(current->email, newEmail);
    }
    else
      printf("\nOk! O email permanecerá %s!\n", current->email);
    printf("\nVocê gostaria de alterar o cpf desse usuário?(s/n)\n");
    scanf("%c", &choice);
    clearInputBuffer();
    if (choice == 's')
    {
      int cpfAux = 0;
      do
      {
        printf("Informe o novo cpf desse usuário: ");
        fgets(newCpf, sizeof(newCpf), stdin);
        newCpf[strcspn(newCpf, "\n")] = '\0';
        if (strlen(newCpf) != 11)
        {
          printf("\nCPF inválido!\n");
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
      printf("\nOk! O CPF permanecerá %s\n", current->cpf);
    printf("\nVocê gostaria de alterar o cargo desse usuário?(s/n)\n");
    scanf("%c", &choice);
    clearInputBuffer();
    if (choice == 's')
    {
      do
      {
        printf("\nInforme o novo cargo desse usuário:(residente/preceptor) ");
        fgets(newRole, sizeof(newRole), stdin);
        newRole[strcspn(newRole, "\n")] = '\0';
        if (strcmp(newRole, "residente") != 0 && strcmp(newRole, "preceptor") != 0)
          printf("\nCargo inválido! Digite novamente!\n");
      } while (strcmp(newRole, "residente") != 0 && strcmp(newRole, "preceptor") != 0);
      strcpy(current->role, newRole);
    }
    else
      printf("\nOk! O cargo permanecerá %s!\n", current->role);
    printf("\nVocê gostaria de alterar a senha desse usuário?(s/n)\n");
    scanf("%c", &choice);
    clearInputBuffer();
    if (choice == 's')
    {
      printf("Informe a nova senha desse usuário: ");
      fgets(newPassword, sizeof(newPassword), stdin);
      newPassword[strcspn(newPassword, "\n")] = '\0';
      strcpy(current->password, newPassword);
    }
    else
      printf("\nOk! A senha permanecerá %s!", current->password);
    return;
  }

  while (current != NULL && strcmp(current->email, email) != 0)
  { // procurando o usuario para alterar
    current = current->next;
  }

  if (current == NULL)
  {
    printf("O usuário com o email '%s' nao foi encontrado.\n", email);
    return;
  }

  printf("\n\nNome do residente: %s\n", current->name);
  printf("Email do residente: %s\n", current->email);
  printf("CPF do residente: %s\n", current->cpf);
  printf("\nVocê gostaria de alterar o nome desse usuário?(s/n)\n");
  clearInputBuffer();
  scanf("%c", &choice);
  clearInputBuffer();
  if (choice == 's')
  {
    printf("\nInforme o novo nome desse usuário: ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0';
    strcpy(current->name, newName);
  }
  else
    printf("\nOk! O nome permanecerá %s!\n", current->name);
  printf("\nVocê gostaria de alterar o email desse usuário?(s/n)\n");
  scanf("%c", &choice);
  clearInputBuffer();
  if (choice == 's')
  {
    printf("\nInforme o novo email desse usuário: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';
    strcpy(current->email, newEmail);
  }
  else
    printf("\nOk! O email permanecerá %s!\n", current->email);
  printf("\nVocê gostaria de alterar o cpf desse usuário?(s/n)\n");
  scanf("%c", &choice);
  clearInputBuffer();
  if (choice == 's')
  {
    int cpfAux = 0;
    do
    {
      printf("Informe o novo cpf desse usuário: ");
      fgets(newCpf, sizeof(newCpf), stdin);
      if (strlen(newCpf) != 11)
      {
        printf("\nCPF inválido!\n");
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
    printf("\nOk! O CPF permanecerá %s\n", current->cpf);
  printf("\nVocê gostaria de alterar o cargo desse usuário?(s/n)\n");
  scanf(" %c", &choice);
  clearInputBuffer();
  if (choice == 's')
  {
    do
    {
      printf("\nInforme o novo cargo desse usuário:(residente/preceptor) ");
      fgets(newRole, sizeof(newRole), stdin);
      newRole[strcspn(newRole, "\n")] = '\0';
      if (strcmp(newRole, "residente") != 0 && strcmp(newRole, "preceptor") != 0)
        printf("\nCargo inválido! Digite novamente!\n");
    } while (strcmp(newRole, "residente") != 0 && strcmp(newRole, "preceptor") != 0);
    strcpy(current->role, newRole);
  }
  else
    printf("\nOk! O cargo permanecerá %s!\n", current->role);
  printf("\nVocê gostaria de alterar a senha desse usuário?(s/n)\n");
  scanf("%c", &choice);
  clearInputBuffer();
  if (choice == 's')
  {
    printf("Informe a nova senha desse usuário: ");
    fgets(newPassword, sizeof(newPassword), stdin);
    newPassword[strcspn(newPassword, "\n")] = '\0';
    strcpy(current->password, newPassword);
  }
  else
    printf("\nOk! A senha permanecerá %s!", current->password);

  return;
}
#endif
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
