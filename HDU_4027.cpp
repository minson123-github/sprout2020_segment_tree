#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;

const int maxn = 100010;
ll sum[maxn * 4];
void modify(int l, int r, int ql, int qr, int idx) {
	if (sum[idx] == r - l + 1) return;
	if (l == r) {
		sum[idx] = sqrt(sum[idx]);
	} else if (l == ql && r == qr){
		int mid = (l + r) >> 1;
		modify(l, mid, l, mid, idx << 1);
		modify(mid + 1, r, mid + 1, r, idx << 1 | 1);
		sum[idx] = sum[idx << 1] + sum[idx << 1 | 1];
	} else {
		int mid = (l + r) >> 1;
		if (qr <= mid) modify(l, mid, ql, qr, idx << 1);
		else if (ql > mid) modify(mid + 1, r, ql, qr, idx << 1 | 1);
		else {
			modify(l, mid, ql, mid, idx << 1);
			modify(mid + 1, r, mid + 1, qr, idx << 1 | 1);
		}
		sum[idx] = sum[idx << 1] + sum[idx << 1 | 1];
	}
}

ll query(int l, int r, int ql, int qr, int idx) {
	if (l == ql && r == qr) return sum[idx];
	int mid = (l + r) >> 1;
	if (qr <= mid) return query(l, mid, ql, qr, idx << 1);
	else if (ql > mid) return query(mid + 1, r, ql, qr, idx << 1 | 1);
	return query(l, mid, ql, mid, idx << 1) + query(mid + 1, r, mid + 1, qr, idx << 1 | 1);
}

ll v[maxn];
void build(int l, int r, int idx) {
	if (l == r) {
		sum[idx] = v[l];
	} else {
		int mid = (l + r) >> 1;
		build(l, mid, idx << 1);
		build(mid + 1, r, idx << 1 | 1);
		sum[idx] = sum[idx << 1] + sum[idx << 1 | 1];
	}
}

vector<pli> tmp;

int main() {
	int n, kase = 0;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++)
			scanf("%lld", v + i);
		build(1, n, 1);
		int m, t, x, y;
		scanf("%d", &m);
		printf("Case #%d:\n", ++kase);
		while (m--) {
			scanf("%d%d%d", &t, &x, &y);
			if (x > y) swap(x, y);
			if (t == 0) {
				modify(1, n, x, y, 1);
			} else {
				printf("%lld\n", query(1, n, x, y, 1));
			}
		}
		puts("");
	}
	return 0;
}
