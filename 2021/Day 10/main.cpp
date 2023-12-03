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
#include <stack>
#include <unordered_set>
#include <unordered_map>

using namespace std;

char getClosingChar(char openChar) {
    static const unordered_map<char, char> closingChars = {
        {'{', '}'},
        {'(', ')'},
        {'<', '>'},
        {'[', ']'}
    };

    auto it = closingChars.find(openChar);
    if (it != closingChars.end()) {
        return it->second;
    } else {
        // If the character is not one of the opening characters, return '\0' or handle it accordingly
        return '\0';
    }
}

int part_1() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    string line;

    
    unordered_set<char> openingTags = {'{', '(', '<', '['};
    stack<char> openedTags = {};
    int points = 0;

    while ( getline(inputFile, line) ) {
        for (char c : line) {
            if (openingTags.find(c) != openingTags.end()) {
                openedTags.push(c);
            } else {
                if(getClosingChar(openedTags.top()) == c){
                    openedTags.pop();
                }
                else {
                    //corruption
                    switch (c)
                    {
                    case ')':
                        points += 3;
                        break;
                    case ']':
                        points += 57;
                        break;
                    case '}':
                        points += 1197;
                        break;
                    case '>':
                        points += 25137;
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }

        }
    }



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
    string line;

    
    unordered_set<char> openingTags = {'{', '(', '<', '['};
    vector<long long> points = {};

    while ( getline(inputFile, line) ) {
        stack<char> openedTags = {};
        bool isCorrupted = false;
        for (char c : line) {
            if (openingTags.find(c) != openingTags.end()) {
                openedTags.push(c);
            } else {
                if(getClosingChar(openedTags.top()) == c){
                    openedTags.pop();
                }
                else {
                    //corrupted line
                    isCorrupted = true;
                    break;
                }
            }

        }
        if(openedTags.size()>0 && !isCorrupted){
            long long linePoints = 0;
            while(!openedTags.empty()) {
                char closingTag = getClosingChar(openedTags.top());
                 switch (closingTag)
                    {
                    case ')':
                        linePoints = (linePoints *5) + 1;
                        break;
                    case ']':
                        linePoints = (linePoints *5) + 2;
                        break;
                    case '}':
                        linePoints = (linePoints *5) + 3;
                        break;
                    case '>':
                        linePoints = (linePoints *5) + 4;
                        break;
                    default:
                        break;
                    }

                openedTags.pop();
            }
            points.push_back(linePoints);
        }
    }

    sort(points.begin(), points.end());

    int score = points[points.size()/2];

    inputFile.close();
    return score;
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
