#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <cctype>
#include <chrono>
#include <tuple>

using engine = std::mt19937;

using std::string;
using std::cin;
using std::cout;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::to_string;
using std::endl;
using std::setw;


int createFileWithRandomNumbers(const string& fileName, const int numbersCount, int minNumberValue, int maxNumberValue)
{
    if (numbersCount < 0 || fileName.empty())
    {
        return -2;
    }

    if (minNumberValue > maxNumberValue) {
        int t = minNumberValue;
        minNumberValue = maxNumberValue;
        maxNumberValue = t;
    }

    std::random_device os_seed;
    const int seed = os_seed();

    engine generator(seed);
    std::uniform_int_distribution<int> distribute(minNumberValue, maxNumberValue);

    ofstream outf(fileName);
    if (!outf)
    {
        return -1;
    }

    for (int i = 0; i < numbersCount; i++)
    {
        outf << distribute(generator) << " ";
    }

    outf.close();
    return 0;
}

int deleteElement(const string& filename, const int element) {
    ifstream input(filename);
    ofstream output("temp.txt");
    int count = 0;

    if (!input.is_open() || !output.is_open())
    {
        throw string("file did not opened deleteElement(string)");
    }

    int val;
    while (input >> val) {
        if (val == element) {
            count++;
        }
        else {
            output << val << " ";
        }
    }

    output << element;

    input.close();
    output.close();

    remove(filename.c_str());
    return count;
}

void fillIpAndMs(int* ip, int* ms, const int size)
{
    ip[size - 1] = ms[size - 1] = 0;
    for (int i = 0; i < size - 1; i++)
    {
        ip[i] = ms[i] = 1;
    }
}

void calculatingIdealPartiosionAndMissingSegments(int* ip, int* ms, const int size)
{
    int temp = ip[0];
    for (int i = 0; i < size - 1; i++)
    {
        ms[i] = ip[i + 1] - ip[i] + temp;
        ip[i] = ip[i + 1] + temp;
    }
}

int* partition(const string& fileName, const int filesCount, const int , int& level, int* idealPartition)
{
    const string name("test");
    vector<ofstream*> auxiliaryFiles;
    auxiliaryFiles.reserve(filesCount);

    // Open files
    ifstream data(fileName);
    for (int i = 0; i < filesCount - 1; i++)
    {
        ofstream* testFile = new ofstream(name + to_string(i) + ".txt", std::ios::in | std::ios::trunc);
        if (!testFile->is_open())
        {
            throw string("axiliary files does not opened polyphaseSort(string, int)");
        }
        auxiliaryFiles.push_back(testFile);
    }

    int* missingSegments = new int[filesCount];
    fillIpAndMs(idealPartition, missingSegments, filesCount);

    int currentIncSequence;
    int i = 0;
    if (data >> currentIncSequence)
    {
        while (i < filesCount - 1)
        {

            int nextIncSequence;

            while (data >> nextIncSequence)
            {
                if (currentIncSequence <= nextIncSequence)
                {
                    (*auxiliaryFiles[i]) << currentIncSequence << " ";
                    currentIncSequence = nextIncSequence;
                }
                else
                {
                    (*auxiliaryFiles[i]) << currentIncSequence << " ";
                    (*auxiliaryFiles[i]) << INT_MIN << " ";
                    currentIncSequence = nextIncSequence;
                    break;
                }

            }
            missingSegments[i]--;
            if (!data || nextIncSequence == INT_MIN)
            {
                break;
            }

            if (missingSegments[i] < missingSegments[i + 1])
            {
                i++;
            }
            else
            {
                if (missingSegments[i] == 0)
                {
                    level++;
                    i = 0;
                    calculatingIdealPartiosionAndMissingSegments(idealPartition, missingSegments, filesCount);
                }
                else
                {
                    i = 0;
                }
            }

        }
    }


    //cout << "Partition:\n";
    // reallocate memory
    data.close();
    for (int j = 0; j < filesCount - 1; j++)
    {
        auxiliaryFiles[j]->close();
        //printFile(name + to_string(j) + ".txt", );
        delete auxiliaryFiles[j];
    }

    return missingSegments;
}

int isFileContainsSortedArray(const string& fileName)
{
    if (fileName.empty())
    {
        return -2;
    }

    ifstream inf(fileName);
    if (!inf.is_open())
    {
        return -1;
    }

    if (inf.eof())
    {
        return 0;
    }

    int temp;
    int current;

    inf >> temp;
        while (inf >> current)
        {
            if (temp > current)
            {
                return 1;
            }
            temp = current;
        }

    return 0;
}

void print(const int* array, const int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}



void printFile(const string& fileName, const int )
{
    ifstream f;
    f.open(fileName);
    cout << fileName << ": ";

    int temp;
    while (f >> temp)
    {
        if (temp == INT_MIN)
            cout << "| ";
        else
            cout << temp << " ";
    }
    cout << endl;
    f.close();
}

void oneRunMerge(vector<fstream*>& files, const int filesCount, vector<bool>& filesToMerge)
{
    int* buffer = new int[filesToMerge.size()];
    for (unsigned int i = 0; i < filesToMerge.size(); i++)
    {
        if (filesToMerge[i])
        {
            if (!((*files[i]) >> buffer[i]))
            {
                buffer[i] = INT_MIN;
            }
        }
        else
        {
            buffer[i] = INT_MIN;
        }
    }

    int j = (int)filesToMerge.size();
    while (true)
    {
        int minIndex = -1;
        int min_value;

        for (unsigned int i = 0; i < filesToMerge.size(); i++) {
            if (filesToMerge[i] && (buffer[i] != INT_MIN) && (minIndex == -1 || buffer[i] < min_value))
            {
                minIndex = i;
                min_value = buffer[i];
            }
        }

        if (minIndex == -1 || buffer[minIndex] == INT_MIN) {
            break;
        }

        (*files[files.size() - 1]) << min_value << " ";
        (*files[minIndex]) >> buffer[minIndex];
        if (files[minIndex]->eof())
        {
            filesToMerge[minIndex] = false;
            j--;
        }
    }

    (*files[files.size() - 1]) << INT_MIN  << " ";
    delete[] buffer;
}

void inputSegment(const string& from, const string& to)
{
    ifstream f(from);
    ofstream t(to, std::ios::out | std::ios::app);
    if (!f.is_open() || !t.is_open())
    {
        throw 1;
    }

    int val;
    while (f >> val)
    {
        if (val == INT_MIN )
        {
            break;
        }
        t << val << " ";
    }

    f.close();
    t.close();
}

void merge(const string& fileName, const int filesCount, int& level, int* missingSegments, int* idealPartition)
{
    const string name("test");
    vector<fstream*> auxiliaryFiles;
    vector<string> names(filesCount);
    auxiliaryFiles.reserve(filesCount);

    // Open file
    for (int i = 0; i < filesCount - 1; i++)
    {
        names[i] = name + to_string(i) + ".txt";
        fstream* testFile = new fstream(names[i], std::ios::in);
        if (!testFile->is_open())
        {
            throw string("axiliary files does not opened polyphaseSort(string, int)");
        }
        auxiliaryFiles.push_back(testFile);
    }
    names[filesCount - 1] = name + to_string(filesCount - 1) + ".txt";
    auxiliaryFiles.push_back(new fstream(names[filesCount - 1], std::ios::out));

    while (level != 0)
    {
        int lastIdealPartition = idealPartition[filesCount - 2];
        while (lastIdealPartition != 0)
        {
            vector<bool> filesToMerge(filesCount - 1, false);
            int numberOfFilesToMerge = 0;
            for (int i = 0; i < filesCount - 1; i++)
            {
                if (missingSegments[i] > 0)
                {
                    missingSegments[i]--;
                }
                else
                {
                    filesToMerge[i] = true;
                    numberOfFilesToMerge++;
                }
            }

            if (numberOfFilesToMerge == 0)
            {
                missingSegments[filesCount - 1]++;
            }
            else
            {
                oneRunMerge(auxiliaryFiles, numberOfFilesToMerge, filesToMerge);
            }
            lastIdealPartition--;
        }


        fstream* tempFile = auxiliaryFiles[filesCount - 1];

        // problem
        auxiliaryFiles[filesCount - 2]->close();
        auxiliaryFiles[filesCount - 2]->open(names[filesCount - 2], std::ios::out);
        
        auxiliaryFiles[filesCount - 1]->close();
        auxiliaryFiles[filesCount - 1]->open(names[filesCount - 1], std::ios::in);

        if (!(auxiliaryFiles[filesCount - 2]->is_open()) || !(auxiliaryFiles[filesCount - 1]->is_open()))
        {
            throw 1;
        }

        int z = idealPartition[filesCount - 2];
        int msTemp = missingSegments[filesCount - 1];
        string tempName = names[filesCount - 1];

        for (int i = filesCount - 1; i > 0; i--)
        {
            names[i] = names[i - 1];
            auxiliaryFiles[i] = auxiliaryFiles[i - 1];
            missingSegments[i] = missingSegments[i - 1];
            idealPartition[i] = idealPartition[i - 1] - z;
        }

        level--;
        names[0] = tempName;
        auxiliaryFiles[0] = tempFile;
        missingSegments[0] = msTemp;
        idealPartition[0] = z;
    }

    for (int i = 0; i < filesCount; i++)
    {
        auxiliaryFiles[i]->close();
        delete auxiliaryFiles[i];
    }
    //printFile(names[0], );
    inputSegment(names[0], fileName);
}

void inputs(const string& fileName, const int borderCount)
{
    ofstream file(fileName, std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        throw 1;
    }

    for (int i = 0; i < borderCount; i++)
    {
        file << INT_MIN << " ";
    }
}

void polyphaseSort(const string& fileName, int filesCount)
{
    if (filesCount < 3)
    {
        filesCount = 3;
    }
    try
    {
        int borderCount = deleteElement(fileName, INT_MIN);
        int level = 1;

        int* idealPartition = new int[filesCount];
        int* missingSegments = partition(fileName, filesCount, INT_MIN, level, idealPartition);
        cout << setw(10) <<  level;

        inputs(fileName, borderCount);

        merge(fileName, filesCount, level, missingSegments, idealPartition);

        delete[] missingSegments;
        delete[] idealPartition;
    }
    catch (...)
    {
        throw 1;
    }
}

int findMinElement(const int* arr, const int size)
{
    int minElement = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (minElement > arr[i])
        {
            minElement = arr[i];
        }
    }

    return minElement;
}



void printFile(fstream& f)
{
    int temp;
    while (f >> temp)
    {
        if (temp == INT_MIN)
            cout << "| ";
        else
            cout << temp << " ";
    }
    cout << endl;
}

int test(const string& fileName, const int fileNumbers, const int numberCount, const int minNumber, const int maxNumber)
{
    if (createFileWithRandomNumbers(fileName, numberCount, minNumber, maxNumber)) {
        return -1;
    }

    const auto start = std::chrono::steady_clock::now();
    polyphaseSort(fileName, fileNumbers);
    const auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << setw(20) << std::setprecision(8) << elapsed_seconds.count();

    if (isFileContainsSortedArray(fileName)) {
        return -2;
    }

    return 1;
}

string ggt(string s){
    return "\x1b[32m" + s + "\x1b[30m";
}

int main()
{
    cout.setf(std::ios::fixed);
    const string fileName("data.txt");
    int maxNumber = INT_MAX-10;
    int minNumber = INT_MIN+10;

    cout << setw(12) << "count |";
    cout << setw(12) << "range |";
    cout << setw(10) << "files |";
    cout << setw(10) << "phases |";
    cout << setw(20) << "time |";
    cout << setw(10) << "result" << endl;
    
    for (int numberCount = 10000; numberCount <= 1000000; numberCount *= 10) {
        
        for (maxNumber = 10, minNumber = -10; maxNumber <= 1000000000; maxNumber *= 10, minNumber *= 10) {
            
            for (int fileCount = 3; fileCount <= 6; fileCount++) {
                
                for (int i = 0; i < 10; i++) {
                    cout << setw(12) << numberCount ;
                    cout  << setw(12) << maxNumber * 2;
                    cout << setw(10) << fileCount;
                    switch (test(fileName, fileCount, numberCount, minNumber, maxNumber)) {
                    case 1:
                        cout << setw(10) << "[OK]" << endl;
                        break;

                    case -1:
                        cout << "Test failed: can't create file." << endl;
                        break;

                    case -2:
                        cout << "Test failed: file isn't sorted." << endl;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
