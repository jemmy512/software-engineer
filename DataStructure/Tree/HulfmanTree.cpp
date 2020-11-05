#include <iostream>

struct HulfTree {
    char word;
    int weight;
    int left;
    int right;
    int parents;
    int *code;
};

void CreatHulfTree(HulfTree *F,int n) {
    int i,k1,k2;
    for (int loop = 0; loop < n-1; loop++) {
        /* search first available node */
        for (k1 = 0; k1 < n+loop && F[k1].parents != -1; k1++);

        /* search second available node */
        for (k2 = k1+1; k2 < n+loop && F[k2].parents != -1; k2++);

        for (i = 0; i < n+loop; i++) {
            if (F[i].parents == -1) {
                if (F[i].weight < F[k1].weight) {
                    k2 = k1;
                    k1 = i;
                } else if (F[i].weight == F[k1].weight) {

				} else if (F[i].weight < F[k2].weight) {
                    k2 = i;
                }
            }
        }

        F[i].word = 'X';
        F[i].left = k1;
        F[i].right = k2;
        F[i].parents = -1;
        F[i].code = nullptr;
        F[i].weight = F[k1].weight + F[k2].weight;
        F[k1].parents = F[k2].parents = i;
    }

}

void HulfTreeCode (HulfTree *F,int n) {
    for (int i = 0; i < n; i++) {
        F[i].code =  (int *)malloc(n * sizeof(int));
        F[i].code[0] = 0;
        int c = i;
        while (F[c].parents != -1) {
            int p = F[c].parents;
            if (F[p].left == c)  {
				F[i].code[++F[i].code[0]] = 0;
			} else  {
				F[i].code[++F[i].code[0]] = 1;
			}
            c = p;
        }
    }
}

void PrintHulfTree (HulfTree *F,int n) {
    for (int i = 0; i < n; i++) {
        std::cout << F[i].word << "'s code: ";
        for (int j = F[i].code[0]; j > 0; j--) {
            std::cout << F[i].code[j] << " ";
        }
        std::cout << std::endl;
    }
}

int main (void)
{
    int n;
    std::cin >> n;
    HulfTree *F = (HulfTree*)malloc((2*n-1) * sizeof(HulfTree)) ;
    for (int i = 0; i < n; i++) {
        fflush (stdin) ;
        std::cin >> F[i].word >> F[i].weight;
        F[i].left = F[i].right = F[i].parents = -1;
        F[i].code = NULL;
    }

    CreatHulfTree(F,n);
    HulfTreeCode(F,n);
    PrintHulfTree(F,n);
    return 0;
}
/*
input:
4
A 9
B 2
C 4
D 7

result:
A's code: 0
B's code: 1 0 0
C's code: 1 0 1
D's code: 1 1

input:
8
A 3
B 2
C 5
D 8
E 4
F 7
G 6
H 9

result:
A's code: 1 0 0 1
B's code: 1 0 0 0
C's code: 0 1 1
E's code: 0 1 0
F's code: 1 1 0
G's code: 1 0 1
H's code: 0 0
D's code: 1 1 1 */
