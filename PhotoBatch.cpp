#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

string toLower(string str) {
 
	transform(begin(str), end(str), begin(str), [](unsigned char c) {
		return tolower(c);
		});

	return str;
}

class ArgumentParser {
public:
	void registerFlag(const string& flag) {
		
		if (flag.empty()) {
			return;
		}

		_flags[flag] = false;
	}

	bool getFlag(const string& flag) const {
		
		if (!flag.empty()) {
			//o metodo find vai retornar outro mapa, entao nesse caso eh melhor utilizar o AUTO
			auto flagIt = _flags.find(flag);

			//verificando se o conjunto chave-valor nao esta fora dos parametros aceitos (registrados no registerFlag)
			//TODO - verificar se essa validacao pode ser melhorada (usar o at e tratar exception)
			if (flagIt != end(_flags)) {
				//retornando o valor, e nao a chave
				return flagIt->second;
			}
		}
		
		return false;
	}

	void parse(int argc, char* argv[]) {

		
		if (argc > 1) {
			for (int i = 0; i < argc; i++) {

				string arg = toLower(argv[i]);

				//TODO - melhorar validacao pq nao gostei
				if (arg.length() > 3) {
					if (arg[0] == '-' && arg[1] == '-') {
						arg = arg.substr(2);

						if (arg.find_first_of('=') != string::npos) {
							//eh opcao
						}
						else {

							//TODO - melhorar validacao
							auto flagIt = _flags.find(arg);

							if (flagIt != end(_flags)) {
								flagIt->second = true;
							}
						}
					}
				}
			}
		}
	}
private:
	map<string, bool> _flags;
};

int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "pt_BR");

	ArgumentParser argumentParser;

	argumentParser.registerFlag("rename");
	argumentParser.registerFlag("convert");
	argumentParser.registerFlag("resize");
	argumentParser.registerFlag("scale");

	argumentParser.parse(argc, argv);

	cout << boolalpha << "RENAME - " << argumentParser.getFlag("rename") << endl;
	cout << boolalpha << "CONVERT - " << argumentParser.getFlag("convert") << endl;
	cout << boolalpha << "RESIZE - " << argumentParser.getFlag("resize") << endl;
	cout << boolalpha << "SCALE - " << argumentParser.getFlag("scale") << endl;

	//getchar(); //usada para pausar o programa antes do final

	return 0;
}