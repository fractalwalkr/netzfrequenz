# Erweiterungen

Die Frequenz wird zusätzlich zum Serial-Output auch auf dem einem 2.8 TTF-Display ausgegeben.

Die Genauigkeit konnte zudem durch folgende Massnahmen erhöht werden:

* Betrieb ohne Arduino Board direkt mit einem ATMega328-Chip und einem 16MHz Quarz. Die Arduino Unos haben statt einem Quarz nur einen ungenaueren Resonator.
* PROBE_COUNT 500 statt 50. Ausgabe ist nun alle 10 Sekunden, aber dafür viel genauer und ohne Jitter.

Bei Testmessungen war die Abweichung zum Wert auf www.netzfrequenz.info bei +0.005.

# Ausblick

Messwerte auf SD-Karte schreiben.
