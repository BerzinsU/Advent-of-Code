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

vector<int> getNeighbours(vector<vector<int>> caves, vector<int> coordinates) {
    size_t rows = caves.size();
    size_t columns =  caves[0].size();
    int x = coordinates[0];
    int y = coordinates[1];

    vector<int> neighbours = {};

    //Top
    if(x > 0){
        neighbours.push_back(caves[x-1][y]);
    }
    //Bottom
    if(x < rows-1){
        neighbours.push_back(caves[x+1][y]);
    }
    //left
    if(y > 0){
        neighbours.push_back(caves[x][y-1]);
    }
    //right
    if(y < columns-1){
        neighbours.push_back(caves[x][y+1]);
    }
    return neighbours;
}

vector<vector<int>> getBasinNeighbourCoordinates(vector<vector<int>> caves, vector<int> coordinates) {
    size_t rows = caves.size();
    size_t columns =  caves[0].size();
    int x = coordinates[0];
    int y = coordinates[1];

    vector<vector<int>> neighbours = {};

    //Top
    if(x > 0 && caves[x-1][y] < 9){
        neighbours.push_back({x-1,y});
    }
    //Bottom
    if(x < rows-1  && caves[x+1][y] < 9){
        neighbours.push_back({x+1,y});
    }
    //left
    if(y > 0  && caves[x][y-1] < 9){
        neighbours.push_back({x,y-1});
    }
    //right
    if(y < columns-1 && caves[x][y+1] < 9){
        neighbours.push_back({x,y+1});
    }
    return neighbours;
}


int part_1() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    string line;
    vector<vector<int>> caves;

    while ( getline(inputFile, line) ) {
        string number;
        vector<int> numbers = {};
        for (char c : line) {
            int num = c - '0';
            numbers.push_back(num);
        }
        caves.push_back(numbers);
    }

    int totalRisk = 0;

    for(int i = 0; i < caves.size(); i++){
        for(int j = 0; j < caves[0].size(); j++){
            // cout<< i << ":" <<j << endl;
            // cout<< "Point:" <<caves[i][j] << endl;

            int point = caves[i][j];

            vector<int> neighbours = getNeighbours(caves, {i,j});

            if(all_of(neighbours.begin(), neighbours.end(), [point](int num) {return num > point;} )) {
                totalRisk += 1+point;
            }

        }
    }


    inputFile.close();
    return totalRisk;
}


void removeVisited(std::vector<std::vector<int>>& vector1, const std::vector<std::vector<int>>& vector2) {
    for (auto it = vector1.begin(); it != vector1.end(); ) {
        if (std::find(vector2.begin(), vector2.end(), *it) != vector2.end()) {
            it = vector1.erase(it);
        } else {
            ++it;
        }
    }
}

bool isVectorNotIn2DVector(const std::vector<std::vector<int>>& matrix, const std::vector<int>& vec) {
    return std::find(matrix.begin(), matrix.end(), vec) == matrix.end();
}


int walkTheBasin(vector<vector<int>> caves, vector<vector<int>> * visited, vector<int> point ){
    // cout << "Searching from: [" << point[0] << "," << point[1] << "]" << endl;
    // cout << "Visited: " << visited->size()<< endl;

    vector<vector<int>> basinNeighbours = getBasinNeighbourCoordinates(caves, point);
    removeVisited(basinNeighbours, *visited);

    int basinSize = 1;

    for(vector<int> neighbour: basinNeighbours){
        if(isVectorNotIn2DVector(*visited, neighbour)){
            visited->push_back(neighbour);
            basinSize += walkTheBasin(caves, visited, neighbour);
        }
    }
    

    return basinSize;
}


int part_2() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    string line;
    vector<vector<int>> caves;

    while ( getline(inputFile, line) ) {
        string number;
        vector<int> numbers = {};
        for (char c : line) {
            int num = c - '0';
            numbers.push_back(num);
        }
        caves.push_back(numbers);
    }

    vector<vector<int>> lowPoints= {};
    vector<int> basins= {};

    for(int i = 0; i < caves.size(); i++){
        for(int j = 0; j < caves[0].size(); j++){
            // cout<< i << ":" <<j << endl;
            // cout<< "Point:" <<caves[i][j] << endl;

            int point = caves[i][j];
            vector<int> neighbours = getNeighbours(caves, {i,j});

            if(all_of(neighbours.begin(), neighbours.end(), [point](int num) {return num > point;} )) {
                // A lowpoint
                lowPoints.push_back({i,j});
                // cout<< "___________ Lowpoint:" << i<<j << endl;
                vector<vector<int>>* visited = new vector<vector<int>>;
                visited->push_back({i,j});
                int basinSize = walkTheBasin(caves, visited, {i,j});
                basins.push_back(basinSize);
            }

        }
    }

    partial_sort(basins.begin(), basins.begin() + 3, basins.end(), std::greater<int>());

    int totalBasinCount = basins[0] * basins[1] * basins[2];

    inputFile.close();
    return totalBasinCount;
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
