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

float Knapsack::highestValueFunction(vector <Item> items)
{
    float currentCost=0;
    highestValueTotal=0;
    for(int i=0; currentCost<limit && i<items.size(); i++)
    {
        if((items[i].getCost()+currentCost) < limit)
        {
            currentCost = items[i].getCost()+currentCost;
            highestValueTotal = items[i].getCost()+highestValueTotal;
        }
    }
    
    return highestValueTotal;
}

float Knapsack::lowestCostFunction(vector <Item> items)
{
    float currentCost=0;
    lowestCostTotal=0;
    for(int i=0; currentCost<limit && i<items.size(); i++)
    {
        if((items[i].getCost()+currentCost) < limit)
        {
            currentCost = items[i].getCost()+currentCost;
            lowestCostTotal = items[i].getCost()+lowestCostTotal;
        }
    }
    
    return lowestCostTotal;
    
}

float Knapsack::valueCostRatioFunction(vector <Item> items)
{
    float currentCost=0;
    valueCostRatioTotal=0;
    for(int i=0; currentCost<limit && i<items.size(); i++)
    {
        if((items[i].getCost()+currentCost) < limit)
        {
            currentCost = items[i].getCost()+currentCost;
            valueCostRatioTotal = items[i].getCost()+valueCostRatioTotal;
        }
    }
    
    return valueCostRatioTotal;
    
}

float Knapsack::partialTotalFunction(vector <Item> items)//******** need to finish
{
    float currentCost=0;
    partialTotal=0;
    for(int i=0; currentCost<limit && i<items.size(); i++)
    {
        if((items[i].getCost()+currentCost) < limit)
        {
            currentCost = items[i].getCost()+currentCost;
            partialTotal = items[i].getCost()+partialTotal;
        }
    }
    return partialTotal;//not complete.... need to do the partial part!!!!!
    
}
