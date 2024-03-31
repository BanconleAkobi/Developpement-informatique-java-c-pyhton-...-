package TP1JAVA;

//AKOBI BANCONLE ISMAEIL 

import java.util.Random;

class Aleatoire{
	int T[];
	int Bornsup, Borninf,Max;
	
	/*un constructeur permettant notamment d’ initialiser le tableau avec des nombres
	aléatoires pris dans l’intervalle [Inf, Sup] ;*/
	
	public Aleatoire(int Borninf, int Bornsup, int Max) {
		this.Bornsup = Bornsup;
		this.Borninf = Borninf;
		this.Max = Max;
		T = new int[Max];
		Random r = new Random();
		
		for(int i=0; i<Max; i++) {
			T[i] = r.nextInt(Bornsup)+Borninf;
		}
	}
	//fonction qui affiche les valeurs du tableau
	void affiche() {
		for(int i=0; i<Max; i++) {
			System.out.print("T["+i+"] ="+T[i]+"  ");
		}
		System.out.print("\n");
	}
	
	//geter et seter de bornSup et Borninf pour pour pouvoir modifier les bornes
	
	int getBornsup(){
		return Bornsup;
	}
	void setBornsup(int Bornsup) {
		this.Bornsup =Bornsup;
	}
	
	int getBorninf(){
		return Borninf;
	}
	void setBorninf(int Borninf) {
		this.Borninf =Borninf;
	}
	
 //fonction permet qui permet de faire le tri
	public void permuter(int[] T, int i, int j) {
		int tmp;
		tmp = T[i];
		T[i] = T[j];
		T[j] = tmp;
	}

	void tri() {
		int i, j;
		System.out.println("le taleau trie est :");
		for (i =0; i<Max-1; i++) {
			for(j=i+1; j<Max; j++) {
				if(T[i] > T[j]) {
					permuter(T, i,j);
				}
			}
		}
	}
	
	int occurences(int n) {
		int nboccurences =0, i;
		for(i =0; i<Max; i++) {
			if(T[i] == n) {
				nboccurences++;
			}
		}
		return nboccurences;
		
		
	}
	
	void histogramme() {
		   int i;
		   System.out.println("Histogramme");
/*Comme on sait que les valeurs sont entre borninf et bornsup 
 * alors on peut verifier si le nombre est present dans le tableau en verifiant 
 * son nombre d'occurences et donc on pourra eviter les repetitions */
		  
		   for (i =Borninf; i<=Bornsup; i++) {
			    if( occurences(i)>0) {
			   System.out.print(i+" ");
			   for(int j =1 ; j<=occurences(i); j++) {
				   System.out.print("-");
			   }
			   System.out.print("\n");
			    }
		   }
	}
	
}

public class Test {
	public static void main(String[] args) {
		Aleatoire aleatoire = new Aleatoire(0, 50, 15);
		aleatoire.affiche();
		aleatoire.tri();
		//affichons le tableau apres le tri
		
		aleatoire.affiche();
		
		/* testons un setteur pour pouvoir modifier la valeur de la borne
		 *  inf par exemple et affichons */
		aleatoire.setBorninf(-5);
		
		
		//testons la fonction occurence
		int n =10;
		System.out.println( n+" a pour nombre d'occurences "+aleatoire.occurences(n));
		
		// testons l'histogramme
		aleatoire.histogramme();
	}
}
