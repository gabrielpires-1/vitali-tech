#include <stdio.h>
#include <string.h>
#include <stdlib.h>

  typedef struct{
    char name[50];
    char email[50];
    char *password;
    char cpf[14];
    int option;
  } register;

  //inserre um novo "perfil" (não sei nome melhor)
  register* createProfile(char name[50], char email[50], char *password, char cpf[14], int option) {
    register* ptr = malloc(sizeof(register));
    if (ptr == NULL) {
        printf("Erro ao tentar criar um novo perfil.\n");
        return NULL;
    }
    strncpy(ptr->name, name, 50);
    strncpy(ptr->email, email, 50);
    ptr->password = strdup(password);
    strncpy(ptr->cpf, cpf, 14);
    ptr->option = option;  

    return ptr;
  }

  //libera a memoria do ponteiro e libera da senha pq strdup() duplica a string
  void freeProfile(register* ptr) {
    free(ptr->password);
    free(ptr);
  }

  //salva o ponteiro no arquivo 
  void storeRegister(register* ptr) {
    
    FILE *Register = fopen("Register.txt", "a");  
    if (Register == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    
    fprintf(Register, "Nome: %s Email: %s Senha: %s Cpf: %s\n", ptr.name, ptr.email, ptr.password, ptr.cpf);
    if(option == 0) {
      fprinf(Register, "Tipo: Residente");
    }else {
      fprintf(Register, "Tipo: Preceptor");
    }
    
    fclose(Register);
  }

int main(void) {
  
  //ainda precisa criar a função que vai colocar os parametros em createProfile
  createProfile();
  
  storeRegister(createProfile());
  
  freeProfile(ptr);

  return 0;
}
