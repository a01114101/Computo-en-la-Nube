/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <omp.h>
#include <iomanip>

#define N 1000
#define chunk 100
#define mostrar 15

void imprimeArreglo(float *d, const char* nombre);

int main()
{
    std::cout << "==========================================\n";
    std::cout << "     PROCESAMIENTO PARALELO CON OPENMP    \n";
    std::cout << "==========================================\n";
    
    #ifdef _OPENMP
        std::cout << "[INFO] OpenMP disponible. Hilos maximos: " << omp_get_max_threads() << "\n";
    #else
        std::cout << "[ALERTA] OpenMP no detectado. Se ejecutara secuencialmente.\n";
    #endif
    std::cout << "------------------------------------------\n\n";

    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 10.0f;
        b[i] = (i + 3) * 3.7f;
    }
    
    int pedazos = chunk;

    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    std::cout << "Muestra de resultados (primeros " << mostrar << " elementos):" << std::endl;
    
    imprimeArreglo(a, "Arreglo a");
    imprimeArreglo(b, "Arreglo b");
    imprimeArreglo(c, "Arreglo c (Suma)");

    return 0;
}

void imprimeArreglo(float *d, const char* nombre)
{
    std::cout << ">> " << nombre << ":" << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    
    for (int x = 1; x-1 < mostrar; x++)
    {
        std::cout << "[" << std::setw(1) << x << "]: " << std::setw(2) << d[x] << "    ";
        
        if ((x) % 5 == 0) 
            std::cout << std::endl;
    }
    std::cout << std::endl;
}