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
#include <math.h> 
#include <stdlib.h>

using namespace std;


map<int, vector<int>> buildLayers(vector<int> history){
     map<int, vector<int>> layers = {};
        layers[0] = history;

        bool isZeros = false;
        int layerIdx = 0;
        while(!isZeros){
            vector<int> currentLayer = layers[layerIdx];
            vector<int> newLayer = {};
            for(int i = 1; i < currentLayer.size(); ++i){
                newLayer.push_back(currentLayer[i]-currentLayer[i-1]);
            }
            ++layerIdx;
            layers[layerIdx] = newLayer;

            if(all_of(newLayer.begin(), newLayer.end(),[](int x) {return x == 0;}))
            {
                isZeros = true;
            }
        }
    return layers;
}

int part_1(ifstream &inputFile) 
{
    string line;
    int result = 0;

    while(getline(inputFile, line)){
        vector<int> history = {};

        istringstream history_stream(line);
        string historyPoint;
        while(getline(history_stream, historyPoint, ' ')){
            history.push_back(stoi(historyPoint));
        }

        map<int, vector<int>> layers = buildLayers(history);

        int nextElemInLine = 0;
        for(int i = layers.size()-1; i > -1; --i){
            int lastInLine = layers[i].back();
            nextElemInLine = nextElemInLine + lastInLine;
        }
        result += nextElemInLine;
    }

    return result;
}

int part_2(ifstream &inputFile) 
{
    string line;
    int result = 0;

    while(getline(inputFile, line)){
        vector<int> history = {};
        istringstream history_stream(line);
        string historyPoint;
        while(getline(history_stream, historyPoint, ' ')){
            history.push_back(stoi(historyPoint));
        }

       
        map<int, vector<int>> layers = buildLayers(history);
        
        int nextElemInLine = 0;
        int historicalElemInLine = 0;
        for(int i = layers.size()-1; i > -1; --i){
            int firstInLine = layers[i].front();
            historicalElemInLine = firstInLine - historicalElemInLine;
        }

        result += historicalElemInLine;
    }
    
    return result;
}


int main()
{   
    ifstream inputFile("input.txt");
    auto start = chrono::high_resolution_clock::now();
    
    long long int result = 0;
    
    result = part_1(inputFile);
    cout << endl << "Part 1: " << result << endl <<endl;

    inputFile.clear();
    inputFile.seekg(0);

    result = part_2(inputFile);
    cout << "Part 2: " << result << endl << endl;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Time taken: " << duration.count()/1e+6 << " seconds" << endl;
    inputFile.close();

    // string dummy;
    // cout << "Enter to continue..." << endl;
    // getline(cin, dummy);

    return 0;
}
