template <class S, S(*op)(S, S), S(*e)()> struct SegTree2DCompress {
public:
    using coordinate_t = long long;

    SegTree2DCompress() : SegTree2DCompress(std::vector<coordinate_t>(), std::vector<coordinate_t>()) {}
    explicit SegTree2DCompress(const std::vector<coordinate_t>& px, const std::vector<coordinate_t>& py) {
        for (coordinate_t x : px)hidx.emplace_back(x);
        compress(hidx);
        h = 1;
        while (h < int(hidx.size()))h <<= 1;
        widx.resize(h * 2);
        int sz = int(px.size());
        for (int i = 0; i < sz;i++) {
            int ix = std::lower_bound(hidx.begin(), hidx.end(), px[i]) - hidx.begin();
            widx[ix + h].emplace_back(py[i]);
        }
        for (int i = h * 2 - 1;i >= 1;i--) {
            compress(widx[i]);
            for (coordinate_t p : widx[i])widx[i / 2].emplace_back(p);
        }
        data.resize(h * 2);
        for (int i = 1; i < h * 2; i++)data[i] = atcoder::segtree<S, op, e>(wsz(i));
    }

    void set(coordinate_t x, coordinate_t y, S v) {
        int ix = std::lower_bound(hidx.begin(), hidx.end(), x) - hidx.begin();
        assert(ix < h);
        ix += h;
        int iy = std::lower_bound(widx[ix].begin(), widx[ix].end(), y) - widx[ix].begin();
        data[ix].set(iy, v);
        int seen = -1, idx = -1;
        ix >>= 1;
        for (; ix > 0; ix >>= 1) {
            iy = std::lower_bound(widx[ix].begin(), widx[ix].end(), y) - widx[ix].begin();
            assert(iy < wsz(ix));
            assert(widx[ix][iy] == y);
            int liy = seen == ix * 2 ? idx : std::lower_bound(widx[ix * 2].begin(), widx[ix * 2].end(), y) - widx[ix * 2].begin();
            int riy = seen == ix * 2 + 1 ? idx : std::lower_bound(widx[ix * 2 + 1].begin(), widx[ix * 2 + 1].end(), y) - widx[ix * 2 + 1].begin();
            S vl = e(), vr = e();
            if (liy < wsz(ix * 2) && widx[ix * 2][liy] == y)vl = data[ix * 2].get(liy);
            if (riy < wsz(ix * 2 + 1) && widx[ix * 2 + 1][riy] == y)vr = data[ix * 2 + 1].get(riy);
            data[ix].set(iy, op(vl, vr));
            seen = ix; idx = iy;
        }
    }

    S prod(coordinate_t lx, coordinate_t ly, coordinate_t rx, coordinate_t ry) const {
        int lix = std::lower_bound(hidx.begin(), hidx.end(), lx) - hidx.begin();
        int rix = std::lower_bound(hidx.begin(), hidx.end(), rx) - hidx.begin();
        S sml = e(), smr = e();
        lix += h; rix += h;
        while (lix < rix) {
            if (lix & 1) {
                int liy = std::lower_bound(widx[lix].begin(), widx[lix].end(), ly) - widx[lix].begin();
                int riy = std::lower_bound(widx[lix].begin(), widx[lix].end(), ry) - widx[lix].begin();
                sml = op(sml, data[lix].prod(liy, riy));
                lix++;
            }
            if (rix & 1) {
                rix--;
                int liy = std::lower_bound(widx[rix].begin(), widx[rix].end(), ly) - widx[rix].begin();
                int riy = std::lower_bound(widx[rix].begin(), widx[rix].end(), ry) - widx[rix].begin();
                smr = op(smr, data[rix].prod(liy, riy));
            }
            lix >>= 1;
            rix >>= 1;
        }
        return op(sml, smr);
    }

    S get(coordinate_t x, coordinate_t y) const {
        int ix = std::lower_bound(hidx.begin(), hidx.end(), x) - hidx.begin();
        int iy = std::lower_bound(widx[ix + h].begin(), widx[ix + h].end(), y) - widx[ix + h].begin();
        return data[ix + h].get(iy);
    }

    template<class stream>
    friend stream& operator<<(stream& os, const SegTree2DCompress& st) {
        os << "\n";
        for (int i = 1;i < 2 * st.h;i++) {
            os << "[";
            for (int j = 0;j < st.wsz(i);j++)os << st.data[i].get(j) << (j == int(st.widx[i].size()) - 1 ? "" : ",");
            os << "]\n";
        }
        return os;
    }

private:
    int h;
    std::vector<atcoder::segtree<S, op, e>> data;
    std::vector<std::vector<coordinate_t>> widx;
    std::vector<coordinate_t> hidx;

    inline constexpr int wsz(int k) const noexcept { return int(widx[k].size()); }
    static inline constexpr void compress(std::vector<coordinate_t>& v) { std::sort(v.begin(), v.end()); v.erase(std::unique(v.begin(), v.end()), v.end()); }
};