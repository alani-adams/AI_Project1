//
//  Project1.cpp
//  
//
//  Created by Alani Peters on 1/30/17.
//
//

#include <stdio.h>
#include <vector>
#include <algorithm>
#include "Header.h"

float Knapsack::highestValueFunction(vector <Item> items, Knapsack knapsack)
{
    float currentCost=0;
    float currentValue=0;
    for(int i=0; currentCost<knapsack.getLimit() && i<items.size(); i++)
    {
        if((items[i].getCost()+currentCost) < knapsack.getLimit())
        {
            currentCost = items[i].getCost()+currentCost;
            currentValue = items[i].getCost()+currentValue;
        }
    }
    return currentValue;
}

float Knapsack::lowestCostFunction(vector <Item> items, Knapsack knapsack)
{
    float currentCost=0;
    float currentValue=0;
    for(int i=0; currentCost<knapsack.getLimit() && i<items.size(); i++)
    {
        if((items[i].getCost()+currentCost) < knapsack.getLimit())
        {
            currentCost = items[i].getCost()+currentCost;
            currentValue = items[i].getCost()+currentValue;
        }
    }
    return currentValue;
    
}

float Knapsack::valueCostRatioFunction(vector <Item> items)
{
    float currentCost=0;
    float currentValue=0;
    for(int i=0; currentCost<knapsack.getLimit() && i<items.size(); i++)
    {
        if((items[i].getCost()+currentCost) < knapsack.getLimit())
        {
            currentCost = items[i].getCost()+currentCost;
            currentValue = items[i].getCost()+currentValue;
        }
    }
    return currentValue;
    
}

float Knapsack::partialTotalFunction(vector <Item> items)//******** need to finish
{
    float currentCost=0;
    float currentValue=0;
    for(int i=0; currentCost<knapsack.getLimit() && i<items.size(); i++)
    {
        if((items[i].getCost()+currentCost) < knapsack.getLimit())
        {
            currentCost = items[i].getCost()+currentCost;
            currentValue = items[i].getCost()+currentValue;
        }
    }//not complete.... need to do the partial part!!!!!
    return currentValue;
    
}
