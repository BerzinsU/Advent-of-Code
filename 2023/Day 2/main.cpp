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


int part_1() 
{
    ifstream inputFile("input.txt");

    string line;
    int result = 0;
    int maxRed = 12;
    int maxGreen = 13;
    int maxBlue = 14;

    while (getline(inputFile, line)) {
        size_t delimiterPos = line.find(":");
        string gameName = line.substr(0, delimiterPos);
        string games = line.substr(delimiterPos+2);

        istringstream line_stream(games);
        string gameString;
        bool gamePossible = true;

        while (getline(line_stream, gameString, ';')) {
            istringstream point_stream(gameString);
            string cubesString;

            while (getline(point_stream, cubesString, ',')) {
                istringstream cube_stream(cubesString);
                string color = "";
                int count = 0;

                cube_stream >> count;
                cube_stream >> color;

                if(color == "red" && count > 12){
                    gamePossible = false;
                }
                else if(color == "green" && count > 13){
                    gamePossible = false;
                }
                else if(color == "blue" && count > 14){
                    gamePossible = false;
                }

            }
        }

        if(gamePossible){
            size_t delimiterPos = gameName.find(" ");
            int gameNumber = stoi(gameName.substr(delimiterPos));
            result += gameNumber;
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
   
    while (getline(inputFile, line)) {
        size_t delimiterPos = line.find(":");
        string games = line.substr(delimiterPos+2);

        istringstream line_stream(games);
        string gameString;

        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;

        while (getline(line_stream, gameString, ';')) {
            istringstream point_stream(gameString);
            string cubesString;

            while (getline(point_stream, cubesString, ',')) {
                istringstream cube_stream(cubesString);
                string color = "";
                int count = 0;

                cube_stream >> count;
                cube_stream >> color;

                if(color == "red" && count > maxRed){
                    maxRed = count;
                }
                else if(color == "green" && count > maxGreen){
                    maxGreen = count;
                }
                else if(color == "blue" &&  count > maxBlue){
                    maxBlue = count;
                }
            }
        }

        int gamePower = (maxRed * maxGreen * maxBlue );
        result += gamePower;
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
