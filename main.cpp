#include <iostream>
#include <string>
#include <math.h>
#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;
using namespace std;
typedef mp::cpp_int INT;

INT add(const INT &s1,const INT &s2,const INT &s3)
{
    return ((s1%s3)+(s2%s3))%s3;
}

INT multi(const INT &s1,const INT &s2,const INT &s3)
{
    return ((s1%s3)*(s2%s3))%s3;
}

INT modexp(const INT &s1,const INT &s2,const INT &s3)
{
    INT s5=s2,m=s1%s3,s=1;
    
    while(s5!=0)
    {
        
        if(s5%2==1)
        {
            s=(s*m)%s3;
        }
        m=(m*m)%s3;
        s5=s5/2;
    }
    return s;
}

INT gcd(const INT &s1,const INT &s2)
{
    if(s2==0)
        return s1;
    else
        return gcd(s2,s1%s2);
}

INT invmod(INT s1,INT s2)
{
    if(gcd(s1,s2)!=1)
        return 0;
    
    INT tx,ty,x1("0"),x2("1"),y1("1"),y2;
    INT dup=s2,h;
    y2=-(s1/s2);
    INT r=s1%s2;
    while(r!=1)
    {
        s1=s2;
        s2=r;
        tx=x2;
        ty=y2;
        h=s1/s2;
        x2=x1-x2*h;
        y2=y1-y2*h;
        x1=tx;
        y1=ty;
        r=s1%s2;
    }
    
    return (x2+dup)%dup;
}

INT discretelog(INT h,INT g,INT p)
{
    p--;
    INT m=sqrt(p)+1;
    p++;
    INT prod("1"),prod2("1");
    INT z=invmod(g,p);
    z=modexp(z,m,p);
    prod2=h%p;
    for(INT j=0;j<m;j++)
    {
        prod=1;
        for(INT i=0;i<m;i++)
        {
            if(prod2==prod)
                return j*m+i;
            
            prod=(prod*g)%p;
        }
        prod2=(prod2*z)%p;
    }
    
}



struct RSA
{
private:
    INT p,q,d,phi;
public:
    INT n,e;
    RSA()
    {
        p=2;q=2;e=65537;
    }
    
    RSA KeyGen()
    {
        q=5915587277;
        p=1500450271;
        p--;q--;
        phi=p*q;
        ++p;
        ++q;
        n=p*q;
        d=invmod(e,phi);
        return *this;
    }
    
    INT Encryption(INT m)
    {
        
        
        return modexp(m,e,n);
    }
    
    INT Decryption(INT cipher)
    {
        return modexp(cipher,d,n);
    }
};




int main()
{
    int k;
    string x,y,z,g;
    cout<<"please enter right number for the operation that you want to do on these numbers:"<<endl;
    cout<<"enter '1' for modular addition  "<<endl;
    cout<<"enter '2' for modular multiplication "<<endl;
    cout<<"enter '3' for modular exponentiation "<<endl;
    cout<<"enter '4' for gcd of a and b"<<endl;
    cout<<"enter '5' for inverse modulo"<<endl;
    cout<<"enter '6' for descreate log "<<endl;
    cout<<"enter '7' for RSA "<<endl;
    cout<<"Input";
    cin>>k;
    INT s,cipher,message;
    RSA R;
    
    
    
    switch(k)
    {
        case 1:{
            cout<<"Please Enter numbers a ,b and c "<<endl;
            cin>>x>>y>>z;
            INT s1(x),s2(y),s3(z);
            s=add(s1,s2,s3);
            cout<<(s1+s2)%s3<<endl;
            break;
        }
        case 2:{
            cout<<"Please Enter numbers a ,b and c "<<endl;
            cin>>x>>y>>z;
            INT s1(x),s2(y),s3(z);
            s=multi(s1,s2,s3);
            cout<<s<<endl;
            break;
        }
        case 3:{
            cout<<"Please Enter numbers a ,b and c "<<endl;
            cin>>x>>y>>z;
            INT s1(x),s2(y),s3(z);
            s=modexp(s1,s2,s3);
            cout<<s<<endl;
            break;
        }
        case 4:{
            cout<<"Please Enter numbers a and b "<<endl;
            cin>>x>>y;
            INT s1(x),s2(y);
            s=gcd(s1,s2);
            cout<<s<<endl;
            break;
        }
        case 5:{
            cout<<"Please Enter numbers a and b "<<endl;
            cin>>x>>y;
            INT s1(x),s2(y);
            s=invmod(s1,s2);
            cout<<s<<endl;
            break;
        }
        case 6:{
            cout<<"Please Enter numbers a ,b and c "<<endl;
            cin>>x>>y>>z;
            INT s1(x),s2(y),s3(z);
            s=discretelog(s1,s2,s3);
            cout<<s<<endl;
            break;
        }
        case 7:{
            cout<<"enter a plain text message "<<endl;
            cin>>x;
            INT m(x);
            R=R.KeyGen();
            cipher=R.Encryption(m);
            cout<<cipher<<endl;
            message=R.Decryption(cipher);
            cout<<message<<endl;
            break;
        }
        default :{
            cout<<"Invalid input"<<endl;
        }
    }
}
