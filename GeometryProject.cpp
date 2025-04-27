#include <iostream>
#include <sstream>
#include <string>
#include <locale>
#include <vector>
#include <cmath>
using namespace std;

float leerFraccionComoFloat(string entrada) {
    size_t slashPos = entrada.find('/');

    if (slashPos != string::npos) {
        // Es una fracción tipo 3/4
        int numerador = stoi(entrada.substr(0, slashPos));
        int denominador = stoi(entrada.substr(slashPos + 1));

        if (denominador == 0) {
            cerr << "Error: división por cero." << endl;
            return 0;
        }

        return static_cast<float>(numerador) / denominador;
    } else {
        // No hay '/', intentamos interpretarlo como decimal
        try {
            return stof(entrada);  // string to float
        } catch (...) {
            cerr << "Formato inválido." << endl;
            return 0;
        }
    }
}


class Line{
    private:
        vector<float> vectu;
        vector<float> pointp;

    public:
        //constructor
        Line(vector<float> vect,vector<float> point):vectu(vect),pointp(point){}

        //getters
        vector<float> getVectu(){return vectu;}
        vector<float> getPointp(){return pointp;}

};
Line createLine(int& numero) {
    vector<float> vect;
    bool valido = false;

    while (!valido) {
        cout << "\nEscribe el vector director de la recta " << numero << " (inserta x,y,z en orden con . o /):\n";
        vect.clear();

        for (int i = 0; i < 3; i++) {
            string str;
            float x;
            cout << "Número " << i+1 << ":\n";
            cin >> str;
            x = leerFraccionComoFloat(str);
            vect.push_back(x);
        }

        if (abs(vect.at(0)) < 1e-5 && abs(vect.at(1)) < 1e-5 && abs(vect.at(2)) < 1e-5) {
            cout << "(0,0,0) no es un vector válido. Introduce otra vez los datos.\n";
        } else {
            valido = true;
        }
    }

    cout << "\nEscribe un punto de la recta " << numero << " (inserta x,y,z en orden con . o /):\n";
    vector<float> point;
    for (int i = 0; i < 3; i++) {
        string str;
        float x;
        cout << "Número " << i+1 << ":\n";
        cin >> str;
        x = leerFraccionComoFloat(str);
        point.push_back(x);
    }

    numero += 1; // solo sumar cuando ya es una recta válida
    Line line(vect, point);
    return line;
}

class Plane{
    private:
        vector<float> vecteg;
        
    public:
        //constructor
        Plane(vector<float> vectreg):vecteg(vectreg){}

        //getters
        vector<float> getvecteg(){return vecteg;}

};
Plane createPlane(int& numero) {
    vector<float> vecteg;
    bool valido = false;

    while (!valido) {
        cout << "Escribe la ecuación general del plano " << numero << " (inserta Ax+By+Cy+D=0 en orden con . o /):\n";
        vecteg.clear(); // Limpia antes de volver a leer

        for (int i = 0; i < 4; i++) {
            string str;
            float x;
            cout << "Número " << i+1 << ":\n";
            cin >> str;
            x = leerFraccionComoFloat(str);
            vecteg.push_back(x);
        }

        if (abs(vecteg.at(0)) < 1e-5 && abs(vecteg.at(1)) < 1e-5 && abs(vecteg.at(2)) < 1e-5) {
            cout << "(0,0,0) no es un vector normal válido. Introduce otra vez los datos.\n";
        } else {
            valido = true;
            numero += 1; // solo aumentar si el plano es válido
        }
    }

    Plane plane(vecteg);
    return plane;
}

int calcRan2_3x2(float mat[3][2]){
    double aux=0;
    aux=mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    if(abs(aux)>1e-5){return 2;}else{aux=0;}

    aux=mat[0][0]*mat[2][1] - mat[0][1]*mat[2][0];
    if(abs(aux)>1e-5){return 2;}else{aux=0;}
    
    aux=mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0];
    if(abs(aux)>1e-5){return 2;}else{return 1;}
}
int calcRan2_3x3(float mat[3][3]){
    double aux=0;
    aux=mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}
    
    aux=mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][1]*mat[1][2]-mat[0][2]*mat[1][1];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}
    
    aux=mat[1][1]*mat[2][2]-mat[1][2]*mat[2][1];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][0]*mat[2][2]-mat[0][2]*mat[2][0];
    if(abs(aux)>1e-5){return 2;}else{return 1;}
}
int calcRan3_3x3(float mat[3][3]){
    double aux=0;
    aux+=mat[0][0]*mat[1][1]*mat[2][2];
    aux+=mat[1][0]*mat[2][1]*mat[0][2];
    aux+=mat[2][0]*mat[0][1]*mat[1][2];
    
    aux-=mat[0][2]*mat[1][1]*mat[2][0];
    aux-=mat[1][2]*mat[2][1]*mat[0][0];
    aux-=mat[2][2]*mat[0][1]*mat[1][0];
    
    if(abs(aux)<1e-5){return 0;}else{return 3;}
    //se considera 0
}
int calcRan2_3x4(float mat[3][4]){
    double aux=0;
    aux=mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}
    
    aux=mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][1]*mat[1][2]-mat[0][2]*mat[1][1];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}
    
    aux=mat[1][1]*mat[2][2]-mat[1][2]*mat[2][1];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][0]*mat[2][2]-mat[0][2]*mat[2][0];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][2]*mat[1][3]-mat[0][3]*mat[1][2];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}
    
    aux=mat[1][2]*mat[2][3]-mat[1][3]*mat[2][2];
    if(abs(aux)>1e-5){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][1]*mat[2][3]-mat[0][3]*mat[2][1];
    if(abs(aux)>1e-5){return 2;}else{return 1;}


}
int calcRan3_3x4(float mat[3][4]){
    double aux=0;
    aux+=mat[0][0]*mat[1][1]*mat[2][2];
    aux+=mat[1][0]*mat[2][1]*mat[0][2];
    aux+=mat[2][0]*mat[0][1]*mat[1][2];
    aux-=mat[0][2]*mat[1][1]*mat[2][0];
    aux-=mat[1][2]*mat[2][1]*mat[0][0];
    aux-=mat[2][2]*mat[0][1]*mat[1][0];
    
    if(abs(aux)<1e-5){aux=0;}else{return 3;}
    //se considera 0

    aux+=mat[0][1]*mat[1][2]*mat[2][3];
    aux+=mat[1][1]*mat[2][2]*mat[0][3];
    aux+=mat[2][1]*mat[0][2]*mat[1][3];
    aux-=mat[0][3]*mat[1][2]*mat[2][1];
    aux-=mat[1][3]*mat[2][2]*mat[0][1];
    aux-=mat[2][3]*mat[0][2]*mat[1][1];
    
    if(abs(aux)<1e-5){aux=0;}else{return 3;}

    aux+=mat[0][0]*mat[1][1]*mat[2][3];
    aux+=mat[1][0]*mat[2][1]*mat[0][3];
    aux+=mat[2][0]*mat[0][1]*mat[1][3];
    aux-=mat[0][3]*mat[1][1]*mat[2][0];
    aux-=mat[1][3]*mat[2][1]*mat[0][0];
    aux-=mat[2][3]*mat[0][1]*mat[1][0];
    
    if(abs(aux)<1e-5){aux=0;}else{return 3;}

    aux+=mat[0][0]*mat[1][2]*mat[2][3];
    aux+=mat[1][0]*mat[2][2]*mat[0][3];
    aux+=mat[2][0]*mat[0][2]*mat[1][3];
    aux-=mat[0][3]*mat[1][2]*mat[2][0];
    aux-=mat[1][3]*mat[2][2]*mat[0][0];
    aux-=mat[2][3]*mat[0][2]*mat[1][0];
    
    if(abs(aux)<1e-5){return 2;}else{return 3;}
}

int main(){
    setlocale(LC_ALL, "C"); // asegura punto decimal

    cout<<"\nQué quieres hacer?\n -Posición relativa entre 2 rectas (1)\n -Posición relativa entre recta y plano (2)\n -Posición relativa entre 2 planos (3)\n -Posición relativa entre 3 planos (4)\n -Salir (0)\n";
    int op;
    cin>>op;
    int q=1; //variable para que te pida la recta de forma bonita :D
    int w=1; //variable para que te pida el plano de forma bonita :D

    if(op==1){ //entre 2 rectas
        //crear recta 1
        Line line1=createLine(q);
        
        //crear recta 2
        Line line2=createLine(q);
        
        //Matriz A (compuesta por los vectores directores de las rectas)
        float matA[3][2];

        for(int j=0;j<2;j++){
            for(int i=0;i<3;i++){
                if(j==0){
                    matA[i][j]=line1.getVectu().at(i);
                }
                if(j==1){
                    matA[i][j]=line2.getVectu().at(i);
                }
            }
        }

        //Matriz B (compuesta por los vectores directores y el vector formado por los puntos de las rectas)
        vector<float> vectPoints={line2.getPointp().at(0)-line1.getPointp().at(0),line2.getPointp().at(1)-line1.getPointp().at(1),line2.getPointp().at(2)-line1.getPointp().at(2)};
        cout<<"El vector entre los puntos es: "<<vectPoints.at(0)<<" "<<vectPoints.at(1)<<" "<<vectPoints.at(2)<<endl;
        float matB[3][3];

        for(int j=0;j<3;j++){
            for(int i=0;i<3;i++){
                if(j==0){
                    matB[i][j]=line1.getVectu().at(i);
                }
                if(j==1){
                    matB[i][j]=line2.getVectu().at(i);
                }
                if(j==2){
                    matB[i][j]=vectPoints.at(i);
                }
            }
        }

        //Rango de la matriz A
        int rankA= calcRan2_3x2(matA);
        cout<<"El rango de la matriz A es: "<<rankA<<endl;

        //Rango de la matriz B
        int rankB=calcRan3_3x3(matB);
        if(rankB == 0){
            rankB=calcRan2_3x3(matB);
        }
        cout<<"El rango de la matriz B es: "<<rankB<<endl;

        if(rankA==1 && rankB==1){
            cout<<"Las rectas son coincidentes\n";
        }else if(rankA==1 && rankB==2){
            cout<<"Las rectas son paralelas\n";
        }else if(rankA==2 && rankB==2){
            cout<<"Las rectas son secantes\n";
            cout<<"¿Quieres calcular la intersección?\n -Sí (1)\n -No (2)\n";
            cin>>op;
            if(op==1){
                double x,y,z,lmd;
                lmd=(line1.getVectu().at(1)*(line1.getPointp().at(0)-line2.getPointp().at(0))+line1.getVectu().at(0)*(line2.getPointp().at(1)-line1.getPointp().at(1)))/(line1.getVectu().at(1)*line2.getVectu().at(0)-line1.getVectu().at(0)*line2.getVectu().at(1));
                x=line2.getVectu().at(0)*lmd+line2.getPointp().at(0);
                y=line2.getVectu().at(1)*lmd+line2.getPointp().at(1);
                z=line2.getVectu().at(2)*lmd+line2.getPointp().at(2);
                cout<<"El punto de intersección entre las dos rectas es I("<<x<<", "<<y<<", "<<z<<")\n";
            }else if(op==2){
                cout<<"Entendido\n";    
            }else{
                cout<<"Opción no válida\n"<<endl;
            }

        }else if(rankA==2 && rankB==3){
            cout<<"Las rectas se cruzan\n";
        }
        q,w=1;//reseteo variables estéticas
        main();

    }else if(op==2){ //entre recta y plano
        Line line=createLine(q);
        Plane plane=createPlane(w);
        double product = line.getVectu().at(0) * plane.getvecteg().at(0) + line.getVectu().at(1) * plane.getvecteg().at(1) + line.getVectu().at(2) * plane.getvecteg().at(2);
        if(abs(product) > 1e-5){ //product != 0
            cout<<"Son secantes\n";
            cout<<"¿Quieres calcular la intersección?\n -Sí (1)\n -No (2)\n";
            cin>>op;
            if(op==1){
                double x,y,z,lmd;
                lmd=(-plane.getvecteg().at(0)*line.getPointp().at(0)-plane.getvecteg().at(1)*line.getPointp().at(1)-plane.getvecteg().at(2)*line.getPointp().at(2)-plane.getvecteg().at(3))/(plane.getvecteg().at(0)*line.getVectu().at(0)+plane.getvecteg().at(1)*line.getVectu().at(1)+plane.getvecteg().at(2)*line.getVectu().at(2));
                x=line.getVectu().at(0)*lmd+line.getPointp().at(0);
                y=line.getVectu().at(1)*lmd+line.getPointp().at(1);
                z=line.getVectu().at(2)*lmd+line.getPointp().at(2);
                cout<<"El punto de intersección entre las dos rectas es I("<<x<<", "<<y<<", "<<z<<")\n";
            }else if(op==2){
                cout<<"Entendido\n";    
            }else{
                cout<<"Opción no válida\n"<<endl;
            }
        }else if(abs(product) < 1e-5){ //product == 0
            if(abs(line.getPointp().at(0) * plane.getvecteg().at(0) + line.getPointp().at(1) * plane.getvecteg().at(1) + line.getPointp().at(2) * plane.getvecteg().at(2) + plane.getvecteg().at(3))<1e-5){
                cout<<"Son coincidentes\n";
            }else{
                cout<<"Son paralelos\n";
            }
        }
        q,w=1;//reseteo variables estéticas
        main();

    }else if (op==3){ //entre 2 planos
        Plane plane1=createPlane(w);
        Plane plane2=createPlane(w);

        double A = plane1.getvecteg().at(0)/plane2.getvecteg().at(0);
        double B = plane1.getvecteg().at(1)/plane2.getvecteg().at(1);
        double C = plane1.getvecteg().at(2)/plane2.getvecteg().at(2);
        double D = plane1.getvecteg().at(3)/plane2.getvecteg().at(3);

        if(A==B && B==C && C==D){
            cout<<"Son coincidentes";
        }else if(A==B && B==C && C!=D){
            cout<<"Son paralelos";
        }else if(A!=B || A!=C || B!=C){
            cout<<"Son secantes\n";
            cout<<"¿Quieres calcular la recta de intersección?\n -Sí (1)\n -No (2)\n";
            cin>>op;
            if(op==1){
                double v1,v2,v3,x,y,z;
                v1=plane1.getvecteg().at(1)*plane2.getvecteg().at(2)-plane1.getvecteg().at(2)*plane2.getvecteg().at(1);
                v2=plane1.getvecteg().at(2)*plane2.getvecteg().at(0)-plane1.getvecteg().at(0)*plane2.getvecteg().at(2);
                v3=plane1.getvecteg().at(0)*plane2.getvecteg().at(1)-plane1.getvecteg().at(1)*plane2.getvecteg().at(0);
                if(abs(plane1.getvecteg().at(0))>1e-5 && abs(plane2.getvecteg().at(1)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(1))>1e-5){
                    y=(plane2.getvecteg().at(0)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(0))/(plane2.getvecteg().at(1)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(1));
                    x=(-plane1.getvecteg().at(1)*y-plane1.getvecteg().at(3))/(plane1.getvecteg().at(0));
                    z=0;

                }else if(abs(plane1.getvecteg().at(1))>1e-5 && abs(plane2.getvecteg().at(0)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(0))>1e-5){
                    x=(plane2.getvecteg().at(1)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(1))/(plane2.getvecteg().at(0)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(0));
                    y=(-plane1.getvecteg().at(0)*x-plane1.getvecteg().at(3))/(plane1.getvecteg().at(1));
                    z=0;

                }else if(abs(plane1.getvecteg().at(2))>1e-5 && abs(plane2.getvecteg().at(1)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(1))>1e-5){
                    y=(plane2.getvecteg().at(2)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(2))/(plane2.getvecteg().at(1)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(1));
                    z=(-plane1.getvecteg().at(1)*y-plane1.getvecteg().at(3))/(plane1.getvecteg().at(2));
                    x=0;

                }else if(abs(plane1.getvecteg().at(1))>1e-5 && abs(plane2.getvecteg().at(2)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(2))>1e-5){
                    z=(plane2.getvecteg().at(1)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(1))/(plane2.getvecteg().at(2)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(2));
                    y=(-plane1.getvecteg().at(2)*z-plane1.getvecteg().at(3))/(plane1.getvecteg().at(1));
                    x=0;

                }else if(abs(plane1.getvecteg().at(0))>1e-5 && abs(plane2.getvecteg().at(2)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(2))>1e-5){
                    z=(plane2.getvecteg().at(0)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(0))/(plane2.getvecteg().at(2)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(2));
                    x=(-plane1.getvecteg().at(2)*z-plane1.getvecteg().at(3))/(plane1.getvecteg().at(0));
                    y=0;
                    
                }else if(abs(plane1.getvecteg().at(2))>1e-5 && abs(plane2.getvecteg().at(0)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(0))>1e-5){
                    x=(plane2.getvecteg().at(2)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(2))/(plane2.getvecteg().at(0)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(0));
                    z=(-plane1.getvecteg().at(0)*x-plane1.getvecteg().at(3))/(plane1.getvecteg().at(2));
                    y=0;
                    
                }else{
                    cout<<"No se puede calcular"<<endl;
                }

                cout<<"La recta de intersección entre los dos planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
            }else if(op==2){
                cout<<"Entendido\n";    
            }else{
                cout<<"Opción no válida\n"<<endl;
            }
        }else{
            cout<<"Se ha producido un error";
        }
        q,w=1;//reseteo variables estéticas
        main();

    }else if(op==4){ //entre 3 planos
        Plane plane1 = createPlane(w);
        Plane plane2 = createPlane(w);
        Plane plane3 = createPlane(w);
        //Matriz A (compuesta por los vectores directores de las rectas)
        float matA[3][3];

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(i==0){
                    matA[i][j]=plane1.getvecteg().at(j);
                }
                if(i==1){
                    matA[i][j]=plane2.getvecteg().at(j);
                }
                if(i==2){
                    matA[i][j]=plane3.getvecteg().at(j);
                }
            }
        }

        //Matriz B (compuesta por los vectores normales y los términos independientes)
        float matB[3][4];

        for(int i=0;i<3;i++){
            for(int j=0;j<4;j++){
                if(i==0){
                    matB[i][j]=plane1.getvecteg().at(j);
                }
                if(i==1){
                    matB[i][j]=plane2.getvecteg().at(j);
                }
                if(i==2){
                    matB[i][j]=plane3.getvecteg().at(j);
                }
            }
        }

        //Rango de la matriz A
        int rankA=calcRan3_3x3(matA);
        if(rankA == 0){
            rankA=calcRan2_3x3(matA);
        }
        cout<<"El rango de la matriz A es: "<<rankA<<endl;

        //Rango de la matriz B
        int rankB;
        if(rankA==3){
            rankB=3;
        }else if(rankA==2){
            rankB=calcRan3_3x4(matB);
        }else if(rankA==1){
            rankB=calcRan2_3x4(matB);
            if(rankB==2){
                rankB=calcRan3_3x4(matB);
            }
        }
        cout<<"El rango de la matriz B es: "<<rankB<<endl;
        double A1=plane1.getvecteg().at(0);
        double B1=plane1.getvecteg().at(1);
        double C1=plane1.getvecteg().at(2);
        double D1=plane1.getvecteg().at(3);

        double A2=plane2.getvecteg().at(0);
        double B2=plane2.getvecteg().at(1);
        double C2=plane2.getvecteg().at(2);
        double D2=plane2.getvecteg().at(3);

        double A3=plane3.getvecteg().at(0);
        double B3=plane3.getvecteg().at(1);
        double C3=plane3.getvecteg().at(2);
        double D3=plane3.getvecteg().at(3);

        double a12= A1/A2;
        double b12= B1/B2;
        double c12= C1/C2;
        double d12= D1/D2;

        double a13= A1/A3;
        double b13= B1/B3;
        double c13= C1/C3;
        double d13= D1/D3;

        double a23= A2/A3;
        double b23= B2/B3;
        double c23= C2/C3;
        double d23= D2/D3;

       //Asegurarse de que sean coincidentes aunque haya algún 0/0 en Plano1 Plano2
        if(abs(D1)<1e-5&&abs(D2)<1e-5 && abs(C1)<1e-5&&abs(C2)<1e-5 && abs(B1)<1e-5&&abs(B2)<1e-5 && abs(A1)>1e-5&&abs(A2)>1e-5){
            b12=a12;
            c12=a12;
            d12=a12;
        }else if(abs(D1)<1e-5&&abs(D2)<1e-5 && abs(C1)<1e-5&&abs(C2)<1e-5 && abs(B1)>1e-5&&abs(B2)>1e-5 && abs(A1)<1e-5&&abs(A2)<1e-5){
            a12=b12;
            c12=b12;
            d12=b12;
        }else if(abs(D1)<1e-5&&abs(D2)<1e-5 && abs(C1)>1e-5&&abs(C2)>1e-5 && abs(B1)<1e-5&&abs(B2)<1e-5 && abs(A1)<1e-5&&abs(A2)<1e-5){
            a12=c12;
            b12=c12;
            d12=c12;
        }else if(abs(D1)<1e-5&&abs(D2)<1e-5 && abs(C1)<1e-5&&abs(C2)<1e-5 && abs(B1)>1e-5&&abs(B2)>1e-5 && abs(A1)>1e-5&&abs(A2)>1e-5 && a12==b12){
            c12=a12;
            d12=a12;
        }else if(abs(D1)<1e-5&&abs(D2)<1e-5 && abs(C1)>1e-5&&abs(C2)>1e-5 && abs(B1)>1e-5&&abs(B2)>1e-5 && abs(A1)<1e-5&&abs(A2)<1e-5 && c12==b12){
            a12=b12;
            d12=b12;
        }else if(abs(D1)>1e-5&&abs(D2)>1e-5 && abs(C1)>1e-5&&abs(C2)>1e-5 && abs(B1)<1e-5&&abs(B2)<1e-5 && abs(A1)<1e-5&&abs(A2)<1e-5 && c12==d12){
            a12=c12;
            b12=c12;
        }else if(abs(D1)>1e-5&&abs(D2)>1e-5 && abs(C1)<1e-5&&abs(C2)<1e-5 && abs(B1)<1e-5&&abs(B2)<1e-5 && abs(A1)>1e-5&&abs(A2)>1e-5 && a12==d12){
            c12=a12;
            b12=a12;
        }else if(abs(D1)<1e-5&&abs(D2)<1e-5 && abs(C1)>1e-5&&abs(C2)>1e-5 && abs(B1)<1e-5&&abs(B2)<1e-5 && abs(A1)>1e-5&&abs(A2)>1e-5 && a12==c12){
            d12=a12;
            b12=a12;
        }else if(abs(D1)>1e-5&&abs(D2)>1e-5 && abs(C1)<1e-5&&abs(C2)<1e-5 && abs(B1)>1e-5&&abs(B2)>1e-5 && abs(A1)<1e-5&&abs(A2)<1e-5 && b12==d12){
            c12=b12;
            a12=b12;
        }else if(abs(D1)>1e-5&&abs(D2)>1e-5 && abs(C1)<1e-5&&abs(C2)<1e-5 && abs(B1)>1e-5&&abs(B2)>1e-5 && abs(A1)<1e-5&&abs(A2)<1e-5 && b12==d12){
            c12=b12;
            a12=b12;
        }else if(abs(D1)<1e-5&&abs(D2)<1e-5 && abs(C1)>1e-5&&abs(C2)>1e-5 && abs(B1)>1e-5&&abs(B2)>1e-5 && abs(A1)>1e-5&&abs(A2)>1e-5 && a12==b12 && b12==c12){
            d12=a12;
        }else if(abs(D1)>1e-5&&abs(D2)>1e-5 && abs(C1)<1e-5&&abs(C2)<1e-5 && abs(B1)>1e-5&&abs(B2)>1e-5 && abs(A1)>1e-5&&abs(A2)>1e-5 && a12==b12 && b12==d12){
            c12=a12;
        }else if(abs(D1)>1e-5&&abs(D2)>1e-5 && abs(C1)>1e-5&&abs(C2)>1e-5 && abs(B1)<1e-5&&abs(B2)<1e-5 && abs(A1)>1e-5&&abs(A2)>1e-5 && a12==c12 && c12==d12){
            b12=a12;
        }else if(abs(D1)>1e-5&&abs(D2)>1e-5 && abs(C1)>1e-5&&abs(C2)>1e-5 && abs(B1)>1e-5&&abs(B2)>1e-5 && abs(A1)<1e-5&&abs(A2)<1e-5 && b12==c12 && c12==d12){
            a12=b12;
        }
        
        //Asegurarse de que sean coincidentes aunque haya algún 0/0 en Plano1 Plano3
        if(abs(D1)<1e-5&&abs(D3)<1e-5 && abs(C1)<1e-5&&abs(C3)<1e-5 && abs(B1)<1e-5&&abs(B3)<1e-5 && abs(A1)>1e-5&&abs(A3)>1e-5){
            b13=a13;
            c13=a13;
            d13=a13;
        }else if(abs(D1)<1e-5&&abs(D3)<1e-5 && abs(C1)<1e-5&&abs(C3)<1e-5 && abs(B1)>1e-5&&abs(B3)>1e-5 && abs(A1)<1e-5&&abs(A3)<1e-5){
            a13=b13;
            c13=b13;
            d13=b13;
        }else if(abs(D1)<1e-5&&abs(D3)<1e-5 && abs(C1)>1e-5&&abs(C3)>1e-5 && abs(B1)<1e-5&&abs(B3)<1e-5 && abs(A1)<1e-5&&abs(A3)<1e-5){
            a13=c13;
            b13=c13;
            d13=c13;
        }else if(abs(D1)<1e-5&&abs(D3)<1e-5 && abs(C1)<1e-5&&abs(C3)<1e-5 && abs(B1)>1e-5&&abs(B3)>1e-5 && abs(A1)>1e-5&&abs(A3)>1e-5 && a13==b13){
            c13=a13;
            d13=a13;
        }else if(abs(D1)<1e-5&&abs(D3)<1e-5 && abs(C1)>1e-5&&abs(C3)>1e-5 && abs(B1)>1e-5&&abs(B3)>1e-5 && abs(A1)<1e-5&&abs(A3)<1e-5 && c13==b13){
            a13=b13;
            d13=b13;
        }else if(abs(D1)>1e-5&&abs(D3)>1e-5 && abs(C1)>1e-5&&abs(C3)>1e-5 && abs(B1)<1e-5&&abs(B3)<1e-5 && abs(A1)<1e-5&&abs(A3)<1e-5 && c13==d13){
            a13=c13;
            b13=c13;
        }else if(abs(D1)>1e-5&&abs(D3)>1e-5 && abs(C1)<1e-5&&abs(C3)<1e-5 && abs(B1)<1e-5&&abs(B3)<1e-5 && abs(A1)>1e-5&&abs(A3)>1e-5 && a13==d13){
            c13=a13;
            b13=a13;
        }else if(abs(D1)<1e-5&&abs(D3)<1e-5 && abs(C1)>1e-5&&abs(C3)>1e-5 && abs(B1)<1e-5&&abs(B3)<1e-5 && abs(A1)>1e-5&&abs(A3)>1e-5 && a13==c13){
            d13=a13;
            b13=a13;
        }else if(abs(D1)>1e-5&&abs(D3)>1e-5 && abs(C1)<1e-5&&abs(C3)<1e-5 && abs(B1)>1e-5&&abs(B3)>1e-5 && abs(A1)<1e-5&&abs(A3)<1e-5 && b13==d13){
            c13=b13;
            a13=b13;
        }else if(abs(D1)>1e-5&&abs(D3)>1e-5 && abs(C1)<1e-5&&abs(C3)<1e-5 && abs(B1)>1e-5&&abs(B3)>1e-5 && abs(A1)<1e-5&&abs(A3)<1e-5 && b13==d13){
            c13=b13;
            a13=b13;
        }else if(abs(D1)<1e-5&&abs(D3)<1e-5 && abs(C1)>1e-5&&abs(C3)>1e-5 && abs(B1)>1e-5&&abs(B3)>1e-5 && abs(A1)>1e-5&&abs(A3)>1e-5 && a13==b13 && b13==c13){
            d13=a13;
        }else if(abs(D1)>1e-5&&abs(D3)>1e-5 && abs(C1)<1e-5&&abs(C3)<1e-5 && abs(B1)>1e-5&&abs(B3)>1e-5 && abs(A1)>1e-5&&abs(A3)>1e-5 && a13==b13 && b13==d13){
            c13=a13;
        }else if(abs(D1)>1e-5&&abs(D3)>1e-5 && abs(C1)>1e-5&&abs(C3)>1e-5 && abs(B1)<1e-5&&abs(B3)<1e-5 && abs(A1)>1e-5&&abs(A3)>1e-5 && a13==c13 && c13==d13){
            b13=a13;
        }else if(abs(D1)>1e-5&&abs(D3)>1e-5 && abs(C1)>1e-5&&abs(C3)>1e-5 && abs(B1)>1e-5&&abs(B3)>1e-5 && abs(A1)<1e-5&&abs(A3)<1e-5 && b13==c13 && c13==d13){
            a13=b13;
        }

        //Asegurarse de que sean coincidentes aunque haya algún 0/0 en Plano2 Plano3
        if(abs(D2)<1e-5&&abs(D3)<1e-5 && abs(C2)<1e-5&&abs(C3)<1e-5 && abs(B2)<1e-5&&abs(B3)<1e-5 && abs(A2)>1e-5&&abs(A3)>1e-5){
            b23=a23;
            c23=a23;
            d23=a23;
        }else if(abs(D2)<1e-5&&abs(D3)<1e-5 && abs(C2)<1e-5&&abs(C3)<1e-5 && abs(B2)>1e-5&&abs(B3)>1e-5 && abs(A2)<1e-5&&abs(A3)<1e-5){
            a23=b23;
            c23=b23;
            d23=b23;
        }else if(abs(D2)<1e-5&&abs(D3)<1e-5 && abs(C2)>1e-5&&abs(C3)>1e-5 && abs(B2)<1e-5&&abs(B3)<1e-5 && abs(A2)<1e-5&&abs(A3)<1e-5){
            a23=c23;
            b23=c23;
            d23=c23;
        }else if(abs(D2)<1e-5&&abs(D3)<1e-5 && abs(C2)<1e-5&&abs(C3)<1e-5 && abs(B2)>1e-5&&abs(B3)>1e-5 && abs(A2)>1e-5&&abs(A3)>1e-5 && a23==b23){
            c23=a23;
            d23=a23;
        }else if(abs(D2)<1e-5&&abs(D3)<1e-5 && abs(C2)>1e-5&&abs(C3)>1e-5 && abs(B2)>1e-5&&abs(B3)>1e-5 && abs(A2)<1e-5&&abs(A3)<1e-5 && c23==b23){
            a23=b23;
            d23=b23;
        }else if(abs(D2)>1e-5&&abs(D3)>1e-5 && abs(C2)>1e-5&&abs(C3)>1e-5 && abs(B2)<1e-5&&abs(B3)<1e-5 && abs(A2)<1e-5&&abs(A3)<1e-5 && c23==d23){
            a23=c23;
            b23=c23;
        }else if(abs(D2)>1e-5&&abs(D3)>1e-5 && abs(C2)<1e-5&&abs(C3)<1e-5 && abs(B2)<1e-5&&abs(B3)<1e-5 && abs(A2)>1e-5&&abs(A3)>1e-5 && a23==d23){
            c23=a23;
            b23=a23;
        }else if(abs(D2)<1e-5&&abs(D3)<1e-5 && abs(C2)>1e-5&&abs(C3)>1e-5 && abs(B2)<1e-5&&abs(B3)<1e-5 && abs(A2)>1e-5&&abs(A3)>1e-5 && a23==c23){
            d23=a23;
            b23=a23;
        }else if(abs(D2)>1e-5&&abs(D3)>1e-5 && abs(C2)<1e-5&&abs(C3)<1e-5 && abs(B2)>1e-5&&abs(B3)>1e-5 && abs(A2)<1e-5&&abs(A3)<1e-5 && b23==d23){
            c23=b23;
            a23=b23;
        }else if(abs(D2)>1e-5&&abs(D3)>1e-5 && abs(C2)<1e-5&&abs(C3)<1e-5 && abs(B2)>1e-5&&abs(B3)>1e-5 && abs(A2)<1e-5&&abs(A3)<1e-5 && b23==d23){
            c23=b23;
            a23=b23;
        }else if(abs(D2)<1e-5&&abs(D3)<1e-5 && abs(C2)>1e-5&&abs(C3)>1e-5 && abs(B2)>1e-5&&abs(B3)>1e-5 && abs(A2)>1e-5&&abs(A3)>1e-5 && a23==b23 && b23==c23){
            d23=a23;
        }else if(abs(D2)>1e-5&&abs(D3)>1e-5 && abs(C2)<1e-5&&abs(C3)<1e-5 && abs(B2)>1e-5&&abs(B3)>1e-5 && abs(A2)>1e-5&&abs(A3)>1e-5 && a23==b23 && b23==d23){
            c23=a23;
        }else if(abs(D2)>1e-5&&abs(D3)>1e-5 && abs(C2)>1e-5&&abs(C3)>1e-5 && abs(B2)<1e-5&&abs(B3)<1e-5 && abs(A2)>1e-5&&abs(A3)>1e-5 && a23==c23 && c23==d23){
            b23=a23;
        }else if(abs(D2)>1e-5&&abs(D3)>1e-5 && abs(C2)>1e-5&&abs(C3)>1e-5 && abs(B2)>1e-5&&abs(B3)>1e-5 && abs(A2)<1e-5&&abs(A3)<1e-5 && b23==c23 && c23==d23){
            a23=b23;
        }

        if(rankA==1 && rankB==1){
            cout<<"Los 3 planos son coincidentes"<<endl;
        }else if(rankA==1 && rankB==2){
            if((a12==b12&&b12==c12&&c12==d12)||(a13==b13&&b13==c13&&c13==d13)||(a23==b23&&b23==c23&&c23==d23)){
                cout<<"Hay 2 planos coincidentes y 1 paralelo"<<endl;
            }else{
                cout<<"Los tres planos son paralelos"<<endl;
            }
        }else if(rankA==2 && rankB==2){
            if((a12==b12&&b12==c12&&c12==d12)||(a13==b13&&b13==c13&&c13==d13)||(a23==b23&&b23==c23&&c23==d23)){
                cout<<"Hay 2 planos coincidentes y 1 secante"<<endl;
                cout<<"¿Quieres calcular la recta de intersección?\n -Sí (1)\n -No (2)\n";
                cin>>op;
                if(op==1){
                    if((a12==b12&&b12==c12&&c12==d12)||(a23==b23&&b23==c23&&c23==d23)){
                        double v1,v2,v3,x,y,z;
                        v1=plane1.getvecteg().at(1)*plane3.getvecteg().at(2)-plane1.getvecteg().at(2)*plane3.getvecteg().at(1);
                        v2=plane1.getvecteg().at(2)*plane3.getvecteg().at(0)-plane1.getvecteg().at(0)*plane3.getvecteg().at(2);
                        v3=plane1.getvecteg().at(0)*plane3.getvecteg().at(1)-plane1.getvecteg().at(1)*plane3.getvecteg().at(0);
                        if(abs(plane1.getvecteg().at(0))>1e-5 && abs(plane3.getvecteg().at(1)*plane1.getvecteg().at(0)-plane3.getvecteg().at(0)*plane1.getvecteg().at(1))>1e-5){
                            y=(plane3.getvecteg().at(0)*plane1.getvecteg().at(3)-plane3.getvecteg().at(3)*plane1.getvecteg().at(0))/(plane3.getvecteg().at(1)*plane1.getvecteg().at(0)-plane3.getvecteg().at(0)*plane1.getvecteg().at(1));
                            x=(-plane1.getvecteg().at(1)*y-plane1.getvecteg().at(3))/(plane1.getvecteg().at(0));
                            z=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";

                        }else if(abs(plane1.getvecteg().at(1))>1e-5 && abs(plane3.getvecteg().at(0)*plane1.getvecteg().at(1)-plane3.getvecteg().at(1)*plane1.getvecteg().at(0))>1e-5){
                            x=(plane3.getvecteg().at(1)*plane1.getvecteg().at(3)-plane3.getvecteg().at(3)*plane1.getvecteg().at(1))/(plane3.getvecteg().at(0)*plane1.getvecteg().at(1)-plane3.getvecteg().at(1)*plane1.getvecteg().at(0));
                            y=(-plane1.getvecteg().at(0)*x-plane1.getvecteg().at(3))/(plane1.getvecteg().at(1));
                            z=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                        
                        }else if(abs(plane1.getvecteg().at(2))>1e-5 && abs(plane3.getvecteg().at(1)*plane1.getvecteg().at(2)-plane3.getvecteg().at(2)*plane1.getvecteg().at(1))>1e-5){
                            y=(plane3.getvecteg().at(2)*plane1.getvecteg().at(3)-plane3.getvecteg().at(3)*plane1.getvecteg().at(2))/(plane3.getvecteg().at(1)*plane1.getvecteg().at(2)-plane3.getvecteg().at(2)*plane1.getvecteg().at(1));
                            z=(-plane1.getvecteg().at(1)*y-plane1.getvecteg().at(3))/(plane1.getvecteg().at(2));
                            x=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                        
                        }else if(abs(plane1.getvecteg().at(1))>1e-5 && abs(plane3.getvecteg().at(2)*plane1.getvecteg().at(1)-plane3.getvecteg().at(1)*plane1.getvecteg().at(2))>1e-5){
                            z=(plane3.getvecteg().at(1)*plane1.getvecteg().at(3)-plane3.getvecteg().at(3)*plane1.getvecteg().at(1))/(plane3.getvecteg().at(2)*plane1.getvecteg().at(1)-plane3.getvecteg().at(1)*plane1.getvecteg().at(2));
                            y=(-plane1.getvecteg().at(2)*z-plane1.getvecteg().at(3))/(plane1.getvecteg().at(1));
                            x=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                        
                        }else if(abs(plane1.getvecteg().at(0))>1e-5 && abs(plane3.getvecteg().at(2)*plane1.getvecteg().at(0)-plane3.getvecteg().at(0)*plane1.getvecteg().at(2))>1e-5){
                            z=(plane3.getvecteg().at(0)*plane1.getvecteg().at(3)-plane3.getvecteg().at(3)*plane1.getvecteg().at(0))/(plane3.getvecteg().at(2)*plane1.getvecteg().at(0)-plane3.getvecteg().at(0)*plane1.getvecteg().at(2));
                            x=(-plane1.getvecteg().at(2)*z-plane1.getvecteg().at(3))/(plane1.getvecteg().at(0));
                            y=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                        
                        }else if(abs(plane1.getvecteg().at(2))>1e-5 && abs(plane3.getvecteg().at(0)*plane1.getvecteg().at(2)-plane3.getvecteg().at(2)*plane1.getvecteg().at(0))>1e-5){
                            x=(plane3.getvecteg().at(2)*plane1.getvecteg().at(3)-plane3.getvecteg().at(3)*plane1.getvecteg().at(2))/(plane3.getvecteg().at(0)*plane1.getvecteg().at(2)-plane3.getvecteg().at(2)*plane1.getvecteg().at(0));
                            z=(-plane1.getvecteg().at(0)*x-plane1.getvecteg().at(3))/(plane1.getvecteg().at(2));
                            y=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                        
                        }else{
                            cout<<"No se puede calcular"<<endl;
                        }
                    }else if(a13==b13&&b13==c13&&c13==d13){
                        double v1,v2,v3,x,y,z;
                        v1=plane1.getvecteg().at(1)*plane2.getvecteg().at(2)-plane1.getvecteg().at(2)*plane2.getvecteg().at(1);
                        v2=plane1.getvecteg().at(2)*plane2.getvecteg().at(0)-plane1.getvecteg().at(0)*plane2.getvecteg().at(2);
                        v3=plane1.getvecteg().at(0)*plane2.getvecteg().at(1)-plane1.getvecteg().at(1)*plane2.getvecteg().at(0);
                        if(abs(plane1.getvecteg().at(0))>1e-5 && abs(plane2.getvecteg().at(1)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(1))>1e-5){
                            y=(plane2.getvecteg().at(0)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(0))/(plane2.getvecteg().at(1)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(1));
                            x=(-plane1.getvecteg().at(1)*y-plane1.getvecteg().at(3))/(plane1.getvecteg().at(0));
                            z=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";

                        }else if(abs(plane1.getvecteg().at(1))>1e-5 && abs(plane2.getvecteg().at(0)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(0))>1e-5){
                            x=(plane2.getvecteg().at(1)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(1))/(plane2.getvecteg().at(0)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(0));
                            y=(-plane1.getvecteg().at(0)*x-plane1.getvecteg().at(3))/(plane1.getvecteg().at(1));
                            z=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                        
                        }else if(abs(plane1.getvecteg().at(2))>1e-5 && abs(plane2.getvecteg().at(1)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(1))>1e-5){
                            y=(plane2.getvecteg().at(2)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(2))/(plane2.getvecteg().at(1)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(1));
                            z=(-plane1.getvecteg().at(1)*y-plane1.getvecteg().at(3))/(plane1.getvecteg().at(2));
                            x=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                        
                        }else if(abs(plane1.getvecteg().at(1))>1e-5 && abs(plane2.getvecteg().at(2)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(2))>1e-5){
                            z=(plane2.getvecteg().at(1)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(1))/(plane2.getvecteg().at(2)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(2));
                            y=(-plane1.getvecteg().at(2)*z-plane1.getvecteg().at(3))/(plane1.getvecteg().at(1));
                            x=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                        
                        }else if(abs(plane1.getvecteg().at(0))>1e-5 && abs(plane2.getvecteg().at(2)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(2))>1e-5){
                            z=(plane2.getvecteg().at(0)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(0))/(plane2.getvecteg().at(2)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(2));
                            x=(-plane1.getvecteg().at(2)*z-plane1.getvecteg().at(3))/(plane1.getvecteg().at(0));
                            y=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                        
                        }else if(abs(plane1.getvecteg().at(2))>1e-5 && abs(plane2.getvecteg().at(0)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(0))>1e-5){
                            x=(plane2.getvecteg().at(2)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(2))/(plane2.getvecteg().at(0)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(0));
                            z=(-plane1.getvecteg().at(0)*x-plane1.getvecteg().at(3))/(plane1.getvecteg().at(2));
                            y=0;
                            cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                        
                        }else{
                            cout<<"No se puede calcular"<<endl;
                        }
                    }
                    
                }else if(op==2){
                    cout<<"Entendido\n";    
                }else{
                    cout<<"Opción no válida\n"<<endl;
                }
            }else{
                cout<<"Los tres forman un haz de planos (1 recta en común)"<<endl;
                cout<<"¿Quieres calcular la recta de intersección?\n -Sí (1)\n -No (2)\n";
                cin>>op;
                if(op==1){
                    double v1,v2,v3,x,y,z;
                    v1=plane1.getvecteg().at(1)*plane2.getvecteg().at(2)-plane1.getvecteg().at(2)*plane2.getvecteg().at(1);
                    v2=plane1.getvecteg().at(2)*plane2.getvecteg().at(0)-plane1.getvecteg().at(0)*plane2.getvecteg().at(2);
                    v3=plane1.getvecteg().at(0)*plane2.getvecteg().at(1)-plane1.getvecteg().at(1)*plane2.getvecteg().at(0);
                    if(abs(plane1.getvecteg().at(0))>1e-5 && abs(plane2.getvecteg().at(1)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(1))>1e-5){
                        y=(plane2.getvecteg().at(0)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(0))/(plane2.getvecteg().at(1)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(1));
                        x=(-plane1.getvecteg().at(1)*y-plane1.getvecteg().at(3))/(plane1.getvecteg().at(0));
                        z=0;
                        cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";

                    }else if(abs(plane1.getvecteg().at(1))>1e-5 && abs(plane2.getvecteg().at(0)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(0))>1e-5){
                        x=(plane2.getvecteg().at(1)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(1))/(plane2.getvecteg().at(0)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(0));
                        y=(-plane1.getvecteg().at(0)*x-plane1.getvecteg().at(3))/(plane1.getvecteg().at(1));
                        z=0;
                        cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                    
                    }else if(abs(plane1.getvecteg().at(2))>1e-5 && abs(plane2.getvecteg().at(1)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(1))>1e-5){
                        y=(plane2.getvecteg().at(2)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(2))/(plane2.getvecteg().at(1)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(1));
                        z=(-plane1.getvecteg().at(1)*y-plane1.getvecteg().at(3))/(plane1.getvecteg().at(2));
                        x=0;
                        cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                    
                    }else if(abs(plane1.getvecteg().at(1))>1e-5 && abs(plane2.getvecteg().at(2)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(2))>1e-5){
                        z=(plane2.getvecteg().at(1)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(1))/(plane2.getvecteg().at(2)*plane1.getvecteg().at(1)-plane2.getvecteg().at(1)*plane1.getvecteg().at(2));
                        y=(-plane1.getvecteg().at(2)*z-plane1.getvecteg().at(3))/(plane1.getvecteg().at(1));
                        x=0;
                        cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                    
                    }else if(abs(plane1.getvecteg().at(0))>1e-5 && abs(plane2.getvecteg().at(2)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(2))>1e-5){
                        z=(plane2.getvecteg().at(0)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(0))/(plane2.getvecteg().at(2)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(2));
                        x=(-plane1.getvecteg().at(2)*z-plane1.getvecteg().at(3))/(plane1.getvecteg().at(0));
                        y=0;
                        cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                    
                    }else if(abs(plane1.getvecteg().at(2))>1e-5 && abs(plane2.getvecteg().at(0)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(0))>1e-5){
                        x=(plane2.getvecteg().at(2)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(2))/(plane2.getvecteg().at(0)*plane1.getvecteg().at(2)-plane2.getvecteg().at(2)*plane1.getvecteg().at(0));
                        z=(-plane1.getvecteg().at(0)*x-plane1.getvecteg().at(3))/(plane1.getvecteg().at(2));
                        y=0;
                        cout<<"La recta de intersección entre los tres planos es (x,y,z)=("<<x<<", "<<y<<", "<<z<<")+λ("<<v1<<", "<<v2<<", "<<v3<<")\n";
                    
                    }else{
                        cout<<"No se puede calcular"<<endl;
                    }

                }else if(op==2){
                    cout<<"Entendido\n";    
                }else{
                    cout<<"Opción no válida\n"<<endl;
                }
            }
        }else if(rankA==2 && rankB==3){
            if((a12==b12&&b12==c12)||(a13==b13&&b13==c13)||(a23==b23&&b23==c23)){
                cout<<"Hay 2 planos paralelos y 1 secante"<<endl;
            }else{
                cout<<"Los planos se cortan 2 a 2"<<endl;
            }
        }else if(rankA==3 && rankB==3){
            cout<<"Los 3 planos se cortan en 1 punto"<<endl;
            cout<<"¿Quieres calcular el punto de intersección?\n -Sí (1)\n -No (2)\n";
            cin>>op;
            if(op==1){
                double v1,v2,v3,xp,yp,zp,x,y,z,lmd;
                //Recta de intersección entre 2 planos
                v1=plane1.getvecteg().at(1)*plane2.getvecteg().at(2)-plane1.getvecteg().at(2)*plane2.getvecteg().at(1);
                v2=plane1.getvecteg().at(2)*plane2.getvecteg().at(0)-plane1.getvecteg().at(0)*plane2.getvecteg().at(2);
                v3=plane1.getvecteg().at(0)*plane2.getvecteg().at(1)-plane1.getvecteg().at(1)*plane2.getvecteg().at(0);
                yp=(plane2.getvecteg().at(0)*plane1.getvecteg().at(3)-plane2.getvecteg().at(3)*plane1.getvecteg().at(0))/(plane2.getvecteg().at(1)*plane1.getvecteg().at(0)-plane2.getvecteg().at(0)*plane1.getvecteg().at(1));
                xp=(-plane1.getvecteg().at(1)*yp-plane1.getvecteg().at(3))/(plane1.getvecteg().at(0));
                zp=0;

                //Corte de la recta de intesección con el plano 3
                lmd=(-plane3.getvecteg().at(0)*xp-plane3.getvecteg().at(1)*yp-plane3.getvecteg().at(2)*zp-plane3.getvecteg().at(3))/(plane3.getvecteg().at(0)*v1+plane3.getvecteg().at(1)*v2+plane3.getvecteg().at(2)*v3);
                x=v1*lmd+xp;
                y=v2*lmd+yp;
                z=v3*lmd+zp;
                cout<<"El punto de intersección entre los 3 planos es I("<<x<<", "<<y<<", "<<z<<")\n";
            }else if(op==2){
                cout<<"Entendido\n";    
            }else{
                cout<<"Opción no válida\n"<<endl;
            }
        }
        q,w=1;//reseteo variables estéticas
        main();

    }else if(op==0){
        cout<<"Saliendo del programa...\n";
        return 0;
    }else{
        cout<<"Opción no válida, por favor intenta de nuevo.\n";
        main();
    }
}
