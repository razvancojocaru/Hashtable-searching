//Cojocaru Mihail-Razvan 313CA
#include "hashtable.h"

//Hashtable definit global
int hmax = 100;
Hashtable h(hmax);

//Functie care intersecteaza 2 liste sortate
//Returneaza o lista sortata
LinkedList<string> intersect(LinkedList<string> *l1, LinkedList<string> *l2) {
	LinkedList<string> final;
	Node<string> *p1, *p2, *paux;
	p1 = l1->pfirst;
	p2 = l2->pfirst;

	//Foloseste proprietatea ca listele sunt sortate
	while ( p1 && p2 ) {
		paux = l2->findfrom(p1->info, p2);
		if ( paux != NULL ) {
			final.addLast(p1->info);
			p2 = paux->next;
		}
		p1 = p1->next;
	}		
	return final;
}


void indexSite(const std::string &row)
{
	char *row_tok=strdup(row.c_str());
	char *command=strtok(row_tok," ");
	if (strcmp(command,"PUT")!=0)
	{
		free(row_tok);
		return;
	}
	
	char *site=strtok(NULL," ");
	char *word=strtok(NULL," ");
	while(word)
	{
		//Adauga site-ul la lista cuvantului din hashtable
		h.put(word, site);
		word=strtok(NULL," ");
	}
	free(row_tok);
}

void getSites(const std::string &row)
{
	char *row_tok=strdup(row.c_str());
	char *command=strtok(row_tok," ");
	//final - formata din intersectia listelor de site-uri ale cuvintelor citite
	//sites - lista auxiliara in care se pastreaza listele cu site-uri
	LinkedList<string> final, sites;

	if (strcmp(command,"GET")!=0)
	{
		free(row_tok);
		return;
	}
	
	char *word=strtok(NULL," ");
	//Daca primul cuvant nu este in hashtable, nu poate avea site asociat
	if ( h.hasKey(word) == 0 ) {
		cout<<"SITE_NOT_FOUND"<<endl;
		free(row_tok);
		return;
	}
	sites = h.get(word);
	//In cazul in care interogarea contine un singur cuvant, 
	//lista finala va fi aceeasi cu lista de site-uri a cuvantului respectiv
	final = sites;
	word=strtok(NULL," ");
	while(word)
	{

		sites = h.get(word);
		
		//Intersectam lista obtinuta la pasul curent cu lista cuvantului curent
		final = intersect(&final, &sites);
		
		//Daca lista ajunge vida, iesim din while
		if ( final.isEmpty() ) {  
			cout<<"SITE_NOT_FOUND"<<endl;
			free(row_tok);
			return;
		}
		word=strtok(NULL," ");
	}
	final.printList();
	cout<<endl;
	free(row_tok);
}

void wordInSite(const std::string &row)
{
	char *row_tok=strdup(row.c_str());
	char *command=strtok(row_tok," ");
	//Lista auxiliara in care se retin site-urile asociate unui cuvant
	LinkedList<string> sites;
	if (strcmp(command,"SITE")!=0)
	{
		free(row_tok);
		return;
	}
	
	char *site=strtok(NULL," ");
	char *word=strtok(NULL," ");

	while(word)
	{	
		sites = h.get(word);
		//Cautam site-ul in lista de site-uri a cuvantului curent
		if ( sites.find(site) == 0 ) {
			cout<<"WORD_NOT_FOUND"<<endl;
			free(row_tok);
			return;
		}
		word=strtok(NULL," ");
	}
	cout<<"WORD_FOUND"<<endl;
	free(row_tok);
}

void resolve()
{
	string row;
	while ( std::cin.good() )
	{
		std::getline(std::cin,row);
		//nu iau in considerare linii cu mai putin de 3 caractere
		if (row.size()<3)
			continue;
		switch(row[0])
		{
		//PUT
		case 'P':
			indexSite(row);
			break;
		//GET
		case 'G':
			getSites(row);
			break;
		//SITE
		case 'S':
			wordInSite(row);
			break;
		default:
			cout<<"Invalid option"<<endl;
		}
	}
}




int main()
{

	resolve();
	return 0;
}

