// Written By Paul Onyebuchi
// Title: Systen Log Processor
// Description: This program reads a log log file, counts occurences of critical hardware conditions and writes the result to a CSV file

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Global constants
const int SIZE = 3;
const string INPUT_FILE_NAME = "system_dump.txt",
OUTPUT_FILE_NAME = "error_report.csv";
const string ERROR_WORDS[SIZE] = { "ERROR", "WARNING", "CRITICAL" }; // Words to search for


// Function prototypes
bool processLogs(ifstream& fileStream, int [], const string []);
void writeCSVReport(ofstream& outputStream, int[], const string[], int);


int main() {
	// Variables
	int errorCounts[SIZE]{};

	// Reads the file system_dump.txt
	// - open file and associate with file name
	ifstream inputFile(INPUT_FILE_NAME);

	// Check if file opened
	if (!inputFile.is_open())
	{
		cerr << "Failed to open file! \n";
		return 1;
	}
	else
	{
		// Search for keywords: ERROR, WARNING, CRITICAL in the log file
		// count number of times each error occurs
		processLogs(inputFile, errorCounts, ERROR_WORDS);
		inputFile.close();
	}

	// Output clear summary to a file: error_report.csv
	ofstream outputFile(OUTPUT_FILE_NAME);

	if (!outputFile.is_open())
	{
		cerr << "Failed to open output File. \n";
		return 1;
	}
	else
		writeCSVReport(outputFile, errorCounts, ERROR_WORDS, SIZE);
	outputFile.close();


	return 0;
}

// Functions
//- This function reads the file and searches for all ocurrences of the keyword
bool processLogs(ifstream& fileStream, int counter[], const string errorWords[])
{
	string logLine{}; // The log will be read line-by-line rather than word-by-word
	
	// - Reading the file line by line
	while (getline(fileStream, logLine))
	{
		for (int index{}; index <= SIZE - 1; index++)
		{
			if (logLine.find(errorWords[index]) != string::npos)
				// Increment the corresponding error counter array element
				counter[index]++;
		}
	}
	return true;
}


// This function creates a summary of reports from error log
void writeCSVReport(ofstream& outputStream, int counter[], const string errorWords[], int arrSize)
{
	outputStream << "Log_error, Error_count \n";

	for (int index{}; index <= arrSize-1; index++)
	{
		outputStream << errorWords[index] << "," << counter[index] << " \n";
	}

}