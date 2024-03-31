package TP3;
import java.util.HashSet;
import java.util.ArrayList;

import java.util.Objects;


enum CahierCouleur {
    Jaune, Rouge, Bleu;
}

class Cahier {
    private int nombreDePages;
    CahierCouleur couleur;

    public Cahier(int nombreDePages, CahierCouleur couleur) {
        this.nombreDePages = nombreDePages;
        this.couleur = couleur;
    }

    public int getNombreDePages() {
        return nombreDePages;
    }

    public CahierCouleur getCouleur() {
        return couleur;
    }

    public double calculerPrix() {
        return nombreDePages / 2.0;
    }

    public String toString() {
        return getCouleur() + " " + getNombreDePages() + " x ";
    }
    
    public boolean equals(Object objet) {
        if (this == objet) {
            return true;
        }
        if (objet == null || getClass() != objet.getClass()) {
            return false;
        }
        Cahier cahier = (Cahier) objet;
        return nombreDePages == cahier.nombreDePages && couleur.equals(cahier.couleur);
    }

    public int hashCode() {
        return Objects.hash(nombreDePages, couleur);
    }
   
}

class Carnet {
    private int facteurDeQualite;

    public Carnet(int facteurDeQualite) {
        this.facteurDeQualite = facteurDeQualite;
    }

    public int getFacteurDeQualite() {
        return facteurDeQualite;
    }

    public double calculerPrix() {
        return 3 * facteurDeQualite;
    }

    public String toString() {
        return "Carnet (qualité " + facteurDeQualite + ")";
    }
}

class QuantiteArticle {
    private Object article;
    private int quantite;

    public QuantiteArticle(Object article, int quantite) {
        this.article = article;
        this.quantite = quantite;
    }

    public Object getArticle() {
        return article;
    }

    public int getQuantite() {
        return quantite;
    }
}

class Achat {
	    private HashSet<QuantiteArticle> articles;

	    public Achat() {
	        articles = new HashSet<>();
	    }


public void add(Object article, int quantite) {
    articles.add(new QuantiteArticle(article, quantite));
}

public double calculerPrixTotal() {
    double prixTotal = 0;
    for (QuantiteArticle quantiteArticle : articles) {
        Object article = quantiteArticle.getArticle();
        int quantite = quantiteArticle.getQuantite();
        if (article instanceof Cahier) {
            prixTotal += ((Cahier) article).calculerPrix() * quantite;
        } else if (article instanceof Carnet) {
            prixTotal += ((Carnet) article).calculerPrix() * quantite;
        }
    }
    return prixTotal;
}

public String toString() {
    StringBuilder resultat = new StringBuilder();
    for (QuantiteArticle quantiteArticle : articles) {
        Object article = quantiteArticle.getArticle();
        int quantite = quantiteArticle.getQuantite();
        resultat.append(article.toString()).append(quantite).append("\n");
    }
    resultat.append("Prix total: ").append(calculerPrixTotal());
    return resultat.toString();
}
}


public class Test {
	public static void main(String[] args) {
		Cahier cahier1 = new Cahier(20, CahierCouleur.Jaune);
		 Cahier cahier2 = new Cahier(40, CahierCouleur.Rouge);
		 Carnet carnet = new Carnet (5);

		 Achat achat = new Achat();
		 achat.add(cahier1, 5); // 5 cahiers
		 achat.add(cahier2,1);
		 achat.add(carnet , 7); // 7 carnets
		 System.out.println(achat);
		 } 

    
}

