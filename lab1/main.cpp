#include <iostream>
#include <stdio.h>
#include "porter.h"
#include <map>
#include <regex>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <boost/algorithm/string.hpp>
using namespace std;

regex puncmark(",|\\.|!|\\?|\\\"|…|:|-|\\(|\\)|—|\\[|\\]");//edit for punctuation

bool isUniqWord(string word,map <string,int>* filter)
{
    if (filter->count(word))
        return false;
    return true;
}
void statistic(string wordFIle, map<string,int>* store,map<string,int>* filter) { //counting frequences
    if (regex_search(wordFIle,puncmark)) {
        wordFIle=regex_replace(wordFIle,puncmark,"");
    }
    if (wordFIle=="" || wordFIle.length()<8) return;
    porter(&wordFIle);
    if (store->count(wordFIle)==1) {                       //addition of old element
        (*store)[wordFIle]++;
    }
    else {
        if (isUniqWord(wordFIle, filter) && wordFIle.length()>8)//addition of new element
            store->insert ( pair<string,int>(wordFIle,1) );
    }
}

void countKeyWords(map <string,int>* storeFile1,char filename[100],map <string,int>* filter) {
    string wordFIle;
    ifstream in;
    int amount=0;
    in.open(filename);
    if (!in.is_open()) {
        cout<<"trouble with"<<filename<<endl;
        //return -1;
    }
    while (in>>wordFIle) {
        statistic(wordFIle, storeFile1,filter);
        amount++;
    }
    in.close();
    //return amount;
}
string getText(char filename[100]) {
    string wordFIle;
    string result;
    ifstream in;
    int amount=0;
    in.open(filename);
    if (!in.is_open()) {
        cout<<"trouble with"<<filename<<endl;
        return "ERROR";
    }
    while (in>>wordFIle) {
        if (wordFIle=="!" || wordFIle=="?")
        {
            wordFIle=".";
        }
        result=result+" "+wordFIle;
        amount++;
    }
    in.close();
    return result;
}

bool compare(map<string,int>::value_type &i1, map<string,int>::value_type &i2)
{
    return i1.second<i2.second;
}
bool veccompare(vector<int>::value_type &i1, vector<int>::value_type &i2)
{
    return i1<i2;
}

void outputMAP(map<string,int> store) {
    while(store.size()!=0)
    {
        auto it =max_element(store.begin(), store.end(),compare);
        cout << it->first<<" : "<<it->second<<endl;
        store.erase(it);
    }
    
}
void WithoutPorterstatistic(string wordFIle, map<string,int>* store) { //counting frequences
    if (regex_search(wordFIle,puncmark)) {
        wordFIle=regex_replace(wordFIle,puncmark,"");
    }
    if (wordFIle=="") return;
    if (store->count(wordFIle)==1) {
        //addition of old element
        (*store)[wordFIle]++;
    }
    else {                                            //addition of new element
        store->insert ( pair<string,int>(wordFIle,1) );
    }
}
int countWordsPA(map <string,int>* storeFile1,char filename[100]) {
    string wordFIle;
    ifstream in;
    int amount=0;
    in.open(filename);
    if (!in.is_open()) {
        cout<<"trouble with"<<filename<<endl;
        return -1;
    }
    while (in>>wordFIle) {
        WithoutPorterstatistic(wordFIle, storeFile1);
        amount++;
    }
    in.close();
    return amount;
}
vector<string> split_string(const std::string& str,
                            const std::string& delimiter)
{
    vector<string> strings;
    
    string::size_type pos = 0;
    string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
    
    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));
    
    return strings;
}

bool isCounted(const vector<string> &temp,string curstr)
{
    for (int i=0; i<temp.size(); i++) {
        if (temp[i]==curstr) {
            return true;
        }
    }
    return false;
}

int getMark(const string &sentence, map <string,int> &storeFile)
{
    double result = 0;
    vector<string> words=split_string(sentence," ");
    
    vector<string> temp;
    for (int i=0;i<words.size();i++)
    {
        if (storeFile.count(words[i]) && words[i].length()>6) {
            porter(&words[i]);
            if (!isCounted(temp, words[i]))
            {
                result+=storeFile[words[i]]/sqrt(words.size());
                temp.push_back(words[i]);
            }
            
        }
    }
    return round(result);
}
void getAnnot(vector<string> &text,map <string,int> &storeFile)
{
    vector<int> statka;
    for (int i = 0; i<text.size(); i++) {
        statka.push_back(getMark(text[i], storeFile));
    }
    int max=INT16_MAX;
    int cv=0;
    while(max>0 && cv<2) //
    {
        auto it =max_element(statka.begin(), statka.end())-statka.begin();
        if (it-1>=0)
        {
            cout << text[it-1]<<endl;
            statka[it-1]=-1;
        }
        cout << text[it]<<endl;
        if (it+1<text.size())
        {
            cout << text[it+1]<<endl;
            statka[it+1]=-1;
        }
        max=statka[it];
        statka[it]=-1;
        cv++;
    }
}

int main()
{
    char filename1[40]="/Users/v144/Documents/fortest/2.txt";
    char filename2[100]="/Users/v144/Documents/fortest/cleaning.txt";
    map <string,int> filter;
    map <string,int> storeFile1;
    countWordsPA(&filter, filename2);
    countKeyWords(&storeFile1, filename1,&filter);
    string k=getText(filename1);
    vector<string> text=split_string(k, ".");
    getAnnot(text, storeFile1);
    outputMAP(storeFile1);
    return 0;
}

