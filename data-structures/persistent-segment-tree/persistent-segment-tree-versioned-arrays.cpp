// Persistent Segment Tree (PST) implementation working with versioned arrays.
class PersistentSegmentTree
{
private:
    // Represents a single node in the persistent segment tree.
    struct Node
    {
        int left;   // Index of the left child node
        int right;  // Index of the right child node
        int sum;    // Stored sum for this range
        Node() : left(0), right(0), sum(0) {} // Default constructor initializing fields to 0
    };

    int n;              // Size of the array (1-indexed)
    vector<Node> tree;  // Dynamic node pool storing all nodes across all versions
    vector<int> roots;  // Stores the root node indices for each version

    // Allocates a new node in the tree pool and returns its index.
    int new_node()
    {
        tree.emplace_back();
        return tree.size() - 1;
    }

    // Recursively builds the initial segment tree from the array and returns the root index.
    int build(vector<int> &arr, int l, int r)
    {
        int curr = new_node();

        if (l == r)
        {
            tree[curr].sum = arr[l];
            return curr;
        }

        int mid = (l + r) / 2;

        tree[curr].left = build(arr, l, mid);
        tree[curr].right = build(arr, mid + 1, r);

        tree[curr].sum = tree[tree[curr].left].sum + tree[tree[curr].right].sum;
        return curr;
    }

    // Creates a new path of nodes to update a value at 'pos' based on the 'prev' version, returning the new node/root index.
    int update(int prev, int l, int r, int pos, int val)
    {
        int curr = new_node();

        tree[curr] = tree[prev];

        if (l == r)
        {
            tree[curr].sum = val;
            return curr;
        }

        int mid = (l + r) / 2;
        if (pos <= mid)
            tree[curr].left = update(tree[prev].left, l, mid, pos, val);
        else
            tree[curr].right = update(tree[prev].right, mid + 1, r, pos, val);
        tree[curr].sum = tree[tree[curr].left].sum + tree[tree[curr].right].sum;
        return curr;
    }

    // Recursively queries the range sum [ql, qr] from the current node and returns the accumulated sum.
    int query(int curr, int l, int r, int ql, int qr)
    {
        if (qr < l || ql > r)
            return 0;

        if (qr >= r && ql <= l)
            return tree[curr].sum;

        int mid = (l + r) / 2;
        return query(tree[curr].left, l, mid, ql, qr) + query(tree[curr].right, mid + 1, r, ql, qr);
    }

public:
    // Constructor for a 1-indexed array: initializes the tree and creates the initial version (version 0).
    PersistentSegmentTree(vector<int> &arr)
    {
        n = arr.size() - 1;
        tree.emplace_back();
        roots.push_back(build(arr, 1, n));
    }

    // Updates an existing version at position 'pos' with 'val', modifies that version in-place, and returns a version identifier/status integer.
    int update_version(int version, int pos, int val)
    {
        if (version < 0 || version >= roots.size() || pos < 1 || pos > n)
            return -1;
        int new_root = update(roots[version], 1, n, pos, val);
        roots[version] = new_root;
        return roots.size() - 1;
    }

    // Queries the sum in range [l, r] for a specific version, returning the resulting sum.
    int query(int version, int l, int r)
    {
        if (version < 0 || version >= roots.size() || l < 1 || r > n || l > r)
            return 0;

        return query(roots[version], 1, n, l, r);
    }

    // Returns the total number of version roots currently tracked.
    int count_versions()
    {
        return roots.size();
    }

    // Duplicates an existing version's root by index and appends it as a new version.
    void dpc(int idx)
    {
        roots.push_back(roots[idx]);
    }
};