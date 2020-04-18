#include "SKU.h"

    SKU::SKU()
    {
        remove("files/skulist/skulist_departmemt_backup.txt");
        remove("files/skulist/skulist_type_backup.txt");
        remove("files/skulist/skulist_brand_backup.txt");
        remove("files/skulist/skulist_feature_backup.txt");

        ifstream fin;
        fin.open("files/skulist/skulist_department.txt");
        if(!fin)
        {   cout<<"NEW LIST"<<endl;
            ofstream fout;
            fout.open("files/skulist/skulist_department.txt");
            fout.close();
            fin.open("files/skulist/skulist_department.txt");
        }
        while(!fin.eof())
        {
            string str,sku;
            fin>>sku>>str;
            skulist_department.insert(make_pair(sku,str));
        }
        fin.close();
        rename("files/skulist/skulist_department.txt","files/skulist/skulist_department_backup.txt");

//*************************************************************************************

        fin.open("files/skulist/skulist_brand.txt");
        if(!fin)
        {   cout<<"NEW LIST"<<endl;
            ofstream fout;
            fout.open("files/skulist/skulist_brand.txt");
            fout.close();
            fin.open("files/skulist/skulist_brand.txt");
        }
        while(!fin.eof())
        {
            string str,sku;
            fin>>sku>>str;
            skulist_brand.insert(make_pair(sku,str));
        }

        fin.close();
        rename("files/skulist/skulist_brand.txt","files/skulist/skulist_brand_backup.txt");
//*************************************************************************************

        fin.open("files/skulist/skulist_type.txt");
        if(!fin)
        {   cout<<"NEW LIST"<<endl;
            ofstream fout;
            fout.open("files/skulist/skulist_type.txt");
            fout.close();
            fin.open("files/skulist/skulist_type.txt");
        }
        while(!fin.eof())
        {
            string str,sku;
            fin>>sku>>str;
            skulist_type.insert(make_pair(sku,str));
        }
        fin.close();
        rename("files/skulist/skulist_type.txt","files/skulist/skulist_type_backup.txt");
//*************************************************************************************

        fin.open("files/skulist/skulist_feature.txt");
        if(!fin)
        {   cout<<"NEW LIST"<<endl;
            ofstream fout;
            fout.open("files/skulist/skulist_feature.txt");
            fout.close();
            fin.open("files/skulist/skulist_feature.txt");
        }
        while(!fin.eof())
        {
            string str,sku;
            fin>>sku>>str;
            skulist_feature.insert(make_pair(sku,str));
        }
        fin.close();

        rename("files/skulist/skulist_feature.txt","files/skulist/skulist_feature_backup.txt");
//*************************************************************************************


    }
    SKU::~SKU()
    {
        ofstream fout;
        fout.open("files/skulist/skulist_department.txt");
        for(auto it=skulist_department.begin();it!=skulist_department.end();it++)
            fout<<it->first<<endl<<it->second<<endl;
        fout.close();

        fout.open("files/skulist/skulist_brand.txt");
        for(auto it=skulist_brand.begin();it!=skulist_brand.end();it++)
            fout<<it->first<<endl<<it->second<<endl;
        fout.close();

        fout.open("files/skulist/skulist_type.txt");
        for(auto it=skulist_type.begin();it!=skulist_type.end();it++)
            fout<<it->first<<endl<<it->second<<endl;
        fout.close();

        fout.open("files/skulist/skulist_feature.txt");
        for(auto it=skulist_feature.begin();it!=skulist_feature.end();it++)
            fout<<it->first<<endl<<it->second<<endl;
        fout.close();

    }

    string SKU:: str(string str,int type)
    {
        int n=4;
        string temp=str;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        string sku="";                  // n=4 for department type and brand, 3 features
        if(str.length()>n)
            sku.append(temp,0,n);
        else
        {   int len=0;
            while(str.length()<n-len)
                sku.append("0",0,1),len++;
            sku.append(temp,0,temp.length());
        }
        map<string,string> ::iterator it;
        int x=1;
        switch(type)
        {
            case 1: {
                        do
                        {
                            it=skulist_department.find(sku);
                            if(it==skulist_department.end())
                                skulist_department.insert(make_pair(sku,str));
                            else if (!strcmp(it->second,str))
                            {
                                break;
                            }
                            else
                            {
                                for( int i=1;i<=x;i=i*10)
                                    sku.pop_back();
                                sku.append(to_string(x++));



                            }

                        }while(it!=skulist_department.end());


                    }
                break;
            case 2: {
                        do
                        {
                            it=skulist_type.find(sku);
                            if(it==skulist_type.end())
                                skulist_type.insert(make_pair(sku,str));
                            else if (strcmp(it->second,str)==0)
                            {
                                break;
                            }
                            else
                            {
                                for( int i=1;i<=x;i=i*10)
                                    sku.pop_back();
                                sku.append(to_string(x++));



                            }

                        }while(it!=skulist_type.end());

                    }
                break;
            case 3: {
                            do
                        {
                            it=skulist_brand.find(sku);
                            if(it==skulist_brand.end())
                                skulist_brand.insert(make_pair(sku,str));
                            else if (strcmp(it->second,str)==0)
                            {int x=1;
                                break;
                            }
                            else
                            {
                                for( int i=1;i<=x;i=i*10)
                                    sku.pop_back();
                                sku.append(to_string(x++));



                            }

                        }while(it!=skulist_brand.end());


                    }
                break;
            case 4: {

                        do
                        {
                            it=skulist_feature.find(sku);
                            if(it==skulist_feature.end())
                                skulist_feature.insert(make_pair(sku,str));
                            else if (strcmp(it->second,str)==0)
                            {
                                break;
                            }
                            else
                            {
                                for( int i=1;i<=x;i=i*10)
                                    sku.pop_back();
                                sku.append(to_string(x++));



                            }

                        }while(it!=skulist_feature.end());

                      }
                break;
            default :cout<<"error?";
        }
        return sku;
    }

    void SKU::get_details(string str)
    {
        string sku="";

        sku.append(str,0,4);
        auto it=skulist_department.find(sku);
        if(it==skulist_department.end())
            cout<<"error?";
        else
            cout<<it->second<<endl;
        sku.clear();

        sku.append(str,4,4);

        it=skulist_type.find(sku);
        if(it==skulist_type.end())
            cout<<"error?";
        else
            cout<<it->second<<endl;
        sku.clear();

        sku.append(str,8,4);

        it=skulist_brand.find(sku);
        if(it==skulist_brand.end())
            cout<<"error?";
        else
            cout<<it->second<<endl;
        sku.clear();

        int len=str.length()-12;
        int x=12;
        while(len>1)
        {
            sku.append(str,x,4);


            it=skulist_feature.find(sku);
            if(it==skulist_feature.end())
                cout<<"error?\n";
            else
                cout<<it->second<<endl;
            sku.clear();
            x=x+4;
            len=len-4;
        }

    }

bool SKU::strcmp(string s1, string s2)
{

   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 0;
   return 1;
}
string SKU::get_department(string sku)
        {
            auto it=skulist_department.find(sku);
            if(it==skulist_department.end())
            {
                return "-1";
            }
            return it->second;
        }
string SKU::get_type(string sku)
        {
            auto it=skulist_type.find(sku);
            if(it==skulist_type.end())
            {
                return "-1";
            }
            return it->second;
        }






