using System;
using System.Collections.Generic;
using System.IO;

class Program
{
    // Fast scanner
    sealed class FastScanner
    {
        private readonly Stream _s;
        private readonly byte[] _b = new byte[1 << 16];
        private int _l, _p;
        public FastScanner(Stream s) { _s = s; }
        private byte Read()
        {
            if (_p >= _l)
            {
                _l = _s.Read(_b, 0, _b.Length);
                _p = 0;
                if (_l <= 0) return 0;
            }
            return _b[_p++];
        }
        public int NextInt()
        {
            byte c;
            do c = Read(); while (c <= 32);
            int sign = 1;
            if (c == '-') { sign = -1; c = Read(); }
            int val = 0;
            while (c > 32)
            {
                val = val * 10 + (c - 48);
                c = Read();
            }
            return val * sign;
        }
    }

    struct Query
    {
        public int t;      
        public int u;       
        public int idx;
        public long nojump; 
    }

    static void Main()
    {
        var fs = new FastScanner(Console.OpenStandardInput());
        int N = fs.NextInt();
        int Q = fs.NextInt();

        long[][] P = new long[N + 1][];
        for (int i = 0; i <= N; i++) P[i] = new long[N + 1];

        for (int i = 1; i <= N; i++)
        {
            long acc = 0;
            for (int j = 1; j <= N; j++)
            {
                acc += fs.NextInt();
                P[i][j] = acc;
            }
        }

        const long INF = (long)1e18;
        long[][] B = new long[N][];
        for (int k = 0; k < N; k++)
        {
            B[k] = new long[N + 1]; // 1..N 사용
            long best = INF;
            for (int u = 1; u <= N; u++)
            {
                long val = P[u][N] - P[u][k];
                if (val < best) best = val;
                B[k][u] = best;
            }
        }

        List<Query>[] byRow = new List<Query>[N + 1];
        long[] ans = new long[Q];

        for (int qi = 0; qi < Q; qi++)
        {
            int sx = fs.NextInt();
            int sy = fs.NextInt();
            int L = fs.NextInt();

            int t = sy - 1; 
            long nojump = P[sx][N] - P[sx][t];

            int u = sx - Math.Max(L, 1); 
            if (u <= 0)
            {
                ans[qi] = nojump; 
                continue;
            }

            (byRow[sx] ??= new List<Query>()).Add(new Query
            {
                t = t, u = u, idx = qi, nojump = nojump
            });
        }

        for (int x = 1; x <= N; x++)
        {
            var list = byRow[x];
            if (list == null || list.Count == 0) continue;

            // t 내림차순 정렬 → k를 내릴 때 해당 t를 즉시 처리
            list.Sort((a, b) => b.t.CompareTo(a.t));
            int pos = 0;

            long[] best = new long[x]; // 1..x-1 사용
            for (int i = 1; i < x; i++) best[i] = INF;

            for (int k = N - 1; k >= 0; k--)
            {
                long pxk = P[x][k];

                // 모든 u(1..x-1)에 대해 best[u] 갱신
                for (int u = 1; u < x; u++)
                {
                    long cand = pxk + B[k][u];
                    if (cand < best[u]) best[u] = cand;
                }

                // t==k 인 쿼리 답변
                while (pos < list.Count && list[pos].t == k)
                {
                    var q = list[pos];
                    long jumpCost = best[q.u] - P[x][k];
                    long res = q.nojump < jumpCost ? q.nojump : jumpCost;
                    ans[q.idx] = res;
                    pos++;
                }
            }
        }

        var sw = new StreamWriter(Console.OpenStandardOutput());
        for (int i = 0; i < Q; i++) sw.WriteLine(ans[i]);
        sw.Flush();
    }
}
