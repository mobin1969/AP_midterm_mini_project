#include <bits/stdc++.h>
#include <GENE.h>
using namespace std;

//return complement of a A <-> T and  C <-> G
char find_complement (char ch) {
    if (ch == 'A')
        return 'T';
    else if (ch == 'T')
        return 'A';
    else if (ch == 'C')
        return 'G';
    else 
        return 'C';
}

//return a string that any char is complemented
string find_complement (string s) {
    for (int i = 0; i < s.size(); i++) {
        s[i] = find_complement (s[i]);
    }
    return s;
}

class CELL {
public:
    vector <GENOME> list;
    void add_qr (string dna0, string dna1) {
        GENOME mygene (dna0, dna1);
        list.push_back(mygene);
    }

    // return the number of chromose of a a cell
    int count_chromosome () {
        return list.size();
    }

    // extra function check wether is a chromose alive or not if yes return true else return false 
    bool is_alive (GENOME mygene) {
        int cntAT = 0, cntCG = 0;
        for (int i = 0; i < mygene.DNA[0].size(); i++) {
            if (mygene.DNA[0][i] == 'A' || mygene.DNA[1][i] == 'T')
                cntAT++;
            if (mygene.DNA[0][i] == 'T' || mygene.DNA[1][i] == 'A')
                cntAT++;
            if (mygene.DNA[0][i] == 'C' || mygene.DNA[1][i] == 'G')
                cntCG++;
            if (mygene.DNA[0][i] == 'G' || mygene.DNA[1][i] == 'C')
                cntCG++;
        }
        if (cntAT > 3*cntCG)
            return 0;
        int cnt = 0;
        for (int i = 0; i < mygene.DNA[0].size(); i++) {
            if (find_complement (mygene.DNA[0][i]) != mygene.DNA[1][i])
                cnt++;
        }
        return (cnt >= 5 ? false : true);
    }

    // check all chromosome in the list and delete the dead chromosomes and uses is_alive function
    void who_is_alive () {
        vector <GENOME> a;
        for (int i = 0; i < list.size(); i++) {
            if (is_alive (list[i]))
                a.push_back (list[i]);
        }
        list = a;
    }

    // extra function which is used for replacing s1 and s2 in a string
    void replace (string &s, int i, string s1, string s2) {
        string ans = "";
        ans = s.substr (0, i);
        ans += s2;
        int id = i+s1.size();
        ans += s.substr (id, s.size()-id);
        s = ans;
    }

    // replace the first occurrence of s1 in n1th chromose with the first occurence of s2 in n2th chromosome
    void big_mutation (string s1, int n1, string s2, int n2) {
        int it1 = -1, it2 = -1;

        for (int i = 0; i <= list[n1-1].DNA[0].size() - s1.size(); i++) {
             if (list[n1-1].DNA[0].substr (i, s1.size()) == s1 || list[n1-1].DNA[1].substr (i, s1.size()) == s1) {  
                it1 = i;
                break;
            }
        }

        for (int i = 0; i <= list[n2-1].DNA[0].size() - s2.size(); i++) {
             if (list[n2-1].DNA[0].substr (i, s2.size()) == s2 || list[n2-1].DNA[1].substr (i, s2.size()) == s2) {  
                it2 = i;
                break;
            }
        }


        if (it1 != -1 and it2  != -1) {
            replace (list[n1-1].DNA[0], it1, s1, s2);
            s1 = find_complement (s1);
            replace (list[n1-1].DNA[1], it1, s1, s2);

            replace (list[n2-1].DNA[0], it2, s2, s1);
            s2 = find_complement (s2);
            replace (list[n2-1].DNA[1], it2, s2, s1);
        }
    }

    // find the first n number of occurrence of a in m-th chromosome and replace them with b
    void lit_mutation (char a, char b, int n, int m) {
        for (int i = 0; i < list[m-1].DNA[0].size(); i++) {
            if (n == 0)
                break;
            if (list[m-1].DNA[0][i] == a) {
                list[m-1].DNA[0][i] = b;
                list[m-1].DNA[1][i] = find_complement (b);
                m--;
            }
            else if (list[m-1].DNA[1][i] == a) {
                list[m-1].DNA[1][i] = b;
                list[m-1].DNA[0][i] = find_complement (b);
                m--;
            }
        }
    }

    // extra function which do a copmlent for dna in a range
    void CDNA_complement (int l, int r, int n) {
        for (int i = l; i < r; i++) {
            list[n-1].DNA[0][i] = find_complement (list[n-1].DNA[0][i]);
            list[n-1].DNA[1][i] = find_complement (list[n-1].DNA[1][i]);
        }
    }

    // first occurrence of s1 in n-th chromosome and do a complement on it
    void rev_mutation (string s1, int n) {
        for (int i = 0; i <= list[n-1].DNA[0].size() - s1.size(); i++) {
            if (list[n-1].DNA[0].substr (i, s1.size()) == s1 || list[n-1].DNA[1].substr (i, s1.size()) == s1) {  
                CDNA_complement (i, i+s1.size(), n);
                break;
            }
        }
    }

    //with dp we find all palindrome of a chromosome and print them
    void find_complement_palindrome (int n) {
        int sz = list[n-1].DNA[0].size();
        bool pal[sz][sz];
        for (int i = 0; i < sz; i++)
            pal[i][i] = true;

        for (int i = 1; i < sz; i++) {
            pal[i-1][i] = (list[n-1].DNA[0][i-1] == list[n-1].DNA[0][i] ? 1 : 0);
        }
        for (int i = 2; i < sz; i++) {
            for (int j = i; j < sz-i; j++) {
                if (list[n-1].DNA[0][j] == list[n-1].DNA[0][j+i] and pal[j+1][j+i-1]) {
                    pal[j][j+i] = 1;
                    cout << list[n-1].DNA[0].substr (j, i+1);
                }
                else
                    pal[j][j+i] = 0;
            }
        }
        
        for (int i = 0; i < sz; i++)
            pal[i][i] = true;

        for (int i = 1; i < sz; i++) {
            pal[i-1][i] = (list[n-1].DNA[1][i-1] == find_complement (list[n-1].DNA[1][i]) ? 1 : 0);
        }
        for (int i = 2; i < sz; i++) {
            for (int j = i; j < sz-i; j++) {
                if (list[n-1].DNA[1][j] == find_complement(list[n-1].DNA[1][j+i]) and pal[j+1][j+i-1]) {
                    pal[j][j+i] = 1;
                    cout << list[n-1].DNA[1].substr (j, i+1);
                }
                else
                    pal[j][j+i] = 0;
            }
        }

    }

    //displau chromosome of the cell
    void display () {   
        for (int i = 0; i < list.size(); i++) {
            cout << i+1 << "th chromosome is\n";
            list[i].display_DNA();
        }
    }
    friend class ANIMAL;
};
