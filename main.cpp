#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;

/*
Práctica 3 -- parte 2 [Aplicación]

Modelar un sistema de registro de usuarios que tenga las siguientes funcionalidades:

1. Acceder al sistema como usuario administrador.
Nota: La validación de acceso se debe hacer abriendo el archivo sudo.txt y comparando con la
clave registrada que debe estar encriptada.



=====================================================================

Especificaciones del programa
*********************
Metodo2 desencriptar y encriptar con semilla fija de 4.

=====================================================================





*/



//prototipos de función
string lectura(int);
void Escritura(string,int);
string conversion_a_binario(string);
string binario_a_caracteres(string);
string metodo2_encriptar(string ,int);
string metodo2_desencriptar(string ,int);


int main()
{
    string contenido;
    string contenidocod;
    string binario;
    string binariocod;
    int semilla=4,cod=1; //cod encriptar
    contenido=lectura(cod);

    binario = conversion_a_binario(contenido);
    //cout <<"\n\n"<< binario << "\n\n";
    binariocod = metodo2_encriptar(binario,semilla);
    //cout <<"\n\n"<< binariocod << "\n\n";
    Escritura(binariocod,cod);

    cod=2; //descriptar
    contenido=lectura(cod);

    binario = metodo2_desencriptar(contenido,semilla);
    //cout <<"\n\n"<< binario << "\n\n";

    contenidocod = binario_a_caracteres(binario);
    //cout <<"\n\n"<< contenidocod << "\n\n";
    //return 0;
    Escritura(contenidocod,cod);
}



//****************************************************************************
string metodo2_encriptar(string binario,int semilla){
    //Codificacion
    int length_b = binario.length();
    string binariocod;
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
    return binariocod ;

}


//****************************************************************************
string metodo2_desencriptar(string contenido1,int semilla){
    //Decodificacion

    int length_b=contenido1.length();
    string binario1;

    for (int i=0,pos=0;i<length_b;)
    {
        pos=i;//primera posicion del grupo n semilla
        i++;

        for (int j=0;j<semilla-1 and i<length_b;j++,i++) {
                binario1+=contenido1[i];
                //binario1[i-1]+=contenido1[i];
        }
        binario1+=contenido1[pos];
        //binario1[i-1]+=contenido1[pos];
    }
    return binario1 ;
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





/*****************************************! 2. Escritura de archivos */
void Escritura(string binariocod,int n){

    //char data[100];

    // abrir un archivo en modo escritura
    ofstream outfile;

    if(n==1){
        // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
        outfile.open("../Aplicacion/BD/Binario_codificado.txt");
    }

    if(n==2){
        // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
        outfile.open("../Aplicacion/BD/Binario_decodificado.txt");
    }


    // Se comprueba si el archivo fue abierto exitosamente
    if (!outfile.is_open())
    {
     cout << "\n\nError abriendo el archivo\n\n" << endl;
     exit(1);
    }

//    cout << "\n\nEscribiendo en el archivo" << endl;
//    cout << "Ingresa tu nombre: ";
//    cin.getline(data, 100);

    // Escribir el dato ingresado en el archivo
    outfile << binariocod << endl;

//    cout << "Ingresa tu edad: ";
//    cin >> data;
//    cin.ignore();

//    // Se escribe la edad en el archivo
//    outfile << data << endl;

    // Se cierra el archivo
    cout << "\n\nArchivo Escrito<--\n\n" << endl;
    outfile.close();
}






/****************************************1. Lectura de archivos*/
string lectura(int n){

    string data;
    // Abre el archivo en modo lectura
    ifstream infile;

    //****************************************************************************************
    //****************************************************************************************

    /*string nombre;
    string frase;

    cout << "Dime el nombre del fichero: ";
    getline(cin,nombre);

    infile.open ( nombre.c_str() , ios::in);
    if (infile.is_open()) {

        while (! infile.eof() ) {
            getline (infile,frase);
            data+=frase; // almacenar en un string
        }

        infile.close();
    }

    else {cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;
          exit(1); //terminar programa
    }*/

    //****************************************************************************************
    //****************************************************************************************



    // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
    //n=1 codificar
    if(n==1){
        infile.open("../Aplicacion/BD/afile.txt");
    }
    //n=1 decodificar
    if(n==2){
        infile.open("../Aplicacion/BD/Binario_codificado.txt");
    }



    // Se comprueba si el archivo fue abierto exitosamente
    if (!infile.is_open())
    {
     cout << "\n\n!Error abriendo el archivo¡\n\n" << endl;
     exit(1);
    }

    //cout << "\n\nLeyendo el archivo\n\n" << endl;
    infile >> data;
    //
    // Se escribe el dato en la pantalla
//    cout << data << endl;
//    cout << "longitud: " << data.length() << endl;

//    cout << "Impresion caracter a caracter" << endl;
//    for (unsigned int i = 0; i < data.length(); i++) {
//       cout << data.at(i) << endl;
//    }

//    // Se cierra el archivo abierto
//    infile.close();
    //

    cout << "\n\nArchivo leido-->\n\n" << endl;
    return data;
}
