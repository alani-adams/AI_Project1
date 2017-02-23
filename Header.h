//
//  Header.h
//  AI_Project1
//
//  Created by Alani Peters and Cole Spears on 1/19/17.
//  Copyright © 2017 Peters and Spears. All rights reserved.
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
    float partialTotalCost;

    vector<Item> highestValueItems;
    vector<Item> lowestCostItems;
    vector<Item> valueCostRatioItems;
    vector<Item> partialItems;

    
public:
    float getLimit() {return limit;}
    void setLimit(int a) {limit = a;}
    //set Value
    void setHighestValueTotal (float a) {highestValueTotal = a;}
    void setLowestCostTotal (float a) {lowestCostTotal = a;}
    void setValueCostRatioTotal (float a) {valueCostRatioTotal = a;}
    void setPartialTotal (float a) {partialTotal = a;}
    //set Cost
    void setHighestValueCost(float a) { highestValueTotalCost = a;}
    void setLowestCostCost(float a) { lowestCostTotalCost = a;}
    void setValueCostRatioCost(float a) { valueCostRatioTotalCost = a;}
    void setPartialCost (float a) {partialTotal = a;}


    //set Items
    void setValueCostRatioItems(vector<Item> a) { valueCostRatioItems = a;}
    void setHighestValueItems(vector<Item> a) { highestValueItems = a;}
    void setLowestCostItems(vector<Item> a) { lowestCostItems = a;}
    void setPartialItems(vector<Item> a) { partialItems = a;}



    float getHighestValue() {return highestValueTotal;}
    float getLowestCost() {return lowestCostTotal;}
    float getValueCostRatio() {return valueCostRatioTotal;}
    float getPartialTotal() {return partialTotal;}

    //get Cost
    float getHighestValueCost() {return highestValueTotalCost;}
    float getLowestCostCost() {return lowestCostTotalCost;}
    float getValueCostRatioCost() {return valueCostRatioTotalCost;}
    float getPartialCost() {return partialTotalCost;}

    //get Items
    vector<Item> getValueCostRatioItems() { return valueCostRatioItems;}
    vector<Item> getHighestValueItems() { return highestValueItems;}
    vector<Item> getLowestCostItems() { return lowestCostItems;}
    vector<Item> getPartialItems() { return partialItems;}


    //http://www.cplusplus.com/reference/algorithm/sort/
    static bool sortHighestValue(Item i, Item j) { return (i.getValue() > j.getValue());}
    static bool sortLowestCost(Item i, Item j) { return (i.getCost() < j.getCost());}
    static bool sortValueCostRatio(Item i, Item j) { return (((float)(i.getValue() / i.getCost()) > (float)(j.getValue() / j.getCost())));}
    static bool sortPartialTotal(Item i, Item j) { return (((float)(i.getValue() / i.getCost()) > (float)(j.getValue() / j.getCost())));}
    static bool sortByName(Item i, Item j) {return ((int)i.getName()[0] < (int)j.getName()[0]);}

    static float calculateGreedySolution(vector<Item> v, Knapsack &k, bool vCRatio, bool highestV, bool lowestC){

        float sol = 0;
        float i = 0;
        float currentWeight = 0;
        std::vector<Item> takenItems;

        for ( i = 0; i < v.size(); i++)
        {
            if ( currentWeight + v[i].getCost() <= k.getLimit()) //if we can take an item
            {
                sol += v[i].getValue();
                currentWeight += v[i].getCost();
                takenItems.push_back(v[i]);

            }
            else 
            {   
                if(vCRatio)
                {
                    k.setValueCostRatioItems(takenItems);
                    k.setValueCostRatioCost(currentWeight);
                }
                else if(highestV)
                {
                    k.setHighestValueItems(takenItems);
                    k.setHighestValueCost(currentWeight);
                }
                else if(lowestC)
                {
                    k.setLowestCostItems(takenItems);
                    k.setLowestCostCost(currentWeight);
                }
                break; //if there is ever a case where our knapsack will be too large, we break, taking greedy solution
            }
        }   
                if(vCRatio)
                {
                    k.setValueCostRatioItems(takenItems);
                    k.setValueCostRatioCost(currentWeight);
                }
                else if(highestV)
                {
                    k.setHighestValueItems(takenItems);
                    k.setHighestValueCost(currentWeight);
                }
                else if(lowestC)
                {
                    k.setLowestCostItems(takenItems);
                    k.setLowestCostCost(currentWeight);
                }
        return sol;
    }

    static float calculatePartialKnapsackSolution(vector<Item> v, Knapsack &k){

        float sol = 0; //solution
        float i = 0; //counter
        float currentWeight = 0;
        std::vector<Item> takenItems;

        for ( i = 0; i < v.size(); i++)
        {
            if ( currentWeight + v[i].getCost() <= k.getLimit()) //if we can take an item
            {
                sol += v[i].getValue();
                currentWeight += v[i].getCost();
                takenItems.push_back(v[i]);

            }
            else
            {
                float difference = k.getLimit() - currentWeight;
                sol = sol + (v[i].getValue() * (v[i].getCost()/difference));
                //Get the partial of the next item, up to limit, then break
                takenItems.push_back(v[i]);
                k.setPartialItems(takenItems);
                k.setPartialCost(k.getLimit());
                k.setPartialTotal(sol);
                break;
            }
        }   

        return sol;
    }
    
};
