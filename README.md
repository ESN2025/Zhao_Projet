# Zhao_lab4
## Introduction
Lors du dernier laboratoire, nous prévoyons de concevoir un système permettant d’afficher les données de l’accéléromètre (ADXL345) de la carte de développement DE10-Lite sur les afficheurs 7 segments. La communication avec l’accéléromètre sera réalisée à l’aide d’un module IP I2C dédié. De plus, un bouton poussoir permettra de basculer entre les différentes axes à afficher.

## Architecture du sytème
![alt text](image/llab2.png)
Le système est composé d’une architecture de base comprenant un processeur Nios II, une mémoire RAM, une horloge (Clock) et un port JTAG. À cette architecture s’ajoutent des périphériques supplémentaires, notamment cinq PIO de 4 bits pour les cinq afficheurs 7 segments, dont le cinquième est dédié à l’affichage du signe, un PIO de 1 bit pour le bouton poussoir (KEY0), un Timer de 32 bits réglé sur une période de 1s, ainsi qu’un module OpenCores I2C pour la communication avec l’accéléromètre.

## Platform Designer
L'architecture sous Platform Designer (QSYS) est donc la suivante :
![alt text](image/lab2.PNG)  
Sous Quartus, nous commençons par récupérer le fichier BCD7SEG.vhd, écrit lors du lab 2, afin d’y ajouter une condition permettant d’afficher le signe “-” sur un afficheur 7 segments. Pour cela, j’ai décidé d’attribuer la valeur 10 au dernier 7 segments lorsque le nombre à afficher est négatif.

Ensuite, nous décrivons le fichier toplevel.vhd, dans lequel nous connectons les composants créés sous Qsys aux afficheurs 7 segments.

Après cela, nous effectuons le pin assignment (assignation des broches) des afficheurs 7 segments et du bouton poussoir, soit en utilisant le Pin Planner, soit en modifiant directement le fichier .qsf.
![alt text](image/lab2.PNG) 
Enfin, nous réalisons une compilation complète du design. Si aucune erreur n’est détectée, nous pouvons alors programmer l’architecture sur la carte FPGA.

## Nios-II
Depuis le terminal Nios II, nous commençons par créer le Makefile et générer le BSP. Une fois cette étape terminée, nous écrivons nos scripts en langage C, les compilons, puis les téléversons sur notre carte FPGA.
## Travail effectué
Nous avons ensuite développé deux fichiers, main.c et main1.c, qui regroupent les fonctions nécessaires pour effectuer des opérations de lecture et d’écriture sur les registres via le protocole I2C. Les données sont ensuite affichées sur l’interface UART, avec un rythme d’affichage contrôlé par un timer. Enfin, nous avons calibré la carte afin d’obtenir des valeurs cohérentes et exploitables.

## I2C
Dans un premier temps, j’ai développé les fonctions principales nécessaires à mon projet. La fonction read_adxl345() permet de lire les registres 0x32, 0x33, 0x34, 0x35, 0x36 et 0x37, correspondant respectivement aux coordonnées X0, X1, Y0, Y1, Z0 et Z1. J’ai également implémenté la fonction write_adxl345(), qui permet d’écrire une donnée dans un registre précis. Enfin, j’ai utilisé la fonction alt_printf() pour afficher les valeurs lues en hexadécimal, ce qui m’a permis de vérifier la validité des données issues du capteur ADXL345.
![alt text](image/lab2.PNG)  

## Résultats
https://github.com/user-attachments/assets/81f36d26-1ef1-4b58-be3d-ca3ed8f2fbcd

## Conclusion
Ce projet a permis de maîtriser la communication I2C entre un FPGA et un capteur externe, ainsi que le traitement et l’affichage des données en temps réel. Les différentes étapes ont été validées grâce à un affichage dans le terminal et sur des afficheurs 7 segments, garantissant le bon fonctionnement de l’ensemble du système. De plus, il m’a permis d’acquérir une compréhension plus approfondie des mécanismes d’interruption et de l’utilisation des timers dans un système embarqué.
