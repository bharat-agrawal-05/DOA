#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printArr(vector<int>& arr){
    for(auto& i :arr){
        cout<<i<<' ';
    }
    cout<<endl;
}

int partition(vector<int>& nums,int idx, int start, int end){
    int j=start,i=start-1;
    swap(nums[idx],nums[end]);
    while(j <= end){
        if(nums[j] < nums[end]){
            ++i;
            swap(nums[j],nums[i]);
        }
        j++;
    }
    swap(nums[end],nums[i+1]);

    return i+1;
    
}

// to find the kth smallest element in the array
int quickSelect(int k,vector<int>& nums){
    k-=1;
    int start = 0;
    int end = nums.size()-1;
    int i = 0;
    while(start <= end){
        int idx = (rand() % (end-start+1)) + start;
        i = partition(nums,idx,start,end);
        if(i == k){
            return nums[i];
        }
        else if(i > k){
            end = i-1;
        }
        else{
            start = i+1;
        }
    }
    return -1;
}

int main()
{
    vector<int> nums = {10, 100, 232, 345, 23, 654, 23, 34, 23, 9};
    int k = 1;
    int ans = quickSelect(k,nums);
    cout<<ans<<endl;

    //for checking
    sort(nums.begin(),nums.end());
    printArr(nums);

    return 0;
}