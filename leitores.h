
#ifndef LEITORES_H
#define LEITORES_H

#include <stdio.h>
#include <string.h>

// MODULO 2 - FICHARIO DE LEITORES
// Autor: Yan - RGM: PREENCHER

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

// Procura um leitor pelo ID
int buscarIndiceLeitor(int id) {
    for (int i = 0; i < totalLeitores; i++) {
        if (leitores[i].idLeitor == id) {
            return i;
        }
    }
    return -1;
}

// Salva os leitores no CSV
void salvarLeitoresCSV() {
    FILE *arquivo = fopen("leitores.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar leitores!\n");
        return;
    }

    for (int i = 0; i < totalLeitores; i++) {
        fprintf(arquivo, "%d;%s;%s;%d;%.2f;%d\n",
            leitores[i].idLeitor,
            leitores[i].nome,
            leitores[i].telefone,
            leitores[i].numeroCarteirinha,
            leitores[i].multaPendente,
            leitores[i].ativo);
    }

    fclose(arquivo);
}

// Carrega os leitores do CSV
void carregarLeitoresCSV() {
    FILE *arquivo = fopen("leitores.csv", "r");

    if (arquivo == NULL) {
        printf("Arquivo leitores.csv nao encontrado!\n");
        return;
    }

    totalLeitores = 0;

    while (totalLeitores < 50 &&
        fscanf(arquivo, " %d;%49[^;];%19[^;];%d;%f;%d",
            &leitores[totalLeitores].idLeitor,
            leitores[totalLeitores].nome,
            leitores[totalLeitores].telefone,
            &leitores[totalLeitores].numeroCarteirinha,
            &leitores[totalLeitores].multaPendente,
            &leitores[totalLeitores].ativo) == 6) {

        totalLeitores++;
    }

    fclose(arquivo);
}

// Cadastra um novo leitor
void cadastrarLeitor() {
    if (totalLeitores >= 50) {
        printf("Limite de leitores atingido!\n");
        return;
    }

    struct Leitor novo;

    printf("ID do leitor: ");
    scanf("%d", &novo.idLeitor);

    if (buscarIndiceLeitor(novo.idLeitor) != -1) {
        printf("Este ID ja existe!\n");
        return;
    }

    printf("Nome: ");
    scanf(" %49[^\n]", novo.nome);

    printf("Telefone: ");
    scanf(" %19[^\n]", novo.telefone);

    printf("Numero da carteirinha: ");
    scanf("%d", &novo.numeroCarteirinha);

    for (int i = 0; i < totalLeitores; i++) {
        if (leitores[i].numeroCarteirinha ==
            novo.numeroCarteirinha) {
            printf("Carteirinha ja cadastrada!\n");
            return;
        }
    }

    printf("Multa pendente: ");
    scanf("%f", &novo.multaPendente);

    if (novo.multaPendente < 0) {
        printf("A multa nao pode ser negativa!\n");
        return;
    }

    novo.ativo = 1;

    leitores[totalLeitores] = novo;
    totalLeitores++;

    salvarLeitoresCSV();

    printf("Leitor cadastrado com sucesso!\n");
}

// Lista os leitores
void listarLeitores() {
    printf("\n=== LEITORES CADASTRADOS ===\n");

    if (totalLeitores == 0) {
        printf("Nenhum leitor cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalLeitores; i++) {
        printf("\nID: %d\n", leitores[i].idLeitor);
        printf("Nome: %s\n", leitores[i].nome);
        printf("Telefone: %s\n", leitores[i].telefone);
        printf("Carteirinha: %d\n",
               leitores[i].numeroCarteirinha);
        printf("Multa: R$ %.2f\n",
               leitores[i].multaPendente);
        printf("Status: %s\n",
               leitores[i].ativo ? "Ativo" : "Inativo");
    }
}

// Busca um leitor pelo nome
void buscarLeitorPorNome() {
    char termo[50];
    int encontrados = 0;

    printf("Digite parte do nome: ");
    scanf(" %49[^\n]", termo);

    for (int i = 0; i < totalLeitores; i++) {
        if (strstr(leitores[i].nome, termo) != NULL) {
            printf("ID: %d | Nome: %s\n",
                   leitores[i].idLeitor,
                   leitores[i].nome);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum leitor encontrado.\n");
    }
}

// Edita os dados do leitor
void editarLeitor() {
    int id;

    printf("ID do leitor para editar: ");
    scanf("%d", &id);

    int pos = buscarIndiceLeitor(id);

    if (pos == -1) {
        printf("Leitor nao encontrado!\n");
        return;
    }

    printf("Novo nome: ");
    scanf(" %49[^\n]", leitores[pos].nome);

    printf("Novo telefone: ");
    scanf(" %19[^\n]", leitores[pos].telefone);

    printf("Nova multa pendente: ");
    float novaMulta;
    scanf("%f", &novaMulta);

    if (novaMulta < 0) {
        printf("Valor de multa invalido!\n");
        return;
    }

    leitores[pos].multaPendente = novaMulta;

    salvarLeitoresCSV();

    printf("Leitor atualizado!\n");
}

// Desativa um leitor
void removerLeitor() {
    int id;

    printf("ID do leitor para remover: ");
    scanf("%d", &id);

    int pos = buscarIndiceLeitor(id);

    if (pos == -1) {
        printf("Leitor nao encontrado!\n");
        return;
    }

    if (leitores[pos].ativo == 0) {
        printf("Leitor ja esta inativo!\n");
        return;
    }

    leitores[pos].ativo = 0;

    salvarLeitoresCSV();

    printf("Leitor desativado com sucesso!\n");
}

// Menu principal do modulo Yan
void moduloLeitores() {
    int opcao;

    do {
        printf("\n=== FICHARIO DE LEITORES ===\n");
        printf("1. Cadastrar leitor\n");
        printf("2. Listar leitores\n");
        printf("3. Buscar leitor por nome\n");
        printf("4. Editar leitor\n");
        printf("5. Remover / desativar leitor\n");
        printf("0. Voltar\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Digite um numero valido!\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                cadastrarLeitor();
                break;
            case 2:
                listarLeitores();
                break;
            case 3:
                buscarLeitorPorNome();
                break;
            case 4:
                editarLeitor();
                break;
            case 5:
                removerLeitor();
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);
}

#endif
