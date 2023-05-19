#include <stdio.h>
#include <string.h>
#include <stdlib.h>

  typedef struct User{
    char name[50];
    char email[50];
    char password[50];
    char cpf[12];
    int option; // 0- residente, 1- preceptor 2 - gestor
  }User;

  //insere um novo "perfil" (não sei nome melhor)
  User * createProfile(char name[50], char email[50], char password[50], char cpf[14], int option) {
    User * ptr = malloc(sizeof(User));
    if (ptr == NULL) {
        printf("Erro ao tentar criar um novo perfil.\n");
        return NULL;
    }

    strncpy(ptr->name, name, 50);
    strncpy(ptr->email, email, 50);
    strncpy(ptr->password, password, 50);
    strncpy(ptr->cpf, cpf, 14);
    ptr->option = option;

    return ptr;
  }

  //libera a memoria do ponteiro e libera da senha pq strdup() duplica a string
  void freeProfile(User* ptr) {
    free(ptr);
  }

  //salva o ponteiro no arquivo 
  void storeRegister(User* ptr, int option) {
    
    FILE *Register = fopen("Register.txt", "a");  
    if (Register == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    
    fprintf(Register, "Nome: %s Email: %s Senha: %s Cpf: %s\n", ptr->name, ptr->email, ptr->password, ptr->cpf);
    if(option == 0) {
      fprintf(Register, "Tipo: Residente\n");
    }else {
      fprintf(Register, "Tipo: Preceptor\n");
    }
    
    fclose(Register);
  }

int main() {
  
  //ainda precisa criar a função que vai colocar os parametros em createProfile
  //createProfile("gabriel","email@email.com", "senha123", "111111", 1);
  
  storeRegister(createProfile("gabriel","email@email.com", "senha123", "11111111111", 1), 1);
  
  //freeProfile(ptr);

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