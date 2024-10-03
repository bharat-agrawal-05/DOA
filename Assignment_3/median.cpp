#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

void insertionSort(vector<int>& arr){
    for(int i = 1;i < arr.size();i++){
        int key = arr[i];
        int j = i-1;
        while(key < arr[j] && j>= 0){
            j--;
            arr[j+1] = arr[j];
        }
        arr[j+1] = key;
    }
}
void printArr(vector<int>& nums){
    for(auto i :nums){
        cout<<i<<' ';
    }
    cout<<endl;
}
int partition(vector<int>& nums,int value, int start, int end){
    int idx;
    for(int i = start;i <= end; i++){
        if(nums[i] == value){
            idx = i;break;
        }
    }
    swap(nums[idx],nums[end]);
    int j=start,i=start-1;
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



int median(vector<int>& nums, int start, int end){
    vector<vector<int>> groups;
    for(int i = start; i <= end;i+=5){
        vector<int> group;
        for(int j = i; j < i+5 && j <= end; j++){
            group.push_back(nums[j]);
        }
        groups.push_back(group);
    }
    vector<int> medians;
    for(auto& group: groups){
        insertionSort(group);
        medians.push_back(group[(group.size()-1)/2]);
    }

    if(medians.size() <= 5){
        insertionSort(medians);
        return medians[(medians.size()-1)/2];
    }
    return median(medians,0,medians.size()-1);

}

int medianOfMedians(vector<int> nums,int k){
    int start = 0;
    int end = nums.size() - 1;

    while(start <= end){
        int pivot = median(nums,start,end);
        int i = partition(nums,pivot,start,end);
        if(i == k){
            return nums[i];
        }
        else if(i > k){
            end = i - 1;
        }
        else start = i + 1;
    }
    return -1;
}


int main()
{
    vector<int> arr = {5,4,3,7,8,10,13,11,15,2,2,2,2,2,1};
    int k = arr.size()/2;
    cout<<medianOfMedians(arr,k)<<endl;


    return 0;
}