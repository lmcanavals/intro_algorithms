#ifndef __RANDMAP_H__
#define __RANDMAP_H__

#include <stdlib.h>

struct Vert {
    int* v;
    int n;
};

void shuffle(int* a, int n) {
    for (int i = n - 1; i > 0; --i) {
        int randomPos = rand() % i;
        int temp = a[i];
        a[i] = a[randomPos];
        a[randomPos] = temp;
    }
}

int** randLab(int rows, int cols) {
    if (rows % 2 == 0) --rows;
    if (cols % 2 == 0) --cols;

    int n = rows / 2;
    int m = cols / 2;
    Vert* G = new Vert[n*m];
    int p, q;
    for (int i = 0; i < n; ++i)  {
        for (int j = 0; j < m; ++j) {
            int u = i * m + j;
            G[u].v = new int[4];
            G[u].n = 0;
            p = i - 1; q = j;
            if (!(p < 0 || p >= n || q < 0 || q >= m)) G[u].v[G[u].n++] = p * m + q;
            p = i;     q = j - 1;
            if (!(p < 0 || p >= n || q < 0 || q >= m)) G[u].v[G[u].n++] = p * m + q;
            p = i + 1; q = j;
            if (!(p < 0 || p >= n || q < 0 || q >= m)) G[u].v[G[u].n++] = p * m + q;
            p = i;     q = j + 1;
            if (!(p < 0 || p >= n || q < 0 || q >= m)) G[u].v[G[u].n++] = p * m + q;
        }
    }

    bool* visited = new bool[n*m];
    int* path = new int[n*m];
    int* stack = new int[n*m];
    int ns = 0;
    for (int i = 0; i < n*m; ++i) {
        visited[i] = false;
        path[i] = -1;
    }
    stack[ns++] = 0;

    while (ns) {
        int u = stack[--ns];
        for (int i = 0; i < G[u].n; ++i) {
            int v = G[u].v[i];
            if (!visited[v]) {
                visited[v] = true;
                stack[ns++] = v;
                path[v] = u;
            }
        }
        shuffle(stack, ns);
    }

    int** lab = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        lab[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            lab[i][j] = !(i % 2 == 1 && j % 2 == 1) * 3;
        }
    }

    for (int u = 0; u < n*m; ++u) {
        if (path[u] < 0) continue;
        int v = path[u];
        int i0 = (u / m) * 2 + 1;
        int j0 = (u % m) * 2 + 1;
        int i1 = (v / m) * 2 + 1;
        int j1 = (v % m) * 2 + 1;
        if (i0 == i1) {
            lab[i0][(j0 + j1) / 2] = 0;
        } else {
            lab[(i0 + i1) / 2][j0] = 0;
        }
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (lab[i][j] != 0) {
                lab[i][j] = 0;
                p = i - 1; q = j;
                if (!(p < 0 || p >= rows || q < 0 || q >= cols) && lab[p][q] != 0) {
                    lab[i][j] = 1;
                }
                p = i + 1; q = j;
                if (!(p < 0 || p >= rows || q < 0 || q >= cols) && lab[p][q] != 0) {
                    lab[i][j] = 1;
                }
                p = i;     q = j - 1;
                if (!(p < 0 || p >= rows || q < 0 || q >= cols) && lab[p][q] != 0) {
                    lab[i][j] |= 2;
                }
                p = i;     q = j + 1;
                if (!(p < 0 || p >= rows || q < 0 || q >= cols) && lab[p][q] != 0) {
                    lab[i][j] |= 2;
                }
            }
        }
    }

    delete[] visited;
    delete[] path;
    for (int i = 0; i < n*m; ++i) {
        delete[] G[i].v;
    }
    delete[] G;
    delete[] stack;

    return lab;
}

#endif
