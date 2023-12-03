#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <queue>
#include <numeric>
#include <map>
#include <algorithm>
#include <regex>

using namespace std;

int part_1() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    string numberstring;
    vector< int> crabs;

    while (getline(inputFile, line)) {
        istringstream line_stream(line);
        while (getline(line_stream, numberstring, ',')) {
             int number = stoi(numberstring);
            crabs.push_back(number);
        }
    }
    inputFile.close();

    sort(crabs.begin(),crabs.end());
    int middle = crabs.size()/2;
    int median = crabs[middle];

    int fuel = 0;
    for (int crab: crabs) {
        fuel = fuel + (abs(median-crab));
    }

    return fuel;
}


int part_2() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    string numberstring;
    vector< int> crabs;

    while (getline(inputFile, line)) {
        istringstream line_stream(line);
        while (getline(line_stream, numberstring, ',')) {
             int number = stoi(numberstring);
            crabs.push_back(number);
        }
    }
    inputFile.close();

    double sum = accumulate(crabs.begin(), crabs.end(), 0) ;
    int meanUp = round(sum/ crabs.size());
    int meanDown = sum/ crabs.size();

    int fuelUp = 0;
    for (int crab: crabs) {
        int distance =  (abs(meanUp-crab));
        fuelUp = fuelUp + distance*(distance+1)/2;
    }

    int fuelDown = 0;
    for (int crab: crabs) {
        int distance =  (abs(meanDown-crab));
        fuelDown = fuelDown + distance*(distance+1)/2;
    }

    return min(fuelDown, fuelUp);
}

int main()
{   
    auto start = std::chrono::high_resolution_clock::now();
    
    int result = 0;

    result = part_1();
    cout << "Part 1: " << result << endl;

    result = part_2();
    cout << "Part 2: " << result << endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Time taken by function: " << duration.count()/1e+6 << " seconds" << std::endl;

    return 0;
}
