#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <sys/time.h>

int L=7;


double drawRandomNumber () {
// returns a random number between 0 and 1

    double v1 = rand();
    double v2 = RAND_MAX+1;
    double v_out = v1 / v2;
    return v_out;
}


void setSpinToCold(int lattice[], int size) {
// sets all spins to -1
// params: lattice[]: array that contains the spins of each lattice point
//         size: length of the array (= L*L)

    for (int i = 0; i < size; i++) {
        lattice[i] = -1;
    }
}


int getSuperIndex( int i, int j, int L) {
// returns the SuperIndex for a 2D Coordinate.
// params: i: row-index,
//         j: col-index,
//         L: length of the lattice (i.e. range of i or j)

    return (i*L)+j;
}


double computeSum( int array[], int n ) {
// helper function. Computes the sum over the elements of an array.
// params: array[]: target array,
//         n: length of array

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + array[i];
    }
    return sum;
}


double computeMagnetisation(int lattice[], int size) {
// computes the magnetisation M = 1/L^2 * sum_i,j s_i,j
// params: lattice[]: array which contains the spins of each lattice point,
//         size: length of the array (i.e. L*L when L is the length of the lattice)

    double n = (double) size;
    double sum = computeSum(lattice, n);
    double M = (1/n) * sum;
    return M;
}


void computeHamiltonian( int lattice[], int H[], int L ) {
// computes the Hamiltonian of each lattice point
// params: lattice[]: array which contains the spins of each lattice point,
//         H[]: array in which the H values are saved,
//         L: length of the lattice


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

//  conditions for border positions

//        top border:
        if(i < L){
            i_up = i+(L-1)*L;
        }
//        bottom border:
        if(L*(L-1)<= i && i < L*L) {
            i_down = i-(L-1)*L;
        }
//        left border:
        if(i%L == 0) {
            i_left =i+L-1;
        }
//        right border:
        if(i%L == (L-1)) {
            i_right = i-(L-1);
        }

        H[i] = - lattice[i] * ( lattice[i_up] + lattice[i_down] + lattice[i_left] + lattice[i_right] ) ;
    }

}


void computeDelta( int H[], int Delta_H[], int n ) {
// computes the energy difference delta H = H'(s_i,j) - H(s_i,j)
// params: H[]: array which contains the Hamiltonian of each lattice point,
//         Delta_H[]: array in which the delta H will be saved,
//         n: length of the array H[]

    for (int i = 0; i < n; i++) {
        Delta_H[i] = -2 * H[i];
    }
}


void updateLattice ( int latticeSpin[], int Delta_H[] , double effectiveBeta, int n ) {
// calculates if there should be a spin flip for any given lattice point by their delta H and updates the lattice
// accordingly.
// params: latticeSpin[]: array which contains the spin of every lattice point,
//         Delta_H[]: array that contains the delta H of every lattice point,
//         effectiveBeta: number which follows: J*(k_B*T)^(-1),
//         n: length of the array


    for (int i = 0; i < n; i++) {

        if(Delta_H[i] < 0) {
            Delta_H[i] = - Delta_H[i];
        }

        else {

            double rand = drawRandomNumber();
            double threshold = exp( - effectiveBeta * (double)Delta_H[i]);
            if( rand <= threshold) {
                Delta_H[i] = - Delta_H[i];
                printf("[%d: yes: thresh=%lf, rand=%lf]; \n", i, threshold, rand );
            }
            else{
                printf("[%d: no: thresh:%lf, rand=%lf]; \n",  i, threshold, rand);
                continue;
            }
        }
    }
}


void computeStep( int latticeSpin[], int H[], int Delta_H[], int L, int n, double effectiveBeta ) {
// wraps up the computeHamiltonian, computeDelta and the updateLattice functions into one function.
// params: computeHamiltonian, computeDelta, updateLattice: see docs of the functions
//         H[]: array that contains the Hamiltonian of each lattice point,
//         Delta_H[]: array that contains the delta H of each lattice point,
//         L: length of the lattice,
//         n: length of the array,
//         effectiveBeta: number which follows: J*(k_B*T)^(-1)

    computeHamiltonian(latticeSpin, H, L);
    computeDelta(H, Delta_H, n);
    updateLattice ( latticeSpin, Delta_H , effectiveBeta, n );
}


int main() {

    int L=4;
    int n = L*L;
    double effectiveBeta = 0.5 ;
    int latticeSpin[n];
    int H[n];
    int Delta_H[n];

    setSpinToCold(latticeSpin, n);
    computeMagnetisation(latticeSpin, n);
    computeStep(latticeSpin, H, Delta_H, L, n, effectiveBeta);


}
