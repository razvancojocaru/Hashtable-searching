//Cojocaru Mihail-Razvan 313CA
#include <iostream>
#include <stdlib.h>
using namespace std;

template <typename T>struct Node {
 
public:
 
	T info;
	Node<T> *next;
	Node<T> *prev;
};
 
template <typename T>class LinkedList{
public:
 
	Node<T> *pfirst, *plast;
 

 
	//Constructor
	LinkedList(){
      	pfirst = plast = NULL;
    }
 
	/*Adauga un nod cu valoarea == value la inceputul listei */
	void addFirst(T value){
		Node<T> *paux;

		paux = new Node<T>;
		paux->info = value;
		paux->prev = NULL;
		paux->next = pfirst;

		if (pfirst != NULL) pfirst->prev = paux;
		pfirst = paux;

		if (plast==NULL) plast=pfirst;	
	}
	
	/*Adauga un nod cu valoarea == value la sfarsitul listei */
	void addLast(T value){
		Node<T> *paux;
		paux = new Node<T>;
		paux->info = value;
		paux->prev = plast;
		paux->next = NULL;

		if (plast != NULL) plast->next = paux;
		plast = paux;
		if (pfirst == NULL) pfirst = plast;
	}
 
	/*Elimina elementul de la inceputul listei si intoarce valoarea acestuia*/
	T removeFirst(){
		Node<T> *paux; T aux;
		if (pfirst != NULL) {
			paux = pfirst->next;
			aux = pfirst->info;
			if (pfirst == plast) plast = NULL;
			delete pfirst;
			pfirst = paux;
			if (pfirst != NULL) pfirst->prev = NULL;
		}
		else cout<<"Error 101 - The list is empty"<<endl; 
		return aux;
	}
 
	/*Elimina elementul de la sfarsitul listei listei 
	si intoarce valoarea acestuia*/
	T removeLast(){
		Node<T> *paux; T aux;
		if (plast != NULL) {
			paux = plast->prev;
			aux = plast->info;
			if (pfirst == plast) pfirst = NULL;
			delete plast;
			plast = paux;
			if (plast != NULL) plast->next = NULL;
		}
		else cout<<"Error 102 - The list is empty"<<endl;
		return aux;
	}
	
	/*Intoarce prima aparitie a elementului care are valoarea == value, 
	NULL daca nu exista*/
	Node<T>* find(T value){
		Node<T> *paux;
		paux = pfirst;
		while (paux != NULL) {
			if (paux->info == value)
				return paux;
			paux = paux->next;
		}
		return NULL;
	}
	
	/*Intoarce prima aparitie a elementului care are valoarea == value, 
	incepand de la pozitia p, NULL daca nu exista*/
	Node<T>* findfrom(T value, Node<T> *p){
		Node<T> *paux;
		paux = p;
		//Foloseste faptul ca lista e sortata
		if ( value < p->info ) return NULL;
		while (paux != NULL) {
			if (paux->info == value)
				return paux;
			paux = paux->next;
		}
		return NULL;
	}
 
 
	/*Intoarce 1 daca lista este vida, 0 altfel*/
	int isEmpty() {
		return (pfirst == NULL);
	}

	/*Intoarce primul element din lista*/
	T getFirst() {
		return pfirst->info;
	}

	/*Calculeaza nr de elemente din lista*/
	int size() {
		int i=1;
		Node<T> *p;
		p = pfirst;
		if (p == NULL) return 0;
		while ( p != plast ) {
			i++;
			p = p->next;
		}
		return i;
	}

	//Afiseaza continutul listei
	void printList() {
		Node<T> *p;
		if (isEmpty()) {
			cout<<"List is empty!";
			return;
		}
		p = pfirst;
		if (pfirst==plast) 
			cout<<p->info;
		else {
			cout<<p->info<<" ";
			while (p != plast) {
				p = p->next;
				cout<<p->info<<" ";		
			}
		}
		return;
	}


	//Pentru lista sortata
	//Adauga element, mentinand lista sortata
	void addElement(T x) {
		Node<T> *p, *paux;

		p = pfirst;
		while (p != NULL && p->info < x)
			p = p->next;

		if (p == NULL)
			addLast(x);
		else {
			paux = new Node<T>;
			paux->info = x;
			paux->next = p;
			paux->prev = p->prev;

			if (p->prev != NULL) p->prev->next = paux;
			else pfirst = paux;
			
			p->prev = paux;
		}
	}
};
