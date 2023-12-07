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
    long long int result = 0;

    vector<long long int> positions;
    vector<long long int> savedPositions;

    getline(inputFile, line);
    size_t delimiterPos = line.find(":");
    string seeds = line.substr(delimiterPos+1);  

    istringstream stream(seeds);
    string seed;
    while(getline(stream, seed, ' ')) {
        if(seed.size()>0) {
            long long int number = stoull(seed,nullptr, 10);
            savedPositions.push_back(number);
        }
    }

    while ( getline(inputFile, line) ) {
        if(line.size() == 0) {
            continue;
        }

        size_t delimiterPos = line.find(":");
        if(delimiterPos != string::npos ) {
            //map change
            positions = savedPositions;
        } else {
            long long int destination, source, range;
            istringstream stream(line);
            stream >> destination;
            stream >> source;
            stream >> range;
            
            for(int i = 0; i< positions.size(); ++i) {
                long long int position = positions[i];
                if(position >= source && position < source + range){
                    long long int offset = destination - source;
                    savedPositions[i] = position + offset;
                }
            }
        }
    }
    result = *min_element(savedPositions.begin(), savedPositions.end());

    return result;
}




vector<long long int> splitRange(long long int from, long long int range) {
    vector<long long int> ranges = {};
    ranges.push_back(from);
    ranges.push_back(range/4);
    ranges.push_back(from + range/4 +1);
    long long int endRange = range/4-2+(range % 4);
    if(endRange < 1) {
        endRange =1;
    }
    ranges.push_back(endRange);
    return ranges;
}

std::vector<long long> split_range(long long start, long long end) {
    if (start > end) {
        std::cerr << "Invalid range: start should be less than or equal to end." << std::endl;
        // You might want to handle the error in a different way based on your requirements.
        // Here, I'm returning an empty vector.
        return {};
    }

    long long range_size = (end - start + 1) / 4;

    std::vector<long long> batches;

    batches.push_back(start);
    batches.push_back(start + range_size - 1);
    batches.push_back(start + range_size);
    batches.push_back(start + 2 * range_size - 1);
    batches.push_back(start + 2 * range_size);
    batches.push_back(start + 3 * range_size - 1);
    batches.push_back(start + 3 * range_size);
    batches.push_back(end);

    return batches;
}



long long int part_2(ifstream &inputFile) 
{
    string line;
    long long int result = 0;

    vector<long long int> positions;
    vector<long long int> savedPositions;
    vector<long long int> savedSeedPairs;
    vector<long long int> seedPairs;
    vector<vector<vector<long long int>>> maps;
   
    getline(inputFile, line);
    size_t delimiterPos = line.find(":");
    string seeds = line.substr(delimiterPos+1);  

    istringstream stream(seeds);
    string seed;
    while(getline(stream, seed, ' ')) {
        if(seed.size()>0) {
            long long int number = stoull(seed,nullptr, 10);
            savedSeedPairs.push_back(number);
        }
    }
    int mapIndex = -1;
    while ( getline(inputFile, line) ) {
        if(line.size() == 0) {
            continue;
        }
        size_t delimiterPos = line.find(":");

        if(delimiterPos != string::npos ) {
            //map change
            ++mapIndex;
            maps.push_back({});
        } else {
            long long int destination, source, range;
            istringstream stream(line);
            stream >> destination;
            stream >> source;
            stream >> range;
            maps[mapIndex].push_back({destination, source, range});
        }
    }

    vector<long long int> smallestValues = {};

    
    
    return *min_element(smallestValues.begin(), smallestValues.end());
}

long long int part_2b(ifstream &inputFile) 
{
    string line;
    long long int result = 0;

    vector<long long int> positions;
    vector<long long int> savedPositions;
    vector<long long int> savedSeedPairs;
    vector<long long int> seedPairs;
    vector<vector<vector<long long int>>> maps;
   
    getline(inputFile, line);
    size_t delimiterPos = line.find(":");
    string seeds = line.substr(delimiterPos+1);  

    istringstream stream(seeds);
    string seed;
    while(getline(stream, seed, ' ')) {
        if(seed.size()>0) {
            long long int number = stoull(seed,nullptr, 10);
            savedSeedPairs.push_back(number);
        }
    }
    int mapIndex = -1;
    while ( getline(inputFile, line) ) {
        if(line.size() == 0) {
            continue;
        }
        size_t delimiterPos = line.find(":");

        if(delimiterPos != string::npos ) {
            //map change
            ++mapIndex;
            maps.push_back({});
        } else {
            long long int destination, source, range;
            istringstream stream(line);
            stream >> destination;
            stream >> source;
            stream >> range;
            maps[mapIndex].push_back({destination, source, range});
        }
    }

    vector<long long int> smallestValues = {};
    long long int smallestValueSoFar = LLONG_MAX;

    int pairCount = 0;
    size_t batchsize = 50000000;
    for(int idp=0; idp< savedSeedPairs.size(); idp = idp +2){
        cout << "Running pair " << ++pairCount << ": " << savedSeedPairs[idp]<<  ":" << savedSeedPairs[idp+1] << endl;
        cout << "Batches: " << savedSeedPairs[idp+1]/batchsize << endl;
        
        bool finished = false;
        int itter = 0;
       
        
        savedPositions={};
        size_t batchCounter = 0; 
        for(int j=0; j<savedSeedPairs[idp+1]+1; ++j){
            ++batchCounter;
            if(batchCounter < batchsize && j<savedSeedPairs[idp+1]){
                savedPositions.push_back(savedSeedPairs[idp]+j);
            }
            else {
                itter +=batchsize; 
                if(itter % batchsize == 0){
                    cout << "Running batch " << itter/batchsize <<" with size: " << batchCounter <<endl;
                }

                for(vector<vector<long long int>> map: maps){
                    positions.resize(savedPositions.size());
                    positions = savedPositions;
                    for(vector<long long int> mapLine: map){
                        long long int destination, source, range;
                        destination = mapLine[0];
                        source = mapLine[1];
                        range = mapLine[2];
                        
                        for(int i = 0; i< positions.size(); ++i) {
                            long long int position = positions[i];
                            if(position >= source && position < source + range){
                                long long int offset = destination - source;
                                savedPositions[i] = position + offset;
                            }
                        }
                    }
                }
                long long int minVal = *min_element(savedPositions.begin(), savedPositions.end());
                if(minVal<smallestValueSoFar){
                    smallestValueSoFar = minVal;
                }
                batchCounter = 0;
                savedPositions = {};
            }
        }
        cout << "Smallest so far: " << smallestValueSoFar << endl <<endl;
    }
    
    return smallestValueSoFar;
}


// 99751240 Running pair 5: 1018893962:410959790

//input 2 
// 50855035

int main()
{   
    ifstream inputFile("input.txt");
    auto start = chrono::high_resolution_clock::now();
    
    int result = 0;
    
    // result = part_1(inputFile);
    // cout << endl << "Part 1: " << result << endl <<endl;

    inputFile.clear();
    inputFile.seekg(0);

    result = part_2b(inputFile);
    cout << "Part 2: " << result << endl;
    // 99751240 Running pair 5: 1018893962:410959790

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Time taken: " << duration.count()/1e+6 << " seconds" << endl;
    inputFile.close();

    // string dummy;
    // cout << "Enter to continue..." << endl;
    // getline(cin, dummy);

    return 0;
}
