#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Produto {
public:
    string nome_produto;
    int codigo;
    int estoque;
    double preco_venda;

    Produto(string name, int cod, int qtd, double price){
        nome_produto = name;
        codigo = cod;
        estoque = qtd;
        preco_venda = price;
    }
};

vector <Produto> listagem_produtos;

bool codigo_igual(int codigo){
    for (int i = 0; i < listagem_produtos.size(); i++) {
        if (listagem_produtos[i].codigo == codigo) {
            return true;
        }
    }
    return false;
}



void cadastro_produtos() {
    int codigo;
    int quantidade;
    string nome;
    double preco;

    cout << "Cadastro do Produto: \n ";
    cout << "Digite o codigo que sera cadastrado: ";
    cin >> codigo;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (codigo_igual(codigo)){
        cout << "Ja existe um produto com este codigo! \n";
        cout << "Erro de operacao! \n\n";
        return;
    }

    cout << "Digite o nome do produto: ";
    getline(cin, nome);

    cout << "Digite o estoque do produto: ";
    cin >> quantidade;

    cout << "Digite o preco do produto (R$): ";
    cin >> preco;

    Produto cadastroProduto (nome, codigo, quantidade, preco);

    listagem_produtos.push_back(cadastroProduto);

    cout << "\nCadastro do produto ' " << nome << " ' realizado!\n\n";

}
void alterar_produtos() {
    cout << "Alteracao de Produtos Cadastrados: \n";

    if (listagem_produtos.empty()){
        cout << "Nenhum produto cadastrado encontrado! \n";
        cout << "Encerrando operacao! \n\n";
        return;
    }

    int codigo_alterar;
    cout<< "Digite o codigo do produto para alteracao: ";
    cin >> codigo_alterar;

    int analise_produto = -1;

    for (int i = 0; i < listagem_produtos.size(); i++){
        if (listagem_produtos[i].codigo == codigo_alterar) {
            analise_produto = i;
            break;
        }
    }

    if (analise_produto == -1){
            cout << "\nProduto com o codigo " << codigo_alterar << " nao encontrado.\n\n";
    }
    else {
        int opcao_mudar;
        do {
            cout << "\n Produto encontrado \n";
            cout << "Codigo: " << listagem_produtos[analise_produto].codigo << "\n";
            cout << "1- Nome: " << listagem_produtos[analise_produto].nome_produto << "\n";
            cout << "2- Quantidade em Estoque: " << listagem_produtos[analise_produto].estoque << "\n";
            cout << "3- Preco da Venda: R$ " << listagem_produtos[analise_produto].preco_venda << "\n";
            cout << "\n\n";

            cout << "Digite a escolha de alteracao (0 para finalizar): ";
            cin >> opcao_mudar;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (opcao_mudar){
        case 1: {
            string novo_nome;
            cout << "Digite o novo nome: ";
            getline(cin, novo_nome);
            listagem_produtos[analise_produto].nome_produto = novo_nome;
            cout << "Nome alterado!\n";
            break;
        }
            case 2: {
            int novo_estoque;
            cout << "Digite o novo estoque: ";
            cin >> novo_estoque;
            listagem_produtos[analise_produto].estoque = novo_estoque;
            cout << "Estoque alterado!\n";
            break;
            }
            case 3: {
            double novo_preco;
            cout << "Digite o novo preco de venda: R$ ";
            cin >> novo_preco;
            listagem_produtos[analise_produto].preco_venda = novo_preco;
            cout << "Preco alterado!\n";
            break;
            }
            case 0:
                cout << "Alteracoes concluidas. Retorno ao menu de produtos... \n\n";
                break;
            default:
                cout << "Opcao invalida!\n";
                break;
            }


        }while (opcao_mudar != 0);
    }
}
void consultar_produtos() {
    cout << " Lista de Produtos: \n";

    if (listagem_produtos.empty()) {
        cout << "Sem produtos cadastrados. \n\n";
        return;
    }

    for (size_t i = 0; i < listagem_produtos.size(); ++i) {
        cout << "\n";
        cout << "Codigo: " << listagem_produtos[i].codigo << "\n";
        cout << "Nome: " << listagem_produtos[i].nome_produto << "\n";
        cout << "Quantidade em Estoque: " << listagem_produtos[i].estoque << "\n";
        cout << "Preco de Venda: R$ " << listagem_produtos[i].preco_venda << "\n";
    }
    cout << "\n\n";
}

void excluir_produtos() {
    cout << "Excluir Produto: \n";

    if (listagem_produtos.empty()){
        cout << "Nenhum produto encontrado para exclusao!\n\n";
        return;
    }

    int codigo_excluir;
    cout << "Digite o codigo do produto para exlcuir: ";
    cin >> codigo_excluir;

    int alterar_produtos = -1;

    for (int i = 0; i < listagem_produtos.size(); ++i){
        if (listagem_produtos[i].codigo == codigo_excluir){
            alterar_produtos = i;
            break;
        }
    }

    if (alterar_produtos == -1){
        cout << "\nProduto com codigo " << codigo_excluir << " nao encontrado!\n\n";
    }
    else{
        cout << "\n Produto Encontrado: \n";
        cout << "Codigo: " << listagem_produtos[alterar_produtos].codigo << "\n";
        cout << "Nome: " << listagem_produtos[alterar_produtos].nome_produto << "\n";
        cout << "Quantidade em Estoque: " << listagem_produtos[alterar_produtos].estoque << "\n";
        cout << "\n";
    }

    char confirma;
    cout << "Deseja mesmo exlcuir o produto? (S/N): ";
    cin >> confirma;

    if (confirma == 'S' || confirma == 's'){
        listagem_produtos.erase(listagem_produtos.begin() + alterar_produtos);
        cout << "\nProduto excluido!\n\n";
        }
        else{
            cout << "\nExclusao cancelada.\n\n";
        }
    }


    void menu_produtos(){

        int opcao;

    do{
        cout << " MENU - Produtos \n";
        cout << "1- Cadastrar produtos; \n";
        cout << "2- Alterar produtos; \n";
        cout << "3- Consultar produtos; \n";
        cout << "4- Excluir produtos; \n";
        cout << "5- Voltar ao menu principal; \n";
        cout << "\n";
        cout << "Digite a escolha: ";
        cin >> opcao;

        cout << "\n";

        switch (opcao){
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
            return;
        default:
            cout << "Opcao invalida!";
        }

    }while (opcao != 0);

    }


int main(){

    int opcao;

do{
    cout << "MENU - COMERCIO ELETRONICO \n";
    cout << "1- Cadastrar Produto; \n";
    cout << "2- Cadastrar Vendedor; \n";
    cout << "3- Cadastrar Comprador; \n";
    cout << "4- Cadastrar Venda; \n";
    cout << "5- Emissao de Nota Fiscal; \n";
    cout << "0 - Sair \n";

    cout << "\n \n";

    cout << "Digite a sua escolha: ";
    cin >> opcao;

    cout << "\n";

    switch (opcao){
        case 1:
        menu_produtos();
        break;
        case 2:
            alterar_produtos();
        //função de cadastro de vendedor (função que vai abrir um menu para os vendedores);
        //menu_vendedores(); //função para o menu de cadastro dos vendedores.
        break;
        case 3:
        //função de cadastro de comprador
        break;
        case 4:
        //função de cadastro de vendas
        break;
        case 5:
        //função de emissão de nota fiscal
        break;
        case 0:
        cout << "Fim de execucao!";
        return 0;
        break;
        default:
            cout << "Opcao invalida! \n";
    };        }while(opcao != 0);

    return 0;
}
