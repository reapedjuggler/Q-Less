#include<bits/stdc++.h>
using namespace std;
#ifndef SKU_H
#define SKU_H


class SKU
{
    public:
        SKU();
        ~SKU();
        string str(string str,int type);
        void get_details(string str);
        bool strcmp(string s1, string s2);
        string get_department(string sku);
        string get_type(string sku);
        int encode(string sku);




    protected:

    private:
      map<string,string> skulist_department,skulist_brand,skulist_type,skulist_feature;
};

#endif // SKU_H
