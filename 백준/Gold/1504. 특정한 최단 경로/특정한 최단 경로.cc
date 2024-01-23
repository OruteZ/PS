#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
using namespace std;

int INF = 799001;

//[출발점][목적지] [거리]
vector<pair<int,int>> table[801];
//vector<int> visit[801];
int dis[801];


void line(){
    cout << "------------------------------------------" << endl;
}
void Dijkstra(int start_num){
    //container생성 <해당 점까지의 최소 거리, 해당 점>
    priority_queue<pair<int, int>> container;

    //1. 시작점에 인접한 노드들의 최소 거리 초기화
    //2. 해당 노드들의 참여 경로에 시작 노드 추가
    //3. container에 인접노드 push
    for(int i = 0; i < table[start_num].size(); i++){
        dis[table[start_num][i].second] = table[start_num][i].first;
        //visit[table[start_num][i].second].push_back(start_num);
        container.push({-dis[table[start_num][i].second], table[start_num][i].second});
    }

    while(!container.empty()){

        /*
        for(int i = 1; i <= 4; i++){
            if(dis[i] == INF) cout << "INF" << " ";
            else cout << dis[i] << " ";
        } cout<< endl;*/


        //값 꺼내오기
        int cur_node = container.top().second;
        int cur_length = -container.top().first;
        container.pop();

        ////cout << "node : " << cur_node << " length : " << cur_length << endl;


        if(cur_length >  dis[cur_node]) continue;

        ////cout << cur_node << "'s side node" << endl;

        //for문으로 curNode의 인접노드 값들 가져오기
        for(int i = 0 ; i < table[cur_node].size(); i ++){
            ////cout << cur_node << "'s side node " << table[cur_node][i].second << " call" << endl;

            int next_node = table[cur_node][i].second;
            int next_dis = table[cur_node][i].first;
            //새로운 경로가 기존보다 더 짧은 거리를 가진다면
            if(dis[next_node] > cur_length + next_dis){
                ////cout << cur_node << " to " << table[cur_node][i].second << " is new dis" << endl;
                //1.dis값 초기화하기
                dis[next_node] = cur_length + next_dis;
                /*
                //2. 경로값 초기화하기
                //2-1 대상 경로 초기화
                visit[table[cur_node][i].second].clear();
                //2-2 이전 경로  추가
                for(int j = 0; j < visit[cur_node].size(); j++){
                    visit[table[cur_node][i].second].emplace_back(visit[cur_node][j]);
                }
                //2-3 cur_node push
                visit[table[cur_node][i].second].emplace_back(cur_node);
                */
                //3. 인접값 container에 추가하기
                container.push({-dis[next_node], next_node});
            }
        }



    }

    /*
    for(int i = 1; i <= 4; i++){
        if(dis[i] == INF) cout << "INF" << " ";
        else cout << dis[i] << " ";
    } cout<< endl;*/

}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);



    //입력받기
    bool isConnected = true;
    int N, E;cin >> N >> E;
    int a,b,c;
    while(E--){
        cin >> a >> b >> c;
        table[a].emplace_back(c,b);
        table[b].emplace_back(c,a);
    }
    int v1, v2; cin >> v1 >> v2;

    //파악해야될 데이터
    //1. 1에서 v1까지 최소거리
    //2. 1에서 v2까지 최소거리
    //3. v1에서 v2까지 최소거리
    //1번 2번값들중 작은 값 + 3번값

    //테이블 초기화
    for(int i = 1; i <= N; i++){
        dis[i] = INF;
        //visit[i].clear();
    } dis[1] = 0;
    Dijkstra(1);

    int one_to_v1 = dis[v1];
    int one_to_v2 = dis[v2];
    if(one_to_v2 == INF || one_to_v1 == INF) isConnected = false;


    ////line();

    //테이블 초기화
    for(int i = 1; i <= N; i++){
        dis[i] = INF;
        //visit[i].clear();
    } dis[v1] = 0;
    Dijkstra(v1);

    int v1_to_v2 = dis[v2];

    if(v1_to_v2 == INF) isConnected = false;


    ////line();

    //테이블 초기화
    for(int i = 1; i <= N; i++){
        dis[i] = INF;
        //visit[i].clear();
    } dis[N] = 0;
    Dijkstra(N);

    int v2_to_N = dis[v2];
    int v1_to_N = dis[v1];

    if(v1_to_N == INF || v2_to_N == INF) isConnected = false;


    if(isConnected){
        long answer1 = one_to_v2 + v1_to_v2 + v1_to_N;
        long answer2 = one_to_v1 + v1_to_v2 + v2_to_N;

        ////line();

        if(answer1 < answer2) cout << answer1 << endl;
        else  cout << answer2 << endl;
    } else {
        cout << -1 << endl;
    }



    /*
       cout << one_to_v1 << endl;
       cout << one_to_v2 << endl;
       cout << v1_to_v2 << endl;
       cout << v1_to_N << endl;
       cout << v2_N << endl;

    /*



       for(int i = 1; i < N+1; i++){
           if(dis[i] == INF) cout << "INF" << endl;
           else cout << dis[i] << endl;
       }*/
    return 0;
}