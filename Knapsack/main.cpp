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


void printItemVector(vector<Item> items)
{
    for (int i=0; i < items.size(); i++){
        cout << "Name: " << items[i].getName() << " Cost:" << items[i].getCost() << " Value: " << items[i].getValue() << endl;
    }
}

int main() {
    
    Knapsack knapsack;
    vector <Item> items;
    string filename;
    cout <<"Insert file name: ";
    cin >> filename;
    Item temp;
    fstream fs;
    fs.open (filename);
    if (fs.is_open())
    {
        string line1;
        int maxWeight;
        getline(fs, line1);
        stringstream ss(line1);
        ss >> maxWeight;
        
        knapsack.setLimit(maxWeight);
        
        while(getline(fs, line1))//get all the items
        {
            
            std::istringstream ss(line1);
            std::string token;
            int count=0;
            string name;
            string cost;
            string value;
            string i;
            while(getline(ss, token, ','))
            {
                
                if(count==0)
                    name=token;
                else if(count==1)
                    cost=token;
                else
                    value=token;
                
                count++;
            }
            
            //cout<<"name "<<name<<endl;
            temp.setName(name);
            int cost1 = atoi(cost.c_str());
            //cout<<"cost "<<cost1<<endl;
            temp.setCost(cost1);
            int value1 = atoi(value.c_str());
            //cout<<"value "<<value1<<endl;
            temp.setValue(value1);
            items.push_back(temp);
        }
    }
    fs.close();

    cout << endl << "Limit: " << knapsack.getLimit() << endl << endl;

    sort(items.begin(), items.end(), Knapsack::sortHighestValue);
    cout<<"Highest Value First: "<< endl;
    //printItemVector(items);    
    cout << "Solution: "<< Knapsack::calculateGreedySolution(items, knapsack) << endl << endl;

    sort(items.begin(), items.end(), Knapsack::sortLowestCost);
    cout<<"Lowest Cost First: "<<endl;
    //printItemVector(items);
    cout << "Solution: "<< Knapsack::calculateGreedySolution(items, knapsack) << endl << endl;

    sort(items.begin(), items.end(), Knapsack::sortValueCostRatio);
    cout<<"Highest Ratio First: "<<endl;
    //printItemVector(items);
    cout << "Solution: "<< Knapsack::calculateGreedySolution(items, knapsack) << endl << endl;
    
    sort(items.begin(), items.end(), Knapsack::sortPartialTotal);
    cout<<"Partial Knapsack: "<<endl;
    cout << "THIS STILL NEEDS TO BE FIXED" << endl;
    cout << "Solution: "<< Knapsack::calculatePartialKnapsackSolution(items, knapsack) << endl << endl;
    //printItemVector(items);
}
