# local_ftp
Création et manipulations sur un serveur locale ftp / création d'un processus daemon

# 1 Le protocole FTP
Le protocole FTP veut dire « File Transfert Protocol » ou Protocole de transfert de Fichier.
C’est le protocole de référence pour le transfert de fichiers. Il respecte une architecture clientserveur
entre un client FTP et un serveur FTP.
FTP opère sur la couche 7 du modèle OSI (Application) et a besoin d’un protocole de transport
fiable tel que TCP (s’utilise donc en mode connecté car si un paquet se perd cela engendre une
donnée erronée chez le client ou le serveur) et il fonctionne par défaut sur le port 21 pour
recevoir les commandes FTP et le port 20 pour recevoir les données.
La séquence de base de fonctionnement du protocole FTP est la suivante :
  • établir une connexion
  • envoyer son identifiant/nom d’utilisateur
  • envoyer son mot de passe
  • afficher le dossier courant
  • changer de dossier courant
  • récupérer une copie d’un fichier (download ou téléchargement)
  • déposer une copie d’un fichier (upload ou téléversement)
  • supprimer un fichier
FTP est dis non sécurisé car l’identifiant et mot de passe sont transmis en clair sur le
réseau ainsi il est aujourd’hui plus judicieux d’utiliser SFTP (SSH File Transfer Protocol) ou
FTP/S qui sont des dérivées de FTP chiffrant ces informations.

##################### Voir le rapport.pdf pour l'explication des tests #####################

P.s. ne pas avoir peur du russe sur certaines captures d'écran :D
