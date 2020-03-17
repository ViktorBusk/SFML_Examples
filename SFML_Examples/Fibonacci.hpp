/*Copyright (c) 2010, Robin Message <Robin.Message@cl.cam.ac.uk>
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Univsersity of Cambridge nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY OF CAMBRIDGE OR ROBIN MESSAGE
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

template <class N> class FibonacciHeap;

template <class N> struct node {
private:
	node<N>* prev;
	node<N>* next;
	node<N>* child;
	node<N>* parent;
	N value;
	int degree;
	bool marked;
public:
	friend class FibonacciHeap<N>;
	node<N>* getPrev() {return prev;}
	node<N>* getNext() {return next;}
	node<N>* getChild() {return child;}
	node<N>* getParent() {return parent;}
	N getValue() {return value;}
	bool isMarked() {return marked;}

	bool hasChildren() {return child;}
	bool hasParent() {return parent;}
};

template <class N> class FibonacciHeap {
protected:
	node<N>* heap;
public:

	FibonacciHeap() {
		heap=_empty();
	}
	virtual ~FibonacciHeap() {
		if(heap) {
			_deleteAll(heap);
		}
	}
	node<N>* insert(N value) {
		node<N>* ret=_singleton(value);
		heap=_merge(heap,ret);
		return ret;
	}
	void merge(FibonacciHeap& other) {
		heap=_merge(heap,other.heap);
		other.heap=_empty();
	}

	bool isEmpty() {
		return heap==NULL;
	}

	N getMinimum() {
		return heap->value;
	}

	N removeMinimum() {
		node<N>* old=heap;
		heap=_removeMinimum(heap);
		N ret=old->value;
		delete old;
		return ret;
	}

	void decreaseKey(node<N>* n,N value) {
		heap=_decreaseKey(heap,n,value);
	}

	node<N>* find(N value) {
		return _find(heap,value);
	}
private:
	node<N>* _empty() {
		return NULL;
	}

	node<N>* _singleton(N value) {
		node<N>* n=new node<N>;
		n->value=value;
		n->prev=n->next=n;
		n->degree=0;
		n->marked=false;
		n->child=NULL;
		n->parent=NULL;
		return n;
	}

	node<N>* _merge(node<N>* a,node<N>* b) {
		if(a==NULL)return b;
		if(b==NULL)return a;
		if(a->value->get_f()>b->value->get_f()) {
			node<N>* temp=a;
			a=b;
			b=temp;
		}
		node<N>* an=a->next;
		node<N>* bp=b->prev;
		a->next=b;
		b->prev=a;
		an->prev=bp;
		bp->next=an;
		return a;
	}

	void _deleteAll(node<N>* n) {
		if(n!=NULL) {
			node<N>* c=n;
			do {
				node<N>* d=c;
				c=c->next;
				_deleteAll(d->child);
				delete d;
			} while(c!=n);
		}
	}
	
	void _addChild(node<N>* parent,node<N>* child) {
		child->prev=child->next=child;
		child->parent=parent;
		parent->degree++;
		parent->child=_merge(parent->child,child);
	}

	void _unMarkAndUnParentAll(node<N>* n) {
		if(n==NULL)return;
		node<N>* c=n;
		do {
			c->marked=false;
			c->parent=NULL;
			c=c->next;
		}while(c!=n);
	}

	node<N>* _removeMinimum(node<N>* n) {
		_unMarkAndUnParentAll(n->child);
		if(n->next==n) {
			n=n->child;
		} else {
			n->next->prev=n->prev;
			n->prev->next=n->next;
			n=_merge(n->next,n->child);
		}
		if(n==NULL)return n;
		node<N>* trees[64]={NULL};
		
		while(true) {
			if(trees[n->degree]!=NULL) {
				node<N>* t=trees[n->degree];
				if(t==n)break;
				trees[n->degree]=NULL;
				if(n->value->get_f() <t->value->get_f()) {
					t->prev->next=t->next;
					t->next->prev=t->prev;
					_addChild(n,t);
				} else {
					t->prev->next=t->next;
					t->next->prev=t->prev;
					if(n->next==n) {
						t->next=t->prev=t;
						_addChild(t,n);
						n=t;
					} else {
						n->prev->next=t;
						n->next->prev=t;
						t->next=n->next;
						t->prev=n->prev;
						_addChild(t,n);
						n=t;
					}
				}
				continue;
			} else {
				trees[n->degree]=n;
			}
			n=n->next;
		}
		node<N>* min=n;
		node<N>* start=n;
		do {
			if(n->value->get_f() <min->value->get_f())min=n;
			n=n->next;
		} while(n!=start);
		return min;
	}

	node<N>* _cut(node<N>* heap,node<N>* n) {
		if(n->next==n) {
			n->parent->child=NULL;
		} else {
			n->next->prev=n->prev;
			n->prev->next=n->next;
			n->parent->child=n->next;
		}
		n->next=n->prev=n;
		n->marked=false;
		return _merge(heap,n);
	}

	node<N>* _decreaseKey(node<N>* heap,node<N>* n,N value) {
		if(n->value->get_f() <value->get_f())return heap;
		n->value=value;
		if(n->parent) {
			if(n->value->get_f() <n->parent->value->get_f()) {
				heap=_cut(heap,n);
				node<N>* parent=n->parent;
				n->parent=NULL;
				while(parent!=NULL && parent->marked) {
					heap=_cut(heap,parent);
					n=parent;
					parent=n->parent;
					n->parent=NULL;
				}
				if(parent!=NULL && parent->parent!=NULL)parent->marked=true;
			}
		} else {
			if(n->value->get_f() < heap->value->get_f()) {
				heap = n;
			}
		}
		return heap;
	}

	node<N>* _find(node<N>* heap,N value) {
		node<N>* n=heap;
		if(n==NULL)return NULL;
		do {
			if(n->value->get_f() ==value->get_f())return n;
			node<N>* ret=_find(n->child,value);
			if(ret)return ret;
			n=n->next;
		}while(n!=heap);
		return NULL;
	}
};