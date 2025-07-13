#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int arr[100001][11]={}; // 1칸 부모, 2칸 부모, 4칸 부모, 8칸 부모 ... 1024칸 부모 ( 2^index칸 부모 )
int height[100001]={};
vector<vector<int>> v(100001);

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

    int N; fin >> N;
    for(int i=1; i<N; i++){
        int a, b; fin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
    for(int i=0; i<10; i++){
        arr[1][i] = 1;
        height[1] = 0;
    }

    queue<int> q;
    for(int i=0; i<v[1].size(); i++){
        q.push(v[1][i]);
        arr[v[1][i]][0] = 1;
        height[v[1][i]] = height[1]+1;
    }
    while(!q.empty()){
        int node = q.front();
        q.pop();
            
        for(int i=0; i<v[node].size(); i++){
            int num = v[node][i];
            if(!arr[num][0]){
                q.push(num);
                arr[num][0] = node;
                height[num] = height[node]+1;
            }
        }
    }
    for(int i=1; i<11; i++){
        for(int j=1; j<=N; j++) arr[j][i] = arr[arr[j][i-1]][i-1];
    }

    int M; fin >> M;
    for(int i=0; i<M; i++){
        int a, b; fin >> a >> b;
        if(height[a] > height[b]){
            int differ = height[a]-height[b];
            while(differ > 0){
                for(int div = 1024, i = 10; div >= 1; div /= 2, i--){
                    if(differ >= div){
                        differ -= div;
                        a = arr[a][i];
                        break;
                    }
                }
            }
        }
        else if(height[a] < height[b]){
            int differ = height[b]-height[a];
            while(differ > 0){
                for(int div = 1024, i = 10; div >= 1; div /= 2, i--){
                    if(differ >= div){
                        differ -= div;
                        b = arr[b][i];
                        break;
                    }
                }
            }
        }

        while(a != b){
            for(int i = 10; i >= 0; i--){
                if(arr[a][i] != arr[b][i]){
                    a = arr[a][i];
                    b = arr[b][i];
                    break;
                }
                else{
                    if(i == 0){
                        a = arr[a][0];
                        b = arr[b][0];
                        break;
                    }
                }
            }
        }
        cout << a << "\n";
    }
}