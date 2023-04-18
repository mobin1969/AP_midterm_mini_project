#include <genome.h>
#include <cell.h>
double find_equality (GENOME a, GENOME b) {
    int n = a.DNA[0].size();
    int m = b.DNA[0].size();
    int dp[n][m];
    
    dp[0][0] = (a.DNA[0][0] == b.DNA[0][0] and a.DNA[1][0] == b.DNA[1][0] ? 1 : 0);
    for (int i = 1; i < m; i++) {
        dp[0][i] = (a.DNA[0][0] == b.DNA[0][i] and a.DNA[1][0] == b.DNA[1][i] ? 1 : 0);
        dp[0][i] = max (dp[0][i-1], dp[0][i]);
    }
    for (int i = 1; i < n; i++) {
        dp[i][0] = (a.DNA[0][i] == b.DNA[0][0] and a.DNA[1][i] == b.DNA[1][0] ? 1 : 0);
        dp[i][0] = max (dp[i][0], dp[i-1][0]);
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            dp[i][j] = max (dp[i-1][j], dp[i][j-1]);
            if (a.DNA[0][i] == b.DNA[0][j] and a.DNA[1][i] == b.DNA[1][j])
                dp[i][j] = max (dp[i][j], dp[i-1][j-1] + 1);
        }
    }
    int mx = 0;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            mx = max (mx, dp[i][j]);

    return (double)mx/ (max (n, m)) * 100.0;
}

class ANIMAL {
public:
    CELL mycell;
    //set cell for ANIMAL
    void set_mycell (CELL mycell) {
        this->mycell = mycell;
    }

    //return if two ANIMALs are same 
    double equal_percentage (ANIMAL obj) {
        int n = mycell.count_chromosome();
        int m = obj.mycell.count_chromosome();
       
        double mx1[n], mx2[m];
        fill (mx1, mx1+n, 0);
        fill (mx2, mx2+m, 0); 

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                double jav = find_equality (mycell.list[i], obj.mycell.list[j]);
                mx1[i] = max (mx1[i], jav);
                mx2[j] = max (mx2[j], jav);
            }
        }

        double ans1 = 0.0, ans2 = 0.0;
        for (int i = 0; i < n; i++) 
            ans1 += mx1[i];
        for (int i = 0; i < n; i++)
            ans2 += mx2[i];

        ans1 /= n, ans2 /= m;
        return min (ans1, ans2);
    }

    //check if two animal is same
    bool operator== (ANIMAL &b) {
        if (equal_percentage (b) >= 70.0 && mycell.count_chromosome() == b.mycell.count_chromosome())
            return 1;
        else
            return 0;
    }

    //return a random animal who has equal percentage more than 70 
    ANIMAL asexual_reproduction () {
        vector <int> vec;
        int n = mycell.count_chromosome();
        for (int i = 0; i < n; i++) {
            vec.push_back (i);
            vec.push_back (i);
        }
        ANIMAL anim;
        anim.mycell = mycell;
        int t = 1000;
        while (t--) {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            shuffle (vec.begin(), vec.end(), std::default_random_engine(seed));
            ANIMAL ANM;
            for (int i = 0; i < n; i++) {
                ANM.mycell.add_qr (mycell.list[vec[i]].DNA[0], mycell.list[vec[i]].DNA[1]);
            }

            if (equal_percentage (ANM)) {
                anim = ANM;
                break;
            }
        }
        return anim;
    }

    //first asexual reproduction the two object then find a random child who has equality percentage more than 70
    ANIMAL operator+ (ANIMAL obj) {
        ANIMAL child1 = asexual_reproduction (), child2 = obj.asexual_reproduction();
        ANIMAL child;
        if (mycell.count_chromosome() != obj.mycell.count_chromosome())
            return child; 
        else if (mycell.count_chromosome() %2 == 1)
            return child;
        else {
            vector <int> vec;
            int n = mycell.count_chromosome();
            for (int i = 0; i < n; i++) {
                vec.push_back (i);
            }
            int t = 1000;
            while (t--) {
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                shuffle (vec.begin(), vec.end(), std::default_random_engine(seed));
                ANIMAL c;
                for (int i = 0; i < n/2; i++) {
                    c.mycell.add_qr (child1.mycell.list[vec[i]].DNA[0], child1.mycell.list[vec[i]].DNA[1]);
                }   
                for (int i = n/2; i < n; i++) {
                    c.mycell.add_qr (child2.mycell.list[vec[i]].DNA[0], child2.mycell.list[vec[i]].DNA[1]);
                }
                if (equal_percentage (c) >= 70.0 and obj.equal_percentage (c) >= 70.0) {
                    child = c;
                    break;
                }
            }
        }
        return child;
    }

    //display the animal cell
    void display () {
        mycell.display();
        cout << '\n';
    }
};
