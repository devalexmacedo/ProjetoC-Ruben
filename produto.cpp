#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <locale.h>


using namespace std;


//Estrutura do produto
struct Produto {
    int id;
    string nome;
    int quantidade;
    float precoCusto;
};
//função que diz ao cout como mostrar item por item
ostream& operator<<(ostream& os, const Produto& p) {
    os << "ID: " << p.id << " | "
       << "Nome: " << p.nome << " | "
       << "Quantidade: " << p.quantidade << " | "
       << "Preco: €" << p.precoCusto << endl;
    return os;
}

//Insere produtos no estoque
Produto estoque[] = {
    {1, "Placa Mae ASUS B550", 20, 85.00},
    {2, "Processador Ryzen 5 5600X", 20, 140.00},
    {3, "Memoria RAM 16GB DDR4", 20, 35.00},
    {4, "Disco SSD 1TB NVMe", 20, 55.00},
    {5, "Fonte 650W 80+ Bronze", 20, 45.00},
    {6, "Placa Grafica RTX 3060", 20, 260.00},
    {7, "Caixa Mid Tower", 20, 40.00},
    {8, "Cooler CPU ARGB", 20, 25.00},
    {9, "Monitor 24'' Full HD", 20, 90.00},
    {10, "Teclado Mecânico RGB", 20, 30.00},
    {11, "Rato Gaming 7200 DPI", 20, 15.00},
    {12, "Hub USB 3.0", 20, 10.00},
    {13, "Adaptador Wi-Fi USB", 20, 12.00},
    {14, "Pasta Térmica", 20, 3.00},
    {15, "Cabo HDMI 2.0", 20, 4.00},
    {16, "Ventoinha 120mm", 20, 5.00},
    {17, "Kit Chave Torx PC", 20, 6.00},
    {18, "Extensão de Energia", 20, 7.00},
    {19, "Suporte Monitor", 20, 8.00},
    {20, "Base Refrigerada Notebook", 20, 14.00}
};

//Calcula o tamanho do estoque para o usar o ciclo de repetição 
const int tamEstoque = sizeof (estoque) / sizeof (estoque[0]);

//função mostrar estoque
void mostrarEstoque() {
    for(int i = 0; i < tamEstoque; i++) {
        cout << estoque[i];
    }
}
//Função para escolher os produtos e a quantidade
void selecionarProduto() {
    int qtdProdutoVenda, idProduto, qtdVenda;
    float valorPago;

    cout << "Inserir a quantidade de produtos desejados: ";
    cin >> qtdProdutoVenda;
        for (int i = 0; i < qtdProdutoVenda; i++) {
            cout << "Digite o id do produto que deseja: ";
            cin >> idProduto;
            cout << "Digite a quantidade do produto que deseja: ";
            cin >> qtdVenda;
                for (int j = 0; j < tamEstoque; j++) {

                }


        }

}
//função menu
void exibirMenu() {
    int opcao;
    //menu com as interações do programa
    do {
        cout << "------MENU PRINCIPAL------" << endl;
        cout << "1. Efetuar Venda" << endl;
        cout << "2. Criar Novo Artigo" << endl;
        cout << "3. Excluir Produto" << endl;
        cout << "4. Exibir Stock" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                // chamar função de venda aqui
                mostrarEstoque();
                break;
            case 2:
                // chamar função de criação
                break;
            case 3:
                // chamar função de eliminação
                break;
            case 4:
                // mostrar stock
                mostrarEstoque();
                break;
            case 5:
                cout << "Saindo do programa..." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }

        cout << endl;

    } while (opcao != 5);
}

int main () {
    setlocale (LC_ALL, "Portuguese");

    exibirMenu();
}
