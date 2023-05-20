#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "lib.h"

int main() {
  char email[50];
  char password[50];
  system("color 0b");
  system("cls");
  User * usr = malloc(sizeof(User));;
  usr->name = malloc(51 * sizeof(char));
  usr->email = malloc(51 * sizeof(char));
  usr->password = malloc(51 * sizeof(char));
  usr->cpf = malloc(12 * sizeof(char));
  usr->role = malloc(51 * sizeof(char));

  // use o código abaixo para criar um diretor, caso o txt seja apagado.
  // storeRegister(createProfile("diretor","diretor@hospital.com", "senha123", "99999999999", "gestor"));

  int isLoggedIn = 0;
  do {
  printf("\t\t\tSeja bem-vindo ao VitaliJourney! Seu hospital virtual!\n\nLogin (email):");
  scanf("%s", email);
  printf("Senha: ");
  scanf("%s", password);

  if(isLoggedIn = login(email, password, usr)){
    system("cls");
		printf("\n\t\t\tBem vindo, %s!",usr->name);
		printf("\n|Email:\t\t%s",usr->email);
		printf("\n|CPF:\t\t%s",usr->cpf);
		printf("\n|Cargo: \t%s", usr->role);
    if(!strcmp(usr->role, "gestor")){
      int choice;
      menu:
      printf("\n\n\t\t\tO que voce gostaria de fazer hoje?\n");
      printf("1 - Cadastrar um novo residente ou preceptor\n");
      printf("2 - Apagar um residente ou preceptor do sistema\n");
      printf("3 - Visualizar lista de residentes cadastrados no sistema\n");
      printf("4 - Visualizar lista de preceptores cadastrados no sistema\n");
      printf("5 - sair do programa\n");
      scanf("%d", &choice);
      User * newUser = malloc(sizeof(User));
      switch (choice) {
        case 1:
          newUser->name = malloc(51 * sizeof(char));
          newUser->email = malloc(51 * sizeof(char));
          newUser->password = malloc(51 * sizeof(char));
          newUser->cpf = malloc(12 * sizeof(char));
          newUser->role = malloc(51 * sizeof(char));
		      printf("\n\t\t\tVamos cadastrar um novo usuario!");
          printf("Qual o nome do usuario?\n");
          scanf("%s", newUser->name);
          printf("Qual sera o email do usuario?\n");
          scanf("%s", newUser->email);
          printf("Qual sera a senha do usuario?\n");
          scanf("%s", newUser->password);
          printf("Qual eh o CPF do usuario?\n");
          scanf("%s", newUser->cpf);
          printf("Qual eh o cargo do usuario? (Digite \"preceptor\" ou \"residente)");
          scanf("%s", newUser->role);
          storeRegister(newUser);
          system("cls");
          printf("Usuário cadastrado com sucesso no sistema!\n");
          goto menu;
          break;
        // DANILO E TOM VÃO IMPLEMENTAR ESSA FUNCIONALIDADE
        case 2:
          system("cls");
		      printf("\n\t\t\tVamos apagar um usuario do sistema!",usr->name);
          printf("Qual o nome do usuario?\n");
          printf("Qual eh o email do usuario?\n");
          printf("Qual eh o CPF do usuario?\n");
          break;
        case 3:
          system("cls");
		      list("residente");
          break;
        case 4:
          system("cls");
		      list("preceptor");
          break;
        case 5:
          system("cls");
          freeProfile(usr); // libera a memória alocada para encontrar o usuário
		      exit(1);
          break;
      }
    }
      // caso o usuário seja um preceptor, esse bloco de código será executado.
         else if (!strcmp(usr->role,"preceptor")) {
        printf("\n\n\t\t\tO que voce gostaria de fazer hoje?\n");
        printf("1 - Aba de notas\n");
        printf("2 - Aba de feedbacks\n");
        printf("3 - Sair do programa\n");
      }
      // caso o usuário seja um residente, esse bloco de código será executado.
      else if (!strcmp(usr->role,"residente")){
        printf("\n\n\t\t\tO que voce gostaria de fazer hoje?\n");
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
preceptores, residentes e gestores terão um cadastro(0 - residente, 1 - preceptor 2 - gestor)
especificar no readme isso de cada um ter seu cadastro
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
      -(0-5)o residente conseguiu passar confiança dos conteudos aprendidos na faculdade?
      -(0-5) outras perguntas (vamo ver ainda as perguntas)
      Tags:
      -deseja inserir alguma tag pra complementar a avaliação?
      Exemplos:
      -o residente nao conseguiu se comunicar de forma eficiente com seus colegas
      -o residente nao passou confiança dos conhecimentos aprendidos na faculdade

    2- aba de feedbacks
      -exibir feedbacks do usuario
      1- deseja enviar algum feedback?
      -digite o nome da pessoa a quem voce deseja enviar
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
      -digite o nome da pessoa a quem voce deseja enviar
      -insira tag:
      Exemplo:
      -comunicativo
      -dedicado
      -atencioso
      -disperso
      -mais tags(fica num array de strings ou numa lista)
  3- sair
*/
