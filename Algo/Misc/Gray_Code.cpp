/*
Gray codes have some useful applications, sometimes quite unexpected:

Gray code of n bits forms a Hamiltonian cycle on a hypercube, where each bit corresponds to one dimension.

Gray codes are used to minimize the errors in digital-to-analog signals conversion (for example, in sensors).

Gray code can be used to solve the Towers of Hanoi problem. Let n denote number of disks. Start with Gray code of length n which consists of all zeroes (G(0)) and move between consecutive Gray codes (from G(i) to G(i+1)). Let i-th bit of current Gray code represent n-th disk (the least significant bit corresponds to the smallest disk and the most significant bit to the biggest disk). Since exactly one bit changes on each step, we can treat changing i-th bit as moving i-th disk. Notice that there is exactly one move option for each disk (except the smallest one) on each step (except start and finish positions). There are always two move options for the smallest disk but there is a strategy which will always lead to answer: if n is odd then sequence of the smallest disk moves looks like f→t→r→f→t→r→... where f is the initial rod, t is the terminal rod and r is the remaining rod), and if n is even: f→r→t→f→r→t→....

Gray codes are also used in genetic algorithms theory.
*/
int g (int n) {
    return n ^ (n >> 1);
}

int rev_g (int g) {
  int n = 0;
  for (; g; g >>= 1)
    n ^= g;
  return n;
}
