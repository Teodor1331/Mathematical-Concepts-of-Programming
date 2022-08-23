// Teodor Dishanski, XI B, Number 23
// Technological School "Electronic Systems"

#include <iostream>
#include <vector>


void printSinglePermutation(int arr[], int n) {

    /* This function will print every possible
    different permutation of the array elements. */

    for (int i = 0; i < n; i++) {
        if (i != n - 1) { std::cout << arr[i] << " "; }
        else { std::cout << arr[i] << std::endl; }
    }
}

void swap(int &num1, int &num2) {
    int temporary = num1;
    num1 = num2;
    num2 = temporary;
}

void printPermutations(int arr[], int n, int start) {

    /* The function for the permutations will be recursive. 
    The "start" parameter will be needed to make a shift from
    the beginning of the array from left to right every time
    we want to make a new permutation. But, for that purpose,
    we will need and swapping of every two elements.
    
    On every shift we will call the function recursively and,
    after we have printed all the permutations with the first
    element fixed, we will print the next set of permutations
    with the next element fixed. If we continue this way, we
    will print all permuations with every element fixed as
    first, one from the other elements fixed as second and so
    one till the moment the function prints all of them. */

    if (start == n) { 
        printSinglePermutation(arr, n);
        return;
    }
    
    for (int i = start; i < n; i++) {
        swap(arr[i], arr[start]);
        printPermutations(arr, n, start + 1);
        swap(arr[i], arr[start]);
    }
}

bool sortedPermutationAscending(int arr[], int n) {
    if (n == 1 || n == 0) { return true; }
    if (arr[n - 2] > arr[n - 1]) { return false; }
    return sortedPermutationAscending(arr, n - 1);
}

bool sortedPermutationDescending(int arr[], int n) {
    if (n == 1 || n == 0) { return true; }
    if (arr[n - 2] < arr[n - 1]) { return false; }
    return sortedPermutationDescending(arr, n - 1);
}

void printSortedPermutations(int arr[], int n, int start) {

    /* The only difference here will be to print the two
    permutations, which are sorted (in ascending or descending
    order). This means we could use two more recursive functions
    to check if the permutation is sorted in one of the two ways. */

    if (start == n) {
        if (sortedPermutationAscending(arr, n) || sortedPermutationDescending(arr, n)) {
            printSinglePermutation(arr, n);
        }
        return;
    }

    for (int i = start; i < n; i++) {
        swap(arr[i], arr[start]);
        printSortedPermutations(arr, n, start + 1);
        swap(arr[i], arr[start]);
    }
}

void printSingleCombination(std::vector<int> combination) {

    /* This function will print every possible
    different combination of the array elements. */

    for (unsigned int i = 0; i < combination.size(); i++) {
        if (i != combination.size() - 1) { std::cout << combination[i] << " "; }
        else { std::cout << combination[i] << std::endl; }
    }
}

void printCombinations(int arr[], int n, int k, int start, std::vector<int> combination) {

    /* The function for the combinations will be recursive too.
    Analogically to the function for the permutations, we will
    have a "start" variable again. 
    
    There is a little difference, which we can use here - a
    vector for storing every combination. When we have found
    one of all possible combinations, we will print the values
    of this vector. 
    
    Every time we will increment our start variable to make a
    shift from left to right and after this we will make it from
    right to left by deleting the last element from the last
    printed combination. We know that this algorithm won't print
    the combinations, which may repeat, because the recursion
    won't "have in mind" the last fixed element, which has been
    on first position. This way we get just the combinations,
    which are unique. */

    if (k == 0) {
        printSingleCombination(combination);
        return;
    }


    for (int i = start; i <= n - k; i++) {
        combination.push_back(arr[i]);
        printCombinations(arr, n, k - 1, i + 1, combination);
        combination.pop_back();
    }
}

int main() {

    int option = 0;

    std::cout << "1. Calculate permutations." << std::endl;
    std::cout << "2. Calculate combinations." << std::endl;

    do {
        std::cout << "Enter your option: ";
        std::cin >> option;
    } while (option != 1 && option != 2);

    std::cout << std::endl;
    std::cout << std::endl;

    int size = 0;
            
    do {
        std::cout << "Enter the size of your array: ";
        std::cin >> size;
    } while (size < 1);

    int *arr = new int[size];
    std::cout << "Enter your array: ";

    for (int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }

    if (option == 1) {
        std::cout << std::endl;
        std::cout << "The permutations are: " << std::endl;
        printPermutations(arr, size, 0);

        std::cout << "The sorted permutations are: " << std::endl;
        printSortedPermutations(arr, size, 0);
    }
    else {
        int kElements = 0;

        do {
            std::cout << "Enter how many elements we choose: ";
            std::cin >> kElements;
        } while (kElements < 1 || kElements > size);

        std::vector<int> combination;

        std::cout << std::endl;
        std::cout << "The combinations are: " << std::endl;
        printCombinations(arr, size, kElements, 0, combination);
    }

    delete[] arr;
    return 0;
}
