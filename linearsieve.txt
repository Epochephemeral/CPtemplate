const int M = (int) 1e6 + 8;
bool vis[M];
vector<int> p;
void es(){
    for(int i = 2; i <= M - 5; i++){
       if(vis[i] == 0){
            p.push_back(i);
       }
       for(int j = 0; j < p.size(); j++){
            if(i * p[j] > M - 5){
                break;
            }
            vis[i * p[j]] = 1;
            if(i % p[j] == 0){
                 break;
            }
       }
    }
}