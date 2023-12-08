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

int part_1(ifstream &inputFile) 
{
    string line;
    int result = 0;

    vector<char> commands = {};
    map<string, vector<string>> nodes = {};

    getline(inputFile, line);
    for(char dir: line){
        commands.push_back(dir);
    }

    getline(inputFile, line); // skip empty

    while ( getline(inputFile, line) ) {
        string nodeName = line.substr(0,3);
        string lNode = line.substr(7,3);
        string rNode = line.substr(12,3);

        nodes[nodeName] = {lNode, rNode};
    }

    int stepCount = 0;
    bool zFound = false;
    string currentNodeName = "AAA";
    while(!zFound){
        char command = commands[stepCount % commands.size()];
        string newNodeName;
        if(command == 'L'){
            newNodeName = nodes[currentNodeName].front();
        } else {
            newNodeName = nodes[currentNodeName].back();
        }
        if (newNodeName == "ZZZ") {
            zFound = true;
        } 
        else {
            currentNodeName = newNodeName;
        }
        ++stepCount;
    }
    result = stepCount;
    return result;
}


long long gcd(long long int a, long long int b) 
{ 
  if (b == 0) 
    return a; 
  return gcd(b, a % b); 
} 
  

long long lcm(long long a, long long  int b) 
{ 
    return (a / gcd(a, b)) * b; 
} 
   

long long int part_2(ifstream &inputFile) 
{
    string line;
    long long int result = 1;

    vector<char> commands = {};
    map<string, vector<string>> nodes = {};
    vector<string> startNodes = {};
    vector<string> endNodes = {};

    getline(inputFile, line);
    for(char dir: line){
        commands.push_back(dir);
    }

    getline(inputFile, line); // skip empty

    while ( getline(inputFile, line) ) {
        string nodeName = line.substr(0,3);
        string lNode = line.substr(7,3);
        string rNode = line.substr(12,3);

        if(nodeName.back() == 'A'){
            startNodes.push_back(nodeName);
        }
        if(nodeName.back() == 'Z'){
            endNodes.push_back(nodeName);
        }

        nodes[nodeName] = {lNode, rNode};
    }

    vector<long long int> zHits = {};
    vector<string> currentNodeNames = startNodes;

    for(string currentNodeName: startNodes){
        bool zFound = false;
        long long int stepCount = 0;
        while(!zFound){
            char command = commands[stepCount % commands.size()];
            string newNodeName;
            if(command == 'L'){
                newNodeName = nodes[currentNodeName].front();
            } else {
                newNodeName = nodes[currentNodeName].back();
            }
            if (newNodeName.back() == 'Z') {
                zFound = true;
                zHits.push_back(stepCount+1);
            } 
            else {
                currentNodeName = newNodeName;
            }
            ++stepCount;
        }
    }

    result =  zHits.back();
    zHits.pop_back();
    for(long long hit: zHits){
        result = lcm(result, hit);

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
