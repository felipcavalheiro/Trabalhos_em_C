#include <stdio.h>
#include <string.h>

#define MAX_CLIENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_CPF_LENGTH 15
#define MAX_PASSWORD_LENGTH 20

struct Cliente {
    char nome[MAX_NAME_LENGTH];
    int idade;
    char cpf[MAX_CPF_LENGTH];
    char senha[MAX_PASSWORD_LENGTH];
    double saldo;
};

struct Cliente clientes[MAX_CLIENTS];
int clientCount = 0;
int usuarioLogado = -1;

void cadastrarCliente();
void listarClientes();
void realizarLogin();
void fazerDeposito();
void fazerSaque();
void salvarDados();
void carregarDados();
void liberarMemoria();

int main() {
    
	carregarDados(); // Carrega os dados dos clientes do arquivo

    int escolha;

    do {
        printf("\nMenu Principal:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar clientes\n");
        printf("3. Fazer login\n");
        printf("4. Fazer depósito\n");
        printf("5. Fazer saque\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                realizarLogin();
                break;
            case 4:
                fazerDeposito();
                break;
            case 5:
                fazerSaque();
                break;
            case 6:
                printf("Saindo do programa. Obrigado!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (escolha != 6);

    salvarDados(); // Salva os dados dos clientes no arquivo
    liberarMemoria(); // Libera a memória alocada

    return 0;
}

void cadastrarCliente() {
    if (clientCount < MAX_CLIENTS) {
        struct Cliente novoCliente;

        printf("Digite o nome do cliente: ");
        scanf("%s", novoCliente.nome);

        printf("Digite a idade do cliente: ");
        scanf("%d", &novoCliente.idade);

        printf("Digite o CPF do cliente: ");
        scanf("%s", novoCliente.cpf);

        printf("Digite a senha do cliente: ");
        scanf("%s", novoCliente.senha);

        novoCliente.saldo = 0.0;

        clientes[clientCount++] = novoCliente;

        printf("Cliente cadastrado com sucesso!\n");
    } else {
        printf("Limite de clientes atingido. Impossivel cadastrar mais clientes.\n");
    }
}

void listarClientes() {
    int i = 0;
		printf("\nClientes Cadastrados:\n");
    for (i = 0; i < clientCount; i++) {
        printf("Nome: %s\n", clientes[i].nome);
        printf("Idade: %d\n", clientes[i].idade);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Saldo: R$%.2f\n", clientes[i].saldo);
        printf("\n");
    }
}

void realizarLogin() {
    int i = 0;
	char cpf[MAX_CPF_LENGTH];
    char senha[MAX_PASSWORD_LENGTH];

    printf("Digite o CPF: ");
    scanf("%s", cpf);

    printf("Digite a senha: ");
    scanf("%s", senha);

    for (i = 0; i < clientCount; i++) {
        
		if (strcmp(cpf, clientes[i].cpf) == 0 && strcmp(senha, clientes[i].senha) == 0) {
            printf("Login bem-sucedido! Bem-vindo, %s!\n", clientes[i].nome);
            usuarioLogado = i;
            return;
        }
    }

    printf("CPF ou senha incorretos. Tente novamente.\n");
}

void fazerDeposito() {
    if (usuarioLogado != -1) {
        double valorDeposito;
        printf("Digite o valor do deposito: R$");
        scanf("%lf", &valorDeposito);

        clientes[usuarioLogado].saldo += valorDeposito;
        printf("Deposito de R$%.2f realizado. Saldo atual: R$%.2f\n", valorDeposito, clientes[usuarioLogado].saldo);
    } else {
        printf("Nenhum cliente logado. Realize o login antes de fazer um deposito.\n");
    }
}

void fazerSaque() {
    if (usuarioLogado != -1) {
        double valorSaque;
        printf("Digite o valor do saque: R$");
        scanf("%lf", &valorSaque);

        if (valorSaque <= clientes[usuarioLogado].saldo) {
            clientes[usuarioLogado].saldo -= valorSaque;
            printf("Saque de R$%.2f realizado. Saldo atual: R$%.2f\n", valorSaque, clientes[usuarioLogado].saldo);
        } else {
            printf("Saldo insuficiente. Saque nao realizado.\n");
        }
    } else {
        printf("Nenhum cliente logado. Realize o login antes de fazer um saque.\n");
    }
}

void salvarDados() {
    int i = 0;
	FILE *arquivo;
    arquivo = fopen("dados_clientes.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (i = 0; i < clientCount; i++) {
        fprintf(arquivo, "%s %d %s %s %.2f\n",
                clientes[i].nome, clientes[i].idade, clientes[i].cpf, clientes[i].senha, clientes[i].saldo);
    }

    fclose(arquivo);
}

void carregarDados() {
    FILE *arquivo;
    arquivo = fopen("dados_clientes.txt", "r");

    if (arquivo == NULL) {
        // Se o arquivo não existir, não exibe a mensagem de erro
        return;
    }

    while (fscanf(arquivo, "%s %d %s %s %lf\n",
                  clientes[clientCount].nome, &clientes[clientCount].idade,
                  clientes[clientCount].cpf, clientes[clientCount].senha, &clientes[clientCount].saldo) == 5) {
        clientCount++;
    }

    fclose(arquivo);
}

void liberarMemoria() {
}

void excluirConta
