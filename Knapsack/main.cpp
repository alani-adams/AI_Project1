//
//  main.cpp
//  AI_Project1
//
//  Created by Alani Peters on 1/19/17.
//  Copyright © 2017 Alani Peters. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#include "Header.h"



int main(int argc, const char * argv[]) {
    
vector:KnapsackItems
    
    Knapsack knapsack;
    vector <Item> items;
    Item temp;
    fstream fs;
    fs.open (argv[0]);
    if (fs.is_open())
    {
        string line1;
        string maxWeight;
        getline(fs, line1);
        stringstream ss(line1);
        ss >> maxWeight;
        
        knapsack.setLimit(<int>maxWeight);
        
        while(getline(fs, line1))//get all the items
        {
            string name;
            string weight;
            string value;
            ss >> name;
            temp.setName(name);
            ss >> weight;
            temp.setWeight(weight);
            ss >> value;
            temp.setValue(value);
            items.insert(temp);
        }
    }
    fs.close();
    
    cout<<"Highest Value First: "<< endl;
    cout<<"Lowest Cost First: "<<endl;
    cout<<"Highest Ratio First: "<<endl;
    cout<<"Partial Knapsack: "<<endl;
}
