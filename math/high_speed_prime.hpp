std::vector<int> prime_factor_table;
void prime_factor_pre_calc(int n = 1e5){
    prime_factor_table.resize(n);
    prime_factor_table[1] = 1;
    for(int i = 2;i < n;i++){
        if(!prime_factor_table[i]){
            for(int j = i;j < n;j += i)prime_factor_table[j] = i;
        }
    }
}
std::map<int,int> high_speed_prime_factor(int n){
    std::map<int,int> res;
    while(n != 1){
        res[prime_factor_table[n]]++;
        n /= prime_factor_table[n];
    }
    return res;
}
