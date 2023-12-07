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


vector<char> cardStrengths = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

map<string,int>cardMemo = {};

int getHandStrength(string hand)
{   
    int precalc = cardMemo[hand];
    if(precalc){
        return precalc;
    }
    map<char, int> charCount;
    for(char ch : hand){
        charCount[ch]++;
    }

    int strenght = 1;
    vector<int> counts;
    for (const auto& pair : charCount) {
        counts.push_back(pair.second);
    }

    if(find(counts.begin(), counts.end(), 5)!= counts.end()){
        //five kind
        strenght = 7;
    }
    else if(find(counts.begin(), counts.end(), 4)!= counts.end()){
        // four kind
        strenght = 6;
    }
    else if(find(counts.begin(), counts.end(), 3)!= counts.end() && 
    (find(counts.begin(), counts.end(), 2)!= counts.end())){
        // full house
        strenght = 5;
    }
    else if(find(counts.begin(), counts.end(), 3)!= counts.end() && 
    (find(counts.begin(), counts.end(), 2)== counts.end())){
        // three kind
        strenght = 4;
    }
    else if(count(counts.begin(), counts.end(), 2) > 1){
        // two  pair
        strenght = 3;
    }
    else if(count(counts.begin(), counts.end(), 2) == 1){
        // pair
        strenght = 2;
    }
    // high card

    cardMemo[hand] = strenght;

    return strenght;
}



int part_1(ifstream &inputFile) 
{
    string line;
    int result = 0;

    vector<pair<string, int>> hands = {};

    while ( getline(inputFile, line) ) {
        istringstream lineStream(line);
        string hand;
        int bid;
        lineStream>>hand;
        lineStream>>bid;
        hands.push_back({ hand, bid});
    }

    sort(hands.begin(), hands.end(), [](const auto &a, const auto &b) {
        int strenghtA = getHandStrength(a.first);
        int strenghtB = getHandStrength(b.first);
        if(strenghtA == strenghtB){
            for(int i = 0; i < a.first.size(); ++i){
                auto secondaryA = find(cardStrengths.begin(), cardStrengths.end(), a.first[i]);
                auto secondaryB = find(cardStrengths.begin(), cardStrengths.end(), b.first[i]);
                if (secondaryA != secondaryB){
                    return secondaryA > secondaryB;
                }
            }
        }
        return strenghtA < strenghtB;
    });

    for (int i = 0; i < hands.size();++i){
        result +=  hands[i].second * (i+1);
    }

    return result;
}

vector<char> cardStrengthsWithJoker = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

map<string,int>cardMemoJoker = {};

int getHandStrengthWithJoker(string hand)
{  
    int precalc = cardMemo[hand];
    if(precalc){
        return precalc;
    }
     map<char, int> charCount;
    int jokers = 0;
    for(char ch : hand){
        charCount[ch]++;
        if(ch == 'J'){
            jokers++;
        }
    }
    vector<int> counts;
    for (const auto& pair : charCount) {
        counts.push_back(pair.second);
    }

    int strength = 1;
    if(find(counts.begin(), counts.end(), 5)!= counts.end()){
        //five kind
        strength = 7;
    }
    else if(find(counts.begin(), counts.end(), 4)!= counts.end()){
        // four kind
        if (jokers> 0){
            strength = 7;
        } else {
            strength = 6;
        }
    }
    else if(find(counts.begin(), counts.end(), 3)!= counts.end() && 
    (find(counts.begin(), counts.end(), 2)!= counts.end())){
        switch(jokers){
        case 3:
            //five kind
            strength = 7;
            break;
        case 2:
            // five kind
            strength = 7;
            break;
        default:
            strength = 5;
            break;
        }
    }
    else if(find(counts.begin(), counts.end(), 3)!= counts.end() && 
            (find(counts.begin(), counts.end(), 2)== counts.end())){
        // three kind
        switch(jokers){
            case 3:
                strength = 6;
                break;
            case 2:
                //five kind
                strength = 7;
                break;
            case 1:
                // four kind is better than full house
                strength = 6;
                break;
            default:
                strength = 4;
                break;
            }
    }
    else if(count(counts.begin(), counts.end(), 2) > 1){
        // two  pair
         switch(jokers){
            case 2:
                // four kind is better than full house
                strength = 6;
                break;
            case 1:
                // full house
                strength = 5;
                break;
            default: 
                strength = 3;
                break;
         }
        
    }
    else if(count(counts.begin(), counts.end(), 2) == 1){
        // pair
         switch(jokers){
            case 2: 
                // three kind
                strength = 4;
                break;
            case 1:
                // three kind
                strength = 4;
                break;
            default: 
                strength = 2;
                break;
         }
    } else {
        // single joker makes a pair;
        if(jokers == 1){
            strength = 2; 
        }
    }

    if(jokers > 1  && strength==5 ){
        cout << hand << ": " << strength << endl;
    }
    cardMemo[hand] = strength;
    return strength;
}


int part_2(ifstream &inputFile) 
{
    string line;
    int result = 0;

    vector<pair<string, int>> hands = {};

    while ( getline(inputFile, line) ) {
        istringstream lineStream(line);
        string hand;
        int bid;
        lineStream>>hand;
        lineStream>>bid;
        hands.push_back({ hand, bid});
    }

    sort(hands.begin(), hands.end(), [](const auto &a, const auto &b) {
        int strenghtA = getHandStrengthWithJoker(a.first);
        int strenghtB = getHandStrengthWithJoker(b.first);
        if(strenghtA == strenghtB){
            for(int i = 0; i < a.first.size(); ++i){
                auto secondaryA = find(cardStrengthsWithJoker.begin(), cardStrengthsWithJoker.end(), a.first[i]);
                auto secondaryB = find(cardStrengthsWithJoker.begin(), cardStrengthsWithJoker.end(), b.first[i]);
                if (secondaryA != secondaryB){
                    return secondaryA > secondaryB;
                }
            }
        }
        return strenghtA < strenghtB;
    });

    for (int i = 0; i < hands.size();++i){
        result +=  hands[i].second * (i+1);
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