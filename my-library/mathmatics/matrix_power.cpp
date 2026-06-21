/*
 * Matrix struct with modular arithmetic and fast exponentiation.
 *
 * Supports N x N matrices over Z/pZ with O(N^3 log e) matrix power.
 * Demonstration: compute Fibonacci(n) via 2x2 matrix exponentiation.
 *
 * Time complexity : O(N^3 log e) for mat_pow, where N is matrix size
 *                   and e is the exponent.
 * Space complexity: O(N^2).
 *
 * Typical use cases:
 *   - Linear recurrences (Fibonacci, Tribonacci, etc.) for huge n (ABC-D/E).
 *   - Counting paths of length k in a graph (adjacency matrix ^ k).
 *   - DP transition speedup when the transition is a fixed linear map.
 *
 * Caveats:
 *   - All arithmetic is done modulo MOD; set MOD before use.
 *   - Matrix size is fixed at construction; multiplying differently-sized
 *     matrices triggers an assertion failure.
 *   - For N > ~500 and large exponents, the O(N^3 log e) cost may be too slow.
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll MOD = 1000000007;

// Square matrix of size n x n with elements in Z/MOD*Z.
struct Matrix {
    int n;
    vector<vector<ll>> a;

    // Construct an n x n zero matrix.
    Matrix(int n) : n(n), a(n, vector<ll>(n, 0)) {}

    // Return the n x n identity matrix.
    static Matrix identity(int n) {
        Matrix I(n);
        for (int i = 0; i < n; i++) I.a[i][i] = 1;
        return I;
    }

    // Matrix multiplication: C = A * B (mod MOD).
    Matrix operator*(const Matrix &B) const {
        assert(n == B.n);
        Matrix C(n);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (a[i][k] == 0) continue; // Small optimisation.
                for (int j = 0; j < n; j++) {
                    C.a[i][j] = (C.a[i][j] + a[i][k] * B.a[k][j]) % MOD;
                }
            }
        }
        return C;
    }
};

// Fast matrix exponentiation: compute M^e using repeated squaring.
Matrix mat_pow(Matrix M, ll e) {
    Matrix result = Matrix::identity(M.n);
    while (e > 0) {
        if (e & 1) result = result * M;
        M = M * M;
        e >>= 1;
    }
    return result;
}

// Compute the n-th Fibonacci number (0-indexed: F(0)=0, F(1)=1) mod MOD.
// Uses the identity:
//   | F(n+1) |   | 1 1 |^n   | 1 |
//   | F(n)   | = | 1 0 |   * | 0 |
ll fibonacci(ll n) {
    if (n <= 0) return 0;
    Matrix A(2);
    A.a[0][0] = 1; A.a[0][1] = 1;
    A.a[1][0] = 1; A.a[1][1] = 0;
    Matrix R = mat_pow(A, n);
    return R.a[1][0]; // F(n)
}

// --- Minimal usage example ---
int main() {
    // F(10) = 55
    cout << "F(10) = " << fibonacci(10) << endl;

    // F(100) mod 10^9+7 = 687995182
    cout << "F(100) = " << fibonacci(100) << endl;

    // Large: F(10^18) mod 10^9+7
    cout << "F(10^18) = " << fibonacci(1000000000000000000LL) << endl;

    return 0;
}
