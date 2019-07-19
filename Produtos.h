#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

typedef struct
{
    char sDescricao[512];
    int codigo, quantidade;
    float preco;
} Produto;

void LeProduto ( Produto *ptrProduto );
void EscreveProduto ( Produto produto );

int ComparaProduto ( void *ptrElemento, void *ptrChaveBusca );
int CopiaProduto ( void *ptrDestino, void *ptrOrigem );

#endif // PRODUTO_H_INCLUDED
