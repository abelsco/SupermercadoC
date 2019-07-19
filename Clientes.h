#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED


typedef struct
{
    int chaveCliente;
    int elementos;
    int *produto;
    int *quantidadeCliente;
} Cliente;

void LeCliente ( Cliente *ptrCliente );
void EscreveCliente ( Cliente cliente );

int ComparaCliente ( void *ptrElemento, void *ptrChaveBusca );
int CopiaCliente ( void *ptrDestino, void *ptrOrigem );

#endif // CLIENTE_H_INCLUDED
