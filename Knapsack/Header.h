//
//  Header.h
//  AI_Project1
//
//  Created by Alani Peters on 1/19/17.
//  Copyright © 2017 Alani Peters. All rights reserved.
//


class Item {

private:
    int value;
    int cost; //weight
    string name; //one letter char
    
public:
    int getValue() {return value;}
    int getCost() {return cost;}
    string getName() {return name;}
    void setValue(int a) {value = a;}
    void setCost (int a) {cost = a;}
    void setName (string a) {name = a;}
        
};
    
class Knapsack {
    
private:
    int limit;
    float currentValue;
    
    int highestValueTotal;
    int lowestCostTotal;
    int valueCostRatioTotal;
    int partialTotal;
    
public:
    int getLimit() {return limit;}
    void setLimit(int a) {limit = a;}
    void setHighestValueTotal (int a) {highestValueTotal = a;}
    void setLowestCostTotal (int a) {lowestCostTotal = a;}
    void setValueCostRatioTotal (int a) {valueCostRatioTotal = a;}
    void setPartialTotal (int a) {partialTotal = a;}

    //http://www.cplusplus.com/reference/algorithm/sort/
    bool sortHighestValue(Item i, Item j) { return (i.getValue() > j.getValue());}
    bool sortLowestCost(Item i, Item j) { return (i.getCost() < j.getCost());}
    bool sortValueCostRatio(Item i, Item j) { return (((float)(i.getValue() / i.getCost()) > (float)(j.getValue() / j.getCost())));}
    bool sortPartialTotal(Item i, Item j) { return (((float)(i.getValue() / i.getCost()) > (float)(j.getValue() / j.getCost())));}
    
};
