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


vector<vector<vector<int>>> keepOnlyStraightLines(vector<vector<vector<int>>> ventLines)
{
    vector<vector<vector<int>>> result={};

    auto isStraigt = [](vector<vector<int>> line) {
        return line[0][0] == line[1][0] || line[0][1] == line[1][1];
    };
    copy_if(ventLines.begin(), ventLines.end(), std::back_inserter(result), isStraigt);
    return result;
}



vector<vector<int>> drawLine( vector<vector<int>> diagram, vector<vector<int>> ventLine) {
    // https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C++
    int x1 = ventLine[0][0];
    int x2 = ventLine[1][0];
    int y1 = ventLine[0][1];
    int y2 = ventLine[1][1];

    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep)
    {
        swap(x1, y1);
        swap(x2, y2);
    }

    if(x1 > x2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);
    
    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for(int x=(int)x1; x<=maxX; x++)
    {
        if(steep)
        {
            diagram[x][y] = diagram[x][y]+1;
        }
        else
        {
            
            diagram[y][x] = diagram[y][x]+1;
        }
                
        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
    return diagram;
} 

void renderDiagram(vector<vector<int>> diagram) 
{
    for (int i = 0; i < diagram.size(); ++i) {
    for (int j = 0; j < diagram.size(); ++j) {
        if(diagram[i][j] == 0 ){
            cout << '.';
        } else {
        cout << diagram[i][j];
        }
    }
    cout<< endl;
    }
}

vector<vector<int>> drawDiagram(vector<vector<vector<int>>> ventLines, int size) 
{
    vector<vector<int>> diagram(size,vector<int>(size,0));

    for(auto & ventLine: ventLines )
    {
        diagram = drawLine(diagram, ventLine);
    }
    return diagram;
}

int countOverlapPoints(vector<vector<int>> diagram, int limit, int size) 
{
    int points = 0;
     for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int point = diagram[i][j];
            if(point>=limit) {
                ++points;
            }
        }
     }

    return points;
}

int part_1() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    vector<vector<vector<int>>> ventLines = {};
    string line;
    int size = 0;

    while (getline(inputFile, line)) {
        vector<vector<int>> ventLine = {};
        line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
        line = regex_replace(line, regex("->"), ":");

        istringstream line_stream(line);
        string pointstring;

        while (getline(line_stream, pointstring, ':')) {
            istringstream point_stream(pointstring);
            string numberstring;
            vector<int> point = {};

            while (getline(point_stream, numberstring, ',')) {
                int number = stoi(numberstring);
                if(size< number+1) {
                    size = number+1;
                }
                point.push_back(number);
            }
            ventLine.push_back(point);
        }
        ventLines.push_back(ventLine);
    }
   
    ventLines = keepOnlyStraightLines(ventLines);
    vector<vector<int>> diagram = drawDiagram(ventLines, size);
    // renderDiagram(diagram);
    int points = countOverlapPoints(diagram, 2, size);

    inputFile.close();
    return points;
}



int part_2() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    vector<vector<vector<int>>> ventLines = {};
    string line;
    int size = 0;

    while (getline(inputFile, line)) {
        vector<vector<int>> ventLine = {};
        line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
        line = regex_replace(line, regex("->"), ":");

        istringstream line_stream(line);
        string pointstring;

        while (getline(line_stream, pointstring, ':')) {
            istringstream point_stream(pointstring);
            string numberstring;
            vector<int> point = {};

            while (getline(point_stream, numberstring, ',')) {
                int number = stoi(numberstring);
                if(size< number+1) {
                    size = number+1;
                }
                point.push_back(number);
            }
            ventLine.push_back(point);
        }
        ventLines.push_back(ventLine);
    }
   
    // ventLines = keepOnlyStraightLines(ventLines);
    vector<vector<int>> diagram = drawDiagram(ventLines, size);
    // renderDiagram(diagram);
    int points = countOverlapPoints(diagram,2, size);

    inputFile.close();
    return points;
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
