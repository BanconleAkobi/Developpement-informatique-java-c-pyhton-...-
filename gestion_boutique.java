package TP6Java;

import java.util.ArrayList;

class Produit implements Payable{
	private final String nom;
	private final long prix;
	int poids;
	
	public Produit(String nom, long prix, int poids){
		this.nom=nom;
		this.prix=prix;
		this.poids=poids;
		}
	
	public String getNom() {
		return nom;
	}
	
	public long getPrix() {
		return prix;
	}
	public long getPoids() {
		return poids;
	}
	
	public String toString(){
		double prix_euros=prix/100.0;
		return String.format("%s: %.2f €", nom, prix_euros);
	}
	public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Produit other = (Produit) obj;
        return this.nom.equals(other.nom) && this.prix == other.prix;
    }
	
	public String label() {
        return getNom();
    }

    public long cout() {
        return getPrix();
    }


    public long taxe() {
        return (long) (getPrix() * 0.10);
    }
}

class Panier{
	ArrayList<Produit> panier;
	private static int Id_panier=1;
	private final int Id;
	
	public Panier() {
		this.Id=Id_panier++;
		panier=new ArrayList<>();
	}
	
	public void ajoutProduit(Produit nouveau_produit) {
		if(nouveau_produit.poids>10000) {
			System.out.println("Votre produit dépasse les 10 kg->IMPOSSIBLE A AJOUTER!!!");
		}
		else {
		panier.add(nouveau_produit);
		
	}
	}
	
	public boolean supprimerProduit(Produit produit) {
		if(panier.contains(produit)) {
		panier.remove(produit);
		return true;
		}
		else {
			return false;
		}
	}
	
	public int nombreProduit() {
		return panier.size();
	}
	
	// Complexité d'ordre 0(n)
	public long prixTotal(){
	  long prixtotal=0;
	  for(Produit p:panier) {
		  prixtotal+=p.getPrix();
	  }
	  return prixtotal;
		}
	
	int getId() {
		return Id;
	}
	
	public String toString() {
	    StringBuilder resultat = new StringBuilder();
	    
	    resultat.append("Panier ").append(Id).append("[").append(nombreProduit()).append(" article(s)]");

	    for (Produit p : panier) {
	        resultat.append("\n").append(p.toString());
	    }

	    return resultat.toString();
	}

	
}

class ProduitFrais extends Produit{
	String DateLimiteConso;
	ProduitFrais(String nom, long prix, int poids,String DateLimiteConso){
		super(nom, prix, poids);
		this.DateLimiteConso=DateLimiteConso;
		
	}
	
	public String toString() {
		double prix_euros=super.getPrix()/100.0;
		return String.format("B:%s %s: %.2f €",DateLimiteConso, super.getNom(),prix_euros);
	}
	
	 public long taxe() {
	        double reduction = getPoids() * 0.001;
	        return (long) (super.taxe() - reduction);
	    }
}


class Ticket implements Payable {
 private final String reference;
 private final long prix;

 public Ticket(String reference, long prix) {
     this.reference = reference;
     this.prix = prix;
 }

 
 public String label() {
     return reference;
 }

 
 public long cout() {
     return prix;
 }

 
 public long taxe() {
    
     return (long) (prix * 0.25);
 }
}


interface Payable {
 String label();
 long cout();
 long taxe();
}
//3. Classe Facture
class Facture {
 private final ArrayList<Payable> Apayer;
 private long coutTotal;
 private long taxeTotale;


 public Facture() {
     this.Apayer = new ArrayList<>();
     this.coutTotal = 0;
     this.taxeTotale = 0;
 }

 public void ajout(Payable p) {
     Apayer.add(p);
     coutTotal += p.cout();
     taxeTotale += p.taxe();
 }

 // Méthodes montantTotal() et taxeTotale() sans parcourir la liste à nouveau
 public long montantTotal() {
     return coutTotal;
 }

 public long taxeTotale() {
     return taxeTotale;
 }

 
}

class Test {
     public static void main(String[] args) {
    	 Produit tin = new Produit("sardine", 500, 500);
    	 ProduitFrais frais = new ProduitFrais("sardine", 500, 500, "01-12-2022");
    	 ProduitFrais frais2 = new ProduitFrais("sardine x3", 1500, 1500, "01-12-2022");
    	 System.out.println(tin.taxe()); // affiche: 50
    	 System.out.println(frais.taxe()); // affiche: 49
    	 System.out.println(frais2.taxe()); // affiche: 148
    	 Facture facture = new Facture();
    	 facture.ajout(tin);
    	 facture.ajout(frais);
    	 facture.ajout(frais2);
    	 System.out.println(facture.montantTotal()); // affiche: 2500
    	 System.out.println(facture.taxeTotale()); // affiche: 248
     }
}
