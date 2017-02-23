//
//  Header.h
//  AI_Project1
//
//  Created by Alani Peters on 1/19/17.
//  Copyright © 2017 Alani Peters. All rights reserved.
//
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>


using namespace std;

class Item {

private:
    float value;
    float cost; //weight
    string name; //one letter char
    
public:
    float getValue() {return value;}
    float getCost() {return cost;}
    string getName() {return name;}
    void setValue(int a) {value = a;}
    void setCost (int a) {cost = a;}
    void setName (string a) {name = a;}
        
};
    
class Knapsack {
    
private:
    float limit;
    float currentValue;
    
    float highestValueTotal;
    float lowestCostTotal;
    float valueCostRatioTotal;
    float highestValueTotalCost;
    float lowestCostTotalCost;
    float valueCostRatioTotalCost;
    float partialTotal;
    
public:
    float getLimit() {return limit;}
    void setLimit(int a) {limit = a;}
    void setHighestValueTotal (float a) {highestValueTotal = a;}
    void setLowestCostTotal (float a) {lowestCostTotal = a;}
    void setValueCostRatioTotal (float a) {valueCostRatioTotal = a;}
    void setPartialTotal (float a) {partialTotal = a;}
    float getHighestValue() {return highestValueTotal;}
    float getLowestCost() {return lowestCostTotal;}
    float getValueCostRatio() {return valueCostRatioTotal;}
    float getHighestValueCost() {return highestValueTotalCost;}
    float getLowestCostCost() {return lowestCostTotalCost;}
    float getValueCostRatioCost() {return valueCostRatioTotalCost;}

    //http://www.cplusplus.com/reference/algorithm/sort/
    static bool sortHighestValue(Item i, Item j) { return (i.getValue() > j.getValue());}
    static bool sortLowestCost(Item i, Item j) { return (i.getCost() < j.getCost());}
    static bool sortValueCostRatio(Item i, Item j) { return (((float)(i.getValue() / i.getCost()) > (float)(j.getValue() / j.getCost())));}
    static bool sortPartialTotal(Item i, Item j) { return (((float)(i.getValue() / i.getCost()) > (float)(j.getValue() / j.getCost())));}
    static bool sortByName(Item i, Item j) {return ((int)i.getName()[0] < (int)j.getName()[0]);}

    static float calculateGreedySolution(vector<Item> v, Knapsack k){

        float sol = 0;
        float i = 0;
        float currentWeight = 0;

        for ( i = 0; i < v.size(); i++)
        {
            if ( currentWeight + v[i].getCost() <= k.getLimit()) //if we can take an item
            {
                sol += v[i].getValue();
                currentWeight += v[i].getCost();
            }
            else 
                break; //if there is ever a case where our knapsack will be too large, we break, taking greedy solution
        }   

        return sol;
    }

    static float calculatePartialKnapsackSolution(vector<Item> v, Knapsack k){

        float sol = 0; //solution
        float i = 0; //counter
        float currentWeight = 0;

        for ( i = 0; i < v.size(); i++)
        {
            if ( currentWeight + v[i].getCost() <= k.getLimit()) //if we can take an item
            {
                sol += v[i].getValue();
                currentWeight += v[i].getCost();
            }
            else
            {
                float difference = k.getLimit() - currentWeight;
                sol = sol + (v[i].getValue() * (v[i].getCost()/difference));
                //Get the partial of the next item, up to limit, then break
                break;
            }
        }   

        return sol;
    }
    
};
