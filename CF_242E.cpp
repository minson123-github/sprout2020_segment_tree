#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 100010;
int a[maxn], seg_xor[maxn * 4], seg_bit[20][maxn * 4];

inline void exec_xor(int idx, int len, int v) {
	seg_xor[idx] ^= v;
	for (int k = 0; k < 20; k++)
		if (v & (1 << k))
			seg_bit[k][idx] = len - seg_bit[k][idx];
}

inline void down(int idx, int l, int r) {
	int mid = (l + r) >> 1;
	if (seg_xor[idx]) {
		exec_xor(idx << 1, mid - l + 1, seg_xor[idx]);
		exec_xor(idx << 1 | 1, r - mid, seg_xor[idx]);
		seg_xor[idx] = 0;
	}
}

inline void up(int idx) {
	for (int k = 0; k < 20; k++)
		seg_bit[k][idx] = seg_bit[k][idx << 1] + seg_bit[k][idx << 1 | 1];
}

void modify(int l, int r, int ql, int qr, int v, int idx) {
	if (l == ql && r == qr) {
		exec_xor(idx, r - l + 1, v);
	} else {
		int mid = (l + r) >> 1;
		down(idx, l, r);
		if (qr <= mid) modify(l, mid, ql, qr, v, idx << 1);
		else if (ql > mid) modify(mid + 1, r, ql, qr, v, idx << 1 | 1);
		else {
			modify(l, mid, ql, mid, v, idx << 1);
			modify(mid + 1, r, mid + 1, qr, v, idx << 1 | 1);
		}
		up(idx);
	}
}

ll query(int l, int r, int ql, int qr, int idx) {
	if (l == ql && r == qr) {
		ll sum = 0;
		for (int k = 0; k < 20; k++)
			sum += (1ll << k) * seg_bit[k][idx];
		return sum;
	} else {
		int mid = (l + r) >> 1;
		down(idx, l, r);
		if (qr <= mid) return query(l, mid, ql, qr, idx << 1);
		else if (ql > mid) return query(mid + 1, r, ql, qr, idx << 1 | 1);
		return query(l, mid, ql, mid, idx << 1) + query(mid + 1, r, mid + 1, qr, idx << 1 | 1);
	}
}

void build(int l, int r, int idx) {
	if (l == r) {
		for (int k = 0; k < 20; k++)
			if (a[l] & (1 << k))
				seg_bit[k][idx]++;
	} else {
		int mid = (l + r) >> 1;
		build(l, mid, idx << 1);
		build(mid + 1, r, idx << 1 | 1);
		up(idx);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	build(1, n, 1);
	int m, t, l, r, x;
	scanf("%d", &m);
	while (m--) {
		scanf("%d%d%d", &t, &l, &r);
		if (t == 1) {
			printf("%lld\n", query(1, n, l, r, 1));
		} else {
			scanf("%d", &x);
			modify(1, n, l, r, x, 1);
		}
	}
	return 0;
}
