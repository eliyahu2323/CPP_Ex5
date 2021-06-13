

#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>
using namespace std;
double** read_mat(string filename, int* size);
void printmatrix(double** arr, int size);
double* smallernum(double** arr, int size, double num, int* newsize);
int counterSmallNumber(double** arr, int size, double num);
string words_begin(string filename, char ch);

int main()
{
	int menu;
	bool flag = true; //boolean variable for loop
	int size = 0;
	double** mat=nullptr;
	double* arr;
	int newsize = 0;
	while (flag) {
		cout << "Menu:" << endl;
		cout << "Press:" << endl;
		cout << "0 for exit" << endl;
		cout << "1 for read and print matrix from file" << endl;
		cout << "2 for print array with smaller numbers from matrix" << endl;
		cout << "3 for print words begins with  given char from file" << endl;
		cout << "Enter your choice:";
		cin >> menu; //get your choice from user

		switch (menu) {
			
		case 0: {//if menu == 0 you want exit
			cout << "Thank you for using the program" << endl;
			if (mat != nullptr){
				for (int i = 0; i < size; i++)
				{
					delete[]mat[i];
				}
			delete[]mat;
		    }			
			flag = false;
			break;
		}

		case 1: {
		    mat = read_mat("numbers.txt", &size);
			printmatrix(mat, size);
			break;
		}

		case 2: {
			double num;
			cout << "please enter number: ";
			cin >> num;
			arr = smallernum(mat, size, num, &newsize);
			if(newsize>0){
				cout << "*newsize =" << newsize<<endl;
				cout << "new_array ={";
			for (int i = 0; i < newsize; i++) {//print arr
				cout<<arr[i];
				if (i < newsize - 1) {
					cout <<",";
				}
			}
			cout <<"}\n";
			delete[]arr;
		    }
			else {
				cout << "There are no numbers smaller than the given number\n";
			}
			break;
		}
		case 3: {
			char tav;
			cout << "please enter your char: ";
			cin >> tav;
			string save=words_begin("strangers.txt", tav);
			if (save.empty()) {
				cout << "the string empty\n";
			}
			else{
			cout << save<<endl;
			}
			break;
		}
		}
	}

}
	

double** read_mat(string filename, int* size) {
	
	ifstream file(filename);
	if (!file) {//Checks if the file exists
		cout << "file" << filename << "do not exist!!!" << endl;
		return 0;
	}
	int cout = 0;
	int n;
	if (cout == 0) {//Skip the first member of the file
		file >> n;
		cout++;
	}
	*size = n;
	double** mat = new double* [*size];//dinamic allocation memory for array of pointers
	for (int i = 0; i < *size; i++){
		mat[i] = new double[*size];//memory for rows
		for (int j = 0; j < *size; j++){
			
			file >> mat[i][j];//Saving numbers from the file to the matrix
		}
	}
	file.close();
	return mat;
}

void printmatrix(double** arr, int size) {//print the matrix
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << arr[i][j]<<" ";
		}
		cout << endl;	
	}
}


double* smallernum(double** arr, int size, double num, int* newsize) {
	 *newsize = counterSmallNumber(arr, size, num);
	 int count = 0;
	 double* newarr = new double [*newsize];//Creating a dynamic array
	 for (int i = 0; i < size; i++){
		 for (int j = 0; j < size; j++){
			 if (arr[i][j] < num) {
				 newarr[count] = arr[i][j];
				 count++;
		     }
		 }
	 }
	return newarr;
}

int counterSmallNumber(double** arr,int size, double num) {//A function that checks some numbers smaller than the given number
	int coun = 0;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (arr[i][j] < num) {
				coun++;
			}
		}
	}
	return coun;
}

string words_begin(string filename, char ch) {
	
	ifstream file(filename);
	if (!file) {//Checks if the file exists
		cout << "file" << filename << "do not exist!!!" << endl;
		exit(1);
	}

	string retu;
	string n;
	while (file >> n)//reading by word-until space
	{
		if (n[0] == ch) {//Checks if the first word in the word is "ch"
			if (retu.empty()) {//When finding the first word
				retu += n;
			}
			else{
			retu +=" "+n;
			}
		}
	}
	//cout << retu;
	file.close();//close file
	return retu;
}