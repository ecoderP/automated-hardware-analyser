// Written By Paul Onyebuchi
// Title: System Log Processor
// Description: This program reads a log file, counts log lines with configured severity keywords and writes the result to a CSV file

#include <iostream>
#include <string>
#include <fstream>
//using namespace std;

// Global constants
const int SIZE = 3;
const std::string INPUT_FILE_NAME = "system_dump.txt",
OUTPUT_FILE_NAME = "error_report.csv";
const std::string ERROR_WORDS[SIZE] = { "ERROR", "WARNING", "CRITICAL" }; // Words to search for


// Function prototypes
bool processLogs(std::ifstream& fileStream, int [], const std::string []);
bool writeCSVReport(std::ofstream& outputStream, const int[], const std::string[], int);


int main() {
	// Variables
	int errorCounts[SIZE]{};

	// Reads the file system_dump.txt
	// - open file and associate with file name
	std::ifstream inputFile(INPUT_FILE_NAME);

	// Check if file opened
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open file! \n";
		return 1;
	}
	
	// Search for keywords: ERROR, WARNING, CRITICAL in the log file
	// count number of log lines containing each keyword
	if (!processLogs(inputFile, errorCounts, ERROR_WORDS))
	{
		std::cerr << "Failed while processing log file.\n";
		return 2;
	}

	inputFile.close();


	// Writing log-level counts to: error_report.csv
	// Open output report
	std::ofstream outputFile(OUTPUT_FILE_NAME);

	if (!outputFile.is_open())
	{
		std::cerr << "Failed to open output File. \n";
		return 1;
	}

	// Write report
	if (!writeCSVReport(outputFile, errorCounts, ERROR_WORDS, SIZE))
	{
		std::cerr << "Failed to write report";
		return 3;
	}

	outputFile.close();


	return 0;
}

// Functions
//- This function reads the file and searches for log lines containing a keyword
bool processLogs(std::ifstream& fileStream, int counter[], const std::string errorWords[])
{
	std::string logLevel{};
	
	while (getline(fileStream, logLevel))
	{
		for (int index{}; index < SIZE; ++index)
		{
			if (logLevel.find(errorWords[index]) != std::string::npos)
				// Increment the corresponding error counter array element
				counter[index]++;
		}
	}
	return true;
}


// This function creates a summary of reports from error log
bool writeCSVReport(std::ofstream& outputStream, const int counter[], const std::string errorWords[], int arrSize)
{
	outputStream << "Log_Level,Line_Count \n";

	for (int index{}; index < arrSize; ++index)
	{
		outputStream << errorWords[index] << "," << counter[index] << " \n";
	}
	return true;

}