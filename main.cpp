#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <math.h>

int L=7;


double drawRandomNumber () {
    srand(time(nullptr));

    double v1 = rand();
    double v2 = RAND_MAX+1;
    double v_out = v1 / v2;
    return v_out;
}


void setSpinToCold(int lattice[], int size) {

    for (int i = 0; i < size; i++) {
        lattice[i] = -1;
    }
}


int getSuperIndex( int i, int j, int L) {
    return (i*L)+j;
}


double computeSum( int array[], int n ) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + array[i];
    }
    return sum;
}

double computeMagnetisation(int lattice[], int size) {
    double n = (double) size;
    double sum = computeSum(lattice, n);
    double M = (1/n) * sum;
    return M;
}


void computeHamiltonian( int lattice[], int H[], int L ) {
    int n = L*L;
    int i;
    int i_up;
    int i_down;
    int i_left;
    int i_right;


    for (i=0; i < n; i++) {

        i_up = i-L;
        i_down = i+L;
        i_left = i-1;
        i_right = i+1;

//        conditions for border positions
        if(i < L){
            i_up = i+(L-1)*L;
        }
        if(L*(L-1)<= i && i < L*L) {
            i_down = i-(L-1)*L;
        }
        if(i%L == 0) {
            i_left =i+L-1;
        }
        if(i%L == (L-1)) {
            i_right = i-(L-1);
        }

        H[i] = - lattice[i] * ( lattice[i_up] + lattice[i_down] + lattice[i_left] + lattice[i_right] ) ;
    }

}


void computeDelta( int H[], int Delta_H[], int n ) {
    for (int i = 0; i < n; i++) {
        Delta_H[i] = -2 * H[i];
    }
}


void updateLattice ( int latticeSpin[], int Delta_H[] , double effectiveBeta, int n ) {

    double rand;

    for (int i = 0; i < n; i++) {



        if(Delta_H[i] < 0) {
            Delta_H[i] = - Delta_H[i];
        }

        else {
            double rand = drawRandomNumber();
            double threshold = exp( - effectiveBeta * (double)Delta_H[i]);
            if( rand <= threshold) {
                Delta_H[i] = - Delta_H[i];
                printf("[(%d)flip: thresh=%lf, rand=%lf]; ", i, threshold, rand );
            }
            else{
                printf("[%d: no thresh:%lf, rand=%lf];",  i, threshold, rand);
            }
        }
    }
}



int main() {

    int L=4;
    int n = L*L;
    double effectiveBeta = 1;
    int latticeSpin[n];
    int H[n];
    int Delta_H[n];

    setSpinToCold(latticeSpin, n);
    computeMagnetisation(latticeSpin, n);
    computeHamiltonian(latticeSpin, H, L);
    computeDelta(H, Delta_H, n);
    updateLattice ( latticeSpin, Delta_H , effectiveBeta, n );

}
