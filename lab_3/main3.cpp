#include "lab3.h"

int main() {
    int n = 50;
    ArithmeticProgression *progressions = new ArithmeticProgression[n];

    int num_progressions;
    read_progressions(progressions, num_progressions);
    print_progressions(progressions, num_progressions);
    find_max_sum(progressions, num_progressions);
    delete[] progressions;

    return 0;
}