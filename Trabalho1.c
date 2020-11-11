#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct rotulos_lista{
	char nome[52];
	int valor;
	struct rotulos_lista *proximo;
};

struct macro_lista{
	char nome[52];
	char instruct[52];
	int rotulo;
	int valor;
	struct macro_lista *proximo;
};

int checa(char *leitura){
	int i;
	for (i = 0; ((i < 52) && (leitura[i] != NULL)); ++i){
		leitura[i] = toupper(leitura[i]);
	}
	if (leitura[0] == ';' || leitura[i-1] == ';'){
		return 99;
	}
	if(leitura[i-1] == ':'){
		return 98;
	}
	if (strcmp(leitura, "ADD") == 0){
		return 0;
	}
	if (strcmp(leitura, "SUB") == 0){
		return 1;
	}
	if (strcmp(leitura, "MULT") == 0){
		return 2;
	}
	if (strcmp(leitura, "DIV") == 0){
		return 3;
	}
	if (strcmp(leitura, "JMP") == 0){
		return 4;
	}
	if (strcmp(leitura, "JMPN") == 0){
		return 5;
	}
	if (strcmp(leitura, "JMPP") == 0){
		return 6;
	}
	if (strcmp(leitura, "JMPZ") == 0){
		return 7;
	}
	if (strcmp(leitura, "COPY") == 0){
		return 8;
	}
	if (strcmp(leitura, "LOAD") == 0){
		return 9;
	}
	if (strcmp(leitura, "STORE") == 0){
		return 10;
	}
	if (strcmp(leitura, "INPUT") == 0){
		return 11;
	}
	if (strcmp(leitura, "OUTPUT") == 0){
		return 12;
	}
	if (strcmp(leitura, "STOP") == 0){
		return 13;
	}
	if (strcmp(leitura, "SECTION") == 0){
		return 14;
	}
	if (strcmp(leitura, "SPACE") == 0){
		return 15;
	}
	if (strcmp(leitura, "CONST") == 0){
		return 16;
	}
	if (strcmp(leitura, "EQU") == 0){
		return 17;
	}
	if (strcmp(leitura, "IF") == 0){
		return 18;
	}
	if (strcmp(leitura, "MACRO") == 0){
		return 19;
	}
	if (strcmp(leitura, "ENDMACRO") == 0){
		return 20;
	}
	else{
		return 21;
	}

}

int checa_operandos(int mnemonico){
	if((mnemonico >= 0 && mnemonico <= 7) || (mnemonico >= 9 && mnemonico <= 12) || mnemonico == 14 || (mnemonico >= 16 && mnemonico <= 18)){
		return 1;
	}
	else{
		if (mnemonico == 8){
			return 2;
		}
		else{
			return 0;
		}
	}
}

int checa_tamanho(int mnemonico){
	if(mnemonico == 13 || mnemonico == 15 || mnemonico == 16){
		return 1;
	}
	if((mnemonico >= 0 && mnemonico <=7) || (mnemonico >=9 && mnemonico <=12)){
		return 2;
	}
	if(mnemonico == 8){
		return 3;
	}
	else{
		return 0;
	}
}

void cria_no(struct rotulos_lista *inicio, char *leitura, int valor){
	struct rotulos_lista *atual;
	int i = 0;

	while(i < 52 && leitura[i] != NULL){
		i++;
	}
	leitura[i-1] = leitura[i];
	atual = inicio;
	while(atual->proximo != NULL){
		atual = atual->proximo;
	}
	atual->proximo = (struct rotulos_lista*)malloc(sizeof(struct rotulos_lista));
	atual->proximo->proximo = NULL;
	strcpy(atual->nome, leitura);
	atual->valor = valor;
}

void cria_no_macro(struct macro_lista *inicio, char *leitura, char *instruct, int rotulo, int numero){
	struct macro_lista *atual;
	int i;

	while(i<52 && leitura[i] != NULL){
		i++;
	}
	leitura[i-1] = leitura[i];
	atual = inicio;
	while(atual->proximo != NULL){
		atual = atual->proximo;
	}
	atual->proximo = (struct macro_lista*)malloc(sizeof(struct macro_lista));
	atual->proximo->proximo = NULL;
	strcpy(atual->nome, leitura);
	strcpy(atual->instruct, instruct);
	atual->rotulo;
	atual->valor = numero;
}

struct rotulos_lista* percorre_lista(struct rotulos_lista *inicio, char *rotulo){
	struct rotulos_lista *atual;

	atual = inicio;
	while(atual->proximo != NULL && strcmp(atual->nome, rotulo) != 0){
		atual = atual->proximo;
	}
	return atual;
}

struct macro_lista* percorre_lista_macro(struct macro_lista *inicio, char *rotulo){
	struct macro_lista *atual;

	atual = inicio;
	while(atual->proximo != NULL && strcmp(atual->nome, rotulo) != 0){
		atual = atual->proximo;
	}
	return atual;
}

void instruct(FILE *arq, FILE *arq2, char *leitura, int mnemonico){
	int operandos, i;

	fprintf(arq2, "%s ", leitura);
			operandos = checa_operandos(mnemonico);
			for (i = 0; i < operandos; ++i){
				fscanf(arq, "%s", leitura);
				fprintf(arq2, "%s ", leitura);
			}
			fprintf(arq2, "\n");
}

int if_condition(FILE *arq, struct rotulos_lista *inicio){
	struct rotulos_lista *percorre;
	char leitura[52];


	fscanf(arq, "%s", leitura);
	checa(leitura);
	percorre = percorre_lista(inicio, leitura);
	if(percorre->valor == 0){
		while(fgetc(arq) != '\n');
		while(fgetc(arq) != '\n');
		return 0;
	}
	return 1;
}

void rotulo(FILE *arq, FILE *arq2, char *leitura, struct rotulos_lista *inicio, struct macro_lista *inicio2){
	struct rotulos_lista *percorre;
	char proximo[52];
	int mnemonico, operandos, i, contador;

	fscanf(arq, "%s", proximo);
	mnemonico = checa(proximo);
	if(mnemonico == 17){
		fscanf(arq, "%s", proximo);
		cria_no(inicio, leitura, atoi(proximo));	
	}
	else{
		if(mnemonico >= 0 && mnemonico <= 16){
			fprintf(arq2, "%s ", leitura);
			instruct(arq, arq2, proximo, mnemonico);
		}
		if(mnemonico == 19){
			while(mnemonico != 20){
				fscanf(arq, "%s", proximo);
				mnemonico = checa(proximo);
				if(mnemonico == 99){
					while(fgetc(arq) != '\n');
				}
				if(mnemonico >= 0 && mnemonico <= 16){
					cria_no_macro(inicio2, leitura, proximo, 0, 0);	
					operandos = checa_operandos(mnemonico);
					for (i = 0; i < operandos; ++i){
						fscanf(arq, "%s", proximo);
						mnemonico = checa(proximo);
						if(mnemonico == 21){
							percorre = percorre_lista(inicio, proximo);
							if(strcmp(percorre->nome, proximo) == 0){
								cria_no_macro(inicio2, leitura, leitura, 1, percorre->valor);
							}
							else{
								cria_no_macro(inicio2, leitura, proximo,0,0);
							}
						}
						else{
							cria_no_macro(inicio2, leitura, proximo, 0, 0);
						}
					}
				}
				if(mnemonico == 18){
					fscanf(arq, "%s", proximo);
					checa(proximo);
					percorre = percorre_lista(inicio, proximo);
					if(percorre->valor == 0){
						while(fgetc(arq) != '\n');
						while(fgetc(arq) != '\n');
					}
				} 
			}
		}
	}
}



int pre_processa(FILE *arq, FILE *arq2){
	struct rotulos_lista *inicio = NULL, *percorre;
	struct macro_lista *inicio2 = NULL, *percorre2;
	char leitura[52], macro[52];
	int mnemonico, operandos, i;

	inicio = (struct rotulos_lista*)malloc(sizeof(struct rotulos_lista));
	inicio->proximo = NULL;
	inicio2 = (struct macro_lista*)malloc(sizeof(struct macro_lista));
	inicio2->proximo = NULL;


	while(fscanf(arq, "%s", leitura) != EOF){
		mnemonico = checa(leitura);
		if(mnemonico>=0 && mnemonico <=16){
			instruct(arq, arq2, leitura, mnemonico);
		}
		if(mnemonico == 18){
			if_condition(arq, inicio);
		}
		if(mnemonico == 98){
			rotulo(arq, arq2, leitura, inicio, inicio2);
		}
		if(mnemonico == 99){
			while(fgetc(arq) != '\n');
		}
		if(mnemonico == 21){
			percorre2 = percorre_lista_macro(inicio2, leitura);
			while(percorre2->proximo != NULL && strcmp(percorre2->nome, leitura) == 0){
				fprintf(arq2, "%s ", percorre2->instruct);
				operandos=checa_operandos(checa(percorre2->instruct));
				for (i = 0; i < operandos; ++i){
					percorre2 = percorre2->proximo;
					if(percorre2->rotulo == 0){
						fprintf(arq2, "%s ", percorre2->instruct);
					}
					if(percorre2->rotulo == 1){
						fprintf(arq2, "%d ", percorre2->valor);	
					}
				}
				fprintf(arq2, "\n");
				percorre2 = percorre2->proximo;
			}
		}
	}
	return 0;
}

int monta(FILE *arq, FILE *arq2){
	struct rotulos_lista *inicio, *percorre;
	char leitura[52], transfere[52], rotulo[52];
	int mnemonico, operandos, i = 0, j, k, tamanho = 0, passagem=0;
	
	inicio = (struct rotulos_lista*)malloc(sizeof(struct rotulos_lista));
	inicio->proximo = NULL;
	percorre = inicio;

	while(fscanf(arq, "%s", leitura) != EOF){
		mnemonico = checa(leitura);
		if(mnemonico >=0 && mnemonico <= 16){
			tamanho = tamanho + checa_tamanho(mnemonico);
			operandos = checa_operandos(mnemonico);
			for (i = 0; i < operandos; ++i){
				fscanf(arq, "%s", leitura);
				mnemonico = checa(leitura);
				tamanho = tamanho + checa_tamanho(mnemonico);
			}
		}
		if(mnemonico == 98){
			strcpy(rotulo, leitura);
			cria_no(inicio, rotulo, tamanho);
		}
	}
	
	rewind(arq);

	while(fscanf(arq, "%s", leitura) != EOF){
		mnemonico = checa(leitura);
		if((mnemonico >= 0 && mnemonico <=13) || mnemonico == 16){
			if(mnemonico != 16){
				fprintf(arq2, "%d ", mnemonico+1);
			}
			if(mnemonico == 8){
				fscanf(arq, "%s", leitura);
				leitura[strlen(leitura)-1] = leitura[strlen(leitura)];
				j = 0;
				j = atoi(leitura);
				sprintf(transfere, "%d", j);
				if(strcmp(transfere, leitura) != 0){
					percorre = percorre_lista(inicio, leitura);
					fprintf(arq2, "%d ", percorre->valor);
					fscanf(arq, "%s", leitura);
					j=0;
					j= atoi(leitura);
					sprintf(transfere, "%d", j);
					if(strcmp(transfere, leitura) != 0){
						percorre = percorre_lista(inicio, leitura);
						fprintf(arq2, "%d ", percorre->valor);
					}
					else{
						fprintf(arq2, "%d ", j);
					}
				}
				else{
					fprintf(arq2, "%d ", j);
					fscanf(arq, "%s", leitura);
					j = 0;
					j = atoi(leitura);
					sprintf(transfere, "%d", j);
					if(strcmp(transfere, leitura) != 0){
						percorre = percorre_lista(inicio, leitura);
						fprintf(arq2, "%d ", percorre->valor);
					}
					else{
						fprintf(arq2, "%d ", j);
					}
				}
			}
			else{
				operandos = checa_operandos(mnemonico);
				for (i = 0; i < operandos; ++i){
					fscanf(arq, "%s", leitura);
					j = 0;
					j = atoi(leitura);
					sprintf(transfere, "%d", j);
					if(strcmp(transfere, leitura) != 0){
						percorre = percorre_lista(inicio, leitura);
						fprintf(arq2, "%d ", percorre->valor);

					}
					else{
						fprintf(arq2, "%d ", j);
					}
				
				}
			}
		}
		if(mnemonico == 14){
			fscanf(arq, "%s", leitura);
		}
		if(mnemonico == 98){
		}
		if(mnemonico == 15){
			fprintf(arq2, "%s ", "0");
		}
	}

}

int main(int argc, char **argv){
	FILE *arq;
	FILE *arq2;
	int i=0;

	


	if(strcmp(argv[1], "-p") == 0){
		arq = fopen(argv[2], "r");
		
		while(argv[2][i] != NULL){
			i++;
		}
		argv[2][i-3] = 'P';
		argv[2][i-2] = 'R';
		argv[2][i-1] = 'E';

		arq2 = fopen(argv[2], "w");
		
		pre_processa(arq, arq2);
	}

	if(strcmp(argv[1], "-o") == 0){
		arq = fopen(argv[2], "r");
		
		while(argv[2][i] != NULL){
			i++;
		}
		argv[2][i-3] = 'O';
		argv[2][i-2] = 'B';
		argv[2][i-1] = 'J';

		arq2 = fopen(argv[2], "w");
		monta(arq, arq2);
	}

	fclose(arq);
	fclose(arq2);

	return 0;
}