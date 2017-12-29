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


int computeHamiltonian( int lattice[], int L ) {
    int i;
    int i_up;
    int i_down;
    int i_left;
    int i_right;
    int H[L*L];

    for (i=0; i < L*L; i++) {

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
        printf("%d, ", H[i]);
    }

}


int main() {
    int L=7;
    int n = L*L;
    int latticeSpin[n];
    initLatticeSpin(latticeSpin, n);
    computeMagnetisation(latticeSpin, n);
    computeHamiltonian(latticeSpin, L);
}
