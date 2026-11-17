#include <stdio.h>
#include "acervo.h"       // Joao Pedro
#include "leitores.h"     // Yan
#include "emprestimos.h"  // Bernardo
#include "reservas.h"     // Andre: depende dos 3 modulos anteriores

/* Recalcula se cada livro esta ocupado por um emprestimo ou reserva ativa.
   Definida aqui para enxergar tanto emprestimos quanto reservas. */
void sincronizarDisponibilidade(void) {
    if (totalLivros == 0) return;

    for (int i = 0; i < totalLivros; i++) {
        int ocupado = 0;
        for (int j = 0; j < totalEmprestimos; j++) {
            if (emprestimos[j].idLivro == acervo[i].idLivro &&
                emprestimos[j].devolvido == 0) {
                ocupado = 1;
                break;
            }
        }
        for (int j = 0; j < totalReservas; j++) {
            if (reservas[j].idLivro == acervo[i].idLivro &&
                reservas[j].ativa == 1) {
                ocupado = 1;
                break;
            }
        }
        acervo[i].disponivel = ocupado ? 0 : 1;
    }
    salvarLivrosCSV();
}

int main(void) {
    int opcaoPrincipal;
    carregarLivrosCSV();
    carregarLeitoresCSV();
    carregarEmprestimosCSV();
    carregarReservasCSV();
    sincronizarDisponibilidade();

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
        printf("Escolha: ");

        if (scanf("%d", &opcaoPrincipal) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            opcaoPrincipal = -1;
        }
        switch (opcaoPrincipal) {
            case 1: moduloLivros(); break;
            case 2: moduloLeitores(); break;
            case 3: moduloEmprestimos(); break;
            case 4:
                moduloReservasRelatorios();
                sincronizarDisponibilidade();
                break;
            case 0: printf("Encerrando o sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcaoPrincipal != 0);
    return 0;
}