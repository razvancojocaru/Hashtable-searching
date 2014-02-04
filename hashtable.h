//Cojocaru Mihail-Razvan 313CA
#include "list.h"
#include <string.h>
#include <string>

struct elem_info {
	//cuvantul
	string key;
	
	//lista care pastreaza site-urile
	LinkedList<string> sites; 
};

class Hashtable {
	private:
        LinkedList<struct elem_info> *H;
        //Dimensiunea maxima hashtable
        int HMAX;

		//Functia de hash
        unsigned int hash(string key) {
			unsigned int h = 5381;
			for (unsigned int i=0;i<key.size();i++)
				h = (((h << 5) + h) + (int)key[i]) % HMAX;
			return h;
		}

    public:
        Hashtable(int hmax) {
			HMAX = hmax;
            H = new LinkedList<struct elem_info> [HMAX]; 
        }        

		~Hashtable() {
			for (int i = 0; i < HMAX; i++) {
				while (!H[i].isEmpty())
				H[i].removeFirst();
			}
            delete[] H;
        }
        
        //Adauga un site in lista de site-uri a unui cuvant    
        void put(string key, string site) {
            struct Node<struct elem_info> *p;
            struct elem_info info;

            int hkey = hash(key);
            p = H[hkey].pfirst;

            while (p != NULL) {
                if ( p->info.key == key )
                    break;
                p = p->next;
            }

				/*Verifica daca exista deja cuvantul in hashtable
				/Daca exista, adauga site-ul in lista, 
				pastrand ordine alfabetica*/
                if (p != NULL) {
                	if (p->info.sites.find(site) != NULL) return;;
                    p->info.sites.addElement(site);
                }
                else {
				//Daca nu exista cuvantul in hashtable
                    info.key = key;
                    info.sites.addElement(site);
                    H[hkey].addLast(info);
                }
        }
        
        //Returneaza lista de site-uri a unui cuvant    
        LinkedList<string> get(string key) {
            struct Node<struct elem_info> *p;

            int hkey = hash(key);
            p = H[hkey].pfirst;

            while (p != NULL) {
                if (p->info.key == key) break;
                p = p->next;
            }

            if (p != NULL)
                return p->info.sites;
            else {
                LinkedList<string> x;
                return x;
            }
        }

		/*Intoarce 1 daca respectivul cuvant exista in hashtable sau
		0 daca nu exista cuvantul in hashtable*/
        int hasKey(string key) {
            struct Node<struct elem_info> *p;

            int hkey = hash(key);
            p = H[hkey].pfirst;

            while (p != NULL) {
                if (p->info.key == key)
                    break;
                p = p->next;
            }

            if (p != NULL)
                return 1;
            else
                return 0;
        }

};
