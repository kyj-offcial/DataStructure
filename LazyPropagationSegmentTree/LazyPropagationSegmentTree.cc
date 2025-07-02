#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class SegmentTree {
    private:
        long long init2(int node, int start, int end){
            if(start == end){
                tree[node] = v[start];
                return tree[node];
            }
            int mid = (start+end)/2;
            tree[node] = init2(node*2, start, mid)+init2(node*2+1, mid+1, end);
            return tree[node];
        }
        long long query2(int node, int start, int end, int left, int right){
            updateLazy(node, start, end);
            if(right < start || end < left) return 0;
            else if(left <= start && end <= right) return tree[node];
            int mid = (start+end)/2;
            return query2(node*2, start, mid, left, right) + query2(node*2+1, mid+1, end, left, right);
        }
        void updateRange2(int node, int start, int end, int left, int right, long long differ){
            updateLazy(node, start, end);
            if(right < start || end < left) return;
            else if(left <= start && end <= right){
                tree[node] += (end-start+1)*differ;
                if(start != end){
                    lazy[node*2] += differ;
                    lazy[node*2+1] += differ;
                }
                return;
            }
            int mid = (start+end)/2;
            updateRange2(node*2, start, mid, left, right, differ);
            updateRange2(node*2+1, mid+1, end, left, right, differ);
            tree[node] = tree[node*2]+tree[node*2+1];
        }
        void updateLazy(int node, int start, int end){
            if(lazy[node]){
                tree[node] += (end-start+1)*lazy[node];
                if(start != end){
                    lazy[node*2+1] += lazy[node];
                    lazy[node*2] += lazy[node];
                }
                lazy[node] = 0;
            }
        }
    public:
        vector<long long> v;
        vector<long long> tree;
        vector<long long> lazy;
        int size;
        void init(){
            size = v.size();
            tree.resize(4*size, 0);
            lazy.resize(4*size, 0);
            init2(1, 0, size-1);
        }
        void updateRange(int left, int right, long long differ){
            updateRange2(1, 0, size-1, left, right, differ);
        }
        long long query(int left, int right){
            return query2(1, 0, size-1, left, right);
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

    int N, M; fin >> N >> M;
    SegmentTree seg;
    for(int i=0; i<N; i++){
        long long num; fin >> num;
        seg.v.push_back(num);
    }
    seg.init();
    for(int i=0; i<M; i++){
        int num; fin >> num;
        if(num == 1){
            long long a, b, c; fin >> a >> b >> c;
            if(a > b){
                long long temp = a;
                a = b;
                b = temp;
            }
            seg.updateRange(a-1, b-1, c);
        }
        else{
            int a, b; fin >> a >> b;
            if(a > b){
                long long temp = a;
                a = b;
                b = temp;
            }
            cout << seg.query(a-1, b-1) << "\n";
        }
    }
}