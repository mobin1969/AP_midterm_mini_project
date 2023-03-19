
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

class GENE {
private:
    string RNA;
    string DNA[2];
public:
    GENE (string rna) {
        RNA = rna;
        DNA[0] = rna;
        DNA[1] = complement (rna);
    }

    string complement (string s) {
        for (int i = 0; i < s.size(); i++) 
            s[i] = find_complement (s[i]);

        return s;
    }

    void RNA_complement (int l, int r) {
        for (int i = l; i < r; i++)
            RNA[i] = find_complement (RNA[i]);
    }
    void DNA_complement (int l, int r) {
        for (int i = l; i < r; i++) {
            DNA[0][i] = find_complement (DNA[0][i]);
            DNA[1][i] = find_complement (DNA[1][i]);
        }
    }

    string build_my_DNA () {
        return complement (RNA);
    }

    void mutation (char a, char b, int n) {
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

    void replace (string &s, int i, string s1, string s2) {
        string ans = "";
        ans = s.substr (0, i);
        ans += s2;
        int id = i+s1.size();
        ans += s.substr (id, s.size()-id);
        s = ans;
    }

    void mutation (string s1, string s2) {
        for (int i = 0; i <= RNA.size() - s1.size(); i++) {
            if (RNA.substr (i, s1.size()) == s1) {  
                replace (RNA, i, s1, s2);
                break;
            }
        } 
        for (int i = 0; i <= DNA[0].size() - s1.size(); i++) {
            if (DNA[0].substr (i, s1.size()) == s1) {  
                replace (DNA[0], i, s1, s2);
                for (int j = i; j < i+s1.size(); j++)
                    DNA[1][j] = find_complement (DNA[0][j]);
                break;
            }
            else if (DNA[1].substr (i, s1.size()) == s1) {
                replace (DNA[1], i, s1, s2);
                for (int j = i; j < i+s1.size(); j++)
                    DNA[0][j] = find_complement (DNA[1][j]);
                break;
            }
        }
    }

    void mutation (string s1) {
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
    void display_RNA () {
        cout << "RNA   => " << RNA << '\n';
    }

    void display_DNA () {
        cout << "DNA 1 => " << DNA[0] << '\n' << "DNA 2 => " << DNA[1] << '\n';
    }
    friend class ANIMAL;
};
