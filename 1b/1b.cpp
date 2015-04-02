/***************************************************/
/* PROGRAM: 1b			                           */
/*                                                 */
/* AUTHOR: Clayton Kimber                          */
/*                                                 */
/* DATE: 01Feb15                                   */
/*                                                 */
/* REVISIONS:                                      */
/*                                                 */
/* PURPOSE: take in a file of symbols and store    */
/*          them for use in a slot machine-like    */
/*			interface.  Various user inputs and    */
/*			outputs			     				   */
/***************************************************/

//// Header
using namespace std;
#include <fstream>
#include <iostream>
#include <cstdlib>	// for random (stdlib is depreciated)
#include <ctime>	// for random
//#include <iomanip>	// for beautification


//// Global Variables
int numOfReels = 3;										// number of reels
int numOfPerReel = 10;									// number of symbols per reel
int numOfSymbols = 6;									// number of symbols
int sizeOfSymbols = 10;									// max size of symbol storage

//char test[][2][10] = {"bar","6","bell","5","cherry","1","lemon","0","orange","0","7","10"};

////Function Prototypes ////
void readFile (char[][2][10]);		// read the hardcoded file
void bonusToScreen (char[][2][10]);		// print the symbols file to screen
void userFileRead (char[][3][10], char[]);	// read a user selected file
void reelsToScreen (char[][3][10]);		// output the reels setup to screen
void createSlot (char[][2][10], char[10][3][10]);	// create a new random reels
void writeFile (char[][3][10]);		// write reels to file
void selectionToScreen (char[][2][10], char[10][3][10]);	// get and print specific bar reel from user
int bonusFetch (char [][2][10], char []);	// fetch the bonus associated with the symbol
bool strComp (char[],char[]);	// compare two strings

//// Main ////
int main()
{
	// local variables
	int selection=0;	// selection of user
	bool hasRead = 0;		// true if file loaded
	char reels[10][3][10]; 	// reels file

	// seed random number generator
	srand(time(NULL));

	do
	{
		// Main Menu graphics
		cout << "Slot Machine Menu" << endl;
		cout << " 1. Populate a new slot machine " << endl;
		cout << " 2. Read an existing slot machine configuration"<< endl;
		cout << " 3. Print the existing slot machine configuration to screen" << endl;
		cout << " 4. Print a selected reel and stop"<< endl;
		cout << " 5. Print configuration to file" << endl;
		cout << " 6. Exit" << endl;
		cout << " Enter your selection: ";
		cin >> selection;

		// Main menu
		switch (selection)
		{

		case 1:		// make new slot
			cout << endl << endl << "Populate a new slot machine " << endl << endl;

			// read file data
			cout << "File fetching in progress ! ! !" << endl;

			// load bonus array
			char bonusFile[6][2][10];
			readFile(bonusFile);
			hasRead = 1;

			// create new slot machine
			createSlot (bonusFile, reels);
			break;

		case 2:		// Read slot
			char userFilename[20];
			cout << endl << endl << "Read an existing slot machine configuration" << endl;
			// input file to read
			cout << "Please type the file that you would like to open  - ";
			cin >> userFilename;
			cout << endl << "You have requested to open " << userFilename << endl;
			// get files
			readFile(bonusFile);
			userFileRead (reels,userFilename);
			hasRead = 1;
			break;

		case 3:		// output to screen
			if(hasRead)
			{
				cout << endl << endl << "Print the existing slot machine configuration to screen" << endl;

				// print loaded array to screen
				bonusToScreen(bonusFile);

				// print reels to screen
				reelsToScreen(reels);
			}
			else
			{
				// why it won't print out to the screen
				cout << endl << "A file has not been created or specified" << endl;
				cout << "Please enter either 1 or 2 prior to this selection"<< endl << endl;
			}
			break;

		case 4:		// Select reel and stop and output to screen
			cout << endl << endl << "Print a selected reel and stop" << endl;
			selectionToScreen (bonusFile,reels);
			break;

		case 5:		// File output
			cout << endl << endl << "Print configuration to file" << endl;

			// File output
			writeFile (reels);

			// output to file
			break;

			// Exit
		case 6:
			cout << endl << endl << "Goodbye." << endl << endl;
		}

	}
	while(selection!=0);

	return 0;
}


////Function implementation ////
void readFile (char output[][2][10])
{
	// open and prepare file
	ifstream reel;
	reel.open ("symbols");
	// read in
	int i,j;
	for (i=0; i<6; i++)
	{
		for(j=0; j<2;j++)
		{
			reel >> output[i][j];
		}
	}
	// close the opened file.
	reel.close();
	cout << "file read complete" << endl << endl;
}
void userFileRead (char output[][3][10], char fileName[])
{
	int i,j;
	// prepare file
	ifstream reel;
	reel.open (fileName);
	// load file
	for (i=0; i<10;i++)
	{
		for(j=0; j<3;j++)
		{
			reel >> output[i][j];
		}
	}
	// close the opened file.
	reel.close();
	cout << "file read complete" << endl << endl;
}
void bonusToScreen (char input[][2][10])
{
	int i, j;
	// message
	cout << endl << "!!BONUS!!" << endl;
	// output to screen
	for (i=0; i<6; i++)
	{
		for(j=0; j<2;j++)
		{
			cout << input[i][j] << "\t";
		}
		cout << endl;
	}
	// end message
	cout << endl << "Bonus complete"<< endl;
}
void reelsToScreen (char input[][3][10])
{
	int i, j;
	// message
	cout << endl << "!!Reels!!" << endl;
	cout << "Reel 1" << "\t" << "Reel 2" << "\t" << "Reel 3"  << endl << endl;
	// print reels to screen
	for (i=0; i<10; i++)
	{
		for(j=0; j<3;j++)
		{
			cout << input[i][j] << "\t";
		}
		cout << endl;
	}
	// message
	cout << endl << "Reels complete"<< endl;
}
void createSlot (char bonusInput[][2][10], char reelsInput[10][3][10])
{
	int i, j, k=0;
	// message
	cout << "Creating Slot machine" << endl;
	// create random slot machine
	for (i=0; i<10;i++)
	{
		for (j=0; j<3;j++)
		{
			int x = rand () % 6; // will run random number between 0 and 6

			// load in chars 1 by one
			for (k=0 ; k<10; k++)
			{
				reelsInput[i][j][k] = bonusInput[x][0][k];
			}
		}
	}
	// message
	cout << "Slot Machine Created" << endl;
}
void writeFile (char reelOutput[][3][10])
{
	int i,j;
	//File output
	cout << "File output in progress" << endl;
	cout << "Please enter the name of the output file - " << endl;
	char outputName[20];
	cin >> outputName ;
	cout << outputName << endl;
	// prepare file to output
	ofstream outputFile;
	outputFile.open(outputName);
	// output to file
	for (i=0;i<10;i++)
	{
		for (j=0;j<3;j++)
		{
			outputFile << reelOutput [i][j] << "\t";
		}
		outputFile << endl;
	}
	// close file
	outputFile.close();
	// close message
	cout << "File write complete, file closed" << endl;
}
void selectionToScreen (char bonus[][2][10], char reel[10][3][10])
{
	int selection1,selection2,value;
	// message and prompt
	cout << "Please select the reel you would like displayed (1-3) - ";
	cin >> selection1;
	cout << "Please select the stop you would like displayed (1-10) - ";
	cin >> selection2;
	// error bounding in selection
	if (selection1 > 3 || selection2 > 10)
	{
		cout << "Your selection is not within the required inputs" << endl;
		return;
	}
	// fetch and print out the values
	cout << "Your selected symbol is - " << reel[(selection2 - 1)][selection1 -1 ] << endl;
	value = bonusFetch (bonus,reel[(selection1 - 1)][selection2 -1 ]);
	cout << "The bonus associated with that symbol is - " << value << endl << endl;

}
int bonusFetch (char bonus[][2][10], char item[])
{
	int x,index=0;
	bool found=false;
	// iterate through strComp to find the bonus
	while (!found)
	{
		found = strComp(bonus[index][0],item);
		index++;
	}
	// return the bonus
	x = atoi(bonus[index][1]);
	return x;
}
bool strComp (char inputA[],char inputB[])
{
	// returns true if inputA and inputB are the same up to the null, otherwise false
	int i=0;
	bool done;
	while (!done)
	{
		if (inputA[i] != inputB[i])
		{
			return false;
		}
		if (inputA[i] == '\0')
		{
			done = true;
		}
		else i++;
	}
	return true;
}

