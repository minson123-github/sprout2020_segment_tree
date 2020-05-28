#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 800010;
int seg_add[maxn * 4], minv[maxn * 4];

void modify(int l, int r, int ql, int qr, int idx) {
	if (l == ql && r == qr) {
		seg_add[idx]++;
		minv[idx]++;
	} else {
		int mid = (l + r) >> 1;
		if (qr <= mid) modify(l, mid, ql, qr, idx << 1);
		else if (ql > mid) modify(mid + 1, r, ql, qr, idx << 1 | 1);
		else {
			modify(l, mid, ql, mid, idx << 1);
			modify(mid + 1, r, mid + 1, qr, idx << 1 | 1);
		}
		minv[idx] = min(minv[idx << 1], minv[idx << 1 | 1]) + seg_add[idx];
	}
}

int query(int l, int r, int pos, int idx) {
	if (l == r) return minv[idx];
	int mid = (l + r) >> 1;
	if (pos <= mid) return query(l, mid, pos, idx << 1) + seg_add[idx];
	return query(mid + 1, r, pos, idx << 1 | 1) + seg_add[idx];
}

int query_leq(int l, int r, int v, int idx) {
	if (l == r) return l;
	int mid = (l + r) >> 1;
	v -= seg_add[idx];
	if (minv[idx << 1 | 1] <= v) return query_leq(mid + 1, r, v, idx << 1 | 1);
	return query_leq(l, mid, v, idx << 1);
}

int main() {
	int n, l, r;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &l, &r);
		int v = query(0, n - 1, r, 1);
		r = query_leq(0, n - 1, v, 1);
		modify(0, n - 1, l, r, 1);
	}
	printf("%d\n", query(0, n - 1, n - 1, 1));
	return 0;
}
