#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_MSG 500
#define SENHA_MESTRA "2871"


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void sanitizarMemoria(char *ptr, size_t tamanho) {
    memset(ptr, 0, tamanho);
}


void processarCesar(char texto[], int shift, char modo) {

    shift = shift % 26;
    if (modo == 'd') shift = -shift;

    for (int i = 0; texto[i] != '\0'; ++i) {
        if (isalpha(texto[i])) {
            char base = isupper(texto[i]) ? 'A' : 'a';

            int resultado = (texto[i] - base + shift) % 26;
            if (resultado < 0) resultado += 26;

            texto[i] = (char)(resultado + base);
        }
    }
}

int main() {
    char senha_digitada[50];
    char mensagem[MAX_MSG];
    int opcao, chave;

    printf("--- ENIGMA V1.2 PRO (Cesar Edition) ---\n");

    //
    printf("SENHA DE ACESSO: ");
    if (scanf("%49s", senha_digitada) != 1) return 1;
    limparBuffer();

    if (strcmp(senha_digitada, SENHA_MESTRA) != 0) {
        printf("Acesso negado!\n");
        sanitizarMemoria(senha_digitada, sizeof(senha_digitada));
        return 0;
    }

    while (1) {
        printf("\n1. Criptografar\n2. Descriptografar\n3. Sair\nEscolha: ");


        if (scanf("%d", &opcao) != 1) {
            printf("Erro: Digite apenas o numero da opcao.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        if (opcao == 3) break;

        if (opcao == 1 || opcao == 2) {
            printf("Confirme a senha: ");
            scanf("%49s", senha_digitada);
            limparBuffer();

            if (strcmp(senha_digitada, SENHA_MESTRA) == 0) {
                printf("Digite a mensagem:\n> ");
                fgets(mensagem, MAX_MSG, stdin);
                mensagem[strcspn(mensagem, "\n")] = 0;

                printf("Digite a chave (deslocamento): ");
                if (scanf("%d", &chave) != 1) {
                    printf("Erro: Chave invalida!\n");
                    limparBuffer();
                    continue;
                }
                limparBuffer();

                processarCesar(mensagem, chave, (opcao == 1 ? 'c' : 'd'));

                printf("\n--- RESULTADO ---\n%s\n-----------------\n", mensagem);
                sanitizarMemoria(mensagem, MAX_MSG);
            } else {
                printf("!!! Senha incorreta.\n");
            }
        } else {
            printf("Opcao inexistente.\n");
        }
    }
    sanitizarMemoria(senha_digitada, sizeof(senha_digitada));
    printf("Encerrando com seguranca...\n");
    return 0;
}
