#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> //for timing
#include <algorithm> //for random
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
//#include <stdlib.h> // for memory tracking



using namespace std;
const int arraySizes[] = { 10, 25, 50, 100, 250, 500, 750, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000}; //set up array sizes so increases in array size can be managed more precisely
long long durationInsert, durationShell, durationRadix ,durationQuick, durationBubble, durationStd, durationOver, durationInsertOpt, durationShellOpt, durationRadixOpt, durationRadixOptBit, durationQuickOpt, durationBubbleOpt, durationRadixOptBitVector, durationBubbleCombOpt; // Declare globally



// Bubble Sort function
void bubbleSortOptimised(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) { //runs for each element in the array
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false) { //Will stop sorting if detects no swaps
            break;
        }
    }
}
 
void bubbleSortCombOptimised(int arr[], int n) { //like bubble sort but compares elements more than a simgle space away
    int gap = n;
    bool swapped = true;
    while (gap > 1 || swapped == true) { //prevents sorting from ending early, will only stop when both the gap is reduced to 1 and no swaps have been made
        gap = std::max(1, (gap * 10) / 13); //prevents gap from ever being lower than 1
        swapped = false;
        for (int i = 0; i + gap < n; i++) { //acts like bubble sort in terms of mechanics but with the elements being "gap" apart
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}
    

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) { //runs for every element in the array
        
        for (int j = 0; j < n - i - 1; ++j) { //compares each element with the one infront, swapping if it is bigger
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                
            }
        }
        
    }
}
// Insert Sort function

void insertSort(int arr[], int n) { 
    for (int i = 1; i < n; i++) {//Starts from the second element in the array
        int key = arr[i];
        int j = i - 1;//The value being moved
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertSortOptimised(int arr[], int n) { //better for smaller array sizes
    for (int i = 1; i < n; i++) { //Starts from the second element in the array
        int key = arr[i]; //The value being moved
        int pos = std::upper_bound(arr, arr + i, key) - arr; //Comparing the key with the rest of the array to determine what position it should be in- uses binary search
        for (int j = i; j > pos; --j) { //shifts elements in the array to make space as the arrays cannot be resized
            arr[j] = arr[j - 1];
        }
        arr[pos] = key; //Sets the value of the element at pos to the value of the key.
    }
}
// Shell Sort Function
void shellSortOptimised(int arr[],const int n) {  //WIP
    int gap = 1; //set start point

    // Start with a gap sequence that gradually decreases
    while (gap < n / 3) { // Compute initial gap using Knuth's formula: gap = 3^k - 1
        gap = gap * 3 + 1;
    }


    for (; gap > 0; gap = (gap / 3) - 1) {  //reduce gap as sort runs
        for (int i = gap; i < n; i++) {
            int arrNum = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > arrNum) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = arrNum;
        }
    }
}

void shellSort(int arr[], const int n) {
    
    for (int gap = n / 2; gap > 0; gap = gap / 2) {
        
        
        for (int i = gap; i < n; i++) { // Perform insertion sort for elements seperated by the gap
            int j;

            
            for (j = i; j >= gap && arr[j - gap] > arr[i]; j -= gap) { // Compare elements separated by the gap and shift elements when necessary
                arr[j] = arr[j - gap];  // Move elements forward
            }

            
            arr[j] = arr[i]; // Place the current element in its correct position
        }
    }
}

//Radix Sort Function
 
void rubixSort(int arr[], const int n) {
    // Initialize sortNum with the first element in the array
    int sortNum = arr[0];

    // Find the maximum value in the array
    for (int i = 1; i < n; i++) {
        if (arr[i] > sortNum) {
            sortNum = arr[i]; // Updates sortNum to the largest value in the array
        }
    }

    // Declare a map to store the count of digits
    std::map<int, int> count;

   
    for (int j = 1; (sortNum / j) > 0; j) { 
       
        std::map<int, int>().swap(count);  // Clear the count map for each digit place

        
        for (int k = 0; k < n; k++) { // Count occurrences of each digit at the current place value
            count[(arr[k] / j) % 10]++;
        }

      
        for (int l = 1; l < 10; l++) {   // Update count to store cumulative frequency
            count[l] = count[l] + count[l - 1];
        }

        
        std::vector<int> output(n);// Use vector to create new output array

        
        for (int i = n - 1; i >= 0; i--) { // Place elements in the correct position based on the count array
            output[--count[(arr[i] / j) % 10]] = arr[i];
        }

       
        for (int i = 0; i < n; i++) {  // Copy sorted values back into the original array
            arr[i] = output[i];
        }
    }

}

// Radix Sort optimised Function
void radixSortOptimised(int arr[], const int n) {
    int sortNum = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > sortNum) {
            sortNum = std::max(sortNum, arr[i]); //sets sortNum to be the maximum value of the array
        }
    }
    int count[10];

    for (int j = 1; (sortNum / j) > 0; j *= 10) {
        memset(count, 0, sizeof(count)); //sets each byte of memory at count to 0
        for (int k = 0; k < n; k++) {
            count[(arr[k] / j) % 10]++;
        }

        for (int l = 1; l < 10; l++) {
            count[l] = count[l] + count[l - 1];
        }
        std::vector<int> output(n);  // Use vector to create new output array
        for (int i = n - 1; i >= 0; i--) {  // Place elements in the correct position based on the count array
            output[--count[(arr[i] / j) % 10]] = arr[i];
        }

        for (int i = 0; i < n; i++) { // Copy sorted values back into the original array
            arr[i] = output[i];
        }




    }

}
// Radix Sort Function
void radixSortOptimisedBit (int arr[], const int n) {
   
    int* bucket0 = new int[n]; //Set up pointers for bucket for 0 and 1 bit values
    int* bucket1 = new int[n];
   
    for (int bit = 0; bit < 32; bit++) { //for each bit in the integer values
        int  bucket0Pos = 0; //reset bucket position inside loop to prevent overwriting bucket which may cause heap corruption
        int bucket1Pos = 0;
        
        for (int i = 0; i < n; i++) { //for size of array
            int sortNum = arr[i];
            if (sortNum & (1 << bit)) { //does bitwise AND operation of the element i of the array and the specific bit being tested

               if(bucket1Pos < n) bucket1[bucket1Pos++] = sortNum; //if bit at element i == 1, the if statement should never be untrue 
            }
            else {
                if(bucket0Pos < n) bucket0[bucket0Pos++] = sortNum; //if bit at element == 0
            }
        }
        int arrPos = 0;  //merge both buckets back into array to sort
        for( int i = 0; i < bucket0Pos; i++ ) {
            arr[arrPos++] = bucket0[i];  
        }
        for (int i = 0; i < bucket1Pos; i++) {
            arr[arrPos++] = bucket1[i];
        }
        
    }
    delete[] bucket0; //Free up array to prevent overloading
    delete[] bucket1;
    
}
void radixSortOptimisedBitVector(int arr[], const int n) {

    int* bucket0 = new int[n]; //Set up pointers for bucket for 0 and 1 bit values
    int* bucket1 = new int[n];

    for (int bit = 0; bit < 32; bit++) { //for each bit in the integer values
        int  bucket0Pos = 0; //reset bucket position inside loop to prevent overwriting bucket which may cause heap corruption
        int bucket1Pos = 0;

        for (int i = 0; i < n; i++) { //for size of array
            int sortNum = arr[i];
            if (sortNum & (1 << bit)) { //does bitwise AND operation of the element i of the array and the specific bit being tested

                if (bucket1Pos < n) bucket1[bucket1Pos++] = sortNum; //if bit at element i == 1, the if statement should never be untrue 
            }
            else {
                if (bucket0Pos < n) bucket0[bucket0Pos++] = sortNum; //if bit at element == 0
            }
        }
        int arrPos = 0;  //merge both buckets back into array to sort
        for (int i = 0; i < bucket0Pos; i++) {
            arr[arrPos++] = bucket0[i];
        }
        for (int i = 0; i < bucket1Pos; i++) {
            arr[arrPos++] = bucket1[i];
        }

    }
    delete[] bucket0; //Free up array to prevent overloading
    delete[] bucket1;
}
// Selection Sort Function
void selectionSort(int arr[], int n) {
    //not used may add if needed for more diverse testing
}
//Quick Sort function

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high]; //pivot point
       
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {  //elements smaller than the pivot value are sorted to the left whilst larger elements are sorted to the right
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1); //iterate through the partitions starting with the one to the left and then the right
        quickSort(arr, pi + 1, high);
    }


}

void quickSortOptimised(int arr[], int low, int high) { //better for larger arrays
    if (low < high) {
        int pivot = arr[high]; //pivot point

        int i = low - 1;
        for (int j = low; j <= high - 1; j++) { //elements smaller than the pivot value are sorted to the left whilst larger elements are sorted to the right
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]); 
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        if (pi - 1 - low < high - pi - 1) { //reduces stack size by reducing amount of looping and only running one side of the partion at a time
            quickSortOptimised(arr, low, pi - 1); // Smaller side
            low = pi + 1;
        }
        else {
            quickSortOptimised(arr, pi + 1, high); // larger side
            high = pi - 1;
        }

    }


}


void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 10000; // Generates random numbers between 0 and 999 and allows for a varying size of array
    }
}



//function to copy arrays
void copyArray(const int source[], int dest[], int n) {
    for (int i = 0; i < n; ++i) {
        dest[i] = source[i];
    }
}

// function to print arrays
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void writeToCSV(const string& filename, const string& algorithm, long long array, long long duration, const string& hue) {
    ofstream file(filename, ios::app); // Open the file in write 

    if (file.is_open()) {
        file << algorithm << "," << array << "," << duration << "," << hue << "\n";
        file.close();
    }
    else {
        cerr << "Error opening file!" << endl;
    }
}

void sortingTests(){
    auto startOver = chrono::high_resolution_clock::now();
    ofstream file("sort_results.csv");
    if (file.is_open()) {
        file << "Algorithm,Array Size,Time (nanoseconds), Hue\n";
        file.close();
    }
    string filePath = "sort_results.csv";
    //writeToCSV(filePath, "Test Sort", 123457);
    for (int arraySize : arraySizes) {
        int* arr = new int[arraySize];
        generateRandomArray(arr, arraySize);
       // writeToCSV(filePath, "Test Sort 2", 123457);
        // Allocate array dynamically based on arraySize
        int* insertArr = new int[arraySize];
        int* insertOptArr = new int[arraySize];
        int* shellArr = new int[arraySize];
        int* shellOptArr = new int[arraySize];
        int* radixArr = new int[arraySize];
        int* radixOptArr = new int[arraySize];
        int* radixOptBitArr = new int[arraySize];
        int* radixOptBitVectArr = new int[arraySize];
        int* quickArr = new int[arraySize];
        int* quickOptArr = new int[arraySize];
        int* bubbleArr = new int[arraySize];
        int* bubbleOptArr = new int[arraySize];
        int* bubbleOptCombArr = new int[arraySize];
        int* stdArr = new int[arraySize];

        // Copy Arrays for before and after, not currently useful but will be
        copyArray(arr, insertArr, arraySize);
        copyArray(arr, insertOptArr, arraySize);
        copyArray(arr, shellArr, arraySize);
        copyArray(arr, shellOptArr, arraySize);
        copyArray(arr, radixArr, arraySize);
        copyArray(arr, radixOptArr, arraySize);
        copyArray(arr, radixOptBitArr, arraySize);
        copyArray(arr, radixOptBitVectArr, arraySize);
        copyArray(arr, quickArr, arraySize);
        copyArray(arr, quickOptArr, arraySize);
        copyArray(arr, bubbleArr, arraySize);
        copyArray(arr, bubbleOptArr, arraySize);
        copyArray(arr, bubbleOptCombArr, arraySize);
        copyArray(arr, stdArr, arraySize);
        //writeToCSV(filePath, "Test Sort 3", 123457);
         
         
        
        //Run tests and record time
        //insert sort
        auto startInsert = chrono::high_resolution_clock::now();
        insertSort(insertArr, arraySize);
        auto endInsert = chrono::high_resolution_clock::now();
        durationInsert = chrono::duration_cast<chrono::microseconds>(endInsert - startInsert).count();

        //optimised insert sort 
        auto startInsertOpt = chrono::high_resolution_clock::now();
        insertSortOptimised(insertOptArr, arraySize);
        auto endInsertOpt = chrono::high_resolution_clock::now();
        durationInsertOpt = chrono::duration_cast<chrono::microseconds>(endInsertOpt - startInsertOpt).count();

        

        //shell sort
        auto startShell = chrono::high_resolution_clock::now();
        shellSort(shellArr, arraySize);
        auto endShell = chrono::high_resolution_clock::now();
        durationShell = chrono::duration_cast<chrono::microseconds>(endShell - startShell).count();

        //optimised shell sort
        auto startShellOpt = chrono::high_resolution_clock::now();
        shellSortOptimised(shellOptArr, arraySize);
        auto endShellOpt = chrono::high_resolution_clock::now();
        durationShellOpt = chrono::duration_cast<chrono::microseconds>(endShellOpt - startShellOpt).count();



        //rubix sort
        auto startRadix = chrono::high_resolution_clock::now();
        radixSort(radixArr, arraySize);
        auto endRadix = chrono::high_resolution_clock::now();
        durationRadix = chrono::duration_cast<chrono::microseconds>(endRadix - startRadix).count();

        //optimised rubix sort
        auto startRadixOpt = chrono::high_resolution_clock::now();
        radixSortOptimised(radixOptArr, arraySize);
        auto endRadixOpt = chrono::high_resolution_clock::now();
        durationRadixOpt= chrono::duration_cast<chrono::microseconds>(endRadixOpt - startRadixOpt).count();

        //bitwise optimised rubix sort
        auto startRadixOptBit = chrono::high_resolution_clock::now();
        radixSortOptimisedBit(radixOptBitArr, arraySize);
        auto endRadixOptBit = chrono::high_resolution_clock::now();
        durationRadixOptBit = chrono::duration_cast<chrono::microseconds>(endRadixOptBit - startRadixOptBit).count();

        //bitwise optimised vector rubix sort
        auto startRadixOptBitVector = chrono::high_resolution_clock::now();
        radixSortOptimisedBitVector(radixOptBitVectArr, arraySize);
        auto endRadixOptBitVector = chrono::high_resolution_clock::now();
        durationRadixOptBitVector = chrono::duration_cast<chrono::microseconds>(endRadixOptBitVector - startRadixOptBitVector).count();



        //quick sort
        auto startQuick = chrono::high_resolution_clock::now();
        quickSort(quickArr, 0, arraySize - 1);
        auto endQuick = chrono::high_resolution_clock::now();
        durationQuick = chrono::duration_cast<chrono::microseconds>(endQuick - startQuick).count();

        //optimsied quick sort
        auto startQuickOpt = chrono::high_resolution_clock::now();
        quickSortOptimised(quickOptArr, 0, arraySize - 1);
        auto endQuickOpt = chrono::high_resolution_clock::now();
        durationQuickOpt = chrono::duration_cast<chrono::microseconds>(endQuickOpt - startQuickOpt).count();



        //bubble sort
        auto startBubble = chrono::high_resolution_clock::now();
        bubbleSort(bubbleArr, arraySize);
        auto endBubble = chrono::high_resolution_clock::now();
        durationBubble = chrono::duration_cast<chrono::microseconds>(endBubble - startBubble).count();

        //optimised bubble sort
        auto startBubbleOpt = chrono::high_resolution_clock::now();
        bubbleSortOptimised(bubbleOptArr, arraySize);
        auto endBubbleOpt = chrono::high_resolution_clock::now();
        durationBubbleOpt = chrono::duration_cast<chrono::microseconds>(endBubbleOpt - startBubbleOpt).count();

        //optimised bubble comb sort
        auto startBubbleCombOpt = chrono::high_resolution_clock::now();
        bubbleSortCombOptimised(bubbleOptCombArr, arraySize);
        auto endBubbleCombOpt = chrono::high_resolution_clock::now();
        durationBubbleCombOpt = chrono::duration_cast<chrono::microseconds>(endBubbleCombOpt - startBubbleCombOpt).count();



        //std sort
        auto startStd = chrono::high_resolution_clock::now();
        std::sort(stdArr, stdArr + arraySize);
        auto endStd = chrono::high_resolution_clock::now();
        durationStd = chrono::duration_cast<chrono::microseconds>(endStd - startStd).count();
        //writeToCSV(filePath, "Test Sort 4", 123457)
        
        


        // Write results to CSV and print to console
        cout << "Insertion Sort - Size " << arraySize << ": " << durationInsert << " nanoseconds" << endl;
        writeToCSV(filePath, "Insertion Sort" , arraySize, durationInsert, "UnOptimised");

        cout << "Insertion Sort Optimised - Size " << arraySize << ": " << durationInsertOpt << " nanoseconds" << endl;
        writeToCSV(filePath, "Insertion Sort Optimised", arraySize, durationInsertOpt, "Optimised");


        cout << "Shell Sort - Size " << arraySize << ": " << durationShell << " nanoseconds" << endl;
        writeToCSV(filePath, "Shell Sort", arraySize, durationShell, "UnOptimised");

        cout << "Shell Sort Optimised - Size " << arraySize << ": " << durationShellOpt << " nanoseconds" << endl;
        writeToCSV(filePath, "Shell Sort Optimised ", arraySize, durationShellOpt, "Optimised");


        cout << "Rubix Sort - Size " << arraySize << ": " << durationRadix << " nanoseconds" << endl;
        writeToCSV(filePath, "Rubix Sort", arraySize, durationRadix, "UnOptimised");

        cout << "Rubix Sort Optimised  - Size " << arraySize << ": " << durationRadixOpt << " nanoseconds" << endl;
        writeToCSV(filePath, "Rubix Sort Optimised ", arraySize, durationRadixOpt, "Optimised");

        cout << "Bitwise Optimised Rubix Sort - Size " << arraySize << ": " << durationRadixOptBit << " nanoseconds" << endl;
        writeToCSV(filePath, "Bitwise Optimised Rubix Sort", arraySize, durationRadixOptBit, "Optimised");

        cout << "Bitwise Optimised Vector Rubix Sort - Size " << arraySize << ": " << durationRadixOptBitVector << " nanoseconds" << endl;
        writeToCSV(filePath, "Bitwise Optimised Vector Rubix Sort", arraySize, durationRadixOptBitVector, "Optimised");


        cout << "Quick Sort - Size " << arraySize << ": " << durationQuick << " nanoseconds" << endl;
        writeToCSV(filePath, "Quick Sort", arraySize, durationQuick, "UnOptimised");

        cout << "Quick Sort Optimised  - Size " << arraySize << ": " << durationQuickOpt << " nanoseconds" << endl;
        writeToCSV(filePath, "Quick Sort Optimised", arraySize, durationQuickOpt, "Optimised");


        cout << "Bubble Sort - Size " << arraySize << ": " << durationBubble << " nanoseconds" << endl;
        writeToCSV(filePath, "Bubble Sort", arraySize, durationBubble, "UnOptimised");

        cout << "Bubble Sort Optimised - Size " << arraySize << ": " << durationBubbleOpt << " nanoseconds" << endl;
        writeToCSV(filePath, "Bubble Sort Optimised ", arraySize, durationBubbleOpt, "Optimised");

        cout << "Bubble Comb Sort Optimised - Size " << arraySize << ": " << durationBubbleCombOpt << " nanoseconds" << endl;
        writeToCSV(filePath, "Bubble Comb Sort Optimised", arraySize, durationBubbleCombOpt, "Optimised");



        cout << "Std Sort - Size " << arraySize << ": " << durationStd << " nanoseconds" << endl;
        writeToCSV(filePath, "Std Sort", arraySize, durationStd, "Optimised");

        // Free memory
        delete[] arr;
        delete[] insertArr;
        delete[] insertOptArr;
        delete[] shellArr;
        delete[] shellOptArr;
        delete[] radixArr;
        delete[] radixOptArr;
        delete[] radixOptBitArr;
        delete[] radixOptBitVectArr;
        delete[] quickArr;
        delete[] quickOptArr;
        delete[] bubbleArr;
        delete[] bubbleOptArr;
        delete[] bubbleOptCombArr;


        delete[] stdArr;
        auto endOver = chrono::high_resolution_clock::now();
        durationOver = chrono::duration_cast<chrono::microseconds>(endOver - startOver).count();
        cout << "Total Time " << durationOver << " microseconds" << endl;
    }
}
int main() {
    
    sortingTests();
    return 0;
}
