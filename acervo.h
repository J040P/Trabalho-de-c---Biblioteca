
#ifndef ACERVO_H
#define ACERVO_H

#include <stdio.h>
#include <string.h>

// MODULO 1 - ACERVO DE LIVROS
// Autor: Joao Pedro

struct Livro {
    int idLivro;
    char titulo[50];
    char autor[50];
    int anoPublicacao;
    float valorEstimado;
    int disponivel;
};

struct Livro acervo[50];
int totalLivros = 0;

// Procura um livro pelo ID
int buscarIndiceLivro(int id) {
    for (int i = 0; i < totalLivros; i++) {
        if (acervo[i].idLivro == id) {
            return i;
        }
    }
    return -1;
}

// Salva os livros no arquivo CSV
void salvarLivrosCSV() {
    FILE *arquivo = fopen("livros.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar livros!\n");
        return;
    }

    for (int i = 0; i < totalLivros; i++) {
        fprintf(arquivo, "%d;%s;%s;%d;%.2f;%d\n",
            acervo[i].idLivro,
            acervo[i].titulo,
            acervo[i].autor,
            acervo[i].anoPublicacao,
            acervo[i].valorEstimado,
            acervo[i].disponivel);
    }

    fclose(arquivo);
}

// Carrega os livros do CSV para a memoria
void carregarLivrosCSV() {
    FILE *arquivo = fopen("livros.csv", "r");

    if (arquivo == NULL) {
        printf("Arquivo livros.csv nao encontrado!\n");
        return;
    }

    totalLivros = 0;

    while (totalLivros < 50 &&
        fscanf(arquivo, " %d;%49[^;];%49[^;];%d;%f;%d",
            &acervo[totalLivros].idLivro,
            acervo[totalLivros].titulo,
            acervo[totalLivros].autor,
            &acervo[totalLivros].anoPublicacao,
            &acervo[totalLivros].valorEstimado,
            &acervo[totalLivros].disponivel) == 6) {
        totalLivros++;
    }

    fclose(arquivo);
}

// Cadastra um novo livro
void cadastrarLivro() {
    if (totalLivros >= 50) {
        printf("Acervo cheio!\n");
        return;
    }

    struct Livro novo;

    printf("ID do livro: ");
    if (scanf("%d", &novo.idLivro) != 1) {
        printf("ID invalido!\n");
        return;
    }

    if (buscarIndiceLivro(novo.idLivro) != -1) {
        printf("Esse ID ja existe!\n");
        return;
    }

    printf("Titulo: ");
    scanf(" %49[^\n]", novo.titulo);

    printf("Autor: ");
    scanf(" %49[^\n]", novo.autor);

    printf("Ano de publicacao: ");
    scanf("%d", &novo.anoPublicacao);

    printf("Valor estimado: ");
    scanf("%f", &novo.valorEstimado);

    novo.disponivel = 1;

    acervo[totalLivros] = novo;
    totalLivros++;

    salvarLivrosCSV();
    printf("Livro cadastrado!\n");
}

// Lista todos os livros
void listarLivros() {
    printf("\n=== LIVROS CADASTRADOS ===\n");

    if (totalLivros == 0) {
        printf("Nenhum livro encontrado.\n");
        return;
    }

    for (int i = 0; i < totalLivros; i++) {
        printf("\nID: %d\n", acervo[i].idLivro);
        printf("Titulo: %s\n", acervo[i].titulo);
        printf("Autor: %s\n", acervo[i].autor);
        printf("Ano: %d\n", acervo[i].anoPublicacao);
        printf("Valor: R$ %.2f\n",
               acervo[i].valorEstimado);
        printf("Disponivel: %s\n",
               acervo[i].disponivel ? "Sim" : "Nao");
    }
}

// Busca livros pelo titulo
void buscarLivroPorTitulo() {
    char termo[50];
    int encontrados = 0;

    printf("Digite parte do titulo: ");
    scanf(" %49[^\n]", termo);

    for (int i = 0; i < totalLivros; i++) {
        if (strstr(acervo[i].titulo, termo) != NULL) {
            printf("ID: %d | %s\n",
                   acervo[i].idLivro,
                   acervo[i].titulo);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum livro encontrado.\n");
    }
}

// Edita informacoes de um livro
void editarLivro() {
    int id;

    printf("ID do livro para editar: ");
    scanf("%d", &id);

    int pos = buscarIndiceLivro(id);

    if (pos == -1) {
        printf("Livro nao encontrado!\n");
        return;
    }

    printf("Novo titulo: ");
    scanf(" %49[^\n]", acervo[pos].titulo);

    printf("Novo autor: ");
    scanf(" %49[^\n]", acervo[pos].autor);

    printf("Novo ano: ");
    scanf("%d", &acervo[pos].anoPublicacao);

    printf("Novo valor: ");
    scanf("%f", &acervo[pos].valorEstimado);

    salvarLivrosCSV();
    printf("Livro atualizado!\n");
}

// Remove um livro pelo ID
void removerLivro() {
    int id;

    printf("ID do livro para remover: ");
    scanf("%d", &id);

    int pos = buscarIndiceLivro(id);

    if (pos == -1) {
        printf("Livro nao encontrado!\n");
        return;
    }

    if (acervo[pos].disponivel == 0) {
        printf("Livro emprestado. Remocao bloqueada!\n");
        return;
    }

    for (int i = pos; i < totalLivros - 1; i++) {
        acervo[i] = acervo[i + 1];
    }

    totalLivros--;

    salvarLivrosCSV();
    printf("Livro removido!\n");
}

// Submenu do Acervo
void moduloLivros() {
    int opcao;

    do {
        printf("\n=== ACERVO DE LIVROS ===\n");
        printf("1. Cadastrar livro\n");
        printf("2. Listar livros\n");
        printf("3. Buscar livro pelo titulo\n");
        printf("4. Editar livro\n");
        printf("5. Remover livro\n");
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
                cadastrarLivro();
                break;
            case 2:
                listarLivros();
                break;
            case 3:
                buscarLivroPorTitulo();
                break;
            case 4:
                editarLivro();
                break;
            case 5:
                removerLivro();
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
