using System;
using System.Collections.Generic;

class Program
{
    static int n, m;
    static int[,] a;

    static bool InRange(int x, int y) => (0 <= x && x < n && 0 <= y && y < m);

    static bool Can(int L)
    {
        // 시작/끝은 반드시 밟아야 함
        if (a[0, 0] > L || a[n - 1, m - 1] > L) return false;

        // visited[r, c, usedJump(0/1)]
        bool[,,] vis = new bool[n, m, 2];
        var q = new Queue<(int r, int c, int used)>();

        vis[0, 0, 0] = true;
        q.Enqueue((0, 0, 0));

        int[] dx = { -1, 1, 0, 0 };
        int[] dy = { 0, 0, -1, 1 };

        // 벽 부수기 가능 BFS
        while (q.Count > 0)
        {
            var cur = q.Dequeue();
            int r = cur.r, c = cur.c, used = cur.used;

            if (r == n - 1 && c == m - 1) return true;

            for (int dir = 0; dir < 4; dir++)
            {
                int nr = r + dx[dir];
                int nc = c + dy[dir];
                if (InRange(nr, nc) && a[nr, nc] <= L && !vis[nr, nc, used])
                {
                    vis[nr, nc, used] = true;
                    q.Enqueue((nr, nc, used));
                }

                if (used == 0)
                {
                    int jr = r + 2 * dx[dir];
                    int jc = c + 2 * dy[dir];
                    if (InRange(jr, jc) && a[jr, jc] <= L && !vis[jr, jc, 1])
                    {
                        vis[jr, jc, 1] = true;
                        q.Enqueue((jr, jc, 1));
                    }
                }
            }
        }

        return false;
    }

    static void Main()
    {
        var first = Console.ReadLine().Split(new[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
        n = int.Parse(first[0]);
        m = int.Parse(first[1]);

        a = new int[n, m];
        int lo, hi, ans;

        // lo는 반드시 시작/끝을 밟아야 하므로 그 둘 중 큰 값 이상
        // hi는 격자 내 최대값
        int maxv = 0;
        int needMin = 0;

        for (int i = 0; i < n; i++)
        {
            var parts = Console.ReadLine().Split(new[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
            for (int j = 0; j < m; j++)
            {
                a[i, j] = int.Parse(parts[j]);
                if (a[i, j] > maxv) maxv = a[i, j];
            }
        }

        needMin = Math.Max(a[0, 0], a[n - 1, m - 1]);
        lo = needMin;
        hi = maxv;
        ans = hi;

        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (Can(mid))
            {
                ans = mid;
                hi = mid - 1;
            }
            else
            {
                lo = mid + 1;
            }
        }

        Console.WriteLine(ans);
    }
}
