#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <conio.h>
#include <windows.h>
using namespace std;

int stringToInt(string s);
inline bool isInteger(const std::string& s);
int getInput(string question);
int getInput(string question, int maxOutput, int minOutput);

int main() {
	//Constant variable declarations
	const int NAME_SPACING = 30;
	const int COL_SPACING = 10;

	//Variable Declarations
	string userInput;
	string oppTeamName;
	string map;
	string fileName;
	string winner;
	string CCEScore;
	string OPPScore;
	string CCETime;
	string OPPTime;
	string CCEDistance;
	string OPPDistance;
	int attOrDef;
	int matchId = -1;
	int teamFights = 0;
	int totalCCEUltsUsed = 0;
	int totalOPPUltsUsed = 0;
	int roundWinner = 0;
	int gameWinner = 0;
	int switcher = 1;
	int CCETeamFightWins = 0;
	int OPPTeamFightWins = 0;
	int unassignedFights = 0;

	ifstream fin("tracking input.txt"); //For testing

	//gets input about the opposing team
	cout << "What team are CCE facing? ";
	cin >> oppTeamName;

	//Gets input about the map of the game
	cout << "What map is it on? ";
	cin >> map;

	//sets up output files
	fileName = "CCE vs " + oppTeamName + "; " + map + ".csv";//The csv file that is easily imported into google sheets
	ofstream fout(fileName);
	fileName = "CCE vs " + oppTeamName + "; " + map + ".txt";//the file contains a lot of totals and some easy to read stuff
	ofstream tfout(fileName);
	if (fout.fail()) {
		cout << "Use this name for your txt file,";
		cout << fileName << ",";
		exit(0);
	}

	//set Up for the csv file (headings)
	{
		fout << setw(COL_SPACING) << left << "ROUND,";
		fout << setw(COL_SPACING) << left << "TEAM FIGHT,";
		fout << setw(COL_SPACING) << right << "CCE ULTS,";
		fout << setw(COL_SPACING) << right << oppTeamName + " ULTS,";
		fout << setw(COL_SPACING) << right << "CCE win,";
		fout << setw(COL_SPACING) << right << oppTeamName << " win," << endl;
	}

	//Loops each time a new round is started
	while (userInput != "end") {
		attOrDef = getInput("Is CCE attack(1) or defense(2) or control(3)?", 3, 1);//Asks for this round if CCE is attacking or defending
		//gets the name of the control map if nececary
		if (attOrDef == 3) {
			cout << "What control map are you on? ";
			cin >> map;
		}
		system("pause");

		//Loops for each new teamfight
		while (userInput != "end") {
			//Local Variable Declarations
			int fightUltsUsed;
			int fightWinner;

			fout << setw(COL_SPACING) << left << attOrDef << ","; //Records if CCE is attacking or defending
			fout << setw(COL_SPACING) << left << (teamFights + 1) << ","; // Records the Team fight index

			fightUltsUsed = getInput("How many ults did CCE use? ", 6, 0);//indicates the number of ults CCE used in a fight
			totalCCEUltsUsed += fightUltsUsed; //Adds to total numbher of fights
			fout << setw(COL_SPACING) << right << fightUltsUsed << ","; //Records for the fight

			//same as above for OPP team
			fightUltsUsed = 0;
			fightUltsUsed = getInput("How many ults did " + oppTeamName + " use? ", 6, 0);
			totalOPPUltsUsed += fightUltsUsed;
			fout << setw(COL_SPACING) << right << fightUltsUsed << ",";

			fightWinner = getInput("Who Won(CCE[1] or " + oppTeamName + "[2]): ", 2, 0);//Asks for the winner of the team fight
			if (fightWinner == 1) {
				CCETeamFightWins++;
				fout << setw(COL_SPACING) << right << 1 << ",";
				fout << setw(COL_SPACING) << right << 0 << ",";
			}
			else if (fightWinner == 2) {
				OPPTeamFightWins++;
				fout << setw(COL_SPACING) << right << 0 << ",";
				fout << setw(COL_SPACING) << right << 1 << ",";

			}
			else unassignedFights++;
			teamFights++;

			cout << "if the round is over type end else type y? ";
			cin >> userInput;

			fout << endl;
		}

		roundWinner = getInput("Who won the round(CCE[1] or " + oppTeamName + "[2])? ");
		if (roundWinner == 1) {
			winner = "CCE";
		}
		else if (roundWinner == 2) {
			winner = oppTeamName;
		}
		else
			winner = "no winner determined";

		//outputs to file for the totals of the round
		{
			tfout << setw(NAME_SPACING) << right << "the winner of the round was " << winner << endl
				<< endl << setw(NAME_SPACING) << right << "TOTAL FIGHTS: " << teamFights << endl
				<< setw(NAME_SPACING) << right << "CCE ults used per fight: " << totalCCEUltsUsed << endl
				<< setw(NAME_SPACING) << right << "OPP ults used per fight: " << totalOPPUltsUsed << endl
				<< setw(NAME_SPACING) << right << "CCE fight wins: " << CCETeamFightWins << endl
				<< setw(NAME_SPACING) << right << "OPP fight wins: " << OPPTeamFightWins << endl
				<< setw(NAME_SPACING) << right << "Unassigned fight wins: " << unassignedFights << endl;


			fout << "totals,"
				<< teamFights << ","
				<< totalCCEUltsUsed << ","
				<< totalOPPUltsUsed << ","
				<< CCETeamFightWins << ","
				<< OPPTeamFightWins << ","
				<< map << "," << endl;
		} //outputs to file for the totals of the round
		//other round information
		int choice = getInput("Who was attacking(1CCE,2OPP,3Control)? ", 3, 1);
		if (choice == 1) {
			cout << "What was CCE's Score?";
			getline(cin, CCEScore);
			cout << "What was CCE's Distance?";
			getline(cin, CCEDistance);
			cout << "What was CCE's Time?";
			getline(cin, CCETime);
		}
		else if (choice == 2) {
			cout << "What was " + oppTeamName + "'s Score?";
			getline(cin, OPPScore);
			cout << "What was " + oppTeamName + "'s Distance?";
			getline(cin, OPPDistance);
			cout << "What was " + oppTeamName + "'s Time?";
			getline(cin, OPPTime);
		}
		else if (choice == 3) {
			cout << "What was CCE's Score?";
			getline(cin, CCEScore);
			cout << "What was " + oppTeamName + "'s Score?";
			getline(cin, OPPScore);
		}


		cout << "if the game is over type end else type y? ";
		cin >> userInput;
	}

	gameWinner = getInput("Who won the game(CCE[1] or " + oppTeamName + "[2])? ");
	if (gameWinner == 1) {
		winner = "CCE";
	}
	else if (gameWinner == 2) {
		winner = oppTeamName;
	}
	else
		winner = "no winner determined";

	//outputs the totals for the Game
	{
		tfout << setw(NAME_SPACING) << right << "the winner of the game was " << winner << endl
			<< endl << setw(NAME_SPACING) << right << "TOTAL FIGHTS: " << teamFights << endl
			<< setw(NAME_SPACING) << right << "CCE ults used per fight: " << totalCCEUltsUsed << endl
			<< setw(NAME_SPACING) << right << "OPP ults used per fight: " << totalOPPUltsUsed << endl
			<< setw(NAME_SPACING) << right << "CCE fight wins: " << CCETeamFightWins << endl
			<< setw(NAME_SPACING) << right << "OPP fight wins: " << OPPTeamFightWins << endl
			<< setw(NAME_SPACING) << right << "Unassigned fight wins: " << unassignedFights << endl;

		fout << "Game Totals,"
			<< teamFights << ","
			<< totalCCEUltsUsed << ","
			<< totalOPPUltsUsed << ","
			<< CCETeamFightWins << ","
			<< OPPTeamFightWins << ",";
	}//outputs the totals for the game


	fout.close();
}


int stringToInt(string s) {
	// object from the class stringstream 
	stringstream geek(s);

	int x = 0;
	geek >> x;
	return x;
}

inline bool isInteger(const std::string& s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char* p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

int getInput(string question, int maxOutput, int minOutput) {
	string inputString = "default";
	int outputNumber = -1;

	do {
		cout << question;
		cin >> inputString;
		//cin >> inputString;
		outputNumber = stringToInt(inputString);
		//cout << minOutput<<";"<<maxOutput << inputString;

		if (!(outputNumber <= maxOutput && outputNumber >= minOutput)) {
			cout << endl << "That number is out of bounds of the range: " << minOutput << "to" << maxOutput << endl << endl;
		}
	} while (!isInteger(inputString) || (outputNumber > maxOutput || outputNumber < minOutput));
	return outputNumber;

}

int getInput(string question) {
	string inputString;
	int outputNumber = -1;

	while (!isInteger(inputString))
	{
		cout << question;
		getline(cin, inputString);
		//cin >> inputString;
		outputNumber = stringToInt(inputString);
	}
	return outputNumber;
}


