#include <iostream>
#include <algorithm>
using namespace std;

struct Job{
    int start,finish,profit;
};

bool jobComparator(Job s1 , Job s2){
    return (s1.finish<s2.finish);
}
 /*Finding the latest job (in sorted array) that doesn't
 conflict with the job[i]. If there is no compatible job,
 then it returns -1.*/
int latestNonConflict(Job arr[] , int i){
    for (int j=i-1; j>=0; j--)
    {
        if (arr[j].finish <= arr[i-1].start)
            return j;
    }
    return -1;
}
//sorting the inputs according to finish time
int findMaxProfit(Job arr[] , int n){
    sort(arr,arr+n,jobComparator);
    /*Creating an array to store solutions of subproblems.  table[i]
    stores the profit for jobs till arr[i] (including arr[i])*/
    int *table = new int[n];
    table[0] = arr[0].profit;
    //Filling the table values
    for(int i=1;i<n;i++){
        int inclprof = arr[i].profit;
        int l=latestNonConflict(arr,i);
        if(l!=-1) inclprof += table[l];
        table[i] = max(inclprof,table[i-1]);//storing the maximum of including the element and excluding the element . 
    }
    int result = table[n-1];
    delete[] table; 
    return result;
}

//Driver code (Taking the input and printing the output)
int main()
{
    int n;
	cout<<"Enter the Number of jobs : ";
	cin>>n;
	cout<<endl;
	Job arr[n];
	for(int i=0;i<n;i++){
	    cout<<"Enter the start time of "<<i+1<<" job : ";
	    cin>>arr[i].start;
	    cout<<endl;
	    cout<<"Enter the Finish time of "<<i+1<<" job : ";
	    cin>>arr[i].finish;
	    cout<<endl;
	    cout<<"Enter the Profit of "<<i+1<<" job : ";
	    cin>>arr[i].profit;
	    cout<<endl;
	}
	int max_profit=findMaxProfit(arr, n);
	cout<<"Maximum profit which can be obtained = "<<max_profit<<endl;
	return 0;
}

