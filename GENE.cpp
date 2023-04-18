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

class GENOME {
public:
    string RNA;
    string DNA[2];
    GENOME () {

    }
    GENOME (string dna0, string dna1, string rna = "nothing") {
        RNA = rna;
        DNA[0] = dna0;
        DNA[1] = dna1;
    }

    // set dna and rna for a genome
    void setter (string dna0, string dna1, string rna = "nothing") {
        RNA = rna;
        DNA[0] = dna0;
        DNA[1] = dna1;
    }

    //return a string that any char is complemented
    string complement (string s) {
        for (int i = 0; i < s.size(); i++) 
            s[i] = find_complement (s[i]);

        return s;
    }

    //do a complement on a range of rna
    void RNA_complement (int l, int r) {
        for (int i = l; i < r; i++)
            RNA[i] = find_complement (RNA[i]);
    }
    // do a complent on a range of dna
    void DNA_complement (int l, int r) {
        for (int i = l; i < r; i++) {
            DNA[0][i] = find_complement (DNA[0][i]);
            DNA[1][i] = find_complement (DNA[1][i]);
        }
    }

    //return a builded dna from rna
    string build_my_DNA () {
        return complement (RNA);
    }

    //find first n occurrence of char a and replace it with b
    void lit_mutation (char a, char b, int n) {
        int m = n;
        for (int i = 0; i < RNA.size(); i++) {
            if (m == 0)
                break;
            if (RNA[i] == a)
                RNA[i] = b, m--;
        }
        m = n;
        for (int i = 0; i < DNA[0].size(); i++) {
            if (m == 0)
                break;
            if (DNA[0][i] == a) {
                DNA[0][i] = b;
                DNA[1][i] = find_complement (b);
                m--;
            }
            else if (DNA[1][i] == a) {
                DNA[1][i] = b;
                DNA[0][i] = find_complement (b);
                m--;
            }
        }
    }

    //extra function for replacing s1 and s2
    void replace (string &s, int i, string s1, string s2) {
        string ans = "";
        ans = s.substr (0, i);
        ans += s2;
        int id = i+s1.size();
        ans += s.substr (id, s.size()-id);
        s = ans;
    }

    // replace first s1 with s2 in rna and dna 
    void big_mutation (string s1, string s2) {
        for (int i = 0; i <= RNA.size() - s1.size(); i++) {
            if (RNA.substr (i, s1.size()) == s1) {  
                replace (RNA, i, s1, s2);
                break;
            }
        } 
        for (int i = 0; i <= DNA[0].size() - s1.size(); i++) {
            if (DNA[0].substr (i, s1.size()) == s1) {  
                replace (DNA[0], i, s1, s2);
                replace (DNA[1], i, s1, find_complement (s2));
                break;
            }
            else if (DNA[1].substr (i, s1.size()) == s1) {
                replace (DNA[1], i, s1, s2);
                replace (DNA[0], i, s1, find_complement (s2));
                break;
            }
        }
    }

    // find first ocurence of s1 and do a complement on it
    void rev_mutation (string s1) {
        for (int i = 0; i <= RNA.size() - s1.size(); i++) {
            if (RNA.substr (i, s1.size()) == s1) {  
                RNA_complement (i, i+s1.size());
                break;
            }
        } 
        for (int i = 0; i <= DNA[0].size() - s1.size(); i++) {
            if (DNA[0].substr (i, s1.size()) == s1 || DNA[1].substr (i, s1.size()) == s1) {  
                DNA_complement (i, i+s1.size());
                break;
            }
        } 
    }

    // dispaly rna of a genome
    void display_RNA () {
        cout << "RNA   => " << RNA << '\n';
    }

    // display dna of a genome
    void display_DNA () {
        cout << "DNA 1 => " << DNA[0] << '\n' << "DNA 2 => " << DNA[1] << '\n';
    }
    friend class CELL;
    friend class ANIMAL;
};
