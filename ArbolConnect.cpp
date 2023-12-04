#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class ArbolConnect{
public:
    ArbolConnect();
    void jugar();

private:
    bool provocacion;
    char input[43];
    int terminar;
    int IA;

    void Limpiar();
    int Jugada(int columna);
    int Victoria();
    void ImprimirTablero();
    void Jugar(char Ficha);
    int JugadaIA();
    int MiniMax(int Profundidad);
};

ArbolConnect::ArbolConnect(){
    srand(time(0));
    Limpiar();
}

void ArbolConnect::Limpiar(){ //Limpia el tablero del connect
    provocacion = false;
    for(int i = 0; i < 43; ++i){
        input[i] = ' ';
    }
}

int ArbolConnect::Jugada(int columna){ //Busca la posicion vacia de la columna
    if(columna > 7)
        return 0;

    int n;
    for(int i = 0; i <= 6; ++i){
        if(input[columna + 7 * i] == ' '){
            n = columna + 7 * i;
            break;
        }
    }

    if(n > 42)
        return 0;

    return n;
}

int ArbolConnect::Victoria(){ //Comprueba si ya hay un ganador en el juego
    int temp=0;
    for(int i = 1 ; i<= 42 ; i++)
    {
        if(input[i] != ' ')
        {
            temp++;
            if(i - int((i-1)/7)*7 <= 4) // Horizontal
                if(input[i] == input [i+1] && input[i] == input[i+2] && input[i] == input[i+3])
                    if(input[i] == 'X')
                        return 1 ;
                    else
                        return 2;
            if(i <= 21) //Verical
                if ( input[i] == input[i+7] && input[i] == input[i+14] && input[i] == input[i+21])
                    if(input[i] == 'X')
                        return 1 ;
                    else
                        return 2;
            if(i - int((i-1)/7) * 7 <= 4 && i<=18) //Diagonal para arriba
                if(input[i] == input[i+8] && input[i] == input[i+16] && input[i]==input[i+24])
                    if(input[i] == 'X')
                        return 1 ;
                    else
                        return 2;
            if(i - int((i-1)/7) * 7 >= 4 && i <= 21) //Diagonal par abajo
                if(input[i] == input[i+6] && input[i] == input[i+12] && input[i]==input[i+18])
                    if(input[i] == 'X')
                        return 1 ;
                    else
                        return 2;
        }

    }
    if (temp == 42) //Empate
        return 3;
    return 0;
}

void ArbolConnect::ImprimirTablero() { //Imprime el tablero despues de cada jugada
    cout<<endl<<"    1   "<<"    2   "<<"    3   "<<"    4   "<<"    5   "<<"    6   "<<"    7   "<<endl;

    int j = 42;
    for(int i = 0 ; i<= 23 ; i++)
    {
        if(i % 4 == 0)
            cout<<string(57,'-');
        else
        {
            if( (i - 2) % 4 == 0)
            {
                j=42-(0.25*i+0.5)*6-((0.25*i+0.5)-1) ;
                for(int i = 0 ; i<=6 ; i++)
                {
                    cout<<"|"<<"   "<<input[j]<<"   ";
                    j++;
                }
                cout<<"|";
            }
            else
            {
                for(int i = 0 ; i<=6 ; i++)
                    cout<<"|"<<string(7,' ');
                cout<<"|";
            }
        }
        cout<<endl;
    }
    cout<<string(57,'-');
    if(provocacion == true)
        cout<<endl<<"Estoy a un paso de la victoria O.O"<<endl;
}

void ArbolConnect::Jugar(char Ficha) { //Hace la jugada
    int sth;
    cout<<endl<<"Elija la columna que desea jugar la ficha: "<<endl;
    while(true)
    {
        cin>>sth;
        sth=Jugada(sth);
        if( sth != 0 )
        {
            input[sth] = Ficha;
            return ;
        }
        else
            cout<<"ERROR"<<endl;
    }
}

int ArbolConnect::JugadaIA() {
    float chance[2] = {9999999 , 0};
    for(int column = 1 ; column <= 7 ; column ++)
    {
        terminar = 0;
        IA=0;
        int NumJugado = Jugada(column);
        if( NumJugado != 0 )
        {

            input[NumJugado] = 'O';
            if(Victoria()==2)
               {
                   input[NumJugado]=' ';
                   return NumJugado ;
               }
            float temp = -(100*MiniMax(1));
            if(terminar != 0)
                temp -= ((100*IA)/terminar);
            if(-temp >= 100)
                provocacion = true;
            if(chance[0] > temp)
            {
                chance[0] = temp  ;
                chance[1] = NumJugado;
            }
            
            input[NumJugado] = ' ';
        }
    }
    return chance[1];
}

int ArbolConnect::MiniMax(int Profundidad) {
    char Ficha;
    int NumJugado[8] = {0,0,0,0,0,0,0,0}; // Valores de la entrada de cada columna
    int chance=0;
    if(Profundidad % 2 != 0)
        Ficha='X';
    else
        Ficha='O';
    for(int column = 1 ; column <= 7 ; column ++)
        NumJugado[column]=Jugada(column);
    for(int column = 1 ; column <= 7 ; column++)
    {
        if(NumJugado[column] != 0)
        {
            input[NumJugado[column]]=Ficha;
            if( Victoria() != 0 )
            {
                terminar ++;
                if(Ficha=='O')
                    IA ++;
                else
                    IA --;
                input[NumJugado[column]]=' ';
                return -1;
            }
            input[NumJugado[column]]=' ';
        }
    }
    if(Profundidad <= 6)
    {

        for(int column = 1 ; column <= 7 ; column ++)
        {
            int temp=0;
            if( NumJugado[column] != 0 )
            {
                input[NumJugado[column]]=Ficha;
                if( Victoria() != 0 )
                {
                    terminar++;
                    if(Ficha=='O')
                        IA++;
                    else
                        IA--;
                    input[NumJugado[column]]=' ';
                    return -1;
                }
                temp = MiniMax(Profundidad+1);
                if(column == 1)
                    chance = temp;
                if(chance < temp)
                    chance = temp;
                input[NumJugado[column]]=' ';
            }
        }
    }
    return -chance;
}

void ArbolConnect::jugar() {
    while (true) {
        input[JugadaIA()] = 'O';
        system("cls");
        ImprimirTablero();

        int victoria = Victoria();
        if (victoria != 0) {
            if (victoria == 1)
                cout<<"\n¡Jugador 2 Gana!\n";
            else if (victoria == 2)
                cout<<"\n¡Jugador 1 Gana!\n";
            else if (victoria == 3)
                cout<<"Empate!\n";

            system("pausado");
            Limpiar();
        } else {
            Jugar('X');
        }
    }
}