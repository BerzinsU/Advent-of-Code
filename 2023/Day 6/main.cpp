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


using namespace std;

int part_1(ifstream &inputFile) 
{
    string line;
    int result = 1;

    vector<double> times;
    vector<double> distances;

    getline(inputFile, line);
    size_t delimiterPos = line.find(":");
    string timesS = line.substr(delimiterPos+1);  

    istringstream stream(timesS);
    string time;
    while(getline(stream, time, ' ')) {
        if(time.size()>0) {
             double timeI = stod(time);
            times.push_back(timeI);
        }
    }

    getline(inputFile, line);
    delimiterPos = line.find(":");
    string distanceS = line.substr(delimiterPos+1); 

    stream = istringstream(distanceS);
    string distance;
    while(getline(stream, distance, ' ')) {
        if(distance.size()>0) {
             double distanceI = stod(distance);
            distances.push_back(distanceI);
        }
    }

    for(int i = 0; i < times.size(); ++i ){
        double time = times[i];
        double record = distances[i];

        double s = sqrt((time*time)/4.0 - record);

        int x1 = time/2-s;
        int x2 = ceil(time/2 + s -1);
        result *= x2 - x1;
    }
    return result;
}


int part_2(ifstream &inputFile) 
{
    string line;
    long long int result = 1;

    long double raceTime;
    long double raceDistance;

    getline(inputFile, line);
    size_t delimiterPos = line.find(":");
    string timesS = line.substr(delimiterPos+1);  

    istringstream stream(timesS);
    string time;
    string timeB;
    while(getline(stream, time, ' ')) {
        if(time.size()>0) {
            timeB += time;
        }
    }
    raceTime = stold(timeB);

    getline(inputFile, line);
    delimiterPos = line.find(":");
    string distanceS = line.substr(delimiterPos+1); 

    stream = istringstream(distanceS);
    string distance;
    string distanceB;
    while(getline(stream, distance, ' ')) {
        if(distance.size()>0) {
            distanceB += distance;
        }
    }
    raceDistance = stold(distanceB);
    double s = sqrt((raceTime*raceTime)/4.0 - raceDistance);

    int x1 = raceTime/2-s;
    int x2 = ceil(raceTime/2 + s -1);
    result = x2 - x1;

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
