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



int main() {
    
    Knapsack knapsack;
    vector <Item> items;
    vector<Item>::iterator it;
    it = items.begin();
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
            
            cout<<"name "<<name<<endl;
            temp.setName(name);
            int cost1 = atoi(cost.c_str());
            cout<<"cost "<<cost1<<endl;
            temp.setCost(cost1);
            int value1 = atoi(value.c_str());
            cout<<"value "<<value1<<endl;
            temp.setValue(value1);
            items.insert(it, temp);
        }
    }
    fs.close();
    
    cout<<"Highest Value First: "<< endl;
    cout<<"Lowest Cost First: "<<endl;
    cout<<"Highest Ratio First: "<<endl;
    cout<<"Partial Knapsack: "<<endl;
}
