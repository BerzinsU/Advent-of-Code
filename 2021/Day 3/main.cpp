#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <queue>
#include <numeric>
#include <map>
#include <algorithm>

using namespace std;

int part_1() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    vector<int> sumVec = {};
    int lineCount = 0;

    while (getline(inputFile, line)) {
        istringstream line_stream(line);
        vector<int> lineVec;
        
        for(char c: line){
            int digit = c - '0';
            lineVec.push_back(digit);
        }
        if(sumVec.size()<1)
        {
            sumVec = lineVec;
            continue;
        }
        transform (sumVec.begin(), sumVec.end(), lineVec.begin(), sumVec.begin(), std::plus<int>());
        ++lineCount;

    }

    int majorityCount = (lineCount + 2 -1) / 2;

    unsigned int gammaRate = 0;
    unsigned int epsilonRate = 0;

    for (int &element : sumVec) {
        if(element>= majorityCount){
            gammaRate = (gammaRate << 1) | 1;
            epsilonRate = (epsilonRate << 1) | 0;
        } else {
            gammaRate = (gammaRate << 1) | 0;
            epsilonRate = (epsilonRate << 1) | 1;
        }
    }

    inputFile.close();
    return gammaRate * epsilonRate;
}


vector<int> countBitOccurances(vector<string> lines) 
{
    vector<int> sumVec = {};
    vector<string>::iterator iter = lines.begin();
    for(iter; iter< lines.end(); iter++){
        vector<int> lineVec;
         for(char c: *iter){
            int digit = c - '0';
            lineVec.push_back(digit);
        }
        if(sumVec.size()<1)
        {
            sumVec = lineVec;
            continue;
        }
        transform (sumVec.begin(), sumVec.end(), lineVec.begin(), sumVec.begin(), std::plus<int>());
    }
    int majorityCount = (lines.size() + 2 -1) / 2;

    for (int &element : sumVec) {
        if(element>= majorityCount){
           element = 1;
        } else {
            element = 0;
        }
    }

    return sumVec;
}

int part_2() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    vector<string> report = {};

    while (getline(inputFile, line)) {
        istringstream line_stream(line);
        report.push_back(line);
    }

    vector<int> sumVec = countBitOccurances(report);

    string searchString = "";
    vector<string> possibleOxygenResults(report);

    while(possibleOxygenResults.size()>1){
        for (int i = 0; i < sumVec.size(); ++i) {
            searchString.append(to_string(sumVec[i]));
            auto it = copy_if(possibleOxygenResults.begin(),possibleOxygenResults.end(),possibleOxygenResults.begin(),[searchString](string line){ return line.rfind(searchString, 0)==0;});
            possibleOxygenResults.resize(distance(possibleOxygenResults.begin(),it));
            sumVec = countBitOccurances(possibleOxygenResults);
        }
        
    }

    unsigned int oxygenRate = stoi(possibleOxygenResults.front(),0,2);

    searchString = "";
    sumVec = countBitOccurances(report);
    vector<string> possibleCO2Results(report);

    while(possibleCO2Results.size()>1){
        for (int i = 0; i < sumVec.size(); ++i) {
            searchString.append(to_string(sumVec[i] ^ 1));
            auto it = copy_if(possibleCO2Results.begin(),possibleCO2Results.end(),possibleCO2Results.begin(),[searchString](string line){ return line.rfind(searchString, 0)==0;});
            possibleCO2Results.resize(distance(possibleCO2Results.begin(),it));
            sumVec = countBitOccurances(possibleCO2Results);
            if( possibleCO2Results.size() < 2 ) {break;}
        }
        
    }

    unsigned int co2Rate = stoi(possibleCO2Results.front(),0,2);

    inputFile.close();
    return oxygenRate * co2Rate;
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
