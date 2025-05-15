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

An AVL tree is a BST that maintains $|h_{l}(n)-h_{r}(n)|\leq 1,\ \forall n\in V(T)$. This property guarantees a logarithmetic relationship between number of noded and tree height.

Definition
: Denote $a$, $b$ as two nodes, $A$, $B$ and $C$ as three subtrees, a ***left rotation*** on node $a$ is defined by

<body></body>

In both **push** and **pop** operation, we uopdate the tree ***bottom-up***, therefore if we found an unbalanced subtree, then both it's subtrees are already balanced.

### Rotation

Lemma
: Before a neccessary ***left rotation***, $h_{r}(b)\geq h_{l}(b)\geq h_{l}(a)$ and $h_{r}(b)\geq h_{l}(a)+1$.

proof
: Before invoking a *left rotation*, $a$ is both right heavy and right sub-heavy, therefore
	$$\max\{h_{l}(b),h_{r}(b)\}+1=h_{r}(a)>h_{l}(a)+1
	\\ \max\{h_{l}(b),h_{r}(b)\}=h_{r}(b)$$
which implies $h_{r}(b)\geq h_{l}(a)+1$. Suppose $h_{l}(b)<h_{l}(a)$, thus
	$$h_{l}(b)+1<h_{l}(a)+1\leq h_{r}(b)\implies h_{r}(b)>h_{l}(b)+1$$
$b$ is right heavy, this is impossible since $b$ is balanced before $a$, therefore $h_{r}(b)\geq h_{l}(a)$.

As $b$ will replace $a$ as a subtree of above node, the rotation function does this by passing reference to index of $a$ in `pool[]`, denoted by `a_i`.

```cpp
void l_rotate(uint32_t& a_i) {
	uint32_t b_i = pool[a_i].r_subtree;           // preserve b_i to replace a_i finaly
	pool[a_i].r_subtree = pool[b_i].l_subtree;    // change b to B
	pool[b_i].l_subtree = a_i;                    //
	pool[a_i].r_height = pool[b_i].l_height;
	pool[b_i].l_height = pool[a_i].l_height + 1;  // this is guaranteed by h(B) >= h(A)
	a_i = b_i;
}
```
Right rotation is symetrically same.

### Push

$h_{l}$ and $h_{r}$ are updated at each ***push*** and ***pop*** operation. The most straightforward way is $h_{l}(n)=\max(h_{l}(n_{l}),h_{r}(n_{l}))$, this invokes **two** instructions, comparison and assignment. But in fact,

height update stops at certain node and we should avoid more assignments after that. This is flagged by `bool avl::h_update`

Lemma
: Each *push* results at most one *balancing*.

```cpp

```

### Pop

### Query On Index
