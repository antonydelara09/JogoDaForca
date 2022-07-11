#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>


using namespace std;

void limpaTela(){
    system("CLS");
}

string retPA(){ //retPA = retorna palavra aleatoria
    //Vetor com palavras disponiveis
    string words[20] = {"laranja", "maracuja", "pessego", "maca", "pera", "cereja", "uva", "ameixa", "tanjerina", "goiaba",
    "melancia", "melao", "abacaxi", "banana", "morango", "mamao", "framboesa", "limao", "amora", "kiwi"};

    //Indice gerado no intervalo (0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19)
    int indAle = rand() % 20; //indAle = Indice Aleatorio;

    //Exibe a palavra aleatoriamente
    //cout << words[indAle];

    return words[indAle];
}

string retornaPCM(string palavra, int tamPalavra){ //retornaPCM = Retorna palavra com mascara
    string palavraCM; //palavraCM = palavra com mascara

    //Coloca uma mascara
    for(int i=0; i<tamPalavra;i++){
        palavraCM += "_";
    }
    return palavraCM;
}

void exibeStatus(string palavraCM, int tamPalavra, int tentRest, string letrasJA, string mensagem){
    cout << mensagem;
    cout << "\nPalavra: " << palavraCM << "(Tamanho: "<< tamPalavra << ")";
    cout << "\nTentativas Restantes: " << tentRest <<endl;

    //Exibe as letras arriscadas
    cout << "\nLetras arriscadas: ";
    for(int i=0;i<letrasJA.size();i++){
        cout << letrasJA[i] << ", ";
    }
}

int jogar(int numJogadores){

    //Palavra a ser advinhada();
    string palavra;

    if(numJogadores == 1){
        palavra = retPA();
    }else{
        cout << "\nDigite uma palavra: ";
        cin >> palavra;
    }

    //Tamanho da palavra
    int tamPalavra = palavra.size();

    //Palavra mascarada
    string palavraCM = retornaPCM(palavra, tamPalavra);

    ///VARIAVEIS GERAIS
    int tent=0, maxTent=15;                 //Numero de tentativas e erros
    int i=0;                                //Auxiliar para laços de repeticao
    char letra;                             //Letra arriscada pelo usuario
    int op;                                 //Opções finais
    string letrasJA;                        //Acumula as tentativas do jogador (letrasJA = Letras ja arriscadas)
    string mensagem = "Bem vindo ao jogo\n";  //Feedback do jogador
    bool jaDL = false, acertouLetra = false;  //Auxiliar para saber se a letra ja foi digitada

    do{

        limpaTela();
        //Exibe um status atual do jogo
        exibeStatus(palavraCM, tamPalavra, maxTent - tent, letrasJA, mensagem);
        //Le um palpite
        cout << "Digite uma Letra: ";
        cin >> letra;
        //Percorre as letras ja arriscadas
        for(i=0;i<tent;i++){
            //Se encontrar a letra
            if(letrasJA[i] == letra){
                mensagem = "Essa letra ja foi digitada!";
                //Indica com a variavel booleana
                jaDL = true;
            }
        }

        //Se for uma letra novo
        if(jaDL == false){
            //Incrementa as letras ja arriscadas
            letrasJA += tolower(letra);
            //Percorra a palavra real e
            for(i=0;i<tamPalavra;i++){
                //Se a letra existir na palavra escondida
                if(palavra[i] == tolower(letra)){
                    //Faço aquela letra aparecer na palavra com mascara (palavraCM)
                    palavraCM[i] = palavra[i];

                    acertouLetra = true;

                }
            }
            if(acertouLetra == false){

                mensagem = "voce errou a letra\n";

            }else{

                mensagem = "Voce acertou um letra!\n";
                acertouLetra = false;

            }
            //Aumenta uma tentativa realizada
            tent++;

        }

        //Reiniciando auxiliares
        jaDL = false;
        acertouLetra = false;

    }
    while(palavra != palavraCM && maxTent - tent > 0);

    if(palavra == palavraCM){
        limpaTela();
        cout << "Parabens, voce venceu!"<<endl;
        cout << "A palavra eh " << palavra <<endl;
        cout << "Deseja jogar novamente?" <<endl;
        cout << "Apenas digite o numero 1 para continuar" <<endl;
        cin >> op;
        return op;
    }else{
        limpaTela();
        cout << "Que pena, voce perdeu, ";
        cout << "A palavra era " << palavra <<endl;
        cout << "Deseja jogar novamente?" <<endl;
        cout << "Apenas digite o numero 1 para continuar" <<endl;
        cin >> op;
        return op;
    }

    //cout << "A palavra secreta eh " << palavra << "(Tamanho: "<< tamPalavra << ")";


}

void menuInicial(){
    //Opçcao escolhida pelo usuario
    int op=0;
    ifstream texto("Sobre.txt");
    string sobre;
    limpaTela();
    while (op < 1 || op > 3){
        cout << "=============== J O G O  D A   F O R C A  ================" << endl;
        cout << "\n1 - Jogar Sozinho";
        cout << "\n2 - Jogar em Dupla";
        cout << "\n2 - Sobre";
        cout << "\n3 - Sair" << endl;
        cout << "\nEscolha uma das opçoes e tecle ENTER: ";
        cin >> op;

        switch(op){
            case 1:
                //Inicia o jogo
                cout << "Jogo iniciado" << endl;
                if(jogar(1) == 1){
                    menuInicial();
                }
                break;
            case 2:
                //Inicia o jogo
                cout << "Jogo iniciado" << endl;
                if(jogar(2) == 1){
                    menuInicial();
                }
                break;
            case 3:
                //Sobre o jogo
                cout << "Informacoes do jogo" << endl;
                limpaTela();
                for(string line; getline(texto, line);){
                    sobre += line;
                }
                cout << sobre <<endl;
                cout << "\n\nJogo desenvovido por Antony de Lara em 2021 :D. "<<endl;
                cout << "Para Voltar ao Menu digite (1)" <<endl;
                cin >> op;
                if(op == 1){
                    menuInicial();
                }
                break;
            case 4:
                //Sai do jogo
                cout << "Ate mais!!!" << endl;
                break;
        }
    }

}

int main()
{
    //Para gerar numero realmente aleatórios
    srand((unsigned)time(NULL));

    menuInicial();

    return 0;
}
