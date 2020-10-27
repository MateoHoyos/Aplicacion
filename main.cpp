#include <iostream>
#include <fstream> //clase fstream
#include <string>

using namespace std;

string conversion_a_binario(string);
string binario_a_caracteres(string);


int main()
{
    string contenido="M";
    int semilla=4;
    string binario;
    binario=conversion_a_binario(contenido);

    //***********************************************************

    int length_b = binario.length();
    string binariocod;



    //Codificacion
    int pos=0;
    bool bandera=false;

    for (int i=0;i<length_b;) {

        for (int j=0;j<semilla-1&&i<length_b;i++,j++) {


            //el primer bit corresponde al ultimo bit
            if(bandera == false)
            {
            pos=(i+semilla)-1;
            binariocod+=binario[pos];
            bandera=true;
            binariocod+=binario[i];
            }
            else
            {
              binariocod+=binario[i];
            }

        }

        bandera=false;
        i++;

    }

    //cout<<binariocod<<endl;

    //****************************************************************************




    //***********************************************************
    //Decodificacion

    length_b=binariocod.length();
    string contenido1=binariocod;
    string binario1;

    for (int i=0,pos=0;i<length_b;)
    {
        pos=i;//primera posicion del grupo n semilla
        i++;

        for (int j=0;j<semilla-1;j++,i++) {
                binario1.insert(i-1,"contenido1[i]");
                //binario1[i-1]+=contenido1[i];
        }

        binario1[i-1]+=contenido1[pos];
    }


    string frase=binario_a_caracteres(binario1);
    cout<<frase<<endl;
    return 0;
}


//****************************************************************************
string conversion_a_binario(string contenido){

    //palabra a binario
    //Decimal a binario
    //contador=128 posicion maxima del binario 2^7
    //j<8 son 8 pisiciones del binario
    string binario;
    string aux=contenido; //
    int longitud=contenido.length();


    for (int i=0,contador=128;i<longitud;i++) { //para cada caracter
        for (int j=0;j<8;j++) { //para los 8 bits que ocupa cada caracter
            //numero menor o igual al que esta en aux[i] de izd a der
            if(aux[i]>=contador)
            {
                binario+=49; //ascii del 1 es 49
                //contenido[i]-=contador;
                aux.at(i)-=contador;
                contador/=2; //va disminuyendo 2^n/2
            }

            else
            {
                binario+=48; //ascii del 0 es 48
                contador/=2;
            }
        }

        contador=128;
    }

    return binario;
}


//****************************************************************************
string binario_a_caracteres(string binario){

    string  frase;
    int length_b = binario.length();
    int posicion=0;
    for (int i=0,contador=128,suma=0;i<length_b;) {
        for (int j=0;j<8;i++,j++) {

            if(binario[i]==49)
            {
               suma+=contador;
               contador/=2;
            }

            else
            {
               contador/=2;
            }
        }

        contador=128;
        frase+=suma;
        posicion ++;
        suma=0;
    }

    //cout<<frase<<endl;

    return frase;
}


