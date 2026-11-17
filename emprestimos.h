#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

#include <stdio.h>
#include <string.h>

/* MODULO 3 - EMPRESTIMOS
   Autor: Bernardo - RGM: PREENCHER
   Depende de acervo.h e leitores.h, incluídos antes no main.c.
*/

struct Emprestimo {
    int idEmprestimo;
    int idLivro;
    int idLeitor;
    char dataEmprestimo[11];
    char dataDevolucaoPrevista[11];
    float valorMulta;
    int devolvido; // 0 = em aberto; 1 = devolvido
};

struct Emprestimo emprestimos[50];
int totalEmprestimos = 0;

/* Definida no main.c, depois da inclusão de reservas.h. */
void sincronizarDisponibilidade(void);

int buscarIndiceEmprestimo(int id) {
    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idEmprestimo == id) return i;
    }
    return -1;
}

int existeEmprestimoAbertoLivro(int idLivro) {
    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idLivro == idLivro && emprestimos[i].devolvido == 0)
            return 1;
    }
    return 0;
}

void salvarEmprestimosCSV(void) {
    FILE *arquivo = fopen("emprestimos.csv", "w");
    if (arquivo == NULL) {
        printf("[ERRO] Nao foi possivel salvar emprestimos.csv!\n");
        return;
    }

    for (int i = 0; i < totalEmprestimos; i++) {
        fprintf(arquivo, "%d;%d;%d;%s;%s;%.2f;%d\n",
                emprestimos[i].idEmprestimo,
                emprestimos[i].idLivro,
                emprestimos[i].idLeitor,
                emprestimos[i].dataEmprestimo,
                emprestimos[i].dataDevolucaoPrevista,
                emprestimos[i].valorMulta,
                emprestimos[i].devolvido);
    }
    fclose(arquivo);
}

void carregarEmprestimosCSV(void) {
    FILE *arquivo = fopen("emprestimos.csv", "r");
    if (arquivo == NULL) {
        printf("[AVISO] emprestimos.csv nao encontrado.\n");
        return;
    }

    totalEmprestimos = 0;
    while (totalEmprestimos < 50 &&
           fscanf(arquivo, " %d;%d;%d;%10[^;];%10[^;];%f;%d",
                  &emprestimos[totalEmprestimos].idEmprestimo,
                  &emprestimos[totalEmprestimos].idLivro,
                  &emprestimos[totalEmprestimos].idLeitor,
                  emprestimos[totalEmprestimos].dataEmprestimo,
                  emprestimos[totalEmprestimos].dataDevolucaoPrevista,
                  &emprestimos[totalEmprestimos].valorMulta,
                  &emprestimos[totalEmprestimos].devolvido) == 7) {
        totalEmprestimos++;
    }
    fclose(arquivo);
}

void cadastrarEmprestimo(void) {
    struct Emprestimo novo;
    int posLivro, posLeitor;

    if (totalEmprestimos >= 50) {
        printf("[ERRO] Limite de 50 emprestimos atingido!\n");
        return;
    }

    printf("\n=== NOVO EMPRESTIMO ===\n");
    printf("ID do emprestimo: ");
    if (scanf("%d", &novo.idEmprestimo) != 1) return;
    if (buscarIndiceEmprestimo(novo.idEmprestimo) != -1) {
        printf("[ERRO] ID de emprestimo ja cadastrado!\n");
        return;
    }

    printf("ID do livro: ");
    if (scanf("%d", &novo.idLivro) != 1) return;
    posLivro = buscarIndiceLivro(novo.idLivro);
    if (posLivro == -1) {
        printf("[ERRO] Livro nao encontrado!\n");
        return;
    }
    if (acervo[posLivro].disponivel == 0 || existeEmprestimoAbertoLivro(novo.idLivro)) {
        printf("[ERRO] Livro indisponivel ou ja emprestado/reservado!\n");
        return;
    }

    printf("ID do leitor: ");
    if (scanf("%d", &novo.idLeitor) != 1) return;
    posLeitor = buscarIndiceLeitor(novo.idLeitor);
    if (posLeitor == -1 || leitores[posLeitor].ativo == 0) {
        printf("[ERRO] Leitor inexistente ou inativo!\n");
        return;
    }

    printf("Data do emprestimo (DD/MM/AAAA): ");
    if (scanf(" %10[^\n]", novo.dataEmprestimo) != 1) return;
    printf("Previsao de devolucao (DD/MM/AAAA): ");
    if (scanf(" %10[^\n]", novo.dataDevolucaoPrevista) != 1) return;

    novo.valorMulta = 0.0f;
    novo.devolvido = 0;
    emprestimos[totalEmprestimos] = novo;
    totalEmprestimos++;

    salvarEmprestimosCSV();
    sincronizarDisponibilidade();
    printf("[OK] Emprestimo registrado e arquivos atualizados!\n");
}

void listarEmprestimos(void) {
    printf("\n=== EMPRESTIMOS CADASTRADOS (%d) ===\n", totalEmprestimos);
    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalEmprestimos; i++) {
        printf("ID: %d | Livro: %d | Leitor: %d | Data: %s | Prevista: %s | Multa: R$ %.2f | %s\n",
               emprestimos[i].idEmprestimo,
               emprestimos[i].idLivro,
               emprestimos[i].idLeitor,
               emprestimos[i].dataEmprestimo,
               emprestimos[i].dataDevolucaoPrevista,
               emprestimos[i].valorMulta,
               emprestimos[i].devolvido ? "Devolvido" : "Em aberto");
    }
}

void buscarEmprestimoPorLeitor(void) {
    char nome[50];
    int encontrados = 0;
    printf("Digite parte do nome do leitor: ");
    if (scanf(" %49[^\n]", nome) != 1) return;

    for (int i = 0; i < totalEmprestimos; i++) {
        int pos = buscarIndiceLeitor(emprestimos[i].idLeitor);
        if (pos != -1 && strstr(leitores[pos].nome, nome) != NULL) {
            printf("Emprestimo: %d | Leitor: %s | Livro ID: %d | %s\n",
                   emprestimos[i].idEmprestimo,
                   leitores[pos].nome,
                   emprestimos[i].idLivro,
                   emprestimos[i].devolvido ? "Devolvido" : "Em aberto");
            encontrados++;
        }
    }
    if (encontrados == 0) printf("Nenhum emprestimo encontrado.\n");
}

void editarEmprestimo(void) {
    int id;
    printf("ID do emprestimo a editar: ");
    if (scanf("%d", &id) != 1) return;
    int pos = buscarIndiceEmprestimo(id);
    if (pos == -1) {
        printf("Emprestimo nao encontrado!\n");
        return;
    }
    if (emprestimos[pos].devolvido) {
        printf("Emprestimo ja devolvido: alteracao bloqueada.\n");
        return;
    }
    printf("Nova data prevista (DD/MM/AAAA): ");
    if (scanf(" %10[^\n]", emprestimos[pos].dataDevolucaoPrevista) != 1) return;
    salvarEmprestimosCSV();
    printf("[OK] Data atualizada no CSV!\n");
}

void registrarDevolucao(void) {
    int id, diasAtraso;
    printf("ID do emprestimo devolvido: ");
    if (scanf("%d", &id) != 1) return;
    int pos = buscarIndiceEmprestimo(id);
    if (pos == -1 || emprestimos[pos].devolvido) {
        printf("Emprestimo inexistente ou ja devolvido!\n");
        return;
    }

    printf("Quantos dias de atraso? (0 se pontual): ");
    if (scanf("%d", &diasAtraso) != 1 || diasAtraso < 0) {
        printf("Quantidade de dias invalida!\n");
        return;
    }

    /* Regra didatica: multa automatica de R$ 2,00 por dia de atraso. */
    emprestimos[pos].valorMulta = diasAtraso * 2.0f;
    emprestimos[pos].devolvido = 1;
    salvarEmprestimosCSV();

    int posLeitor = buscarIndiceLeitor(emprestimos[pos].idLeitor);
    if (posLeitor != -1) {
        leitores[posLeitor].multaPendente += emprestimos[pos].valorMulta;
        salvarLeitoresCSV();
    }
    sincronizarDisponibilidade();
    printf("[OK] Devolucao registrada. Multa: R$ %.2f\n",
           emprestimos[pos].valorMulta);
}

void removerEmprestimo(void) {
    int id;
    printf("ID do emprestimo para excluir/cancelar: ");
    if (scanf("%d", &id) != 1) return;
    int pos = buscarIndiceEmprestimo(id);
    if (pos == -1) {
        printf("Emprestimo nao encontrado!\n");
        return;
    }
    for (int i = pos; i < totalEmprestimos - 1; i++) {
        emprestimos[i] = emprestimos[i + 1];
    }
    totalEmprestimos--;
    salvarEmprestimosCSV();
    sincronizarDisponibilidade();
    printf("[OK] Emprestimo removido do CSV.\n");
}

void moduloEmprestimos(void) {
    int opcao;
    do {
        printf("\n=== EMPRESTIMOS - BERNARDO ===\n");
        printf("1. Cadastrar emprestimo\n");
        printf("2. Listar emprestimos\n");
        printf("3. Buscar por nome do leitor\n");
        printf("4. Editar previsao de devolucao\n");
        printf("5. Registrar devolucao e calcular multa\n");
        printf("6. Remover / cancelar emprestimo\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            opcao = -1;
        }
        switch (opcao) {
            case 1: cadastrarEmprestimo(); break;
            case 2: listarEmprestimos(); break;
            case 3: buscarEmprestimoPorLeitor(); break;
            case 4: editarEmprestimo(); break;
            case 5: registrarDevolucao(); break;
            case 6: removerEmprestimo(); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

#endif
