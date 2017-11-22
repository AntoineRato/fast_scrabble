#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <algorithm>


using namespace std;

// Fonction toute faite trouvé sur stackoverflow


/*void create_vector ( std::ifstream & file, std::vector < std::string > & v ) {
	if ( file ) {
		std::string line;
		while ( std::getline ( file, line ) ) {
			v.push_back ( line );
		}
	}
	else {
		std::cerr << "Erreur d'ouverture du fichier" << std::endl;
	}
}

const std::string value_user ( std::vector < std::string > & valUser ) {
	std::string str;
	std::string valTemp;
	for(auto v : valUser) {
        valTemp += v;
	}
	std::cout << "Entrer une chaine de caractere : " << valTemp;
	std::cin >> str;
	valUser.push_back(str);
	return valTemp+str;
}

void search_value ( const std::string & value, const std::vector < std::string > & v ) {
	for ( std::string t : v ) {
		if ( t.find ( value ) == std::string::npos ) {

		}
		else {
			std::cout << t << std::endl;
		}
	}
}*/


std::istream &safeGetline(std::istream &is, std::string &t) {
    t.clear();

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

                if (t.empty())
                    is.setstate(std::ios::eofbit);
                return is;
            default:
                t += (char) c;
        }
    }
}

int main (int argc, char * argv[])
{
    std::string word;
    std::string wordConvert;
    std::string valUSer;
    std::multimap<string, string>::iterator it2;

    // if ( argc > 0 ) {
    //     std::cout << argv [ 0 ] << std::endl;
    // }

    std::ifstream file { argv [ 2 ]};

    multimap<string, string> dictionnary;
    //FORMAT DOS ET UNIX
    if(file) {

        while (!safeGetline(file, word).eof()){
            wordConvert = word;
            transform(wordConvert.begin(), wordConvert.end(), wordConvert.begin(), ::tolower);
            sort(wordConvert.begin(), wordConvert.end());
            dictionnary.insert(make_pair(wordConvert, word));
        }
    }
    while(true) {

        cin >> valUSer;

        transform(valUSer.begin(), valUSer.end(), valUSer.begin(), ::tolower);

        sort(valUSer.begin(), valUSer.end());

        pair<multimap<string,string>::iterator, multimap<string,string>::iterator> it1;

        it1 = dictionnary.equal_range(valUSer);

        for(it2 = it1.first; it2 != it1.second; ++it2){
            cout<<it2->second<<endl;
        }
    }
    return 0;
}
