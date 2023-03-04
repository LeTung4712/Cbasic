#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define Max 10000
#define M 2069 // key hash

typedef char *keyType;
int valid = 0;
int counta = 0, countb = 0, countc = 1, max = 0, resultc = 0, sl1 = 0;

typedef struct Lane
{
    char j1[255];
    char j2[255];
    char name[255];
    int L;
    int W;
    int d;
    struct Lane *left;
    struct Lane *right;
} Lane;

int hash(char *s)
{ // hash function
    int rs = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        rs = (rs * 255 + s[i]) % M;
    return rs;
}

int getMax(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

Lane *root = NULL,*test=NULL;
Lane *validinput[Max];
Lane *rootc[M]; // root compare
Lane *makeNode(char *j1, char *j2, char *name, int L, int W, int d)
{
    Lane *p = (Lane *)malloc(sizeof(Lane));
    strcpy(p->j1, j1);
    strcpy(p->j2, j2);
    strcpy(p->name, name);
    p->L = L;
    p->W = W;
    p->d = d;

    p->left = NULL;
    p->right = NULL;
    return p;
}

bool isvalidjunction(char *j)
{
    if (strlen(j) != 4 || j[0] != 'J')
        return false;
    return true;
}
bool isvalidLong(int number)
{
    if (number < 10 || number > 500)
        return false;
    return true;
}
bool isvalidWeight(int number)
{
    if (number < 3 || number > 20)
        return false;
    return true;
}
int convertIndex(char *junc1, char *junc2)
{
    char *index1 = junc1 + 1;
    char *index2 = junc2 + 1;
    return atoi(index1) + atoi(index2);
}
int compareName(keyType a, keyType b){
  if(strcasecmp(a, b) > 0)
    return 1;
  else if(strcasecmp(a, b) < 0)
    return -1;
  else return 0;
}
int compare(Lane *root, Lane *tmp)
{
    int c = strcmp(root->name, tmp->name);
    if (c < 0)
    {
        return 1;
    }
    else if (c == 0)
    {
        if (convertIndex(root->j1, root->j2) > convertIndex(tmp->j1, tmp->j2))
        {
            return 1;
        }else if (convertIndex(root->j1, root->j2) < convertIndex(tmp->j1, tmp->j2))
        {
            return -1;
        }
        else
            return 0;
    }
    return -1;
}
Lane *insert(Lane *root, Lane *p)
{
    if (root == NULL)
        return p;
    int c = compare(root, p);
    if (c == 0)
    {
        root->L = root->L + p->L;
        root->W = (root->W >= p->W) ? p->W : root->W;
        /*
        if (root->W >= p->W)
            root->W = p->W;
        else
            root->W = root->W;
        */
        return root;
    }
    else if (c < 0)
    {
        root->right = insert(root->right, p);
        return root;
    }
    else
    {
        root->left = insert(root->left, p);
        return root;
    }
}
Lane *buildTree(int N)
{
    for (int i = 0; i < N; i++)
    {
        root = insert(root, validinput[i]);
    }
    return root;
}

void buildTreec(int N)
{
    for (int i = 0; i < N; i++)
    {
        int idx = hash(validinput[i]->name);
        //printf("index :%d\n", idx);
        rootc[idx] = insert(rootc[idx], validinput[i]);
    }
}

int countNode(Lane *root)
{
    if (root == NULL)
        return 0;
    else
    {
        return 1 + countNode(root->left) + countNode(root->right);
    }
}
int height(Lane *root)
{
    if (root == NULL)
        return 0;
    return getMax(height(root->left), height(root->right)) + 1;
}

Lane *search(char *name, Lane *rootc, int *sl)
{
    
    if (rootc == NULL)
    {                // Neu tree rong || de quy den node leaf ma van ko thay -> return NULL
        return NULL; // Not found
    }
    else if (compareName(rootc->name, name) == 0)
    { // Neu tim thay
        //printf("So sánh %s với %s\n",name,rootc[idx]->name);
        return rootc;
    }
    else if (compareName(rootc->name, name) < 0)
    { // Neu < khoa can tim -> tiep tuc tim ben phai
        return search(name, rootc->right, &sl);
    }
    else
    { // Neu > khoa can tim -> tiep tuc tim ben trai
        return search(name, rootc->left, &sl);
    }
}

void inOrderPrint(Lane *lane,int *sl)
{
    if (lane != NULL)
    {
        sl1++;
        *sl++;
        printf("%s %s %s %d %d %d\n", lane->j1, lane->j2, lane->name, lane->L, lane->W, lane->d);
        inOrderPrint(lane->left,&sl);       
        inOrderPrint(lane->right,&sl);
    }
}

Lane *getContent(char *fileName)
{
    Lane *tmp;
    FILE *f;
    int bufferLength = 255;
    char buffer[bufferLength];
    int N;
    f = fopen(fileName, "r");
    int line = 0;
    int SIZE = 0;

    while (fgets(buffer, bufferLength, f))
    {
        if (line == 0)
        {
            sscanf(buffer, "%d", &N);
            // printf("buffer %d\n",N);
            tmp = (Lane *)malloc((N) * sizeof(Lane));
        }
        else if (line <= N)
        {
            Lane lane;

            int i = 0;
            int field = 0;
            int L1, W1, d1;
            sscanf(buffer, "%s %s %s %d %d %d", lane.j1, lane.j2, lane.name, &L1, &W1, &d1);
            lane.L = L1;
            lane.W = W1;
            lane.d = d1;

            if (isvalidjunction(lane.j1) == true || isvalidjunction(lane.j2) == true)
            {
                counta++;
            }
            if (isvalidLong(lane.L) == true || isvalidWeight(lane.W) == true)
            {
                countb++;
            }
            int dientich = L1 * W1;
            if (max < dientich)
            {
                max = dientich;
                resultc = countc;
            }
            countc++;

            if (isvalidjunction(lane.j1) == true && isvalidjunction(lane.j2) == true && isvalidLong(lane.L) == true && isvalidWeight(lane.W) == true)
            {
                Lane *p = makeNode(lane.j1, lane.j2, lane.name, lane.L, lane.W, lane.d);
                validinput[valid] = p;
                valid++;
            }

            tmp[line - 1] = lane;
        }
        line++;
    }
    fclose(f);
    return tmp;
}
int main()
{
    printf("=>enter filename:\n");
    char filename[256], name[256];
    // scanf("%s", filename);
    // getContent(filename);
    getContent("input.txt");

    printf("\033[38;5;226m số dòng có tên hợp lệ là \033[0m \033[38;5;2m%d\033[0m\n", counta);
    printf("\033[38;5;226m số dòng có giá trị long và weight hợp lệ là \033[0m \033[38;5;1m%d\033[0m\n", countb);
    printf("\033[38;5;226m dòng có diện tích lớn nhất là dòng \033[0m \033[38;5;9m%d là %d(m^2)\033[0m\n", resultc, max);

    int N;
    printf("nhap N: ");
    scanf("%d", &N);
    root = buildTree(N);
    //inOrderPrint(root);

    int leaf = countNode(root);
    int hei = height(root);
    printf("so valid %d\n", valid);
    printf("so nut cua cay la %d\n", leaf);
    printf("chieu cao cua cay la %d\n", hei);

    int sl = 0;
    buildTreec(N);
    //for (int i = 0; i < M; i++)
    //{
        //printf("index %d\n",i);
        //inOrderPrint(rootc[i]);
        //printf("\n");
    //}
    
    
    while (1)
    {
    printf("=>enter name: ");
    scanf("%s", name);
    printf("hash %d\n", hash(name));
    inOrderPrint(rootc[hash(name)],&sl);
    printf("số nút có tên %s là %d\n", name,sl1);sl1=0;
    //}
    test =search(name, rootc[hash(name)], &sl);
    printf("tìm thấy %s %s %s %d %d %d\n", test->j1, test->j2, test->name, test->L, test->W, test->d);
    }


}