struct binomial_pre {
    binomial_pre(int p, int q, int m) : p(p), q(q), m(m), fac(m), ifac(m) {
        fac[0] = 1;
        for (int i = 1;i < m;i++) {
            fac[i] = fac[i - 1];
            if (i % p != 0)fac[i] = mod_m((long long)(fac[i]) * i);
        }
        ifac[m - 1] = atcoder::inv_mod(fac[m - 1], m);
        for (int i = m - 2;i > 1;i--) {
            if (i % p == 0) {
                ifac[i] = mod_m(1LL * ifac[i + 1] * (i + 1));
                ifac[i - 1] = ifac[i];
                i--;
            }
            else {
                ifac[i] = mod_m(1LL * ifac[i + 1] * (i + 1));
            }
        }
        ifac[0] = ifac[1] = 1;
    }

    int Lucas(long long n, long long k) const {
        int res = 1;
        while (n) {
            if (n % p < k % p)return 0;
            res = mod_m(1LL * res * fac[n % p]);
            res = mod_m(1LL * res * ifac[k % p]);
            res = mod_m(1LL * res * ifac[n % p - k % p]);
            n /= p;
            k /= p;
        }
        return res;
    }

    int C(long long n, long long k) const {
        if (k > n || n < 0 || k < 0)return 0;
        if (q == 1)return Lucas(n, k);
        long long r = n - k;
        int res = 1;
        int e0 = 0, i = 0, eq = 0;
        while (n) {
            res = mod_m(1LL * res * fac[n % m]);
            res = mod_m(1LL * res * ifac[r % m]);
            res = mod_m(1LL * res * ifac[k % m]);
            n /= p;
            r /= p;
            k /= p;
            e0 += n - r - k;
            if (e0 >= q)return 0;
            if (++i >= q)eq += n - r - k;
        }
        int d = !(p == 2 && q >= 3) && eq % 2 == 1 ? m - 1 : 1;
        res = mod_m(1LL * res * d);
        res = mod_m(1LL * res * mpow(p, e0));
        return res;
    }

private:
    int p, q, m;
    std::vector<int> fac, ifac;
    constexpr inline int mod_m(long long n) const { n %= m; return n < 0 ? n + m : n; }
    constexpr inline int mpow(int a, long long e) const {
        int r = 1;
        while (e) {
            if (e & 1)r = mod_m(1LL * a * r);
            a = mod_m(1LL * a * a);
            e >>= 1;
        }
        return r;
    }
};

struct binomial {
    binomial(int m) : m(m) {
        for (int i = 2;i * i <= m;i++) {
            if (m % i == 0) {
                int p = i, q = 0, pq = 1;
                while (m % i == 0) {
                    m /= i;
                    pq *= i;
                    q++;
                }
                bs.emplace_back(p, q, pq);
                ms.emplace_back(pq);
            }
        }
        if (m != 1) {
            bs.emplace_back(m, 1, m);
            ms.emplace_back(m);
        }
    }

    int C(long long n, long long k) const {
        if (m == 1)return 0;
        std::vector<long long> r, d;
        for (int i = 0;i < int(ms.size());i++) {
            d.emplace_back(ms[i]);
            r.emplace_back(bs[i].C(n, k));
        }
        return atcoder::crt(r, d).first;
    }

private:
    int m;
    std::vector<binomial_pre> bs;
    std::vector<int> ms;
};
