#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>

/* Antoine Rato */

using namespace std;

string convertToLower_And_Sort(string word)
{
    list<char> listOfChar;
    char character;

    for(string::iterator i = word.begin(); i != word.end(); ++i)
    {
        character = tolower(*i);
        if (character >= 'a' && character <= 'z')
            listOfChar.push_back(character);
    }

    listOfChar.sort();

    stringstream streamString;
    for(list<char>::iterator i = listOfChar.begin(); i != listOfChar.end(); ++i)
        streamString << *i;

    return streamString.str();
}

int main(int argc, char *argv[])
{
    multimap<string, string> multimapOfDictionary;
    string nameOfDictionary = argv[1];

    ifstream dictionary(nameOfDictionary.c_str(), ios::in);

    //Initialisation of the
    if (dictionary.fail())
    {
        cout << "This dictionary doesn't exist." << endl;
        return -1;
    }
    else
    {
        string line;
        while(getline(dictionary, line))
        {
            multimapOfDictionary.insert(pair<string,string>(convertToLower_And_Sort(line), line));
        }
    }

    while(true)
    {
        string input;
        cin >> input;
        input = convertToLower_And_Sort(input);

        pair <multimap<string, string>::iterator, multimap<string, string>::iterator> pairIterator = multimapOfDictionary.equal_range(input);

        for (multimap<string, string>::iterator i = pairIterator.first; i != pairIterator.second; ++i)
        {
            cout << i->second << endl;
        }
    }

    dictionary.close();

    return 0;
}