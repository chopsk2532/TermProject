#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

class File {

	string testfile;
	vector<string> storeV2;
	vector<vector<string>> v;
	int LineCount;
	
	void seperLine() {
		for (int k = 0; k < 80; k++) {
			cout << "-";
		}
		cout << endl;
	}


public:

	void openFile(fstream& myfile) {
		myfile.open("test.txt");

		if (myfile.is_open()) {
			while (!myfile.eof()) {	// text파일의 모든 글자를 한번에 string에 저장

				myfile >> testfile;
				storeV2.push_back(testfile);
			}

		}

		else {
			cout << "Can't find the file" << endl;
		}
		myfile.close();
	}


	void fileVector() {

		v.assign(100, vector<string>(0, ""));

		int ct = 0; //현재 글자
		int vectorNum = 0;
		int vectorCt = 0;
		int length = 0;


		while (ct < (int)storeV2.size()) {

			length = length + storeV2[ct].size();

			v[vectorNum].push_back(storeV2[ct]);

			v[vectorNum].push_back(" ");

			vectorCt += 2;
			length++;
			ct++;




			if (length >= 75) { //byte가 75를 넘는다면

				length = length - 1;

				if (length > 75) {

					//마지막 단어와 공백을 ""으로 바꾸고
					v[vectorNum][vectorCt - 2] = "";
							 
					//마지막 단어를 다시 저장하기위해 back

					vectorCt = 0;	//다음 벡터 시작
					length = 0;
					ct--;
					vectorNum++;

				}

				else {


					vectorCt = 0;	//다음 벡터 시작
					length = 0;
					vectorNum++;

				}

			}
		}
		LineCount = vectorNum;
	}

	void print_txt(fstream& myfile) {

		int line = 0;
		int page = 1;
		int lastPage = (int)(LineCount / 20) + 1;
		int errorcode = 0;

		while (1) {
			cout << setw(2) << line + 1 << "| ";
			if (line < (int)(v.size())) {							//20줄씩 출력
				for (int j = 0; j < (int)v[line].size(); j++) {
					cout << v[line][j];
				}
			}

			cout << endl;
			line++;

			if ((line > 0) && (line % 20) == 0) {

				seperLine();

				cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << endl;

				seperLine();

				//에러 메시지 출력창
				cout << errorMessage(errorcode) << endl;

				seperLine();

				input_command(myfile, page, lastPage, line, errorcode);
				
			}
		}
	}


private:
	void input_command(fstream& myfile, int& page, int lastPage, int& line, int& errorcode) {
		
		string command;

		cout << "입력:";
		getline(cin, command);
		seperLine();

		int a = 0;

		switch (command[0]) {

		case 'n':
			if (command.size() > 1) {
				errorcode = 10;
				line = line - 20;
				break;
			}
			if ((page) >= lastPage) {
				errorcode = 1;
				line = line - 20;
				break;
			}
			page++;
			errorcode = 0;
			break;

		case 'p':
			if (command.size() > 1) {
				errorcode = 10;
				line = line - 20;
				break;
			}
			if (line == 20) {
				errorcode = 2;
				line = line - 20;
				break;
			}
			page--;
			errorcode = 0;
			line = line - 40;
			break;

		case 'i':
			a = input_I(command);
			if (a >= 0) {
				if (a == 3) {
					errorcode = 3;
					line = line - 20;
				}
				else if (a == 4) {
					errorcode = 4;
					line = line - 20;
				}
				else if (a == 0) {
					errorcode = 10;
					line = line - 20;
				}
				else {
					fileVector();
					line = line - 20;
					errorcode = 0;
					break;
				}
			}
			break;

		case 'd':
			a = input_d(command);
			if (a >= 0) {
				if (a == 3) {
					errorcode = 3;
					line = line - 20;
				}
				else if (a == 5) {
					errorcode = 5;
					line = line - 20;
				}
				else if (a == 6) {
					errorcode = 6;
					line = line - 20;
				}
				else if (a == 0) {
					errorcode = 10;
					line = line - 20;
				}
				else {
					fileVector();
					line = line - 20;
					errorcode = 0;
				}
				break;
			}
			break;
		case 'c':
			a = input_c(command);
			if (a >= 0) {
				if (a == 3) {
					errorcode = 3;
					line = line - 20;
				}
				else if (a == 7) {
					errorcode = 7;
					line = line - 20;
				}
				else if (a == 0) {
					errorcode = 10;
					line = line - 20;
				}
				else {
					fileVector();
					line = line - 20;
					errorcode = 0;
				}
				break;
			}
			break;
		case 's':
			a = input_s(command);
			if (a >= 0) {
				if (a == 4) {
					errorcode = 4;
					line = line - 20;
				}
				else if (a == 7) {
					errorcode = 7;
					line = line - 20;
				}
				else if (a == 0) {
					errorcode = 10;
					line = line - 20;
				}
				else {
					fileVector();
					line = line - 20;
					errorcode = 0;
				}
				break;
			}
			break;
		case 't':
			if (command.size() > 1) {
				errorcode = 10;
				line = line - 20;
				break;
			}
			else if (input_t(myfile) == 0) {
				errorcode = 10;
				line = line - 20;
				break;
			}
			else {
				exit(0);
				break;
			}

		}
	}

	int input_I(string command) {				// i 명령어

		int first = 0;
		int second = 0;
		string third = "";

		if (command.size() < 2) {
			return 0;
		}


		string a;
		a.resize(command.size() - 3);
		for (int i = 2; i < (int)command.size() - 1; i++) {	// 괄호 내용을 다른 string 배열에 저장
			a[i - 2] = command[i];
		}

		istringstream ss(a);
		string stringBuffer;
		vector<string> x;
		x.clear();

		while (getline(ss, stringBuffer, ',')) {
			x.push_back(stringBuffer);
		}

		if (!is_Digit(x[0]) || !is_Digit(x[1])) {
			return 3;
		}

		first = atoi(x[0].c_str());
		second = atoi(x[1].c_str());
		third = x[2];

		int nullCt = 0;									// first 줄의 공백 개수
		for (int j = 0; j < (int)v[first].size(); j++) {
			if (v[first][j] == " ") {
				nullCt++;
			}
		}

		if ((int)v.size() < first || (int)third.size() > 75) {	//정확한 줄이 아니거나 size가 75가 넘으면
			return 4;
		}
		else if ((int)v[first].size() - nullCt <= second) {	//줄의 단어 개수를 넘어가면
			return 3;
		}
		else {
			int count = 0;
			for (int i = 0; i < first - 1; i++) {
				int nullCt = 0;
				for (int j = 0; j < (int)v[i].size(); j++) {
					if (v[i][j] == " ") {
						nullCt++;
					}
				}
				count += (v[i].size() - nullCt - 1);
			}

			count += (second - 1);
			storeV2.insert(storeV2.begin() + count, third);
			return 1;
		}

	}

	int input_d(string command) {				// d 명령어

		int first = 0;
		int second = 0;

		if (command.size() < 2) {
			return 0;
		}


		string a;
		a.resize(command.size() - 3);
		for (int i = 2; i < (int)command.size() - 1; i++) {	// 괄호 내용을 다른 string 배열에 저장
			a[i - 2] = command[i];
		}

		istringstream ss(a);
		string stringBuffer;
		vector<string> x;
		x.clear();

		while (getline(ss, stringBuffer, ',')) {
			x.push_back(stringBuffer);
		}

		if (!is_Digit(x[0]) || !is_Digit(x[1])) {
			return 3;
		}

		first = atoi(x[0].c_str());
		second = atoi(x[1].c_str());

		int nullCt = 0;									// first 줄의 공백 개수
		for (int j = 0; j < (int)v[first].size(); j++) {
			if (v[first][j] == " ") {
				nullCt++;
			}
		}

		if ((int)v.size() < first) {	//정확한 줄이 아니거나 size가 최대 줄 수를 넘으면
			return 5;
		}
		else if ((int)v[first].size() - nullCt <= second) {	//줄의 단어 개수를 넘어가면
			return 6;
		}
		else {
			int count = 0;
			for (int i = 0; i < first - 1; i++) {
				int nullCt = 0;
				for (int j = 0; j < (int)v[i].size(); j++) {
					if (v[i][j] == " ") {
						nullCt++;
					}
				}
				count += (v[i].size() - nullCt - 1);
			}

			count += (second - 1);
			storeV2.erase(storeV2.begin() + count);

			return 1;
		}
	}


	int input_c(string command) {				// c 명령어

		string first = "";
		string second = "";

		if (command.size() < 2) {
			return 0;
		}


		string a;
		a.resize(command.size() - 3);
		for (int i = 2; i < (int)command.size() - 1; i++) {	// 괄호 내용을 다른 string 배열에 저장
			a[i - 2] = command[i];
		}

		istringstream ss(a);
		string stringBuffer;
		vector<string> x;
		x.clear();

		while (getline(ss, stringBuffer, ',')) {
			x.push_back(stringBuffer);
		}

		first = x[0];
		second = x[1];

		if (first.size() > 75 || second.size() > 75) {	//찾으려는 단어와 바꾸려는 단어가 75바이트를 넘으면
			return 3;
		}

		else {
			vector<int> find_i;

			for (int i = 0; i < (int)storeV2.size() - 1; i++) {
				if (first == storeV2[i]) {
					find_i.push_back(i);
				}
			}
			if (find_i.size() == 0) {
				return 7;
			}
			else {
				for (int i = 0; i < (int)find_i.size() - 1; i++) {
					storeV2.erase(storeV2.begin() + find_i[i]);
					storeV2.insert(storeV2.begin() + find_i[i], second);
				}
				return 1;
			}
		}

	}

	int input_s(string command) {

		string find = "";

		if (command.size() < 2) {
			return 0;
		}


		string a;
		a.resize(command.size() - 3);
		for (int i = 2; i < (int)command.size() - 1; i++) {	// 괄호 내용을 다른 string 배열에 저장
			a[i - 2] = command[i];
		}

		find = a;


		if (find.size() > 75) {	//size가 75가 넘으면
			return 4;
		}

		else {
			int find_i = -1;
			for (int i = 0; i < (int)storeV2.size() - 1; i++) {
				if (find == storeV2[i]) {
					find_i = i;
					break;
				}
			}
			if (find_i == -1) {
				return 7;	//단어를 못찾을 경우
			}
			else {
				storeV2.erase(storeV2.begin() + find_i);
				storeV2.insert(storeV2.begin(), find);
				return 1;
			}
		}
	}

	int input_t(fstream& testfile) {

		string a = " ";

		testfile.open("test.txt");

		if (testfile.is_open()) {
			for (int i = 0; i < (int)storeV2.size(); i++) {
				testfile.write(storeV2[i].c_str(), storeV2[i].size());
				testfile.write(a.c_str(), a.size());

			}
			testfile.close();
			return 1;
		}
		else {
			testfile.close();
			return 0;
		}




	}

	bool is_Digit(string str) {

		return atoi(str.c_str()) != 0 || str.compare("0") == 0;

	}

	string errorMessage(int errorcode) {
		switch (errorcode) {
		case 0:
			return "(콘솔메시지)";

		case 1:
			return "This is the last page!";

		case 2:
			return "This is the first page!";

		case 3:
			return "인자에 제대로 된 값이 입력되지 않았습니다.";

		case 4:
			return "단어의 최대 바이트 수를 초과했습니다.";

		case 5:
			return "최대 줄 수를 초과 했습니다.";

		case 6:
			return "최대 단어 수를 초과 했습니다.";

		case 7:
			return "단어가 존재하지 않습니다.";

		case 10:
			return "명령어를 잘못 입력했습니다.";
		default:
			return "";
		}
	}

};