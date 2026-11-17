#ifndef RESERVAS_H
#define RESERVAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* MODULO 4 - RESERVAS E RELATORIOS
   Autor: Andre Fogaca - RGM: 48380831 */

struct Reserva {
    int idReserva;
    int idLivro;
    int idLeitor;
    char dataReserva[11];
    float taxaReserva;
    int ativa; // 1 = Ativa | 0 = Cancelada (Padrao da Etapa 1 do grupo)
};

struct Reserva reservas[50];
int totalReservas = 0;

/* --- 1. LIMPAR TELA (WINDOWS / LINUX / MAC) --- */
void limparTelaReservas() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/* --- 2. SALVAR VETOR NO ARQUIVO CSV --- */
void salvarReservasCSV() {
    int i;
    FILE *arq = fopen("reservas.csv", "w");
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel abrir reservas.csv para gravacao!\n");
        return;
    }

    for (i = 0; i < totalReservas; i++) {
        fprintf(arq, "%d;%d;%d;%s;%.2f;%d\n",
                reservas[i].idReserva,
                reservas[i].idLivro,
                reservas[i].idLeitor,
                reservas[i].dataReserva,
                reservas[i].taxaReserva,
                reservas[i].ativa);
    }

    fclose(arq);
}

/* --- 3. CARREGAR DO CSV (COM 8 REGISTROS INICIAIS) --- */
void carregarReservasCSV() {
    int i;
    FILE *arq = fopen("reservas.csv", "r");

    // Se o arquivo nao existir, cria os 8 registros iniciais exigidos (IDs 1 a 8)
    if (arq == NULL) {
        struct Reserva iniciais[8] = {
            {101, 1, 1, "02/11/2026", 4.50, 1},
            {102, 3, 2, "04/11/2026", 3.00, 1},
            {103, 2, 3, "05/11/2026", 3.50, 0},
            {104, 5, 4, "07/11/2026", 3.99, 1},
            {105, 4, 5, "09/11/2026", 4.20, 1},
            {106, 1, 6, "11/11/2026", 4.50, 0},
            {107, 6, 7, "13/11/2026", 3.80, 1},
            {108, 7, 8, "15/11/2026", 3.20, 1}
        };

        for (i = 0; i < 8; i++) {
            reservas[i] = iniciais[i];
        }
        totalReservas = 8;
        salvarReservasCSV();
        return;
    }

    totalReservas = 0;
    while (totalReservas < 50 &&
           fscanf(arq, "%d;%d;%d;%10[^;];%f;%d\n",
                  &reservas[totalReservas].idReserva,
                  &reservas[totalReservas].idLivro,
                  &reservas[totalReservas].idLeitor,
                  reservas[totalReservas].dataReserva,
                  &reservas[totalReservas].taxaReserva,
                  &reservas[totalReservas].ativa) == 6) {
        totalReservas++;
    }

    fclose(arq);
}

/* --- 4. CADASTRAR RESERVA (CRUZANDO COM ACERVO E LEITORES) --- */
void cadastrarReserva() {
    int i;
    int idReservaDig, idLivroDigitado, idLeitorDigitado;
    int posLivro = -1, posLeitor = -1;

    if (totalReservas >= 50) {
        printf("\n[AVISO] Limite de 50 reservas atingido!\n");
        return;
    }

    printf("\n=== NOVA RESERVA ===\n");
    printf("Codigo da Reserva (int): ");
    scanf("%d", &idReservaDig);

    for (i = 0; i < totalReservas; i++) {
        if (reservas[i].idReserva == idReservaDig) {
            printf("[ERRO] Esse ID de reserva ja existe!\n");
            return;
        }
    }

    /* 1. Cruza dados com o Modulo 1 (Joao Pedro - acervo) */
    printf("Codigo do Livro (int): ");
    scanf("%d", &idLivroDigitado);
    for (i = 0; i < totalLivros; i++) {
        if (acervo[i].idLivro == idLivroDigitado) {
            posLivro = i;
            break;
        }
    }
    if (posLivro == -1) {
        printf("[ERRO] Livro ID %d nao encontrado no acervo!\n", idLivroDigitado);
        return;
    }
    if (acervo[posLivro].disponivel == 0) {
        printf("[AVISO] O livro '%s' ja esta indisponivel no estoque!\n", acervo[posLivro].titulo);
        return;
    }

    /* 2. Cruza dados com o Modulo 2 (Yan - leitores) */
    printf("Codigo do Leitor (int): ");
    scanf("%d", &idLeitorDigitado);
    for (i = 0; i < totalLeitores; i++) {
        if (leitores[i].idLeitor == idLeitorDigitado) {
            posLeitor = i;
            break;
        }
    }
    if (posLeitor == -1) {
        printf("[ERRO] Leitor ID %d nao encontrado no fichario!\n", idLeitorDigitado);
        return;
    }
    if (leitores[posLeitor].ativo == 0) {
        printf("[AVISO] O leitor '%s' esta inativo no sistema!\n", leitores[posLeitor].nome);
        return;
    }

    /* Grava os dados validados na gaveta atual */
    reservas[totalReservas].idReserva = idReservaDig;
    reservas[totalReservas].idLivro = idLivroDigitado;
    reservas[totalReservas].idLeitor = idLeitorDigitado;

    printf("Selecionado -> Livro: %s | Leitor: %s\n", acervo[posLivro].titulo, leitores[posLeitor].nome);

    printf("Data da Reserva (DD/MM/AAAA): ");
    scanf(" %10[^\n]", reservas[totalReservas].dataReserva);

    /* Calcula a taxa automatica (10% do valor estimado do livro do Joao Pedro) */
    reservas[totalReservas].taxaReserva = acervo[posLivro].valorEstimado * 0.10;
    printf("Taxa calculada (10%% do valor do livro): R$ %.2f\n", reservas[totalReservas].taxaReserva);

    /* Abate a disponibilidade do livro no estoque e salva no CSV de livros (se a funcao existir) */
    acervo[posLivro].disponivel = 0;

    reservas[totalReservas].ativa = 1;
    totalReservas++;

    salvarReservasCSV();
    printf("[OK] Reserva cadastrada, estoque atualizado e salvo em 'reservas.csv'!\n");
}

/* --- 5. LISTAR RESERVAS (MOSTRANDO NOMES REAIS SE DISPONIVEIS) --- */
void listarReservas() {
    int i, j;
    printf("\n=== LISTA DE RESERVAS (%d registros) ===\n", totalReservas);
    if (totalReservas == 0) {
        printf("Nenhuma reserva cadastrada.\n");
        return;
    }

    for (i = 0; i < totalReservas; i++) {
        char *nomeLivro = "Desconhecido";
        char *nomeLeitor = "Desconhecido";

        for (j = 0; j < totalLivros; j++) {
            if (acervo[j].idLivro == reservas[i].idLivro) {
                nomeLivro = acervo[j].titulo;
                break;
            }
        }
        for (j = 0; j < totalLeitores; j++) {
            if (leitores[j].idLeitor == reservas[i].idLeitor) {
                nomeLeitor = leitores[j].nome;
                break;
            }
        }

        printf("ID: %-3d | Livro: %-2d (%-15.15s) | Leitor: %-2d (%-12.12s) | Data: %-10s | Taxa: R$ %-5.2f | Status: %s\n",
               reservas[i].idReserva,
               reservas[i].idLivro,
               nomeLivro,
               reservas[i].idLeitor,
               nomeLeitor,
               reservas[i].dataReserva,
               reservas[i].taxaReserva,
               reservas[i].ativa == 1 ? "Ativa" : "Cancelada");
    }
}

/* --- 6. BUSCAR RESERVA POR DATA (USANDO STRSTR) --- */
void buscarReservaPorData() {
    int i, achou = 0;
    char termo[11];

    printf("\nDigite parte da data para buscar (ex: /11/ ou 15/11): ");
    scanf(" %10[^\n]", termo);

    printf("\n--- RESULTADOS DA BUSCA ---\n");
    for (i = 0; i < totalReservas; i++) {
        if (strstr(reservas[i].dataReserva, termo) != NULL) {
            printf("ID: %-4d | Livro ID: %-3d | Leitor ID: %-3d | Data: %-10s | Taxa: R$ %.2f | Status: %s\n",
                   reservas[i].idReserva,
                   reservas[i].idLivro,
                   reservas[i].idLeitor,
                   reservas[i].dataReserva,
                   reservas[i].taxaReserva,
                   reservas[i].ativa == 1 ? "Ativa" : "Cancelada");
            achou++;
        }
    }

    if (achou == 0) {
        printf("Nenhuma reserva encontrada com esse termo.\n");
    }
}

/* --- 7. EDITAR RESERVA --- */
void editarReserva() {
    int id, i, pos = -1;

    printf("\nID da reserva para editar a data: ");
    scanf("%d", &id);

    for (i = 0; i < totalReservas; i++) {
        if (reservas[i].idReserva == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("[ERRO] Reserva nao encontrada!\n");
        return;
    }

    printf("Data atual: %s | Digite a nova data (DD/MM/AAAA): ", reservas[pos].dataReserva);
    scanf(" %10[^\n]", reservas[pos].dataReserva);

    salvarReservasCSV();
    printf("[OK] Reserva atualizada com sucesso!\n");
}

/* --- 8. CANCELAR RESERVA (DEVOLVENDO LIVRO AO ESTOQUE) --- */
void cancelarReserva() {
    int id, i, j, pos = -1;

    printf("\nID da reserva para cancelar: ");
    scanf("%d", &id);

    for (i = 0; i < totalReservas; i++) {
        if (reservas[i].idReserva == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("[ERRO] Reserva nao encontrada!\n");
        return;
    }

    if (reservas[pos].ativa == 0) {
        printf("[AVISO] Essa reserva ja esta cancelada!\n");
        return;
    }

    reservas[pos].ativa = 0;

    /* Devolve a disponibilidade do livro no vetor do Joao Pedro */
    for (j = 0; j < totalLivros; j++) {
        if (acervo[j].idLivro == reservas[pos].idLivro) {
            acervo[j].disponivel = 1;
            break;
        }
    }

    salvarReservasCSV();
    printf("[OK] Reserva cancelada e livro liberado novamente no acervo!\n");
}

/* --- 9. RELATORIOS CRUZADOS COM EMPRESTIMOS E MATRIZ 2D --- */
void relatorioMatrizReservas() {
    int i;
    /* Matriz 2x2:
       Linha 0 = Ativas (1)     | Coluna 0 = Quantidade | Coluna 1 = Total R$
       Linha 1 = Canceladas (0) | Coluna 0 = Quantidade | Coluna 1 = Total R$ */
    float resumo[2][2] = { {0.0, 0.0}, {0.0, 0.0} };

    for (i = 0; i < totalReservas; i++) {
        if (reservas[i].ativa == 1) {
            resumo[0][0] += 1;
            resumo[0][1] += reservas[i].taxaReserva;
        } else {
            resumo[1][0] += 1;
            resumo[1][1] += reservas[i].taxaReserva;
        }
    }

    printf("\n=== RELATORIO FINANCEIRO DE RESERVAS (MATRIZ 2D) ===\n");
    printf("Status          | Quantidade | Total em Taxas\n");
    printf("-------------------------------------------------\n");
    printf("Ativas (1)      | %-10.0f | R$ %.2f\n", resumo[0][0], resumo[0][1]);
    printf("Canceladas (0)  | %-10.0f | R$ %.2f\n", resumo[1][0], resumo[1][1]);
    printf("-------------------------------------------------\n");
    printf("TOTAL GERAL     | %-10.0f | R$ %.2f\n",
           resumo[0][0] + resumo[1][0],
           resumo[0][1] + resumo[1][1]);
}

void relatorioEmprestimosAbertos() {
    int i, abertos = 0;
    printf("\n=== RELATORIO: EMPRESTIMOS EM ABERTO ===\n");
    for (i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].devolvido == 0) {
            printf("Emprestimo ID: %d | Livro ID: %d | Leitor ID: %d | Prev. Devolucao: %s\n",
                   emprestimos[i].idEmprestimo,
                   emprestimos[i].idLivro,
                   emprestimos[i].idLeitor,
                   emprestimos[i].dataDevolucaoPrevista);
            abertos++;
        }
    }
    if (abertos == 0) {
        printf("Nenhum emprestimo em aberto no momento.\n");
    }
}

/* --- MENU DO MODULO 4 --- */
void moduloReservasRelatorios() {
    carregarReservasCSV();
    int opcao;

    do {
        printf("\n=== RESERVAS E RELATORIOS ===\n");
        printf("1. Cadastrar reserva (Cruza Livro/Leitor)\n");
        printf("2. Listar reservas\n");
        printf("3. Buscar reserva por data (strstr)\n");
        printf("4. Editar data da reserva\n");
        printf("5. Cancelar reserva\n");
        printf("6. Relatorio Consolidado (Matriz 2D)\n");
        printf("7. Relatorio de Emprestimos em Aberto\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        limparTelaReservas();

        switch (opcao) {
            case 1: cadastrarReserva(); break;
            case 2: listarReservas(); break;
            case 3: buscarReservaPorData(); break;
            case 4: editarReserva(); break;
            case 5: cancelarReserva(); break;
            case 6: relatorioMatrizReservas(); break;
            case 7: relatorioEmprestimosAbertos(); break;
            case 0: printf("Voltando ao menu principal...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while (opcao != 0);
}

#endif
