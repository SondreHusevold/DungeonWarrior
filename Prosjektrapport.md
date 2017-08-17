Prosjektrapport

Arbeidsfordelig:
Med git har vi hatt mulighet til å jobbe fleksibelt med alle klasser uavhengig av hverandre. Vi har hatt arbeidsfordeling.md som utgangspungt til arbeidet, men begge har bidratt med feilrettinger og forbedringer i de fleste større klassene. 
Arbeidet med QT og de visuelle elementene viste seg å være større enn vi først antok. Begge har derfor måtte bidra med ferdigstilling av blant annet creature, player, monster og item. Commit loggen på git skal vise hvem som har gjort hva der. 
Ansvars fordeling er i utgangspunket følgende:

Sondre:
-	mainwindow
-	map
-	inventoryuiitem
-	game_button
-	GUI_handler
-	creature
-	player
-	monster
-	item
Magnus:
-	position
-	visible
-	clickable
-	reportable
-	block
-	level
-	game
-	factoriene for monstere
-	item_database


Prosjektprosessen:
Vi brukte noen dager på å lage klassediagram og sekvensdiagram før vi startet med selve kodingen. Føler vi fikk igjen for dette ved at selve implementeringen av programmet gikk relativt problemritt. Sekvensdiagrammene ble kunn brukt for planlegging av programmet og er ikke oppdatert for det ferdige produktet.
Vi har ikke jobbet med QT tidligere. Det var derfor noe usikkerhet rundt dette. Tanken var, som beskrevet i de første klasse diagrammene, at mainwindow eller en annen qt-klasse skulle koples mot gui_handler med signaler slik at gui_handler kan tolke disse å kalle riktige metoder i game. Ettersom vi statt oss mer inn i QT, endte vi opp med en løsning der gui_handler for det meste har static metoder som endrer de visuelle elementene. QT virker heller ikke som et passende verktøy å utvikle spill med. 

Produktet:
Vi føler selv vi har fått til mye av det vi ønsket. Spillet kjører problemfritt på OSX, linux mint og windows 8.1(med #include <time.h> lagt til i game.cpp) og det vi har funnet av bugs er rettet opp. Vi valgte å gå bort ifra noen av ideene fra prosjektbeskrivelsen og heller bruke mer tid på andre ting. Egen spill valuta og ingame butikk med kjøp og salg av utstyr ble ikke prioritert. Dette i tillegg til “consumeable” items er noe vi kunne ha lagt til med mer tid. Vi valgte heller å lage et større utvalg av monstere og items enn å starte på noe vi ikke veit om vi hadde rukket å fullføre. 

