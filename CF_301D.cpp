#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 200010;
int pos[maxn];
vector<int> fac[maxn];
struct Section {
	int o, l, r;
	Section(int _o, int _l, int _r):o(_o), l(_l), r(_r) {}
	inline bool operator<(const Section& rhs) const {
		if (l != rhs.l) return l > rhs.l;
		return o < rhs.o;
	}
};
vector<Section> sec;
int ans[maxn], sum[maxn * 4];

void modify(int l, int r, int pos, int idx) {
	if (l == r) sum[idx]++;
	else {
		int mid = (l + r) >> 1;
		if (pos <= mid) modify(l, mid, pos, idx << 1);
		else modify(mid + 1, r, pos, idx << 1 | 1);
		sum[idx] = sum[idx << 1] + sum[idx << 1 | 1];
	}
}

int query(int l, int r, int ql, int qr, int idx) {
	if (l == ql && r == qr) return sum[idx];
	int mid = (l + r) >> 1;
	if (qr <= mid) return query(l, mid, ql, qr, idx << 1);
	else if (ql > mid) return query(mid + 1, r, ql, qr, idx << 1 | 1);
	return query(l, mid, ql, mid, idx << 1) + query(mid + 1, r, mid + 1, qr, idx << 1 | 1);
}

int main() {
	int n, m, p;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p);
		pos[p] = i;
	}
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j += i)
			fac[j].push_back(i);
	for (int x = 1; x <= n; x++) {
		for (int i = 0; i < (int)fac[x].size(); i++) {
			int y = fac[x][i];
			int l = pos[x], r = pos[y];
			if (l > r) swap(l, r);
			sec.push_back(Section(0, l, r));
		}
	}
	int l, r;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &l, &r);
		sec.push_back(Section(i, l, r));
	}
	sort(sec.begin(), sec.end());
	for (int i = 0; i < (int)sec.size(); i++) {
		if (sec[i].o == 0) {
			modify(1, n, sec[i].r, 1);
		} else {
			ans[sec[i].o] = query(1, n, sec[i].l, sec[i].r, 1);
		}
	}
	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}
