#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 100010;
pii tag[maxn * 4];
int a[maxn], b[maxn];

void build(int l, int r, int idx) {
	tag[idx] = pii(-1, -1);
	int mid = (l + r) >> 1;
	if (l != r) build(l, mid, idx << 1), build(mid + 1, r, idx << 1 | 1);
}

inline void down(int idx) {
	if (tag[idx] != pii(-1, -1))
		tag[idx << 1] = tag[idx << 1 | 1] = tag[idx];
	tag[idx] = pii(-1, -1);
}

void modify(int l, int r, int ql, int qr, pii pr, int idx) {
	if (l == ql && r == qr) {
		tag[idx] = pr;
	} else {
		int mid = (l + r) >> 1;
		down(idx);
		if (qr <= mid) modify(l, mid, ql, qr, pr, idx << 1);
		else if (ql > mid) modify(mid + 1, r, ql, qr, pr, idx << 1 | 1);
		else {
			modify(l, mid, ql, mid, pr, idx << 1);
			modify(mid + 1, r, mid + 1, qr, pr, idx << 1 | 1);
		}
	}
}

int query(int l, int r, int pos, int idx) {
	if (l == r)
		return tag[idx] == pii(-1, -1) ? b[l] : a[tag[idx].first + l - tag[idx].second];
	int mid = (l + r) >> 1;
	down(idx);
	if (pos <= mid) return query(l, mid, pos, idx << 1);
	return query(mid + 1, r, pos, idx << 1 | 1);
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	for (int i = 1; i <= n; i++)
		scanf("%d", b + i);
	int t, x, y, k;
	build(1, n, 1);
	while (m--) {
		scanf("%d%d", &t, &x);
		if (t == 1) {
			scanf("%d%d", &y, &k);
			modify(1, n, y, y + k - 1, pii(x, y), 1);
		} else {
			printf("%d\n", query(1, n, x, 1));
		}
	}
	return 0;
}
