#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm> 

using namespace std;

class Produto {
public:
    string nome_produto;
    int codigo;
    int estoque;
    double preco_venda;

    Produto(string name, int cod, int qtd, double price) {
        nome_produto = name;
        codigo = cod;
        estoque = qtd;
        preco_venda = price;
    }
};

vector<Produto> listagem_produtos;

static int proximo_codigo = 1001;

bool codigo_igual(int codigo) {
    for (size_t i = 0; i < listagem_produtos.size(); i++) {
        if (listagem_produtos[i].codigo == codigo) {
            return true;
        }
    }
    return false;
}

void cadastro_produtos() {
    int codigo_final;
    int escolha_codigo;
    int quantidade;
    string nome;
    double preco;

    cout << "--- Cadastro de Novo Produto ---\n\n";

    cout << "Digite o codigo desejado para o produto (ou digite 0 para gerar um automaticamente): ";
    cin >> escolha_codigo;

    if (cin.fail()) {
        cout << "\nERRO: Entrada invalida. Por favor, digite um numero.\n\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (escolha_codigo == 0) {
        codigo_final = proximo_codigo++;
        cout << "Codigo automatico gerado: " << codigo_final << "\n";
    } else {
        if (codigo_igual(escolha_codigo)) {
            cout << "\nERRO: Ja existe um produto com o codigo " << escolha_codigo << "!\n";
            cout << "A operacao de cadastro foi cancelada.\n\n";
            return;
        }
        codigo_final = escolha_codigo;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "Digite o nome do produto: ";
        getline(cin, nome);
        nome.erase(0, nome.find_first_not_of(" \t\n\r"));
        nome.erase(nome.find_last_not_of(" \t\n\r") + 1);

        if (!nome.empty()) {
            break;
        }
        cout << "ERRO: O nome do produto nao pode ser em branco. Por favor, tente novamente.\n";
    }

    while (true) {
        cout << "Digite o estoque do produto: ";
        cin >> quantidade;
        if (cin.fail()) {
            cout << "ERRO: Entrada invalida. Digite um numero inteiro.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; 
        }
        if (quantidade >= 0) {
            break; 
        }
        cout << "ERRO: A quantidade em estoque nao pode ser um numero negativo.\n";
    }

    while (true) {
        cout << "Digite o preco do produto (R$): ";
        cin >> preco;
        if (cin.fail()) {
            cout << "ERRO: Entrada invalida. Digite um numero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (preco >= 0.0) {
            break;
        }
        cout << "ERRO: O preco do produto nao pode ser um numero negativo.\n";
    }

    Produto cadastroProduto(nome, codigo_final, quantidade, preco);
    listagem_produtos.push_back(cadastroProduto);
    cout << "\nCadastro do produto '" << nome << "' (Codigo: " << codigo_final << ") realizado!\n\n";
}

void alterar_produtos() {
    cout << "--- Alteracao de Produtos Cadastrados ---\n\n";

    if (listagem_produtos.empty()) {
        cout << "Nenhum produto cadastrado encontrado!\n";
        cout << "Encerrando operacao.\n\n";
        return;
    }

    int codigo_alterar;
    cout << "Digite o codigo do produto para alteracao: ";
    cin >> codigo_alterar;

    if (cin.fail()) {
        cout << "\nERRO: Codigo invalido. Digite apenas numeros.\n\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int indice_produto = -1;
    for (size_t i = 0; i < listagem_produtos.size(); i++) {
        if (listagem_produtos[i].codigo == codigo_alterar) {
            indice_produto = i;
            break;
        }
    }

    if (indice_produto == -1) {
        cout << "\nProduto com o codigo " << codigo_alterar << " nao encontrado.\n\n";
    } else {
        int opcao_mudar;
        do {
            cout << "\n--- Produto Encontrado ---\n";
            cout << "Codigo: " << listagem_produtos[indice_produto].codigo << "\n";
            cout << "1- Nome: " << listagem_produtos[indice_produto].nome_produto << "\n";
            cout << "2- Quantidade em Estoque: " << listagem_produtos[indice_produto].estoque << "\n";
            cout << "3- Preco da Venda: R$ " << listagem_produtos[indice_produto].preco_venda << "\n";
            cout << "-------------------------------------\n";
            cout << "Digite o campo para alterar (0 para finalizar): ";
            cin >> opcao_mudar;

            if (cin.fail()) {
                cout << "\nERRO: Opcao invalida. Digite apenas numeros.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                opcao_mudar = -1; 
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (opcao_mudar) {
                case 1: {
                    string novo_nome;
                    while (true) {
                        cout << "Digite o novo nome: ";
                        getline(cin, novo_nome);
                        novo_nome.erase(0, novo_nome.find_first_not_of(" \t\n\r"));
                        novo_nome.erase(novo_nome.find_last_not_of(" \t\n\r") + 1);
                        if (!novo_nome.empty()) {
                            listagem_produtos[indice_produto].nome_produto = novo_nome;
                            cout << "Nome alterado!\n";
                            break;
                        }
                        cout << "ERRO: O nome nao pode ser em branco.\n";
                    }
                    break;
                }
                case 2: {
                    int novo_estoque;
                    while (true) {
                        cout << "Digite o novo estoque: ";
                        cin >> novo_estoque;
                        if (cin.fail()) {
                            cout << "ERRO: Entrada invalida. Digite um numero inteiro.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (novo_estoque >= 0) {
                            listagem_produtos[indice_produto].estoque = novo_estoque;
                            cout << "Estoque alterado!\n";
                            break;
                        }
                        cout << "ERRO: O estoque nao pode ser um numero negativo.\n";
                    }
                    break;
                }
                case 3: {
                    double novo_preco;
                    while (true) {
                        cout << "Digite o novo preco de venda: R$ ";
                        cin >> novo_preco;
                        if (cin.fail()) {
                            cout << "ERRO: Entrada invalida. Digite um numero.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (novo_preco >= 0.0) {
                            listagem_produtos[indice_produto].preco_venda = novo_preco;
                            cout << "Preco alterado!\n";
                            break;
                        }
                        cout << "ERRO: O preco nao pode ser um numero negativo.\n";
                    }
                    break;
                }
                case 0:
                    cout << "Alteracoes concluidas. Retornando ao menu de produtos...\n\n";
                    break;
                default:
                    cout << "Opcao invalida!\n";
                    break;
            }
        } while (opcao_mudar != 0);
    }
}

void consultar_produtos() {
    cout << "--- Lista de Produtos Cadastrados ---\n";

    if (listagem_produtos.empty()) {
        cout << "Nenhum produto cadastrado no momento.\n\n";
        return;
    }

    for (size_t i = 0; i < listagem_produtos.size(); ++i) {
        cout << "-------------------------------------\n";
        cout << "Codigo: " << listagem_produtos[i].codigo << "\n";
        cout << "Nome: " << listagem_produtos[i].nome_produto << "\n";
        cout << "Quantidade em Estoque: " << listagem_produtos[i].estoque << "\n";
        cout << "Preco de Venda: R$ " << listagem_produtos[i].preco_venda << "\n";
    }
    cout << "-------------------------------------\n\n";
}

void excluir_produtos() {
    cout << "--- Excluir Produto ---\n\n";

    if (listagem_produtos.empty()) {
        cout << "Nenhum produto encontrado para exclusao!\n\n";
        return;
    }

    int codigo_excluir;
    cout << "Digite o codigo do produto para excluir: ";
    cin >> codigo_excluir;

    if (cin.fail()) {
        cout << "\nERRO: Codigo invalido. Digite apenas numeros.\n\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int indice_produto = -1;
    for (size_t i = 0; i < listagem_produtos.size(); ++i) {
        if (listagem_produtos[i].codigo == codigo_excluir) {
            indice_produto = i;
            break;
        }
    }

    if (indice_produto == -1) {
        cout << "\nProduto com codigo " << codigo_excluir << " nao encontrado!\n\n";
    } else {
        cout << "\n--- Produto Encontrado ---\n";
        cout << "Codigo: " << listagem_produtos[indice_produto].codigo << "\n";
        cout << "Nome: " << listagem_produtos[indice_produto].nome_produto << "\n";
        cout << "Estoque: " << listagem_produtos[indice_produto].estoque << "\n";

        char confirma;
        cout << "\nDeseja realmente excluir este produto? (S/N): ";
        cin >> confirma;

        if (confirma == 'S' || confirma == 's') {
            listagem_produtos.erase(listagem_produtos.begin() + indice_produto);
            cout << "\nProduto excluido com sucesso!\n\n";
        } else {
            cout << "\nExclusao cancelada pelo usuario.\n\n";
        }
    }
}

void menu_produtos() {
    int opcao;
    do {
        cout << "--- MENU - PRODUTOS ---\n";
        cout << "1- Cadastrar produtos\n";
        cout << "2- Alterar produtos\n";
        cout << "3- Consultar produtos\n";
        cout << "4- Excluir produtos\n";
        cout << "5- Voltar ao menu principal\n";
        cout << "-----------------------\n";
        cout << "Digite a sua escolha: ";
        cin >> opcao;

        if (cin.fail()) {
            cout << "\nERRO: Por favor, digite apenas numeros.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = 0; 
        }

        cout << "\n";

        switch (opcao) {
            case 1:
                cadastro_produtos();
                break;
            case 2:
                alterar_produtos();
                break;
            case 3:
                consultar_produtos();
                break;
            case 4:
                excluir_produtos();
                break;
            case 5:
                cout << "Retornando ao menu principal...\n\n";
                return;
            case 0:
                break;
            default:
                cout << "Opcao invalida! Tente novamente.\n\n";
        }
    } while (opcao != 5);
}

int main() {
    int opcao;
    do {
        cout << "====== MENU - COMERCIO ELETRONICO ======\n";
        cout << "1- Gerenciar Produtos\n";
        cout << "2- Gerenciar Vendedores (Nao implementado)\n";
        cout << "3- Gerenciar Compradores (Nao implementado)\n";
        cout << "4- Realizar Venda (Nao implementado)\n";
        cout << "5- Emitir Nota Fiscal (Nao implementado)\n";
        cout << "0- Sair\n";
        cout << "========================================\n";
        cout << "Digite a sua escolha: ";
        cin >> opcao;

        if (cin.fail()) {
            cout << "\nERRO: Por favor, digite apenas numeros.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
        }

        cout << "\n";

        switch (opcao) {
            case 1:
                menu_produtos();
                break;
            case 2:
                //menu_vendedores();
                break;
            case 3:
                //compradores..
                break;
            case 4:
                //vendas..
                break;
            case 5:
                //nota fiscal...
                break;
            case 0:
                cout << "Fim de execucao do programa.\n";
                break;
            default:
                cout << "Opcao invalida! Tente novamente.\n\n";
        }
    } while (opcao != 0);

    return 0;
}
