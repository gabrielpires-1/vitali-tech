#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int choice;

int main() {
  setlocale(LC_ALL, "Portuguese_Brazil");
  char email[50];
  char password[50];
  char newName[50], newEmail[50], newPassword[50], newCpf[12], newRole[50];
  char delName[50], delEmail[50];
  system("color 0b");
  system("cls");
  User *usr = malloc(sizeof(User));
  usr->name = malloc(51 * sizeof(char));
  usr->email = malloc(51 * sizeof(char));
  usr->password = malloc(51 * sizeof(char));
  usr->cpf = malloc(12 * sizeof(char));
  usr->role = malloc(51 * sizeof(char));
  User *head = NULL;
  create_list(&head);
  // use o código abaixo para criar um gestor, caso o txt seja apagado.
  // storeRegister(createUser("diretor","diretor@hospital.com", "senha123", "99999999999", "gestor"));

  int isLoggedIn = 0, cpfAux = 0;

  printf("\t\t\tSeja bem-vindo ao VitaliJourney! Seu hospital virtual!\n");
  do {  
    printf("\nLogin (email):");
    scanf("%s", email);
    printf("Senha: ");
    scanf("%s", password);

    if (isLoggedIn = login(email, password, usr)) {
      system("cls");
      printf("\n\t\t\tBem vindo, %s!", usr->name);
      printf("\n|Email:\t\t%s", usr->email);
      printf("\n|CPF:\t\t%s", usr->cpf);
      printf("\n|Cargo: \t%s", usr->role);
      if (!strcmp(usr->role, "gestor")) {
        //Coloquei o choise como varivel global
      menu:
        system("cls");
        printf("\t\t\tO que voc� gostaria de fazer %s?\n", usr->name);
        printf("1 - Cadastrar um novo residente ou preceptor\n");
        printf("2 - Apagar um residente ou preceptor do sistema\n");
        printf("3 - Visualizar lista de residentes cadastrados no sistema\n");
        printf("4 - Visualizar lista de preceptores cadastrados no sistema\n");
        printf("5 - sair do programa\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
          printf("\n\t\t\tVamos cadastrar um novo usu�rio!\n");
          printf("Qual o nome do usu�rio?\n");
          scanf("%s", newName);
          printf("Qual ser� o email do usu�rio?\n");
          scanf("%s", newEmail);
          printf("Qual ser� a senha do usu�rio?\n");
          scanf("%s", newPassword);
          do {
            printf("Qual � o CPF do usu�rio?\n");
            scanf("%s", newCpf);
            if (strlen(newCpf) != 11) {
              printf("CPF inv�lido!\n");
              cpfAux = 1;
            } else {
              cpfAux = 0;
            }
          } while (cpfAux);
          printf("Qual � o cargo do usu�rio? (Digite \"preceptor\" ou \"residente\")");
          scanf("%s", newRole);

          User *newUser = createUser(newName, newEmail, newPassword, newCpf, newRole);
          append(&head, newUser->name,newUser->email, newUser->password, newUser->cpf, newUser->role);
          saveList(&head);
          freeUser(newUser);
          goto menu;
          break;

        // DANILO E TOM VÃO IMPLEMENTAR ESSA FUNCIONALIDADE
        case 2: {
          printf("\n\t\t\tVamos apagar um usu�rio do sistema!\n");
          printf("Digite o nome do perfil a ser removido:\n");
          scanf("%s", delName);
          printf("Digite o e-mail do perfil a ser removido:\n");
          scanf("%s", delEmail);

          deleteByName(&head, delName);
          saveList(&head);

          goto menu;
          break;
        }
        case 3:
          system("cls");
          printList(head, "residente");
          pause();
          goto menu;
          break;
        case 4:
          system("cls");
          printList(head, "preceptor");
          pause();
          goto menu;
          break;
        case 5:
          system("cls");
          freeUser(usr); // libera a memória alocada para encontrar o usu�rio
          exit(1);
          break;
        }
      }
      // caso o usuário seja um preceptor, esse bloco de código ser� executado.
      else if (!strcmp(usr->role, "preceptor")) {
        printf("\n\n\t\t\tO que voc� gostaria de fazer hoje?\n");
        printf("1 - Aba de notas\n");
        printf("2 - Aba de feedbacks\n");
        printf("3 - Sair do programa\n");
        scanf("%i",&choice);
        switch (choice)
        {
        case 1:
          system("cls");
          printList(head, "residente");
          break;
        
        default:
          break;
        }
      }
      // caso o usuário seja um residente, esse bloco de código ser� executado.
      else if (!strcmp(usr->role, "residente")) {
        printf("\n\n\t\t\tO que você gostaria de fazer hoje?\n");
        printf("1 - Aba de notas\n");
        printf("2 - Aba de feedbacks\n");
        printf("3 - Sair do programa\n");
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

  -Menu preceptor
    1- aba de avaliação(notas)
      Criterios:
      Exemplo:
      -(0-5) Comunicação
      -(0-5) outros criterios(olhar no notion os criterios de avaliação)
      -perguntas norteadoras(responder de 0 a 5):
      Exemplo:
      -(0-5)o residente se mostrou capaz de se comunicar bem com seus colegas?
      -(0-5)o residente conseguiu passar confiança dos conteudos aprendidos na
faculdade?
      -(0-5) outras perguntas (vamo ver ainda as perguntas)
      Tags:
      -deseja inserir alguma tag pra complementar a avaliação?
      Exemplos:
      -o residente nao conseguiu se comunicar de forma eficiente com seus
colegas -o residente nao passou confiança dos conhecimentos aprendidos na
faculdade

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
