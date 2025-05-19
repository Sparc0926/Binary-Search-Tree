#pragma once

#define TEST

#include <stdint.h>

#ifdef TEST
#	include <stdio.h>
#	include <assert.h>
#endif

template <class T, size_t N> class avl {
private:
	struct node {
		node()
			: lHeight(0), rHeight(0), lSubtree(0), rSubtree(0), lSize(0), rSize(0) {
		}
		~node() {
		}
		T value;
		uint32_t lHeight, rHeight;
		uint32_t lSubtree, rSubtree;
		uint32_t lSize, rSize;
	};
	bool(*cmp)(const T& a, const T& b);
	uint32_t root, pool_ptr;
	node* pool;
	bool hUpdate;
	/// <summary>
	/// left rotate on pool[subtree] and update it
	/// </summary>
	/// <param name="a_i"> index in pool[N] of subtree root to be modified </param>
	void lRotate(uint32_t& a_i) {
		uint32_t b_i = pool[a_i].rSubtree;
		pool[a_i].rSubtree = pool[b_i].lSubtree;
		pool[b_i].lSubtree = a_i;
		pool[a_i].rHeight = pool[b_i].lHeight;
		pool[b_i].lHeight = pool[a_i].lHeight + 1;
		a_i = b_i;
	}
	/// <summary>
	/// right rotate on pool[subtree] and update it
	/// </summary>
	/// <param name="a_i"> index in pool[N] of subtree root to be modified </param>
	void rRotate(uint32_t& a_i) {
		uint32_t b_i = pool[a_i].lSubtree;
		pool[a_i].lSubtree = pool[b_i].rSubtree;
		pool[b_i].rSubtree = a_i;
		pool[a_i].lHeight = pool[b_i].rHeight++;
		pool[b_i].rHeight = pool[a_i].rHeight + 1;
		a_i = b_i;
	}
	/// <summary>
	/// push a target value into the subtree rooted at p[root]
	/// </summary>
	/// <param name="root"> p[root] is the root of specified subtree </param>
	/// <param name="rotated"> indicates whether or not any more height update </param>
	/// <param name="target"> value to be pushed </param>
	void push(uint32_t& p_root, const T& p_vaule) {
		if (!p_root) {
			pool[p_root = pool_ptr++].value = p_vaule;
			return;
		}
		node& r = pool[p_root];
		if (cmp(p_vaule, r.value)) {    // push to left subtree
			push(r.lSubtree, p_vaule);
			if (hUpdate == false)  return;
			if (r.lHeight < r.rHeight) {
				r.lHeight++;
				hUpdate = false;  // doesn't affect parent height
			}
			else if (r.lHeight == r.rHeight) {
				r.lHeight++;
				hUpdate = true;
			}
			else {			   // left heavy
				if (pool[r.lSubtree].rHeight > pool[r.lSubtree].lHeight)
					avl::lRotate(r.lSubtree);
				avl::rRotate(p_root);
				hUpdate = false;  // no height contribution after once rotation
			}
		}
		else {                         // push to right subtree
			push(r.rSubtree, p_vaule);
			if (hUpdate == false)  return;
			if (r.rHeight < r.lHeight) {
				r.rHeight++;
				hUpdate = false;  // doesn't affect parent height
			}
			else if (r.rHeight == r.lHeight) {
				r.rHeight++;
				hUpdate = true;
			}
			else {             // right heavy
				if (pool[r.rSubtree].lHeight > pool[r.rSubtree].rHeight)
					avl::rRotate(r.rSubtree);
				avl::lRotate(p_root);
				hUpdate = false;  // no height contribution after once rotation
			}
		}
	}
#ifdef TEST
	uint32_t heightCheck(uint32_t p_root) {
		int max = 0;
		if (pool[p_root].lSubtree) {
			max = heightCheck(pool[p_root].lSubtree) + 1;
			assert(pool[p_root].lHeight == max);
		}
		if (pool[p_root].rSubtree) {
			int rh = heightCheck(pool[p_root].rSubtree) + 1;
			max = rh > max ? rh : max;
			assert(pool[p_root].rHeight == rh);
		}
		return max;
	}

	uint32_t sizeCheck(uint32_t p_root) {
		int size = 0;
		if (pool[p_root].lSubtree) {
			size = sizeCheck(pool[p_root].lSubtree) + 1;
			assert(pool[p_root].lSize == size);
		}
		if (pool[p_root].rSubtree) {
			int rs = sizeCheck(pool[p_root].rSubtree) + 1;
			size += rs;
			assert(pool[p_root].rSize == rs);
		}
		return size;
	}
#endif
public:
	avl(bool(*cmp)(const T& a, const T& b))
		: cmp(cmp), root(0), pool_ptr(1), hUpdate(true) {
		pool = new node[N + 1];
		for (size_t i = 0; i <= N; i++)
			pool[i] = node();
	}

#ifdef TEST
	~avl() {
		heightCheck(root);
		//sizeCheck(root);
		delete[] pool;
	}
#else
	~avl() {
		delete[] pool;
	}
#endif

	void Push(const T& p_value) {
		hUpdate = true;
		push(root, p_value);
	}
	
	void Pop(T& p_value) {
		
	}
	
	T& At(uint32_t p_index) const {
		
	}
	
	void operator<<(const T& p_value) {
		Push(p_value);
	}
	
	void operator>>(T& p_value) {
		Pop(p_value);
	}

	T& operator[](uint32_t p_index) {
		return At(p_index);
	}
};