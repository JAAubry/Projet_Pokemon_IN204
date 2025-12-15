enum Statut_Utilisation {
        pioche,
        main,
        active,
        deja_utilisee
};

enum Element {
    Normal,
    Feu,
    Eau,
    Plante,
    Electrik,
    Glace,
    Combat,
    Poison,
    Sol,
    Vol,
    Psy,
    Insecte,
    Roche,
    Spectre,
    Dragon,
    Tenebres,
    Acier,
    Fee
} ;

class Carte {
    // on devra sûrement rajouter des champs d'objet graphique
    protected :
    char* id
    Statut_Utilisation statut ;
    char* url_image ;
    // Constructeur par défaut
    Carte()
    // Constructeur qui va chercher dans la base de données
    Carte()

    public :
    
} ;