//
//  Header.h
//  AI_Project1
//
//  Created by Alani Peters on 1/19/17.
//  Copyright © 2017 Alani Peters. All rights reserved.
//


class Item {
    
    private int value;
    private int cost; //weight
    private string name; //one letter char
    
    public int getValue() {return value;}
    public int getCost() {return cost;}
    public int getName() {return name;}
    public void setValue(int a) {value = a;}
    public void setCost (int a) {cost = a;}
    public void setName {string a) {name = a;}
    
};

class Knapsack {
    
    private int limit;
    private float currentValue;
    
    private int highestValueTotal;
    private int lowestCostTotal;
    private int valueCostRatioTotal;
    private int partialTotal;
    
    
    public int getLimit() {return limit};
    public void setLimit(int a) {limit = a;}
    public void setHighestValueTotal (int a) {highestValueTotal = a);
    public void setLowestCostTotal (int a) {lowestCostTotal = a);
    public void setValueCostRatioTotal (int a) {valueCostRatioTotal = a);
    public void setPartialTotal (int a) {partialTotal = a);
};
