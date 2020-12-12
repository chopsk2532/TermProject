#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include "File.h"

using namespace std;


int main() {

	fstream myfile;
	File file;

	file.openFile(myfile);
	file.fileVector();
	file.print_txt(myfile);

	

}
