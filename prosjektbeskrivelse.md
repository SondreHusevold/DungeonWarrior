# Prosjektarbeid i C++ 2015
* **Tittel**: Spill uten tittel
* **Gruppemedlemmer**: s198755, s198761

## Prosjektbeskrivelse

Dette er vårt prosjekt i C++, våren 2015. Vi skal lage en roguelike dungeon crawler ala [Nethack](http://www.nethack.org/)/[Pixel Dungeon](http://pixeldungeon.watabou.ru/).

Det ligger et førsteutkast av klassediagram i repoet. Det vil bli endringer ettersom vi prøver å finne den beste løsningen for spillet.

## Hovedfunksjonalitet i korte trekk

Vi kommer til å bruke Qt for å vise GUI og tiles og bruker et åpent og gratis fanmade tileset fra [Dwarf Fortress](http://www.bay12games.com/dwarves/) kalt [Spacefox](http://www.bay12forums.com/smf/index.php?topic=129219.0) for å gi spillet grafikk, mens resten blir C++ kode. Målet er å ha en barebones dungeon crawler med player, noen monstre, random labyrinth generation, items og forskjellige floors. 

Her er en prototype hvordan vi håper at det vil se ut: ![alt tag](http://a.pomf.se/ivwigf.png)

## Designmål: 

Utvidbart, modulært, gjenbrukbarhet, til en viss grad reponsivt. 

## Avgrensning:

Et barebones dungeon crawler spill med et godt utvalg tilfeldig genererte monstre, tilfeldig genererte labyrinter med et godt utvalg tilfeldig genererte utstyr til spilleren, med spilleregenskaper som liv, styrke og beskyttelse. Et egen interface for utstyr og annet man plukker opp under ferden. Vi ønsker et spill som alltid er nytt hver gang du spiller, og som er umulig å fullføre men er likevel gøy å spille.

Hvis vi får tid vil vi også legge inn spillvaluta og butikker inne i labyrintene slik at det er mulig å kjøpe/selge utstyr man finner.

Minimumkrav:
* Tilfeldig labyrint generering
* Bevegelse i labyrinten hvor spilleren har enkle angrep og interaktivitet.
* Grafikk på et vis, om vi så må bruke ASCII.
