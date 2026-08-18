#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct SinhVien
{
    char name[50];
    char class[50];
    char MaSV[10];
    float GPA;
}sv;
typedef struct node
{
    sv a;
    struct node *next;
}node;
node *MakeNode(sv a)
{
    node *NewNode=(node *)malloc(sizeof(node));
    NewNode->a=a;
    NewNode->next = NULL;
    return NewNode;
}
void InSinhVien(node *head)
{
    if(head==NULL)
    {
        printf("trong danh sach khong co sinh vien nao ca");
    }
    while(head!=NULL)
    {
        printf("Ho Ten: %sMSSV: %sLop: %sDiem GPA: %.2f\n", head->a.name, head->a.MaSV, head->a.class, head->a.GPA);
        head=head->next;
    }
}
int SoLuongSinhVien(node *head)
{
    int dem=0;
    while(head!=NULL)
    {
        dem++;
        head=head->next;
    }
    return dem;
}
void ThemVaoDau(node **head, sv a)
{
    node *NewNode=MakeNode(a);
    NewNode->next=*head;
    *head=NewNode;  
}
void ThemVaoSau(node **head, sv a)
{
    node *temp=*head;
    node *NewNode=MakeNode(a);
    if(*head==NULL)
    {
        *head=NewNode;
        return ;
    }
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next = NewNode;
}
void ThemVaoViTri(node **head, sv a, int k)
{
    int n = SoLuongSinhVien(*head);
    if(k==1)
    {
        ThemVaoDau(head, a);
        return;
    }
    if(k==n+1)
    {
        ThemVaoSau(head, a);
        return;
    }
    node *temp=*head;
    for(int i=1;i<=k-2;i++)
    {
        temp=temp->next;
    }
    node *NewNode=MakeNode(a);
    NewNode->next=temp->next;
    temp->next=NewNode;
}
void NhapSinhVien(int n,node **head, int LanNhap)
{
    sv a;
    for(int i=1;i<=n;i++)
    {
        do
        {
            printf("nhap ten sinh vien thu %d: ", i);
            fgets(a.name, sizeof(a.name), stdin);
            if(strlen(a.name)>49||strlen(a.name)==0)
            {
                printf("vui long nhap lai ten\n");
            }
        }while(strlen(a.name)>49||strlen(a.name)==0);
        do
        {
            printf("nhap ma sinh vien: ");
            fgets(a.MaSV, sizeof(a.MaSV), stdin);
            if(strlen(a.MaSV)>9||strlen(a.MaSV)==0)
            {
                printf("vui long nhap lai ma sinh vien\n");
            }
        }while(strlen(a.MaSV)>9||strlen(a.MaSV)==0);
        do
        {
            printf("nhap lop: ");
            fgets(a.class, sizeof(a.class), stdin);
            if(strlen(a.class)>49||strlen(a.class)==0)
            {
                printf("vui long nhap lai lop\n");
            }
        }while(strlen(a.class)>49||strlen(a.class)==0);
        do
        {
            printf("nhap diem GPA: ");
            scanf("%f", &a.GPA);
            if(a.GPA<0||a.GPA>4)
            {
                printf("vui long nhap lai diem GPA\n");
            }
        }while(a.GPA<0||a.GPA>4);
        getchar();
        int m=SoLuongSinhVien(*head);
        if(!LanNhap)
        {
            ThemVaoSau(head, a);
        }
        else
        {
            int k;
            do
            {
                printf("Nhap vi tri can chen vao danh sach: ");
                scanf("%d", &k);
                getchar();
                if(k<1||k>m+1)
                {
                    printf("vui long nhap lai vi tri can chen\n");
                }
            }while(k<1||k>m+1);
            ThemVaoViTri(head, a, k);
        }
    }
}
void XoaDau(node **head)
{
    if(*head==NULL)
    {
        return;
    }
    node *temp=*head;
    *head=temp->next;
    free(temp);
}
void XoaCuoi(node **head)
{
    node *temp=*head;
    if(*head==NULL)
    {
        return;
    }
    if(temp->next==NULL)
    {
        *head=NULL;
        free(temp);
        return;
    }
    while(temp->next->next!=NULL)
    {
        temp=temp->next;
    }
    node *NodeCuoi=temp->next;
    temp->next=NULL;
    free(NodeCuoi);
}
void XoaGiua(node **head, int m)
{
    int n=SoLuongSinhVien(*head);
    if(m<1||m>n)
    {
        return;
    }
    if(m==1)
    {
        XoaDau(head);
        return;
    }
    if(m==n)
    {
        XoaCuoi(head);
        return;
    }
    node *temp=*head;
    for(int i=1;i<=m-2;i++)
    {
        temp=temp->next;
    }
    node *xoa=temp->next;
    temp->next=temp->next->next;
    free(xoa);
}
int main()
{
    int n;
    node *head=NULL;
    do
    {
        printf("nhap so sinh vien can them vao danh sach: ");
        scanf("%d", &n); 
        if(n==0) return 0;
        if(n<0)
        {
            printf("vui long nhap lai so sinh vien\n");
        }
    }while(n<=0);
    getchar();
    NhapSinhVien(n, &head, 0);
    InSinhVien(head);
    int k;    
    do
    {
        printf("nhap so sinh vien can bo sung vao danh sach: ");
        scanf("%d", &k);  
        if(k<0)
        {
            printf("vui long nhap lai so sinh vien\n");
        }
    }while(k<0);
    getchar();
    NhapSinhVien(k, &head, 1);
    InSinhVien(head);
    printf("\n");
    XoaDau(&head);
    InSinhVien(head);
    printf("\n");
    XoaCuoi(&head);
    InSinhVien(head);
}
