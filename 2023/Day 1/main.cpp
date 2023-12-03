#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <queue>
#include <map>
#include <numeric>
#include <cctype> 

using namespace std;


int part_1() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    int result = 0;
    string line;
    while (getline(inputFile, line)) {
        char firstDigit;
        char secondDigit;
       for(char c: line){
            if (std::isdigit(c)) {
                firstDigit = c;
                break;
            }
        }
        string reversed(line.rbegin(), line.rend());
        for(char c:reversed ){
            if (std::isdigit(c)) {
                secondDigit = c;
                break;
            }
        }
        string number(1, firstDigit);
        number += secondDigit;
        result += stoi(number);
    }

    inputFile.close();
    return result;
}

string replaceWords(string& line){
    map<string, string> numberNames {{"one", "1"}, 
                                    {"two", "2"}, 
                                    {"three", "3"}, 
                                    {"four", "4"}, 
                                    {"five","5"}, 
                                    {"six","6"}, 
                                    {"seven","7"}, 
                                    {"eight","8"},
                                    {"nine", "9"}};

    
    bool noneFound = false;

    while(!noneFound){
        pair<string, string> firstNumber;
        int smallestIndex = line.size();
        for (const auto& number : numberNames) {
            size_t found = line.find(number.first);
            if (found!=std::string::npos){
                if(found < smallestIndex){
                        firstNumber = number;
                        smallestIndex = found;
                }
            }
        }
        if(smallestIndex < line.size()){
            line.replace(smallestIndex, firstNumber.first.size(), firstNumber.second);}
        else{ 
            noneFound = true;
        }
    }

    return line;
}


int part_2() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    long long int result = 0;
    string line;


    while (getline(inputFile, line)) {
        char firstDigit;
        char secondDigit;
        line = replaceWords(line);
       for(char c: line){
            if (std::isdigit(c)) {
                firstDigit = c;
                break;
            }
        }
        string reversed(line.rbegin(), line.rend());
        for(char c:reversed ){
            if (std::isdigit(c)) {
                secondDigit = c;
                break;
            }
        }
        string number(1, firstDigit);
        number += secondDigit;
        result += stoi(number);
    }

    inputFile.close();
    return result;
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
