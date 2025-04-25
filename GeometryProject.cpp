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
Line createLine(int& numero){
    cout<<"Escribe el vector director de la recta "<<numero<<" (inserta x,y,z en orden con . o /):\n";
        vector<float> vect;
        for(int i=0;i<3;i++){
            string str;
            float x;
            cin>>str;
            x=leerFraccionComoFloat(str);
            vect.push_back(x);
        }
        cout<<"Escribe un punto de la recta "<<numero<<" (inserta x,y,z en orden con . o /):\n";
        vector<float> point;
        for(int i=0;i<3;i++){
            string str;
            float x;
            cin>>str;
            x=leerFraccionComoFloat(str);
            point.push_back(x);
        }
        numero+=1;
        Line line(vect,point);
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
Plane createPlane(int& numero){
    cout<<"Escribe la ecuación general del plano "<<numero<<" (inserta Ax+By+Cy+D=0 en orden con . o /):\n";
    vector<float> vecteg;
    for(int i=0;i<4;i++){
        string str;
        float x;
        cin>>str;
        x=leerFraccionComoFloat(str);
        vecteg.push_back(x);
    }
    numero+=1;
    Plane plane(vecteg);
    return plane;
}

int calcRan2_3x2(float mat[3][2]){
    double aux=0;
    aux=mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    if(aux==0){return 1;}else{aux=0;}

    aux=mat[0][0]*mat[2][1] - mat[0][1]*mat[2][0];
    if(aux==0){return 1;}else{aux=0;}
    
    aux=mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0];
    if(aux==0){return 1;}else{return 2;}
}
int calcRan2_3x3(float mat[3][3]){
    double aux=0;
    aux=mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}
    
    aux=mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0];
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][1]*mat[1][2]-mat[0][2]*mat[1][1];
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}
    
    aux=mat[1][1]*mat[2][2]-mat[1][2]*mat[2][1];
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][0]*mat[2][2]-mat[0][2]*mat[2][0];
    if(aux!=0){return 2;}else{return 1;}
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
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}
    
    aux=mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0];
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][1]*mat[1][2]-mat[0][2]*mat[1][1];
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}
    
    aux=mat[1][1]*mat[2][2]-mat[1][2]*mat[2][1];
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][0]*mat[2][2]-mat[0][2]*mat[2][0];
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][2]*mat[1][3]-mat[0][3]*mat[1][2];
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}
    
    aux=mat[1][2]*mat[2][3]-mat[1][3]*mat[2][2];
    if(aux!=0){return 2;}else if(abs(aux)<1e-5){aux=0;}

    aux=mat[0][1]*mat[2][3]-mat[0][3]*mat[2][1];
    if(aux!=0){return 2;}else{return 1;}


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

    cout<<"Qué quieres hacer?\n -Posición relativa entre 2 rectas (1)\n -Posición relativa entre recta y plano (2)\n -Posición relativa entre 2 planos (3)\n -Posición relativa entre 3 planos (4)\n -Salir (0)\n";
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
        }else if(rankA==2 && rankB==3){
            cout<<"Las rectas se cruzan\n";
        }

    }else if(op==2){ //entre recta y plano
        Line line=createLine(q);
        Plane plane=createPlane(w);
        double product = line.getVectu().at(0) * plane.getvecteg().at(0) + line.getVectu().at(1) * plane.getvecteg().at(1) + line.getVectu().at(2) * plane.getvecteg().at(2);
        if(abs(product) > 1e-5){ //product != 0
            cout<<"Son secantes\n";
        }else if(abs(product) < 1e-5){ //product == 0
            if(product - plane.getvecteg().at(3)<1e-5){
                cout<<"Son coincidentes\n";
            }else{
                cout<<"Son paralelos\n";
            }
        }


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
            cout<<"Son secantes";
        }else{
            cout<<"Se ha producido un error";
        }
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

        double a12= plane1.getvecteg().at(0)/plane2.getvecteg().at(0);
        double b12= plane1.getvecteg().at(1)/plane2.getvecteg().at(1);
        double c12= plane1.getvecteg().at(2)/plane2.getvecteg().at(2);
        double d12= plane1.getvecteg().at(3)/plane2.getvecteg().at(3);

        double a13= plane1.getvecteg().at(0)/plane3.getvecteg().at(0);
        double b13= plane1.getvecteg().at(1)/plane3.getvecteg().at(1);
        double c13= plane1.getvecteg().at(2)/plane3.getvecteg().at(2);
        double d13= plane1.getvecteg().at(3)/plane3.getvecteg().at(3);

        double a23= plane2.getvecteg().at(0)/plane3.getvecteg().at(0);
        double b23= plane2.getvecteg().at(1)/plane3.getvecteg().at(1);
        double c23= plane2.getvecteg().at(2)/plane3.getvecteg().at(2);
        double d23= plane2.getvecteg().at(3)/plane3.getvecteg().at(3);

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
            }else{
                cout<<"Los tres forman un haz de planos (1 recta en común)"<<endl;
            }
        }else if(rankA==2 && rankB==3){
            if((a12==b12&&b12==c12)||(a13==b13&&b13==c13)||(a23==b23&&b23==c23)){
                cout<<"Hay 2 planos paralelos y 1 secante"<<endl;
            }else{
                cout<<"Los planos se cortan 2 a 2"<<endl;
            }
        }else if(rankA==3 && rankB==3){
            cout<<"Los 3 planos se cortan en 1 punto"<<endl;
        }


    }else if(op==0){
        cout<<"Saliendo del programa...\n";
        return 0;
    }else{
        cout<<"Opción no válida, por favor intenta de nuevo.\n";
        main();
    }
}
