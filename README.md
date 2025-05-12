# Binary Search Tree

A binary search tree (BST) is a data structure maintains a sorted order of elements.

```cpp
template<class T, size_t N> struct node {
	node()
		: l_height(0), r_height(0), l_subtree(0), r_subtree(0), l_size(0), r_size(0) {
	}

	T value;
	uint32_t l_height, r_height;
	uint32_t l_subtree, r_subtree;
	uint32_t l_size, r_size;
};
```

## AVL Tree

An AVL tree is a BST that guarantees $|l\_height-r\_height|\leq 1$. This property

Definition
: Denote $a$, $b$ as two nodes, $A$, $B$ and $C$ as three subtrees, a ***left rotation*** on node $a$ is

<body></body>

```cpp
void l_rotate(uint32_t& a_i) {
	uint32_t b_i = pool[a_i].r_subtree;
	pool[a_i].r_subtree = pool[b_i].l_subtree;
	pool[b_i].l_subtree = a_i;
	pool[a_i].r_height = pool[b_i].l_height;
	pool[b_i].l_height = pool[a_i].l_height + 1;
	a_i = b_i;
}
```
where `a_i` and `b_i` is the indices of node $a$ and $b$ in `pool[]`. Right rotation symetrically same.

### Calculate $l\_height$ and $r\_height$

One might think that `l_height = std::max(pool[l_subtree].l_height, pool[l_subtree].r_height)`, but in fact, 

Lemma
: Each *push* results at most one *balancing*.

```cpp
template<class T, size_t N> struct node {
	node()
		: l_height(0), r_height(0), l_subtree(0), r_subtree(0), l_size(0), r_size(0) {
	}

	T value;
	uint32_t l_height, r_height;
	uint32_t l_subtree, r_subtree;
	uint32_t l_size, r_size;
};
```

```cpp

```
