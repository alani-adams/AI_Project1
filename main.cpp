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
#include <cstdio>
#include <ctime>
#include <math.h>
#include <cmath>



#include "Header.h"
#include "bst.h"

using namespace std;

/*void printItemVector(vector<Item> items)
{
    for (int i=0; i < items.size(); i++){
        cout << "Name: " << items[i].getName() << " Cost:" << items[i].getCost() << " Value: " << items[i].getValue() << endl;
    }
}*/

//template <typename T>
Tree<vector <Item> > createTree(vector<Item> items, Knapsack knapsack)
{
    Tree<vector <Item> > bst1;
    initialize(bst1);

    return insert(bst1, items, knapsack);
}

Tree<vector <Item> > createTreePrune(vector<Item> items, Knapsack knapsack)
{
    Tree<vector <Item> > bst1;
    initialize(bst1);
    return insertPrune(bst1, items, knapsack);
}

int main() 
{
    
    Knapsack knapsack;
    vector<Item> items;
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

    //===========================
    float minimumVal = 0;
    float minimumCost = 0;
    float minimum = 0;
    bool highestValueMin = false;
    vector<Item> minItems;


    sort(items.begin(), items.end(), Knapsack::sortHighestValue);
    cout<<"Highest Value First: "<< endl;
    //printItemVector(items);
    float a = Knapsack::calculateGreedySolution(items, knapsack, false, true, false);  
    cout << "Solution: "<< a << endl << endl;
    knapsack.setHighestValueTotal(a);

    if(knapsack.getHighestValue() >= minimumVal)
    {
        minimumVal = knapsack.getHighestValue();
        minimumCost = knapsack.getHighestValueCost();
        highestValueMin = true;
        minItems = knapsack.getHighestValueItems();
    }

    //===========================

    bool lowestCostMin = false;

    sort(items.begin(), items.end(), Knapsack::sortLowestCost);
    cout<<"Lowest Cost First: "<<endl;
    //printItemVector(items);
    float b = Knapsack::calculateGreedySolution(items, knapsack, false, false, true);
    cout << "Solution: "<< b << endl << endl;
    knapsack.setLowestCostTotal(b);

    if(knapsack.getLowestCost() >= minimumVal)
    {
        minimumVal = knapsack.getLowestCost();
        minimumCost = knapsack.getLowestCostCost();
        lowestCostMin = true;
        minItems = knapsack.getLowestCostItems();

    }
    //===========================
    bool valueCostRatioMin = false;

    sort(items.begin(), items.end(), Knapsack::sortValueCostRatio);
    cout<<"Highest Ratio First: "<<endl;
    //printItemVector(items);
    float c = Knapsack::calculateGreedySolution(items, knapsack, true, false, false);
    cout << "Solution: "<< c << endl << endl;
    knapsack.setValueCostRatioTotal(c);

    if(knapsack.getValueCostRatio() >= minimumVal)
    {
        minimumVal = knapsack.getValueCostRatio();
        minimumCost = knapsack.getValueCostRatioCost();
        valueCostRatioMin = true;
        minItems = knapsack.getValueCostRatioItems();

    }
    //===========================

    
    sort(items.begin(), items.end(), Knapsack::sortPartialTotal);
    cout<<"Partial Knapsack: "<<endl;
    cout << "Solution: "<< Knapsack::calculatePartialKnapsackSolution(items, knapsack) << endl << endl;
    //printItemVector(items);


    /*float minimums[3] = {knapsack.getHighestValue(), knapsack.getLowestCost(), knapsack.getValueCostRatio()};
    for (int i = 0; i < 3; i++)
    {
        if(minimums[i] >= minimum)
            minimum = minimums[i];
    } */

    //===========================EXHAUSTIVE
    //===========================


    sort(items.begin(), items.end(), Knapsack::sortByName);

    std::clock_t start;
    double duration;

    start = std::clock();

    double exTime = 0;
    cout << "Running Exhaustive Search..." << endl;
    Tree <vector <Item> > bst = createTree(items, knapsack);
    if (!bst.isFinished)
    {
        cout << "Exhaustive Search exceeds 10 minutes. Stopping." << endl;
        exTime = -1;
    }
    else
    {
        cout << "Exhaustive: " << endl;
        cout << "Solution: " << bst.bestValue <<endl;
        printItemVector(bst.bestSolution);

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::cout<<"Time: "<< duration <<'\n';
        exTime=duration;
        cout << endl;
    }
   
    start = std::clock();

    //===========================PRUNING
    //===========================

    double prTime=0;

    Tree <vector <Item> > bstPrune = createTreePrune(items, knapsack);
    if (!bstPrune.isFinished)
    {
        cout << "Pruning Search exceeds 10 minutes. Stopping." << endl;
        prTime = -1;
    }
    else
    {    
        cout << "Tree Pruning: " << endl;
        cout << "Solution: " << bstPrune.bestValue <<endl;
        printItemVector(bstPrune.bestSolution);

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::cout<<"Time: "<< duration <<'\n';
        prTime=duration;
    }


   //==================Output to file
    
    
    ofstream myfile;
    myfile.open ("solution.txt");
    myfile << filename << "\n";
    myfile << knapsack.getLimit() << endl;
    //best greedy min
    myfile << minimumVal << "," << minimumCost;
    sort(minItems.begin(), minItems.end(), Knapsack::sortByName);
    for(int i=0; i<minItems.size(); i++)
    {
        myfile << "," << minItems[i].getName();
    }
    myfile << endl;
    //best greedy max (partial)
    myfile << knapsack.getPartialTotal() << "," << knapsack.getLimit();
    vector<Item> partialItems = knapsack.getPartialItems();
    sort(partialItems.begin(), partialItems.end(), Knapsack::sortByName);
    for(int i=0; i<partialItems.size(); i++)
    {
        myfile << "," << partialItems[i].getName();
    }
    myfile << endl;
    
    //optimal solution (pruning)
    myfile << bstPrune.bestValue << "," << bstPrune.bestValueCost;
    for(int i=0; i<bstPrune.bestSolution.size(); i++)
    {
        myfile << "," << bstPrune.bestSolution[i].getName();
    }
    myfile << endl;

    myfile << exTime << endl;
    myfile << prTime << endl;

    myfile.close();


  



   //destroy(bst);
 /* HOW TO DO A TIMER 
    std::clock_t start;
    double duration;

    start = std::clock();

    //Your algorithm here
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"printf: "<< duration <<'\n';
 */
}
