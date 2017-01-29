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
