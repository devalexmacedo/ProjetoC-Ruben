#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <locale.h> // Para permitir caracteres especiais
#include <conio.h> // Adicionado para usar o comando _getch, que interrompe limpezas de tela for de hora esperando um input do user
#include <vector>
#include <algorithm> // adicionador para verificar a igualdade entre strings: transform e tolower
#include <limits> // Necessário para as funções de validações

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS, necessario para usar o localtime


using namespace std;


//Estrutura do produto.
struct Produto {
    int id;
    string nome;
    int quantidade;
    float precoCusto;
};

//fun��o que diz ao cout como mostrar item por item.
ostream& operator<<(ostream& os, const Produto& p) {
    os << "ID: " << p.id << " | "
        << "Nome: " << p.nome << " | "
        << "Quantidade: " << p.quantidade << " | "
        << "Preco: " << p.precoCusto << endl;
    return os;
}

//Insere produtos no estoque.
vector<Produto> estoque = {
    {1, "Placa", 20, 85.00},
    {2, "Processador Ryzen 5 5600X", 20, 140.00},
    {3, "Memoria RAM 16GB DDR4", 20, 35.00},
    {4, "Disco SSD 1TB NVMe", 20, 55.00},
    {5, "Fonte 650W 80+ Bronze", 20, 45.00},
    {6, "Placa Grafica RTX 3060", 20, 260.00},
    {7, "Caixa Mid Tower", 20, 40.00},
    {8, "Cooler CPU ARGB", 20, 25.00},
    {9, "Monitor 24'' Full HD", 20, 90.00},
    {10, "Teclado Mec�nico RGB", 20, 30.00},
    {11, "Rato Gaming 7200 DPI", 20, 15.00},
    {12, "Hub USB 3.0", 20, 10.00},
    {13, "Adaptador Wi-Fi USB", 20, 12.00},
    {14, "Pasta T�rmica", 20, 3.00},
    {15, "Cabo HDMI 2.0", 20, 4.00},
    {16, "Ventoinha 120mm", 20, 5.00},
    {17, "Kit Chave Torx PC", 20, 6.00},
    {18, "Extens�o de Energia", 20, 7.00},
    {19, "Suporte Monitor", 20, 8.00},
    {20, "Base Refrigerada Notebook", 20, 14.00}
};

//fun��o mostrar estoque
void mostrarEstoque() {
    for (int i = 0; i < estoque.size(); i++) {
        if (estoque[i].quantidade != 0)
            cout << fixed << setprecision(2) << estoque[i];
    }
}

//função para verificar se o produto escolhido tem no estoque.
void checarProdutoEstoque(int idProduto, Produto*& produtoSelecionado) {
    //percorre o estoque e se encontrar o produto no estoque, guarda o vetor no ponteiro.
    produtoSelecionado = nullptr; // Inicia o ponteiro a nullo, para não haver lixo
    for (int i = 0; i < estoque.size(); i++) {
        if (estoque[i].id == idProduto) {
            produtoSelecionado = &estoque[i];
            break;
        }
    }
}
// Função auxiliar para limpar o buffer de entrada e tratar erros
void limparBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//função para tratar entrada inválida.
void tratarErroEntrada() {
    cout << "Entrada inválida. Por favor, tente novamente.\n";
    cin.clear(); // Limpa os flags de erro
    limparBufferEntrada(); // Descarta a entrada inválida
}

// Função para obter um float válido do usuário
float obterFloat(const string& prompt) {
    float valor;
    while (true) {
        cout << prompt;
        if (cin >> valor) {
            limparBufferEntrada();
            return valor;
        } else {
            tratarErroEntrada();
        }
    }
}

// Fun��o para gerar venda aleatoria gratis          
int vendaGratis() {
    return (rand() % 4) == 0;
}

// Fun��o para adicionar 30% ao valor de custo
float calcValorVenda(float precoCusto) {
    return precoCusto * 1.3;
}

// Fun��o para calular o iva
float calcIVA(float precoTotal) {
    return precoTotal * 0.23;
}

void removerProduto() {
    mostrarEstoque();
    int idProduto;
    char continuar;

    cout << "Insira o ID do produto: ";
    cin >> idProduto;

    Produto* produtoSelecionado = nullptr; // Inicialmente não sabemos se o ID/Produto que o utilizador vai inserir existe, ent�o inicializamos um ponteiro nulo que é atualizado
    checarProdutoEstoque(idProduto, produtoSelecionado);

    // Verifica se o produto existe
    if (produtoSelecionado == nullptr) {
        cout << "Produto com ID " << idProduto << " não encontrado.\n";
    }
    else if (produtoSelecionado->quantidade == 0) { // Se o produto existe, mas não está mais em estoque
        cout << "Este produto ja nao esta em estoque.";
    }
    else { // O produto existe e está em estoque
        do { // Garante que o usuario escreveu o nome certo e quer prosseguir
            system("cls");
            cout << "Produto selecionado - ID: " << produtoSelecionado->id << " | Nome: " << produtoSelecionado->nome << " | Quantidade: " << produtoSelecionado->quantidade << " | Custo: " << produtoSelecionado->precoCusto << "\nDeseja remover do estoque? (Y/N): ";
            cin >> continuar;
        } while (continuar != 'y' && continuar != 'n' && continuar != 'Y' && continuar != 'N');

        if (continuar == 'n' || continuar == 'N') // Se o usuario não quiser prosseguir, retorne a função anterior
            return;

        produtoSelecionado->quantidade = 0;
        cout << "Produto removido.\n";
    }

    _getch();
}

// Função para converter uma string para minúsculas
string toMinuscula(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void adicionarProduto() {

    string nome;
    int valorAdd;
    bool existe = false; // Flag inspeciona se o artigo j� existe

    mostrarEstoque();

    cout << "Insira o nome do novo artigo: ";
    cin.ignore();
    getline(cin, nome); // L� a linha inteira, permitindo espa�os nos nomes 

    system("cls");

    for (int i = 0; i < estoque.size(); i++) {
        if (toMinuscula(estoque[i].nome) == toMinuscula(nome)) {  // Compara o nome do produto com cada item do estoque. Se encontrar um igual, deixa de adicionar e come�a a alterar o produto existente
            cout << "PRODUTO - " << estoque[i];
            cout << "Adicione ao stock: ";
            cin >> valorAdd;
            estoque[i].quantidade += valorAdd;
            cout << "Artigo atualizado.";
            existe = true;
            break;
        }
    }
    if (existe == false) {
        char continuar;

        do { // Garante que o usuario escreveu o nome certo e quer prosseguir
            cout << "Nome inserido: " << nome << ". Deseja continuar? (Y/N): ";
            cin >> continuar;
            system("cls");
        } while (continuar != 'y' && continuar != 'n' && continuar != 'Y' && continuar != 'N');

        if (continuar == 'n' || continuar == 'N') // Se o usuario não quiser prosseguir, retorne a função anterior
            return;

        Produto p; // Novo produto que iremos adicionar ao array no final

        p.nome = nome; // O nome do produto � o nome que inserimos acima
        p.id = estoque.size() + 1; // Id atribuido � um a mais do que o tamanho do estoque, que seria o ultimo id por default

        cout << "Nome: " << nome << endl;
        p.precoCusto = obterFloat("Insira o custo: ");
        cout << "Insira a quantidade: ";
        cin >> p.quantidade;

        // Adiciona ao vetor e aumenta o tamanho do estoque para que mais adi��es sejam possiveis
        estoque.push_back(p);

        cout << "Artigo adicionado.";
    }
    _getch();
}

void inicializarMatriz(float**& mat, int qtdProdutoVenda) {
    mat = new float* [qtdProdutoVenda];
    for (int i = 0; i < qtdProdutoVenda; ++i) {
        mat[i] = new float[6];
    }
}
//função para registrar a venda
bool registrarVenda(int i, float** mat, Produto*& produtoSelecionado) {
    int idProduto, qtdVenda;
    float precoSemIVA, ivaUnitario, precoUnit, precoTotal, IVA, totalComIVA;

    cout << "Digite o id do produto: ";
    cin >> idProduto;
    checarProdutoEstoque(idProduto, produtoSelecionado);
    if (!produtoSelecionado) {
        cout << "Produto nao encontrado.\n";
        return false;
    }

    cout << "Digite a quantidade de " << produtoSelecionado->nome << " que deseja: ";
    cin >> qtdVenda;

    if (qtdVenda > produtoSelecionado->quantidade) {
        cout << "Quantidade insuficiente (" << produtoSelecionado->quantidade << " em estoque).\n";
        cout << "Digite nova quantidade (ou 0 para cancelar): ";
        cin >> qtdVenda;
        if (qtdVenda == 0 || qtdVenda > produtoSelecionado->quantidade) {
            cout << "Item cancelado.\n";
            return false;
        }
    }

    precoSemIVA = calcValorVenda(produtoSelecionado->precoCusto);
    ivaUnitario = calcIVA(precoSemIVA);
    precoUnit = precoSemIVA + ivaUnitario;
    precoTotal = precoUnit * qtdVenda;
    IVA = ivaUnitario * qtdVenda;
    totalComIVA = precoTotal;

    mat[i][0] = idProduto; //armazena o id do produto escolhido
    mat[i][1] = qtdVenda; //armazena a quantidade escolhida
    mat[i][2] = precoSemIVA; // armazena o preço sem IVA
    mat[i][3] = IVA; //armazena o IVA total
    mat[i][4] = totalComIVA; //armazena o valor total com IVA
    mat[i][5] = precoUnit; //armazena o valor de venda do produto

    return true;
}
//função checkout
void checkout(float** mat, int qtdProdutoVenda, float& somaTotal, float& somaIVA) {
    Produto* produtoSelecionado = nullptr; //transforma a posição de memória separada em null, para não ter lixo
    somaTotal = somaIVA = 0;

    cout << "=========== Checkout ===========\n";
    for (int i = 0; i < qtdProdutoVenda; ++i) {
        int idProduto = mat[i][0];
        checarProdutoEstoque(idProduto, produtoSelecionado);
        if (produtoSelecionado) {
            cout << "Produto: " << produtoSelecionado->nome << "\n";
            cout << "Quantidade: " << static_cast<int>(mat[i][1]) << "\n";
            cout << "Preço Unitário: " << fixed << setprecision(2) << mat[i][5] << " euros\n";
            cout << "Preço s/IVA: " << fixed << setprecision(2) << mat[i][2] << " euros\n";
            cout << "IVA (23%): " << fixed << setprecision(2) << mat[i][3] / mat[i][1] << " euros\n";
            produtoSelecionado->quantidade -= static_cast<int>(mat[i][1]);

            somaTotal += mat[i][4];
            somaIVA += mat[i][3];
            cout << "---------------------------------\n";
        }
    }

    cout << "Subtotal s/IVA: " << fixed << setprecision(2) << somaTotal - somaIVA << " euros\n";
    cout << "Total IVA: " << fixed << setprecision(2) << somaIVA << " euros\n";
    cout << "Total c/IVA: " << fixed << setprecision(2) << somaTotal << " euros\n\n";
}
//função para imprimir o talão
void imprimirTalao(float** mat, int qtdProdutoVenda, int numFatura, int numCliente, float somaTotal, float somaIVA, float valorPago, float troco) {
    Produto* produtoSelecionado = nullptr; //transforma a posição de memória separada em null, para não ter lixo
    time_t t = time(nullptr);
    tm* dataAtual = localtime(&t);

    cout << "\n======= TALÃO DE COMPRAS =======\n";
    cout << "Fatura N: " << numFatura << "\n";
    cout << "Data: " << put_time(dataAtual, "%d/%m/%Y %H:%M") << "\n";
    cout << "Cliente N: " << numCliente << "\n\n";
    cout << "----- Detalhes dos Produtos -----\n";

    for (int i = 0; i < qtdProdutoVenda; ++i) {
        int idProduto = mat[i][0];
        checarProdutoEstoque(idProduto, produtoSelecionado);
        if (produtoSelecionado) {
            cout << "Produto: " << produtoSelecionado->nome << "\n";
            cout << "Quantidade: " << static_cast<int>(mat[i][1]) << "\n";
            cout << "Preço Unitário: " << fixed << setprecision(2) << mat[i][5] << " euros\n";
            cout << "Preço s/IVA: " << fixed << setprecision(2) << mat[i][2] << " euros\n";
            cout << "IVA (23%): " << fixed << setprecision(2) << mat[i][3] << " euros\n";
            cout << "---------------------------------\n";
        }
    }

    cout << "Subtotal s/IVA: " << fixed << setprecision(2) << somaTotal - somaIVA << " euros\n";
    cout << "Total IVA: " << fixed << setprecision(2) << somaIVA << " euros\n";
    cout << "Total c/IVA: " << fixed << setprecision(2) << somaTotal << " euros\n";
    cout << "Valor Pago: " << fixed << setprecision(2) << valorPago << " euros\n";
    cout << "Troco: " << fixed << setprecision(2) << troco << " euros\n";
    cout << "=====================================\n";
}


//Função para escolher os produtos e a quantidade.
void venda() {
    int qtdProdutoVenda, numCliente;
    float valorPago = 0, troco = 0, somaTotal = 0, somaIVA = 0;
    static int numFatura = 1;

    Produto* produtoSelecionado = nullptr;
    mostrarEstoque();
    while (true) {
        cout << "Inserir a quantidade de produtos a serem vendidos: ";
        cin >> qtdProdutoVenda;

        if (cin.good() && qtdProdutoVenda > 0) {
            break; // Sai do loop se a entrada for válida
        } else {
            cout << "Quantidade invalida. Por favor, insira uma quantidade que exista no estoque.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    float** mat;
    inicializarMatriz(mat, qtdProdutoVenda);

    int produtosProcessados = 0;
    for (int i = 0; i < qtdProdutoVenda; ++i) {
        if (registrarVenda(i, mat, produtoSelecionado))
            produtosProcessados++;
    }

    if (produtosProcessados == 0) {
        cout << "Nenhum produto válido foi processado. Venda cancelada.\n";
        return;
    }

    checkout(mat, qtdProdutoVenda, somaTotal, somaIVA);

    bool vendaSorteada = vendaGratis();
    if (vendaSorteada) {
        somaTotal = 0;
        somaIVA = 0;
        cout << "Venda sorteada! Cliente não pagará.\n";
    }
    else {
        cout << "Total a pagar: " << fixed << setprecision(2) << somaTotal << " euros\n";
        while (true) {
            valorPago = obterFloat("Insira o valor pago pelo cliente: ");
    
            if (cin.good() && valorPago > somaTotal) {
                break; // Sai do loop se a entrada for válida
            } else {
                cout << "Valor pago não pode ser menor que o total a pagar.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    troco = valorPago - somaTotal;

    cout << "Digite o codigo do cliente: ";
    cin >> numCliente;

    imprimirTalao(mat, qtdProdutoVenda, numFatura++, numCliente, somaTotal, somaIVA, valorPago, troco);

    _getch();
}

//função menu
void exibirMenu() {
    int opcao;
    //menu com as intera��es do programa
    do {
        system("cls"); // Limpa a tela toda a vez que uma op��o � selecionada

        cout << "------MENU PRINCIPAL------" << endl;
        cout << "1. Efetuar Venda" << endl;
        cout << "2. Criar Novo Artigo/Atualizar Artigo" << endl;
        cout << "3. Excluir Produto" << endl;
        cout << "4. Exibir Stock" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            // chamar fun��o de venda aqui
            venda();
            break;
        case 2:
            // chamar fun��o de cria��o
            adicionarProduto();
            break;
        case 3:
            // chamar fun��o de elimina��o
            removerProduto();
            break;
        case 4:
            // chamar fun��o mostrar estoque
            mostrarEstoque();
            cout << "Prima qualquer tecla...";
            _getch();
            break;
        case 5:
            cout << "Pressione qualquer tecla..." << endl;
            _getch();
            break;
        default:
            cout << "Opcao invalida! Tente novamente." << endl;
            _getch();
        }

        cout << endl;

    } while (opcao != 5);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    exibirMenu();
}