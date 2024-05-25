#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    
    public: 
    vector<int> input;
    vector<int> segmentTree;
    
    SegmentTree(vector<int> input) {
        this->input.insert(this->input.begin(),input.begin(),input.end());
        segmentTree.resize(2 * input.size() + 1, 0);
        build(0,0,input.size()-1);
    } 
    
    
    void build(int index,int low,int high) {
        
        if (low == high) {
            segmentTree[index] =  input[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * index+1,low,mid);
        build(2 * index+2,mid+1,high);
    
        segmentTree[index] = std::min(segmentTree[2*index+1],segmentTree[2*index+2]);
    }
    
    
    int solveQuery(int index,int low,int high,int left,int right) {
        
        // low...high...left || right..low..high
        if (right < low || left > high) {
            return INT_MAX;
        }
        
        //left...low....high...right
        
        if (left <= low && high <= right) {
            return segmentTree[index];
        }
        
        int mid = (low + high) / 2;
        
        int leftMin = solveQuery(2 * index + 1,low,mid,left,right);
        int rightMin = solveQuery(2 * index + 2,mid+1,high,left,right);
        
        return std::min(leftMin,rightMin);
    }
    
    void updateQuery(int index,int low,int high,int updateIndex,int val) {
        
        if (low == high) {
            segmentTree[index] = val;
            return;
        }
        
        int mid = (low + high) / 2;
        if (updateIndex <= mid) {
            updateQuery(2 * index + 1,low,mid,updateIndex,val);
        } else {
            updateQuery(2 * index + 2,mid+1,high,updateIndex,val);
        }
        segmentTree[index] = std::min(segmentTree[2*index+1],segmentTree[2*index+2]);
    }
    
    void update(int index,int val) {
        input[index] = val;
        updateQuery(0,0,arr.size(),index,val);
    }
};
