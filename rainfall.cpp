/*

Rainfall data collector by Weather Ministry

The program includes the ability to insert data , show in terminal report and printing out a txt graph file for hardcopy / external use .

*/

#include <cctype>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <vector>
#include <sstream>
#include <dirent.h>

using namespace std;

string months[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
string continuation , username  , state;
int rainfall[12];
int sum = 0, option , i = 0;
bool pwstatus = false;
bool readstatus = false;

time_t now = time(0);

// fuction used to read the data inserted in the files
void fileread(){
	
	cout << "Data files for states available :" << endl ;
	cout << "---------------------------------" << endl << endl;
	
	// Open the current directory
	DIR *dr;
	struct dirent *en;
	dr = opendir("."); 

    if (dr) {
    while ((en = readdir(dr)) != NULL) {
    	
        // Check if the file name starts with data.txt
        
        if (strstr(en->d_name, " data.txt") != NULL) {
          cout << en->d_name;
		  cout << endl; 
        }
      }
    closedir(dr);
  	}	
  	
  	cout << endl;
  	cout << "---------------------------------" << endl ;
	cout << " ONLY ENTER THE STATE NAME       " << endl ;
	cout << " WITHOUT DATA.TXT                " << endl ;
	cout << "---------------------------------" << endl << endl;
	
	// input the file want to open
  ifstream infile;
  string filename;
  cout << "Enter the file name you want to open : ";
  cin.ignore(1);
  getline(cin,filename);
  state=filename;
  
  	// for user's convienience so that data.txt is not needed to be typed 
  	// at the same time it can group data files
  filename = filename + " data.txt";
  infile.open(filename.c_str());
  if (!infile.is_open()) {
    cout << "File does not exist / incompatible file type" << endl;
    readstatus = false;
  }
  vector<int> number_values;
  
  

  // Reading each of the lines in the file
  string line;
  while (getline(infile, line)) {

    string  number_value;
    int i = 0;
    number_value = line.substr(i);

    // Convert to integer for manipulation and use
    int number_value_int;
    stringstream ss(number_value);
    ss >> number_value_int;

    if (!ss) {
      cout << "Error converting to integer: " << number_value << endl;
      readstatus = false;

    }
    
	readstatus = true;
	
    // Changes the vector into the array in the program
    number_values.push_back(number_value_int);
	    
	 	for (size_t i = 0; i < number_values.size(); i++) {
	    	rainfall[i] = number_values[i];
	  	}

	}	
}

// function used to insert the data (specifically from the rainfall array) to the text file
void fileinsert(){
	
		string filename;
    	filename = state + " data.txt";
		
		ofstream insertfile;
    	insertfile.open(filename.c_str());
    	
    	for (int i = 0 ; i <= 11 ; i++){	
    	insertfile << rainfall[i] << endl;
    	}
    	
		insertfile.close();
	
}	

// function use to insert data into array then into a data file for future use
void insert() {
	
    cin.ignore();

    cout << "Enter the name of the state: ";
    getline(cin, state);
    cout << endl;
	
    for (int i = 0 ; i <= 11 ; i++) {

		cout << left;
        cout << setw(35) << "Enter the rainfall for " + months[i] << ": ";
        cin >> rainfall[i];
		
		// validate whether the rainfall data is valid or not
        while (rainfall[i] < 0 || rainfall[i] > 45) {
			
            cout << "Invalid amount. Please re-enter the data " <<
                ": ";
            cin >> rainfall[i];
            cout << endl;
        }
		
        cout << endl << endl;	
		fileinsert();  
    }
    
}

// function to generate a report within the terminal
void report() {

	sum = 0;
	
	// call the read function to get the data file wanted by the user
	fileread();
	
	if(readstatus == true){
	
	cout << endl;
	cout << "------------------------------------" << endl ;
	cout << "Ranfall Report on " << state << endl;
	cout << "------------------------------------" << endl << endl;
    for (int i = 0; i <= 11; i++) { 
    	cout << endl << left;
        sum = rainfall[i] + sum;

        
        cout << setw(15) << months[i] << " : " << rainfall[i] ;
    }
	
	cout << "\n \n";
    cout << setw(30) << "Total rainfall for a year  "<< ": " << sum << endl;
    cout << setw(30) << "Average rainfall for a year "<< ": " << sum / 12 << endl << endl;
    
    cout << setw(30) << "Status " << ": ";
    
    // status section check
    if (sum/12 == 0) {
            cout << "No Rain";
        }

    if (sum/12 > 0 && sum/12 < 15) {
            cout << "Less amount of Rain";
    }

    if (sum/12 >= 15 && sum/12 < 30) {
            cout << "Moderate amount of Rain";
    }

    if (sum/12 >= 30) {
            cout << "Heavy amount of Rain";
    }
    
    cout << endl << endl;
    
    
	}
	
	if(readstatus == false) {
		cout << endl;
	}

}

// function to print out an external graph
void graph() {
	
	string filename ;
	
	// call the read function to get the data file wanted by the user
	fileread();

	if (readstatus == true){
	
	cout << "What do you want to name this file :";
	getline(cin,filename);
	
    filename = filename + " .txt";

    ofstream graphfile;
    graphfile.open(filename.c_str());
    graphfile << "Rainfall for a Year in " << state << endl << endl;

    for (int i = 0; i <= 11; i++) {

        graphfile << left;
        graphfile << setw(20) << months[i] << " | ";

        for (int j = 0; j < rainfall[i]; j++) {
            graphfile << "# ";
        }

        graphfile << endl;
         
    }

	graphfile << endl;
	graphfile << "By " << username << " on " << ctime(&now); 
    graphfile.close();

    cout << "Graph has been saved ";
    cout << endl;
	}
	
	if(readstatus == false){
		cout << endl;
	}
}

// function for the login process at the beginning
void login(){
	 
    	char pw[] = "1234ABC", str[4];
    	
    	if(pwstatus == false){
		
			cout << "Enter your username : " ;
			getline(cin,username);	
			
						
			cout << "Welcome to the system " << username << endl;
			cout << "Please enter your password to enter: ";
			cin >> str;
		}
			
    	do {
			
    		// Password Validation
    		if(pwstatus == false){
    			
    			if (strcmp(pw, str) == 0) {
			
			        cout << endl << "Correct password." << endl << endl;
			        pwstatus = true;
			        break;
			    } 
			
				
				else {
					pwstatus = false;
			        cout << endl << "Wrong password. Please try again : " ;
			        cin >> str;
			    }
			}
		
		}while (pwstatus == false);
}	
	
int main() {
	
	do{
		
		// call the login fuction
		login();
		
		// menu 
        cout << "Welcome to the Weather Department Rainfall Data System" << endl << endl;
        cout << "Choose an Operation (Use the indicated number to select the "
        "operation)" << endl;
        cout << "-----------------------" << endl;
        cout << "| 1.       Input Data |" << endl;
        cout << "| 2.      Show Report |" << endl;
        cout << "| 3.    Display Graph |" << endl;
        cout << "|                     |" << endl;
        cout << "| 4.             EXIT |" << endl;
		cout << "-----------------------" << endl;
		
		cout << endl;
		cout << "Operation number :";
        cin >> option;

        while (option < 1 || option > 4) {

            // cin clear to clear the option var
            // this was done to primarily prevent text input from breaking the error message
            cin.clear();
            cin.ignore(numeric_limits < streamsize > ::max(), '\n');

            cout << "Invalid Input. Please try again." << endl;
            cin >> option;
        }

		// decide which code was chose using switch case
        switch (option) {
        case 1:
            insert();
            break;

        case 2:
            report();
            break;

        case 3:
            graph();
            break;
            
        case 4:
        	break;
        }

		if (option == 4){
			break;
		}
		
		// ask for user whether they want to continue or terminate the program
        cout << "Would you like to continue the program? (type 4 to exit / any keys to continue)" << endl;
        cin >> continuation;
    } while (!(continuation == "4"));
    
    cout << endl;
    cout << "Program has ended thanks for using it " << username;
}
