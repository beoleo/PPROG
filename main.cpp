#include <cstdio>
#include <cstdlib>
#include <ctime>

double drawRandomNumber () {
    srand(time(NULL));

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

void initLatticeSpin( int lattice[], int size) {
    setSpinToCold(lattice, size);
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

int computeHamiltonian( int i, int L ) {

}

int get2dIndex( int SI, int L){
    SI = SI + 1;
    int col;
    int row;
    int j;
    j = SI % L;

}

int main() {
    int L=7;
    int n = L*L;
    int latticeSpin[n];
    initLatticeSpin(latticeSpin, n);
    computeMagnetisation(latticeSpin, n);
}
