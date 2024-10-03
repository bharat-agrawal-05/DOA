#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int minimum(vector<int>& nums){
    int ans = INT_MAX;

    for(int i = 0;i < nums.size(); i++){
        if(nums[i] < ans){
            ans = nums[i];
        }
    }
    return ans;
}

int maximum(vector<int>& nums){
    int ans = INT_MIN;

    for(int i = 0;i < nums.size();i++){
        if(nums[i] > ans){
            ans = nums[i];
        }
    }
    return ans;
}

int main()
{
    vector<int> arr = {1,2,3,3,100};
    cout<<maximum(arr)<<endl;
    cout<<minimum(arr)<<endl;
    
    return 0;
}