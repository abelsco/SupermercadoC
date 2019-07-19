#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "Clientes.h"
#include "Utilitarios.h"

void LeCliente ( Cliente *ptrCliente )
{
    int contador = 0;
    printf ( "\n\nChave cliente: " );
    scanf ( "%d", &ptrCliente->chaveCliente );
    limpaBufferTeclado();
    printf ( "\nQuantos produtos deseja cadastrar? " );
    scanf ( "%d", &ptrCliente->elementos );
    limpaBufferTeclado();
    ptrCliente->produto =  ( int * ) malloc ( ptrCliente->elementos * sizeof ( int ) );
    ptrCliente->quantidadeCliente = ( int * ) malloc ( ptrCliente->elementos * sizeof ( int ) );
    do
    {
        printf ( "\nCodigo: " );
        scanf ( "%d", &ptrCliente->produto[contador] );
        limpaBufferTeclado();
        printf ( "\nQuantidade desejada: " );
        scanf ( "%d", &ptrCliente->quantidadeCliente[contador] );
        limpaBufferTeclado();
        contador++;
    }
    while ( contador < ptrCliente->elementos );
    EscreveCliente ( *ptrCliente );
}

void EscreveCliente ( Cliente cliente )
{
    int elemento = 0;
    printf ( "\n\nChave cliente: %d", cliente.chaveCliente );
    printf ( "\nElementos: %d", cliente.elementos );
    for ( ; elemento < cliente.elementos; elemento++ )
    {
        printf ( "\nCodigo: %d", cliente.produto[elemento] );
        printf ( "\nQuantidade: %d", cliente.quantidadeCliente[elemento] );

    }
}

int ComparaCliente ( void *ptrElemento, void *ptrChaveBusca )
{
    Cliente *ptrCliente = ( Cliente * ) ptrElemento;
    int   *ptrChave    = ( int * )   ptrChaveBusca;
    return ptrCliente->chaveCliente - *ptrChave;
}

int CopiaCliente ( void *ptrDestino, void *ptrOrigem )
{
    Cliente *ptrClienteDestino = ( Cliente * ) ptrDestino;
    Cliente *ptrClienteOrigem  = ( Cliente * ) ptrOrigem;
    *ptrClienteDestino = *ptrClienteOrigem;
    return 1;
}
