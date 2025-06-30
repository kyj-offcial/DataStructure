#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class segmentTree {
    private:
        int init(vector<int> v, int node, int start, int end){
            if(start == end){
                tree[node] = v[start];
                return tree[node];
            }
            int mid = (start+end)/2;
            tree[node] = init(v, node*2, start, mid) + init(v, node*2+1, mid+1, end);
            return tree[node];
        }
        int queryBase(int node, int start, int end, int left, int right){
            if(right < start || left > end) return 0;
            else if(left <= start && end <= right) return tree[node];
            int mid = (start+end)/2;
            return queryBase(node*2, start, mid, left, right) + queryBase(node*2+1, mid+1, end, left, right);
        }
        void updateBase(int node, int start, int end, int index, int differ){
            if(index < start || index > end) return;
            tree[node] += differ;
            if(start != end){
                int mid = (start+end)/2;
                updateBase(node*2, start, mid, index, differ);
                updateBase(node*2+1, mid+1, end, index, differ);
            }
        }
        void printTree(bool tnf=false){
            int floor=1, count=0;
            cout << "----SegmentTree----\n";
            for(int i=1; i<tree.size(); i++){
                if(!count) cout << "| ";
                if(tnf && !tree[i]) break;
                cout << tree[i] << " ";
                count++;
                if(count == floor){
                    cout << "\n";
                    floor*=2;
                    count=0;
                }
            }
            cout << "\n----------------\n\n";
        }
    public:
        vector<int> tree;
        int size;
        segmentTree(){}
        segmentTree(vector<int> v){
            size = v.size();
            tree.resize(4*size);
            init(v, 1, 0, size-1);
            cout << "init";
            printTree(1);
        }
        void query(int left, int right){
            cout << "*" << left << "~" << right << "* SUM : " << queryBase(1, 0, size-1, left, right) << "\n\n";
        }
        void update(vector<int>& v, int index, int newValue){
            int differ = newValue - v[index];
            v[index] = newValue;
            updateBase(1, 0, size-1, index, differ);
            cout << "update";
            printTree(1);
        }
};

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
    char key;
    vector<int> arr;
    segmentTree* seg;
    while(fin >> key){
        switch(key){
            case 'I':
                int n;
                fin >> n;
                for(int i=0; i<n ;i++){
                    int num; fin >> num;
                    arr.push_back(num);
                }
                seg = new segmentTree(arr);
                break;
            case 'Q':
                int left, right;
                fin >> left >> right;
                seg->query(left, right);
                break;
            case 'U':
                int index, newValue;
                fin >> index >> newValue;
                seg->update(arr, index, newValue);
                break;
            default:
                cout << "Input Alphabet Error\n";
                break;
        }
    }
}
