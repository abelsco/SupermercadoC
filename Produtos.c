#include <stdio.h>
#include <string.h>

#include "Produtos.h"
#include "Utilitarios.h"

void LeProduto ( Produto *ptrProduto )
{
    printf ( "\n\nCodigo: " );
    scanf ( "%d", &ptrProduto->codigo );
    limpaBufferTeclado();
    printf ( "\nDescricao: " );
    scanf ( "%s", ptrProduto->sDescricao );
    limpaBufferTeclado();
    printf ( "\nQuantidade: " );
    scanf ( "%d", &ptrProduto->quantidade );
    limpaBufferTeclado();
    printf ( "\nPreco: " );
    scanf ( "%f", &ptrProduto->preco );
    limpaBufferTeclado();
}

void EscreveProduto ( Produto produto )
{
    printf ( "\n\nCodigo: %d", produto.codigo );
    printf ( "\nDescricao: %s", produto.sDescricao );
    printf ( "\nQuantidade: %d", produto.quantidade );
    printf ( "\nPreco: R$ %.2f", produto.preco );
}

int ComparaProduto ( void *ptrElemento, void *ptrChaveBusca )
{
    Produto *ptrProduto = ( Produto * ) ptrElemento;
    int *ptrCodigo = ( int * ) ptrChaveBusca;
    return ptrProduto->codigo - *ptrCodigo;
}

int CopiaProduto ( void *ptrDestino, void *ptrOrigem )
{
    Produto *ptrProdutoDestino = ( Produto * ) ptrDestino;
    Produto *ptrProdutoOrigem = ( Produto * ) ptrOrigem;
    *ptrProdutoDestino = *ptrProdutoOrigem;
    return 1;
}
