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

long long int solve(int daysToSim) 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    string numberstring;
    vector< long long int> fishes;

    while (getline(inputFile, line)) {
        istringstream line_stream(line);
        while (getline(line_stream, numberstring, ',')) {
             long long int number = stoi(numberstring);
            fishes.push_back(number);
        }
    }
    inputFile.close();
    deque< long long int> fishCount(9, 0);

    for( long long int fish: fishes ){
        fishCount[fish] = ++fishCount[fish];
    }

    long long int result = 0;

    for(int i=0; i< daysToSim; ++i){
        if(fishCount.front()> 0){
            long long int fishesToGenerate = fishCount.front();
            fishCount.pop_front();
            fishCount.push_back(fishesToGenerate);
            fishCount[6] = fishCount[6]+fishesToGenerate;

        } else {
            fishCount.pop_front();
            fishCount.push_back(0);
        }
    }
    for(  long long int fish:fishCount ){
        result = result + fish; 
    }
    return result;
    
}


int main()
{   
    auto start = std::chrono::high_resolution_clock::now();
    
     long long int result = 0;

    result = solve(80);
    cout << "Part 1: " << result << endl;

    result = solve(256);
    cout << "Part 2: " << result << endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Time taken by function: " << duration.count()/1e+6 << " seconds" << std::endl;

    return 0;
}
