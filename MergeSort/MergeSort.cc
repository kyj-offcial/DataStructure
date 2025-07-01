#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void MergeSort(vector<int>& v, int left, int right, int mid){
    int i = left;
    int j = mid+1;
    vector<int> sortV;
    while(i <= mid && j <= right){
        if(v[i] < v[j]) sortV.push_back(v[i++]);
        else sortV.push_back(v[j++]);
    }

    if(i > mid) for(int temp = j; temp <= right; temp++) sortV.push_back(v[temp]);
    else for(int temp = i; temp <= mid; temp++) sortV.push_back(v[temp]);
    for(int temp = left; temp <= right; temp++)  v[temp] = sortV[temp-left];
}

void Merge(vector<int>& v, int left, int right){
    int mid = (left+right)/2;

    if(left < right){
        Merge(v, left, mid);
        Merge(v, mid+1, right);
        MergeSort(v, left, right, mid);
    }
}

int main(int argc, char* argv[]){
    if(argc < 2){
        cout << "입력 파일이 없습니다.\n";
        return 1;
    }
    ifstream fin(argv[1]);
    if(!fin.is_open()){
        cout << "파일을 다시 선택해주십시오.\n";
        return 1;
    }
    int num;
    vector<int> v;
    while(fin >> num) v.push_back(num);

    Merge(v, 0, v.size()-1);

    cout << "____Sorting Result____\n";
    for(int i=0; i<v.size(); i++) cout << v[i] << " ";
    cout << "\n";
}