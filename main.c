
/* MODULO 1 - ACERVO DE LIVROS
   Autor: Joao Pedro */

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

void moduloLivros() {
    int opcao;

    do {
        printf("\n=== ACERVO DE LIVROS ===\n");
        printf("1. Cadastrar livro\n");
        printf("2. Listar / buscar livros\n");
        printf("3. Editar livro\n");
        printf("4. Remover livro\n");
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
