
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



/* MODULO 4 - RESERVAS E RELATORIOS
   Autor: André Fogaça - RGM: 48380831 */

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
                printf("Cancelamento em construcao\n");
                break;
            case 5:
                printf("Relatorio de livros em construcao\n");
                break;
            case 6:
                printf("Relatorio de leitores em construcao\n");
                break;
            case 7:
                printf("Relatorio de emprestimos em construcao\n");
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }

    } while (opcao != 0);
}
