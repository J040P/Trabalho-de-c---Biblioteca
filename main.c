
#include <stdio.h>
#include "acervo.h"

// ==========================================
// BIBLIOTECA CLASSICA - CHECKPOINT 2
// Integrantes:
// Joao Pedro - Acervo de Livros
// Yan - Fichario de Leitores
// Bernardo - Emprestimos
// Andre Fogaca - Reservas e Relatorios
// ==========================================

// MODULO 1 - ACERVO DE LIVROS
// Autor: Joao Pedro
// Implementado no arquivo acervo.h

// ==========================================
// MODULO 2 - FICHARIO DE LEITORES
// Autor: Yan
// ==========================================

struct Leitor {
    int idLeitor;
    char nome[50];
    char telefone[20];
    int numeroCarteirinha;
    float multaPendente;
    int ativo;
};

struct Leitor leitores[50];
int totalLeitores = 0;

void moduloLeitores() {
    int opcao;

    do {
        printf("\n=== FICHARIO DE LEITORES ===\n");
        printf("1. Cadastrar leitor\n");
        printf("2. Listar / buscar leitores\n");
        printf("3. Editar leitor\n");
        printf("4. Remover leitor\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Cadastro em construcao\n");
                break;
            case 2:
                printf("Listagem em construcao\n");
                break;
            case 3:
                printf("Edicao em construcao\n");
                break;
            case 4:
                printf("Remocao em construcao\n");
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }

    } while (opcao != 0);
}

// ==========================================
// MODULO 3 - EMPRESTIMOS
// Autor: Bernardo
// ==========================================

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

// ==========================================
// MODULO 4 - RESERVAS E RELATORIOS
// Autor: Andre Fogaca
// RGM: 48380831
// ==========================================

struct Reserva {
    int idReserva;
    int idLivro;
    int idLeitor;
    char dataReserva[11];
    float taxaReserva;
    int ativa;
};

struct Reserva reservas[50];
int totalReservas = 0;

void moduloReservasRelatorios() {
    int opcao;

    do {
        printf("\n=== RESERVAS E RELATORIOS ===\n");
        printf("1. Cadastrar reserva\n");
        printf("2. Listar / buscar reservas\n");
        printf("3. Editar reserva\n");
        printf("4. Cancelar reserva\n");
        printf("5. Livro mais emprestado\n");
        printf("6. Leitor mais ativo\n");
        printf("7. Emprestimos em aberto\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Cadastro em construcao\n");
                break;
            case 2:
                printf("Consulta em construcao\n");
                break;
            case 3:
                printf("Edicao em construcao\n");
                break;
            case 4:
                printf("Remocao em construcao\n");
                break;
            case 5:
                printf("Relatorio do livro mais emprestado em construcao\n");
                break;
            case 6:
                printf("Relatorio do leitor mais ativo em construcao\n");
                break;
            case 7:
                printf("Relatorio de emprestimos em aberto em construcao\n");
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }

    } while (opcao != 0);
}

// ==========================================
// MENU PRINCIPAL
// Autores: Joao Pedro, Yan, Bernardo e Andre
// ==========================================

int main() {
    int opcaoPrincipal;

    // Carrega os livros armazenados no CSV
    carregarLivrosCSV();

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
            printf("Digite um numero valido!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
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
