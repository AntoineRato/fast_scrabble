#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


void create_vector ( std::ifstream & file, std::vector < std::string > & v ) {
	if ( file ) {
		std::string line;
		std::string s;
		while ( std::getline ( file, line ) ) {
            s=line;
            if (!line.empty() && line[line.size() - 1] == '\r')
               line.erase(line.size() - 1);
                transform(line.begin(), line.end(), line.begin(), ::tolower);
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
	std::cin >> str;
	valUser.push_back(str);
	return str;
}

void search_value ( const std::string & value, const std::vector < std::string > & v ) {
	for ( std::string t : v ) {
		if ( t.find ( value ) == std::string::npos ) {

		}
		else {
			std::cout << t << std::endl;
		}

	}
}

int main (int argc, char *argv[]) {
    if ( argc > 0 ) {
        std::cout << argv [ 0 ] << std::endl;
    }
    else {
        //std::cout << "Pas de parametre" << std::endl;
    }

    std::ifstream file { argv [ 2 ] };
    //std::ifstream file { "words_alpha.txt" };
    std::vector < std::string > v;
    create_vector ( file, v ); // Remplir le tableau
    std::vector < std::string > valUser {};
    do
    {
        const std::string value { value_user ( valUser ) };
        search_value ( value, v ); // Recherche la valeur "aaa" dans le tableau
    }while(true);

}
