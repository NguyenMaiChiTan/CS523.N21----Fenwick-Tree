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

int* BIT_1;
int* BIT_2;

void Menu();
void updateBIT(int BITree[], int n, int index, int val);
int *constructBITree(int arr[], int n);
void update(int BITree[], int l, int r, int n, int val);
void printFenwick(int BITTree[], int n);
int getSum(int BITree[], int index);
void updateRange(int BITTree1[], int BITTree2[], int n, int val, int l, int r);
int rangeSum(int l, int r, int BITTree1[], int BITTree2[]);
int sum(int x, int BITTree1[], int BITTree2[]);
void constructAllZeros(int* a, int n);

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
    int n, temp_idx, temp_val, left_idx, right_idx;
    cin >> n;
    cout << "Input array's content: ";
    a = new int[n];
    for (int i = 0; i<n; ++i) cin >> a[i];
    BIT_1 = new int[n+1];
    BIT_2 = new int[n+1];
    BIT_1 = constructBITree(a, n);
    constructAllZeros(BIT_2, n);
    do{
        cout << "\nChoose an action: ";
        cin >> x; 
        switch (x) {
        case 0: 
            return;
        case 1: // point query
            cout << "\nPoint query: ";
            cout << "\nInput index: ";
            cin >> temp_idx; 
            cout << "\nSum from 0 to " << temp_idx << ": " << getSum(BIT_1, temp_idx);
            break;
        case 2: // point update
            cout << "\nPoint update: ";
            cout << "\nInput index: ";
            cin >> temp_idx;
            cout << "\nInput update value: ";
            cin >> temp_val;
            updateBIT(BIT_1, n, temp_idx, temp_val);
            cout << "\nFenwick tree after update: ";
            printFenwick(BIT_1, n);
            break;
        case 3: // range queries (only use this if you haven't performed range update)
            cout << "\nRange query: ";
            cout << "\nInput left and right index: ";
            cin >> left_idx >> right_idx;
            cout << "\nSum from " << left_idx << " to " << right_idx << ": " << (getSum(BIT_1, right_idx) - getSum(BIT_1, left_idx));
            break;
        case 4: // range update - point query 
            cout << "\nRange update and point query: ";
            cout << "\nInput left and right index: ";
            cin >> left_idx >> right_idx;
            cout << "Input update value: ";
            cin >> temp_val;
            cout << "Input query index: ";
            cin >> temp_idx;
            update(BIT_1, left_idx, right_idx, n, temp_val);
            cout << "Sum from 0 to " << right_idx << " after update: " << getSum(BIT_1, temp_idx);
            break;
        case 5: //range update - range query 
            cout << "Range update and range query: ";
            cout << "\nInput left and right update index: ";
            cin >> left_idx >> right_idx;
            cout << "Input update value: ";
            cin >> temp_val;
            updateRange(BIT_1, BIT_2, n, temp_val, left_idx, right_idx);
            cout << "Input left and right query index: ";
            cin >> left_idx >> right_idx;
            cout << "\nSum from " << left_idx << " to " << right_idx  << ": " << rangeSum(left_idx, right_idx, BIT_1, BIT_2);
            break; 
        case 6: //print array fenwick
            cout << "\nChoose which fenwick array to print (1 - 2): ";
            cin >> temp_val;
            if(temp_val==2) printFenwick(BIT_2, n);
            else printFenwick(BIT_1, n);
            break;
        case 7: // range query (use this after you performed fenwick tree)
            cout << "\nRange query";
            cout << "\nInput left and right index: ";
            cin >> left_idx >> right_idx;
            cout << "\nSum from " << left_idx << " to " << right_idx  << ": " << rangeSum(left_idx, right_idx, BIT_1, BIT_2);
            break;
        case 8: // Reset fenwick tree to all 0
            constructAllZeros(BIT_1, n);
            constructAllZeros(BIT_2, n);
            cout << "\nReset done!";
            break;
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

void constructAllZeros(int* a, int n){
    for(int i = 1; i <= n; ++i) a[i] = 0;
}
