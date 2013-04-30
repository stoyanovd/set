#define BOOST_TEST_MODULE set_testing
#define BOOST_TEST_MAIN

#include <boost\test\unit_test.hpp>
#include <stdio.h>

struct node
{
    node* left;
    node* right;
    node* anc;
    int value;

    node()
  {
		this -> value = 0;
		this -> left = NULL;
		this -> right = NULL;
		this -> anc = NULL;
	}

	~node(){}

    node* pnode()
    {
        node();

    }
	node(node* _left, node* _right, node* _anc, int _value)
	{
		this -> value = _value;
		this -> left = _left;
		this -> right = _right;
		this -> anc = _anc;
	}

	node(node* _node)
	{
		this -> value = _node -> value;
		this -> left = _node -> left;
		this -> right = _node -> right;
		this -> anc = _node -> anc;
	}

	node(int _value)
	{
		this -> value = _value;
		this -> left = NULL;
		this -> right = NULL;
		this -> anc = NULL;
	}

	void operator=(node* const& _node)
	{
		this -> value = _node -> value;
		this -> left = _node -> left;
		this -> right = _node -> right;
		this -> anc = _node -> anc;
	}

	bool operator==(node const& _node)
	{
		return (_node.left == left && _node.right == right && _node.anc == anc && _node.value == value);
	}

	bool operator!=(node const& _node)
	{
		return !(_node.left == left && _node.right == right && _node.anc == anc && _node.value == value);
	}

};

struct iterator
{
    node* cur_node;

    iterator()
	{
		cur_node = NULL;
	}

	~iterator(){}

	iterator(node* _node)
	{
		cur_node = _node;
	}

	int operator*() const
	{
		if(cur_node == NULL)
			return 0;
		return cur_node -> value;
	}

	iterator& operator++()
	{
		if(this -> cur_node == NULL)
			return *this;
		if(this -> cur_node -> right != NULL)
		{
		    this -> cur_node = this -> cur_node -> right;
		    while(this -> cur_node -> left != NULL)
                this -> cur_node = this -> cur_node -> left;
            return *this;
		}
		while(this -> cur_node -> anc != NULL && this -> cur_node -> anc -> right == this -> cur_node)
		    this -> cur_node = this -> cur_node -> anc;
		if(this -> cur_node -> anc == NULL)
			this -> cur_node = NULL;
		else
            this -> cur_node = this -> cur_node -> anc;
		return *this;
	}

	iterator operator++(int)
	{
		if(this -> cur_node == NULL)
			return *this;
		if(this -> cur_node -> right != NULL)
		{
		    this -> cur_node = this -> cur_node -> right;
		    while(this -> cur_node -> left != NULL)
                this -> cur_node = this -> cur_node -> left;
            return *this;
		}
		while(this -> cur_node -> anc != NULL && this -> cur_node -> anc -> right == this -> cur_node)
		    this -> cur_node = this -> cur_node -> anc;
		if(this -> cur_node -> anc == NULL)
			this -> cur_node = NULL;
		else
            this -> cur_node = this -> cur_node -> anc;
		return *this;
	}

	iterator& operator--()
	{
		if(this -> cur_node == NULL)
			return *this;
		if(this -> cur_node -> left != NULL)
		{
		    this -> cur_node = this -> cur_node -> left;
		    while(this -> cur_node -> right != NULL)
                this -> cur_node = this -> cur_node -> right;
            return *this;
		}
		while(this -> cur_node -> anc != NULL && this -> cur_node -> anc -> left == this -> cur_node)
		    this -> cur_node = this -> cur_node -> anc;
		if(this -> cur_node -> anc == NULL)
		    this -> cur_node = NULL;
		else
            this -> cur_node = this -> cur_node -> anc;
		return *this;
	}

	iterator operator--(int)
	{
		if(this -> cur_node == NULL)
			return *this;
		if(this -> cur_node -> left != NULL)
		{
		    this -> cur_node = this -> cur_node -> left;
		    while(this -> cur_node -> right != NULL)
                this -> cur_node = this -> cur_node -> right;
            return *this;
		}
		while(this -> cur_node -> anc != NULL && this -> cur_node -> anc -> left == this -> cur_node)
		    this -> cur_node = this -> cur_node -> anc;
		if(this -> cur_node -> anc == NULL)
		    this -> cur_node = NULL;
		else
            this -> cur_node = this -> cur_node -> anc;
		return *this;
	}

	bool operator==(iterator const& _it)
	{
		return (this -> cur_node == _it.cur_node);
	}

	bool operator!=(iterator const& _it)
	{
		return (this -> cur_node != _it.cur_node);
	}

};

struct set
{
	node* root;
	int size;

    set()
	{
		root = NULL;
		size = 0;
	}

	~set()
	{
		node* t = root;
		node* p = NULL;

		while(t != NULL)
		{
			if(t -> left != NULL)
				t = t -> left;
			else if(t -> right != NULL)
				t = t -> right;
			else if(t != root && t != NULL)
			{
				p = t -> anc;
				if(p == NULL)
					break;
				if(p -> left == t)
					p -> left = NULL;
				else if(p -> right == t)
					p -> right = NULL;
				delete t;
				t = p;
			}
			else if(t == root)
				break;
		}
		delete root;
	}

    set(set const& _set)
	{
		size = _set.size;
		root = new node();
		node* t = _set.root;
		node* p = root;
		node* x = NULL;

		while(t != NULL)
		{
			if(t -> left != NULL && p -> left == NULL)
			{
				x = new node(t -> left -> value);
				x -> anc = p;
				p -> left = x;
				p = x;
				t = t -> left;
			}
			else if(t -> right != NULL && p -> right == NULL)
			{
				x = new node(t -> right -> value);
				x -> anc = p;
				p -> right = x;
				p = x;
				t = t -> right;
			}
			else if(t == _set.root)
				break;
			else
			{
				p = p -> anc;
				t = t -> anc;
			}
		}
	}

    set& operator =(set const& _set)
	{
		return set(_set);
	}

    void insert(int x)
	{
		if(size == 0)
		{
			root = new node(x);
			size++;
			return;
		}
		node* t = root;
		node* p = new node(x);
		while(t != NULL)
		{
			if(x <= t -> value)
			{
				if(t -> left != NULL)
				{
					t = t -> left;
					continue;
				}
				p -> anc = t;
				t -> left = p;
				break;
			}
			if(t -> right != NULL)
			{
				t = t -> right;
				continue;
			}
			p -> anc = t;
			t -> right = p;
			break;			
		}
		size++;
		return;
	}

    iterator find(int x)
	{
		node* t = root;
		node* p = NULL;
		iterator ans;
		while(t != NULL)
		{
			if(x == t -> value)
			{
				ans.cur_node = t;
				return ans;
			}
			if(x < t -> value)
			{
				if(t -> left != NULL)
				{
					t = t -> left;
					continue;
				}
				ans.cur_node = t;
				return ans;
			}
			if(t -> right != NULL)
			{
				t = t -> right;
				continue;
			}
			ans.cur_node = t;
			return ans;
		}
	}

    void erase(iterator it)
	{
		if(size == 0)
			return;
		size--;
		iterator p_it = it;
		if(p_it.cur_node == NULL)
			return;
		if(p_it.cur_node -> left == NULL && p_it.cur_node -> right == NULL)
		{
			if(p_it.cur_node -> anc != NULL)
			{
				if(p_it.cur_node -> anc -> left == p_it.cur_node)
					p_it.cur_node -> anc -> left = NULL;
				else if(p_it.cur_node -> anc -> right == p_it.cur_node)
					p_it.cur_node -> anc -> right = NULL;
			}
			else
			{
				root = NULL;
				root -> anc = NULL;
			}
			delete p_it.cur_node;
			return;
		}
		if(p_it.cur_node -> left == NULL)
		{
			if(p_it.cur_node -> anc != NULL)
			{
				if(p_it.cur_node -> anc -> left == p_it.cur_node)
					p_it.cur_node -> anc -> left = p_it.cur_node -> right;
				else if(p_it.cur_node -> anc -> right == p_it.cur_node)
					p_it.cur_node -> anc -> right = p_it.cur_node -> right;
				p_it.cur_node -> right -> anc = p_it.cur_node -> anc;
			}
			else
			{
				root = p_it.cur_node -> right;
				root -> anc = NULL;
			}
			delete p_it.cur_node;
			return;
		}
		if(p_it.cur_node -> right == NULL)
		{
			if(p_it.cur_node -> anc != NULL)
			{
				if(p_it.cur_node -> anc -> left == p_it.cur_node)
					p_it.cur_node -> anc -> left = p_it.cur_node -> left;
				else if(p_it.cur_node -> anc -> right == p_it.cur_node)
					p_it.cur_node -> anc -> right = p_it.cur_node -> left;
				p_it.cur_node -> left -> anc = p_it.cur_node -> anc;
			}
			else
			{
				root = p_it.cur_node -> left;
				root -> anc = NULL;
			}
			delete p_it.cur_node;
			return;
		}	
		p_it--;
		if(p_it.cur_node != NULL)
		{
			it.cur_node -> value = p_it.cur_node -> value;
			if(p_it.cur_node -> right != NULL)
			{
				if(p_it.cur_node -> anc != NULL)
				{
					if(p_it.cur_node -> anc -> left == p_it.cur_node)
						p_it.cur_node -> anc -> left = p_it.cur_node -> right;
					else if(p_it.cur_node -> anc -> right == p_it.cur_node)
						p_it.cur_node -> anc -> right = p_it.cur_node -> right;
					p_it.cur_node -> right -> anc = p_it.cur_node -> anc;
				}
				else
				{
					root = p_it.cur_node -> right;
					root -> anc = NULL;
				}
			}
			else if(p_it.cur_node -> left != NULL)
			{
				if(p_it.cur_node -> anc != NULL)
				{
					if(p_it.cur_node -> anc -> left == p_it.cur_node)
						p_it.cur_node -> anc -> left = p_it.cur_node -> left;
					else if(p_it.cur_node -> anc -> right == p_it.cur_node)
						p_it.cur_node -> anc -> right = p_it.cur_node -> left;
					p_it.cur_node -> left -> anc = p_it.cur_node -> anc;
				}
				else
				{
					root = p_it.cur_node -> left;
					root -> anc = NULL;
				}
			}
			else
			{
				if(p_it.cur_node -> anc != NULL)
				{
					if(p_it.cur_node -> anc -> left == p_it.cur_node)
						p_it.cur_node -> anc -> left = NULL;
					else if(p_it.cur_node -> anc -> right == p_it.cur_node)
						p_it.cur_node -> anc -> right = NULL;
				}
				else
				{
					root = NULL;
					root -> anc = NULL;
				}
			}
			delete p_it.cur_node;
			return;
		}
	}

    iterator begin()
	{
		iterator it;
		it.cur_node = root;
		iterator p = it;
		p--;
		while(p.cur_node != NULL)
		{
			p--;
			it--;
		}
		return it;
	}

    iterator end()
	{
		iterator it;
		it.cur_node = root;
		iterator p = it;
		p++;
		while(p.cur_node != NULL)
		{
			p++;
			it++;
		}
		return it;
	}
};

BOOST_AUTO_TEST_CASE(test_true)
{
	BOOST_CHECK_EQUAL(1, 1);
}

BOOST_AUTO_TEST_CASE(test_set_insert)
{
	set _set;
	_set.insert(1);
	set _set1;
	_set1.insert(1);
	BOOST_CHECK_EQUAL(*(_set.begin()), 1);
	BOOST_CHECK_EQUAL(*(_set1.begin()), 1);
}

BOOST_AUTO_TEST_CASE(test_set_multiinsert)
{
	set _set;
	for(int i = 0; i < 5; i++)
		_set.insert(i);
	iterator it = _set.begin();
	for(int i = 0; i < 5; i++)	
	{
		BOOST_CHECK_EQUAL(*it, i);
		it++;
	}
}

BOOST_AUTO_TEST_CASE(test_set_multiinsert_find)
{
	set _set;
	for(int i = 0; i < 5; i++)
		_set.insert(i);
	iterator it = _set.begin();
	for(int i = 0; i < 5; i++)	
	{
		BOOST_CHECK_EQUAL(*it, *_set.find(i));
		it++;
	}
}

BOOST_AUTO_TEST_CASE(test_set_find_erase)
{
	set _set;
	_set.insert(1);
	_set.insert(2);
	_set.erase(_set.find(1));
	set _set1;
	_set1.insert(1);
	_set1.insert(2);
	_set1.erase(_set1.find(1));
	BOOST_CHECK_EQUAL(*_set.begin(), 2);
	BOOST_CHECK_EQUAL(*_set1.begin(), 2);
}

BOOST_AUTO_TEST_CASE(test_iterator_inc_dec)
{
	set _set;
	int a[5], b[5], c[5], i;
	iterator it;

	for (i = 0; i < 5; i++)
	{
		_set.insert(i);
		c[i] = i;
	}
	for (it =_set.begin(), i = 0; it != _set.end(); ++it, i++)
		a[i] = it.cur_node -> value;
	a[i] = it.cur_node -> value;

	for (it =_set.end(), i = 4; it != _set.begin(); it--, i--)
		b[i] = it.cur_node -> value;
	b[i] = it.cur_node -> value;

	for (int i = 0; i < 5; i++)
	{
		BOOST_CHECK_EQUAL(a[i], c[i]);
		BOOST_CHECK_EQUAL(c[i], b[i]);
	}
}

BOOST_AUTO_TEST_CASE(test_multi_erase)
{
	set _set;
	int i;
	iterator it;
	for(i = 0; i < 6; i++)
		_set.insert(i);
	it = _set.begin();
	it = _set.begin();
	for(;; it++)	
		if(it == _set.end())
			break;
	for(i = 1; i < 6; i += 2)
	{
		_set.erase(_set.find(i));
		_set.end();
	}
	it = _set.begin();
	for(;; it++)	
		if(it == _set.end())
			break;
	i = 0;
	for (it = _set.begin(); i < 6; it++, i += 2)
		BOOST_CHECK_EQUAL(i, *it);
}

BOOST_AUTO_TEST_CASE(test_set_copy)
{
	set _set;
	_set.insert(1);
	_set.insert(2);
	set _set1 = _set;
	_set.erase(_set.begin());
	_set1.erase(_set1.begin());
	BOOST_CHECK_EQUAL(*_set.begin(), 2);
	BOOST_CHECK_EQUAL(*_set.begin(), 2);
}
