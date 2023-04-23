#include<iostream>
#include<cmath>
#include<windows.h>

using namespace std;

void gotoxy(int x,int y){
          HANDLE hcon;
          hcon = GetStdHandle(STD_OUTPUT_HANDLE);
          COORD dwPos;
          dwPos.X = x;
          dwPos.Y= y;
          SetConsoleCursorPosition(hcon,dwPos);
        };

// Clase base -Funcion-
class funcion{
private:
    double c,fc;
    int m;
    int columnas;
    double* pol;

public:
     ~funcion(){
        delete []pol;
     }
    void pedir_polinomio(){
        cout<<"  Ingresa el grado del polinomio: "; cin>>m;
        cout<<endl;
        //-- matriz --
        columnas=2*(m+1);

        pol= new double [columnas];
        for(int j=0;j<columnas;j++){
            pol[j]=0;
        }

        int exp=m;
        for(int j=0; j<columnas;j=j+2){
            cout<<"  Ingresa el coeficiente de x^"<<exp<<"= ";
            cin>>pol[j];
            pol[j+1]=exp;
            exp--;
        }

        cout<<"\n  El polinomio ingresado es:  ";
    for(int k=0;k<columnas;k=k+2){
        cout<<pol[k];
        if(k+2<columnas)
            cout<<" x^"<<pol[k+1]<<" + ";
    }
    cout<<endl<<endl<<"  ";
    system("pause");
    }

    void leer(double n){
    c=n;
    }

    void evaluar(){
        fc=0;
        for(int j=0;j<columnas;j=j+2){
            fc=fc+(pol[j]*pow(c,pol[j+1]));
        }
    }
    double resultado(){
    return fc;
    }
};

// Clase derivada -Metodo-
class Metodo:protected funcion{
private:
    double cl,cu,cr,fcl,fcu,fcr,er;

public:
    void polinomio(){
        pedir_polinomio();
    }
    int valida_intervalo(double a,double b){
        cl=a;
        cu=b;
        leer(cl);
        evaluar();
        fcl=resultado();
        leer(cu);
        evaluar();
        fcu=resultado();
        if((fcl*fcu)<0)
        return 0;
        else
        return 1;
    }
    double biseccion(){
        leer(cl);
        evaluar();
        fcl=resultado();
        leer(cu);
        evaluar();
        fcu=resultado();
        cr=(cl+cu)/2;
        leer(cr);
        evaluar();
        fcr=resultado();

            if((fcl*fcr)<0){
            cu=cr;

        return cr;
        }
        else if((fcl*fcr)>0){
        cl=cr;
        return cr;
        }
        else
        return cr;
        }

        double regla_falsa(){
        leer(cl);
        evaluar();
        fcl=resultado();
        leer(cu);
        evaluar();
        fcu=resultado();
        cr=cu-((fcu*(cl-cu))/(fcl-fcu));
        leer(cr);
        evaluar();
        fcr=resultado();

            if((fcl*fcr)<0){
            cu=cr;

        return cr;
        }
        else if((fcl*fcr)>0){
        cl=cr;
        return cr;
        }
        else
        return cr;
        }

    double error(double ant){
        er=(fabs((cr-ant)/cr))*100;
        return er;
    }

    void imprimir_cl(){
        cout<<cl;
    }
    void imprimir_cu(){
        cout<<cu;
    }
};

// Funcion principal
int main(){
int flag=1,i=1;
int a2,b2;
int it_b,it_rf;
double err_b,err_rf;
double a,b,raiz,anterior=0,error,tol=0;
Metodo obj;
    system("color 0A");
    cout<<"\n\t\tMETODO DE BISECCION Y REGLA FALSA"<<endl<<endl;
    obj.polinomio();
    do{
        system("cls");
        cout<<"\n  Ingrese el limite inferior Xl: ";
        cin>>a;
        a2=a;
        cout<<"  Ingrese el limite superior Xu: ";
        cin>>b;
        b2=b;
        cout<<"  Ingrese la tolerancia: ";
        cin>>tol;
        flag=obj.valida_intervalo(a,b);
        if(flag==1){
        cout<<"  Intervalo no valido... intenta de nuevo"<<endl;
        system("pause");
        }
    }while(flag!=0);
system("cls");
system("color 0B");
cout<<"\n\t\t\tMETODO: BISECCION"<<endl;
gotoxy(2,4);cout<<"It\t\t Xl\t\t Xu\t\t Xr\t\tError"<<endl;
gotoxy(1,5);cout<<"-----------------------------------------------------------------------"<<endl;
    do{
        raiz=obj.biseccion();
        error=obj.error(anterior);
        gotoxy(2,i+5);cout<<i;
        gotoxy(17,i+5);obj.imprimir_cl();
        gotoxy(32,i+5);obj.imprimir_cu();
        gotoxy(47,i+5);cout<<raiz;
        gotoxy(62,i+5);cout<<error<<endl;
        anterior=raiz;
        i++;
    }while(error>=tol);
    it_b=i-1;
    err_b=error;
    cout<<endl<<"  ";
    system("pause");
    system("cls");

    flag=1;
    i=1;
    anterior=0;

    flag=obj.valida_intervalo(a2,b2);

system("color 0E");
cout<<"\n\t\t\tMETODO: REGLA FALSA"<<endl;
gotoxy(2,4);cout<<"It\t\t Xl\t\t Xu\t\t Xr\t\tError"<<endl;
gotoxy(1,5);cout<<"-----------------------------------------------------------------------"<<endl;
    do{
        raiz=obj.regla_falsa();
        error=obj.error(anterior);
        gotoxy(2,i+5);cout<<i;
        gotoxy(17,i+5);obj.imprimir_cl();
        gotoxy(32,i+5);obj.imprimir_cu();
        gotoxy(47,i+5);cout<<raiz;
        gotoxy(62,i+5);cout<<error<<endl;
        anterior=raiz;
        i++;
    }while(error>=tol);
    it_rf=i-1;
    err_rf=error;
    cout<<endl<<"  ";
system("pause");
system("cls");
system("color 0A");
    cout<<"\n  Biseccion..."<<endl<<"  Ultima iteracion: "<<it_b<<"\tUltimo error: "<<err_b;
    cout<<"\n  Regla falsa..."<<endl<<"  Ultima iteracion: "<<it_rf<<"\tUltimo error: "<<err_rf;
    cout<<"\n\n\n  -> El metodo mas eficiente fue: ";
    if(it_b<it_rf){
        cout<<"Biseccion"<<endl;
    }else if(it_rf<it_b){
        cout<<"Regla falsa"<<endl;
    }else{
        if(err_b<err_rf){
            cout<<"Biseccion"<<endl;
        }else if(err_rf<err_b){
            cout<<"Regla falsa"<<endl;
        }else{
            cout<<"Ambos"<<endl;
        }
    }

cout<<endl<<endl<<"  ";
system("pause");
return 0;
}
