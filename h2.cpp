
#include <iostream>
#include<windows.h>
#define M_PI 3.14145
#define mutationRate 0.01
# define crossRate 0.8
# define nrOfDimensions 30
#define putereAmplificare 1
# define Untouchable 4
# define CapatMicInterval -5.12
#define CapatMareInterval  5.12
using namespace std;
bool individ[10000][8000],nextIndivid[101][8000];
bool copieIndivid[8000],variabilaControlSch;
double qp[10000],eval[100000];
double valoriZecimale[30],precizie=1.0/32;
int lungimeCoord,X,negativ,currentPopSize;
void generationZero();
void mainFunction(double(*fct)());
double Rastrigin( );
double Schweffel();
double Michalewicz();
double DeJong();
void converseBaza10(int k,double a, double b);
void precalcul(double a, double b);
void mutatie();
void creareProbabilitati(double(*fct)());
void cross();
void select();
void copyF(int indexCopie, int k);
int main()
{
    mainFunction(Rastrigin);
}
void generationZero()
{
    int i = 0,j;
    srand(time(0));
    for (i = 0; i < 100; i++)
    {
       for (j = 0; j < lungimeCoord*nrOfDimensions; j++)
        {
            int aux = rand();
            individ[i][j] = aux % 2 ? 1 : 0;
        }
    }
    currentPopSize = 100;
}
void mainFunction(double(*fct)())
{
    precalcul(CapatMicInterval,CapatMareInterval);
    int i = 0,j,k,ii;
    for (i = 0; i <= 1499; i++)
    {
        if (i == 0)
            generationZero();
        currentPopSize = 100;
        for (ii = 0; ii < 100; ii++)
        {
            converseBaza10(ii, CapatMicInterval, CapatMareInterval);
            eval[ii] = 1 / (fct() + 0.0001);
        }
    //    cout << "ok";
        for (ii = 0; ii < 99; ii++)
        {
            for (j = ii + 1; j < 100; j++)
                if (eval[ii] < eval[j])
                {
                    for (k = 0; k < lungimeCoord * nrOfDimensions; k++)
                        copieIndivid[k] = individ[ii][k];
                    for (k = 0; k < lungimeCoord * nrOfDimensions; k++)individ[ii][k] = individ[j][k];
                    for (k = 0; k < lungimeCoord * nrOfDimensions; k++)individ[j][k] = copieIndivid[k];
                    swap(eval[ii], eval[j]);
                }
        }
        mutatie();
       
        cross();
     
        creareProbabilitati(fct);

        select();

        double minim = 10000000;
        for (j = 0; j < 100; j++)
        {
            converseBaza10(j, -5.12, 5.12);
            
            eval[j] = fct();
            if (minim > eval[j])
                minim = eval[j];
        }
        cout <<"iteratia "<<i<<": "<<" "<<"minim: " << minim << "\n";
        cout << '\n';
        cout << '\n';
    }
    cout <<"nr de selectii al primelor 1: "<<X<<'\n';
    cout << "negativ: " << negativ;
}
void precalcul(double a,double b)
{
    double lgInterval; 
    int nrIntervale ,logaritm=0;
    lgInterval = b - a;
    nrIntervale = pow(10, 5) * lgInterval;
    while (nrIntervale)
    {
        nrIntervale /= 2;
        logaritm++;
    }
    lungimeCoord= logaritm;
}
double Rastrigin( )
{
    int i;
    double result = 10 * nrOfDimensions;
    for (i = 0; i < nrOfDimensions; i++)
    {
        result += valoriZecimale[i] * valoriZecimale[i];
        result -= 10 * cos(2 * M_PI * valoriZecimale[i]);
    }
    return result;

}
double Schweffel()
{
    int i;
    double result = 418.9829 * nrOfDimensions;
    for (i = 0; i < nrOfDimensions; i++)
    {
        result -= valoriZecimale[i] * sin(sqrt(abs(valoriZecimale[i])));
    }
    if (result < 12000) variabilaControlSch = 1;
   // cout << result<<"  "<<variabilaControlSch<<'\n';
    return result;
}
double Michalewicz()
{
    int i;
    double result = 0;
    for (i = 0; i < nrOfDimensions; i++)
    {
        result -=sin(valoriZecimale[i])*pow(sin(i*valoriZecimale[i]*valoriZecimale[i]/M_PI),20);
    }
    return result;
}
double DeJong()
{
    int i;
    double result = 0;
    for (i = 0; i < nrOfDimensions; i++)
    {
        result += valoriZecimale[i]*valoriZecimale[i];
    }
    return result;
}
void converseBaza10(int k,double a,double b)
{
    int i,j;
    double aux,copie_precizie=precizie;
   // cout << lungimeCoord << '\n';
    for (i = 0; i < nrOfDimensions; i ++)
    {
        aux = 0; copie_precizie = precizie;
       
        for (j =(i+1)*lungimeCoord - 1; j >= i*lungimeCoord; j--)
        {
            aux += copie_precizie * individ[k][j];
            copie_precizie *= 2;
        }
     //   cout << aux << '\n';
        valoriZecimale[i] = a + (b - a) * aux / (copie_precizie - 1);
    }
 /* for (i = 0; i < nrOfDimensions; i++)
        cout << "dimenisune " << i << ": " << valoriZecimale[i] << '\n';*/
}
void mutatie()
{
    int  i,j,cnt=0,ij;
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < lungimeCoord * nrOfDimensions; j++)
        {
            int aux = rand();
            if (aux % 100 < 100 * mutationRate) {
                currentPopSize++;
                for (ij = 0; ij < j; ij++)individ[currentPopSize][ij] = individ[i][ij];
                individ[currentPopSize][j] = 1 - individ[i][j];
                for (ij = j+1; ij < lungimeCoord * nrOfDimensions; ij++)individ[currentPopSize][ij] = individ[i][ij];
            }
        }
    }
    
}
void cross()
{
    int i, j,aux1,aux2,k,ij;
    for (i=0;i<99;i++)
    {
        aux1 = rand() % 100;
        if (aux1 < 100 * crossRate)
        {
            j = i+1;
            while (j<99)
            {
               
                aux2 = rand() % 100;
                if (aux2 < 100 * crossRate)break;
                j++;
            }
            if (j == 100)j = 99;
       //     for (ij = 0; ij < 2; ij++) {
              int numberRandom = rand() % (lungimeCoord * nrOfDimensions);
              currentPopSize++;
              for (ij = 0; ij < numberRandom; ij++)individ[currentPopSize][ij] = individ[i][ij];
              for(ij=numberRandom;ij< lungimeCoord * nrOfDimensions;ij++)individ[currentPopSize][ij] = individ[j][ij];
           // }
            i = j;
        }
    }
}
void creareProbabilitati(double(fct)())
{
    int i,j,k,ij;
    double sum = 0;
  
    for (i = 0; i < currentPopSize; i++)
    {
        converseBaza10(i, -5.12, 5.12);
        //eval[i] =pow((40.45*nrOfDimensions- Rastrigin()),putereAmplificare);
        if(fct==Michalewicz)
        eval[i] = pow(1 / (fct()+30),putereAmplificare);
        else
            if(fct!=Schweffel)
            eval[i] = pow(1 / (fct() + 0.0001), putereAmplificare);
            else
                if(variabilaControlSch==0)
                  eval[i] = pow(1 / (abs(fct() -11999)), putereAmplificare);
                else
                    eval[i] = pow(1 / (fct()+0.0001), putereAmplificare);
        if (eval[i] < 0)negativ++;
        sum += eval[i];
    }
    for (i = 0; i < currentPopSize-1; i++)
    {
       for(j=i+1;j<currentPopSize;j++)
           if (eval[i] < eval[j])
           {

               for (k = 0; k < lungimeCoord * nrOfDimensions; k++)
                   copieIndivid[k] = individ[i][k];
               for (k = 0; k < lungimeCoord * nrOfDimensions; k++)individ[i][k] = individ[j][k];
               for (k = 0; k < lungimeCoord * nrOfDimensions; k++)individ[j][k] = copieIndivid[k];
               swap(eval[i], eval[j]);
           }
    }
   // cout << "Valoare bf wheel: "<<eval[0] << '\n';
    qp[0] = 0;
    for (i = 1; i < currentPopSize; i++)
        qp[i] = qp[i - 1] + eval[i-1] / sum;
    
    qp[currentPopSize] = 1;
    /*for (i = 0; i < 100; i++)
        cout << (qp[i+1]-qp[i]) << '\n';*/

}
void select()
{
    int i,indexCopie=0,j,indiceProb=109;
    double aux;
    Sleep(1);
    srand(time(0));
    for (i = 0; i < Untouchable; i++)
    {
        copyF(indexCopie,i);
        indexCopie++;
    }
    for (i = Untouchable; i < 100; i++)
    {
        aux = rand()*1.0/RAND_MAX;
        for(j=0;j<currentPopSize;j++)
            if (qp[j] <= aux && aux <= qp[j + 1])
            {
          // cout << "Selectat: " << j << '\n';
                if (j < 1)X++;
                if (j < indiceProb)indiceProb = j;
                copyF(indexCopie, j);
                indexCopie++;
                break;
            }
    }
    cout << "Indice ales: " << indiceProb << '\n';
    cout << "eval functie: " << eval[indiceProb] << '\n';
    cout << "varcontSchw: " << variabilaControlSch<<'\n';
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < lungimeCoord * nrOfDimensions; j++)
            individ[i][j]=nextIndivid[i][j];
    }
}
void copyF(int indexCopie, int k)
{
    int i;
    for (i = 0; i < lungimeCoord * nrOfDimensions; i++)
        nextIndivid[indexCopie][i] = individ[k][i];
}