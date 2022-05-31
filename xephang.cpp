#include <bits/stdc++.h>

using namespace std;
namespace {
	// macros definitions
	#define all(a)  (a).begin(),  (a).end()
	#define rall(a) (a).rbegin(), (a).rend()
	#define ft first
	#define se second
	#define For(i, u, v) for (int i = (u), _n_ = (v); i <= _n_; i++)
	#define Fod(i, u, v) for (int i = (u), _n_ = (v); i >= _n_; i--)

	// typedefs & constants
	using chr = char;	 using ll = long long;	 using pll = pair<ll, ll>;
	using str = string;   using ld = long double;   using pii = pair<int, int>;
	using p3i = pair<pii, int>;
	using pil = pair<ll, int>;
	template<class T> using MaxHeap = priority_queue<T, vector<T>,	less<T>>;
	template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
	
	// useful functions
	template<class A, class B>
	bool Maxz(A &a, B b) { return a < b && (a = b, true); }
	template<class A, class B>
	bool Minz(A &a, B b) { return b < a && (a = b, true); }
} // main template

const int N = (1<<17), M = 5e4+5;

int n, q;
int ar[M];
vector<int> br(N), cr(N); // br = max, cr = min

void init(int node, int l, int r, vector<int>& mr, bool ok)
{
	//cout << node << " " << l << " " << r << '\n';
	if(l == r)
	{
		mr[node] = l;
		return;
	}
	else
	{
		init(2*node, l, (l+r)/2, mr, ok);
		init(2*node+1, (l+r)/2+1, r, mr, ok);
	}

	if(ok)
	{
		if(ar[mr[2*node]] <= ar[mr[2*node+1]])
			mr[node] = mr[2*node];
		else
			mr[node] = mr[2*node+1];
	}
	else
	{
		if(ar[mr[2*node]] >= ar[mr[2*node+1]])
				mr[node] = mr[2*node];
			else
				mr[node] = mr[2*node+1];
	}
}

int query(int node, int l, int r, vector<int> mr, int i, int j, bool ok)
{
	int p1, p2;

	if(i > r || j < l)
	{
		return -1;
	}
	
	if(l >= i && r <= j)
		return mr[node];

	p1 = query(2*node, l, (l+r)/2, mr, i, j, ok);
	p2 = query(2*node+1, (l+r)/2+1, r, mr, i, j, ok);

	if(p1 == -1)
		return mr[node] = p2;
	
	if(p2 == -1)
		return mr[node] = p1;
	
	if(ok)
	{
		if(ar[p1] <= ar[p2])
			return mr[node] = p1;
		
		return mr[node] = p2;
	}
	else
	{
		if(ar[p1] >= ar[p2])
			return mr[node] = p1;
			
		return mr[node] = p2;
	}
}

/* -----------------[ MAIN CODE GOES HERE ]----------------- */
int main() {
	cin.tie(nullptr) -> sync_with_stdio(false);
	
	cin >> n >> q;
	for(int i = 1; i <= n; i++) cin >> ar[i];

	init(1, 1, n, br, 1);
	init(1, 1, n, cr, 0);

	while(q--)
	{
		int l, r;
		cin >> l >> r;

		int u = query(1, 1, n, br, l, r, 1);
		int v = query(1, 1, n, cr, l, r, 0);

		cout << abs(ar[u]-ar[v]) << '\n';
	}
	//cout << '\n';

	// for(int i = 1; i <= n; i++)
	// 	cout << ar[i] << " ";
	// cout << '\n';

	//for(int i = 1; i <= 13/*2*(1<<(int)(log2(n)))*/; i++)
	//	cout << br[i] << " ";
	// cout << '\n';
	//for(int i = 1; i <= (1<<(int)(log2(n)+2)); i++)
	//	cout << br[i] << " ";
}
//__________,___,_________________________________________
//__________[O.o]_____________|\__/,|   (`\.______________
//__________/)__)____________.|o o  |_   ) )______________
//_________--"--"--____----(((---(((----__________________
//________________________________________________________
