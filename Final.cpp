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

//funcaoo que diz ao cout como mostrar item da struct.
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
    {10, "Suporte Monitor", 20, 8.00},
};

//funcao mostrar estoque
void mostrarEstoque() {
    cout << "------------------------------ ESTOQUE ATUAL ------------------------------" << endl;
    cout << left << setw(5) << "ID" << "| "
        << left << setw(30) << "Nome do Produto" << "| "
        << left << setw(6) << "Qtd." << "| "
        << right << setw(18) << "Preco Custo (EUR)" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    bool estoqueVazioOuZerado = true;
    for (const auto& produto : estoque) {
        if (produto.quantidade > 0) {
            cout << left << setw(5) << produto.id << "| "
                << left << setw(30) << produto.nome << "| "
                << left << setw(6) << produto.quantidade << "| "
                << right << setw(15) << fixed << setprecision(2) << produto.precoCusto << " EUR" << endl;
            estoqueVazioOuZerado = false;
        }
    }
    if (estoqueVazioOuZerado) {
        cout << "O estoque está vazio ou todos os produtos têm quantidade 0." << endl;
    }
    cout << "---------------------------------------------------------------------------" << endl;
}

//função para verificar se o produto escolhido tem no estoque.
void checarProdutoEstoque(int idProduto, Produto*& produtoSelecionado) {
    //percorre o estoque e se encontrar o produto no estoque, guarda o vetor no ponteiro.
    int tamanho = estoque.size(); // Pra não dar erro no VS code
    produtoSelecionado = nullptr; // Inicia o ponteiro a nullo, para não haver lixo
    for (int i = 0; i < tamanho; i++) {
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
        if (cin >> valor && valor > 0) {
            limparBufferEntrada();
            return valor;
        }
        else {
            tratarErroEntrada();
        }
    }
}

int validacaoInt(const string& prompt) { // Usado em cin's para validar ints e retornar os valores se forem validos. Se não forem repete até serem.
    int n;

    while (true) {
        cout << prompt;
        if (cin >> n && n > 0) {
            limparBufferEntrada();
            return n;
        }
        else {
            tratarErroEntrada();
        }
    }

    return n;
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
    int idProduto;
    string input; // Necessario para receber a linha
    char continuar; // Necessario para receber a opção e não encher o buffer

    system("cls");
    mostrarEstoque();

    idProduto = validacaoInt("Insira o ID do produto: ");

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
            getline(cin, input);
            continuar = input[0];
        } while (continuar != 'y' && continuar != 'n' && continuar != 'Y' && continuar != 'N');

        if (continuar == 'n' || continuar == 'N') { // Se o usuario não quiser prosseguir, retorne a função anterior
            return;
        }

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

    system("cls");
    mostrarEstoque();

    cout << "Insira o nome do novo artigo: ";
    // cin.ignore();
    getline(cin, nome); // L� a linha inteira, permitindo espa�os nos nomes 

    system("cls");

    int tamanho = estoque.size(); // Pra não dar erro no VS code

    for (int i = 0; i < tamanho; i++) {
        if (toMinuscula(estoque[i].nome) == toMinuscula(nome)) {  // Compara o nome do produto com cada item do estoque. Se encontrar um igual, deixa de adicionar e come�a a alterar o produto existente
            string input; // Necessario para receber a linha
            char opt; // Necessario para receber a opção sem encher o buffer

            cout << "PRODUTO - " << estoque[i];
            valorAdd = validacaoInt("Adicione ao stock: "); // O user pode adicionar 0 ao estoque para não o forçar a adicionar caso tenha feito um erro
            estoque[i].quantidade += valorAdd;
            do { // Pergunta se o user quer atualizar o preço
                cout << "Deseja atualizar o preço?(Y/N) ";
                getline(cin, input);
                opt = input[0];
            } while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N');

            if (opt == 'y' || opt == 'Y') {
                estoque[i].precoCusto = obterFloat("Insira o novo preço: ");
            }

            cout << "Artigo atualizado.";
            existe = true;
            break;
        }
    }
    if (existe == false) {
        string input; // Necessario para receber a linha
        char continuar; // Necessario para receber a opção e não encher o buffer

        do { // Garante que o usuario escreveu o nome certo e quer prosseguir
            cout << "Nome inserido: " << nome << ". Deseja continuar? (Y/N): ";
            getline(cin, input);
            continuar = input[0];
            system("cls");
        } while (continuar != 'y' && continuar != 'n' && continuar != 'Y' && continuar != 'N');

        if (continuar == 'n' || continuar == 'N') // Se o usuario não quiser prosseguir, retorne a função anterior
            return;

        Produto p; // Novo produto que iremos adicionar ao array no final

        p.nome = nome; // O nome do produto � o nome que inserimos acima
        p.id = estoque.size() + 1; // Id atribuido � um a mais do que o tamanho do estoque, que seria o ultimo id por default

        cout << "Nome do Produto: " << nome << endl;
        p.precoCusto = obterFloat("Insira o custo: ");
        while (p.precoCusto <= 0) // Enquanto o user tentar dar valor 0 ou negativo, fica pedindo por novo valor
            p.precoCusto = obterFloat("Custo invalido. Insira um valor maior que 0: ");
        p.quantidade = validacaoInt("Insira a quantidade: ");
        while (p.quantidade <= 0) // Enquanto o user tentar dar valor 0 ou negativo, fica pedindo por novo valor
            p.quantidade = validacaoInt("Quantidade invalida. Insira um valor maior que 0: ");

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


    idProduto = validacaoInt("Digite o id do " + to_string(i + 1) + "º produto: ");
    checarProdutoEstoque(idProduto, produtoSelecionado);
    if (!produtoSelecionado) {
        cout << "Produto nao encontrado.\n";
        return false;
    }

    qtdVenda = validacaoInt("Digite a quantidade de " + produtoSelecionado->nome + " que deseja: ");

    if (qtdVenda > produtoSelecionado->quantidade) {
        cout << "Quantidade insuficiente (" << produtoSelecionado->quantidade << " em estoque).\n";
        qtdVenda = validacaoInt("Digite nova quantidade (ou 0 para cancelar): ");
        if (qtdVenda == 0) {
            cout << "Item cancelado.\n";
            return false;
        }
        else if (qtdVenda > produtoSelecionado->quantidade) {
            cout << "Quantidade insuficiente (" << produtoSelecionado->quantidade << " em estoque).\nItem cancelado";
            return false;
        }
    }
    else if (qtdVenda <= 0) {
        cout << "Quantidade invalida.\n";
        qtdVenda = validacaoInt("Digite nova quantidade (ou 0 para cancelar): ");
        if (qtdVenda == 0) {
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

// função checkout
bool checkout(float** mat, int qtdProdutoVenda, float& somaTotal, float& somaIVA) {
    Produto* produtoSelecionado = nullptr;
    somaTotal = somaIVA = 0;
    std::vector<std::pair<int, int>> carrinhoOriginal; // Para reverter o estoque em caso de desistência
    string input;
    char confirmacao;

    system("cls");

    cout << "=========== Checkout ===========\n";
    for (int i = 0; i < qtdProdutoVenda; ++i) {
        int idProduto = mat[i][0];
        int quantidadeVendida = static_cast<int>(mat[i][1]);
        checarProdutoEstoque(idProduto, produtoSelecionado);
        if (produtoSelecionado) {
            cout << "Produto: " << produtoSelecionado->nome << "\n";
            cout << "Quantidade: " << quantidadeVendida << "\n";
            cout << "Preço Unitário: " << fixed << setprecision(2) << mat[i][5] << " euros\n";
            cout << "Preço s/IVA: " << fixed << setprecision(2) << mat[i][2] << " euros\n";
            cout << "IVA (23%): " << fixed << setprecision(2) << mat[i][3] / quantidadeVendida << " euros\n";
            cout << "---------------------------------\n";

            carrinhoOriginal.push_back({ idProduto, quantidadeVendida });
            produtoSelecionado->quantidade -= quantidadeVendida; // Atualiza o estoque (temporariamente)

            somaTotal += mat[i][4];
            somaIVA += mat[i][3];
        }
    }

    cout << "Subtotal s/IVA: " << fixed << setprecision(2) << somaTotal - somaIVA << " euros\n";
    cout << "Total IVA: " << fixed << setprecision(2) << somaIVA << " euros\n";
    cout << "Total c/IVA: " << fixed << setprecision(2) << somaTotal << " euros\n\n";

    while (true) {
        do {
            cout << "Confirmar compra (Y - Sim) ou Desistir da venda (N - Não)? ";
            getline(cin, input);
            confirmacao = input[0];
        } while (confirmacao != 'y' && confirmacao != 'n' && confirmacao != 'Y' && confirmacao != 'N');

        if (confirmacao == 'y' || confirmacao == 'Y') {
            cout << "Compra confirmada.\n";
            return true; // Retorna true se a compra for confirmada
        }
        else {
            cout << "Venda cancelada no checkout. Revertendo estoque.\n";
            // Reverter as alterações no estoque
            for (const auto& item : carrinhoOriginal) {
                checarProdutoEstoque(item.first, produtoSelecionado);
                if (produtoSelecionado) {
                    produtoSelecionado->quantidade += item.second;
                }
            }
            somaTotal = 0; // Zera o total para indicar que a venda foi cancelada
            somaIVA = 0;
            return false; // Retorna false se a venda for cancelada
        }
    }
    // Esta linha nunca será alcançada devido ao loop while(true), mas é boa prática ter um retorno padrão (embora neste caso, os retornos dentro do loop cobrem todas as possibilidades).
    return false;
}

//função para imprimir o talão
void imprimirTalao(float** mat, int qtdProdutoVenda, int numFatura, int numCliente, float somaTotal, float somaIVA, float valorPago, float troco) {
    Produto* produtoSelecionado = nullptr; //transforma a posição de memória separada em null, para não ter lixo
    time_t t = time(nullptr);
    tm* dataAtual = localtime(&t);

    system("cls");

    cout << "======= TALÃO DE COMPRAS =======\n";
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
    float** mat = nullptr; // Inicializar mat para evitar problemas com delete[]

    system("cls");
    mostrarEstoque();

    while (true) {
        qtdProdutoVenda = validacaoInt("Inserir a quantidade de produtos a serem vendidos: ");

        if (qtdProdutoVenda > 0) {
            break; // Sai do loop se a entrada for válida
        }
        else {
            cout << "Quantidade invalida. Por favor, insira uma quantidade que exista no estoque.\nPrima ENTER.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            _getch(); // Usar _getch() para pausar
        }
    }

    inicializarMatriz(mat, qtdProdutoVenda);

    int produtosProcessados = 0;
    for (int i = 0; i < qtdProdutoVenda; ++i) {
        if (registrarVenda(i, mat, produtoSelecionado))
            produtosProcessados++;
    }

    if (produtosProcessados == 0) {
        cout << "Nenhum produto válido foi processado. Venda cancelada.\n";
        _getch();
        // Liberar a memória alocada para mat, mesmo que a venda seja cancelada
        for (int i = 0; i < qtdProdutoVenda; ++i) {
            delete[] mat[i];
        }
        delete[] mat;
        return;
    }

    // Chama a função checkout e verifica o resultado
    if (checkout(mat, qtdProdutoVenda, somaTotal, somaIVA)) {
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

                if (valorPago >= somaTotal) {
                    break; // Sai do loop se a entrada for válida
                }
                else {
                    do {
                        valorPago = obterFloat("Valor pago não pode ser menor que o total a pagar\nInsira o valor pago pelo cliente: ");
                    } while (valorPago < somaTotal);
                    break;
                }
            }
        }

        troco = valorPago - somaTotal;

        numCliente = validacaoInt("Digite o codigo do cliente: ");

        imprimirTalao(mat, qtdProdutoVenda, numFatura++, numCliente, somaTotal, somaIVA, valorPago, troco);
    }
    else {
        cout << "\nVenda cancelada durante o checkout.\n";
        // Não precisamos fazer mais nada aqui, pois o checkout já cuidou da reversão do estoque
        somaTotal = 0;
        somaIVA = 0;
    }

    // Liberar a memória alocada para mat
    if (mat != nullptr) {
        for (int i = 0; i < qtdProdutoVenda; ++i) {
            delete[] mat[i];
        }
        delete[] mat;
    }

    _getch();
}

//função menu
void exibirMenu() {
    int opcao;
    vector<pair<int, string>> menuOpcoes = {
        {1, "Efetuar Venda"},
        {2, "Criar Novo Artigo / Atualizar Artigo"},
        {3, "Excluir Produto"},
        {4, "Exibir Stock"},
        {5, "Sair"}
    };

    // Definir as larguras das colunas
    const int larguraID = 7;
    const int larguraOpcao = 40;

    // Calcular a largura total da linha
    const int larguraTotal = larguraID + 2 + larguraOpcao + 2; // ID + " | " + Opção + " |"

    string linhaSeparadora(larguraTotal, '-');

    do {
        system("cls");

        cout << "------------------ MENU PRINCIPAL -----------------" << endl;
        cout << left << setw(larguraID) << "Opção" << " | " << left << setw(larguraOpcao) << "Descrição" << endl;
        cout << linhaSeparadora << endl;

        for (const auto& item : menuOpcoes) {
            cout << left << setw(larguraID) << item.first << " | " << left << setw(larguraOpcao) << item.second << endl;
        }

        cout << linhaSeparadora << endl;
        opcao = validacaoInt("Escolha uma opcao: ");
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