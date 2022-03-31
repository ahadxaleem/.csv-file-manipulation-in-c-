#include <iostream>
#include <vector>
#include <string>
#include <fstream>//for reading file
#include<sstream>//to break the fstream input
#include<iomanip>//to format output
#include<algorithm>//for sorting the vector
#include <windows.h>//for computing the filename

using namespace std;

//A structure to store the desired values
struct salesrecord {
	string date;
	float open_price;
	float adj_close_price;
	float percentage;
};

//***************************************************************************************************
void Compute_1_Filename(string& filename)
{
	//Stores the name of the file with the .csv extension in the filename parameter
	//Make sure that the .csv file is in the same directory as the main .cpp file when
	//you are making this project.

	WIN32_FIND_DATAA findfiledata;
	HANDLE hfind;
	string file_extension = "*.csv";

	string directory_file_ext = file_extension;
	hfind = FindFirstFileA(directory_file_ext.c_str(), &findfiledata);

	if (hfind != INVALID_HANDLE_VALUE)
		filename = findfiledata.cFileName;
	else
		cout << "No file was present" << endl;

}

//to compare two perc and return t or f
bool my_cmp(const salesrecord& a, const salesrecord& b) {
	return a.percentage > b.percentage;
}

//returns a sorted list of struct salesrecord
vector<salesrecord> returnList(string fn, string tn) {
	salesrecord temp;//to temporarily store data of 1 row of csv file
	vector<salesrecord> list;//holds all rows of required data
	fstream fin;
	fin.open(fn, ios::in);
	// as String Vector
	vector<string> row;
	string line, word;
	// to ignore first line as it is lables
	getline(fin, line);
	// Read the Data from the file
	// read an entire row and
	// store it in a string variable 'line'
	while (getline(fin, line)) {

		row.clear();
		
		// used for breaking words
		stringstream s(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (getline(s, word, ',')) {
			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}
		temp.date = row[0];//storing date
		temp.open_price = stof(row[1]);//storing open price
		temp.adj_close_price = stof(row[5]);//storing A.close
		temp.percentage = ((temp.adj_close_price - temp.open_price) / temp.open_price) * 100;//calculating percentage
		list.push_back(temp);//adding in list
	}
	cout << "This program will analyse GLD from " << list.begin()->date << " to " << temp.date << "\n" << list.size() << " trading day(s) exist in the " << tn << endl;
	sort(list.begin(), list.end(), my_cmp);//sorting list
	return list;
}

//***************************************************************************************************
void main()
{
	string filename, ticker_name;
	int no_of_record;
	vector<salesrecord> arr;//store sorted list returned from returnlist
	unsigned int ticker_length;
	Compute_1_Filename(filename);
	ticker_length = filename.length() - 4;//4 is the length of ".csv"
	ticker_name = filename.substr(0, ticker_length);
	/*cout << "The name of the .csv file is: " << ticker_name << endl;*/
	arr = returnList(filename,ticker_name);
	int temps = arr.size();//calculating list size as it'll be used multiple times
	do {//formatted output
		cout << "How many increase records do you want to find? ";
		cin >> no_of_record;
		if (no_of_record > temps) {
			cout << "There are only " << temps << " trading days."<<endl;
		}
	} while (no_of_record > temps);
	cout << "Date\t\tOpen\tA.Close\tPercent\tchange\n";
	for (int i = 0; i < no_of_record; i++) {
		cout << arr[i].date << "\t" << setw(8) <<left<< arr[i].open_price << setw(8) <<left << arr[i].adj_close_price << setw(9) <<left << arr[i].percentage << endl;
	}
	cout << "Press any key to continue . . .";
	cin.get();
}