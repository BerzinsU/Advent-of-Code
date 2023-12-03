#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <queue>
#include <numeric>

using namespace std;


int part_1() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    int previousDepth = 0;
    int increaseCount = 0;
    int currentDepth = 0;

    while (getline(inputFile, line)) {
        currentDepth = stoi(line);
        if(previousDepth != 0) {
            if(currentDepth > previousDepth){
                ++increaseCount;
            }
        }
        previousDepth = currentDepth;
    }

    inputFile.close();
    return increaseCount;
}

int part_2(){
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    deque<int> slidingWindow;
    int previousDepth = 0;
    int increaseCount = 0;
    int currentDepth = 0;

    while (getline(inputFile, line)) {
        currentDepth = stoi(line);
        slidingWindow.push_back(currentDepth);
        if(slidingWindow.size() == 3) {
            
            currentDepth = accumulate(slidingWindow.begin(), slidingWindow.end(),0);
            if(previousDepth != 0) {
                if(currentDepth > previousDepth){
                    
                    ++increaseCount;
                }
            }
            previousDepth = currentDepth;
            slidingWindow.pop_front();
        }
    }

    inputFile.close();
    return increaseCount;
}


int main()
{   
    auto start = std::chrono::high_resolution_clock::now();
    
    int increaseCount = 0;

    increaseCount = part_1();
    cout << "Part 1: " << increaseCount << endl;

    increaseCount = part_2();
    cout << "Part 2: " << increaseCount << endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Time taken by function: " << duration.count()/1e+6 << " seconds" << std::endl;


    return 0;
}
