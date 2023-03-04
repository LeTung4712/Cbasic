#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> #define Max 10000
#define M 365 typedef struct  Lane
{
    int d;
    int m;
    int y;
    char seller[100];
    char buyer[100];
    char pID[100];
    float number;
    float cost;
    struct  Lane *left;
    struct  Lane *right;
}
 Lane;
int h(int d, int m, int y)
{
    int rs = 0;
    rs = (rs * 255 + d) % M;
    rs = (rs * 255 + m) % M;
    rs = (rs * 255 + y) % M;
    return rs;
}
 Lane *root = NULL;
 Lane *validinput[Max];
 Lane *rootc[365];
 Lane *makeNode(int d, int m, int y, char *seller, char *buyer, char *pID, float number, float cost)
{
     Lane *p = ( Lane *)malloc(sizeof( Lane));
    strcpy(p->seller, seller);
    strcpy(p->buyer, buyer);
    strcpy(p->pID, pID);
    p->d = d;
    p->m = m;
    p->y = y;
    p->number = number;
    p->cost = cost;
    p->left = NULL;
    p->right = NULL;
    return p;
}
bool isvalidcost(float cost)
{
    if (cost < 1 || cost > 2000000)
        return false;
    return true;
}
bool isvalidnumber(float number)
{
    if (number < 0 || number > 100)
        return false;
    return true;
}
int isbiggerdate(int d1, int m1, int y1, int d2, int m2, int y2)
{
    if (y1 > y2)
        return 1;
    else if (y1 < y2)
        return -1;
    else
    {
        if (m1 > m2)
            return 1;
        else if (m1 < m2)
            return -1;
        else
        {
            if (d1 > d2)
                return 1;
            else if (d1 < d2)
                return -1;
            else
                return 0;
        }
    }
}
int isbiggerseller(char *sellerA, char *buyerA, char *sellerB, char *buyerB)
{
    return strcmp(sellerA, sellerB) + strcmp(buyerA, buyerB);
}
int compare( Lane *root,  Lane *tmp)
{
    if (root->cost > tmp->cost)
        return 1;
    else if (root->cost == tmp->cost)
    {
        if (root->number < tmp->number)
        {
            return 1;
        }
        else if (root->number == tmp->number)
        {
            int c = strcmp(root->pID, tmp->pID);
            if (c > 0)
            {
                return 1;
            }
            else if (c == 0)
            {
                int c1 = isbiggerdate(root->d, root->m, root->y, tmp->d, tmp->m, tmp->y);
                if (c1 == 1)
                {
                    return 1;
                }
                else if (c1 == 0)
                {
                    int c2 = isbiggerseller(root->seller, root->buyer, tmp->seller, tmp->buyer);
                    if (c > 0)
                    {
                        return 1;
                    }
                    else if (c == 0)
                        return 0;
                }
            }
        }
    }
    return -1;
}
 Lane *insert( Lane *root,  Lane *p)
{
    if (root == NULL)
        return p;
    int c = compare(root, p);
    if (c == 0)
    {
        root->number = root->number + p->number;
        root->cost = root->cost + p->cost;
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
        int idx = h(validinput[i]->d, validinput[i]->m, validinput[i]->y);
        rootc[idx] = insert(rootc[idx], validinput[i]);
    }
}
int countNode( Lane *root)
{
    if (root == NULL)
        return 0;
    else
    {
        // if(root->left == NULL && root->right == NULL) return 1;
        // else return countNode(root->left) + countNode(root->right);
        return 1 + countNode(root->left) + countNode(root->right);
        ;
    }
}
int height( Lane *root)
{
    if (root == NULL)
        return 0;
    int a = height(root->left);
    int b = height(root->right);
    if (a > b)
        return (a + 1);
    else
        return (b + 1);
}
int main()
{
    int i, j, counta = 0, countb = 0, countc = 0, resultc = 0;
    int valid = 0;
    int d, m, y;
    char seller[100];
    char buyer[100];
    char pID[100];
    float number;
    float cost;
    float costperproduct;
    float max;
    char check = '$';
    char input[100];
    fgets(input, 100, stdin);
    while (input[0] != check)
    {
        sscanf(input, "%d-%d-%d %s %s %s %f %f", &d, &m, &y, seller, buyer, pID, &number, &cost);
        if (isvalidcost(cost) == true)
        {
            counta++;
        }
        if (isvalidnumber(number) == true)
        {
            countb++;
        }
        costperproduct = cost / number;
        if (max < costperproduct)
        {
            max = costperproduct;
            resultc = countc;
        }
        countc++;
        if (isvalidcost(cost) == true && isvalidnumber(number) == true)
        {
             Lane *p = makeNode(d, m, y, seller, buyer, pID, number, cost);
            validinput[valid] = p;
            valid++;
        }
        fgets(input, 100, stdin);
    }
    printf("so dong co so tien hop le la %d\n", counta);
    printf("so dong co so san pham hop le la %d\n", countb);
    printf("dong co so tien tren san pham lon nhat la %d\n", resultc);
    int N;
    printf("nhap N: ");
    scanf("%d", &N);
    root = buildTree(N);
    int leaf;
    leaf = countNode(root);
    int hei = height(root);
    printf("so nut cua cay la %d\n", leaf);
    printf("chieu cao cua cay la %d\n", hei);

    buildTreec(N);
    int max Lane = 0;
     Lane *tmp = ( Lane *)malloc(sizeof( Lane));
    for (i = 0; i < 365; i++)
    {
        if (max Lane < countNode(rootc[i]))
        {
            max Lane = countNode(rootc[i]);
            tmp = rootc[i];
        }
    }
    printf("ngay nhieu giao dich nhat la %d %d %d\n", tmp->d, tmp->m, tmp->y);
}
