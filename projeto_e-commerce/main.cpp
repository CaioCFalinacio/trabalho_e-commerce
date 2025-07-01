#include <iostream>
#include <stdio.h>
#include <windows.h>
#define SALARIO_MINIMO 1518

using namespace std;

// Classe que representa um vendedor
class Vendedor
{
private:
    string nome_vendedor; // Nome do vendedor
    int id_vendedor; // ID único do vendedor
    double salario_fixo; // Salário fixo do vendedor
    double total_comissoes = 0; // Total de comissões acumuladas
    static int proximo_id; // Próximo ID disponível (auto-incremento)
public:
    static constexpr float taxa_comissao = 0.03; // Taxa de comissão fixa
    Vendedor() {}
    // Construtor que inicializa nome, salário e ID
    Vendedor(string nome_vendedor, double salario_fixo)
    {
        set_nome_vendedor(nome_vendedor);
        set_salario_fixo(salario_fixo);
        set_id_vendedor();
    }

    // Métodos de acesso (getters)
    string get_nome_vendedor()
    {
        return nome_vendedor;
    }
    int get_id_vendedor()
    {
        return id_vendedor;
    }
    double get_salario_fixo()
    {
        return salario_fixo;
    }
    double get_salario_total()
    {
        return (salario_fixo + total_comissoes);
    }

    // Métodos de modificação (setters) e ações
    void set_nome_vendedor(string novo_nome);
    void set_salario_fixo(double novo_salario);
    void set_id_vendedor();
    void consultar_vendedor();
    void registrar_venda(double valor_venda);
};

// Inicialização do membro estático
int Vendedor::proximo_id = 1;

// Define o nome do vendedor
void Vendedor::set_nome_vendedor(string novo_nome)
{
    nome_vendedor = novo_nome;
}
// Define o salário fixo do vendedor
void Vendedor::set_salario_fixo(double novo_salario)
{
    salario_fixo = novo_salario;
}
// Define o ID do vendedor e incrementa o próximo ID
void Vendedor::set_id_vendedor()
{
    id_vendedor = proximo_id++;
}
// Registra uma venda e adiciona a comissão ao total
void Vendedor::registrar_venda(double valor_venda)
{
    total_comissoes += valor_venda * taxa_comissao;
}
// Exibe as informações do vendedor
void Vendedor::consultar_vendedor()
{
    cout<<"Nome do vendedor: "<<nome_vendedor<<endl;
    cout<<"ID: "<<id_vendedor<<endl;
    cout<<"Salario fixo: R$"<<salario_fixo<<endl;
    cout<<"Comissoes acumuladas: R$"<<total_comissoes<<endl;
    cout<<"Salario total: R$"<<get_salario_total()<<endl;
}

// Busca o índice de um vendedor pelo ID
int buscar_vendedor(Vendedor vendedores[], int total_vendedores, int id)
{
    for(int i = 0; i < total_vendedores; i++)
    {
        if(vendedores[i].get_id_vendedor() == id)
            return i;
    }
    return -1;
}

bool conferir_valor(double valor_venda){
return (valor_venda > 0);
}

bool conferir_salario(double salario){
return (salario >= SALARIO_MINIMO);
}

void cadastrar_vendedor(Vendedor vendedores[], int &total_vendedores)
{
    string nome;
    double salario;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);
    do{
    cout << "Salario fixo: ";
    cin >> salario;
    if(salario < SALARIO_MINIMO)
        cout<<"O salario deve ser, no minimo, um salario minimo." << endl;
    }while(!conferir_salario(salario));
    vendedores[total_vendedores++] = Vendedor(nome, salario);
    cout << "Cadastro realizado com sucesso!" << endl;
}
void listar_vendedores(Vendedor vendedores[], int total_vendedores)
{
    for(int i = 0; i < total_vendedores; i++)
    {
        vendedores[i].consultar_vendedor();
    }
}
void consultar_por_id(Vendedor vendedores[], int total_vendedores)
{
    int id;
    cout << "Qual o ID do vendedor que deseja consultar?" << endl;
    cin >> id;
    int idx = buscar_vendedor(vendedores, total_vendedores, id);
    if(idx != -1)
    {
        vendedores[idx].consultar_vendedor();
    }
    else
    {
        cout << "Vendedor nao encontrado!" << endl;
    }
}
void registrar_venda(Vendedor vendedores[], int total_vendedores)
{
    int id;
    double valor_venda;
    cout << "Digite o ID de quem realizou a venda: ";
    cin >> id;
    int idx = buscar_vendedor(vendedores, total_vendedores, id);
    if(idx != -1)
    {
        do
        {
            cout << "Valor da venda: R$";
            cin >> valor_venda;
        }
        while(!conferir_valor(valor_venda));
        vendedores[idx].registrar_venda(valor_venda);
        cout << "Venda registrada com sucesso!" << endl;
    }
    else
    {
        cout << "Vendedor nao encontrado!" << endl;
    }
}
void editar_informacoes(Vendedor vendedores[], int total_vendedores)
{
    int id;
    double novo_salario;
    string novo_nome;
    cout << "ID do vendedor: ";
    cin >> id;
    int idx = buscar_vendedor(vendedores, total_vendedores, id); // Busca o vendedor pelo ID
    if(idx != -1)
    {
        cout << "Novo nome: ";
        cin.ignore();
        getline(cin, novo_nome); // Lê o novo nome do vendedor
        do{
        cout << "Novo salario: ";
        cin >> novo_salario;
        if(novo_salario < SALARIO_MINIMO)
            cout<<"O salario deve ser, no minimo, um salario minimo." << endl;
        }while(!conferir_salario(novo_salario)); // Garante que o novo salário seja válido
        vendedores[idx].set_nome_vendedor(novo_nome); // Atualiza o nome
        vendedores[idx].set_salario_fixo(novo_salario); // Atualiza o salário
        cout << "Informacoes atualizadas com sucesso!" << endl;
    }
    else
    {
        cout << "Vendedor nao encontrado!" << endl;
    }
}
// Função para excluir um vendedor do array
void excluir_vendedor(Vendedor vendedores[], int &total_vendedores){
    int id;
    cout << "Digite o ID de quem deseja excluir: ";
    cin >> id;
    int idx = buscar_vendedor(vendedores, total_vendedores, id); // Busca o vendedor pelo ID
    if(idx != -1)
    {
        // Move todos os vendedores após o excluído uma posição para trás
        for(int i = idx; i < total_vendedores-1; i++)
        {
            vendedores[i] = vendedores[i+1];
        }
        total_vendedores--; // Decrementa o total de vendedores
        cout<<"Vendedor excluido com sucesso!" << endl;
    }
    else
    {
        cout << "Vendedor nao encontrado!" << endl;
    }
}
// Menu principal para operações com vendedores
void menu_vendedores()
{
    Vendedor vendedores[100]; // Vetor de vendedores
    int opcao;
    int total_vendedores = 0;
    do
    {
        system("cls");
        cout << "O que voce deseja fazer?" << endl;
        cout << "1. Cadastrar vendedor" << endl;
        cout << "2. Listar todos os vendedores" << endl;
        cout << "3. Exibir vendedor por ID" << endl;
        cout << "4. Registrar venda" << endl;
        cout << "5. Editar informacoes" << endl;
        cout << "6. Excluir vendedor" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: " << endl;
        cin >> opcao;

        switch(opcao)
        {
        case 1: // Cadastro de novo vendedor
            cadastrar_vendedor(vendedores, total_vendedores);
            Sleep(2000);
            break;
        case 2: // Listar todos os vendedores
            listar_vendedores(vendedores, total_vendedores);
            if(total_vendedores == 0)
                cout << "Nenhum vendedor cadastrado." << endl;
            Sleep(5000);
            break;
        case 3: // Consultar vendedor por ID
            consultar_por_id(vendedores, total_vendedores);
            Sleep(2000);
            break;
        case 4: // Registrar venda para um vendedor
            registrar_venda(vendedores, total_vendedores);
            Sleep(2000);
            break;
        case 5: // Editar informações de um vendedor
            editar_informacoes(vendedores, total_vendedores);
            Sleep(2000);
            break;
        case 6: // Excluir vendedor do sistema
            excluir_vendedor(vendedores, total_vendedores);
            Sleep(2000);
            break;
        case 0: // Sair do programa
            cout << "Saindo de cadastrar vendedores." << endl;
            break;
        default:
            cout << "Opcao invalida!" << endl;
        }
    }
    while(opcao != 0);
}

int main()
{
    menu_vendedores();
    return 0;
}
