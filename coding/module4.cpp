#include<stdio.h>
#include<malloc.h>
#define infinity 9999
typedef enum { thread, link} boolean;
struct node *in_succ(struct node *p);
struct node *in_pred(struct node *p);

struct node
{
	struct node *left_ptr;
	boolean left;
	int info;
	boolean right;
	struct node *right_ptr;
}*head=NULL;
insert_head()
{
	struct node *tmp;
	head=(struct node *)malloc(sizeof(struct node));
	head->info=infinity;
	head->left=thread;
	head->left_ptr=head;
	head->right=link;
	head->right_ptr=head;
}

find(int item,struct node **par,struct node **loc)
{
	struct node *ptr,*ptrsave;
	if(head->left_ptr==head)/*if tree is empty*/
	{
		*loc=NULL;
		*par=head;
		return 0;
	}
	if(item==head->left_ptr->info)/*item is at head->left_ptr*/
	{
	*loc=head->left_ptr;
	*par=head;
	return 0;	
	}
	ptr=head->left_ptr;
	while(ptr!=head)
	{
		ptrsave=ptr;
		if(item<ptr->info)
		{
			if(ptr->left==link)
			ptr=ptr->left_ptr;
			else
			break;
			
		}
		else
		if(item>ptr->info)
		{
			if(ptr->right==link)
			ptr=ptr->right_ptr;
			else
			break;
		}
		if(item==ptr->info){
		*loc=ptr;
		*par=ptrsave;
		return 0;
	}
	}
	*loc=NULL;/*item not found*/
	*par=ptrsave;
}
insert(int item)
{
	struct node *tmp,*parent,*location;
	if(location!=NULL)
	{
		printf("item already present");
		return 0;
	}
	tmp=(struct node *)malloc(sizeof(struct node));
	tmp->info=item;
	tmp->left=thread;
	tmp->right=thread;
	if(parent==head)/* tree is empty*/
	{
		head->left=link;
		head->left_ptr=tmp;
		tmp->left_ptr=head;
		tmp->right_ptr=head;
	}
	else
	if(item<parent->info)
	{
		tmp->left_ptr=parent->left_ptr;
		tmp->right_ptr=parent;
		parent->left=link;
		parent->right_ptr=tmp;
	}
}
del(int item)
{
	struct node *parent,*location;
	if(head==NULL)
	{
		printf("tree empty");
		return 0;
	}
	find(item,&parent,&location);
	if(location==NULL)
	{
		printf("item not present in tree");
		return 0;
	}
	if(location->left==thread && location->right==thread)
	casea(parent,location);
	if(location->left==link && location->right==thread)
	caseb(parent,location);
	if(location->left==thread && location->right==link)
	caseb(parent,location);
	if(location->left==link && location->right==link)
	casec(parent,location);
}
casea(struct node *par,struct node *loc)
{
	if(par==head)/*item to be deleted is first node*/
	{
		head->left=thread;
		head->left_ptr=head;
	}
	else
	if(loc==par->left_ptr)
	{
		par->left=thread;
		par->left_ptr=loc->left_ptr;
	}
	else
	{
		par->right=thread;
		par->right_ptr=loc->right_ptr;
	}
	free(loc);
}
caseb(struct node *par,struct node *loc)
{
	struct node *child,*s,*p;
	/*initialize child*/
	if(loc->left==link)/*item to be deleted has left_ptr*/
	child=loc->left_ptr;
	else /*item to be deletd has right_ptr*/
	child=loc->right_ptr;
	if(par==head)/*item to be deleted is first node*/
	head->left_ptr=child;
	else
	if(loc==par->left_ptr)/*item is left_ptr of its parent*/
	par->left_ptr=child;
	else /* item is right_ptr of its parent*/
	par->right_ptr=child;
	s=in_succ(loc);
	p=in_pred(loc);
	if(loc->right==link)/*if loc has right subtree*/
	s->left_ptr=p;
	else /* if loc has left subtree*/
	{
		if(loc->left==link)
		p->right_ptr=s;
	}
	free(loc);
}
casec(struct node *par,struct node *loc)
{
	struct node *ptr,*ptrsave,*succ,*parsuc,*s,*p;
	/*find inorder succesor and its parent*/
	ptrsave=loc;
	ptr=loc->right_ptr;
	while(ptr->left==link)
	{
		ptrsave=ptr;
		ptr=ptr->left_ptr;
	}
	succ=ptr;
	parsuc=ptrsave;
	loc->info=succ->info;
	if(succ->left==thread && succ->right==thread)
	casea(parsuc,succ);
	else
	caseb(parsuc,succ);
}
struct node *in_succ(struct node *ptr)
{
	struct node *succ;
	if(ptr->right==thread)
	succ=ptr->right_ptr;
	else
	{
		ptr=ptr->right_ptr;
		while(ptr->left==link)
		ptr=ptr->left_ptr;
		succ=ptr;
	}
	return succ;
}
struct node *in_pred(struct node *ptr)
{
	struct node *pred;
	if(ptr->left==thread)
	pred=ptr->left_ptr;
	else
	{
		ptr=ptr->left_ptr;
		while(ptr->right==link)
		ptr=ptr->right_ptr;
		pred=ptr;
	}
	return pred;
}
inorder(){
	struct node *ptr;
	if(head->left_ptr==head)
	{
		printf("tree is empty");
		return;
	}
	ptr=head->left_ptr;
	/*find the leftmost node and traversal*/
	while(ptr->left==link)
	ptr=ptr->left_ptr;
	printf("%d",ptr->info);
	while(1)
	{
		ptr=in_succ(ptr);
		if(ptr==head)/*if last node reached*/
		break;
		printf("%d",ptr->info);
	}
}
preorder()
{
    struct node *ptr;
    if(head->left_ptr=head)
    {
        printf("tree is empty");
        return;
    }
    ptr=head->left_ptr;
    while(ptr!=head)
    {
        printf("%d",ptr->info);
        if(ptr->left==link)
        ptr=ptr->left_ptr;
        else
        if(ptr->right_ptr==link)
        ptr=ptr->right_ptr;
        else
        {
            while(ptr!=head && ptr->right==thread)
            ptr=ptr->right_ptr;
            if(ptr!=head)
            ptr=ptr->right_ptr;

        }
    }
}
int main(){
	int choice,num;
	insert_head();
	while(1)
	{
		printf("\n");
		printf("1.insert\n");
		printf("2.delete\n");
		printf("3.inorder traversl\n");
		printf("4.preorder traversal\n");
		printf("5.quit\n");
		printf("enter your choice:");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				printf("enter the number to be inserted:");
				scanf("%d",&num);
				insert(num);
				break;
			case 2:
				printf("enter the number to be deleted:");
				scanf("%d",&num);
				del(num);
				break;
			case 3:
				inorder();
				break;
			case 4:
				preorder();
				break;
			case 5:
				exit(0);
			default:
				printf("wrong choice \n");
				
		}
	}
}
