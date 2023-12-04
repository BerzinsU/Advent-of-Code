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

    while ( getline(inputFile, line) ) {
        string winning, scratched;
        vector<int> winningNumbers, scratchedNumbers;
        int cardResult = 0;

        size_t delimiterPosS = line.find(":");
        size_t delimiterPosE = line.find("|");

        winning = line.substr(delimiterPosS+1, delimiterPosE -delimiterPosS-1);   
        winning = regex_replace(winning, regex("^ +| +$|( ) +"), "$1");

        istringstream number_stream(winning);
        string number;

        while(getline(number_stream, number, ' ')) {
            winningNumbers.push_back(stoi(number));
        }
        

        scratched = line.substr( delimiterPosE+1);   
        scratched = regex_replace(scratched, regex("^ +| +$|( ) +"), "$1");

        number_stream = istringstream(scratched);

        while(getline(number_stream, number, ' ')){
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
    while ( getline(inputFile, line) ) {
        uniqueGames++;

        string winning, scratched;
        set<int> winningNumbers;
        int winningNumberCount = 0;
        string cardName;
        int cardNumber = 0;

        size_t delimiterPosS = line.find(":");
        size_t delimiterPosE = line.find("|");

        istringstream gameNameStream(line.substr(0,delimiterPosS));
        gameNameStream >> cardName;
        gameNameStream >> cardNumber;
      
        winning = line.substr(delimiterPosS+1, delimiterPosE -delimiterPosS-1);   
        winning = regex_replace(winning, regex("^ +| +$|( ) +"), "$1");

        istringstream number_stream(winning);
        string number;

        while(getline(number_stream, number, ' ')){
            winningNumbers.insert(stoi(number));
        }

        scratched = line.substr( delimiterPosE+1);   
        scratched = regex_replace(scratched, regex("^ +| +$|( ) +"), "$1");

        number_stream = istringstream(scratched);

        while(getline(number_stream, number, ' ')){
            int scratchedNumber = stoi(number);
            auto it = winningNumbers.find(scratchedNumber);
            if(it != winningNumbers.end()){
                winningNumberCount++;
            }
        }
            
        for(int j = 1; j <= winningNumberCount; ++j){
            copies[cardNumber+j] += copies[cardNumber];
        }
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
    return 0;
}
