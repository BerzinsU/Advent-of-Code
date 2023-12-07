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
#include <set>


using namespace std;

int part_1(ifstream &inputFile) 
{
    string line;
    int result = 0;
    size_t delimiterPosS = 0;
    size_t delimiterPosE = 0;

    while ( getline(inputFile, line) ) {
        string winning, scratched;
        vector<int> winningNumbers, scratchedNumbers;
        int cardResult = 0;
        if(delimiterPosS == 0){
            delimiterPosS = line.find(":");
        }
        if(delimiterPosE == 0){
            delimiterPosE = line.find("|");
        }
        winning = line.substr(delimiterPosS+1, delimiterPosE -delimiterPosS-1);   

        istringstream number_stream(winning);
        string number;

        while(getline(number_stream, number, ' ')) {
            if(number.size()>0){
                winningNumbers.push_back(stoi(number));
            }
        }
        

        scratched = line.substr( delimiterPosE+1);   

        number_stream = istringstream(scratched);

        while(getline(number_stream, number, ' ')){
            if(number.size()>0){
                int scratchedNumber = stoi(number);
                for(int winNumber: winningNumbers){
                    if(winNumber == scratchedNumber){
                        if(cardResult == 0){
                            cardResult = 1;
                        } else {
                            cardResult = cardResult*2;
                        }
                    }
                }
            }
        }
        result += cardResult;
    }
    return result;
}

int part_2(ifstream &inputFile) 
{
    string line;
    int result = 0;
    int uniqueGames = 0;

    vector<int> copies(200,1);
    size_t delimiterPosS = 0;
    size_t delimiterPosE = 0;
    while ( getline(inputFile, line) ) {
       

        string winning, scratched;
        set<int> winningNumbers;
        int winningNumberCount = 0;
        string cardName;

        if(delimiterPosS == 0){
            delimiterPosS = line.find(":");
        }
        if(delimiterPosE == 0){
            delimiterPosE = line.find("|");
        }

        winning = line.substr(delimiterPosS+1, delimiterPosE -delimiterPosS-1);   

        istringstream number_stream(winning);
        string number;

        while(getline(number_stream, number, ' ')){
            if(number.size()>0){
                winningNumbers.insert(stoi(number));
            }
        }

        scratched = line.substr( delimiterPosE+1);   

        number_stream = istringstream(scratched);

        while(getline(number_stream, number, ' ')){
             if(number.size()>0){
                int scratchedNumber = stoi(number);
                auto it = winningNumbers.find(scratchedNumber);
                if(it != winningNumbers.end()){
                    winningNumberCount++;
                }
            }
        }
            
        for(int j = 1; j <= winningNumberCount; ++j){
            copies[uniqueGames+j] += copies[uniqueGames];
        }
        ++uniqueGames;
    }

    for(int i = 1; i <= uniqueGames; ++i){
        result += copies[i];
    }
    return result;
}



int main()
{   
    ifstream inputFile("input.txt");
    auto start = std::chrono::high_resolution_clock::now();
    
    int result = 0;
    
    result = part_1(inputFile);
    cout << "Part 1: " << result << endl;

    inputFile.clear();
    inputFile.seekg(0);

    result = part_2(inputFile);
    cout << "Part 2: " << result << endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Time taken: " << duration.count()/1e+6 << " seconds" << std::endl;
    inputFile.close();

    // std::string dummy;
    // std::cout << "Enter to continue..." << std::endl;
    // std::getline(std::cin, dummy);

    return 0;
}
