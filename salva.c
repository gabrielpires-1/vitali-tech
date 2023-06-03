
void printEvaluations(char *residenteEmail){
  FILE *fileActivities;
  fileActivities = fopen("notas.txt", "r");
  char line[2000];
  int activiesNumber = 0;

  if (fileActivities == NULL) {
    printf("Failed to open the file.\n");
    return;  
  }

  while (fgets(line, sizeof(line), fileActivities)) {
    char *token = strtok(line, ";");
        int i = 0;

        char preceptor[100];
        char residente[100];
        char atividade[100];
        char criterios[12][100];
        char notas[12][100];
        char notaFinal[20];

        while (token != NULL) {
            switch (i) {
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
                    if (i % 4 == 3) {
                        
                        strcpy(notas[i/4 - 1], token);
                    } else if (i % 4 == 0) {
                        strcpy(criterios[i/4 - 1], token);
                    } else if (i == 46) {
                        strcpy(notaFinal, token);
                    }
                    break;
            }

            token = strtok(NULL, ";");
            i++;
        }

        if (strcmp(residente, residenteEmail) == 0) {
          activiesNumber++;
          printf("\nPreceptor: %s, Residente: %s, Nome da atividade: %s\n\n", preceptor, residente, atividade);
          for (int j = 0; j < 12; j++) {
            printf("%s, Nota: %s\n", criterios[j], notas[j]);
          }
          printf("Nota Final: %s\n", notaFinal);
        }

  }

  if(activiesNumber == 0){
    printf("Você não possui nenhuma atividade no momento!\n");
  }

  fclose(fileActivities);

}