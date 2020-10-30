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

2. Una vez se valide el ingreso como administrador, se podrá realizar el registro de usuarios
del cajero electrónico. El formato de registro será el siguiente: cédula, clave, saldo (COP).

3. Debe permitir acceso a los usuarios del sistema y permitir realizar las siguientes
operaciones:
    a. Consultar saldo.
    b. Retirar dinero especificando la cantidad deseada.

4. Se debe actualizar la información del cliente cada vez que acceda al sistema teniendo en
cuenta las siguientes características:
    i. Cada ingreso al cajero por parte de los clientes para retirar dinero o
    consultar el saldo tiene un costo de 1000 COP.
    ii. Cuando se retire dinero del cajero se debe actualizar el saldo en la cuenta
    del usuario.

Nota: Todas las transacciones que se realicen en el cajero deben tener la información
encriptada


=====================================================================

Especificaciones del programa
*********************
Metodo2 desencriptar y encriptar con semilla fija de 4.

Contraseña del admin:"Mateo123"
Ruta relativa para el admin:    "../Aplicacion/BD/sudo.txt"
Ruta relativa para el usuarios: "../Aplicacion/BD/Users.txt"


"sudo.txt" tiene incriptada la contraseña "Mateo123"

El formato de registro será :
cédula de 10 digitos, clave de 4 digitos, Los saldos maximos de 10 digitos.

EL modo administrador no tiene para validar si se ingresaron digitos
o las longitudes de cada dato, como validar si se ingresaron 10 digitos de cedula,etc

usuarios registrados e incripatos en "Users.txt":
0123456789,1111,10000
9876543210,7852,500000

Usario: Ingresa cedula de 10 digitos y clave de 4 digitos

El programa en cada cambio se sale,
excepto el modo admin que puede registrar los usuarios que quiera

=====================================================================
*/

//funciones globales
int semilla=4;
string cedula_usuario;
string clave_usuario;
string saldo_usuario;


//prototipos de función
string lectura(int);
void Escritura(string);
string conversion_a_binario(string);
string binario_a_caracteres(string);
string metodo2_encriptar(string,int);
string metodo2_desencriptar(string,int);
bool validacion_cedula(string);
void registro_de_usuarios(string);
bool validacion_usuario(string);
bool validacion_clave(string);
void consulta();
void retirar();

int main()
{
    //variables
    int cod,n;
    string binario_encriptado;
    string binario;
    string contenido_des;
    string admin;
    string Users;
    string Usuario;
    bool validacion;

    cout<<"****************************"<<endl<<endl;
    cout<<"       $CAJERO ROBARTE$      "<<endl<<endl;
    cout<<"============================"<<endl;
    cout<<"Ingrese 1 para administrador"<<endl;
    cout<<"Ingrese 2 para usuario"<<endl;
    cout<<"Ingrese 0 para salir"<<endl;
    cout<<"============================"<<endl;
    cout<<"Numero: ";
    cin>>cod;
    system("CLS");

    switch(cod){
        case 0:
        system("CLS");
        cout<<"***Gracias por confiar su dinero con nosotros***"<<endl<<endl;
        cout<<"               Vuelva pronto"<<endl<<endl;
        return 0;
        break;

        case 1:
            cout<<"Ingrese clave de administrador: ";
            cin>>admin;

            binario_encriptado=lectura(cod);
            binario = metodo2_desencriptar(binario_encriptado,semilla);
            contenido_des = binario_a_caracteres(binario);

            //validacion de clave
            if(admin!=contenido_des){
                cout<<"  **Clave incorrecta**"<<endl<<endl;
                cout<<"Salida de administrador"<<endl;
                cout<<"     Vuelva pronto"<<endl<<endl;
                return 0;
            }

            do{
                system("CLS");
                cout<<"       ******************"<<endl;
                cout<<"       Modo Administrador"<<endl;
                cout<<"       ******************"<<endl<<endl;
                cout<<"================================="<<endl;
                cout<<"Ingrese 1 para registrar usuarios"<<endl;
                cout<<"Ingrese 0 para salir"<<endl;
                cout<<"================================="<<endl;
                cout<<"Numero: ";
                cin>>n;
                switch(n){
                 case 0:
                    system("CLS");
                    cout<<"  Salida de administrador"<<endl;
                    cout<<"     Vuelva pronto"<<endl<<endl;
                    break;

                case 1:
                    system("CLS");
                    cout<<"             Formato de registro de usuarios"<<endl;
                    cout<<"<cedula de 10 digitos>,<clave de 4 digitos>,<saldo (COP)>"<<endl;
                    cout<<"Ingrese usuario: ";
                    cin>>Users;
                    registro_de_usuarios(Users);
                    break;

                default:
                    cout <<endl<< "**Usted ha ingresado una opcion incorrecta**"<<endl;
                    system("PAUSE");
                }
            }while(n!=0);

            return 0;
        break;

        case 2:
            system("CLS");
            cout<<"         *****Bienvenido****"<<endl<<endl;
            cout<<"           $CAJERO ROBARTE$"<<endl<<endl;
            cout<<"=========================================="<<endl;
            cout<<"     Recuerde ingresar sus datos asi"<<endl;
            cout<<"<cedula de 10 digitos>,<clave de 4 digitos>"<<endl;
            cout<<"=========================================="<<endl;
            cout<<"Ingrese sus datos: ";
            cin>>Usuario;
            validacion=validacion_usuario(Usuario);
            if(validacion==true){
               system("CLS");
               cout<<"\n\n******************************************"<<endl;
               cout<<"Usuario:"<<cedula_usuario<<endl;
               cout<<"******************************************"<<endl;
               cout<<"Ingrese 1 para consultar saldo"<<endl;
               cout<<"Ingrese 2 retirar"<<endl;
               cout<<"Ingrese 0 para salir"<<endl;
               cout<<"=========================================="<<endl;
               cout<<"Numero: ";
               cin>>n;
               switch(n){
               case 0:
                   system("CLS");
                   cout<<"***Gracias por confiar su dinero con nosotros***"<<endl<<endl;
                   cout<<"              Vuelva pronto"<<endl<<endl;
                   break;
               case 1:
                   consulta();
                   system("CLS");
                   cout<<"***Gracias por confiar su dinero con nosotros***"<<endl<<endl;
                   cout<<"              Vuelva pronto"<<endl<<endl;
                   return 0;
                   break;
               case 2:
                   retirar();
                   system("CLS");
                   cout<<"***Gracias por confiar su dinero con nosotros***"<<endl<<endl;
                   cout<<"              Vuelva pronto"<<endl<<endl;
                   return 0;
                   break;

               default:
               cout << "Usted ha ingresado una opcion incorrecta"<<endl;
               cout<<"***Gracias por confiar su dinero con nosotros***"<<endl<<endl;
               cout<<"              Vuelva pronto"<<endl<<endl;
               return 0;
               }
            }
            if(validacion==false){
               system("CLS");
               cout<<"***Gracias por confiar su dinero con nosotros***"<<endl<<endl;
               cout<<"              Vuelva pronto"<<endl<<endl;
            }
            return 0;
        break;

        default:
        cout << "Usted ha ingresado una opcion incorrecta"<<endl;
        cout<<"            Vuelva pronto"<<endl<<endl;

    }
    return 0;
}

void retirar(){

    string binariocod;
    string binario_encriptado;
    string binario;
    string contenido_des;
    string Users_incriptado;

    string cedula_incriptado;
    string clave_incriptado;
    string saldo_incriptado;

   int saldo_numero=::stoi(saldo_usuario);
   int valor=0;

   if(saldo_numero<1000){
       system("CLS");
       cout<<"Usuario:"<<cedula_usuario<<endl;
       cout<<"******************************************"<<endl;
       cout<<"Lo sentimos, no tiene saldo"<<endl;
       exit(1);
   }


   system("CLS");
   cout<<"Usuario:"<<cedula_usuario<<endl;
   cout<<"Recuerde que cada retire tiene un costo de 1,000 pesos"<<endl;
   cout<<"*******************************************************"<<endl;
   cout<<"Ingrese su valor a retirar: ";
   cin>>valor;

   saldo_numero=saldo_numero-valor-1000;

   if(saldo_numero<0){
       system("CLS");
       cout<<"Usuario:"<<cedula_usuario<<endl;
       cout<<"******************************************"<<endl;
       cout<<"Lo sentimos, no se puede retirar ese valor"<<endl;
       system("PAUSE");
       exit(1);
   }


   system("CLS");
   cout<<"Usuario:"<<cedula_usuario<<endl;
   cout<<"******************************************"<<endl;
   cout<<"**********Transaccion realizada***********"<<endl;
   cout<<"******************************************"<<endl;
   cout<<"En su cuenta le quedan: "<<saldo_numero<<endl<<endl;
   system("PAUSE");



   saldo_usuario = to_string(saldo_numero);
   //-----------------------------
   binario = conversion_a_binario(cedula_usuario);
   cedula_incriptado = metodo2_encriptar(binario,semilla);
   //cout<<binariocod.length()<<endl;
   Users_incriptado=cedula_incriptado+' ';

   binario = conversion_a_binario(clave_usuario);
   clave_incriptado = metodo2_encriptar(binario,semilla);
   Users_incriptado+=clave_incriptado+' ';

   binario = conversion_a_binario(saldo_usuario);
   saldo_incriptado = metodo2_encriptar(binario,semilla);
   Users_incriptado+=saldo_incriptado;


   //modificacion de archivo********

   ifstream lectura;
   lectura.open("../Aplicacion/BD/Users.txt",ios::in);
   ofstream aux("../Aplicacion/BD/temporal.txt",ios::out);

   string cedula1_incriptado;
   string clave1_incriptado;
   string saldo1_incriptado;

   if(lectura.is_open()){

       lectura>>cedula1_incriptado;
       while(!lectura.eof()){
           lectura>>clave1_incriptado;
           lectura>>saldo1_incriptado;
           if(cedula1_incriptado==cedula_incriptado){

           }
           else{
             aux<<cedula1_incriptado<<" "<<clave1_incriptado<<" "<<saldo1_incriptado<<endl;
           }
           lectura>>cedula1_incriptado;
       }
       aux<<Users_incriptado<<endl;
       lectura.close();
       aux.close();
   }

   else{
       cout<<"error"<<endl;
   }

   remove("../Aplicacion/BD/Users.txt");
   rename("../Aplicacion/BD/temporal.txt","../Aplicacion/BD/Users.txt");
}










//****************************************************************************
void consulta(){

    string binariocod;
    string binario_encriptado;
    string binario;
    string contenido_des;
    string Users_incriptado;

    string cedula_incriptado;
    string clave_incriptado;
    string saldo_incriptado;

   int saldo_numero=::stoi(saldo_usuario);

   if(saldo_numero<1000){
       system("CLS");
       cout<<"Usuario:"<<cedula_usuario<<endl;
       cout<<"******************************************"<<endl;
       cout<<"Lo sentimos, no tiene saldo"<<endl;
       system("PAUSE");
       exit(1);
   }

   saldo_numero=saldo_numero-1000;
   system("CLS");
   cout<<"Usuario:"<<cedula_usuario<<endl;
   cout<<"******************************************"<<endl;
   cout<<"Su saldo es: "<<saldo_numero<<endl;
   system("PAUSE");

   saldo_usuario = to_string(saldo_numero);

   binario = conversion_a_binario(cedula_usuario);
   cedula_incriptado = metodo2_encriptar(binario,semilla);
   //cout<<binariocod.length()<<endl;
   Users_incriptado=cedula_incriptado+' ';

   binario = conversion_a_binario(clave_usuario);
   clave_incriptado = metodo2_encriptar(binario,semilla);
   Users_incriptado+=clave_incriptado+' ';

   binario = conversion_a_binario(saldo_usuario);
   saldo_incriptado = metodo2_encriptar(binario,semilla);
   Users_incriptado+=saldo_incriptado;


   //modificacion de archivo********

   ifstream lectura;
   lectura.open("../Aplicacion/BD/Users.txt",ios::in);
   ofstream aux("../Aplicacion/BD/temporal.txt",ios::out);

   string cedula1_incriptado;
   string clave1_incriptado;
   string saldo1_incriptado;

   if(lectura.is_open()){

       lectura>>cedula1_incriptado;
       while(!lectura.eof()){
           lectura>>clave1_incriptado;
           lectura>>saldo1_incriptado;
           if(cedula1_incriptado==cedula_incriptado){

           }
           else{
             aux<<cedula1_incriptado<<" "<<clave1_incriptado<<" "<<saldo1_incriptado<<endl;
           }
           lectura>>cedula1_incriptado;
       }
       aux<<Users_incriptado<<endl;
       lectura.close();
       aux.close();
   }

   else{
       cout<<"error"<<endl;
   }

   remove("../Aplicacion/BD/Users.txt");
   rename("../Aplicacion/BD/temporal.txt","../Aplicacion/BD/Users.txt");
}




//****************************************************************************
bool validacion_usuario(string Usuario){
    bool documento;
    bool clave1;

    string binario_encriptado;
    string binario;

    string cedula;
    string clave;

    if(Usuario.length()!=15){
        cout<<"\n\n*****Documento o clave no son validos*****\n\n"<<endl;
        system("PAUSE");
        return 0;
    }

    int length_b = Usuario.length();

    for(int i=0;Usuario[i]!='\n' and i<length_b;i++){
        if(i<10){
           cedula+=Usuario[i];
        }
        else if(i>10){
            clave+=Usuario[i];
        }

    }


    documento = validacion_cedula(cedula);
    clave1 = validacion_clave(clave);

    if(documento==false){
        cout<<"\n\n*****Usuario no registrado*****\n\n"<<endl;
        system("PAUSE");
        return 0;

    }

    if(clave1==false){
        cout<<"\n\n*****Clave invalida*****\n\n"<<endl;
        system("PAUSE");
        return 0;

    }
    cedula_usuario=cedula;
    //clave_usuario=clave;
    return true;
}



//****************************************************************************
void registro_de_usuarios(string Users){

    string Users_incriptado;
    string cedula;
    string clave;
    string saldo;
    string binariocod;
    string binario_encriptado;
    string binario;
    string contenido_des;


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
        cout<<"\n\n*****Usuario ya regristrado*****\n\n"<<endl;
        system("PAUSE");
    }
    else{
        binario = conversion_a_binario(cedula);
        binariocod = metodo2_encriptar(binario,semilla);
        //cout<<binariocod.length()<<endl;
        Users_incriptado=binariocod+' ';

        binario = conversion_a_binario(clave);
        binariocod = metodo2_encriptar(binario,semilla);
        Users_incriptado+=binariocod+' ';

        binario = conversion_a_binario(saldo);
        binariocod = metodo2_encriptar(binario,semilla);
        Users_incriptado+=binariocod;
        Escritura(Users_incriptado);
    }
}

//****************************************************************************
bool validacion_clave(string clave){
    //bool bandera=false;
    string BD=lectura(2);
    //cout<<BD<<endl;
    //return 0;
    string clave1;
    string binario_encriptado;
    string binario;

    string saldo;
    string saldo_encriptado;
    string saldo_binario;

    int length_b = BD.length();

    for(int i=0;i<length_b;i++){


       for(int j=0;BD[i]!='\n';j++,i++){

           if(j==81){
              binario_encriptado=BD[i];
           }
           if(j>81 and j<113)
           {
             binario_encriptado+=BD[i];
           }
           else if(BD[i]!='\n' and j==114){
              saldo_encriptado=BD[i];
           }
           else if(BD[i]!='\n' and j>114){

              saldo_encriptado+=BD[i];
           }
        }

       binario = metodo2_desencriptar(binario_encriptado,4);
       clave1 = binario_a_caracteres(binario);

       //cout<<clave1<<"."<<endl<<endl;
       //system("PAUSE");

       if(clave==clave1){
           saldo_binario = metodo2_desencriptar(saldo_encriptado,4);
           saldo = binario_a_caracteres(saldo_binario);
           //cout<<saldo<<"."<<endl<<endl;
           //system("PAUSE");
           clave_usuario=clave1;
           saldo_usuario=saldo;
           return true;
       }

    }
    return false;
}






//****************************************************************************
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
    cout << "\n\nUsario Registrado<--\n\n" << endl;
    outfile.close();
    system("PAUSE");

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
    //n=1 decodificar
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

    infile.close();
    //cout << "\n\nArchivo leido-->\n\n" << endl;
    return data;
}
