// ==================================================
// MODULO 3 - EMPRESTIMOS
// Autor: Bernardo
// ==================================================
struct Emprestimo {
    int idEmprestimo;
    int idLivro;
    int idLeitor;
    char dataEmprestimo[11];
    char dataDevolucaoPrevista[11];
    float valorMulta;
    int devolvido;
};

struct Emprestimo emprestimos[50];
int totalEmprestimos = 0;

void moduloEmprestimos() {
    int opcao;

    do {
        printf("\n=== EMPRESTIMOS ===\n");
        printf("1. Registrar emprestimo\n");
        printf("2. Listar / buscar emprestimos\n");
        printf("3. Editar / registrar devolucao\n");
        printf("4. Cancelar emprestimo\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Emprestimo em construcao\n");
                break;
            case 2:
                printf("Consulta em construcao\n");
                break;
            case 3:
                printf("Devolucao em construcao\n");
                break;
            case 4:
                printf("Cancelamento em construcao\n");
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 0);
}

// ==================================================
// MODULO 4 - RESERVAS E RELATORIOS
// Autor: Andre Fogaca - RGM: 48380831
// Colocar depois das structs de Leitor e Emprestimo,
// pois reservas.h utiliza ambos os vetores globais.
// ==================================================
#include "reservas.h"

// ==================================================
// MENU PRINCIPAL
// Autores: Joao Pedro, Yan, Bernardo e Andre
// ==================================================
int main(void) {
    int opcaoPrincipal;

    // Os arquivos CSV sao lidos quando o programa inicia.
    carregarLivrosCSV();
    carregarReservasCSV();

    do {
        printf("\n===================================\n");
        printf("         BIBLIOTECA CLASSICA       \n");
        printf("       SISTEMA DE GERENCIAMENTO    \n");
        printf("===================================\n");
        printf("1. Acervo de Livros - Joao Pedro\n");
        printf("2. Fichario de Leitores - Yan\n");
        printf("3. Emprestimos - Bernardo\n");
        printf("4. Reservas e Relatorios - Andre\n");
        printf("0. Encerrar Sistema\n");
        printf("-----------------------------------\n");
        printf("Digite sua opcao: ");

        if (scanf("%d", &opcaoPrincipal) != 1) {
            int c;
            printf("Digite um numero valido!\n");
            while ((c = getchar()) != '\n' && c != EOF) { }
            opcaoPrincipal = -1;
        }

        switch (opcaoPrincipal) {
            case 1:
                moduloLivros();
                break;
            case 2:
                moduloLeitores();
                break;
            case 3:
                moduloEmprestimos();
                break;
            case 4:
                moduloReservasRelatorios();
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                printf("Obrigado por utilizar a Biblioteca Classica!\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
