long long floordiv(long long a,long long b){
    assert(b != 0);
    if(b < 0)a = -a,b = -b;
    if(a >= 0)return a / b;
    else return (a - b + 1) / b;
}

long long ceildiv(long long a,long long b){
    assert(b != 0);
    if(b < 0)a = -a,b = -b;
    if(a >= 0)return (a + b - 1) / b;
    else return a / b;
}

long long floorsqrt(long long a){
    assert(a >= 0);
    long long l = -1,r = 1;
    while(r * r <= a)r <<= 1;
    while(r - l > 1){
        long long mid = (r + l) / 2;
        if(mid * mid > a)r = mid;
        else l = mid;
    }
    return l;
}
