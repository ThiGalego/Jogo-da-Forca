#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> 

#define MAX_TENTATIVAS 6
#define TAMANHO_PALAVRA 30

const char *palavras[] = {
    "computador", "programacao", "teclado", "monitor", "ciencia", "desenvolvedor", "terminal"
};

// Desenho da forca em ASCII
void desenhar_forca(int erros) {
    printf(" _______\n");
    printf(" |     |\n");
    printf(" |     %c\n", (erros >= 1 ? 'O' : ' '));
    printf(" |    %c%c%c\n", 
        (erros >= 3 ? '/' : ' '),
        (erros >= 2 ? '|' : ' '),
        (erros >= 4 ? '\\' : ' ')
    );
    printf(" |    %c %c\n", 
        (erros >= 5 ? '/' : ' '),
        (erros >= 6 ? '\\' : ' ')
    );
    printf("_|_\n\n");
}

const char* escolher_palavra() {
    int total_palavras = sizeof(palavras) / sizeof(palavras[0]);
    return palavras[rand() % total_palavras];
}

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    char palavra[TAMANHO_PALAVRA];
    char palavra_oculta[TAMANHO_PALAVRA];
    char letra;
    int i, tentativas = 0;
    int acertou = 0;

    srand((unsigned int)time(NULL));  

    strcpy(palavra, escolher_palavra());
    int tamanho = strlen(palavra);

    for (i = 0; i < tamanho; i++) {
        palavra_oculta[i] = '_';
    }
    palavra_oculta[tamanho] = '\0';

    char letras_usadas[26] = {0};
    int usadas = 0;

    while (tentativas < MAX_TENTATIVAS && !acertou) {
        limpar_tela();
        desenhar_forca(tentativas);

        // >>>> Adicionado para mostrar a palavra oculta
        printf("Palavra: ");
        for (i = 0; i < tamanho; i++) {
            printf("%c ", palavra_oculta[i]);
        }
        printf("\n\n");

        printf("Letras usadas: ");
        for (i = 0; i < usadas; i++) {
            printf("%c ", letras_usadas[i]);
        }
        printf("\n");

        printf("\nDigite uma letra: ");
        scanf(" %c", &letra);
        letra = tolower(letra);

        // Verifica se já usou essa letra
        int repetida = 0;
        for (i = 0; i < usadas; i++) {
            if (letras_usadas[i] == letra) {
                repetida = 1;
                break;
            }
        }
        if (repetida) {
            printf("Você já tentou essa letra!\n");
            system("pause");
            continue;
        }

        letras_usadas[usadas++] = letra;

        int encontrou = 0;
        for (i = 0; i < tamanho; i++) {
            if (palavra[i] == letra) {
                palavra_oculta[i] = letra;
                encontrou = 1;
            }
        }

        if (!encontrou) {
            tentativas++;
        }

        if (strcmp(palavra, palavra_oculta) == 0) {
            acertou = 1;
        }
    }

    limpar_tela();
    desenhar_forca(tentativas);

    if (acertou) {
        printf("Parabéns! Você acertou: %s\n", palavra);
    } else {
        printf("Você perdeu! A palavra era: %s\n", palavra);
    }

    return 0;
}
