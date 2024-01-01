#ifndef __TEST_ALL_DIMENSION_SEQUENCE_CPP__
#define __TEST_ALL_DIMENSION_SEQUENCE_CPP__

#include "lv2_test.hpp2"

namespace cliz
{
    void generate_all_dimension_sequence(vector<vector<int>> &all_sequence,int i,int dimension_num)
    {
        if (i==0)
        {
            all_sequence.push_back(vector<int>());
            for (int did=0;did<dimension_num;did++)
                all_sequence[0].push_back(did);
        }
        if (i==dimension_num-1)
            return;
        int base_id=all_sequence.size()-1;
        generate_all_dimension_sequence(all_sequence,i+1,dimension_num);
        for (int j=i+1;j<dimension_num;j++)
        {
            all_sequence.push_back(vector<int>());
            for (int k=0;k<dimension_num;k++)
            {
                if ((k<i) || (k>j))
                    all_sequence.rbegin()->push_back(all_sequence[base_id][k]);
                if (k==i)
                    all_sequence.rbegin()->push_back(all_sequence[base_id][j]);
                if ((i<k) && (k<=j))
                    all_sequence.rbegin()->push_back(all_sequence[base_id][k-1]);
            }
            generate_all_dimension_sequence(all_sequence,i+1,dimension_num);
        }
    }

    template<typename T>
    void task_c<T>::test_all_dimension_sequence()
    {
        test_all_dimension_fission();
        vector<vector<int>> all_sequence;
        generate_all_dimension_sequence(all_sequence,0,dimension_num);
        hyper_iterator_c *it1_backup=NULL;
        copy_iterator(it1_backup,it1);
        new_data(it1->dim_seq,it1->n);
        for (auto i=next(all_sequence.begin());i!=all_sequence.end();i++)
        {
            for (auto j=i->begin();j!=i->end();j++)
            {
                it1->dim_seq[j-i->begin()]=*j;
                it1->mx[j-i->begin()]=it1_backup->mx[*j];
            }
            for (int did=it1->n-1;did>=0;did--)
                if (did==it1->n-1)
                    it1->weight[did]=1;
                else
                    it1->weight[did]=it1->weight[did+1]*it1->mx[did+1];
            test_all_dimension_fission();
        }
        copy_iterator(it1,it1_backup);
        delete_data(it1_backup);
    }
}

#endif