#include<SKU.h>
#ifndef DATABASE_H
#define DATABASE_H


class database
{
    public:
        database();
        ~database();
        void dealer_display();
        void customer_display();
        void add_stock();
        void billing();
        bool strcmp(string s1, string s2);

        string departmentis(string type);
    protected:

    private:
        map< string , map < string , map< string , float > > >  stock;
        SKU skulist;
};

#endif // DATABASE_H
