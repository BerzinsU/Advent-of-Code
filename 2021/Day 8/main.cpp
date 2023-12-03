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

int part_1() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    string line;
    int simpleDigitCount = 0;

    while ( getline(inputFile, line) ) {
        // istringstream number_line_stream(line);
        size_t delimiterPos = line.find("|");
        line = line.substr(delimiterPos + 1);
        line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");

        istringstream line_stream(line);
        string substring;

        while(getline(line_stream, substring, ' ')){
            if(substring.size() == 2 ||  // "1"
                substring.size() == 3 || // "7"
                substring.size() == 4 || // "4"
                substring.size() == 7) // "8 "
            {
                simpleDigitCount++;
            }
        }
    }


    inputFile.close();
    return simpleDigitCount;
}

vector<string> getStringsByLength(set<string> strings, int length){
    vector<string> result = {};
    for(const string &str: strings){
        if(str.length() == length ){
            result.push_back(str);
        }
    }
    return result;
}

char findDiffChar(string str1, string str2){
    for (char c: str1)
   {
      if (str2.find(c) != std::string::npos){
        return c;
      }
   }
    return '-1';
}

std::set<char> findDifferingChars(const std::string& str1, const std::string& str2) {
    std::set<char> differingChars;

    for (char ch : str1) {
        if (str2.find(ch) == std::string::npos) {
            differingChars.insert(ch);
        }
    }

    for (char ch : str2) {
        if (str1.find(ch) == std::string::npos) {
            differingChars.insert(ch);
        }
    }

    return differingChars;
}

template <typename T>
void removeValue(std::vector<T>& vec, const T& valueToRemove) {
    vec.erase(std::remove(vec.begin(), vec.end(), valueToRemove), vec.end());
}

int findStringInVector(const vector<string>& stringVec, const string& target) {
    int position = 0;
    for (const std::string& str : stringVec) {
        if (str == target) {
            return position;  // Found the target string, return its position
        }
        position++;
    }

    // If the string is not found, return -1
    return -1;
}

int part_2() 
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    string line;
    int totalSum = 0;


    while ( getline(inputFile, line) ) {
        istringstream line_stream(line);

        size_t delimiterPos = line.find("|");
        string input = line.substr(0, delimiterPos);
        string output = line.substr(delimiterPos + 2);

        istringstream input_stream(input);
        istringstream output_stream(output);
        string digit; 
        set<string> inputDigits;
        vector<string> outputDigits;
        while(getline(input_stream, digit, ' ')){
            sort(digit.begin(), digit.end()); 
            inputDigits.insert(digit);
        }
        string outdigit; 
        while(getline(output_stream, outdigit, ' ')){
            sort(outdigit.begin(), outdigit.end()); 
            outputDigits.push_back(outdigit);
        }

        /////////////////////////////////////////////////////////

        string one =getStringsByLength(inputDigits, 2 ).front();
        string four =getStringsByLength(inputDigits, 4 ).front();
        string seven =getStringsByLength(inputDigits, 3 ).front();
        string eight =getStringsByLength(inputDigits, 7 ).front();
        string two,three,five,six,nine,zero;

        char a,b,c,d,e,f,g;

        a =  *findDifferingChars( seven, one).begin();

        string fourSeven = four+seven;
        set<char> fourSevenSet(fourSeven.begin(), fourSeven.end());
        vector<string> sixSegmentDigits = getStringsByLength(inputDigits, 6);

        fourSeven = "";
        for (char ch : fourSevenSet) {
            fourSeven += ch;
        }

        for(string &str: sixSegmentDigits){
            set<char> diff = findDifferingChars( str, fourSeven);
            if(diff.size() == 1){
                nine = str;
                g = *diff.begin();
            }
        }

        e = *findDifferingChars( nine, eight).begin();
        
        string almostZero = one;
        almostZero.push_back(a);
        almostZero.push_back(g);
        almostZero.push_back(e);

        for(string &str: sixSegmentDigits){
            set<char> diff = findDifferingChars( str, almostZero);
            if(diff.size() == 1){
                zero = str;
                b = *diff.begin();
            }
        }
        removeValue(sixSegmentDigits, nine);
        removeValue(sixSegmentDigits, zero);
        six = sixSegmentDigits.front();

        d = *findDifferingChars( zero, eight).begin();

        string almostTwo({a,b,d,g});

        vector<string> fiveSegmentDigits = getStringsByLength(inputDigits, 5);
        for(string &str: fiveSegmentDigits){
            set<char> diff = findDifferingChars( str, almostTwo);
            if(diff.size() == 1){
                five = str;
                f = *diff.begin();
            }
        }
        removeValue(fiveSegmentDigits, five);


        for(string &str: fiveSegmentDigits){
            set<char> diff = findDifferingChars( str, nine);
            if(diff.size() == 1){
                three = str;
            }
        }
        removeValue(fiveSegmentDigits, three);
        two = fiveSegmentDigits.front();

        c = *findDifferingChars( two, one).begin();

        vector<char> key = {a,b,c,d,e,f,g};
        vector<string> digits ={zero,one, two, three, four, five, six, seven, eight, nine};

        vector<string> outputDecode = {};
        for(string str:outputDigits){
            int location = findStringInVector(digits,str);
            outputDecode.push_back(to_string(location));
            
        }
        string outputString = "";
        for (string& str : outputDecode) {
            outputString += str;
        }
        // cout<< outputString << endl;
        totalSum += stoi(outputString);
    }
    


    inputFile.close();
    return totalSum;
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
