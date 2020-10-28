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

Contraseña del admin:"Mateo123"
Ruta relativa para el admin:    "../Aplicacion/BD/sudo.txt"
Ruta relativa para el usuarios: "../Aplicacion/BD/Users.txt"
sudo.txt tiene la incriptada la contraseña "Mateo123"

El formato de registro usuarios será: cédula 10 digitos, clave 4 digitos, saldo (COP).


=====================================================================





*/



//prototipos de función
void Escritura(string);
string lectura(int);
string conversion_a_binario(string);
string binario_a_caracteres(string);
string metodo2_encriptar(string ,int);
string metodo2_desencriptar(string ,int);
bool validacion_cedula(string);


int main()
{
    int semilla=4;
    int cod=1; // 1 admin

    string admin;
    cout<<"Ingrese clave: ";
    cin>>admin;

    string binario_encriptado=lectura(cod);
    string binario = metodo2_desencriptar(binario_encriptado,semilla);
    string contenido_des = binario_a_caracteres(binario);

    //validacion de clave
    if(admin!=contenido_des){
        cout<<"Clave incorrecta"<<endl;        
    }


    string Users;
    string Users_incriptado;
    string cedula;
    string clave;
    string saldo;
    string binariocod;


    cout<<"Ingrese usuario: ";
    cin>>Users;

    int length_b = Users.length();

    for(int i=0;Users[i]!='\n' and i<length_b;i++){
        if(i<10){
           cedula+=Users[i];
        }
        else if(i>=11 and i<=14){
            clave+=Users[i];
        }
        else if(i>15 and i<length_b){
            saldo+=Users[i];
        }
    }

    bool validar = validacion_cedula(cedula);

    if(validar==true){
        cout<<"Usuario ya regristrado"<<endl;
        return 0;
    }

    /*cout<<cedula<<endl;
    cout<<clave<<endl;
    cout<<saldo<<endl;*/

    binario = conversion_a_binario(cedula);
    binariocod = metodo2_encriptar(binario,semilla);
    //cout<<binariocod.length()<<endl;
    Users_incriptado=binariocod+',';

    binario = conversion_a_binario(clave);
    binariocod = metodo2_encriptar(binario,semilla);
    Users_incriptado+=binariocod+',';

    binario = conversion_a_binario(saldo);
    binariocod = metodo2_encriptar(binario,semilla);
    Users_incriptado+=binariocod;

    Escritura(Users_incriptado);

    return 0;

}

bool validacion_cedula(string cedula){
    //bool bandera=false;
    string BD=lectura(2);
    //cout<<BD<<endl;
    //return 0;
    string cedula1;
    string binario_encriptado;
    string binario;

    int length_b = BD.length();

    for(int i=0;i<length_b;i++){


       for(int j=0;BD[i]!='\n';j++,i++){

           if(j==0){
              binario_encriptado=BD[i];
           }
           else if(BD[i]!=',' and j<80)
           {
             binario_encriptado+=BD[i];
           }
        }

        binario = metodo2_desencriptar(binario_encriptado,4);
        cedula1 = binario_a_caracteres(binario);

        if(cedula==cedula1){
            return true;
        }
    }

    return false;
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
void Escritura(string binariocod){



    ofstream outfile;


    // Se pone de manera explicita la ruta relativa donde se encuentra el archivo
    outfile.open("../Aplicacion/BD/Users.txt",std::ofstream::app);





    // Se comprueba si el archivo fue abierto exitosamente
    if (!outfile.is_open())
    {
     cout << "\n\nError abriendo el archivo\n\n" << endl;
     exit(1);
    }

    outfile << binariocod << endl;

    // Se cierra el archivo
    //cout << "\n\nArchivo Escrito<--\n\n" << endl;
    outfile.close();
}






/****************************************1. Lectura de archivos*/
string lectura(int n){

    string data;
    string frase;
    // Abre el archivo en modo lectura
    ifstream infile;

    //admin
    if(n==1){
        infile.open("../Aplicacion/BD/sudo.txt");
    }
    //n=1 users
    if(n==2){
        infile.open("../Aplicacion/BD/Users.txt");
    }



    // Se comprueba si el archivo fue abierto exitosamente
    if (!infile.is_open())
    {
     cout << "\n\n!Error abriendo el archivo¡\n\n" << endl;
     exit(1);
    }

    if(n==1){  //admin
        infile >> data;
    }
    else{ //users
        while (! infile.eof() ) {
            getline (infile,frase);
            data+=frase+'\n'; // almacenar en un string
        }
    }


    //cout << "\n\nArchivo leido-->\n\n" << endl;
    return data;
}
