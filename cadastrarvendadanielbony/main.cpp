#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Estrutura do produto no estoque
struct Produto {
    int codigo;
    string nome;
    int quantidadeEstoque;
    float precoVenda;
};

// Estrutura do produto vendido
struct ProdutoVendido {
    string nome;
    int codigoProduto;
    int quantidadeVendida;
    float precoUnitario;
    float precoTotal;
};

// Estrutura da venda
struct Venda {
    int codigoVenda;
    vector<ProdutoVendido> produtos;
    float valorTotal;
};

// Vetores globais simulando cadastros
vector<Produto> estoque;
vector<Venda> vendas;

// Busca produto no estoque pelo código
Produto* buscarProduto(int codigo) {
    for (auto &p : estoque)
        if (p.codigo == codigo)
            return &p;
    return nullptr; // não encontrado
}

// Cadastro de venda
void cadastrarVenda() {
    Venda v;
    cout << "Codigo da venda: ";
    cin >> v.codigoVenda;

    int qtdProdutos;
    cout << "Quantidade de produtos na venda: ";
    cin >> qtdProdutos;

    v.valorTotal = 0;

    for (int i = 0; i < qtdProdutos; i++) {
        ProdutoVendido pv;
        cout << "\nProduto #" << i+1 << " - Codigo: ";
        cin >> pv.codigoProduto;

        Produto *prod = buscarProduto(pv.codigoProduto);
        if (!prod) {
            cout << "Produto nao encontrado!\n";
            i--; continue;
        }

        cout << "Quantidade vendida: ";
        cin >> pv.quantidadeVendida;

        if (pv.quantidadeVendida > prod->quantidadeEstoque) {
            cout << "Estoque insuficiente! Estoque atual: " << prod->quantidadeEstoque << endl;
            i--; continue;
        }

        pv.nome = prod->nome;
        pv.precoUnitario = prod->precoVenda;
        pv.precoTotal = pv.quantidadeVendida * pv.precoUnitario;

        // Atualiza estoque
        prod->quantidadeEstoque -= pv.quantidadeVendida;

        v.produtos.push_back(pv);
        v.valorTotal += pv.precoTotal;
    }

    vendas.push_back(v);
    cout << "\nVenda cadastrada com sucesso! Valor total: R$ " << v.valorTotal << endl;
}

// Consultar vendas
void consultarVendas() {
    for (auto &v : vendas) {
        cout << "\nVenda #" << v.codigoVenda << " - Total: R$ " << v.valorTotal << endl;
        for (auto &p : v.produtos)
            cout << "  Produto: " << p.nome << ", Qtde: " << p.quantidadeVendida << ", Total: R$ " << p.precoTotal << endl;
    }
}

// Alterar venda (exemplo simples)
void alterarVenda() {
    int codigo;
    cout << "Codigo da venda para alterar: ";
    cin >> codigo;
    for (auto &v : vendas) {
        if (v.codigoVenda == codigo) {
            cout << "Novo valor total: ";
            cin >> v.valorTotal;
            cout << "Venda alterada!\n";
            return;
        }
    }
    cout << "Venda nao encontrada!\n";
}

// Excluir venda
void excluirVenda() {
    int codigo;
    cout << "Codigo da venda para excluir: ";
    cin >> codigo;
    for (auto it = vendas.begin(); it != vendas.end(); ++it) {
        if (it->codigoVenda == codigo) {
            vendas.erase(it);
            cout << "Venda excluida!\n";
            return;
        }
    }
    cout << "Venda nao encontrada!\n";
}

// Funçao so pra testa o codigo
void carregarEstoque() {
    estoque.push_back({1, "Teclado", 10, 100});
    estoque.push_back({2, "Mouse", 20, 50});
    estoque.push_back({3, "Monitor", 5, 500});
}

int main() {
    carregarEstoque(); // só para teste

    int opcao;
    do {
        cout << "\n1-Cadastrar venda  2-Consultar vendas  3-Alterar venda  4-Excluir venda  0-Sair\nOpcao: ";
        cin >> opcao;
        switch(opcao) {
            case 1: cadastrarVenda(); break;
            case 2: consultarVendas(); break;
            case 3: alterarVenda(); break;
            case 4: excluirVenda(); break;
        }
    } while(opcao != 0);
    return 0;
}
