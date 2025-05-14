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

An AVL tree is a BST that guarantees $|h_{l}(n)-h_{r}(n)|\leq 1,\ \forall n\in V(T)$. This property

Definition
: Denote $a$, $b$ as two nodes, $A$, $B$ and $C$ as three subtrees, a ***left rotation*** on node $a$ is

<body></body>

Before writing the code, there are several lemmas that make it easier.

Lemma
: Before a neccessary ***left rotation***, $h_{r}(b)\geq h_{l}(b)\geq h_{l}(a)$.

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
where `a_i` and `b_i` is the indices of node $a$ and $b$ in `pool[]`. Right rotation is symetrically same.

### Updating $h_{l}$ and $h_{r}$

$h_{l}$ and $h_{r}$ are updated at each ***push*** and ***pop*** operation. The most straightforward way is $h_{l}(n)=\max(h_{l}(n_{l}),h_{r}(n_{l}))$, this invokes **two** instructions, comparison and assignment. But in fact,

height update stops at certain node and we should avoid more assignments after that. This is flagged by `bool avl::h_update`

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
