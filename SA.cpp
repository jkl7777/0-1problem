#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

struct graph {
    int fir, sec;
};

vector<string> allString;
vector<graph> Graph;
vector<bool> Node;

int edges;
int nodes;
time_t Init_Time = time(0);

bool TimeOut(int timegap)
{
    time_t tmpCost_time = time(0);
    double time_difference = difftime(tmpCost_time, Init_Time);
    if (timegap > time_difference)
        return 1;
    else
        return 0;
}
void ReadFile(string fileName)
{
    string loadline;
    ifstream file(fileName);

    if (file.is_open()) {
        while (getline(file, loadline)) {
            allString.push_back(loadline);
        }
        file.close();
    }
    else cout << "Unable to open file";
}
vector<string> Split(string str)
{
    char delim = ' '; 
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}
void SplitSave()
{
    vector<string> splitString;
    graph str_To_Int;
    splitString = Split(allString[0]);
    edges = stoi(splitString[0]);
    nodes = stoi(splitString[1]);
    for (int i = 1; i < allString.size(); i++)
    {
        splitString = Split(allString[i]);
        str_To_Int.fir = stoi(splitString[0]);
        str_To_Int.sec = stoi(splitString[1]);
        Graph.push_back(str_To_Int);
    }
    allString.clear();
}
int costValue(const  vector<bool>& InitNode)
{
    int cost = 0;
    int graphSize = Graph.size();
    for (int i = 0; i < graphSize; i++)
    {
        if (InitNode[Graph[i].fir - 1] != InitNode[Graph[i].sec - 1])
            cost += 1;
    }
    return cost;
}
void Init_nodeMake()
{
    int nodes_0 = nodes / 2;
    for (int i = 0; i < nodes; i++)
    {
        if (i <= nodes_0)   Node.push_back(0);
        else   Node.push_back(1);
    }
}
vector<bool> Swapnode(vector<bool> currentSolution)
{
    while (1) {
        int node1 = rand() % currentSolution.size();
        int node2 = rand() % currentSolution.size();
        int a = currentSolution[node1];
        int b = currentSolution[node2];
        if (currentSolution[node1] != currentSolution[node2]) {       
            currentSolution[node1] = b;     
            currentSolution[node2] = a;        
            break;
        }
    }
    return currentSolution;
}
bool AcceptanceBad(int gap, double initTemp)
{
    double randomValue = (double)rand() / (RAND_MAX + 1.0);
    if (randomValue <= exp(-gap / initTemp))
    {
        return 1;
    }

    return 0;
}
void SA(double initTemp, double endTemp, double cool_Rate, int iter, int time_default)
{
    vector<bool> tmpNode = Node;
    vector<bool> bestNode = tmpNode;
    int tmpCost = costValue(tmpNode);
    int BestCost = tmpCost;
    double Nowtmp = initTemp;
    time_t startTime = time(0);
 
    cout << "Initial temperature = " << initTemp << "\n";
    cout << "Temperature annealing coefficient: " << cool_Rate << "\n";
    cout << "Initial Cost: " << tmpCost << "\n";

    while (Nowtmp > endTemp && TimeOut(time_default))
    {
        for (int i = 0; i < iter; i++)
        {
            vector<bool> SwapNode = Swapnode(tmpNode);
            int newCost = costValue(SwapNode);
            int gap = newCost - tmpCost ;        
            if ((gap < 0) || AcceptanceBad(gap, Nowtmp))
            {
                tmpNode = SwapNode;
                tmpCost = newCost;
                if (newCost < BestCost)
                {
                    bestNode = SwapNode;              
                    BestCost = costValue(bestNode);
                }
            }          
        }
        Nowtmp *= cool_Rate;    
        cout<< fixed << setprecision(5) << "Cost at temperature " << Nowtmp << " " << BestCost << "\n";
    }
    time_t endTime = time(0);
    int  time = difftime(endTime, startTime);
    cout << "Best cost " << BestCost  << "\ttime:" << time << "\nThe final temperature: " << Nowtmp << "\n";
}

int main()
{
    double cool_Rate = 0.98;
    double initTemp = 10;
    double endTemp = 0.01;
    int iter = 20000;
    int time_default = 300;

    srand(time(0));

    cout << "檔案提示: s27o.s298o.s386o.s510o.s953o.s1448o.s5378o.s13207o.s15850o.s35932o.s38417o.s38584o\n";
    cout << "請輸入檔案:";
    cout << fileName<<"\n";
    cin >> fileName;

    ReadFile(fileName);
    SplitSave();
    Init_nodeMake();
    SA(initTemp, endTemp, cool_Rate, iter, time_default);

}