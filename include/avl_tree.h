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
			: l_height(0), r_height(0), l_subtree(0), r_subtree(0), l_size(0), r_size(0) {
		}
		~node() {
		}
		T value;
		uint32_t l_height, r_height;
		uint32_t l_subtree, r_subtree;
		uint32_t l_size, r_size;
	};
	bool(*cmp)(const T& a, const T& b);
	uint32_t root, pool_ptr;
	node pool[N + 1];
	bool h_update;
	/// <summary>
	/// left rotate on pool[subtree] and update it
	/// </summary>
	/// <param name="a_i"> index in pool[N] of subtree root to be modified </param>
	void l_rotate(uint32_t& a_i) {
		uint32_t b_i = pool[a_i].r_subtree;
		pool[a_i].r_subtree = pool[b_i].l_subtree;
		pool[b_i].l_subtree = a_i;
		pool[a_i].r_height = pool[b_i].l_height;
		pool[b_i].l_height = pool[a_i].l_height + 1;
		a_i = b_i;
	}
	/// <summary>
	/// right rotate on pool[subtree] and update it
	/// </summary>
	/// <param name="a_i"> index in pool[N] of subtree root to be modified </param>
	void r_rotate(uint32_t& a_i) {
		uint32_t b_i = pool[a_i].l_subtree;
		pool[a_i].l_subtree = pool[b_i].r_subtree;
		pool[b_i].r_subtree = a_i;
		pool[a_i].l_height = pool[b_i].r_height++;
		pool[b_i].r_height = pool[a_i].r_height + 1;
		a_i = b_i;
	}
	/// <summary>
	/// push a target value into the subtree rooted at p[root]
	/// </summary>
	/// <param name="root"> p[root] is the root of specified subtree </param>
	/// <param name="rotated"> indicates whether or not any more height update </param>
	/// <param name="target"> value to be pushed </param>
	void _push(uint32_t& p_root, const T& p_vaule) {
		if (!p_root) {
			pool[p_root = pool_ptr++].value = p_vaule;
			return;
		}
		node& r = pool[p_root];
		if (cmp(p_vaule, r.value)) {    // push to left subtree
			_push(r.l_subtree, p_vaule);
			if (h_update == false)  return;
			if (r.l_height < r.r_height) {
				r.l_height++;
				h_update = false;  // doesn't affect parent height
			}
			else if (r.l_height == r.r_height) {
				r.l_height++;
				h_update = true;
			}
			else {			   // left heavy
				if (pool[r.l_subtree].r_height > pool[r.l_subtree].l_height)
					avl::l_rotate(r.l_subtree);
				avl::r_rotate(p_root);
				h_update = false;  // no height contribution after once rotation
			}
		}
		else {                         // push to right subtree
			_push(r.r_subtree, p_vaule);
			if (h_update == false)  return;
			if (r.r_height < r.l_height) {
				r.r_height++;
				h_update = false;  // doesn't affect parent height
			}
			else if (r.r_height == r.l_height) {
				r.r_height++;
				h_update = true;
			}
			else {             // right heavy
				if (pool[r.r_subtree].l_height > pool[r.r_subtree].r_height)
					avl::r_rotate(r.r_subtree);
				avl::l_rotate(p_root);
				h_update = false;  // no height contribution after once rotation
			}
		}
	}
#ifdef TEST
	uint32_t _height_check(uint32_t p_root) {
		int max = 0;
		if (pool[p_root].l_subtree) {
			max = _height_check(pool[p_root].l_subtree) + 1;
			assert(pool[p_root].l_height == max);
		}
		if (pool[p_root].r_subtree) {
			int rh = _height_check(pool[p_root].r_subtree) + 1;
			max = rh > max ? rh : max;
			assert(pool[p_root].r_height == rh);
		}
		return max;
	}

	uint32_t _size_check(uint32_t p_root) {
		int size = 0;
		if (pool[p_root].l_subtree) {
			size = _size_check(pool[p_root].l_subtree) + 1;
			assert(pool[p_root].l_size == size);
		}
		if (pool[p_root].r_subtree) {
			int rs = _size_check(pool[p_root].r_subtree) + 1;
			size += rs;
			assert(pool[p_root].r_size == rs);
		}
		return size;
	}
#endif
public:
	avl(bool(*cmp)(const T& a, const T& b))
		: cmp(cmp), root(0), pool_ptr(1), h_update(true) {
		for (size_t i = 0; i <= N; i++)
			pool[i] = node();
	}

#ifdef TEST
	~avl() {
		_height_check(root);
		//_size_check(root);
	}
#else
	~avl() {
	}
#endif

	void push(const T& p_value) {
		h_update = true;
		_push(root, p_value);
	}

	void operator<<(const T& p_value) {
		push(p_value);
	}

	void pop(T& p_value) {
		uint32_t rt = root;
		while (pool[rt].value != p_value) {
			if (cmp(p_value, pool[rt].value)) {
				rt = pool[rt].l_subtree;
			}
			else {
				rt = pool[rt].r_subtree;
			}
		}
	}

	void operator>>(T& p_value) {
		pop(p_value);
	}

	T& at(uint32_t index) const {

	}

	T& operator[](uint32_t index) {
		return at(index);
	}
};