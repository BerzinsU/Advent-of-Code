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

vector<vector<int>> getNeighboringNumbers(vector<vector<char>> grid, vector<int> coordinates) {
    size_t rows = grid.size();
    size_t columns =  grid[0].size();
    int x = coordinates[0];
    int y = coordinates[1];

    vector<vector<int>> nCoord = {{-1, -1},{-1, 0},{-1, 1},{0, -1},{0, 1},{1, -1},{1, 0},{1, 1}};
    vector<vector<int>> digitNeighbours = {};

    for(vector<int> coord: nCoord){
        int nX = x + coord[0];
        int nY = y + coord[1];

        if(nX>=0 && nY>= 0 && nX < rows && nY < columns){
            if(isdigit(grid[nX][nY])){
                digitNeighbours.push_back({nX,nY});
            }
        }
    }
   
    return digitNeighbours;
}

set<int> extractNumbers(vector<vector<char>> grid, vector<vector<int>>digitCoords){
     
     set<int> numbers = {};
     for(vector<int> digitCoord: digitCoords){
        size_t columns =  grid[0].size();
        int x = digitCoord[0];
        int y = digitCoord[1];
        deque<int> number;
        number.push_front(grid[x][y]- '0');

        //look back until . or bound
        int yBack = y-1;
        while(yBack >= 0){
             if(isdigit(grid[x][yBack])){
                number.push_front(grid[x][yBack]-'0');
                yBack--;
             }
             else {
                yBack = -1;
             }
        }

        //look ahead until . or bound
        int yFront = y+1;
         while(yFront < columns){
             if(isdigit(grid[x][yFront])){
                number.push_back(grid[x][yFront]-'0');
                yFront++;
             }
             else {
                yFront = columns;
             }
        }
        string numberStr;
        for (int digit : number) {
            numberStr += to_string(digit);
        }
        numbers.insert(stoi(numberStr));
    }
    return numbers;
}

int part_1() 
{
    ifstream inputFile("input.txt");

    string line;
    int result = 0;
    vector<vector<char>> schematic;


    while ( getline(inputFile, line) ) {
        string symbol;
        vector<char> symbols = {};
        for (char c : line) {
            symbols.push_back(c);
        }
        schematic.push_back(symbols);
    }

     for(int i = 0; i < schematic.size(); i++){
        for(int j = 0; j < schematic[0].size(); j++){
            char point = schematic[i][j];
            if(!isdigit(point) && point != '.'){
                vector<vector<int>> digitNeigbours = getNeighboringNumbers(schematic,{i,j});
                set<int> numbers = extractNumbers(schematic, digitNeigbours);

                for(int number: numbers){
                    result += number;
                }
            }
        }
     }

    inputFile.close();
    return result;
}

int part_2() 
{
    ifstream inputFile("input.txt");

    string line;
    int result = 0;
    vector<vector<char>> schematic;


    while ( getline(inputFile, line) ) {
        string symbol;
        vector<char> symbols = {};
        for (char c : line) {
            symbols.push_back(c);
        }
        schematic.push_back(symbols);
    }

     for(int i = 0; i < schematic.size(); i++){
        for(int j = 0; j < schematic[0].size(); j++){
            char point = schematic[i][j];
            if(!isdigit(point) && point != '.' && point == '*'){
                vector<vector<int>> digitNeigbours = getNeighboringNumbers(schematic,{i,j});
                set<int> numbers = extractNumbers(schematic, digitNeigbours);

                if(numbers.size() > 1){
                    int part1 = *numbers.begin();
                    int part2 = *next(numbers.begin());
                    result += part1 * part2;
                }
            }
        }
     }

    inputFile.close();
    return result;
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
    
    std::cout << "Time taken: " << duration.count()/1e+6 << " seconds" << std::endl;


    return 0;
}
