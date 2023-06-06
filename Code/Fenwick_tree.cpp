/* 
This code is based on the code from:
https://ideone.com/mGlJs2
https://stackoverflow.com/questions/31068521/is-it-possible-to-build-a-fenwick-tree-in-on
https://www.geeksforgeeks.org/binary-indexed-tree-range-update-range-queries/
https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
https://www.geeksforgeeks.org/binary-indexed-tree-range-updates-point-queries/
*/

#include <iostream>
using namespace std;
#define arr_len(arr) (sizeof(arr)/sizeof(*(arr)))

void Menu();
void updateBIT(int BITree[], int n, int index, int val);
int *constructBITree(int arr[], int n);
void update(int BITree[], int l, int r, int n, int val);
void printFenwick(int BITTree[], int n);
int getSum(int BITree[], int index);
void updateRange(int BITTree1[], int BITTree2[], int n, int val, int l, int r);
int rangeSum(int l, int r, int BITTree1[], int BITTree2[]);
int sum(int x, int BITTree1[], int BITTree2[]);

//-----------------------------------------------------------------------------------------//

int main() {
    Menu();
    return 0;
}

//-----------------------------------------------------------------------------------------//

void Menu(){
    cout << "input size of array: ";
    int x = 1;
    int *a;
    int n;
    cin >> n;
    cout << "Input array's content: ";
    a = new int[n];
    for (int i = 0; i<n; ++i) cin >> a[i];
    int* fenwick;
    fenwick = constructBITree(a, n);
    do{
        cout << "\nChoose an action: ";
        cin >> x; 
        switch (x) {
        case 0: 
            return;
        case 1: // point query
            cout << "\nPoint query: ";
            int temp; 
            cout << "\nInput index: ";
            cin >> temp; 
            cout << "\nSum from 0 to " << temp << ": " << getSum(fenwick, temp);
            break;
        case 2: // point update
            cout << "\nPoint update: ";
            int temp_idx, temp_val;
            cout << "\nInput index: ";
            cin >> temp_idx;
            cout << "\nInput update value: ";
            cin >> temp_val;
            updateBIT(fenwick, n, temp_idx, temp_val);
            cout << "\nFenwick tree after update: ";
            printFenwick(fenwick, n);
            break;
        case 3: // range queries
            cout << "\nRange query: ";
            int temp_1, temp_2;
            cout << "\nInput left and right index: ";
            cin >> temp_1 >> temp_2;
            if (temp_1 > temp_2) { 
                int haha = temp_2; 
                temp_2 = temp_1; 
                temp_1 = haha;
            }
            cout << "\nSum from " << temp_1 << "to " << temp_2 << ": " << (getSum(fenwick, temp_2) - getSum(fenwick, temp_1));
            break;
        case 4: // range update - point query (this action will not perform actual range update on Fenwick tree, just a quick query)
            cout << "\nRange update and point query: ";
            int* fenwick_temp;
            fenwick_temp = new int[n+1];
            for(int i = 0; i <= n; ++i) fenwick_temp[i] = 0;
            int left_idx, right_idx, value, query_idx;
            cout << "\nInput left and right index: ";
            cin >> left_idx >> right_idx;
            cout << "Input update value: ";
            cin >> value;
            cout << "Input query index: ";
            cin >> query_idx;
            update(fenwick_temp, left_idx, right_idx, n, value);
            cout << "Sum from 0 to " << query_idx << " after update: " << getSum(fenwick_temp, query_idx) + a[query_idx];
            break;
        case 5: //range update - range query 
            cout << "Range update and range query: ";
            int* BIT_1;
            int* BIT_2;
            BIT_1 = new int[n+1]; 
            BIT_2 = new int[n+1];
            for(int i = 0; i <= n; ++i) BIT_1[i] = BIT_2[i] = 0;
            int leftUpIdx, rightUpIdx, value, leftQueIdx, rightQueIdx;
            cout << "\nInput left and right update index: ";
            cin >> leftUpIdx >> rightUpIdx;
            cout << "Input update value: ";
            cin >> value;
            cout << "Input left and right query index: ";
            cin >> leftQueIdx >> rightQueIdx;
            updateRange(BIT_1, BIT_2, n, value, leftUpIdx, rightUpIdx);
            cout << "\nSum from " << leftQueIdx << " to " << rightQueIdx  << ": " << rangeSum(leftQueIdx, rightQueIdx, BIT_1, BIT_2); 
        default:
            cout << "\nUnrecognizable query type! \nPlease try again.\n";
        }
    }while(x!=0);
}

void updateBIT(int BITree[], int n, int index, int val)
{
    index = index + 1;
    while (index <= n)
    {
    BITree[index] += val;
    index += index & (-index);
    }
}
  
int *constructBITree(int arr[], int n)
{
    int *BITree = new int[n+1];
    for (int i=1; i<=n; i++)
        BITree[i] = 0;
    for (int i=0; i<n; i++)
        updateBIT(BITree, n, i, arr[i]);
    return BITree;
}

void update(int BITree[], int l, int r, int n, int val)
{
    updateBIT(BITree, n, l, val);
    updateBIT(BITree, n, r+1, -val);
}

void printFenwick(int BITTree[], int n)
{
    for(int i = 1; i <= n; ++i) cout << BITTree[i] << '\t';
}

int getSum(int BITree[], int index)
{
    int sum = 0; 
    index = index + 1;
    while (index>0)
    {
        sum += BITree[index];
        index -= index & (-index);
    }
    return sum;
}
void updateRange(int BITTree1[], int BITTree2[], int n, int val, int l, int r)
{
    updateBIT(BITTree1, n, l, val);
    updateBIT(BITTree1, n, r + 1, -val);
    updateBIT(BITTree2, n, l, val * (l - 1));
    updateBIT(BITTree2, n, r + 1, -val * r);
}
 
int rangeSum(int l, int r, int BITTree1[], int BITTree2[])
{
    return sum(r, BITTree1, BITTree2) - sum(l - 1, BITTree1, BITTree2);
}

int sum(int x, int BITTree1[], int BITTree2[])
{
    return (getSum(BITTree1, x) * x) - getSum(BITTree2, x);
}