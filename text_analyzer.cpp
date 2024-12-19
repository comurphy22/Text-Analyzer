#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;
template <typename T>
void printItem(const T& item){
    cout<<": "<<item;
}

void printItem(const char& item){
    if(item == '\t'){
        cout<<": \\t";
    }
    else if(item == '\n'){
        cout<<": \\n";
    }
    else{
        cout<<": "<< item;
    }
}
template <typename K, typename V>
void topTen(const unordered_map<K, V> &map, const unordered_map<K, int> &firstAppearance)
{

    int rank = 0;
    int count = 0;

    vector<pair<K, V>> vect(map.begin(), map.end());  // Directly initialize from the map

    sort(vect.begin(), vect.end(), [&](const pair<K, V>& a, const pair<K, V>& b) {
        if (a.second == b.second) {
            return firstAppearance.at(a.first) < firstAppearance.at(b.first);
        }
        return a.second > b.second;
    });

    for (const auto &elem : vect)
    {
        cout << "No. " << rank;
        printItem(elem.first);
        cout<< "           " << elem.second << endl;
        rank++;
        if (count++ == 9)
            break;
    }
}

template <typename K, typename V>
int numUsed(const unordered_map<K, V> &map)
{
    int numUsed = 10;
    if (map.size() < 10)
        return map.size();
    else
        return numUsed;
}

int main()
{
    int charIndex = 0;
    int wordIndex = 0;
    int numberIndex = 0;
    char ch;
    char prev = 'x';
    string token;
    int number;

    unordered_map<string, int> words;
    unordered_map<string, int> wordsFirst;

    unordered_map<char, int> chars;
    unordered_map<char, int> charsFirst;

    unordered_map<int, int> numbers;
    unordered_map<int, int> numbersFirst;

    while (cin.get(ch))
    {
        if(isalpha(ch))
            ch = tolower(ch);

        if(chars.find(ch) == chars.end()){
            charsFirst[ch] = charIndex++;
        }
        chars[ch]++; // Increment every character count

        if (!isalnum(ch))
        {
            if (!token.empty())
            {
                if (isdigit(token[0]))
                { // Check if the token is a number
                    number = stoi(token);
                    if(numbers.find(number) == numbers.end()){
                        numbersFirst[number] = numberIndex++;
                    }
                    numbers[number]++;
                }
                else
                { // Otherwise, treat it as a word
                    if(words.find(token) == words.end()){
                        wordsFirst[token] = wordIndex++;
                    }
                    words[token]++;
                }
                token.clear();
            }
            prev = 'x';
        }
        else
        {
            if (isalpha(ch))
            {
                if (prev == 'n' && !token.empty())
                {
                    number = stoi(token);
                    if(numbers.find(number) == numbers.end()){
                        numbersFirst[number] = numberIndex++;
                    }
                    numbers[number]++;
                    token.clear();
                }
                prev = 'c';
            }
            else if (isdigit(ch))
            {
                if (prev == 'c' && !token.empty())
                {
                    if(words.find(token) == words.end()){
                        wordsFirst[token] = wordIndex++;
                    }
                    words[token]++;
                    token.clear();
                }
                prev = 'n';
            }
            token += ch;
        }
    }

    if (!token.empty())
    {
        if (isdigit(token[0]))
        {
            number = stoi(token);
            if(numbers.find(number) == numbers.end()){
                numbersFirst[number] = numberIndex++;
            }
            numbers[number]++;
        }
        else
        {

            if(words.find(token) == words.end()){
                wordsFirst[token] = wordIndex++;
            }
            words[token]++;
        }
    }

    cout << "Total " << chars.size() << " different characters, " << numUsed(chars) << " most used character: " << endl;
    topTen(chars, charsFirst);
    cout << "Total " << words.size() << " different words, " << numUsed(words) << " most used words: " << endl;
    topTen(words, wordsFirst);
    cout << "Total " << numbers.size() << " different numbers, " << numUsed(numbers) << " most used numbers: " << endl;
    topTen(numbers, numbersFirst);


    return 0;
}
