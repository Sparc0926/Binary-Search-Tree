//#include <stdlib.h>
//#include "2-3 Tree.h"
//
//
//
//static void insert(_2_3T* root, int tar)
//{
//	if (!root) {
//		U.val = tar, U.l = U.r = 0;
//		return;
//	}
//	// path finding
//	if (tar < root->lval)  insert(root->l, tar);
//	else if (tar < root->rval)  insert(root->m, tar);
//	else  insert(root->r, tar);
//	if (U.val == 0x7fffffff)  return;  // A quick wrap-up if no more 4-nodes
//	// the current node has only lval
//	if (root->rval == 0x7fffffff) {
//		if (U.val < root->lval) {
//			root->rval = root->lval, root->lval = U.val;
//			root->r = root->m, root->l = U.l, root->m = U.r;
//		}
//		else {
//			root->rval = U.val;
//			root->m = U.l, root->r = U.r;
//		}
//		U.val = 0x7fffffff;
//	}
//	// it has both lval and rval
//	else if (U.val < root->lval) {
//		int val = root->lval;
//
//		_2_3T* r = (_2_3T*)malloc(sizeof(_2_3T));
//		r->lval = root->rval, r->rval = 0x7fffffff;
//		r->l = root->m, r->m = root->r, r->r = 0;
//
//		root->lval = U.val, root->rval = 0x7fffffff;
//		root->l = U.l, root->m = U.r, root->r = 0;
//
//		U.val = val, U.l = root, U.r = r;
//	}
//	else if (U.val < root->rval) {
//		_2_3T* r = (_2_3T*)malloc(sizeof(_2_3T));
//		r->lval = root->rval, r->rval = 0x7fffffff;
//		r->l = U.r, r->m = root->r, r->r = 0;
//
//		root->rval = 0x7fffffff;
//		root->m = U.l, root->r = 0;
//
//		U.l = root, U.r = r;
//	}
//	else {
//		int val = root->rval;
//
//		_2_3T* r = (_2_3T*)malloc(sizeof(_2_3T));
//		r->lval = U.val, r->rval = 0x7fffffff;
//		r->l = U.l, r->m = U.r, r->r = 0;
//
//		root->rval = 0x7fffffff;
//		root->r = 0;
//
//		U.val = val, U.l = root, U.r = r;
//	}
//}
//
//
//
//_2_3T* Insert(_2_3T* root, int tar)
//{
//	insert(root, tar);
//	if (U.val == 0x7fffffff)  return root;
//	_2_3T* _r = (_2_3T*)malloc(sizeof(_2_3T));
//	_r->lval = U.val, _r->rval = 0x7fffffff;
//	_r->l = U.l, _r->m = U.r, _r->r = 0;
//	return _r;
//}
//
//
//
//void Free(_2_3T* root)
//{
//	if (!root->l)  Free(root->l);
//	if (!root->m)  Free(root->m);
//	if (!root->r)  Free(root->r);
//	free(root);
//	root = 0;
//}