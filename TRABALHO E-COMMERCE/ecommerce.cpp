#include <iostream>     // Biblioteca para entrada e saída padrão
#include <string>       // Biblioteca para manipulação de strings
#include <vector>       // Biblioteca para uso do vetor dinâmico
#include <limits>       // Biblioteca para manipulação de limites de tipos numéricos
#include <algorithm>    // Biblioteca para algoritmos padrão
#include <windows.h>    // Biblioteca para Sleep() e system()
#include <iomanip>      // Biblioteca para formatação de saída (setprecision)

using namespace std;

const double SALARIO_MINIMO = 1412.00; // Valor do salário mínimo para validação

// Classe que representa um endereço genérico
class Endereco {
public:
    string rua;
    string bairro;
    string cidade;
    string estado;
    string cep;

    // Lê os dados do endereço do usuário
    void lerEndereco() {
        cout << "Rua: ";
        getline(cin, rua);
        cout << "Bairro: ";
        getline(cin, bairro);
        cout << "Cidade: ";
        getline(cin, cidade);
        cout << "Estado: ";
        getline(cin, estado);
        cout << "CEP: ";
        getline(cin, cep);
    }

    // Exibe o endereço formatado
    void mostrarEndereco() const {
        cout << rua << ", " << bairro << ", " << cidade << " - " << estado << ", CEP: " << cep;
    }
};

// Classe que representa um comprador do sistema
class Comprador {
private:
    string nome;
    string cpf;
    string email;
    Endereco endereco;

public:
    // Retorna o CPF do comprador (usado para buscas)
    string getCpf() const { return cpf; }

    // Função para cadastrar um novo comprador
    void cadastrar() {
        cout << "\n--- CADASTRO DE COMPRADOR ---\n";
        cout << "Nome: ";
        getline(cin, nome);
        cout << "CPF: ";
        getline(cin, cpf);
        cout << "Email: ";
        getline(cin, email);
        cout << "\n--- ENDERECO ---\n";
        endereco.lerEndereco();
    }

    // Exibe os dados do comprador
    void mostrar() const {
        cout << "Nome: " << nome << endl;
        cout << "CPF: " << cpf << endl;
        cout << "Email: " << email << endl;
        cout << "Endereco: ";
        endereco.mostrarEndereco();
        cout << endl;
    }

    // Permite alterar os dados do comprador
    void alterar() {
        cout << "\n--- ALTERAR DADOS ---\n";
        cout << "Novo nome: ";
        getline(cin, nome);
        cout << "Novo email: ";
        getline(cin, email);
        cout << "\n--- NOVO ENDERECO ---\n";
        endereco.lerEndereco();
        cout << "Comprador alterado com sucesso!\n";
    }
};

// Classe para gerenciar uma lista de compradores
class CadastroCompradores {
private:
    vector<Comprador> lista; // Vetor que armazena todos os compradores

public:
    // Cadastra um novo comprador
    void cadastrarComprador() {
        Comprador novo;
        novo.cadastrar();
        lista.push_back(novo);
        cout << "Comprador cadastrado com sucesso!\n";
    }

    // Exibe todos os compradores cadastrados
    void consultarCompradores() const {
        cout << "\n--- LISTA DE COMPRADORES ---\n";
        if (lista.empty()) {
            cout << "Nenhum comprador cadastrado.\n";
            return;
        }
        for (size_t i = 0; i < lista.size(); i++) {
            cout << "\nComprador " << i + 1 << ":" << endl;
            lista[i].mostrar();
        }
    }

    // Permite alterar um comprador pelo CPF
    void alterarComprador() {
        if (lista.empty()) {
            cout << "Nenhum comprador cadastrado para alterar.\n";
            return;
        }
        string cpfBusca;
        cout << "\nDigite o CPF do comprador que deseja alterar: ";
        getline(cin, cpfBusca);

        for (Comprador& c : lista) {
            if (c.getCpf() == cpfBusca) {
                c.alterar();
                return;
            }
        }
        cout << "CPF nao encontrado.\n";
    }

    // Permite excluir um comprador pelo CPF
    void excluirComprador() {
         if (lista.empty()) {
            cout << "Nenhum comprador cadastrado para excluir.\n";
            return;
        }
        string cpfBusca;
        cout << "\nDigite o CPF do comprador que deseja excluir: ";
        getline(cin, cpfBusca);

        for (size_t i = 0; i < lista.size(); i++) {
            if (lista[i].getCpf() == cpfBusca) {
                lista.erase(lista.begin() + i);
                cout << "Comprador excluido com sucesso!\n";
                return;
            }
        }
        cout << "CPF nao encontrado.\n";
    }

    // Menu interativo para gerenciamento de compradores
    void menuCompradores() {
        int opcao;
        do {
            system("cls");
            cout << "\n====== MENU COMPRADORES ======\n";
            cout << "1 - Cadastrar Comprador\n";
            cout << "2 - Consultar Compradores\n";
            cout << "3 - Alterar Comprador\n";
            cout << "4 - Excluir Comprador\n";
            cout << "0 - Voltar ao menu principal\n";
            cout << "==============================\n";
            cout << "Escolha uma opcao: ";
            cin >> opcao;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada

            switch (opcao) {
                case 1: cadastrarComprador(); Sleep(2000); break;
                case 2: consultarCompradores(); system("pause"); break;
                case 3: alterarComprador(); Sleep(2000); break;
                case 4: excluirComprador(); Sleep(2000); break;
                case 0: cout << "Retornando ao menu principal...\n"; Sleep(1000); break;
                default: cout << "Opcao invalida!\n"; Sleep(1000); break;
            }
        } while (opcao != 0);
    }
};

// Classe que representa um vendedor do sistema
class Vendedor
{
private:
    string nome_vendedor;
    int id_vendedor;
    double salario_fixo;
    double total_comissoes = 0;
    static int proximo_id; // Variável estática para gerar IDs únicos
public:
    static constexpr float taxa_comissao = 0.03; // Taxa de comissão fixa
    Vendedor() {}
    Vendedor(string nome, double salario) {
        set_nome_vendedor(nome);
        set_salario_fixo(salario);
        set_id_vendedor();
    }

    // Métodos de acesso
    string get_nome_vendedor() { return nome_vendedor; }
    int get_id_vendedor() { return id_vendedor; }
    double get_salario_fixo() { return salario_fixo; }
    double get_salario_total() { return (salario_fixo + total_comissoes); }

    // Métodos de modificação e consulta
    void set_nome_vendedor(string novo_nome);
    void set_salario_fixo(double novo_salario);
    void set_id_vendedor();
    void consultar_vendedor();
    void registrar_venda(double valor_venda);
};

// Classe que representa um produto
class Produto {
public:
    string nome_produto;
    int codigo;
    int estoque;
    double preco_venda;

    // Construtor com valores padrão
    Produto(string name = "", int cod = 0, int qtd = 0, double price = 0.0) {
        nome_produto = name;
        codigo = cod;
        estoque = qtd;
        preco_venda = price;
    }
};

// Estrutura para armazenar informações de um produto vendido em uma venda
class ProdutoVendido {
public:
    string nome;
    int codigoProduto;
    int quantidadeVendida;
    double precoUnitario;
    double precoTotal;
};

// Estrutura para armazenar uma venda
class Venda {
public:
    int codigoVenda;
    vector<ProdutoVendido> produtos;
    double valorTotal;
};

// Classes auxiliares para emissão de nota fiscal (NF)
class NF_Endereco {
private:
    string rua, bairro, cidade, estado, cep;
public:
    NF_Endereco(string r = "", string b = "", string cid = "",
                string est = "", string c = "")
        : rua(r), bairro(b), cidade(cid), estado(est), cep(c) {}

    string getRua() const { return rua; }
    string getBairro() const { return bairro; }
    string getCidade() const { return cidade; }
    string getEstado() const { return estado; }
    string getCep() const { return cep; }
};

class NF_Produto {
private:
    string nome, codigo;
    double precoVenda;
public:
    NF_Produto(string n = "", string cod = "", double preco = 0.0)
        : nome(n), codigo(cod), precoVenda(preco) {}

    string getNome() const { return nome; }
    string getCodigo() const { return codigo; }
    double getPrecoVenda() const { return precoVenda; }
};

class NF_ItemVenda {
private:
    NF_Produto produto;
    int quantidadeVendida;
    double precoTotalItem;
public:
    NF_ItemVenda(const NF_Produto& prod, int qtdVendida)
        : produto(prod), quantidadeVendida(qtdVendida) {
        precoTotalItem = quantidadeVendida * produto.getPrecoVenda();
    }

    const NF_Produto& getProduto() const { return produto; }
    int getQuantidadeVendida() const { return quantidadeVendida; }
    double getPrecoTotalItem() const { return precoTotalItem; }
};

class NF_Comprador {
private:
    string nome, cpf, email;
    NF_Endereco enderecoEntrega;
public:
    NF_Comprador(string n = "", string c = "", string e = "",
                 const NF_Endereco& end = NF_Endereco())
        : nome(n), cpf(c), email(e), enderecoEntrega(end) {}

    string getNome() const { return nome; }
    string getCpf() const { return cpf; }
    string getEmail() const { return email; }
    const NF_Endereco& getEnderecoEntrega() const { return enderecoEntrega; }
};

class NF_Venda {
private:
    int codigoVenda;
    vector<NF_ItemVenda> itensVendidos;
    double valorTotalVenda;
public:
    NF_Venda(int cod = 0) : codigoVenda(cod), valorTotalVenda(0.0) {}

    void adicionarItem(const NF_ItemVenda& item) {
        itensVendidos.push_back(item);
        valorTotalVenda += item.getPrecoTotalItem();
    }

    int getCodigoVenda() const { return codigoVenda; }
    const vector<NF_ItemVenda>& getItensVendidos() const { return itensVendidos; }
    double getValorTotalVenda() const { return valorTotalVenda; }
};

// Instâncias e variáveis globais
CadastroCompradores cadastro_global_compradores;
int Vendedor::proximo_id = 1;
Vendedor vendedores[100];
int total_vendedores = 0;
vector<Produto> listagem_produtos;
vector<Venda> vendas;
static int proximo_codigo = 1001;

// Implementação dos métodos da classe Vendedor
void Vendedor::set_nome_vendedor(string novo_nome) { nome_vendedor = novo_nome; }
void Vendedor::set_salario_fixo(double novo_salario) { salario_fixo = novo_salario; }
void Vendedor::set_id_vendedor() { id_vendedor = proximo_id++; }
void Vendedor::registrar_venda(double valor_venda) { total_comissoes += valor_venda * taxa_comissao; }
void Vendedor::consultar_vendedor() {
    cout << "-------------------------------------\n";
    cout << "Nome do vendedor: " << nome_vendedor << endl;
    cout << "ID: " << id_vendedor << endl;
    cout << "Salario fixo: R$" << fixed << setprecision(2) << salario_fixo << endl;
    cout << "Comissoes acumuladas: R$" << fixed << setprecision(2) << total_comissoes << endl;
    cout << "Salario total: R$" << fixed << setprecision(2) << get_salario_total() << endl;
    cout << "-------------------------------------\n";
}

// --- FUNÇÕES MÓDULO NOTA FISCAL ---

// Calcula o valor do frete de acordo com o valor total da venda
double calcularFrete(double valorTotalVenda) {
    if (valorTotalVenda <= 100.00) return 30.00;
    else if (valorTotalVenda <= 300.00) return 20.00;
    else return 0.00;
}

// Exibe a nota fiscal formatada na tela
void emitirNotaFiscal(const NF_Comprador& comprador, const NF_Venda& venda) {
    double valorFrete = calcularFrete(venda.getValorTotalVenda());
    double valorTotalComFrete = venda.getValorTotalVenda() + valorFrete;

    system("cls");
    cout << "\n-------------------- NOTA FISCAL --------------------" << endl;
    cout << "Codigo da Venda: " << venda.getCodigoVenda() << endl;
    cout << "-----------------------------------------------------" << endl;

    cout << "DADOS DO COMPRADOR:\n";
    cout << "Nome: " << comprador.getNome() << "\nCPF: " << comprador.getCpf()
         << "\nE-mail: " << comprador.getEmail() << "\nEndereco de Entrega: "
         << comprador.getEnderecoEntrega().getRua() << ", "
         << comprador.getEnderecoEntrega().getBairro() << ", "
         << comprador.getEnderecoEntrega().getCidade() << " - "
         << comprador.getEnderecoEntrega().getEstado() << ", CEP: "
         << comprador.getEnderecoEntrega().getCep() << endl;
    cout << "-----------------------------------------------------" << endl;

    cout << "PRODUTOS VENDIDOS:\n";
    cout << fixed << setprecision(2);
    if (venda.getItensVendidos().empty()) {
        cout << "  Nenhum produto listado nesta venda.\n";
    } else {
        for (const auto& item : venda.getItensVendidos()) {
            cout << "  - Produto: " << item.getProduto().getNome()
                 << " (Cod: " << item.getProduto().getCodigo() << ")"
                 << " | Qtd: " << item.getQuantidadeVendida()
                 << " | Preco Unit.: R$ " << item.getProduto().getPrecoVenda()
                 << " | Total Item: R$ " << item.getPrecoTotalItem() << endl;
        }
    }
    cout << "-----------------------------------------------------\n";
    cout << "Valor Total dos Produtos: R$ " << venda.getValorTotalVenda() << endl;
    cout << "Custo do Frete:           R$ " << valorFrete << endl;
    cout << "-----------------------------------------------------\n";
    cout << "VALOR TOTAL DA NOTA:      R$ " << valorTotalComFrete << endl;
    cout << "-----------------------------------------------------\n" << endl;
}

// Menu para emissão de nota fiscal
void menu_notaFiscal() {
    system("cls");
    cout << "\n--- EMISSAO DE NOTA FISCAL ---\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Coleta dados do comprador e endereço
    string nome, cpf, email, rua, bairro, cidade, estado, cep;
    cout << "\n--- DADOS DO COMPRADOR ---\n";
    cout << "Nome do comprador: ";
    getline(cin, nome);
    cout << "CPF: ";
    getline(cin, cpf);
    cout << "Email: ";
    getline(cin, email);
    cout << "\n--- ENDERECO DE ENTREGA ---\n";
    cout << "Rua: ";
    getline(cin, rua);
    cout << "Bairro: ";
    getline(cin, bairro);
    cout << "Cidade: ";
    getline(cin, cidade);
    cout << "Estado: ";
    getline(cin, estado);
    cout << "CEP: ";
    getline(cin, cep);

    NF_Endereco endereco(rua, bairro, cidade, estado, cep);
    NF_Comprador comprador(nome, cpf, email, endereco);

    // Coleta dados da venda e produtos vendidos
    cout << "\n--- DADOS DA VENDA ---\n";
    int codVenda, qtdItens;
    cout << "Codigo da venda: ";
    cin >> codVenda;
    cout << "Quantidade de tipos de itens vendidos: ";
    cin >> qtdItens;

    NF_Venda venda(codVenda);
    for (int i = 0; i < qtdItens; i++) {
        cout << "\n--- Produto #" << i + 1 << " ---\n";
        string nomeProd, codProd;
        double precoUnit;
        int qtdVendida;

        cout << "Nome do produto: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, nomeProd);
        cout << "Codigo do produto: ";
        getline(cin, codProd);
        cout << "Preco unitario: ";
        cin >> precoUnit;
        cout << "Quantidade vendida: ";
        cin >> qtdVendida;

        NF_Produto prod(nomeProd, codProd, precoUnit);
        NF_ItemVenda item(prod, qtdVendida);
        venda.adicionarItem(item);
    }

    emitirNotaFiscal(comprador, venda);
    system("pause");
}

// --- FUNÇÕES DE GERENCIAMENTO DE VENDEDORES ---

// Busca um vendedor pelo ID
int buscar_vendedor(int id) {
    for(int i = 0; i < total_vendedores; i++) {
        if(vendedores[i].get_id_vendedor() == id)
            return i;
    }
    return -1;
}

// Valida valor de venda
bool conferir_valor(double valor_venda){ return (valor_venda > 0); }
// Valida salário
bool conferir_salario(double salario){ return (salario >= SALARIO_MINIMO); }

// Cadastra um novo vendedor
void cadastrar_vendedor_func() {
    string nome;
    double salario;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);
    do {
        cout << "Salario fixo: ";
        cin >> salario;
        if(!conferir_salario(salario))
            cout << "O salario deve ser, no minimo, um salario minimo (R$" << SALARIO_MINIMO << ")." << endl;
    } while(!conferir_salario(salario));

    vendedores[total_vendedores++] = Vendedor(nome, salario);
    cout << "Cadastro realizado com sucesso!" << endl;
}

// Lista todos os vendedores cadastrados
void listar_vendedores() {
    if (total_vendedores == 0) {
        cout << "Nenhum vendedor cadastrado.\n";
        return;
    }
    for(int i = 0; i < total_vendedores; i++) {
        vendedores[i].consultar_vendedor();
    }
}

// Consulta vendedor por ID
void consultar_por_id() {
    int id;
    cout << "Qual o ID do vendedor que deseja consultar?" << endl;
    cin >> id;
    int idx = buscar_vendedor(id);
    if(idx != -1) {
        vendedores[idx].consultar_vendedor();
    } else {
        cout << "Vendedor nao encontrado!" << endl;
    }
}

// Registra uma venda para um vendedor
void registrar_venda_func() {
    int id;
    double valor_venda;
    cout << "Digite o ID de quem realizou a venda: ";
    cin >> id;
    int idx = buscar_vendedor(id);
    if(idx != -1) {
        do {
            cout << "Valor da venda: R$";
            cin >> valor_venda;
        } while(!conferir_valor(valor_venda));
        vendedores[idx].registrar_venda(valor_venda);
        cout << "Venda registrada com sucesso!" << endl;
    } else {
        cout << "Vendedor nao encontrado!" << endl;
    }
}

// Edita informações de um vendedor
void editar_informacoes() {
    int id;
    double novo_salario;
    string novo_nome;
    cout << "ID do vendedor: ";
    cin >> id;
    int idx = buscar_vendedor(id);
    if(idx != -1) {
        cout << "Novo nome: ";
        cin.ignore();
        getline(cin, novo_nome);
        do {
            cout << "Novo salario: ";
            cin >> novo_salario;
            if(!conferir_salario(novo_salario))
                cout << "O salario deve ser, no minimo, um salario minimo (R$" << SALARIO_MINIMO << ")." << endl;
        } while(!conferir_salario(novo_salario));

        vendedores[idx].set_nome_vendedor(novo_nome);
        vendedores[idx].set_salario_fixo(novo_salario);
        cout << "Informacoes atualizadas com sucesso!" << endl;
    } else {
        cout << "Vendedor nao encontrado!" << endl;
    }
}

// Exclui um vendedor pelo ID
void excluir_vendedor() {
    int id;
    cout << "Digite o ID de quem deseja excluir: ";
    cin >> id;
    int idx = buscar_vendedor(id);
    if(idx != -1) {
        for(int i = idx; i < total_vendedores - 1; i++) {
            vendedores[i] = vendedores[i+1];
        }
        total_vendedores--;
        cout << "Vendedor excluido com sucesso!" << endl;
    } else {
        cout << "Vendedor nao encontrado!" << endl;
    }
}

// Menu de gerenciamento de vendedores
void menu_vendedores() {
    int opcao;
    do {
        system("cls");
        cout << "--- MENU - VENDEDORES ---\n";
        cout << "1. Cadastrar vendedor" << endl;
        cout << "2. Listar todos os vendedores" << endl;
        cout << "3. Exibir vendedor por ID" << endl;
        cout << "4. Registrar venda" << endl;
        cout << "5. Editar informacoes" << endl;
        cout << "6. Excluir vendedor" << endl;
        cout << "0. Voltar ao menu principal" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 1: cadastrar_vendedor_func(); Sleep(2000); break;
            case 2: listar_vendedores(); system("pause"); break;
            case 3: consultar_por_id(); system("pause"); break;
            case 4: registrar_venda_func(); Sleep(2000); break;
            case 5: editar_informacoes(); Sleep(2000); break;
            case 6: excluir_vendedor(); Sleep(2000); break;
            case 0: cout << "Retornando ao menu principal..." << endl; Sleep(1000); break;
            default: cout << "Opcao invalida!" << endl; Sleep(1000); break;
        }
    } while(opcao != 0);
}

// Busca um produto pelo código
Produto* buscarProduto(int codigo) {
    for (auto &p : listagem_produtos) {
        if (p.codigo == codigo) {
            return &p;
        }
    }
    return nullptr;
}

// Cadastra uma nova venda
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
        cout << "\nProduto #" << i + 1 << " - Codigo: ";
        cin >> pv.codigoProduto;

        Produto *prod = buscarProduto(pv.codigoProduto);
        if (!prod) {
            cout << "Produto nao encontrado!\n";
            i--; continue;
        }

        cout << "Quantidade vendida: ";
        cin >> pv.quantidadeVendida;

        if (pv.quantidadeVendida > prod->estoque) {
            cout << "Estoque insuficiente! Estoque atual: " << prod->estoque << endl;
            i--; continue;
        }

        pv.nome = prod->nome_produto;
        pv.precoUnitario = prod->preco_venda;
        pv.precoTotal = pv.quantidadeVendida * pv.precoUnitario;

        prod->estoque -= pv.quantidadeVendida;

        v.produtos.push_back(pv);
        v.valorTotal += pv.precoTotal;
    }

    vendas.push_back(v);
    cout << "\nVenda cadastrada com sucesso! Valor total: R$ " << v.valorTotal << endl;
}

// Exibe todas as vendas cadastradas
void consultarVendas() {
    if (vendas.empty()){
        cout << "Nenhuma venda cadastrada.\n";
        return;
    }
    for (auto &v : vendas) {
        cout << "\nVenda #" << v.codigoVenda << " - Total: R$ " << v.valorTotal << endl;
        for (auto &p : v.produtos)
            cout << "  Produto: " << p.nome << ", Qtde: " << p.quantidadeVendida << ", Total: R$ " << p.precoTotal << endl;
    }
}

// Permite alterar o valor total de uma venda (exemplo simples)
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

// Exclui uma venda pelo código
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

// Menu de gerenciamento de vendas
void menu_vendas() {
    int opcao;
    do {
        system("cls");
        cout << "\n--- MENU DE VENDAS ---\n";
        cout << "1 - Cadastrar venda\n";
        cout << "2 - Consultar vendas\n";
        cout << "3 - Alterar venda\n";
        cout << "4 - Excluir venda\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "Opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            cout << "\nERRO: Por favor, digite apenas numeros.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1: cadastrarVenda(); Sleep(2000); break;
            case 2: consultarVendas(); system("pause"); break;
            case 3: alterarVenda(); Sleep(2000); break;
            case 4: excluirVenda(); Sleep(2000); break;
            case 0: cout << "Retornando ao menu principal...\n"; Sleep(1000); break;
            default: cout << "Opcao invalida!\n"; Sleep(1000); break;
        }
    } while (opcao != 0);
}

// Verifica se já existe um produto com o código informado
bool codigo_igual(int codigo) {
    for (size_t i = 0; i < listagem_produtos.size(); i++) {
        if (listagem_produtos[i].codigo == codigo) {
            return true;
        }
    }
    return false;
}

// Cadastra um novo produto
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
        if (!nome.empty()) break;
        cout << "ERRO: O nome do produto nao pode ser em branco. Por favor, tente novamente.\n";
    }

    while (true) {
        cout << "Digite o estoque do produto: ";
        cin >> quantidade;
        if (!cin.fail() && quantidade >= 0) break;
        cout << "ERRO: Entrada invalida ou estoque negativo. Digite um numero inteiro positivo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Digite o preco do produto (R$): ";
        cin >> preco;
        if (!cin.fail() && preco >= 0.0) break;
        cout << "ERRO: Entrada invalida ou preco negativo. Digite um numero positivo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    listagem_produtos.emplace_back(nome, codigo_final, quantidade, preco);
    cout << "\nCadastro do produto '" << nome << "' (Codigo: " << codigo_final << ") realizado!\n\n";
}

// Permite alterar dados de um produto já cadastrado
void alterar_produtos() {
    cout << "--- Alteracao de Produtos Cadastrados ---\n\n";
    if (listagem_produtos.empty()) {
        cout << "Nenhum produto cadastrado encontrado!\n\n";
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
                    cout << "Digite o novo nome: ";
                    getline(cin, novo_nome);
                    listagem_produtos[indice_produto].nome_produto = novo_nome;
                    cout << "Nome alterado!\n";
                    break;
                }
                case 2: {
                    int novo_estoque;
                    cout << "Digite o novo estoque: ";
                    cin >> novo_estoque;
                    listagem_produtos[indice_produto].estoque = novo_estoque;
                    cout << "Estoque alterado!\n";
                    break;
                }
                case 3: {
                    double novo_preco;
                    cout << "Digite o novo preco de venda: R$ ";
                    cin >> novo_preco;
                    listagem_produtos[indice_produto].preco_venda = novo_preco;
                    cout << "Preco alterado!\n";
                    break;
                }
                case 0: cout << "Alteracoes concluidas. Retornando...\n\n"; break;
                default: cout << "Opcao invalida!\n"; break;
            }
        } while (opcao_mudar != 0);
    }
}

// Exibe todos os produtos cadastrados
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
        cout << "Preco de Venda: R$ " << fixed << setprecision(2) << listagem_produtos[i].preco_venda << "\n";
    }
    cout << "-------------------------------------\n\n";
}

// Exclui um produto pelo código
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

    auto it = std::remove_if(listagem_produtos.begin(), listagem_produtos.end(), [&](const Produto& p) {
        return p.codigo == codigo_excluir;
    });

    if (it != listagem_produtos.end()) {
        listagem_produtos.erase(it, listagem_produtos.end());
        cout << "\nProduto(s) com codigo " << codigo_excluir << " excluido(s) com sucesso!\n\n";
    } else {
        cout << "\nProduto com codigo " << codigo_excluir << " nao encontrado!\n\n";
    }
}

// Menu de gerenciamento de produtos
void menu_produtos() {
    int opcao;
    do {
        system("cls");
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
            case 1: cadastro_produtos(); Sleep(2000); break;
            case 2: alterar_produtos(); Sleep(2000); break;
            case 3: consultar_produtos(); system("pause"); break;
            case 4: excluir_produtos(); Sleep(2000); break;
            case 5: cout << "Retornando ao menu principal...\n\n"; Sleep(1000); return;
            default: cout << "Opcao invalida! Tente novamente.\n\n"; Sleep(1000); break;
        }
    } while (opcao != 5);
}

// --- FUNÇÃO PRINCIPAL ---
// Exibe o menu principal do sistema e direciona para os módulos
int main() {
    int opcao;
    do {
        system("cls");
        cout << "====== MENU - COMERCIO ELETRONICO ======\n";
        cout << "1- Gerenciar Produtos\n";
        cout << "2- Gerenciar Vendedores\n";
        cout << "3- Gerenciar Compradores\n";
        cout << "4- Gerenciar Vendas\n";
        cout << "5- Emitir Nota Fiscal\n";
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

        switch (opcao) {
            case 1:
                menu_produtos();
                break;
            case 2:
                menu_vendedores();
                break;
            case 3:
                cadastro_global_compradores.menuCompradores();
                break;
            case 4:
                menu_vendas();
                break;
            case 5:
                menu_notaFiscal();
                break;
                cout << "Fim de execucao do programa.\n"; // Encerra o programa
                break;
            default:
                cout << "Opcao invalida! Tente novamente.\n\n"; // Opção inválida
        }
    } while (opcao != 0);

    return 0; // Fim do programa
}
