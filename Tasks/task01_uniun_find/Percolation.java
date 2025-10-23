import edu.princeton.cs.algs4.WeightedQuickUnionUF;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class Percolation {
    private final int n;
    private final boolean[] openSites;
    private final WeightedQuickUnionUF uf;
    private final WeightedQuickUnionUF ufNoBottom;
    private int openCount;
    private final int top;
    private final int bottom;

    public Percolation(int n) {
        if (n <= 0) throw new IllegalArgumentException();
        this.n = n;
        this.openSites = new boolean[n * n];
        this.uf = new WeightedQuickUnionUF(n * n + 2);
        this.ufNoBottom = new WeightedQuickUnionUF(n * n + 1);
        this.top = n * n;
        this.bottom = n * n + 1;
        this.openCount = 0;
    }

    private int index(int row, int col) {
        if (row < 1 || row > n || col < 1 || col > n) throw new IllegalArgumentException();
        return (row - 1) * n + (col - 1);
    }

    public void open(int row, int col) {
        int i = index(row, col);
        if (openSites[i]) return;
        openSites[i] = true;
        openCount++;
        if (row == 1) {
            uf.union(i, top);
            ufNoBottom.union(i, top);
        }
        if (row == n) uf.union(i, bottom);
        if (row > 1 && isOpen(row - 1, col)) {
            uf.union(i, index(row - 1, col));
            ufNoBottom.union(i, index(row - 1, col));
        }
        if (row < n && isOpen(row + 1, col)) {
            uf.union(i, index(row + 1, col));
            ufNoBottom.union(i, index(row + 1, col));
        }
        if (col > 1 && isOpen(row, col - 1)) {
            uf.union(i, index(row, col - 1));
            ufNoBottom.union(i, index(row, col - 1));
        }
        if (col < n && isOpen(row, col + 1)) {
            uf.union(i, index(row, col + 1));
            ufNoBottom.union(i, index(row, col + 1));
        }
    }

    public boolean isOpen(int row, int col) {
        return openSites[index(row, col)];
    }

    public boolean isFull(int row, int col) {
        return ufNoBottom.find(index(row, col)) == ufNoBottom.find(top);
    }

    public int numberOfOpenSites() {
        return openCount;
    }

    public boolean percolates() {
        return uf.find(top) == uf.find(bottom);
    }
}
