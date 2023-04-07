#include <iostream>
using namespace std;

class ArithmeticProgression
{
    int a, d, n;
    public:
        void set(int a1, int d1, int n1);
        int getA();
        int getD();
        int getN();
        int get_sum();
};

double input_d();

int input_n();

void read_progressions(ArithmeticProgression* progressions, int &num_progressions);

void print_progressions(ArithmeticProgression* progressions, int num_progressions);

void find_max_sum(ArithmeticProgression* progressions, int num_progressions);