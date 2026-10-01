# Commande de buzzers par Wi-Fi – ESP32

Un ESP32 crée un petit serveur web sur le réseau local. Depuis un téléphone ou un PC, une page avec des boutons permet d'activer ou de couper deux buzzers.

Projet réalisé en binôme : Bilal Azelmad et Anouar El Bouzaidi.

## Matériel

- ESP32-WROOM
- 1 buzzer actif (broche 2) et 1 buzzer passif (broche 21)
- Batterie externe pour l'alimentation
- Téléphone ou PC sur le même réseau Wi-Fi

## Fonctionnement

1. L'ESP32 se connecte au Wi-Fi avec la bibliothèque `WiFi.h` et affiche son adresse IP sur le moniteur série.
2. Il sert une page HTML avec un bouton par buzzer.
3. Chaque bouton envoie une requête GET (`/2/on`, `/2/off`, `/21/on`, `/21/off`). Le code analyse la requête et commande la broche correspondante.
4. L'état de chaque buzzer s'affiche sur la page et sur le moniteur série.

## Utilisation

1. Ouvrir `esp32_wifi_buzzer.ino` dans l'Arduino IDE (carte ESP32 installée).
2. Remplacer `NOM_DU_RESEAU_WIFI` et `MOT_DE_PASSE_WIFI` par les identifiants de votre réseau.
3. Téléverser, ouvrir le moniteur série à 115200 bauds, puis noter l'adresse IP affichée.
4. Saisir cette adresse dans le navigateur.
