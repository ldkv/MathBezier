# MathBezier
Projet académique - 4A 3DJV ESGI 2016: implémentation et démonstration sous OpenGL d'algorithme pour générer la courbe Bézier appris dans la classe de Mathématique d'Infographie.

========================================================================================================================================

- Ctrl + A pour ajouter un nouveau groupe de contrôle
- Clique gauche pour commencer la saisie les points
- Clique droite pour finir la saisie
- Ctrl + N pour effacer la scène et les données
- Pour activer les options locales, il faut choisir un groupe de contrôle en cliquant gauche (en dehors de la phase de saisie) sur un point quelconque du groupe. 
- Le groupe sélectionné est de couleur BLANC
- Pour choisir plusieurs groupes, garder CTRL puis clique gauche sur les groupes
- Le raccordement impose des nouveaux points si un seul groupe est sélectionné. Si 2 groupes sont sélectionnés, ils seront raccordés (2ème raccordé au 1er).
- 4 options de personnaliser les couleurs pour chaque groupe de contrôle:
	+ couleur dy polygone de contrôle original
	+ couleur de la courbe généré par l'algorithme Casteljau
	+ couleur des nouveaux points de contrôle par la méthode Corner Cutting
	+ couleur de la courbe générée par la technique Corner Cutting
- Les couleurs NOIR et BLANC sont réservées, on ne peut pas choisir ces couleurs
- Les options sont aussi accessibles par les raccourcis
