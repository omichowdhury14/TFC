from heapq import heappop, heappush

INF = 10**9


def func(a, b):
   
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def astar(grid, st, en):
    n = len(grid)
    m = len(grid[0])

    dist = [[INF] * m for _ in range(n)]
    par = [[None] * m for _ in range(n)]

    pq = []

    dist[st[0]][st[1]] = 0

    f = func(st, en)
    heappush(pq, (f, 0, st[0], st[1]))

    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]

    while pq:
        f, g, x, y = heappop(pq)
        if g != dist[x][y]:
            continue

        if (x, y) == en:
            break

        for k in range(4):
            nx = x + dx[k]
            ny = y + dy[k]

            if nx < 0 or nx >= n or ny < 0 or ny >= m:
                continue
            if grid[nx][ny] == 1:  
                continue

            ng = g + 1

            if ng < dist[nx][ny]:
                dist[nx][ny] = ng
                par[nx][ny] = (x, y)

                nf = ng + func((nx, ny), en)

                heappush(pq, (nf, ng, nx, ny))

    if dist[en[0]][en[1]] == INF:
        return None

    ans = []
    cur = en
    while cur is not None:
        ans.append(cur)
        cur = par[cur[0]][cur[1]]

    ans.reverse()

    return ans


def main():
    n, m = map(int, input().split())

    grid = []

    for _ in range(n):
        grid.append(list(map(int, input().split())))

    sx, sy = map(int, input().split())
    ex, ey = map(int, input().split())

    st = (sx, sy)
    en = (ex, ey)
    ans = astar(grid, st, en)

    if ans is None:
        print("NO")
    else:
        print("YES")
        print("Distance:", len(ans) - 1)

        for x, y in ans:
            print(x, y)


main()