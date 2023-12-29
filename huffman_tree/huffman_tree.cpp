#ifndef __HUFFMAN_TREE_CPP__
#define __HUFFMAN_TREE_CPP__

#include "huffman_tree.hpp2"

namespace cliz
{
	template<typename T>
	void huffman_tree_c<T>::generate_tree()
	{
		for (auto it=nodes.begin();it!=nodes.end();it++)
		{
			int i=it->first;
			nodes[i].self=i;
			nodes[i].father=i;
			nodes[i].lson=i;
			nodes[i].rson=i;
			nodes[i].lmost=i;
			nodes[i].rmost=i;
			unarranged_nodes.insert(&nodes[i]);
		}
		int next_node=32768;
		for (auto it=unarranged_nodes.begin();it!=unarranged_nodes.end();it++)
			printf("%d %d\n",(*it)->self,(*it)->count);
		while (unarranged_nodes.size()>1)
		{
			auto it1=unarranged_nodes.begin();
			auto it2=next(it1);
			auto s1=*it1;
			auto s2=*it2;
			nodes[next_node].count=s1->count+s2->count;
			nodes[next_node].self=next_node;
			nodes[next_node].father=next_node;
			nodes[next_node].lson=s1->self;
			nodes[next_node].rson=s2->self;
			nodes[next_node].lmost=s1->lmost;
			nodes[next_node].rmost=s2->rmost;
			nodes[s1->self].father=next_node;
			nodes[s2->self].father=next_node;
			unarranged_nodes.erase(it1);
			unarranged_nodes.erase(it2);
			unarranged_nodes.insert(&nodes[next_node]);
			next_node++;
		}
	}

	template<typename T>
	void huffman_tree_c<T>::traversal(int id,task_c<T> *task)
	{
		if (nodes[id].father==id)
		{
			nodes[id].code=0;
			nodes[id].length=0;
		}
		else
		{
			if (nodes[nodes[id].father].lson==id)
				nodes[id].code=nodes[nodes[id].father].code*2+1;
			else
				nodes[id].code=nodes[nodes[id].father].code*2;
			nodes[id].length=nodes[nodes[id].father].length+1;
		}
		if (nodes[id].lson!=id)
		{
			traversal(nodes[id].lson,task);
			traversal(nodes[id].rson,task);
			#ifdef JOB_TYPE_COMPRESS
				task->append_cache(nodes[id].lmost);
				task->append_cache(nodes[id].rmost);
			#endif
		}
	}

	//生成huffman编码
	template<typename T>
	void huffman_tree_c<T>::generate_code(task_c<T> *task)
	{
		if (nodes.size()>=2)
		{
			task->template align_cache<int>();
			task->append_cache((int)(nodes.size()-1));
			task->template align_cache<short>();
			auto root=*(unarranged_nodes.begin());
			traversal(root->self,task);
			unarranged_nodes.clear();
		}
		else
			if (nodes.size()==1)
			{
				task->template align_cache<int>();
				task->append_cache((int)1);
				task->template align_cache<short>();
				auto root=*(unarranged_nodes.begin());
				root->code=0;
				root->length=1;
				task->append_cache(root->self);
				unarranged_nodes.clear();
			}
			else
			{
				task->template align_cache<int>();
				task->append_cache((int)0);
			}
	}


	template<typename T>
	void huffman_tree_c<T>::rebuild(task_c<T> *task)
	{
		task->template align_cache<int>();
		int tree_cache_length=task->template read_cache<int>();
		if (tree_cache_length>=2)
		{
			for (int i=0;i<tree_cache_length/2;i++)
			{
				int nid=i+32768;
				nodes[nid].self=nid;
				nodes[nid].father=nid;
				nodes[nid].root=nid;
				task->read_cache(nodes[nid].lmost);
				task->read_cache(nodes[nid].rmost);
				int lmost=nodes[nid].lmost;
				int rmost=nodes[nid].rmost;
				if (nodes.find(lmost)==nodes.end())
				{
					nodes[lmost].self=lmost;
					nodes[lmost].father=nid;
					nodes[lmost].root=lmost;
					nodes[lmost].lson=lmost;
					nodes[lmost].rson=lmost;
					nodes[lmost].lmost=lmost;
					nodes[lmost].rmost=lmost;
				}
				nodes[nid].lson=nodes[lmost].root;
				nodes[lmost].root=nid;
				nodes[nodes[nid].lson].father=nid;
				if (nodes.find(rmost)==nodes.end())
				{
					nodes[rmost].self=rmost;
					nodes[rmost].father=nid;
					nodes[rmost].root=rmost;
					nodes[rmost].lson=rmost;
					nodes[rmost].rson=rmost;
					nodes[rmost].lmost=rmost;
					nodes[rmost].rmost=rmost;
				}
				nodes[nid].rson=nodes[rmost].root;
				nodes[rmost].root=nid;
				nodes[nodes[nid].rson].father=nid;
			}
		}
		else
			if (tree_cache_length==1)
			{
				task->template align_cache<short>();
				int nid=task->template read_cache<short>();
				nodes[nid].self=nid;
				nodes[nid].father=nid;
				nodes[nid].lson=nid;
				nodes[nid].rson=nid;
				nodes[nid].lmost=nid;
				nodes[nid].rmost=nid;
				nodes[nid].root=nid;
			}
	}
}

#endif