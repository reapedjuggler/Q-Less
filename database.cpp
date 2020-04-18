#include "database.h"

void database :: customer_display()
        {
            for(auto it = stock.begin() ; it != stock.end() ; it++)
            {
                for(auto it1 = it->second.begin() ; it1 != it->second.end() ; it1++)
                {
                    cout << it1->first << endl ;
                }
            }

        }
void database ::  dealer_display()
        {
            for(auto it = stock.begin() ; it != stock.end() ; it++)
            {
                for(auto it1 = it->second.begin() ; it1 != it->second.end() ; it1++)
                {
                    cout << it1->first<<"     "<< it1->second.size() << endl ;
                }
            }

        }

void database ::  add_stock()
        {
            string dep,type,feature,brand;
            float price, n_feature=0;
            cout<<"Enter Department :";
            cin>>dep;
            cout<<endl;
            do
            {
                if( strcmp(dep,"-1")!=0 )
                {   string serial="";
                    cout<<"Enter Type : ";
                    cin>>type;
                    cout<<endl;
                    cout<<"Enter Brand : ";
                    cin>>brand;
                    cout<<endl;
                    cout<<"Enter Price : ";
                    cin>>price;
                    cout<<endl;
                    cout<<"Enter Number of Features :";
                    cin>>n_feature;
                    while(isdigit(n_feature))
                     {
                      cout<<"please enter a numeric value";
                      cin>>n_feature;
                     }
                    cout<<endl;
                    serial.append(skulist.str(dep,1));
                    serial.append(skulist.str(type,2));
                    serial.append(skulist.str(brand,3));
                    while(n_feature--)
                    {
                        cout<<"Enter Feature :",
                        cin>>feature,
                        cout<<endl,
                        serial.append(skulist.str(feature,4));

                    }
                    transform(dep.begin(), dep.end(), dep.begin(), ::tolower);
                    auto it=stock.find(dep);
                    if(it==stock.end())
                    {
                        map < string , map< string , float > >temp;
                        map< string , float > tempmap;
                        serial.append("00001");
                        tempmap.insert(make_pair(serial,price));
                        temp.insert(make_pair(type,tempmap));
                        stock.insert(make_pair(dep,temp));


                    }
                    else
                    {
                        auto it1=it->second.find(type);
                        if(it1==it->second.end())
                        {
                            serial.append("00001");
                            map< string , float > tempmap;
                            tempmap.insert(make_pair(serial,price));
                            it->second.insert(make_pair(type,tempmap));

                        }
                        else
                            {
                                int tempsize=it1->second.size(),check=10000;
                                while(tempsize<check)
                                    serial.append("0"),check=check/10;
                                serial.append(to_string(tempsize));
                                it1->second.insert(make_pair(serial,price));
                            }
                    }
                    cout<<"\nStock Added";
                }
                cout<<"\nEnter Department(-1 to Exit) :";
                cin>>dep;
                cout<<endl;
        }while(strcmp(dep,"-1")!=0);



        }
string database :: departmentis(string type)
{
    for(auto it=stock.begin();it!=stock.end();it++)
    {
        if(it->second.find(type)!=it->second.end())
            return it->first;
    }
    return "-1";
}


database ::  database()
        {


            remove("files/stock_backup.txt");
            ifstream fin;
            fin.open("files/stock.txt");
            if(!fin)
            {
                cout<<"NEW DATABASE";
                ofstream fout;
                fout.open("files/stock.txt");
                fout.close();
            }
            else
            {

                string dep;
                do
                {   dep.clear();
                    fin>>dep;
                    map < string , map< string , float > > temp;
                    if(!fin.eof() && strcmp(dep,"-3")!=0)
                    {   string type ;
                        do
                        {

                            map< string , float > tempmap;
                            fin >> type ;
                            if( strcmp(type,"-2")!=0 )
                            {   string serial ;
                                float price;
                                do
                                {
                                    serial.clear();
                                    fin >> serial >>price;
                                    if( strcmp(serial,"-1") !=0 )
                                        tempmap.insert(make_pair(serial,price));

                                } while (   strcmp(serial,"-1") !=0  );

                                temp.insert(make_pair(type,tempmap));

                            }

                        }while( strcmp(type,"-2")!=0 );
                        stock.insert(make_pair(dep,temp));

                    }

                } while(!fin.eof() && strcmp(dep,"-3")!=0);

            }
            fin.close();
            rename("files/stock.txt","files/stock_backup.txt");


        }

database ::  ~database()
        {
            ofstream fout;

            fout.open("files/stock.txt");
            if(!fout)
                cout<<"ERROR"<<endl;
            else
            {
                for(auto it = stock.begin() ; it != stock.end() ; it++)
                {
                    fout<<it->first<<endl;

                    for(auto it1 = it->second.begin() ; it1 != it->second.end() ; it1++)
                    {
                        fout << it1->first << endl ;

                        for(auto it2 = it1->second.begin() ; it2 != it1->second.end() ; it2++)
                        {
                            fout << it2->first << endl << it2->second <<endl;;
                        }
                        fout<<"-1"<<endl<<"-1"<<endl;
                    }
                    fout<<"-2"<<endl;
                }
                fout<<"-3"<<endl;
            }
            fout.close();

        }
void database ::  billing()
        {
            float totalbill=0;
            string serial;
            cout<<"Serial(-1 for Bill):";
            cin>>serial;
            cout<<endl;
            while(strcmp(serial,"-1")!=0)
            {
                string department,type,sku="",sku1="";
                sku.append(serial,0,4);
                sku1.append(serial,4,4);
                department=skulist.get_department(sku);
                type=skulist.get_type(sku1);

                if(strcmp(department,"-1")==0||strcmp(type,"-1")==0)
                    {
                        cout<<"#re-enter serial(-1 for Bill)\n";
                        cin>>serial;
                        continue;

                    }
                else
                {
                    auto it=stock.find(department);
                    auto it1=it->second.find(type);
                    auto it2=it1->second.find(serial);
                    if(it2==it1->second.end())
                    {
                        cout<<"$re-enter serial(-1 for Bill)\n";
                        cin>>serial;
                        continue;

                    }

                    totalbill+=it2->second;
                    it1->second.erase(it2);
                    cout<<"Serial (-1 for Bill):";
                    cin>>serial;
                    cout<<endl;

                }
            }
            cout<<"BILL:"<<totalbill<<endl;

        }
bool database :: strcmp(string s1, string s2)
{

   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return 0;
   return 1;
}

