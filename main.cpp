#include <iostream>
#include <vector>

using namespace std;

struct Nod
{
    int val;
    char culoare;
    Nod *st, *dr, *tata;
    char get_culoare();
    void set_culoare(char culoare);
    Nod(int x);
    Nod();
};

char Nod :: get_culoare()
{
    if (this == nullptr)
    {
        return 'b';
    }
    return this->culoare;
}

void Nod:: set_culoare(char culoare)
{
    if (this == nullptr)
    {
        return;
    }
    this->culoare = culoare;
}

Nod :: Nod()
{
    st = dr = tata = nullptr;
}

Nod :: Nod(int x)
{
    val = x;
    culoare = 'r';
    st = dr = tata = nullptr;
}

class RedBlack
{
private:
    Nod *radacina;
public:
    RedBlack();
    Nod* get_radacina();
    void set_radacina(Nod *x);
    //Nod* NodNou(int val);
    void rotirest(Nod *x);
    void rotiredr(Nod *x);
    Nod* inserareRB(Nod *radacina, Nod *nou);
    void reparareinserare(Nod *x);
    void inordine(Nod *radacina);
    Nod* cautare(Nod *radacina, int x);
    int predecesor(Nod *radacina, int x);
    int succesor(Nod *radacina, int x);
    void inordinesortate(Nod *radacina, int mn, int mx);
    void inserare(int x);
    void gasit(int x);
};

RedBlack :: RedBlack()
{
    radacina = nullptr;
}

void RedBlack :: set_radacina(Nod *x)
{
    radacina = x;
}
Nod* RedBlack :: get_radacina()
{
    return radacina;
}

void RedBlack :: rotirest(Nod *x)
{
    Nod *y = x->dr;
    x->dr = y->st;
    if(x->dr != nullptr)
    {
        x->dr->tata = x;
    }
    y->tata = x->tata;
    if(x->tata == nullptr)
    {
        this->set_radacina(y);
    }
    else if(x == x->tata->st)
    {
        x->tata->st = y;
    }
    else
    {
        x->tata->dr = y;
    }
    y->st = x;
    x->tata = y;
}

void RedBlack :: rotiredr(Nod *x)
{
    Nod *y;
    y = x->st;
    x->st = y->dr;
    if(x->st != nullptr)
    {
        x->st->tata = x;
    }
    y->tata = x->tata;
    if(x->tata == nullptr)
    {
        this->set_radacina(y);
    }
    else if(x == x->tata->st)
    {
        x->tata->st = y;
    }
    else
    {
        x->tata->dr = y;
    }
    y->dr = x;
    x->tata = y;
}

Nod* RedBlack :: inserareRB(Nod *radacina, Nod *nou)
{
    if(radacina == nullptr)
    {
        return nou;
    }
    if(nou->val < radacina->val)
    {
        radacina->st = inserareRB(radacina->st, nou);
        radacina->st->tata = radacina;
    }
    else if(nou->val > radacina->val)
    {
        radacina->dr = inserareRB(radacina->dr, nou);
        radacina->dr->tata = radacina;
    }
    return radacina;
}

void RedBlack :: inordine(Nod * radacina)
{
    if (radacina == nullptr)
    {
        return;
    }
    inordine(radacina->st);
    cout << radacina->val << " " << radacina->get_culoare() << " ";
    inordine(radacina->dr);
}

void RedBlack :: inordinesortate(Nod *radacina, int mn, int mx)
{
    if (radacina == nullptr)
    {
        return;
    }
    inordinesortate(radacina->st, mn, mx);
    if(mn <= radacina->val <= mx)
    {
        cout << radacina->val << " ";
    }
    inordinesortate(radacina->dr, mn, mx);
}

void RedBlack :: reparareinserare(Nod *x)
{
    Nod *unchi = nullptr;
    Nod *tata = nullptr;
    Nod *bunic = nullptr;
    while(x != radacina && x->get_culoare() == 'r' && x->tata->get_culoare() == 'r')
    {
        tata = x->tata;
        bunic = tata->tata;
        if(tata == bunic->dr)// Cazul 1- tatal este fiul drept al bunicului
        {
            unchi = bunic->st;
            //1a- Unchiul este rosu => doar recolorare
            if(unchi !=nullptr && unchi->get_culoare() == 'r')
            {
                unchi->set_culoare('b');
                tata->set_culoare('b');
                bunic->set_culoare('r');
                x = bunic;
            }
            else
            {
                //1b Unchiul este negru si x este fiul stang al tatalui => rotire spre dreapta(tata)
                if (x == tata->st) {
                    this->rotiredr(tata);
                    x = tata;
                    tata = x->tata;
                }
                //1c Unchiul este negru si x este fiul drept al tatalui => rotire spre stanga(bunic) si recolorare
                this->rotirest(bunic);
                swap(tata->culoare, bunic->culoare);
                x = tata;
            }
        }
        else //Cazul 2 - tatal este fiul stang al bunicului
        {
            unchi = bunic->dr;
            //2a- Unchiul este rosu => doar recolorare
            if(unchi !=nullptr && unchi->get_culoare() == 'r')
            {
                unchi->set_culoare('b');
                tata->set_culoare('b') ;
                bunic->set_culoare('r');
                x = bunic;
            }
            else
            {
                //2b Unchiul este negru si x este fiul drept al tatalui => rotire spre stanga(tata)
                if (x == tata->dr) {
                    this->rotirest(tata);
                    x = tata;
                    tata = x->tata;
                }
                //2c Unchiul este negru si x este fiul stang al tatalui => rotire spre dreapta(bunic) si recolorare
                this->rotiredr(bunic);
                swap(tata->culoare, bunic->culoare);
                x = tata;
            }
        }
    }
    radacina->set_culoare('b');
}

Nod* RedBlack :: cautare(Nod *radacina, int x)
{
    if(radacina == nullptr || radacina->val ==x)
    {
        return radacina;
    }
    else if(radacina->val < x)
    {
        return cautare(radacina->dr, x);
    }
    else
    {
        return cautare(radacina->st, x);
    }
}

int RedBlack :: succesor(Nod *radacina, int x)
{
    if (radacina == NULL)
    {
        return 2147483647;
    }
    if (radacina->val == x)
    {
        return x;
    }
    if (x < radacina->val)
    {
        return min(radacina->val, succesor(radacina->st, x));
    }
    else
    {
        return succesor(radacina->dr, x);
    }
}

int RedBlack :: predecesor(Nod *radacina, int x)
{
    if (radacina == nullptr)
    {
        return -2147483647;
    }
    if (radacina->val == x)
    {
        return x;
    }
    if (x < radacina->val)
    {
        return predecesor(radacina->st, x);
    }
    else
    {
        return max(radacina->val, predecesor(radacina->dr, x));
    }
}

void RedBlack :: inserare(int x)
{
    Nod *nou = new Nod(x);
    Nod *radacina = get_radacina();
    set_radacina(inserareRB(radacina, nou));
    reparareinserare(nou);
};

void RedBlack :: gasit(int x)
{
    if(cautare(get_radacina(), x) != nullptr)
    {
        cout << "DA ";
    }
    else
    {
        cout << "NU ";
    }
}
int main()
{
    RedBlack a;
    int x;
    /*for(int i = 1; i <= 7; i++)
    {
        cin >> x;
        Nod *nou = new Nod(x);
        Nod *radacina = a.get_radacina();
        a.set_radacina(a.inserareRB(radacina, nou));
        a.reparareinserare(nou);
    }
    cout << '\n';
    cout << a.get_radacina()->val;
    a.inordine(a.get_radacina());
    if(a.cautare( a.get_radacina(), 2) !=nullptr)
    {
        cout << "DA ";
    }
    else
    {
        cout << "NU ";
    }
    if(a.cautare( a.get_radacina(), 5) != nullptr)
    {
        cout << "DA ";
    }
    else
    {
        cout << "NU ";
    }
    cout << '\n';*/
    int n, op, c, d;
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> op;
        switch(op)
        {
            case 1:
                cin >> x;
                a.inserare(x);
                break;
            case 3:
                cin >> x;
                a.gasit(x);
                break;
            case 4:
                cin >> x;
                cout << a.succesor(a.get_radacina(),x);
                break;
            case 5:
                cin >> x;
                cout << a.predecesor(a.get_radacina(),x);
            case 6:
                cin >> c >> d;
                a.inordinesortate(a.get_radacina(), c, d);
                break;
            default:
                break;
        }
    }
    return 0;
}
