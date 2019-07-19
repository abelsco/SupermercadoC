#include <stdio.h>
#include <stdlib.h>
#include "Clientes.h"
#include "Produtos.h"
#include "Utilitarios.h"
#include "ListaDinamica.h"
/**
****************************************************LEIA O LEIA-ME*************************************************************
Faça um programa para controle de estoque de um supermercado. Este deverá:

1 - ler os dados dos produtos (código, descrição, quantidade, preço), ou seja, o estoque inicial. - OK

Observação: os passos de 2 à 5 deverão ser repetidos enquanto o usuário não abandonar o sistema (por exemplo a tecla “S – Sair”); ao atender um novo cliente,
    todas as listas criadas/definidas nos passos 3 à 5 deverão ser destruídas/“zeradas”. - OK

2 - a qualquer momento durante a execução do sistema, alterações poderão ser realizadas no estoque para adicionar novos produtos recebidos.
    Tais recebimentos de novos produtos poderão implicar na inclusão de um produto ainda não existente no estoque ou apenas na atualização da quantidade em estoque de um produto
    preexistente; - OK

3 - ler a lista de compras de um cliente (dados do produto e quantidade) - OK

4 - depois de obter a lista de compras, o cliente ainda poderá alterá-la antes de efetuar as compras. Caso não queira alterar,
    o cliente deverá confirmar os itens comprados e, a partir disto, o sistema deverá criar, mediante o atendimento (ou não) da quantidade pedida para cada item,
    listas com as relações:
    a) de itens atendidos (quantidade em estoque maior ou igual à quantidade pedida) - OK
    b) de itens não atendidos (quantidade que falta no estoque para atender a quantidade pedida) - OK
    c) calcular e exibir o total da compra realizada pelo cliente - OK
5 - permitir que, após o fechamento da compra (passo 4.c), possam ser realizadas consultas às listas anteriormente criadas (passos 4.a e 4.b), de modo que seja exibido:
    a) os dados do(s) produto(s) que teve(tiveram) a quantidade pedida atendida; - OK
    b) os dados e a quantidade do(s) produto(s) que não havia estoque suficiente. - OK
**/
void RelatorioListaNaoAtendidos ( ListaDinamica *ptrlistaNaoAtendidos, Produto *ptrConsumo )
{
    int contador;
    if ( ptrlistaNaoAtendidos->qtdeElementos == 0 )
    {
        printf ( "\nAtenda a um cliente antes! " );
        return;
    }
    for ( contador = 0; contador < ptrlistaNaoAtendidos->qtdeElementos; contador++ )
    {
        EscreveProduto ( *ptrConsumo );
    }
}
void RelatorioListaAtendidos ( ListaDinamica *ptrlistaAtendidos, Produto *ptrConsumo )
{
    int contador;
    if ( ptrlistaAtendidos->qtdeElementos == 0 )
    {
        printf ( "\nAtenda a um cliente antes! " );
        return;
    }
    for ( contador = 0; contador < ptrlistaAtendidos->qtdeElementos; contador++ )
    {
        EscreveProduto ( *ptrConsumo );
    }
}
void AtendimentoProduto ( ListaDinamica *ptrlistaProduto )
{
    Produto *ptrProduto, produto;
    int retorno = 0, codigo = 0, contador;
    char opcao = '\0';
    do
    {
        printf ( "\n\n=====PRODUTO======\nEscolha a opcao:" );
        printf ( "\nI - Inserir" );
        printf ( "\nC - Consultar" );
        printf ( "\nA - Alterar" );
        printf ( "\nE - Excluir" );
        printf ( "\nR - Relatorio" );
        printf ( "\nS - Sair\n" );
        scanf ( "%c" , &opcao );
        limpaBufferTeclado();
        opcao = toupper ( opcao );
        switch ( opcao )
        {
            case 'I':
                {
                    // cria elemento
                    ptrProduto = ( Produto * ) malloc ( sizeof ( Produto ) );
                    if ( ptrProduto )
                    {
                        LeProduto ( ptrProduto );
                        codigo = ptrProduto->codigo;
                        ConsultaLista ( *ptrlistaProduto, &codigo, &produto );
                        // insere na lista
                        retorno = produto.codigo;

                        if ( retorno != codigo )
                        {
                            retorno = InsereLista ( ptrlistaProduto, ptrProduto );
                            if ( retorno )  // verifica o que aconteceu na rotina de insercao
                                printf ( "\nInsercao OK." );
                            else
                            {
                                free ( ptrProduto );
                                ptrProduto = NULL;
                                printf ( "\nInseraco falhou." );
                            }
                        }
                        else
                        {
                            printf ( "\nProduto ja cadastrado. Somente a quantidade alterada!" );
                            produto.quantidade += ptrProduto->quantidade;
                            AlteraLista ( *ptrlistaProduto, &codigo, &produto );
                        }
                    }
                    else
                        printf ( "\nFalta de memoria." );
                }
                break;
            case 'C':
                {
                    printf ( "\nDigite o codigo: " );
                    scanf ( "%d", &codigo );
                    limpaBufferTeclado();
                    retorno = ConsultaLista ( *ptrlistaProduto, &codigo, &produto );
                    if ( retorno )
                        EscreveProduto ( produto );
                    else
                        printf ( "\nProduto nao encontrado." );
                }
                break;
            case 'A':
                {
                    printf ( "\nEntre com o codigo: " );
                    scanf ( "%d", &codigo );
                    limpaBufferTeclado();
                    printf ( "Deseja alterar somente a quantidade?\nS - SIM\nN - NAO\n" );
                    scanf ( "%c", &opcao );
                    limpaBufferTeclado();
                    opcao = toupper ( opcao );
                    if ( opcao == 'S' )
                    {
                        retorno = ConsultaLista ( *ptrlistaProduto, &codigo, &produto );
                        if ( retorno )
                        {
                            printf ( "\nNova quantidade: " );
                            scanf ( "%d", &produto.quantidade );
                            limpaBufferTeclado();
                            AlteraLista ( *ptrlistaProduto, &codigo, &produto );
                            printf ( "\nProduto alterado." );
                        }
                        else
                            printf ( "\nProduto nao encontrado." );
                    }
                    else
                    {
                        LeProduto ( &produto );
                        retorno = AlteraLista ( *ptrlistaProduto, &codigo, &produto );
                        if ( retorno )
                            printf ( "\nProduto alterado." );
                        else
                            printf ( "\nProduto nao encontrado." );
                    }
                }
                break;
            case 'E':
                {
                    printf ( "\nEntre com o codigo: " );
                    scanf ( "%d", &codigo );
                    limpaBufferTeclado();
                    ptrProduto = ExcluiLista ( ptrlistaProduto, &codigo );
                    if ( ptrProduto )
                    {
                        EscreveProduto ( *ptrProduto );
                        free ( ptrProduto );
                        ptrProduto = NULL;
                    }
                    else
                        printf ( "\nProduto nao encontrado." );
                }
                break;
            case 'R':
                {
                    if ( ptrlistaProduto->qtdeElementos == 0 )
                        printf ( "\nNenhum produto cadastrado." );
                    else
                    {
                        for ( contador = 0; contador < ptrlistaProduto->qtdeElementos; contador++ )
                        {
                            ConsultaListaPosicao ( *ptrlistaProduto, contador, &produto );
                            EscreveProduto ( produto );
                        }
                    }
                }
                break;
        }
    }
    while ( opcao != 'S' );
}
void AtendimentoCliente ( ListaDinamica *ptrlistaCliente, ListaDinamica *ptrlistaAtendida, ListaDinamica *ptrlistaNaoAtendida  )
{
    if ( ptrlistaAtendida->qtdeElementos == 1 && ptrlistaNaoAtendida->qtdeElementos == 1 )
    {
        DestroiLista ( ptrlistaAtendida );
        DestroiLista ( ptrlistaNaoAtendida );
        InicializaLista ( ptrlistaAtendida, ComparaProduto, CopiaProduto );
        InicializaLista ( ptrlistaNaoAtendida, ComparaProduto, CopiaProduto );
    }
    Cliente *ptrCliente, cliente;
    int retorno = 0, chave = 0, contador;
    char opcao = '\0';
    do
    {
        printf ( "\n\n=====CLIENTE======\nEscolha a opcao:" );
        printf ( "\nI - Inserir" );
        printf ( "\nC - Consultar" );
        printf ( "\nA - Alterar" );
        printf ( "\nE - Excluir" );
        printf ( "\nR - Relatorio" );
        printf ( "\nS - Sair\n" );
        scanf ( "%c", &opcao );
        limpaBufferTeclado();
        opcao = toupper ( opcao );
        switch ( opcao )
        {
            case 'I':
                {
                    // cria elemento
                    ptrCliente = ( Cliente * ) malloc ( sizeof ( Cliente ) );
                    if ( ptrCliente )
                    {
                        LeCliente ( ptrCliente );
                        chave = ptrCliente->chaveCliente;
                        // insere na lista
                        ConsultaLista ( *ptrlistaCliente, &chave, &cliente );
                        retorno = cliente.chaveCliente;
                        if ( chave != retorno )
                        {
                            retorno = InsereLista ( ptrlistaCliente, ptrCliente );
                            if ( retorno )  // verifica o que aconteceu na rotina de insercao
                                printf ( "\nInsercao OK." );
                            else
                            {
                                free ( ptrCliente );
                                ptrCliente = NULL;
                                printf ( "\nInsercao falhou." );
                            }
                        }
                        else
                        {
                            printf ( "\nCliente ja cadastrado" );
                        }
                    }
                    else
                        printf ( "\nFalta de memoria." );
                }
                break;
            case 'C':
                {
                    printf ( "\nDigite o codigo: " );
                    scanf ( "%d", &chave );
                    limpaBufferTeclado();
                    retorno = ConsultaLista ( *ptrlistaCliente, &chave, &cliente );
                    if ( retorno )
                        EscreveCliente ( cliente );
                    else
                        printf ( "\nCliente nao encontrado." );
                }
                break;
            case 'A':
                {
                    printf ( "\nEntre com a chave de busca: " );
                    scanf ( "%d", &chave );
                    limpaBufferTeclado();
                    LeCliente ( &cliente );
                    retorno = AlteraLista ( *ptrlistaCliente, &chave, &cliente );
                    if ( retorno )
                        printf ( "\nCliente alterado." );
                    else
                        printf ( "\nCliente nao encontrado." );
                }
                break;
            case 'E':
                {
                    printf ( "\nEntre com a chave de busca: " );
                    scanf ( "%d", &chave );
                    limpaBufferTeclado();
                    ptrCliente = ExcluiLista ( ptrlistaCliente, &chave );
                    if ( ptrCliente )
                    {
                        EscreveCliente ( *ptrCliente );
                        free ( ptrCliente );
                        ptrCliente = NULL;
                    }
                    else
                        printf ( "\nCliente nao encontrado." );
                }
                break;
            case 'R':
                {
                    if ( ptrlistaCliente->qtdeElementos == 0 )
                        printf ( "\nNenhum cliente cadastrado." );
                    else
                    {
                        for ( contador = 0; contador < ptrlistaCliente->qtdeElementos; contador++ )
                        {
                            ConsultaListaPosicao ( *ptrlistaCliente, contador, &cliente );
                            EscreveCliente ( cliente );
                        }
                    }

                }
                break;
        }
    }
    while ( opcao != 'S' );
}
void GerenciaVendas ( ListaDinamica *ptrlistaCliente, ListaDinamica *ptrlistaProduto, ListaDinamica *ptrlistaAtendidos, ListaDinamica *ptrlistaNaoAtendidos, Produto *ptrConsumo, Produto *ptrnConsumo )
{
    float total = 0;
    Produto produto;
    Cliente cliente, *ptrCliente, *ptrAux;
    ptrCliente = ( Cliente* ) malloc ( sizeof ( Cliente ) );
    ptrAux = ( Cliente* ) malloc ( sizeof ( Cliente ) );
    int retorno = 0, contador = 0, chave = 0;
    char opcao = 'n';
    // pegar consumidor
    if ( ptrlistaCliente->qtdeElementos == 0 )
    {
        printf ( "Cadastre um cliente antes!" );
        return;
    }
    printf ( "\n==============ATENDIMENTO=================\n" );
    printf ( "\nDigite o codigo do cliente desejado: " );
    scanf ( "%d", &chave );
    limpaBufferTeclado();
    retorno = ConsultaLista ( *ptrlistaCliente, &chave, &cliente );
    if ( retorno == 0 )
    {
        printf ( "\nCliente nao encontrado!" );
        return;
    }
    printf ( "\nLista de compras:\n" );
    EscreveCliente ( cliente );
    printf ( "\n\nDeseja alterar sua lista de compras?\nS - SIM\nN - NAO\n" );
    scanf ( "%c", &opcao );
    limpaBufferTeclado();
    opcao = toupper ( opcao );
    if ( opcao == 'S' )
    {
        AtendimentoCliente ( ptrlistaCliente, ptrlistaAtendidos, ptrlistaNaoAtendidos );
        return;
    }
    printf ( "\nDeseja confirmar?\nS - SIM\nN - NAO\n" );
    scanf ( "%c", &opcao );
    limpaBufferTeclado();
    opcao = toupper ( opcao );
    if ( opcao != 'S' )
        return;
    for ( contador = 0; contador < cliente.elementos; contador++ )
    {
        retorno = ConsultaLista ( *ptrlistaProduto, &cliente.produto[contador], ptrConsumo );
        ConsultaLista ( *ptrlistaProduto, &cliente.produto[contador], &produto );
        if ( retorno == 0 )
        {
            printf ( "\nProduto %d da lista de compras nao existe no estoque!",  cliente.produto[contador] );
            cliente.produto[contador] = 0;
            cliente.quantidadeCliente[contador] = 0;
        }
        else if ( cliente.quantidadeCliente[contador] > produto.quantidade ) //Não atendido
        {
            ptrConsumo->codigo = produto.codigo;
            strcpy ( ptrConsumo->sDescricao, produto.sDescricao );
            ptrConsumo->quantidade = produto.quantidade;
            ptrConsumo->preco = ptrConsumo->quantidade * produto.preco;
            InsereLista ( ptrlistaAtendidos, ptrConsumo );
            // atualiza qtde. faltante
            cliente.quantidadeCliente[contador] -= produto.quantidade;
            produto.quantidade = 0;
            AlteraLista ( *ptrlistaProduto, &cliente.produto[contador], &produto );
            ptrnConsumo->codigo = produto.codigo;
            strcpy ( ptrnConsumo->sDescricao, produto.sDescricao );
            ptrnConsumo->quantidade = cliente.quantidadeCliente[contador];
            ptrnConsumo->preco = 0;
            InsereLista ( ptrlistaNaoAtendidos, ptrnConsumo );
            printf ( "\nProduto %d, Valor total R$ %.2f.", produto.codigo, ptrConsumo->preco );
            total += ptrConsumo->preco;
        }
        else
        {
            // atualiza estoque
            produto.quantidade -= cliente.quantidadeCliente[contador];
            AlteraLista ( *ptrlistaProduto, &produto.codigo, &produto );
            ptrConsumo->preco = cliente.quantidadeCliente[contador] * produto.preco;
            printf ( "\nProduto %d, Valor total R$ %.2f.", produto.codigo, ptrConsumo->preco );
            total += ptrConsumo->preco;
            cliente.quantidadeCliente[contador] = 0;
            AlteraLista ( *ptrlistaCliente, &cliente.chaveCliente, &cliente );
            ptrConsumo->codigo = produto.codigo;
            strcpy ( ptrConsumo->sDescricao, produto.sDescricao );
            ptrConsumo->quantidade = cliente.quantidadeCliente[contador];

            InsereLista ( ptrlistaAtendidos, ptrConsumo );
        }
    }
    printf ( "\nValor total da compra R$ %.2f do cliente.", total );
    ConsultaLista ( *ptrlistaCliente, &chave, ptrCliente );
    ptrAux = ExcluiLista ( ptrlistaCliente, ptrCliente );
    EscreveCliente ( *ptrAux );
    free ( ptrAux );
    ptrAux = NULL;

}
int main()
{
    char opcao = '\0';
    ListaDinamica listaAtendidos, listaNaoAtendidos, listaCliente, listaProduto;
    Produto consumido, nConsumido;
    InicializaLista ( &listaAtendidos, ComparaProduto, CopiaProduto );
    InicializaLista ( &listaNaoAtendidos, ComparaProduto, CopiaProduto );
    InicializaLista ( &listaCliente, ComparaCliente, CopiaCliente );
    InicializaLista ( &listaProduto, ComparaProduto, CopiaProduto );
    do
    {
        printf ( "\n================-MENU-=================\n\nProduto - P\nCliente - C\nAtendimento - A\nRelatorio - R\nSair - S\n" );
        scanf ( "%c", &opcao );
        limpaBufferTeclado();
        opcao = toupper ( opcao );
        system ( LIMPAR_TELA );
        switch ( opcao )
        {
            case 'P':
                {
                    //AtendimentoProduto
                    AtendimentoProduto ( &listaProduto );

                }
                break;
            case 'C':
                {
                    //AtendimentoCliente
                    AtendimentoCliente ( &listaCliente, &listaAtendidos, &listaNaoAtendidos );

                }
                break;
            case 'A':
                {
                    //AtendimentoVendas
                    GerenciaVendas ( &listaCliente, &listaProduto, &listaAtendidos, &listaNaoAtendidos, &consumido, &nConsumido );

                }
                break;
            case 'R':
                {
                    printf ( "\n========RELATORIO========\nLista atendidos - 1\nLista Nao atendidos - 2\n" );
                    scanf ( "%c", &opcao );
                    limpaBufferTeclado();
                    if ( opcao == '1' )
                        RelatorioListaAtendidos ( &listaAtendidos, &consumido );
                    if ( opcao == '2' )
                        RelatorioListaNaoAtendidos ( &listaNaoAtendidos, &nConsumido );
                }
                break;

            case 'S':
                {
                    printf ( "\nSAINDO\n" );
                }
                break;
            default:
                {
                    printf ( "\nEscolha uma opcao valida\n" );
                }
                break;
        }
    }
    while ( opcao != 'S' );
    DestroiLista ( &listaAtendidos );
    DestroiLista ( &listaNaoAtendidos );
    DestroiLista ( &listaCliente );
    DestroiLista ( &listaProduto );
    return 0;
}
