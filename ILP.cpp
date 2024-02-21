#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
struct graph{
    string firGraph, secGraph;
};
vector<string> allString;
vector<string> Save;
vector<graph> Graph;
int connect ;
vector<string> str_arr1 = { "s27o", "s298o", "s386o", "s510o" ,"s953o","s1448o","s5378o","s13207o","s15850o","s35932o","s38417o","s38584o" };
void ReadFile(string fileName){
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
vector<string> Split(string str){
    char delim = ' ';
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}
void splitSave(){ 
    graph str_To_Int;
    vector<string> splitString;
    splitString = Split(allString[0]);
    connect = stoi(splitString[1]);
    for (int i = 1; i < allString.size(); i++){
        splitString = Split(allString[i]);
        str_To_Int.firGraph = splitString[0];
        str_To_Int.secGraph = splitString[1];
        Graph.push_back(str_To_Int);
    }
}
void SaveFun(){
    string save = "min: ";
    for (int i = 1; i < allString.size(); i++){
        save += "x" + to_string(i);
        if (i != allString.size()-1) save += " + ";
        else{
            save += ";";
            Save.push_back(save);
            save.clear();
        }    
    }
    for (int i = 0; i < connect; i++){
        save += "y" + to_string(i+1);
        if (i != connect - 1) save += " + ";
        else{
            save += " = "+ to_string((connect-1)/2) +";";
            Save.push_back(save);
            save.clear();
        }        
    }
    for (int i = 0; i < Graph.size(); i++){
        string save1 = "x" + to_string(i + 1) + " <= " + "y" + Graph[i].firGraph + " + " + "y" + Graph[i].secGraph + " ;";
        string save2 = "x" + to_string(i + 1) + " >= " + "y" + Graph[i].firGraph + " - " + "y" + Graph[i].secGraph + " ;";
        string save3 = "x" + to_string(i + 1) + " >= " + "y" + Graph[i].secGraph + " - " + "y" + Graph[i].firGraph + " ;";
        string save4 = "x" + to_string(i + 1) + " <= " + "2 - " + "y" + Graph[i].firGraph + " - " + "y" + Graph[i].secGraph + " ;";
        Save.push_back(save1);
        Save.push_back(save2);
        Save.push_back(save3);
        Save.push_back(save4);
    }
    for (int i = 0; i < Graph.size(); i++) {
        string x = "bin x" + to_string(i+1) + ";";
        Save.push_back(x);
        string y = "bin y" + to_string(i+1) + ";";
        Save.push_back(y);
    } 
}
void OutputFile(string fileName) {
    ofstream outputFile("Model_"+fileName );
    for (int i = 0; i < Save.size(); i++){
        outputFile << Save[i] <<"\n";
    }
    outputFile.close();
    allString.clear();
    Save.clear();
    Graph.clear();
}
int main() {
    for (int i = 0; i < str_arr1.size(); i++) {
        cout << "工作進度如下: ( " + to_string(i + 1) + " / " + to_string(str_arr1.size()) + ")  " + str_arr1[i] + "\n";
        ReadFile(str_arr1[i]);
        splitSave();
        SaveFun();
        OutputFile(str_arr1[i]);
    }
}