#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <queue>
#include <numeric>
#include <map>

using namespace std;

int part_1() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    int coordinates[2] = {0,0};



    while (getline(inputFile, line)) {
        istringstream line_stream(line);
        string command;
        int amount;
        line_stream >> command >> amount;
        // cout << "Line:" << command << amount << endl;
        

        if(command == "forward"){
            coordinates[0] = coordinates[0] + amount;
        }
        else if (command == "up") {
            coordinates[1] = coordinates[1] - amount;
        }
        else if (command == "down") {
            coordinates[1] = coordinates[1] + amount;
        }

    }

    // cout << "Coordinates:[" << coordinates[0] << "," << coordinates[1] << "]" << endl;

    inputFile.close();
    return coordinates[0]*coordinates[1];
}

int part_2(){
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    int coordinates[3] = {0,0,0};



    while (getline(inputFile, line)) {
        istringstream line_stream(line);
        string command;
        int amount;
        line_stream >> command >> amount;
        // cout << "Line:" << command << amount << endl;
        

        if(command == "forward"){
            coordinates[0] = coordinates[0] + amount;
            coordinates[1] = coordinates[1] + amount * coordinates[2];
        }
        else if (command == "up") {
            coordinates[2] = coordinates[2] - amount;
        }
        else if (command == "down") {
            coordinates[2] = coordinates[2] + amount;
        }

    }

    // cout << "Coordinates:[" << coordinates[0] << "," << coordinates[1] << "]" << endl;

    inputFile.close();
    return coordinates[0]*coordinates[1];
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
