#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

  typedef struct User{
    char * name;
    char * email;
    char * password;
    char * cpf;
    int option; // 0- residente, 1- preceptor 2 - gestor
  }User;

  //insere um novo "usuário"
  User * createProfile(char *name, char *email, char *password, char *cpf, int option) {
    User * ptr = malloc(sizeof(User));
    if (ptr == NULL) {
        printf("Erro ao tentar criar um novo perfil.\n");
        return NULL;
    }

    ptr->name = malloc(strlen(name) + 1);
    strncpy(ptr->name, name, strlen(name) + 1);

    ptr->email = malloc(strlen(email) + 1);
    strncpy(ptr->email, email, strlen(email) + 1);

    ptr->password = malloc(strlen(password) + 1);
    strncpy(ptr->password, password, strlen(password) + 1);

    ptr->cpf = malloc(strlen(cpf) + 1);
    strncpy(ptr->cpf, cpf, strlen(cpf) + 1);

    return ptr;
  }

  //libera a memoria do ponteiro e libera da senha pq strdup() duplica a string
  void freeProfile(User* ptr) {
    free(ptr->name);
    free(ptr->email);
    free(ptr->password);
    free(ptr->cpf);
    free(ptr);
  }

  //salva o usuário no arquivo
  void storeRegister(User* ptr) {
    FILE* Register = fopen("Register.dat", "w");
    if (Register == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    if (fwrite(ptr, sizeof(User), 1, Register) != 1) {
        printf("Erro ao gravar o usuário no arquivo.\n");
        fclose(Register);
        return;
    }

    printf("Usuário cadastrado com sucesso!\n");

    fclose(Register);
}

int main() {
  char email[21];
  char password[9];
  User usr;
  FILE *fp;

  //ainda precisa criar a função que vai colocar os parametros em createProfile
  storeRegister(createProfile("diretor","diretor@hospital.com", "senha123", "99999999999", 2));
  storeRegister(createProfile("claudio","claudio@hospital.com", "senha123", "99999999999", 1));
  storeRegister(createProfile("roberta","roberta@hospital.com", "senha123", "99999999999", 0));

  printf("Seja bem-vindo ao VitaliJourney!\n\nLogin (email):");
  scanf("%s", email);
  printf("Senha: ");
  scanf("%s", password);

  fp = fopen("Register.dat","r");
			while(fread(&usr,sizeof(User),1,fp)){
				if(!strcmp(usr.email,email)){
					if(!strcmp(usr.password,password)){
						system("cls");
						printf("\n\t\t\t\t\t\tBem vindo, %s!",usr.name);
						printf("\n|Email:\t\t%s",usr.email);
						printf("\n|CPF:\t%s",usr.cpf);
						if(usr.option == 2) printf("\n|Função: Diretor do Hospital\t%s");
                        if(usr.option == 1) printf("\n|Função: Preceptor\t%s");
                        if(usr.option == 0) printf("\n|Função: Residente\t%s");
					}
					else {
						printf("\n\nInvalid Password!");
						Beep(800,300);
					}
			fclose(fp);
      }
  //storeRegister(createProfile("gabriel","email@email.com", "senha123", "11111111111", 1), 1);

  //freeProfile(ptr);
      }
  return 0;
}

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
