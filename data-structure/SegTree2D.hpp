template <class S, S(*op)(S, S), S(*e)()> struct SegTree2D {
public:
    SegTree2D() { init(std::vector<std::vector<S>>()); }
    explicit SegTree2D(int _h, int _w) { init(std::vector<std::vector<S>>(_h, std::vector<S>(_w, e()))); }
    explicit SegTree2D(const std::vector<std::vector<S>>& _data) { init(_data); }

    void set(int x, int y, S v) {
        assert(0 <= x && x < _h && 0 <= y && y < _w);
        x += h; y += w;
        data[x][y] = v;
        for (int nx = x; nx > 0; nx >>= 1)
            for (int ny = y; ny > 0; ny >>= 1)
                update(nx, ny);
    }

    S get(int x, int y) const {
        assert(0 <= x && x < _h && 0 <= y && y < _w);
        return data[x + h][y + w];
    }

    S prod(int lx, int ly, int rx, int ry) const {
        assert(0 <= lx && lx <= rx && rx <= _h && 0 <= ly && ly <= ry && ry <= _w);
        S sml = e(), smr = e();
        int nlx = lx + h, nrx = rx + h;
        while (nlx < nrx) {
            if (nlx & 1) {
                S sml2 = e(), smr2 = e();
                int nly = ly + w, nry = ry + w;
                while (nly < nry) {
                    if (nly & 1) sml2 = op(sml2, data[nlx][nly++]);
                    if (nry & 1) smr2 = op(smr2, data[nlx][--nry]);
                    nly >>= 1;
                    nry >>= 1;
                }
                nlx++;
                sml = op(sml, op(sml2, smr2));
            }
            if (nrx & 1) {
                nrx--;
                S sml2 = e(), smr2 = e();
                int nly = ly + w, nry = ry + w;
                while (nly < nry) {
                    if (nly & 1) sml2 = op(sml2, data[nrx][nly++]);
                    if (nry & 1) smr2 = op(smr2, data[nrx][--nry]);
                    nly >>= 1;
                    nry >>= 1;
                }
                smr = op(smr, op(sml2, smr2));
            }
            nlx >>= 1;
            nrx >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return data[1][1]; }

    template<class stream>
    friend stream& operator<<(stream& os, const SegTree2D& st) {
        // to debug
        os << "\n";
        for (int i = 1;i < 2 * st.h;i++) {
            os << "[";
            for (int j = 1;j < 2 * st.w;j++)
                os << st.data[i][j] << (j == 2 * st.w - 1 ? "]\n" : ",");
        }
        return os;
    }

private:
    int h, w, logh, logw, _h, _w;
    std::vector<std::vector<S>> data;
    void update(int x, int y) {
        if (x >= h && y >= w)return;
        else if (y < w) data[x][y] = op(data[x][2 * y], data[x][2 * y + 1]);
        else data[x][y] = op(data[2 * x][y], data[2 * x + 1][y]);
    }

    void init(const std::vector<std::vector<S>>& _data) {
        _h = int(_data.size()); _w = int(_data[0].size());
        int xh = 1, xw = 1;
        while (xh < _h)xh <<= 1, logh++;
        while (xw < _w)xw <<= 1, logw++;
        h = xh; w = xw;
        data = std::vector<std::vector<S>>(2 * h, std::vector<S>(2 * w, e()));
        for (int i = 0;i < _h;i++)
            for (int j = 0;j < _w;j++)
                data[i + h][j + w] = _data[i][j];
        for (int i = 2 * h - 1;i >= 0;i--)
            for (int j = 2 * w - 1;j >= 0;j--)
                update(i, j);
    }
};
