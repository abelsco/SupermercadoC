#ifndef LISTADINAMICA_H_INCLUDED
#define LISTADINAMICA_H_INCLUDED

#define TAM_LISTA 3

typedef struct No
{
    void *ptrDado;
    struct No *ptrAnt,
            *ptrProx;
} No;

typedef struct ListaDinamica
{
    int qtdeElementos,
        maxElementos;
    No *ptrInicio,
    *ptrFim;

    int ( *ptrFncComparar ) ( void *ptrElemento, void *ptrChaveBusca );
    int ( *ptrFncCopiar ) ( void *ptrDestino, void *ptrOrigem );
} ListaDinamica;

void InicializaLista ( ListaDinamica *ptrLista,
                       int ( *ptrFncComparar ) ( void *ptrElemento, void *ptrChaveBusca ),
                       int ( *ptrFncCopiar ) ( void *ptrDestino, void *ptrOrigem ) );
void DestroiLista ( ListaDinamica *ptrLista );
int InsereLista ( ListaDinamica *ptrLista, void *ptrNovoElemento );
int InsereListaPosicao ( ListaDinamica *ptrLista, void *ptrNovoElemento, int idxPosicao );
void* ExcluiLista ( ListaDinamica *ptrLista, void *ptrChaveBusca );
void* ExcluiListaPosicao ( ListaDinamica *ptrLista, int idxPosicao );
int AlteraLista ( ListaDinamica lista, void *ptrChaveBusca, void *ptrNovo ); //*ptrLista
int AlteraListaPosicao ( ListaDinamica lista, int idxPosicao, void *ptrNovo ); //*ptrLista
int ConsultaLista ( ListaDinamica lista, void *ptrChaveBusca, void *ptrSaida );
int ConsultaListaPosicao ( ListaDinamica lista, int idxPosicao, void *ptrSaida );

#endif // LISTADINAMICA_H_INCLUDED
