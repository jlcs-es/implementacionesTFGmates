/**
 * Algoritmos de
 * A course in computational algebraic number theory
 * Henri Cohen
 */

#include <iostream>
#include <cmath>
#include <random>


long isEven(long x) {
    return ( x%2==0 ? 1 : 0 );
}

long modularExponentiation(long base, long exp, long mod) {
    // base ^ exp (mod)
    long x = 1;
    base %= mod;        // base := base mod modulus
    while (exp != 0)
    {
        if (exp % 2 == 1)
            x = (x * base) % mod;
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return x;
}

long kroneker_symbol(long a, long b) {
    // ( a / b )

    long v, k, r;
    short tab2[] = {0, 1, 0, -1, 0, -1, 0, 1};

    // 1. Test b equal to 0
    if(b==0)
        if( abs(a) == 1 )
            return 1;
        else
            return 0;

    // 2. Remove 2's from b
    if( isEven(a) && isEven(b) )
        return 0;
    v = 0;
    while(isEven(b)){
        v += 1;
        b /= 2;
    }
    if(isEven(v))
        k = 1;
    else
        k = tab2[a&7]; // tab2[a%8]   // k = (-1) ^[(a^2 -l)/8]

    b = abs(b);
    if(a<0)
        k = -k;

    // 3. Finished?
    while( a != 0) {
        v = 0;
        while (isEven(a)) {
            v += 1;
            a /= 2;
        }
        if (!isEven(v))
            k = tab2[b & 7] * k;  // k = (-1) ^[(b^2 -l)/8] k.

        // 4. Apply reciprocity
        if (a & b & 2) k = -k; // k = (-1) ^ [(a-l)(b-l)/4]*k
        r = abs(a);
        a = b % r;
        b = r;
        // goto 3
    }
    // ... 3. Finished?
    if (b == 1)
        return k;
    else
        return 0;
}

long kroneker_binary_symbol(long a, long b) {
    // ( a / b )

    long v, k, r;
    short tab2[] = {0, 1, 0, -1, 0, -1, 0, 1};

    // 1. Test b equal to 0
    if(b==0)
        if( abs(a) == 1 )
            return 1;
        else
            return 0;

    // 2. Remove 2's from b
    if( isEven(a) && isEven(b) )
        return 0;
    v = 0;
    while(isEven(b)){
        v += 1;
        b /= 2;
    }
    if(isEven(v))
        k = 1;
    else
        k = tab2[a&7]; // tab2[a%8]   // k = (-1) ^[(a^2 -l)/8]

    b = abs(b);
    if(a<0)
        k = -k;

    // 3. Reduce size once
    a %= b;


    // 4. Finished?
    while( a != 0) {
        // 5. Remove powers of 2
        v = 0;
        while (isEven(a)) {
            v += 1;
            a /= 2;
        }
        if (!isEven(v))
            k = tab2[b & 7] * k;  // k = (-1) ^[(b^2 -l)/8] k.

        // 6. Subtract and apply reciprocity
        r = b - a;
        if(r>0) {
            if (a & b & 2) k = -k; // k = (-1) ^ [(a-l)(b-l)/4]*k
            b = a;
            a = r;
        } else {
            a = -r;
        }
        // goto 4
    }
    // ... 4. Finished?
    if (b == 1)
        return k;
    else
        return 0;
}

// auxiliar function for shanks_square_root_mod_p
long smallestm(long b, long p) {
    long m = 1;
    while(modularExponentiation(b, 1<<m, p) != 1) {
        m++;
    }
    return m;
}

long shanks_square_root_mod_p(long &x, long a, long p){
    // returns:
    // * 0 : x does not exist
    // * 1 : x exists so x^2 = a mod p

    long q, e, n, z, y, r, b, m, t;

    // 0. p-1 = q * 2^e, p odd, q odd
    if( isEven(p) ) return 0;
    q = p-1; e = 0;
    while(isEven(q)){
        e += 1;
        q /= 2;
    }

    // 1. Find generator

    // random integer generator
    std::random_device rd;                             // only used once to initialise (seed) engine
    std::mt19937 rng(rd());                            // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<long> unif_rand(1,p); // guaranteed unbiased

    do {
        n = unif_rand(rng);
    }while(kroneker_symbol(n, p) != -1);

    z = modularExponentiation(n, q, p);

    // 2. Initialize
    y = z;
    r = e;
    x = modularExponentiation(a, (q-1)/2, p); //
    // b = x*x; b%=p; b*=a; b%=p;
    b = a*x*x; b%=p;
    x = a*x; x%=p;

    // 3. Find exponent
    while(b%p != 1){
        m = smallestm(b, p);
        if(m == r) return 0;    // a is not a quadratic residue mod p

        // 4. Reduce exponent
        t = modularExponentiation(y, 1<<(r-m-1), p);
        y = t*t % p;
        r = m % p;
        x = x*t % p;
        b = b*y % p;
    }
    // ... 3. Find exponent
    return 1;

}

int main() {

    // Kronecker  ( k / n)
    // ( 6 / 5 ) = 1
    std::cout << "( 6 / 5 ) = " << kroneker_symbol(6, 5) << std::endl;
    // ( 6 / 6 ) = 0
    std::cout << "( 6 / 6 ) = " << kroneker_symbol(6, 6) << std::endl;
    // ( 6 / 7 ) = -1
    std::cout << "( 6 / 7 ) = " << kroneker_symbol(6, 7) << std::endl;
    // ( 29 / 26 ) = -1
    std::cout << "( 29 / 26 ) = " << kroneker_symbol(29, 26) << std::endl;
    // ( 29 / 27 ) = -1
    std::cout << "( 29 / 27 ) = " << kroneker_symbol(29, 27) << std::endl;
    // ( 29 / 28 ) = 1
    std::cout << "( 29 / 28 ) = " << kroneker_symbol(29, 28) << std::endl;

    std::cout << std::endl;

    // Kronecker binary ( k / n)
    // ( 6 / 5 ) = 1
    std::cout << "( 6 / 5 ) = " << kroneker_binary_symbol(6, 5) << std::endl;
    // ( 6 / 6 ) = 0
    std::cout << "( 6 / 6 ) = " << kroneker_binary_symbol(6, 6) << std::endl;
    // ( 6 / 7 ) = -1
    std::cout << "( 6 / 7 ) = " << kroneker_binary_symbol(6, 7) << std::endl;
    // ( 29 / 26 ) = -1
    std::cout << "( 29 / 26 ) = " << kroneker_binary_symbol(29, 26) << std::endl;
    // ( 29 / 27 ) = -1
    std::cout << "( 29 / 27 ) = " << kroneker_binary_symbol(29, 27) << std::endl;
    // ( 29 / 28 ) = 1
    std::cout << "( 29 / 28 ) = " << kroneker_binary_symbol(29, 28) << std::endl;

    std::cout << std::endl;

    // Shanks square root mod p
    long x;
    if(shanks_square_root_mod_p(x, 2, 113))
        std::cout << "sqrt(2) mod 113 = " << x << std::endl;
    else
        std::cout << "sqrt(2) mod 113 doesn't exist." << std::endl;

    if(shanks_square_root_mod_p(x, 2, 7))
        std::cout << "sqrt(2) mod 7 = " << x << std::endl;
    else
        std::cout << "sqrt(2) mod 7 doesn't exist." << std::endl;

    if(shanks_square_root_mod_p(x, 2, 5))
        std::cout << "sqrt(2) mod 5 = " << x << std::endl;
    else
        std::cout << "sqrt(2) mod 5 doesn't exist." << std::endl;

    return 0;
}
