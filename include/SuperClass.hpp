#include <vector>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;


class SingleBoxPreference {

	private:
		int val;
		char *status;
		bool on,isChar;
		string path;
		void init();

	public:
		SingleBoxPreference(string path);
		bool stat();
		void sSwitch();
		void write(int nVal);
		int getValue();
		string stat();

		~SingleBoxPreference();
		
};

class ListPreference {

	private:
		vector <int> sVec;
		vector< pair<string,int> > pVec;
		ifstream fin;
		bool SingleFile;

	public:
		ListPreference(string path);
		unsigned int getSize();
		void printVector();
		void writeVector();
};