#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>

int choice;

int main() {
  setlocale(LC_ALL, "Portuguese_Brazil");
  char email[50];
  char password[50];
  char newName[50], newEmail[50], newPassword[50], newCpf[12], newRole[50];
  char delName[50], delEmail[50], nome[50],activityName[70],grade[10],tag[20], confirm_user, confirm_feedback, ch, receiver_name[100];;
  int i = 0, cont_comments = 0;
  system("color 0b");
  clearScreen();
  User *usr = (User *)malloc(sizeof(User));
  allocMemoryForUser(usr);
  User *head = NULL;
  Feedbacks * feedback = NULL;
  create_list(&head);

  // use o código abaixo para criar um gestor, caso o txt seja apagado.
  // storeRegister(createUser("diretor","diretor@hospital.com", "senha123", "99999999999", "gestor"));

  int isLoggedIn = 0, cpfAux = 0;

  printf("\t\t\tSeja bem-vindo ao VitaliJourney! Seu hospital virtual!\n");
  do {  
    printf("\nLogin (email):");
    scanf("%s", email);
    printf("Senha: ");
    
    // Aparecer * na senha
    while (1) {
      ch = getch();

      if (ch == 13) {  // Verifica se Enter foi pressionada, em relação a tabela ascii
        password[i] = '\0';  // Termina a string
        i = 0; // Zera os caracters da strings
        break;
      }

      if (ch == 8) {  // Verifica se a tecla de voltar caracter foi pressionada, em relação a tabela ascii
        if (i > 0) {
          printf("\b \b");  // Apaga o último caractere
          i--;
        }
      } else {
        password[i] = ch;
        printf("*");  // Mostra o * ao inves do caracter
        i++;
      }
    }

    if (isLoggedIn = login(email, password, usr)) {
      clearScreen();
      printf("\n\t\t\tBem vindo, %s!", usr->name);
      printf("\n|Email:\t\t%s", usr->email);
      printf("\n|CPF:\t\t%s", usr->cpf);
      printf("\n|Cargo: \t%s", usr->role);

      //Interface do gestor
      if (!strcmp(usr->role, "gestor")) {
        //Coloquei o choise como varivel global
      managementMenu:
        clearScreen();
        printf("\t\t\tO que voce gostaria de fazer %s?\n", usr->name);
        printf("1 - Cadastrar um novo residente ou preceptor\n");
        printf("2 - Apagar um residente ou preceptor do sistema\n");
        printf("3 - Alterar um usuario existente\n");
        printf("4 - Visualizar lista de residentes cadastrados no sistema\n");
        printf("5 - Visualizar lista de preceptores cadastrados no sistema\n");
        printf("6 - sair do programa\n");
        scanf("%d", &choice);
        switch (choice) {
        //cadastrar usuarios:
        case 1:
          clearScreen();
          printf("\n\t\t\tVamos cadastrar um novo usuario!\n");
          printf("Qual o nome do usuario?\n");
          scanf("%s", newName);
          printf("Qual o email do usuario?\n");
          scanf("%s", newEmail);
          printf("Qual a senha do usuario?\n");
          scanf("%s", newPassword);
          do {
            printf("Qual o CPF do usuario?\n");
            scanf("%s", newCpf);
            if (strlen(newCpf) != 11) {
              printf("CPF invalido!\n");
              cpfAux = 1;
            } else {
              cpfAux = 0;
            }
          } while (cpfAux);
          printf("Qual o cargo do usuario? (Digite \"preceptor\" ou \"residente\")");
          scanf("%s", newRole);

          User *newUser = createUser(newName, newEmail, newPassword, newCpf, newRole);
          append(&head, newUser->name,newUser->email, newUser->password, newUser->cpf, newUser->role);
          saveList(&head, "Register.txt");
          freeUser(newUser);
          goto managementMenu;
          break;
        //deletar usuarios:
        case 2: 
          clearScreen();
          printf("\n\t\t\tVamos apagar um usuario do sistema!\n");
          printf("Digite o nome do perfil a ser removido:\n");
          scanf("%s", delName);
          fflush(stdin);
          printf("Digite o e-mail do perfil a ser removido:\n");
          scanf("%s", delEmail);
          fflush(stdin);
          printf("Tem certeza que deseja apagar o usuario %s com o email %s[s/n]?\n", delName, delEmail);
          scanf("%c", &confirm_user);
          fflush(stdin);

          if (confirm_user == 's'   || confirm_user == 'S' ) {

            if (check_delete(delName, delEmail, head)) {
              deleteByName(&head, delName);
              saveList(&head, "Register.txt");
              printf("Usuario removido com sucesso.\n");

            } else {
              printf("Usuario nao encontrado. Remoçao cancelada.\n");
            }
          } else if (confirm_user == 'n'   || confirm_user == 'N' ) {
            printf("Operaçao de exclusao cancelada pelo usuario.\n");

          } else {
            printf("Opçao invalida. Operaçao de exclusao cancelada.\n");
          }
          pause();

          goto managementMenu;
          break;
        
        // Alterar um usuário já existente
        case 3:
          clearScreen();
          printf("Qual o email do usuario que voce gostaria de alterar os dados?\n");
          scanf("%s", email);
          if(1){
          changeUser(&head, email);
          saveList(&head, "Register.txt");
          }
          pause();
          goto managementMenu;
          break;
        //Visualizar lista de residentes cadastrados no sistema
        case 4:
          clearScreen();
          printList(head, "residente", 1);
          pause();
          goto managementMenu;
          break;
        //Visualizar lista de preceptores cadastrados no sistema
        case 5:
          clearScreen();
          printList(head, "preceptor", 1);
          pause();
          goto managementMenu;
          break;
        case 6:
          clearScreen();
          freeUser(usr); // libera a memória alocada para encontrar o usu�rio
          freelist(&head);
          exit(1);
          break;
        default:
          printf("\nInforme um comando valido! ");
          pause();
          goto managementMenu;
          break;
        }
      }
      // caso o usuário seja um Preceptor, esse bloco de código será executado.
      else if (!strcmp(usr->role, "preceptor")) {
        preceptorMenu:
        clearScreen();
        Evaluations *Epointer = (Evaluations *) malloc(sizeof(Evaluations));
        Epointer->activityName =malloc(strlen(activityName));
        Epointer->grade = malloc(strlen(grade));
        Epointer->tag = malloc(strlen(tag));
        printf("\n\n\t\t\tO que voce gostaria de fazer hoje?\n");
        printf("1 - Aba de notas\n");
        printf("2 - Aba de feedbacks\n");
        printf("3 - Sair do programa\n");
        scanf("%d",&choice);
        switch (choice) {
        case 1:
          clearScreen();
          printList(head, "residente", 1);
          printf("Insira o e-mail do residente que desejas avaliar: \n");
          scanf("%s",email);
          if (check_email(email, head)!=0)
          {
            residentEvaluation(&head,email, "residente", usr->name, Epointer);
          }else
          {
            while(check_email(email,head)==0)
            {
              printf("E-mail invalido!\n");
              printf("Insira um e-mail valido do residente que desejas avaliar: \n");
              scanf("%s",email);
              
            }
            residentEvaluation(&head,email, "residente", usr->name, Epointer);
          }
          printf("Avaliaçao realizada!\n");
          pause();
          goto preceptorMenu;
          break;

        case 2:
          clearScreen();
          //imprimir lista de feedback
          printf("seus feedbacks:\n\n");
          printFeedbacksByName(usr->name);


          printf("Gostaria de enviar algum feedback?[s/n]\n");
          scanf(" %c", &confirm_feedback);

          if(confirm_feedback == 's' || confirm_feedback == 'S')
          {
            clearScreen();
            printf("Seus residentes:\n");
            printList(head, "residente", 0);

            printf("Digite o nome do residente que gostaria de enviar um feedback:\n");
            scanf(" %[^\n]s", receiver_name);
            User * receiver = findUserByName(head, receiver_name);

            if(receiver == NULL)
            {
              printf("Usuario nao encontrado\n");

            }else if (strcmp(receiver->role, "preceptor") == 0 || strcmp(receiver->role, "gestor") == 0)
            {
              printf("O usuario que voce digitou nao e um residente\n");
            }
            
            else 
            {
              create_feedback(&feedback, usr, receiver);
            }
            

          }else if (confirm_feedback == 'n' || confirm_feedback == 'N')
          {
            pause();
            goto preceptorMenu;
            break;
          }
          else printf("Opçao invalida!\n");
          
          
          pause();
          goto preceptorMenu;
          break;

        case 3:
          freelist(&head);
          exit(1);
          break;
        
        default:
          printf("\nInforme um comando valido! ");
          pause();
          goto preceptorMenu;
          break;
        }
      }
      // caso o usuário seja um residente, esse bloco de código ser� executado.
      else if (!strcmp(usr->role, "residente")) {
        residenteMenu:
        printf("\n\n\t\t\tO que voce gostaria de fazer hoje?\n");
        printf("1 - Aba de notas\n"); //visualizar
        printf("2 - Aba de feedbacks\n"); //igual preceptor, mas so pode enviar feedbacks a precetores
        printf("3 - Sair do programa\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
          printEvaluations("gabi@hospital.com");
          pause();
          goto residenteMenu;
          break;
        
        case 2:
          clearScreen();
          printf("Seus feedbacks:\n");
          printFeedbacksByName(usr->name);

          printf("Gostaria de enviar algum feedback?[s/n]\n");
          scanf(" %c", &confirm_feedback);

          if(confirm_feedback == 's' || confirm_feedback == 'S')
          {
            clearScreen();
            printf("Seus preceptores:\n");
            printList(head, "preceptor", 0);

            printf("Digite o nome do preceptor que gostaria de enviar um feedback:\n");
            scanf(" %[^\n]s", receiver_name);

            User * receiver = findUserByName(head, receiver_name);

            if(receiver == NULL) printf("Usuario nao encontrado\n");

            else if (strcmp(receiver->role, "residente") == 0 || strcmp(receiver->role, "gestor") == 0)
            {
              printf("O usuario que voce digitou nao e um preceptor\n");
            }
            
            else create_feedback(&feedback, usr, receiver);
            
            

          }else if (confirm_feedback == 'n' || confirm_feedback == 'N')
          {
            pause();
            goto preceptorMenu;
            break;
          }
          else printf("Opçao invalida!\n");
          
          
          pause();
          goto preceptorMenu;
          break;

        case 3:
          freelist(&head);
          exit(0);

        default:
          printf("\nInforme um comando valido! ");
          pause();
          goto residenteMenu;
          break;
        }
      }
    }
  } while (isLoggedIn == 0);
  return 0;
}

/*
Arquivo txt:
Nome, Email, senha, cpf, função (gestor, residente, preceptor)


*/

/*Arquitetura do codigo:
1 arquivo main
1 arquivo da biblioteca com as funcoes
1 arquivo header
um txt com os cadastros
preceptores, residentes e gestores terão um cadastro(0 - residente, 1 -
preceptor 2 - gestor) especificar no readme isso de cada um ter seu cadastro
Formatação do TXT(exemplo):
Nome: gabriel Email: email@email.com Senha: senha123 Cpf: 111111
Tipo: Preceptor
Como vai funcionar a main:
estilo menu

  -Login
  -primeira pagina da main(login):
    inserir email:
    inserir senha:

  -Menu Gestor
    1- cadastrar residente
      -insira nome:
      -insira email:
      -insira senha:
      -insira cpf:
      option = 0;(nao aparece isso na interface, so no codigo)
    2- cadastrar preceptor
    insira nome:
      -insira email:
      -insira senha:
      -insira cpf:
      option = 1;(nao aparece isso na interface, so no codigo)
    3- apagar user
      -digite o email e o cpf da conta:
      -apaga no txt
    4- sair

--Menu preceptor
    1- aba de avaliação(notas)
      Criterios:
      Exemplo:
      -(0-5) Comunicação
      -(0-5) outros criterios(olhar no notion os criterios de avaliação)
      -perguntas norteadoras(responder de 0 a 5):
      Exemplo:
      -(0-5)o residente se mostrou capaz de se comunicar bem com seus colegas?
      -(0-5)o residente conseguiu passar confiança dos conteudos aprendidos na faculdade?
      -(0-5) outras perguntas (vamo ver ainda as perguntas)
      Tags:
      -deseja inserir alguma tag pra complementar a avaliação?
      Exemplos:
      -o residente nao conseguiu se comunicar de forma eficiente com seus
colegas -o residente nao passou confiança dos conhecimentos aprendidos na
faculdade

    2- ABA de feedbacks
      -exibir feedbacks do usuario 
      1- deseja enviar algum feedback?
      -digite o nome da pessoa a quem voc� deseja enviar -> procura no arquivo a pessoa
      -insira ou selecione tag (nao sei qual fica melhor)
      Exemplos:
      -comunicativo
      -dedicado
      -atencioso
      -disperso
      -mais tags(fica num array de strings ou numa lista)
    3- sair

  -Menu residente
  1- aba de avaliações(notas + comentarios)
  - imprimir notas + tags
  2- aba de feedbacks
   -exibir feedbacks do usuario
      1- deseja enviar algum feedback?
      -digite o nome da pessoa a quem voc� deseja enviar
      -insira tag:
      Exemplo:
      -comunicativo
      -dedicado
      -atencioso
      -disperso
      -mais tags(fica num array de strings ou numa lista)
  3- sair
*/
