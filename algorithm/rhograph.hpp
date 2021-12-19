template<int LOG = 64>
struct RhoGraph{
    int n;
    std::vector<std::vector<int>> table;
    std::function<int(int)> func;
    RhoGraph(int _n,const function<int(int)>& _func):n(_n),func(_func){ build(); }
    void build(){
        table = std::vector<std::vector<int>>(LOG,std::vector<int>(n));
        for(int i = 0;i < n;i++)table[0][i] = func(i);
        for(int i = 1;i < LOG;i++){
            for(int j = 0;j < n;j++){
                table[i][j] = table[i - 1][table[i - 1][j]];
            }
        }
    }
    int query(int x,long long k){
        for(int i = LOG - 1;i >= 0;i--){
            if(k >> i & 1)x = table[i][x];
        }
        return x;
    }
};
