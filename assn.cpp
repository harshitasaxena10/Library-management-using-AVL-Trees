#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;
struct date
{
    int d;int m;int y;
};
date sys_date;
int julian(int year, int month, int day) {
  int a = (14 - month) / 12;
  int y = year + 4800 - a;
  int m = month + 12 * a - 3;
  if (year > 1582 || (year == 1582 && month > 10) || (year == 1582 && month == 10 && day >= 15))
    return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
  else
    return day + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083;
 }
int date_difference(date d1,date d2)
{

  int year1, month1, day1;
  int year2, month2, day2;
  int julian_day1, julian_day2;
  int difference;

  day1 = d1.d; month1 = d1.m; year1 = d1.y;
  day2 = d2.d; month2 = d2.m; year2 = d2.y;

  julian_day1 = julian(year1, month1, day1);
  julian_day2 = julian(year2, month2, day2);


  difference = julian_day2 - julian_day1;

  return difference;
}
struct BOOK
{
    char bookid[7];
    char bookname[51];
    char publisher[51];
    int edition;
    char author[26];
    int issued_to;
    date date_of_issue;
};
struct node
{
    long int key;
    BOOK b;
    int h;
    node *l;
    node *r;
};
class avlbooks
{
    public:
    node *T;
    node * leftRotation (node *GP,node *P,node *C);
    node * rightRotation(node *GP,node *P,node *C);
    avlbooks();
    void insert(long int n,BOOK b);
    void ins_rec(node *prev,node *curr,long int n,BOOK b);
    void print();
    void print_rec(node *);
    void remove(int n);
    void rem_rec(node *prev,node *curr,int n);
    int rem_replace(node *,node *,int);
    void balance(node*,node*);
    node* search(long int);
};
avlbooks :: avlbooks()
{
    T = new node;
    T->l = NULL;
    T->r = NULL;
    T->key = -1;
}
node* avlbooks :: search(long int key)
{
    node *temp;
    temp = T;
    while(temp->l != NULL && temp->r != NULL)
    {
        if(temp->key < key)
            temp = temp->r;
        else if(temp->key > key)
            temp = temp->l;
        else
            return(temp);
    }
    if(temp->key == key)
        return(temp);
    else
        return(NULL);
}
node* avlbooks :: leftRotation(node *GP,node *P,node *C)
{
    int x,y,z;
    if(P->l!=NULL) x = P->l->h; else x = -1;
    if(C->l!=NULL) y = C->l->h; else y = -1;
    if(C->r!=NULL) z = C->r->h; else z = -1;
    P->r = C->l;
    C->l = P;
    if(GP->r == P)      GP->r = C;
    else if(GP->l == P) GP->l = C;
    else T = C;
    if( x>= y ) P->h = x+1; else P->h = y+1;
    if(z>=P->h) C->h = z+1; else C->h = P->h+1;
    return(C);
}
node* avlbooks :: rightRotation(node *GP,node *P,node *C)
{
    int x,y,z;
    if(P->r!=NULL) x = P->r->h; else x = -1;
    if(C->l!=NULL) z = C->l->h; else z = -1;
    if(C->r!=NULL) y = C->r->h; else y = -1;
    P->l = C->r;
    C->r = P;
    if(GP->r == P)      GP->r = C;
    else if(GP->l == P) GP->l = C;
    else T = C;
    if( x>= y ) P->h = x+1; else P->h = y+1;
    if(z>=P->h) C->h = z+1; else C->h = z+1;
    return(C);
}
void avlbooks :: insert(long int n,BOOK b)
{
    if(T->key == -1)
    {
        T->key = n;
        T->b = b;
        T->h = 0;
    }
    else
    {
        ins_rec(T,T,n,b);
        int lh=-1,rh=-1;
        if(T->l != NULL) lh = T->l->h;
        if(T->r != NULL) rh = T->r->h;
        if(lh >= rh) T->h = lh+1;
        else T->h = rh+1;
    }
}

void avlbooks :: ins_rec(node *prev,node *curr,long int n,BOOK b)
{
    if(curr!=NULL)
    {


        if(curr->key<n)
            ins_rec(curr,curr->r,n,b);
        else
            ins_rec(curr,curr->l,n,b);
        balance(prev,curr);
    }
    else
    {
        node *t;
        t = new node;
        t->key = n;
        t->b= b;
        t->l = NULL;
        t->r = NULL;
        t->h = 0;
        if(prev->key < n)
        {
            prev->r = t;
            if(prev->h == 0)
                prev->h = t->h+1;
        }
        else
        {
            prev->l = t;
            if(prev->h == 0)
                prev->h = t->h +1;
        }
    }

}
void avlbooks :: balance(node *prev,node *curr)
{
        int lh=-1,rh=-1;
        int llh=-1,lrh=-1,rlh=-1,rrh=-1;
        int h;

        if(curr->l != NULL){lh = curr->l->h;    if(curr->l->l!= NULL) llh = curr->l->l->h;
                                                if(curr->l->r!= NULL) lrh = curr->l->r->h;}

        if(curr->r != NULL){rh = curr->r->h;    if(curr->r->l!= NULL) rlh = curr->r->l->h;
                                                if(curr->r->r!= NULL) rrh = curr->r->r->h;}

        int bf,lbf,rbf;
        bf  = rh - lh;
        lbf = lrh - llh;
        rbf = rrh - rlh;

        if(bf > 1  && rbf >= 0)      {//cout <<"BEFORE LEFT ROT : "; print();
                                        curr = leftRotation (prev,curr,curr->r);
                                     //cout <<"AFTER LEFT ROT : ";
                                    }
        else if(bf < -1 && lbf <= 0)  {curr = rightRotation(prev,curr,curr->l);}
        else if(bf > 1 && rbf < 0)  {
                                    curr->r = rightRotation(curr,curr->r,curr->r->l);
                                     curr = leftRotation(prev,curr,curr->r);
                                     }
        else if(bf < -1 && lbf > 0)  {curr->l = leftRotation(curr,curr->l,curr->l->r);
                                     curr = rightRotation(prev,curr,curr->l);}
        lh=-1;rh=-1;
        if(curr->l != NULL ) lh = curr->l->h;
        if(curr->r != NULL ) rh = curr->r->h;
        if(lh>=rh) curr->h = lh+1; else curr->h = rh+1;

        lh=-1;rh=-1;
        if(prev->l != NULL ) lh = prev->l->h;
        if(prev->r != NULL ) rh = prev->r->h;
        if(lh>=rh) prev->h = lh+1; else prev->h = rh+1;

}
void avlbooks :: remove(int n)
{
    if(T->key == n && T->h == 0)
    {
        T->key = -1;
        T->l = NULL;
        T->r = NULL;
    }
    else
    {
        rem_rec(T,T,n);
    }

}
void avlbooks :: rem_rec(node *prev,node *curr,int n)
{
    if(curr== NULL) return;
    if(curr->key < n)
    {
        rem_rec(curr,curr->r,n);
        balance(prev,curr);
    }
    else if(curr->key > n)
    {
        rem_rec(curr,curr->l,n);
        balance(prev,curr);
    }
    else
    {
        if(curr->l==NULL && curr->r==NULL)
        {
            if(prev->l == curr) prev->l = NULL;
            else                prev->r = NULL;

            delete(curr);
        }
        else if(curr->l!=NULL)
        {
            curr->key = rem_replace(curr,curr->l,-1);
            balance(prev,curr);
        }
        else
        {
            curr->key = rem_replace(curr,curr->r,1);
            balance(prev,curr);
        }
    }
}
int avlbooks :: rem_replace(node *prev,node *curr,int a)
{
    int ans;
    if(a == 1)
    {
        if(curr->l != NULL)
        {
            ans = rem_replace(curr,curr->l,1);
            balance(prev,curr);
        }
        else
        {
            if(prev->r == curr) {prev->r = NULL; if(prev->h==1 && prev->l==NULL)prev->h = 0;}
            else                {prev->l = NULL; if(prev->h==1 && prev->l==NULL)prev->h = 0;}
            ans = curr->key;
            delete(curr);
            return(ans);
        }
    }
    else
    {
        if(curr->r != NULL)
        {
            ans = rem_replace(curr,curr->r,-1);
            balance(prev,curr);
        }
        else
        {
            if(prev->r == curr) {prev->r = NULL; if(prev->h==1 && prev->l==NULL)prev->h = 0;}
            else                {prev->l = NULL; if(prev->h==1 && prev->l==NULL)prev->h = 0;}
            ans = curr->key;
            delete(curr);
            return(ans);
        }
    }


    return(ans);

}
void avlbooks :: print()
{
    print_rec(T);

    cout << endl;
}
void avlbooks :: print_rec(node *temp)
{
    if(temp!=NULL)
    {
        cout << temp->b.bookid<< ":"<<temp->h<<"  ";
        print_rec(temp->l);

        print_rec(temp->r);
    }
}

avlbooks books;

void readFile()
{
    cout << "READING FILE ..\n";
    fstream ifile("books.db",ios::in);
    BOOK n;
    char p;
    string prev;
    prev ="000000";
    long int key;
    char c;
    char al[51];
    int num = 0;
    int j=0,J=0;
    int i=0;
    while(!ifile.eof())
    {
        ifile.get(c);

        if((c>='a' && c<= 'z') || (c>='A' && c<='Z') || (c>='0' && c<='9')|| (p>='a'&&p<='z' && c==' '))
            al[j++] = c;
        else if(c==',' || c=='-' || (c=='\n' && i==8) )
        {
            al[j++] = '\0';
            switch(i){
            case 0: for(int J = 0;J<j;J++)n.bookid[J] = al[J]; i++; j=0; break;
            case 1: for(int J = 0;J<j;J++)n.bookname[J] = al[J]; i++; j=0; break;
            case 2: for(int J = 0;J<j;J++)n.publisher[J] = al[J]; i++; j=0; break;
            case 3: for(int J = 0;J<j-1;J++) num = num *10 + (al[J]-'0');
                    n.edition = num; num = 0; i++; j = 0; break;
            case 4: for(int J = 0;J<j;J++) n.author[J] = al[J]; i++; j =0; break;
            case 5: for(int J = 0;J<j-1;J++) num = num *10 + (al[J]-'0');
                    n.issued_to = num; num = 0; i++; j=0; break;
            case 6: for(int J = 0;J<j-1;J++) num = num *10 + (al[J]-'0');
                    n.date_of_issue.d = num; num = 0;i++; j=0; break;
            case 7: for(int J = 0;J<j-1;J++) num = num *10 + (al[J]-'0');
                    n.date_of_issue.m = num; num = 0;i++; j=0; break;
            case 8: for(int J = 0;J<j-1;J++) num = num *10 + (al[J]-'0');
                    n.date_of_issue.y = num; num = 0;i++; j=0; break;
            }
        }
        else if(c=='\n')
        {
            num = 0;
            j=0;i=0;
            if(prev.compare(0,6,n.bookid))
            {   prev = n.bookid;
                key =0;
                key = key*100 + (int)prev[0];
                key = key*100 + (int)prev[1];
                key = key*100 + (int)prev[2];
                key = key*10 + (int)prev[3] - '0';
                key = key*10 + (int)prev[4] - '0';
                key = key*10 + (int)prev[5] - '0';


                books.insert(key,n);
                cout << endl;}
        }
        p=c;
    }
    ifile.close();
}

struct USER
{
    int uid;
    char uname[51];
    char utype;
    char gender;
    int number[10];
};

struct node2
{
    long int key;
    USER b;
    int h;
    node2 *l;
    node2 *r;
};
class avlbooksuser
{
    public:
    node2 *T;
    avlbooksuser();
    node2 * leftRotation (node2 *GP,node2 *P,node2 *C);
    node2 * rightRotation(node2 *GP,node2 *P,node2 *C);
    void insert(long int n,USER b);
    void ins_rec(node2 *prev,node2 *curr,long int n,USER b);
    void print();
    void print_rec(node2 *);
    void remove(int n);
    void rem_rec(node2 *prev,node2 *curr,int n);
    int rem_replace(node2 *,node2 *,int);
    void balance(node2*,node2*);
    node2* search(long int);
};
node2* avlbooksuser :: search(long int key)
{
    node2 *temp;
    temp = T;
    while((temp->l != NULL) && (temp->r != NULL))
    {
        if(temp->key < key)
            temp = temp->r;
        else if(temp->key > key)
            temp = temp->l;
        else if(temp->key == key)
            return(temp);
    }
    if(temp->key == key)
        return(temp);
    else
        return(NULL);
}
avlbooksuser :: avlbooksuser()
{
    T = new node2;
    T->l = NULL;
    T->r = NULL;
    T->key = -1;
}

node2* avlbooksuser :: leftRotation(node2 *GP,node2 *P,node2 *C)
{
    int x,y,z;
    if(P->l!=NULL) x = P->l->h; else x = -1;
    if(C->l!=NULL) y = C->l->h; else y = -1;
    if(C->r!=NULL) z = C->r->h; else z = -1;
    P->r = C->l;
    C->l = P;
    if(GP->r == P)      GP->r = C;
    else if(GP->l == P) GP->l = C;
    else T = C;
    if( x>= y ) P->h = x+1; else P->h = y+1;
    if(z>=P->h) C->h = z+1; else C->h = P->h+1;
    return(C);
}
node2* avlbooksuser :: rightRotation(node2 *GP,node2 *P,node2 *C)
{
    int x,y,z;
    if(P->r!=NULL) x = P->r->h; else x = -1;
    if(C->l!=NULL) z = C->l->h; else z = -1;
    if(C->r!=NULL) y = C->r->h; else y = -1;
    P->l = C->r;
    C->r = P;
    if(GP->r == P)      GP->r = C;
    else if(GP->l == P) GP->l = C;
    else T = C;
    if( x>= y ) P->h = x+1; else P->h = y+1;
    if(z>=P->h) C->h = z+1; else C->h = z+1;
    return(C);
}
void avlbooksuser :: insert(long int n,USER b)
{
    if(T->key == -1)
    {
        T->key = n;
        T->b = b;
        T->h = 0;
    }
    else
    {
        ins_rec(T,T,n,b);
        int lh=-1,rh=-1;
        if(T->l != NULL) lh = T->l->h;
        if(T->r != NULL) rh = T->r->h;
        if(lh >= rh) T->h = lh+1;
        else T->h = rh+1;
    }
}

void avlbooksuser :: ins_rec(node2 *prev,node2 *curr,long int n,USER b)
{
    if(curr!=NULL)
    {


        if(curr->key<n)
            ins_rec(curr,curr->r,n,b);
        else
            ins_rec(curr,curr->l,n,b);
        balance(prev,curr);
    }
    else
    {
        node2 *t;
        t = new node2;
        t->key = n;
        t->b= b;
        t->l = NULL;
        t->r = NULL;
        t->h = 0;
        if(prev->key < n)
        {
            prev->r = t;
            if(prev->h == 0)
                prev->h = t->h+1;
        }
        else
        {
            prev->l = t;
            if(prev->h == 0)
                prev->h = t->h +1;
        }
    }

}
void avlbooksuser :: balance(node2 *prev,node2 *curr)
{
        int lh=-1,rh=-1;
        int llh=-1,lrh=-1,rlh=-1,rrh=-1;
        int h;

        if(curr->l != NULL){lh = curr->l->h;    if(curr->l->l!= NULL) llh = curr->l->l->h;
                                                if(curr->l->r!= NULL) lrh = curr->l->r->h;}

        if(curr->r != NULL){rh = curr->r->h;    if(curr->r->l!= NULL) rlh = curr->r->l->h;
                                                if(curr->r->r!= NULL) rrh = curr->r->r->h;}

        int bf,lbf,rbf;
        bf  = rh - lh;
        lbf = lrh - llh;
        rbf = rrh - rlh;

        if(bf > 1  && rbf >= 0)      {//cout <<"BEFORE LEFT ROT : "; print();
                                        curr = leftRotation (prev,curr,curr->r);
                                     //cout <<"AFTER LEFT ROT : ";
                                    }
        else if(bf < -1 && lbf <= 0)  {curr = rightRotation(prev,curr,curr->l);}
        else if(bf > 1 && rbf < 0)  {
                                    curr->r = rightRotation(curr,curr->r,curr->r->l);
                                     curr = leftRotation(prev,curr,curr->r);
                                     }
        else if(bf < -1 && lbf > 0)  {curr->l = leftRotation(curr,curr->l,curr->l->r);
                                     curr = rightRotation(prev,curr,curr->l);}
        lh=-1;rh=-1;
        if(curr->l != NULL ) lh = curr->l->h;
        if(curr->r != NULL ) rh = curr->r->h;
        if(lh>=rh) curr->h = lh+1; else curr->h = rh+1;

        lh=-1;rh=-1;
        if(prev->l != NULL ) lh = prev->l->h;
        if(prev->r != NULL ) rh = prev->r->h;
        if(lh>=rh) prev->h = lh+1; else prev->h = rh+1;

}
void avlbooksuser :: remove(int n)
{
    if(T->key == n && T->h == 0)
    {
        T->key = -1;
        T->l = NULL;
        T->r = NULL;
    }
    else
    {
        rem_rec(T,T,n);
    }

}
void avlbooksuser :: rem_rec(node2 *prev,node2 *curr,int n)
{
    if(curr== NULL) return;
    if(curr->key < n)
    {
        rem_rec(curr,curr->r,n);
        balance(prev,curr);
    }
    else if(curr->key > n)
    {
        rem_rec(curr,curr->l,n);
        balance(prev,curr);
    }
    else
    {
        if(curr->l==NULL && curr->r==NULL)
        {
            if(prev->l == curr) prev->l = NULL;
            else                prev->r = NULL;

            delete(curr);
        }
        else if(curr->l!=NULL)
        {
            curr->key = rem_replace(curr,curr->l,-1);
            balance(prev,curr);
        }
        else
        {
            curr->key = rem_replace(curr,curr->r,1);
            balance(prev,curr);
        }
    }
}
int avlbooksuser :: rem_replace(node2 *prev,node2 *curr,int a)
{
    int ans;
    if(a == 1)
    {
        if(curr->l != NULL)
        {
            ans = rem_replace(curr,curr->l,1);
            balance(prev,curr);
        }
        else
        {
            if(prev->r == curr) {prev->r = NULL; if(prev->h==1 && prev->l==NULL)prev->h = 0;}
            else                {prev->l = NULL; if(prev->h==1 && prev->l==NULL)prev->h = 0;}
            ans = curr->key;
            delete(curr);
            return(ans);
        }
    }
    else
    {
        if(curr->r != NULL)
        {
            ans = rem_replace(curr,curr->r,-1);
            balance(prev,curr);
        }
        else
        {
            if(prev->r == curr) {prev->r = NULL; if(prev->h==1 && prev->l==NULL)prev->h = 0;}
            else                {prev->l = NULL; if(prev->h==1 && prev->l==NULL)prev->h = 0;}
            ans = curr->key;
            delete(curr);
            return(ans);
        }
    }


    return(ans);

}
void avlbooksuser :: print()
{
    print_rec(T);

    cout << endl;
}
void avlbooksuser :: print_rec(node2 *temp)
{
    if(temp!=NULL)
    {
        cout << temp->key<< ":"<<temp->h<<"  ";
        print_rec(temp->l);

        print_rec(temp->r);
    }
}
avlbooksuser users;
void readFile2()
{
    cout << "READING FILE ..\n";
    fstream ifile("users.db",ios::in);
    USER n;
    char p;
    int prev;
    prev =0;
    long int key;
    char c;
    char al[51];
    int num = 0;
    int j=0,J=0;
    int i=0;
    while(!ifile.eof())
    {
        ifile.get(c);

        if((c>='a' && c<= 'z') || (c>='A' && c<='Z') || (c>='0' && c<='9')|| (p>='a'&&p<='z' && c==' '))
            al[j++] = c;
        else if(c==',' || (c=='\n' && i==4) )
        {
            al[j++] = '\0';
            switch(i){
            case 0: num = 0;for(int J = 0;J<j-1;J++)num = num*10 +(al[J]-'0');n.uid = num;num=0; i++; j=0; break;
            case 1: for(int J = 0;J<j;J++)n.uname[J] = al[J]; i++; j=0; break;
            case 2: n.utype = al[0]; i++; j=0; break;
            case 3: n.gender = al[0]; i++; j = 0; break;
            case 4: for(int J = 0;J<j;J++) n.number[J] = (al[J]-'0'); i++; j =0; break;
            }
        }
        if(c=='\n')
        {
            num = 0;
            j=0;i=0;
            if(prev != n.uid)
            {   prev = n.uid;
                key =prev;

                users.insert(key,n);
                cout << endl;}
        }
        p=c;
    }
    ifile.close();
}

class lib
{
    ofstream ofile;
    ofstream outBook;
    ofstream outUser;
    public:
    long int get_key(string prev);
    void issue(string bookid,int userid);
    void del(string bookid);
    void check(string bookid);
    lib();
    void overdue();
    void overdue_rec(node *);
    void renew(string,int);
    void exit();
    void exit1(node*);
    void exit2(node2*);
};
void lib :: exit()
{
    cout << "EXIT CALLED";
    exit1(books.T);
    exit2(users.T);
    remove("books.db");
    rename("final_books.txt","books.db");
    remove("users.db");
    rename("final_users.txt","users.db");
}
void lib :: exit2(node2 *temp)
{
    if(temp!=NULL)
    {
        exit2(temp->l);
        outUser << temp->b.uid <<", "<<temp->b.uname<<", "<<temp->b.utype<<", "<<temp->b.gender << ", ";
        for(int i = 0;i<10;i++)
            outUser << temp->b.number[i];
        outUser << endl;
        exit2(temp->r);
    }
}
lib :: lib()
{
    ofile.open("output.txt",ios :: out);
    outBook.open("final_books.txt",ios :: out);
    outUser.open("final_users.txt",ios :: out);
}
long int lib :: get_key(string prev)
{
    long int key;
    key = 0;
    key =0;
                key = key*100 + (int)prev[0];
                key = key*100 + (int)prev[1];
                key = key*100 + (int)prev[2];
                key = key*10 + (int)prev[3] - '0';
                key = key*10 + (int)prev[4] - '0';
                key = key*10 + (int)prev[5] - '0';
    return(key);

}
void lib :: issue(string bookid,int userid)
{
    long int key;
    key = get_key(bookid);
    node *t;
    node2 *t2;
    t2 = users.search(userid);
    t = books.search(key);
    ofile << "-------\n\n";
    ofile << "ISSUE "<< bookid << " "<< userid<< "\n\n";
    if(t2==NULL)
    {
        ofile << "Error, User not found\n\n";
        return;
    }
    if(t==NULL)
    {
        ofile << "Error, Book not found\n\n";
        return;
    }
    else if(t->b.issued_to == 0)
    {
        t->b.issued_to = userid;
        ofile << "Success," << t->b.bookname << " ("<<t->b.bookid<<") is isuued to "
        <<t2->b.uname<<" (" << userid<<") for 4 days" <<"\n\n";
        t->b.date_of_issue.d = sys_date.d;
        t->b.date_of_issue.m = sys_date.m;
        t->b.date_of_issue.y = sys_date.y;
    }
    else if(t->b.issued_to == -1)
    {
        ofile << "Error, "<<t->b.bookname << " can't be issued\n\n";
    }
    else
    {
        ofile << "Error, "<<t->b.bookname << " is already issued to someone\n\n";
    }
}
void lib :: del(string bookid)
{
    long int key;
    key = get_key(bookid);
    node *t;
    t= books.search(key);
    ofile << "-------\n\n";
    ofile << "DELETE "<< bookid << "\n\n";
    if(t==NULL)
    {
        ofile << "Error, book not found\n\n";
    }
    else if(t->b.issued_to == 0)
    {
        t->b.issued_to = -1;
        ofile << "Success, "<<t->b.bookname<<" ("<<bookid<<") is deleted\n\n";
    }
    else if(t->b.issued_to == -1)
    {
        ofile << "Error, "<<t->b.bookname<<" ("<<bookid<<") is already deleted\n\n";
    }
    else
    {
        ofile << "Error, "<<t->b.bookname<<" ("<<bookid<<") is issued\n\n";
    }
}
void lib :: check(string bookid)
{
    long int key;
    key = get_key(bookid);
    node *t;
    node2 *t2;
    t= books.search(key);
    ofile << "-------\n\n";
    ofile << "CHECK "<< bookid << "\n\n";

    if(t==NULL)
    {
        ofile << "Error, book not found\n\n";
    }
    else if(t->b.issued_to == 0)
    {
        ofile << "Success, "<<t->b.bookname<<" ("<<bookid<<") is not issued to anyone\n\n";
    }
    else if(t->b.issued_to == -1)
    {
        ofile << "Success, "<<t->b.bookname<<" ("<<bookid<<") is deleted\n\n";
    }
    else
    {
        t2 = users.search(t->b.issued_to);
        ofile << "Success, "<<t->b.bookname<<" ("<<bookid<<") is issued to "
        <<t2->b.uname<<" ("<<t->b.issued_to<<") on "<<t->b.date_of_issue.d <<"-"<<t->b.date_of_issue.m
        <<"-"<<t->b.date_of_issue.y<< "\n\n";
    }


}
void lib :: overdue()
{

    ofile << "-------\n\n";
    ofile << "SHOW OVERDUE\n";
    ofile << "List of overdue greater than 4 days is...\n\n";
    overdue_rec(books.T);
    ofile <<"\n";
}
void lib :: overdue_rec(node *temp)
{

    int a;
    if(temp!=NULL)
    {

        if(temp->b.issued_to>0)
        {

            a = date_difference(temp->b.date_of_issue,sys_date);
            cout << a<<endl;
            if(a>4)
                ofile << temp->b.bookid<<", "<< temp->b.issued_to<<"\n";
        }
        overdue_rec(temp->l);

        overdue_rec(temp->r);
    }
}
void lib :: exit1(node *temp)
{
    if(temp!=NULL)
    {
        exit1(temp->l);


        outBook << temp->b.bookid<<", "<<temp->b.bookname<<", "<<temp->b.publisher<<", "<<temp->b.edition<<", "<<temp->b.author<<","
                <<temp->b.issued_to<<", ";
        if(temp->b.issued_to != 0)
                outBook <<temp->b.date_of_issue.d<<"-"<<temp->b.date_of_issue.m<<"-"<<temp->b.date_of_issue.y<<endl;
        else
                outBook <<endl;

        exit1(temp->r);
    }
}

void lib :: renew(string bookid,int userid)
{
    int key;
    key = get_key(bookid);
    node *t;
    t = books.search(key);
    ofile << "-------\n\n";
    ofile << "RENEW "<< bookid << " "<< userid<<"\n\n";
    if(t==NULL)
    {
        ofile << "Error, book not found\n\n";
    }
    else if(t->b.issued_to == 0)
    {
        ofile << "Error, "<<t->b.bookname<<" ("<<bookid<<") is not issued to anyone\n\n";
    }
    else if(t->b.issued_to == -1)
    {
        ofile << "Error, "<<t->b.bookname<<" ("<<bookid<<") is already deleted\n\n";
    }
    else
    {
        node2 *t2;
        t2 = users.search(userid);
        if(t2 == NULL) return;
        else
        {ofile << "Success, "<<t->b.bookname<<" ("<<bookid<<") has been renewed to "<<t2->b.uname
        <<" (" << userid<<")"<< "\n\n";
            t->b.date_of_issue = sys_date;
        }
    }
}

lib l;
void read()
{
    string cmd;
    ifstream ifile("commands.txt",ios :: in);
    while(!ifile.eof())
    {
        ifile >> cmd;
        if(cmd == "ISSUE")
        {
            string bookid;
            int userid;
            ifile >> bookid >> userid;
            l.issue(bookid,userid);
        }
        else if(cmd == "RENEW")
        {
            string bookid;
            int userid;
            ifile >> bookid >> userid;
            l.renew(bookid,userid);
        }
        else if(cmd == "CHECK")
        {
            string bookid;
            ifile >> bookid;
            l.check(bookid);
        }
        else if(cmd == "DELETE")
        {
            string bookid;
            ifile >> bookid;
            l.del(bookid);
        }
        else if(cmd == "SHOW")
        {
            string a;
            ifile >> a;
            l.overdue();
        }
        else if(cmd == "EXIT")
        {
            l.exit();
            return;
        }

    }
}

int main()
{
    readFile();

    readFile2();

    lib l;
    time_t t = time(0);
    struct tm * now = localtime( & t );
    sys_date.y = (now->tm_year + 1900);
    sys_date.m = (now->tm_mon + 1);
    sys_date.d =   now->tm_mday;
    cout << sys_date.d << "  " << sys_date.m << "  "<< sys_date.y<< endl;

    read();
}
