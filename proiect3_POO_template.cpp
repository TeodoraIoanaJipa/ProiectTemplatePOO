#include <iostream>
#include<typeinfo>
#include <string.h>
using namespace std;

template <class T> class Angajat;
template <class T> class part_time;
template <class T> class permanent;

template<class T>
istream& operator>> (istream& in, Angajat<T> &a);
template<class T>
ostream& operator<< (ostream& out,Angajat<T> &a);
template<class T>
istream& operator>> (istream &in, part_time<T> &p);
template<class T>
ostream& operator<< (ostream &o, part_time<T> &p);
template<class T>
istream& operator>>(istream &in, permanent<T> &p);
template<class T>
ostream& operator<<(ostream& out, permanent<T> &p);

template<class T>
class Data
{
    int zi;
    T luna;
    int an;
public:
    Data();
    Data(int );
    Data(int, T);
    Data(int, T,int );              //constructor de initializare cu 3 parametrii
    Data(Data<T> &);               //constructor de copiere
    ~Data(){cout<<" ";}           //destructor
    Data<T>& operator =( const Data<T>&);
    T get_lunaa(){return luna;}
    int get_an(){return an;}
    template<class T1>                  //supraincarcarea operatorului = doar ca functie membra!!!
    friend istream& operator >>(istream& in, Data<T1> & d);
    template<class T1> //supraincaracre op citire Data
    friend ostream& operator <<(ostream& out, Data<T1> & d);
    template<class T1>
    friend istream& operator >>(istream& in,Angajat<T1>& a);//supraincarcare op citire Angajat
    template<class T1>
    friend ostream& operator <<(ostream &out, Angajat<T1>& a);

    friend class Angajat<T>;
    friend class part_time<T>;
    friend class permanent<T>;
};

template<>
class Data<char*>
{

    int zi;
    char* luna;
    int an;
public:
    Data(int a, char * b,int c) {zi=a; luna=new char[20]; strcpy(luna,b); an=c; }
    Data(){ zi=0; an=0; luna=new char[20]; strcpy(luna,"");}
    Data(int a, char* b){ zi=a; luna=new char[20]; strcpy(luna,b);}   //constructor de initializare cu 3 parametrii
    Data(Data<char *>& b){ zi=b.zi; an=b.an; luna=new char[20]; strcpy(luna,b.luna);  }                     //constructor de copiere
    ~Data(){cout<<" ";}                 //destructor
    char* get_lunaa(){  return luna;    }
    int get_an(){ return an;  }
    Data<char*>& operator =( const Data<char *>& a);
                      //supraincarcarea operatorului = doar ca functie membra!!!
    friend istream& operator >>(istream& in, Data<char*> & a){   cout<<"ziua/ luna/ anul: ";
                                                            a.luna=new char[10];
                                                            in>>a.zi>>a.luna>>a.an;
                                                            return in;           }
     //supraincaracre op citire Data
    friend ostream& operator <<(ostream& out, Data<char*> & d){ out<<d.zi<<" "<<d.luna<<" "<<d.an<<endl;return out;};
    friend class Angajat<char *>;
    friend class part_time<char *>;
    friend class permanent<char *>;
};


template <class T>
class Angajat{
protected:
    char* nume;
    char* prenume;
    float salariu;
    float suma_standard;
    Data<T> data_angajarii;

public:
    Angajat();
    Angajat(char *a, char *b, float s, float ss, Data<T> d):data_angajarii(d.zi,d.luna,d.an)
    {   nume=new char[20]; prenume=new char[20];
        strcpy(nume,a); strcpy(prenume,b); salariu=s; suma_standard=ss; };

    Angajat(char *a, char *b, float s, float ss, int d, T e, int f );
    Angajat(Angajat &);
    ~Angajat();
    Angajat<T>& operator=( const Angajat<T>&);
    friend istream& operator>> <>(istream& in, Angajat<T> &a);
    friend ostream& operator<< <>(ostream& out,Angajat<T> &a);
    virtual void citire(){cout<<"Introduceti numele prenumele salariul si suma_standard_stabilita_firma: ";
                        cin>>nume>>prenume>>salariu>>suma_standard;
                        cout<<"Angajat in ";
                        cin>>data_angajarii;}
    virtual void afisare(){ }
    virtual float prima(){ return 0;};
    int verific_an(){     int a; if(this->data_angajarii.get_an()<1940||this->data_angajarii.get_an()>2050) throw a;}
    float verific_zi(){ float b; if(this->data_angajarii.zi<1) throw b;
                                if(this->data_angajarii.zi>31) throw b;}
    double verific_suma(){ double d; if(suma_standard<0||suma_standard>1000) throw d;}
    friend class Data<T>;

};


Data<char*>& Data<char*> :: operator =( const Data<char *>& a)
{
    if(this != &a)
    {
        zi=a.zi;
        luna=new char[20]; strcpy(luna,a.luna);
        an=a.an;
    }
    return (*this);
}

template<class T>
Data<T>::Data()
{
    zi=0;
    luna=" ";
    an=0;
}

template<class T>
Data<T>::Data(int a)
{
    zi=a;
    luna=" ";
    an=0;
}

template<class T>
Data<T>::Data(int a,T b)
{
    zi=a;
    luna=b;
    an=0;
}

template<class T>
Data<T>::Data(int a, T b, int c)
{
    zi=a;
    luna=b;
    an=c;
}

template<class T>
Data<T>::Data( Data<T> &a)
{
    zi=a.zi;  luna=a.luna;   an=a.an;
}

template<class T>
Data<T>& Data<T>::operator=(const Data<T>& a)
{
    if(this != &a)
    {
        this->zi=a.zi;
        luna=a.luna;
        an=a.an;
    }
    return (*this);
}

template<class T>
istream& operator>>(istream &in,Data<T> &a)
{
    cout<<"ziua/ luna/ anul: ";
    in>>a.zi>>a.luna>>a.an;
    return in;
}

template<class T>
ostream& operator << (ostream &out,Data<T> &d)
{
    out<<d.zi<<" "<<d.luna<<" "<<d.an<<endl;
    return out;
}

template<class T>
Angajat<T>::Angajat()
{
    Data<T>d;
    data_angajarii=d;
    nume=new char[20]; prenume=new char[20];
    strcpy(nume,"No name");
    strcpy(prenume,"No name");
    salariu=0;
    suma_standard=0;

}

template<class T>
Angajat<T>::Angajat(char *a, char *b, float s,float ss, int d, T e, int f)
{
    nume=new char[20]; prenume=new char[20]; data_angajarii.luna=new char[10];
    strcpy(nume,a);
    strcpy(prenume,b);
    salariu=s;
    suma_standard=ss;
    data_angajarii.zi=d;
    data_angajarii.an=f;
    strcpy(data_angajarii.luna,e);
}

template<class T>
Angajat<T>::Angajat(Angajat &a)
{
    nume=new char[20]; prenume=new char[20];
    strcpy(nume,a.nume);
    strcpy(prenume,a.prenume);
    salariu=a.salariu;
    suma_standard=a.suma_standard;
    data_angajarii=a.data_angajarii;
}

template<class T>
Angajat<T>::~Angajat()
{ cout<<"D-Ang "; }

template<class T>
istream& operator>>(istream &in, Angajat<T> &a)
{
    cout<<"Introduceti numele prenumele salariul si suma_standard_stabilita_firma: "<<endl;
    in>>a.nume>>a.prenume>>a.salariu>>a.suma_standard;
    cout<<"Angajat in ";
    in>>a.data_angajarii;
    return in;
}

template<class T>
ostream& operator<<(ostream &out, Angajat<T> &a)
{
    out<<a.nume<<" "<<a.prenume<<" "<<a.salariu<<" lei "<<a.suma_standard<<" lei Angajat in "<<a.data_angajarii;
    return out;
}

template<class T>
Angajat<T>& Angajat<T>::operator= (const Angajat<T> &a)
{
    if(this != &a)
    {
        nume=new char[20]; prenume=new char[20];
        strcpy(nume,a.nume);
        strcpy(prenume,a.prenume);
        salariu=a.salariu;
        suma_standard=a.suma_standard;
        data_angajarii=a.data_angajarii;
    }
    return *this;
}

template<class T>
class part_time:public Angajat<T>
{
    int nr_ore_zi;
    Data<T> final_contract;
public:
    part_time():Angajat<T>(){nr_ore_zi=0; Data<T> d; final_contract=d;};
    part_time(int n):Angajat<T>(){ nr_ore_zi=n; };

    part_time(int n,int a,T b,int c):Angajat<T>(){ nr_ore_zi=n; final_contract.zi=a; final_contract.luna=new char[10];
                                  strcpy(final_contract.luna,b); final_contract.an=c; };
    part_time(part_time &);
    ~part_time(){ cout<<" "; }
    T get_luna(){  return final_contract.get_lunaa(); }
    friend istream& operator>> <>(istream &in, part_time &p);

    friend ostream& operator<< <>(ostream &o, part_time &p);

    part_time& operator= (const part_time&);
    void citire();
    void afisare();
    float prima();
    friend class Data<T>;
};

template<class T>
part_time<T>::part_time(part_time<T> &a):Angajat<T>(a)
{
    nr_ore_zi=a.nr_ore_zi;
    final_contract=a.final_contract;
}

template<class T>
part_time<T>& part_time<T>:: operator= (const part_time<T>& x)
{
    if(this!=&x)
    {
        this->Angajat<T>::operator=(x);
        nr_ore_zi=x.nr_ore_zi;
        final_contract=x.final_contract;
    }
}

template<class T>
istream& operator >> (istream &in, part_time<T> &p)
{
    in>>(Angajat<T> &)p;
    cout<<"Introduceti nr_ore_zi:";
    in>>p.nr_ore_zi;
    cout<<"Final contract in ";
    in>>p.final_contract;
    return in;
}

template<class T>
ostream& operator<< (ostream& out, part_time<T> &p)
{
    out<<(Angajat<T> &)p;
    out<<p.nr_ore_zi<<"ore zi";
    cout<<"Final contract in ";
    out<<p.final_contract;
    return out;
}

template<class T>
void part_time<T>::citire()
{
    this->Angajat<T>::citire();
    cout<<"Introduceti nr_ore_zi: ";
    cin>>nr_ore_zi; cout<<"Final contract in "; cin>>final_contract;
}

template<class T>
void part_time<T>::afisare()
{
  cout<<this->nume<<" "<<this->prenume<<" "<<this->salariu<<" lei "<<this->suma_standard<<" lei Angajat in "<<this->data_angajarii;
  cout<<"Nr ore/zi: "<<nr_ore_zi<<". Final contract in "<<final_contract;
}

template<class T>
float part_time<T>::prima()
{
    float p;
    if(this->get_luna()=="aprilie")
        p=0.75*this->suma_standard;
    else
        p=this->suma_standard;
    return p;
}

template<class t>
class permanent:public Angajat<t>
{
    int nr_minori_intretinere;
public:
    permanent():Angajat<t>(){nr_minori_intretinere=0;}
    permanent(int n):Angajat<t>(){ nr_minori_intretinere=n; };
    permanent(permanent<t> &);
    ~permanent(){ cout<<" ";}
    permanent& operator=(const permanent<t> &);
    friend istream& operator>> <>(istream &in, permanent<t> &p);
    friend ostream& operator<< <>(ostream &out, permanent<t> &p);
    void citire();
    void afisare();
    float prima();
    friend class Data<t>;
};

template<class T>
permanent<T>::permanent(permanent<T> &a):Angajat<T>(a)
{
    nr_minori_intretinere=a.nr_minori_intretinere;
}

template<class T>
permanent<T>& permanent<T>::operator=(const permanent<T> &p)
{
    if(this!= &p)
    {
        this->Angajat<T>::operator=(p);
        nr_minori_intretinere=p.nr_minori_intretinere;
    }
}

template<class T>
istream& operator>> (istream &in, permanent<T> &p)
{
    cout<<"Introduceti nr_minori_intretinere:";
    in>>p.nr_minori_intretinere;
    in>>(Angajat<T> &)p;
    return in;
}

template<class T>
ostream& operator<<(ostream& out, permanent<T> &p)
{
    out<<(Angajat<T> &)p;
    out<<"Numar minori:"<<p.nr_minori_intretinere;
    return out;
}

template<class T>
void permanent<T>::citire()
{
    cout<<"Angajat in ";
    cin>>this->data_angajarii;
    cout<<"Introduceti nr_minori_intretinere: ";
    cin>>nr_minori_intretinere;
}

template<class T>
void permanent<T>::afisare()
{
    cout<<this->nume<<" "<<this->prenume<<" "<<this->salariu<<" lei "<<this->suma_standard<<" lei Angajat in "<<this->data_angajarii;
    cout<<"Nr minori: "<<nr_minori_intretinere<<endl;
}

template<class T>
float permanent<T>::prima()
{
    float p;
    if(nr_minori_intretinere!=0)
        p=nr_minori_intretinere*this->suma_standard*(2018-this->data_angajarii.get_an())/100;
    else
        p=(2018-this->data_angajarii.get_an())*this->suma_standard/100;
    return p;
}

int main()
{
    try{

    int option,n;

    cout<<"Introduceti n:";
    cin>>n;
    Angajat<string> **a;
    a=new Angajat<string> *[n];
    for(int i = 0; i < n; i++)
    {
        cout<<endl;
        cout<<"Introduceti 1 pentru a adauga angajat permanent"<<endl;
        cout<<"Introduceti 2 pentru a adauga angajat part-time"<<endl;
        cout<<"Introduceti 3 pentru EXIT"<<endl<<endl;
        cin>>option;

        switch(option)
        {

            case 1:{
                        a[i]=new permanent<string>();
                        cin>>*dynamic_cast<permanent<string>*>(a[i]);
                        break;
                    }
            case 2:{
                        a[i]=new part_time<string>();
                        cin>>*dynamic_cast<part_time<string>*>(a[i]);
                        break;
                    }

            case 3:{
                        return 0;
                    }

        }
        a[i]->verific_an();
        a[i]->verific_zi();
        a[i]->verific_suma();
    }

    for(int i=0; i < n; i++)
    {
        cout<<endl;
        cout<<i+1<<". ";
        a[i]->afisare();
        cout<<"Prima: "<<a[i]->prima();
        cout<<endl;
    }

    }

    catch(int)
    {
        cout<<"Ati introdus anul din data angajarii gresit.";
    }
    catch(float)
    {
        cout<<"Ati introdus ziua din data angajarii gresit.";
    }
    catch(double)
    {
        cout<<"Ati introdus gresit suma_standard";
    }
    catch(...)
    {
        cout<<"Date introduse gresit";
    }

    return 0;
}
