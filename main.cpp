#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>

/* Antoine Rato */

using namespace std;

// source: https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
std::istream &safeGetline(std::istream &is, std::string &t) {
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf *sb = is.rdbuf();

    for (;;) {
        int c = sb->sbumpc();
        switch (c) {
            case '\n':
                return is;
            case '\r':
                if (sb->sgetc() == '\n')
                    sb->sbumpc();
                return is;
            case EOF:
                // Also handle the case when the last line has no line ending
                if (t.empty())
                    is.setstate(std::ios::eofbit);
                return is;
            default:
                t += (char) c;
        }
    }
}

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
    if(argc != 2)
    {
        cout << "Add a dictionary on input." << endl;
        return -1;
    }

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
        while(!safeGetline(dictionary, line).eof())
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