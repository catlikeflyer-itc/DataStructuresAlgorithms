/**
 * @file numSum.cpp
 * @authors Emiliano Cabrera A01025453 & Do Hyun Nam A01025376
 * @brief A program that showcases different functions to add up a secuence of numbers starting from 0
 * @version 0.1
 * @date 2021-08-24
 */
#include<iostream>

using namespace std;

/* Call the function starting from the last value and recurses until 0 is reached */
int recursiveSum(int n) {
  /**
   * @brief Time complexity
   * Runtime of O(n), the first time it calls the function 
   * starts with n which throws a O(1) always, then when the
   * function gets recalled n-1 times, resulting in O(n-1).
   * If we add both of them it results in O(n-1+1) = O(n)
   * 
   */
  if (n >= 1) {
    return n + recursiveSum(n - 1);
  }

  return 0;
}

/* Uses mathematical method to find the sum of the "n"th sequence*/
int mathSum(int n) {
  /**
   * @brief Time complexity
   * Runtime of O(1) as it just need to use the equation
   * once to obtain the total sum of a sequence starting 
   * in 1. Time is constant.
   * 
   */
  return (n * (n + 1)) / 2;
}

/* A while loop until the "n"th value reaches 0*/
int iterativeSum(int n) {
  /**
   * @brief Time complexity
   * Runtime of O(n) as it consists of a linear time loop
   * running n times to add the value to the accumulator
   * 
   */
  int res = 0; // Stores the total value by adding each n step, accumulator

  while (n >= 1) {
    res += n;
    n -= 1;
  }

  return res;
}

int main(int argc, const char * argv[]) {
  int userChoice = * argv[2]; // Gets user selection as a single character from the third argument passed on excecution
  int userInt = atoi(argv[1]); // Converts integer given by user to readable int variable

  if (userInt <= 0) // Checks precondition established: if n's less than a positive integer program exits
  {
    cout << "Utilice un entero positivo" << endl;
    return 1;

  } else {

    switch (tolower(userChoice)) // Statement to check the method the user selected
    {
    case 'r':
      cout << "Recursivo: " << recursiveSum(userInt) << endl;
      break;

    case 'd':
      std::cout << "Directo " << mathSum(userInt) << endl;
      break;

    case 'i':
      std::cout << "Iterativo " << iterativeSum(userInt) << endl;
      break;

    default:
      cout << "Metodo no reconocido. Intente de nuevo" << endl;
      return 1;
    }
  }

  return 0; 
}