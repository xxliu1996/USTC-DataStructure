#include<stdio.h>
#include<math.h>

#define scanf_s scanf

//every polynomial term includes a coefficient and an exponent
typedef struct{
	float coef;//coefficient
	int expn;//exponent
}ElemType;

//use linked list to formulate an unary polynomial
typedef struct LNode{
	ElemType data;
	LNode* next;
}*Polynomial;

void InitPolynomial(Polynomial &L)//initialize unary polynomial
{
	Polynomial p, q;
	float e;//parameter for stopping the input
	L = new LNode;
	p = L;
	printf("Please input the coefficient (left) and exponent (right) of each polynomial term. Enter 0 to stop inputting. \n");
	scanf_s("%f%d", &(p->data.coef), &(p->data.expn));
	e = p->data.coef;
	while (abs(e)>1e-6)
	{
		q = new LNode;
		p->next = q;
		p = q;
		scanf_s("%f%d", &(p->data.coef), &(p->data.expn));
		e = p->data.coef;//if the input is zero, then stop 
	}
	p->next = NULL;
}

void SortPolynomial(Polynomial &L)//sort the terms of the polynomial wit increasing order according to the exponent of each polynomial term
{
	Polynomial p, q;
	ElemType temp;
	for (p = L; p->next != NULL; p = p->next)
	for (q = p->next; q->next != NULL; q = q->next)
	{
		if ((p->data.expn) > (q->data.expn))
		{
			temp.coef = q->data.coef;
			q->data.coef = p->data.coef;
			p->data.coef = temp.coef;

			temp.expn = q->data.expn;
			q->data.expn = p->data.expn;
			p->data.expn = temp.expn;
		}
	}

}

void ReasePolynomial(Polynomial &L)//release the allocated memory of the linked list
{
	Polynomial p, q;
	for (p = L, q = p->next; p != NULL; p = q)
	{
		q = p->next;
		delete p;

	}
}

void Caculate(Polynomial L, float x,float &re)
{
	Polynomial p;
	for (p = L,re=0; abs(p->data.coef) > 1e-6; p = p->next)
	{
		re = re + p->data.coef*(pow(x,p->data.expn));
	}
}


void CopyPolynomial(Polynomial La, Polynomial &Lb)
{
	Polynomial p, q, h;
	h = new LNode;
    h->data = La->data;
	Lb = h;
	
	for (p = La->next; p != NULL; p = p->next)
	{
		q = new LNode;
		h->next = q;
		h = q;
		h->data = p->data;
		

	}

	h->next = NULL;

}

void InsertPolunomial(Polynomial &L, ElemType temp)
{

	Polynomial p, q;
	if (temp.expn <= L->data.expn)
	{
		if (temp.expn == L->data.expn)
		{
			L->data.coef += temp.coef;
			if (abs(L->data.coef) < 1e-6)
			{
				p = L;
				L = L->next;
				delete p;
			}
		}
		else
		{
			p = new LNode;
			p->data = temp;
			p->next = L;
			L = p;
		}
	}
	else
	{
		//for (p = L; ((temp.expn )> (p->next->data.expn)) && (p->next->data.expn != 0); p = p->next)
		p = L;
		while (((temp.expn) > (p->next->data.expn)) && (p->next->data.expn != 0))
			p = p->next;

		if ((temp.expn) == (p->next->data.expn))
		{
			p->next->data.coef += temp.coef;
			if (abs(p->next->data.coef) < 1e-6)
			{
				q = p->next;
				p->next = p->next->next;
				delete q;
			}
		}
		else
			{
				q = new LNode;
				q->data = temp;
				q->next = p->next;
				p->next = q;
			}

	}
}

void AddPolynomial(Polynomial &La, Polynomial &Lb)//addition
{
	Polynomial p;
	if (abs(La->data.coef) < 1e-6)
	{
		CopyPolynomial(Lb,La);
		return;
	}
	for (p = Lb; abs(p->data.coef) >1e-6; p = p->next)
		InsertPolunomial(La, p->data);
	ReasePolynomial(Lb);


}

void DeductPolynomial(Polynomial &La, Polynomial &Lb)//deduction
{
	Polynomial p;
	for (p = Lb; abs(p->data.coef) > 1e-6; p = p->next)
		p->data.coef *= (-1);
	AddPolynomial(La, Lb);
}

Polynomial MultiplySinglePolynomial(Polynomial L, ElemType temp)//multiplication of two single polynomial terms
{
	Polynomial p, Lp;
	CopyPolynomial(L, Lp);
	for (p = Lp; abs(p->data.coef) > 1e-6; p = p->next)
	{
		p->data.coef *= temp.coef;
		p->data.expn += temp.expn;
	}
	return Lp;

}

void MultiplyPolynomial(Polynomial &La, Polynomial &Lb)//multiplication of two unary polynomials
{
	Polynomial p, q,Lc;
	Lc = new LNode;
	Lc->next = NULL;
	Lc->data.coef = 0; Lc->data.expn = 0;

	for (p = Lb; abs(p->data.coef) > 1e-6; p = p->next)
	{
		q = MultiplySinglePolynomial(La, p->data);
		AddPolynomial(Lc, q);
	}

	p = Lb;
	Lb = Lc;
	ReasePolynomial(p);
}

void NPowerPolynomial(Polynomial La, Polynomial &Lb, int n)
{
	CopyPolynomial(La, Lb);
	for (int i = 1; i < n; i++)
		MultiplyPolynomial(La, Lb);
}

void PrintPolynomial(Polynomial L)//print out the unary polynomial
{
	Polynomial p;
	char Link;
	p = L;

	printf("%fX^%d", p->data.coef, p->data.expn);
	for (p = L->next; p->next != NULL; p = p->next)
	{
		if (p->data.coef > 0)
			Link = '+';
		else
			Link = '-';
		printf(" %c %fX^%d", Link, abs(p->data.coef), p->data.expn);
	}
	printf("\n");
}



int main()
{
	printf("---------Implemented functions of polymonial operaton---------\n");
	printf("1----------------Initialization of the Unary Polynomial\n");
	printf("2----------------Print the Unary Polynomial\n");
	printf("3----------------Destroy the Unary Polynomial\n");
	printf("4----------------Make a Copy of the Unary Polynomial\n");
	printf("5----------------Calculate the Addition of Two Unary Polynomials\n");
	printf("6----------------Calculate the Deduction of Two Unary Polynomials\n");
	printf("7----------------Calculate the Multiplication of Two Unary Polynomials\n");
	printf("8----------------Calculate the n-th Power of the Unary Polynomial\n");
	printf("9----------------Calculate the Value of the Unary Polynomial when x = a\n");
	printf("0----------------Exit\n");
	printf("Please Test the Implemented Functions as the Order from 1 to 9. (When Inputting the Efficients of the Unary Polynomial, Please as An Increasing Order of the Exponent)\n");


	int alfa, n;
	float a=0,re=0;
	Polynomial La=NULL, Lb=NULL, Lc=NULL,Ld=NULL,Le=NULL;
	printf("Please Enter alfa:");
	scanf_s("%d", &alfa);
	while (alfa)
	{
		switch (alfa)
		{
		case 1:
			printf("Initialize La: \n");
			InitPolynomial(La);
			printf("Initialize Lb: \n");
			InitPolynomial(Lb);
			break;
		case 2:
			if (La == NULL)
			{
				printf("Please Initialize La First: \n");
				break;
			}
			else
			{
				printf("Print La: \n");
				PrintPolynomial(La);
				break;
			}
		case 3:
			if(La == NULL)
			{
				printf("If La is NULL, Then There is No Need to Destroy It: \n");
				break;
			}
			else
			{
				printf("Destroy La: \n");
				ReasePolynomial(La);
				break;
			}
		case 4:
			printf("Make a Copy of Lb, and Set It as Lc: \n, Lb: \n");
            PrintPolynomial(Lb);
			CopyPolynomial(Lb, Lc);
			printf("Lc: \n");
			PrintPolynomial(Lc);
			break;
		case 5:
			printf("Initialize La Again: \n");
			InitPolynomial(La);
			printf("La & Lb: \n");
			PrintPolynomial(La);
			PrintPolynomial(Lb);
			printf("Add La and Lb, Save the Result on La and Release Lb: \n");
			AddPolynomial(La, Lb);
			PrintPolynomial(La);
			break;
		case 6:
			printf("Initialize Lb Again: ");
			InitPolynomial(Lb);
			printf("La & Lb: \n");
			PrintPolynomial(La);
			PrintPolynomial(Lb);
			printf("Deduct Lb from La, Save the Result on La and Release Lb: \n");
			DeductPolynomial(La, Lb);
			PrintPolynomial(La);
			break;
		case 7:
			printf("Initialize Lb Again: ");
			InitPolynomial(Lb);
			printf("La & Lb: \n");
			PrintPolynomial(La);
			PrintPolynomial(Lb);
			printf("Multiply La and Lb, Save the Result on La: \n");
			MultiplyPolynomial(La, Lb);
			PrintPolynomial(Lb);
			break;
		case 8:
			printf("Initialize Ld: \n");
			InitPolynomial(Ld);
			printf("Ld: \n");
			PrintPolynomial(Ld);
			printf("Le = Ld ^ n\nPlease Enter n: \n");
			scanf_s("%d", &n);
			NPowerPolynomial(Ld, Le, n);
			printf("The Result is: \n");
			PrintPolynomial(Le);
			break;
		case 9:
			printf("If x = a, Compute the Value of the Polynomial: \n");
			printf("Le: \n");
			PrintPolynomial(Le);
			printf("Please Enter a: \n");
			scanf_s("%f", &a);
			Caculate(Le, a, re);
			printf("The Reulst is: %.4f\n", re);
			break;
		default:
			printf("Wrong Number!\n");
			break;
		}
		printf("Please Enter alfa:");
		scanf_s("%d", &alfa);
	}
	return 0;
}