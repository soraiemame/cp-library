/**
 * @brief garner precalc
 * @return long long 
 */
long long pregarner(std::vector<long long> &rems,std::vector<long long> &mods,long long MOD){
    assert(rems.size() == mods.size());
    for(int i = 0;i < int(rems.size());i++){
        for(int j = 0;j < i;j++){
            long long g = std::gcd(mods[i],mods[j]);
            if((rems[i] - rems[j]) % g != 0)return -1;
            mods[i] /= g;mods[j] /= g;
            long long gi = std::gcd(g,mods[i]),gj = g / gi;
            do{
                g = std::gcd(gi,gj);
                gi *= g;gj /= g;
            }while(g != 1);
            mods[i] *= gi;mods[j] *= gj;
            rems[i] %= mods[i];rems[j] %= mods[j];
        }
    }
    long long res = 1;
    for(long long &a : mods)res = res * a % MOD;
    return res;
}

/**
 * @brief returns a integer where rems[i](mod.mods[i]).
 * @return long long 
 */
long long garner(std::vector<long long> rems,std::vector<long long> mods,long long MOD){
    assert(rems.size() == mods.size());
    mods.push_back(MOD);
    int sz = mods.size();
    std::vector<long long> cof(sz,1LL),con(sz,0LL);
    for(int i = 0;i < sz - 1;i++){
        long long cur = (rems[i] - con[i]) * modinv(cof[i],mods[i]) % mods[i];
        if(cur < 0)cur += mods[i];
        for(int j = i + 1;j < sz;j++){
            con[j] = (con[j] + cur * cof[j]) % mods[j];
            cof[j] = cof[j] * mods[i] % mods[j];
        }
    }
    return con.back();
}
