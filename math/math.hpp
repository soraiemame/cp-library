long long extgcd(long long a,long long b,long long &x,long long &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    long long d = extgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}

long long modinv(long long a,long long p){
    long long b = p, u = 1, v = 0;
    while(b){
        long long t = a / b;
        a -= t * b;std::swap(a, b);
        u -= t * v;std::swap(u, v);
    }
    u %= p;
    if(u < 0)u += p;
    return u;
}
