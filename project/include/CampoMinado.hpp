#include <iostream>

using namespace std;

class Campo_minado
{
    private:
        int _linhas;
        int _colunas;
        int _bombas;
        char** _campo;
        int _bandeira;

    public:
        Campo_minado(int escolha);
        ~Campo_minado();

        void Exibe_campo();
        
        int retorna_linha();
        int retorna_coluna();
        int retorna_bombas();
        char retorna_campo(int linha, int coluna);

        void seleciona_campo(int linhas, int colunas, char insercao);
};

Campo_minado::Campo_minado(int escolha){ // para o tamanho do tabuleiro e bombas segui o modelo do windows mesmo

    switch (escolha){
        case 1:
            _linhas = 8;
            _colunas = 8;
            _bombas = 10;
            break;
        case 2:
            _linhas= 14;
            _colunas= 18;
            _bombas= 40;
            break;
        case 3:
            _linhas=20;
            _colunas=24;
            _bombas=99;    
        default:
            break;
    }

    
    _campo = new char*[ _linhas ];
    for(int i = 0; i < _linhas; ++i){
        _campo[i] = new char[_colunas];
        for(int j = 0; j < _colunas; ++j){
            _campo[i][j] = '#'; 
        }
    }
}

Campo_minado::~Campo_minado(){

    for(int i = 0; i < _linhas; ++i){delete[] _campo[i];}
    delete[] _campo;
}

void Campo_minado::Exibe_campo(){
    printf(" ");
    for(int k=0; k<_colunas; k++){
        printf(" %d ", k);
    }
    printf("\n");
    for(int i = 0; i < _linhas; ++i){
        printf("%d", i);
        for(int j = 0; j < _colunas; ++j){
            printf(" %c ", _campo[i][j]);
        }
        printf("\n");
    }
}

int Campo_minado::retorna_linha()
{
    return _linhas;
}

int Campo_minado::retorna_coluna()
{
    return _colunas;
}

int Campo_minado::retorna_bombas()
{
    return _bombas;
}

char Campo_minado::retorna_campo(int linha, int coluna)
{
    return _campo[linha][coluna];
}

void Campo_minado::seleciona_campo(int linhas, int colunas, char insercao){
    #if DEBBUG
    printf("Acessando _campo[%d][%d]\n", linhas, colunas);
    #endif
    _campo[linhas][colunas] = insercao;
}


// prototipos de funcoes pro compilador nao reclamar ( fazer header depois )
void bombasadj(Campo_minado &campo, int linha, int coluna);
void abre_em_volta(Campo_minado &campo, int x, int y);

Campo_minado inicia_jogo(){
    srand(time(NULL)); // inicia contador de tempo para pseudo aleatoriedade da posicao das bombas
    int escolha;
    printf("ESSE JOGO EH FODA\n\n Escolha dificuldade por favor :3\n"); // aq da pra fazer a interface do titulo
    cin>>escolha;
    Campo_minado campo(escolha);
    return campo;
}

void bombasadj(Campo_minado &campo, int linha, int coluna) // funcao recursiva de abre em volta
{
    int i,j,numero_bombas;
    numero_bombas=0;
    for(i=-1;i<=1;i++)
    {
        for(j=-1;j<=1;j++)
        {
            if (linha + i >= 0 && linha + i < campo.retorna_linha() &&
                coluna + j >= 0 && coluna + j < campo.retorna_coluna() &&
                campo.retorna_campo(linha + i, coluna + j) == '*'){
                numero_bombas++;
            }
        }
    }
    
    campo.seleciona_campo(linha, coluna, numero_bombas + '0');
    if( campo.retorna_campo(linha, coluna) == '0') // sqr[linha][coluna] == '0'
    {
        for(i=-1;i<=1;i++)
        {
            for(j=-1;j<=1;j++)
            {
                if(linha+i>=0 && linha+i<= campo.retorna_linha() && coluna+j>=0 && coluna+j<= campo.retorna_coluna())
                    abre_em_volta(campo, linha+i, coluna+j);
            }
        }
    }
}

void abre_em_volta(Campo_minado &campo, int x, int y) // funcao recursiva que depende de bombas adjascentes, e e acionada ate encontrat um numero
{
    if(x< 0 || x>= campo.retorna_linha() || y< 0 || y>= campo.retorna_coluna()){ // fora do campo
        return ; 
    }

    if(campo.retorna_campo(x, y) != '#'){ // ja foi processado
        return ; 
    }

    bombasadj(campo, x, y);
}

int loop_de_escolhas(Campo_minado &campo_principal)
{
    campo_principal.Exibe_campo();
    int linha, coluna;
    printf("faca a escolha da linha e coluna desejada :3 \n");
    cin>> linha >> coluna;

    if(linha > campo_principal.retorna_linha() || coluna > campo_principal.retorna_coluna() ||
       linha < 0                               || coluna < 0){
        printf("OH ANIMAL DO KRL, ESCOLHE CERTO\n");
        return 0;
    }
    else{
        if(campo_principal.retorna_campo(linha, coluna) == '*'){ // voce clicou em uma bomba
            printf("VOCE EH BOBAO CLICOU NA BOMBA ZÉ\n");
            return 0;
        }
        bombasadj(campo_principal, linha, coluna);
    }
    
    return 1;
}

void bomba( Campo_minado &campo, int linha, int coluna)  // funcao de definicao de posicao de bombas aleatoria
{
    srand(time(NULL));
    int i,b,a;
    for(i=0;i<campo.retorna_bombas();i++)
    {
        b=rand()%(campo.retorna_coluna());
        a=rand()%(campo.retorna_linha());
        if(a == linha && b== coluna){ // se o lugar escolhido pelo jogador for inserido bomba, repete processo
            i--;
        }
        else{
            campo.seleciona_campo(a, b, '*');
        }
    }
}

// aqui faremos a primeira leitura da jogada do jogador e colocamos a bomba depois
// para o caso do jogador nao escolher o primeiro lugar e ser uma bomba
void preenche_bombas( Campo_minado &campo_principal)
{
    campo_principal.Exibe_campo();
    int linha, coluna;
    printf("faca a escolha da linha e coluna desejada :3 \n");
    cin>> linha >> coluna;

    while(linha > campo_principal.retorna_linha() || coluna > campo_principal.retorna_coluna() ||
       linha < 0                               || coluna < 0){
        printf("OH ANIMAL DO KRL, ESCOLHE CERTO\n");
        cin>> linha >> coluna;
    }
    
    bomba( campo_principal, linha, coluna);

    bombasadj(campo_principal, linha, coluna);

    system("clear");

    return ;
}