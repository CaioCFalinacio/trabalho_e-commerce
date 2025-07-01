#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


using namespace std;



// classe para endereco
class Endereco {
private:
    string rua;
    string bairro;
    string cidade;
    string estado;
    string cep;

public:
    // construtor
    Endereco(string r = "", string b = "", string cid = "",
             string est = "", string c = "")
        : rua(r), bairro(b), cidade(cid), estado(est), cep(c) {}

    // getters para acessar os dados
    string getRua() const { return rua; }
    string getBairro() const { return bairro; }
    string getCidade() const { return cidade; }
    string getEstado() const { return estado; }
    string getCep() const { return cep; }
};

// classe produto
class Produto {
private:
    string nome;
    string codigo;
    double precoVenda;

public:
    // construtor
    Produto(string n = "", string cod = "", double preco = 0.0)
        : nome(n), codigo(cod), precoVenda(preco) {}

    // getters
    string getNome() const { return nome; }
    string getCodigo() const { return codigo; }
    double getPrecoVenda() const { return precoVenda; }
};

// classe item de venda
class ItemVenda {
private:
    Produto produto; // O produto que foi vendido
    int quantidadeVendida;
    double precoTotalItem; // calcula quantidadeVendida * produto.precoVenda

public:
    // construtor
    ItemVenda(const Produto& prod, int qtdVendida)
        : produto(prod), quantidadeVendida(qtdVendida) {
        precoTotalItem = quantidadeVendida * produto.getPrecoVenda();
    }

    // getters
    const Produto& getProduto() const { return produto; } // retorna uma referencia ao produto
    int getQuantidadeVendida() const { return quantidadeVendida; }
    double getPrecoTotalItem() const { return precoTotalItem; }
};

// classe comprador
class Comprador {
private:
    string nome;
    string cpf;
    string email;
    Endereco enderecoEntrega;

public:
    // construtor
    Comprador(string n = "", string c = "", string e = "",
              const Endereco& end = Endereco())
        : nome(n), cpf(c), email(e), enderecoEntrega(end) {}

    // getters
    string getNome() const { return nome; }
    string getCpf() const { return cpf; }
    string getEmail() const { return email; }
    const Endereco& getEnderecoEntrega() const { return enderecoEntrega; }
};

// classe venda
class Venda {
private:
    int codigoVenda;
    vector<ItemVenda> itensVendidos;
    double valorTotalVenda; // valor total dos produtos na venda, sem frete

public:
    // construtor
    Venda(int cod = 0) : codigoVenda(cod), valorTotalVenda(0.0) {}

    // adiciona um item a venda e atualiza o valor total
    void adicionarItem(const ItemVenda& item) {
        itensVendidos.push_back(item);
        valorTotalVenda += item.getPrecoTotalItem(); // usa getter do ItemVenda
    }

    // getters
    int getCodigoVenda() const { return codigoVenda; }
    const vector<ItemVenda>& getItensVendidos() const { return itensVendidos; }
    double getValorTotalVenda() const { return valorTotalVenda; }
};

double calcularFrete(double valorTotalVenda) {
    if (valorTotalVenda <= 100.00) {
        return 30.00;
    } else if (valorTotalVenda > 100.00 && valorTotalVenda <= 300.00) {
        return 20.00;
    } else {
        return 0.00; // frete gratis
    }
}


void emitirNotaFiscal(const Comprador& comprador, const Venda& venda) {
    double valorFrete = calcularFrete(venda.getValorTotalVenda()); // usa getter
    double valorTotalComFrete = venda.getValorTotalVenda() + valorFrete; // usa getter

    cout << "\n-------------------- NOTA FISCAL --------------------" << endl;
    cout << "Codigo da Venda: " << venda.getCodigoVenda() << endl;
    cout << "-----------------------------------------------------" << endl;

    // dados do comprador
    cout << "DADOS DO COMPRADOR:" << endl;
    cout << "Nome: " << comprador.getNome() << endl;
    cout << "CPF: " << comprador.getCpf() << endl;
    cout << "E-mail: " << comprador.getEmail() << endl;
    cout << "Endereco de Entrega: " << comprador.getEnderecoEntrega().getRua() << ", "
         << comprador.getEnderecoEntrega().getBairro() << ", "
         << comprador.getEnderecoEntrega().getCidade() << " - "
         << comprador.getEnderecoEntrega().getEstado() << ", CEP: "
         << comprador.getEnderecoEntrega().getCep() << endl;
    cout << "-----------------------------------------------------" << endl;

    // descricao dos produtos vendidos
    cout << "PRODUTOS VENDIDOS:" << endl;
    cout << fixed << setprecision(2); // formata para 2 casas decimais

    if (venda.getItensVendidos().empty()) {
        cout << "  Nenhum produto listado nesta venda." << endl;
    } else {
        for (const auto& item : venda.getItensVendidos()) {
            cout << "  - Produto: " << item.getProduto().getNome()
                 << " (Cod: " << item.getProduto().getCodigo() << ")"
                 << " | Qtd: " << item.getQuantidadeVendida()
                 << " | Preco Unit.: R$ " << item.getProduto().getPrecoVenda()
                 << " | Total Item: R$ " << item.getPrecoTotalItem() << endl;
        }
    }
    cout << "-----------------------------------------------------" << endl;

    // resumo da venda
    cout << "RESUMO DA VENDA:" << endl;
    cout << "Valor Total dos Produtos: R$ " << venda.getValorTotalVenda() << endl;
    cout << "Custo do Frete:            R$ " << valorFrete << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "VALOR TOTAL DA NOTA:       R$ " << valorTotalComFrete << endl;
    cout << "-----------------------------------------------------\n" << endl;
}

int main() {
    // MAIN PRA TESTE

    //endereco
    Endereco end1("Rua Exemplo, 123", "Centro", "Cidade Teste", "MG", "30000-000");

    //comprador
    Comprador comprador1("Joao da Silva", "123.456.789-00", "joao.silva@email.com", end1);

    //produtos
    Produto prod1("Monitor LED 24", "MON24", 850.00);
    Produto prod2("Teclado Gamer", "TECGMR", 150.00);
    Produto prod3("Mouse Sem Fio", "MSWLS", 75.00);

    //venda
    Venda venda1(1001);

    //itens a venda
    ItemVenda item1(prod1, 1);
    ItemVenda item2(prod2, 2);
    ItemVenda item3(prod3, 3);

    venda1.adicionarItem(item1);
    venda1.adicionarItem(item2);
    venda1.adicionarItem(item3);

    //nota fiscal
    emitirNotaFiscal(comprador1, venda1);

    //segunda venda com frete gratis
    cout << "\n--- SEGUNDA VENDA ---" << endl;
    Endereco end2("Av. Principal, 456", "Bairro Novo", "Outra Cidade", "SP", "01000-000");
    Comprador comprador2("Maria Souza", "987.654.321-11", "maria.souza@email.com", end2);

    Produto prod4("Fone de Ouvido", "FONEBT", 250.00);
    Produto prod5("Webcam Full HD", "WEBCAMHD", 300.00);

    Venda venda2(1002);
    ItemVenda item4(prod4, 2);
    ItemVenda item5(prod5, 1);

    venda2.adicionarItem(item4);
    venda2.adicionarItem(item5);

    emitirNotaFiscal(comprador2, venda2);

    //venda com apenas um item
    cout << "\n--- TERCEIRA VENDA ---" << endl;
    Endereco end3("Rua da Paz, 789", "Jardim", "Pequena Vila", "RJ", "20000-000");
    Comprador comprador3("Pedro Almeida", "111.222.333-44", "pedro.almeida@email.com", end3);

    Produto prod6("Pen Drive 64GB", "PD64GB", 50.00);

    Venda venda3(1003);
    ItemVenda item6(prod6, 1);
    venda3.adicionarItem(item6);

    emitirNotaFiscal(comprador3, venda3);


    return 0;
}
