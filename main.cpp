#include <GENE.h>
#include <CELL.h>
#include <ANIMAL.h>
#include <bits/stdc++.h>
using namespace std;

ANIMAL inp () {
    ANIMAL anim;
    int cnt;
    cout << "input the chromosome number of your animal" << endl;
    cin >> cnt;
    cout << "input chromosome" << endl;
    while (cnt--) {
        string dna0, dna1;
        cin >> dna0 >> dna1;
        anim.mycell.add_qr (dna0, dna1);
    }
    return anim;
}

int main () {
    int number0;
    cout<<"1)GENOME"<<endl;
    cout<<"2)CELL"<<endl;
    cout<<"3)ANIMAL"<<endl;
    cout<<"what is your choice:";
    cin>>number0;
    system("clear");
    if (number0==1){
    int number1;
    GENOME gene;
    while(true){
        system("clear");
        cout << "1)creat gene"<<endl;
        cout <<"2)display RNA"<<endl;
        cout <<"3)display DNA"<<endl;
        cout <<"4)REVERSE mutation"<<endl;
        cout <<"5)BIG mutation"<<endl;
        cout <<"6)LITTLE mutation"<<endl;
        cout <<"7)buid my DNA from RNA"<<endl;
        cout <<"enter your choice :";
        cin >> number1;
        if(number1 == 1){
            string s1,s2,s3;
            cin >> s1 >> s2 >> s3;
            gene.setter (s1, s2,s3);
        }
        else if(number1 == 2){
            gene.display_RNA ();
            delay (2000);
        }
        else if(number1 == 3){
            gene.display_DNA ();
            delay (2000);
        }
        else if(number1 == 4){
            string a;
            cin >> a;
            gene.rev_mutation (a);
            gene.display_DNA ();
            gene.display_RNA ();
            delay (4000);
        }else if(number1==5){
            string s1, s2;
            cin >> s1 >> s2;
            gene.big_mutation (s1, s2);
            gene.display_DNA ();
            gene.display_RNA ();
            delay (4000);
        }else if(number1 == 6){
            char x, y;
            int n;
            cin >> x >> y >> n;
            gene.lit_mutation(x,y,n);
            gene.display_DNA ();
            gene.display_RNA ();
            delay (4000);
        }else{
            cout << gene.build_my_DNA() << endl;
            delay (2000);
        }
        }}
        else if(number0==2){ //CELL
           int number2;
           CELL cell;
         while(true){
            cout << "1)size of the cell" << endl;
            cout << "2)add chromosomes" << endl;
            cout << " 3)who is alive" << endl;
            cout << "4)big mutation in cell" << endl;
            cout << "5)little mutation in cell" << endl;
            cout << "6)reverse mutation in cell" << endl;
            cout << "7)finding the complement palindrome" << endl;
            cin >> number2;
            if(number2 == 1){
               cell.count_chromosome(); 
            }
            else if(number2 == 2){
                string dna0;
                string dna1;
                cell.add_qr(dna0,dna1);

            }else if(number2 == 3){
                cell.who_is_alive();
            }
            else if(number2 == 4){
                string s1;
                string s2;
                cin>> s1 >> s2;
                int n1, n2;
                cin >> n1 >> n2;
                cell.big_mutation(s1,n1,s2,n2);
            }
            else if(number2 == 5){
                char a, b;
                int n, m;
                cin >> a >> b;
                cin >> n >> m;
                cell.lit_mutation(a,b,n,m);
            }else if(number2 == 6){
                string u;
                cin >> u;
                int z;
                cin >> z;
                cell.rev_mutation(u,z);
            }else{
                int l;
                cin >> l;
                cell.find_complement_palindrome(l);
            }    
         }
}else{ //Animal
        int number3; 
        cout << "1)find the equqlity percentage" << endl;
        cout << "2)are they the same ==?" << endl;
        cout << "3)asexual reproduction" << endl;
        cout << "4)find a reproduction +" << endl;
        cin >> number3;
        if (number3 == 1) {
            ANIMAL a, b;
            a = inp ();
            b = inp ();
            cout << a.equal_percentage (b) << '%' << endl;
            delay (2000);

        }
        else if (number3 == 2) {
            ANIMAL a, b;
            a = inp ();
            b = inp ();
            cout << (a == b ? "YES\n" : "NO\n");
            delay (2000);
        }
        else if (number3 == 3) {
            ANIMAL a, ara;
            a = inp ();
            ara = a.asexual_reproduction ();
            ara.display();
            delay (4000);
        }
        else {
            ANIMAL a, b, child;
            a = inp ();
            b = inp ();
            child.display();
            delay (4000);
        }
    }
