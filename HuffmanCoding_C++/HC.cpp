//Navid Shamsizadeh,Farnush Sohrabi
///////////////////////////////////
//Professor : Ashkan Khatir////////
//Algorithm Design::Huffman Coding/
///////////////////////////////////
#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
//*******************************
class node
{
   public:
   node(int f, char c, node *l=0, node *r=0, node *fat=0)
   {
   	freq=f;
      ch=c;
      lchild=l;
      rchild=r;
      father=fat;	//baraye in father taarif kardim ke betoonim dar recursion
      				//befahmim farzand lchild boode ya rchild
      code[0]='\0';
   }
   void enternewfather(node *fat)
   {
   	father=fat;
   }

   node *readlchild(){return lchild;}
   node *readrchild(){return rchild;}

   char printc()
   {
   	return ch;
   }
   int printf()
   {
   	return freq;
   }

  void inorder (node *root)
{
	if (root != NULL) {
		inorder ((root)->lchild);

      if(root->lchild==NULL && root->rchild==NULL)
      {
		cout << "Character: \"" <<(*root).printc() << "\" , Frequency: \"" << (*root).printf() << "\" , Code: ";
      (*root).goup(root);
      (*root).printcode();
      cout << endl;
      }

		inorder ((root)->rchild);
	}
}


	void goup(node *root)
{  if(root->father != NULL )
 {
 	if( ((root->father)->lchild)==root){strcat(code,"0");}
   if( ((root->father)->rchild)==root){strcat(code,"1");}
   goup(root->father);
 }
}


	void printcode()
   {
   	for(int i=(strlen(code)-1);i>=0;i--)
      {
      	cout << code[i];
      }
   }


	private:
		node *lchild, *rchild;
		int freq;
      char ch;
      node *father;
      char code[5];
};

/////////////////////////////////
void shift(node *node[], int n)
{
   	for(int i=1;i<(n-1);i++)
      {
      	node[i]=node[i+1];
      }
}
//*******************************
void bubble(node *list[], int n) {
	int i, j;
	node *temp;
	for (i = 0; i < n ; i++)
		for (j = 0; j < (n-1) ; j++)
			if ( (*list[j]).printf() > (*list [j + 1]).printf() )
         {
				temp = list [j + 1];
				list [j + 1] = list [j];
				list [j] = temp;
			}
                                 }

/////////////////////////////////
int main(){

cout << "Please Enter Your Characters (ESC is The Last One.) :\n";
char input;
char ch[26];
int chcount[26];
int n=0;
while(true){
input=getch();
if(input==27){cout << "Finish getting characters ...";getch();break;}
if((input>=97 && input<=122)||(input>=65 && input<=90)){
ch[n]= input;
cout << "Character: \"" << input << "\" Quantity : ";
cin >> chcount[n];
n++;                                                   }
}

node *ptr[26];
clrscr();
for(int i=0;i<n;i++)
{
	ptr[i]=new node(chcount[i],ch[i]);
}

bubble(ptr, n);
cout << " Sorted Characters: \n";
for(int i=0;i<n;i++)
	{
		cout << "Character: \"" << (*ptr[i]).printc() << "\" , Frequency: \"" << (*ptr[i]).printf() << "\"" << endl ;
	}

int count=n;

node *temp;
while(count>1)
{

	bubble(ptr, count);
   temp=new node(((*ptr[0]).printf()+(*ptr[1]).printf()),'0',ptr[0],ptr[1]);
   (*( (*temp).readlchild() )).enternewfather(temp);
   (*( (*temp).readrchild() )).enternewfather(temp);
   ptr[0]=temp;
   shift(ptr,count);
   count--;

}
if(n>1)
{
cout << endl;
cout << " Huffman Binary Codes: \n";
(*temp).inorder(temp);
}

getch();
return 0;
}
