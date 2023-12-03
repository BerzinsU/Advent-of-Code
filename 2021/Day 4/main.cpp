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


bool checkForBingo(vector<vector<int>> board, vector<int> &numbers) {
    if(numbers.size() < 5 ) return false;

    vector<int> copyNumbers(numbers);

    sort(copyNumbers.begin(), copyNumbers.end());
    //lines
     for (auto & line : board) {
        vector<int> copyLine(line);
        sort(copyLine.begin(), copyLine.end());
        if(includes(copyNumbers.begin(), copyNumbers.end(), copyLine.begin(), copyLine.end())) {
            return true;
        }
     }
    //columns
    for(int i = 0; i < 5; ++i){
        vector<int> column = {board[0][i],board[1][i],board[2][i],board[3][i],board[4][i]};
        sort(column.begin(), column.end());
        if(includes(copyNumbers.begin(), copyNumbers.end(), column.begin(), column.end())) {
            return true;
        }
    }


    return false;
}

int calculateResult(vector<vector<int>> &board, vector<int> &numbers) {
    vector<int> allNumbers = {};
    vector<int> copyPulledNumbers(numbers);
     for (auto & line : board) {
        allNumbers.insert(allNumbers.end(),line.begin(),line.end());
    }
    vector<int> diff;
    sort(copyPulledNumbers.begin(), copyPulledNumbers.end());
    sort(allNumbers.begin(), allNumbers.end());
 
    set_difference( allNumbers.begin(), allNumbers.end(),copyPulledNumbers.begin(), copyPulledNumbers.end(),
                        inserter(diff, diff.begin()));

     int sum_of_elems = accumulate(diff.begin(), diff.end(), 0);
    

    return sum_of_elems*numbers.back();
}


int part_1() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    vector<int> numbers = {};
    vector<vector<vector<int>>> boards = {};
    string line;
    string substring;

    getline(inputFile, line); // pulled numbers
    istringstream number_line_stream(line);
    while (getline(number_line_stream, substring, ',')) {
        numbers.push_back(stoi(substring));
    }

    while (getline(inputFile, line)) {
        int columnIndex=0;
        vector<vector<int>> board;
        while (getline(inputFile, line)) {
            
            if(line.length()==0){
                break;
            }

            line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");

            istringstream line_stream(line);
            string linesubstring;
            vector<int> boardLine = {};
            while (getline(line_stream, linesubstring, ' ')) {
                boardLine.push_back(stoi(linesubstring));
            }
            board.push_back(boardLine);
            if(board.size() == 5) {
                boards.push_back(board);
                break;
            }
        }
    }
   
    vector<int> pulledNumbers;
    for (auto & number : numbers) {
        pulledNumbers.push_back(number);
        for (auto & board : boards) {
            bool bingo = checkForBingo(board, pulledNumbers);
            if (bingo) {
                // cout << "BINGO!" << endl;
                return calculateResult(board, pulledNumbers);
            }
        }
    }


    inputFile.close();
    return 0;
}



int part_2() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    vector<int> numbers = {};
    vector<vector<vector<int>>> boards = {};
    string line;
    string substring;

    getline(inputFile, line); // pulled numbers
    istringstream number_line_stream(line);
    while (getline(number_line_stream, substring, ',')) {
        numbers.push_back(stoi(substring));
    }

    while (getline(inputFile, line)) {
        int columnIndex=0;
        vector<vector<int>> board;
        while (getline(inputFile, line)) {
            
            if(line.length()==0){
                break;
            }

            line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");

            istringstream line_stream(line);
            string linesubstring;
            vector<int> boardLine = {};
            while (getline(line_stream, linesubstring, ' ')) {
                boardLine.push_back(stoi(linesubstring));
            }
            board.push_back(boardLine);
            if(board.size() == 5) {
                boards.push_back(board);
                break;
            }
        }
    }
   
    vector<int> pulledNumbers;
    int bingoCount = 0;
    vector<int> boardsThatWon;
    vector<int> numbersToWin;
    for (auto & number : numbers) {
        pulledNumbers.push_back(number);
        

        for (int i = 0; i< boards.size(); ++i) {
            if( find(boardsThatWon.begin(), boardsThatWon.end(), i) != boardsThatWon.end() ) 
            {
                continue;
            }

            bool bingo = checkForBingo(boards[i], pulledNumbers);
            if (bingo) {
                bingoCount++;
                // cout << "BINGO!: "<< bingoCount << endl;
                boardsThatWon.push_back(i);
                numbersToWin = pulledNumbers;
                if(boards.size() == 1 ){
                     return calculateResult(boards[i], pulledNumbers);
                }
            }
        }
    }


    inputFile.close();
    return calculateResult(boards[boardsThatWon.back()], numbersToWin);
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
