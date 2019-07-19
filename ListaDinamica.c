#include <stdlib.h>

#include "ListaDinamica.h"

void InicializaLista ( ListaDinamica *ptrLista,
                       int ( *ptrFncComparar ) ( void *ptrElemento, void *ptrChaveBusca ),
                       int ( *ptrFncCopiar ) ( void *ptrDestino, void *ptrOrigem ) )
{
    ptrLista->maxElementos  = -1;
    ptrLista->qtdeElementos = 0;
    ptrLista->ptrInicio = NULL;
    ptrLista->ptrFim    = NULL;
    ptrLista->ptrFncComparar = ptrFncComparar;
    ptrLista->ptrFncCopiar   = ptrFncCopiar;
}
void* ExcluiListaInicio ( ListaDinamica *ptrLista )
{
    // salva as referencias para o No e para o Dado em si
    No   *ptrAux  = ptrLista->ptrInicio;
    void *ptrDado = ptrAux->ptrDado;
    // segundo elemento se torno o primeiro
    ptrLista->ptrInicio = ptrLista->ptrInicio->ptrProx;
    // coloca NULL no ptrAnt do "novo primeiro elemento"
    if ( ptrLista->qtdeElementos != 1 )
    {
        ptrLista->ptrInicio->ptrAnt = NULL;
        free ( ptrAux );
    }
    else
    {
        ptrLista->ptrFim = NULL;
    }
    ptrLista->qtdeElementos--;
    // libera memoria da estrutura No
    return ptrDado; // retorna referencia para o dado excluido
}
void DestroiLista ( ListaDinamica *ptrLista )
{
    void *ptrAux = NULL;
    while ( ptrLista->qtdeElementos )
    {
        if ( ptrLista->qtdeElementos != 1 )
        {
            ptrAux = ExcluiListaPosicao ( ptrLista, NULL );
            free ( ptrAux );
            ptrAux = NULL;
        }
        else
        {
            ptrAux = ExcluiListaInicio ( ptrLista );
        }
    }
    ptrLista->ptrFncComparar = NULL;
    ptrLista->ptrFncCopiar   = NULL;
}
int InsereLista ( ListaDinamica *ptrLista, void *ptrNovoElemento )
{
    No *ptrNoAux = NULL;
    if ( ptrLista->maxElementos != -1 && ptrLista->qtdeElementos == ptrLista->maxElementos )
        return -1;
    ptrNoAux = ( No* ) malloc ( sizeof ( No ) );
    if ( !ptrNoAux )
        return -2;
    ptrNoAux->ptrDado = ptrNovoElemento;
    ptrNoAux->ptrProx = NULL;
    if ( !ptrLista->qtdeElementos ) // verifica se lista esta vazia
    {
        ptrNoAux->ptrAnt  = NULL;   // nao ha elementos antes do primeiro
        ptrLista->ptrInicio = ptrNoAux; // seta ptrInicio para primeiro elemento inserido
    }
    else
    {
        ptrNoAux->ptrAnt          = ptrLista->ptrFim; // novo elemento aponta para o ultimo corrente
        ptrLista->ptrFim->ptrProx = ptrNoAux; // ultimo elemento corrente aponta para o novo elemento
    }
    ptrLista->ptrFim = ptrNoAux; // atualiza campo ultimo da lista para novo elemento
    ptrLista->qtdeElementos++;
    return 1;
}
int InsereListaInicio ( ListaDinamica *ptrLista, void *ptrNovoElemento )
{
    No *ptrNoAux = NULL;
    if ( ptrLista->maxElementos != -1 && ptrLista->qtdeElementos == ptrLista->maxElementos )
        return -1;
    ptrNoAux = ( No* ) malloc ( sizeof ( No ) );
    if ( !ptrNoAux )
        return -2;
    ptrNoAux->ptrDado = ptrNovoElemento;
    ptrNoAux->ptrAnt  = NULL;
    if ( !ptrLista->qtdeElementos ) // verifica se lista esta vazia
    {
        ptrNoAux->ptrProx = NULL;   // nao ha elementos antes do primeiro
        ptrLista->ptrFim  = ptrNoAux; // seta ptrInicio para primeiro elemento inserido
    }
    else
    {
        ptrNoAux->ptrProx           = ptrLista->ptrInicio; // novo elemento aponta para o ultimo corrente
        ptrLista->ptrInicio->ptrAnt = ptrNoAux; // ultimo elemento corrente aponta para o novo elemento
    }
    ptrLista->ptrInicio = ptrNoAux; // atualiza campo ultimo da lista para novo elemento
    ptrLista->qtdeElementos++;
    return 1;
}
int InsereListaMeio ( ListaDinamica *ptrLista, void *ptrNovoElemento, int idxPosicao )
{
    // caminha pela lista ate encontrar a posicao do novo elemento
    No *ptrAux = ptrLista->ptrInicio;
    while ( idxPosicao-- )
        ptrAux = ptrAux->ptrProx;
    No *ptrNovo = ( No * ) malloc ( sizeof ( No ) );
    if ( !ptrNovo )
        return -2;
    ptrNovo->ptrDado = ptrNovoElemento;
    // manipula ponteiros do novo no para referenciar aos nos anterior e posterior a ele
    ptrNovo->ptrAnt  = ptrAux->ptrAnt;
    ptrNovo->ptrProx = ptrAux;
    // manipula ponteiros do no anterior ao novo no
    ptrNovo->ptrAnt->ptrProx = ptrNovo;
    //    ptrAux->ptrAnt->ptrProx = ptrNovo;
    // manipula ponteiros do no posterior ao novo no
    ptrNovo->ptrProx->ptrAnt = ptrNovo;
    //    ptrAux->ptrAnt = ptrNovo;
    return 1;
}
int InsereListaPosicao ( ListaDinamica *ptrLista, void *ptrNovoElemento, int idxPosicao )
{
    // verifica se a posicao eh valida
    if ( idxPosicao < 0 || idxPosicao > ptrLista->qtdeElementos )
        return -1;
    // verifica se a insercao ocorre no inicio da lista
    if ( !idxPosicao )
        return InsereListaInicio ( ptrLista, ptrNovoElemento );
    // verifica se a insercao ocorre no final da lista
    if ( idxPosicao == ptrLista->qtdeElementos )
        return InsereLista ( ptrLista, ptrNovoElemento );
    return InsereListaMeio ( ptrLista, ptrNovoElemento, idxPosicao );
}
No* ConsultaListaGeral ( ListaDinamica lista, void *ptrChaveBusca )
{
    // percorre conjunto de elementos procurando elemento desejado
    int resultado;
    No *ptrAux = lista.ptrInicio;
    while ( ptrAux )
    {
        resultado = lista.ptrFncComparar ( ptrAux->ptrDado, ptrChaveBusca );
        if ( resultado == 0 ) //encontrou elemento procurado
            return ptrAux;
        ptrAux = ptrAux->ptrProx;
    }
    return NULL;   // elemento nao encontrado
}
void* ExcluiListaFim ( ListaDinamica *ptrLista )
{
    // salva as referencias para o No e para o Dado em si
    No   *ptrAux  = ptrLista->ptrFim;
    void *ptrDado = ptrAux->ptrDado;
    // penultimo elemento se torno o ultimo
    ptrLista->ptrFim = ptrLista->ptrFim->ptrAnt;
    // coloca NULL no ptrProx do "novo ultimo elemento"
    ptrLista->ptrFim->ptrProx = NULL;
    ptrLista->qtdeElementos--;
    free ( ptrAux ); // libera memoria da estrutura No
    return ptrDado; // retorna referencia para o dado excluido
}
void* ExcluiListaMeio ( ListaDinamica *ptrLista, No *ptrAux )
{
    // salva a referencia para o Dado em si
    void *ptrDado = ptrAux->ptrDado;
    // no posterior ao no excluido referencia no anterior ao no excluido
    ptrAux->ptrProx->ptrAnt = ptrAux->ptrAnt;
    // no anterior ao no excluido referencia no posterior ao no excluido
    ptrAux->ptrAnt->ptrProx = ptrAux->ptrProx;
    ptrLista->qtdeElementos--;
    free ( ptrAux ); // libera memoria da estrutura No
    return ptrDado; // retorna referencia para o dado excluido
}
void* ExcluiLista ( ListaDinamica *ptrLista, void *ptrChaveBusca )
{
    No *ptrAux;
    ptrAux = ConsultaListaGeral ( *ptrLista, ptrChaveBusca );
    if ( !ptrAux )
        return NULL;
    if ( ptrAux == ptrLista->ptrInicio )
        return ExcluiListaInicio ( ptrLista );
    if ( ptrAux == ptrLista->ptrFim )
        return ExcluiListaFim ( ptrLista );
    return ExcluiListaMeio ( ptrLista, ptrAux );
}
void* ExcluiListaPosicao ( ListaDinamica *ptrLista, int idxPosicao )
{
    No *ptrAux = NULL;
    // elemento/posicao nao existe
    if ( idxPosicao < 0 || idxPosicao >= ptrLista->qtdeElementos )
        return NULL;
    // verifica se a insercao ocorre no inicio da lista
    if ( !idxPosicao )
        return ExcluiListaInicio ( ptrLista );
    // verifica se a insercao ocorre no final da lista
    if ( idxPosicao == ptrLista->qtdeElementos - 1 )
        return ExcluiListaFim ( ptrLista );
    ptrAux = ptrLista->ptrInicio;
    while ( idxPosicao-- )
        ptrAux = ptrAux->ptrProx;
    return ExcluiListaMeio ( ptrLista, ptrAux );
}
int AlteraLista ( ListaDinamica lista, void *ptrChaveBusca, void *ptrNovo ) //*ptrLista
{
    No *ptrNo = NULL;
    // localiza elemento
    ptrNo = ConsultaListaGeral ( lista, ptrChaveBusca );
    if ( ptrNo )
        return lista.ptrFncCopiar ( ptrNo->ptrDado, ptrNovo );
    else
        return 0;
}
int AlteraListaPosicao ( ListaDinamica lista, int idxPosicao, void *ptrNovo ) //*ptrLista
{
    No *ptrAux = NULL;
    // elemento/posicao nao existe
    if ( idxPosicao < 0 || idxPosicao >= lista.qtdeElementos )
        return -1;
    // localiza elemento
    ptrAux = lista.ptrInicio;
    while ( idxPosicao-- )
        ptrAux = ptrAux->ptrProx;
    return lista.ptrFncCopiar ( ptrAux->ptrDado, ptrNovo );
}
int ConsultaLista ( ListaDinamica lista, void *ptrChaveBusca, void *ptrSaida )
{
    // localiza elemento
    No *ptrAux = ConsultaListaGeral ( lista, ptrChaveBusca );
    if ( !ptrAux )
        return 0;
    // copia dado para o parametro de saida
    return lista.ptrFncCopiar ( ptrSaida, ptrAux->ptrDado );
}
int ConsultaListaPosicao ( ListaDinamica lista, int idxPosicao, void *ptrSaida )
{
    No *ptrAux = NULL;
    // elemento/posicao nao existe
    if ( idxPosicao < 0 || idxPosicao >= lista.qtdeElementos )
        return -1;
    // localiza elemento
    ptrAux = lista.ptrInicio;
    while ( idxPosicao-- )
        ptrAux = ptrAux->ptrProx;
    // copia dado para o parametro de saida
    return lista.ptrFncCopiar ( ptrSaida, ptrAux->ptrDado );
}
