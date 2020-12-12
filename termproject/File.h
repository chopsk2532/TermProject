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
			while (!myfile.eof()) {	// text������ ��� ���ڸ� �ѹ��� string�� ����

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

		int ct = 0; //���� ����
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




			if (length >= 75) { //byte�� 75�� �Ѵ´ٸ�

				length = length - 1;

				if (length > 75) {

					//������ �ܾ�� ������ ""���� �ٲٰ�
					v[vectorNum][vectorCt - 2] = "";
							 
					//������ �ܾ �ٽ� �����ϱ����� back

					vectorCt = 0;	//���� ���� ����
					length = 0;
					ct--;
					vectorNum++;

				}

				else {


					vectorCt = 0;	//���� ���� ����
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
			if (line < (int)(v.size())) {							//20�پ� ���
				for (int j = 0; j < (int)v[line].size(); j++) {
					cout << v[line][j];
				}
			}

			cout << endl;
			line++;

			if ((line > 0) && (line % 20) == 0) {

				seperLine();

				cout << "n:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������" << endl;

				seperLine();

				//���� �޽��� ���â
				cout << errorMessage(errorcode) << endl;

				seperLine();

				input_command(myfile, page, lastPage, line, errorcode);
				
			}
		}
	}


private:
	void input_command(fstream& myfile, int& page, int lastPage, int& line, int& errorcode) {
		
		string command;

		cout << "�Է�:";
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

	int input_I(string command) {				// i ��ɾ�

		int first = 0;
		int second = 0;
		string third = "";

		if (command.size() < 2) {
			return 0;
		}


		string a;
		a.resize(command.size() - 3);
		for (int i = 2; i < (int)command.size() - 1; i++) {	// ��ȣ ������ �ٸ� string �迭�� ����
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

		int nullCt = 0;									// first ���� ���� ����
		for (int j = 0; j < (int)v[first].size(); j++) {
			if (v[first][j] == " ") {
				nullCt++;
			}
		}

		if ((int)v.size() < first || (int)third.size() > 75) {	//��Ȯ�� ���� �ƴϰų� size�� 75�� ������
			return 4;
		}
		else if ((int)v[first].size() - nullCt <= second) {	//���� �ܾ� ������ �Ѿ��
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

	int input_d(string command) {				// d ��ɾ�

		int first = 0;
		int second = 0;

		if (command.size() < 2) {
			return 0;
		}


		string a;
		a.resize(command.size() - 3);
		for (int i = 2; i < (int)command.size() - 1; i++) {	// ��ȣ ������ �ٸ� string �迭�� ����
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

		int nullCt = 0;									// first ���� ���� ����
		for (int j = 0; j < (int)v[first].size(); j++) {
			if (v[first][j] == " ") {
				nullCt++;
			}
		}

		if ((int)v.size() < first) {	//��Ȯ�� ���� �ƴϰų� size�� �ִ� �� ���� ������
			return 5;
		}
		else if ((int)v[first].size() - nullCt <= second) {	//���� �ܾ� ������ �Ѿ��
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


	int input_c(string command) {				// c ��ɾ�

		string first = "";
		string second = "";

		if (command.size() < 2) {
			return 0;
		}


		string a;
		a.resize(command.size() - 3);
		for (int i = 2; i < (int)command.size() - 1; i++) {	// ��ȣ ������ �ٸ� string �迭�� ����
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

		if (first.size() > 75 || second.size() > 75) {	//ã������ �ܾ�� �ٲٷ��� �ܾ 75����Ʈ�� ������
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
		for (int i = 2; i < (int)command.size() - 1; i++) {	// ��ȣ ������ �ٸ� string �迭�� ����
			a[i - 2] = command[i];
		}

		find = a;


		if (find.size() > 75) {	//size�� 75�� ������
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
				return 7;	//�ܾ ��ã�� ���
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
			return "(�ָܼ޽���)";

		case 1:
			return "This is the last page!";

		case 2:
			return "This is the first page!";

		case 3:
			return "���ڿ� ����� �� ���� �Էµ��� �ʾҽ��ϴ�.";

		case 4:
			return "�ܾ��� �ִ� ����Ʈ ���� �ʰ��߽��ϴ�.";

		case 5:
			return "�ִ� �� ���� �ʰ� �߽��ϴ�.";

		case 6:
			return "�ִ� �ܾ� ���� �ʰ� �߽��ϴ�.";

		case 7:
			return "�ܾ �������� �ʽ��ϴ�.";

		case 10:
			return "��ɾ �߸� �Է��߽��ϴ�.";
		default:
			return "";
		}
	}

};