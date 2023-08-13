Der SmartBot hat zwei verschiedene Modi. In ihrer Grundfunktion tun beide erstmal das gleiche.
Sie wählen die Karte, die in die kürzest mögliche Reihe geht und keine Punkte verursacht aus.
Der SmartBot der mit dem Parameter True initialisiert wird, wählt, wenn es mehrere Karten gibt, die in die kürzest mögliche Reihe gehen, die mit der kleinsten Differenz aus

Bei einem Spiel mit 10 Karten pro Spieler und 10 Runden, schneidet der Bot mit dem Parameter False besser gegen die primitiven Bots ab.
Bei einem Spiel zwischen den beiden Smarten Bots ist das Ergebnis oft ausgeglichen.

Erhöht man jedoch die Anzahl der Karten pro Spieler oder sowohl die Anzahl der Karten und die Anzahl der Runden (aber nie nur die Rundenzahl)
führt dies sowohl zu einer erhöhten Gewinnchance der Smarten Bots gegen die Primitven, als auch dazu, dass der Smartbot(true) mit einer hohen Chance gegen den SmartBot(false) gewinnt.
Diese Parameter lassen sich in der GameControl auf Zeile 66,67 und 71 in der Funktion startGame() ändern.

Die Ergebnisse der BotvsBot Durchläufe bei 10 und 52 Runden wurden als png in dieses Git hohgeladen.

Nach dem Klonen des Git Repositorys muss lediglich wahlweise entweder 6Nimmt oder GameTest oder beides als Startprojekt ausgewählt werden
