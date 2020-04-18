#include<Graph.h>

using namespace std;
string password="admin";
database *stock=new database;
Graph *gps=new Graph();

void employee_menu()
{

    char op;
    do
    {
        cout<<"1)Add Stock"<<endl;
        cout<<"2)View Stock"<<endl;
        cout<<"3)Renew Navigation Map"<<endl;
        cout<<"4)Return"<<endl;
        cout<<"Select  :";
        cin>>op;
        cout<<endl;
        bool flag=0;
        if(op<'0'&&op>'9')
            continue;
        system("clear") ;
        switch(op)
        {
            case '1':{
                        stock->add_stock();
                        delete(stock);
                        delete(gps);
                        stock=new database;
                        gps=new Graph();
                        cout<<"\n Press 1 to Renew Map";
                        char x;
                        cin>>x;
                        if(x!='1')
                                continue;
                        if(x=='1')
                        {   gps->clearmap();
                            gps->create();
                        }


                   }
                   break;
            case '2':{
                        stock->dealer_display();
                        flag=1;

                   }
                   break;
            case '3':{
                       gps->create();

                   }
                   break;
            case '4':{}
                break;
            default: cout<<"Select a Valid option\n";
        }
        string temp;
        if(flag)
            cin>>temp;
        system("clear") ;
    }
    while(op!='4');
}

void customer_menu()
{

    char op;
    do
    {
        cout<<"1)View Products"<<endl;
        cout<<"2)Navigate"<<endl;
        cout<<"3)Billing"<<endl;
        cout<<"4)Return"<<endl;
        cout<<"Select  :";
        cin>>op;
        cout<<endl;
        if(op<'0'&&op>'9')
            continue;
        system("clear") ;
        bool flag=0;
        switch(op)
        {
            case '1':{  flag=1;
                        stock->customer_display();
                   }
                   break;
            case '2':{
                        set<string> temp;
                        stock->customer_display();
                        cout<<"Enter Products you are Intrusted in (stop for -1):\n";
                        string x;
                        cin>>x;
                        while(x.compare("-1")!=0)
                        {
                            string t=stock->departmentis(x);
                            if(t.compare("-1")==0)
                            {
                                cout<<"Product does not exist\n";
                                cout<<"Re-enter Product :";
                                cin>>x;
                                cout<<endl;

                            }
                            else
                            temp.insert(t),
                            cin>>x;

                        }

                        gps->navigate(temp);
                        getchar();
                        getchar();

                   }
                   break;
            case '3':{ flag=1;
                       stock->billing();

                   }
                   break;
            case '4':{}
                break;
            default: cout<<"Select a Valid option\n";
        }

         string temp;
        if(flag)
            cin>>temp;
        system("clear") ;

    }
    while(op!='4');
}


void main_menu()
{

    char op;
    do
    {
        cout<<"\n1)Employee"<<endl;
        cout<<"2)Customer"<<endl;
        cout<<"3)Exit"<<endl;
        cout<<"Select  :";
        cin>>op;
        if(op<'0'&&op>'9')
            continue;
        cout<<endl;
        system("clear") ;
        switch(op)
        {
            case '1':{
                        employee_menu();
                   }
                   break;
            case '2':{
                        customer_menu();
                   }
                   break;
            case '3':{

                    int i;
                    for(i=0;i<3;i++)
                    {   string pass;
                        cout<<"Enter Password: ";
                        cin>>pass;


                        if(pass.compare(password)==0)
                            break;
                        else if(pass.compare("0")==0)
                            op='0',i=3;
                        else
                        cout<<"Invalid Password\n",op='0',
                        cout<<" Press 0 to return to main menu\n";

                    }


                   }
                   break;
            default: cout<<"Select a Valid option\n";
        }
        system("clear") ;
    }
    while(op!='3');
}
int main()
{
    main_menu();
    delete(stock);
    delete(gps);
	return 0;
}
